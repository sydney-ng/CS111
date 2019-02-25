#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "ext2_fs.h"

//Global Variables
int FD;
char system_image[100];

int num_blocks;
int num_inodes;
int block_size;
int inode_size;
int blocks_per_group;
int inodes_per_group;
int first_non_reserved_inode;
int inode_bitmap;
int block_bitmap;
struct ext2_group_desc G;
int block_numof_first_inode_block;
int GLOBAL_directory_offset = 0;
/* based on documentation by IBM: https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/apis/pread.htm */

// functions:
void setup(char **argv);
void superblock();
void group();
void free_entries(int bitmap, char type);
void inode_summary ();
void get_time(struct ext2_inode inode, char type);
void handle_valid_inode(struct ext2_inode inode, int inode_number, int inode_mode, int inode_linkcount);
unsigned createMask(unsigned x, unsigned y);
void filedirectory_handler(struct ext2_inode inode, char data_type, int parent_inode);
char determine_filetype (struct ext2_inode inode);
void handle_directory_entries(int parent_inode, int current_block);
void pre_directory_handler(struct ext2_inode inode, int inode_number);

int main (int argc, char **argv) {
    setup(argv);
    superblock();
    group();
    free_entries(block_bitmap, 'b');
    free_entries(inode_bitmap, 'i');
    inode_summary();
}

void superblock(){
    char buf[1024];
    off_t off = 1024;
    pread (FD, buf, sizeof(buf), off);
    num_blocks = *(int*)(buf + 4); // 4 offset = s_blocks_count
    num_inodes= *(int*)(buf + 0); // 0 offset = s_inodes_count
    block_size = 1024 << (*(int*)(buf + 24)); // 24 offset = s_log_block_size
    inode_size = *(int*)(buf + 88); // 84 offset = s_inode_size
    blocks_per_group = *(int*)(buf + 32); // 32 offset = s_blocks_per_group
    inodes_per_group = *(int*)(buf + 40); // 40 offset = s_inodes_per_group
    first_non_reserved_inode = *(int*)(buf + 84); // 84 offset = s_first_ino
    printf ("SUPERBLOCK,%d,%d,%d,%d,%d,%d,%d\n", num_blocks, num_inodes, block_size, inode_size, blocks_per_group, inodes_per_group, first_non_reserved_inode);
}

void setup(char **argv){
    strcpy (system_image, argv[1]);
    if ((FD = open(system_image, O_RDONLY)) < 0)
        perror("open() error");
    return;
}

//start using the header file
void group(){
    off_t off = 1024 + 1024; //add an extra 1024 for size of superblock
    pread (FD, &G, sizeof(G), off);
    int group_number = 0;
    int inodes_in_group = num_inodes;
    int free_blocks_in_group = G.bg_free_blocks_count;
    int free_inodes_in_group = G.bg_free_inodes_count;
    block_bitmap = G.bg_block_bitmap;
    inode_bitmap = G.bg_inode_bitmap;
    block_numof_first_inode_block = G.bg_inode_table;
    printf ("GROUP,%d,%d,%d,%d,%d,%d,%d,%d\n", group_number, num_blocks, inodes_in_group, free_blocks_in_group,free_inodes_in_group, block_bitmap, inode_bitmap, block_numof_first_inode_block);
}

void free_entries(int bitmap, char type){
    int byte_iter; //iterate through byte (vertical)
    int bit_iter; //iterate through bit (horizontal)
    int curr_num = 0;
    char buf[block_size];
    off_t off = block_size * bitmap;
    
    //read entire bitmap into buffer
    pread(FD, buf, 1024, off);
    
    //iterate through everything
    for (byte_iter = 0; byte_iter < num_blocks; byte_iter++) {
        char curr_byte = buf[byte_iter];
        for (bit_iter = 0; bit_iter < 8; bit_iter++) {
            curr_num++;
            if ((curr_byte & (1<< bit_iter)) == 0) {
                if (type == 'b'){
                    printf("BFREE,%u\n", curr_num);
                }
                else {
                    printf("IFREE,%u\n", curr_num);
                }
            }
        }
    }
}

/* based on time: https://stackoverflow.com/questions/761791/converting-between-local-times-and-gmt-utc-in-c-c */
//TODO: convert this to string to send back to parent
void get_time(struct ext2_inode inode, char type) {
    char time_return_val[25];
    time_t actual_time;
    if (type == 'c'){
        actual_time = inode.i_ctime;
    }
    else if (type == 'm'){
        actual_time = inode.i_mtime;
    }
    else { // for access time
        actual_time = inode.i_ctime;
    }
    
    struct tm* converted_time = gmtime(&actual_time);
    strftime(time_return_val, 25, "%m/%d/%y %H:%M:%S", converted_time);
    printf ("%s,", time_return_val);
}

void inode_summary(){
    int i;
    int offset = block_numof_first_inode_block * block_size;
    struct ext2_inode inode;
    
    for (i = 0; i < num_inodes; i++){
        pread (FD, &inode, sizeof(inode), offset + (inode_size *i));
        //check if this is a valid inode
        if (inode.i_mode && inode.i_links_count){
            //inodes start @ 1 but our iterator starts at 0
            handle_valid_inode(inode, i+1, inode.i_mode,inode.i_links_count);
        }
    }
}

/* What we need:
 1 INODE
 2 inode number (decimal)
 3 ----- file type ('f' for file, 'd' for directory, 's' for symbolic link, '?" for anything else)
 4 mode (low order 12-bits, octal ... suggested format "%o")
 5 owner (decimal)
 6 group (decimal)
 7 link count (decimal)
 8 time of last I-node change (mm/dd/yy hh:mm:ss, GMT)
 9 modification time (mm/dd/yy hh:mm:ss, GMT)
 10 time of last access (mm/dd/yy hh:mm:ss, GMT)
 11 file size (decimal)
 12 number of (512 byte) blocks of disk space (decimal) taken up by this file
 */

void handle_valid_inode(struct ext2_inode inode, int inode_number, int inode_mode, int inode_linkcount) {
    //extract easy stuff from inode
    char data_type;
    int owner = inode.i_uid;
    int group = inode.i_gid;
    int file_size = inode.i_size;
    int block_size = inode.i_blocks;
    
    data_type = determine_filetype (inode);
    printf ("INODE,%d,", inode_number); // #1, #2
    printf ("%c,%o,%d,%d,%d,", data_type, (inode.i_mode & 0x0FFF), owner, group, inode_linkcount); //#3-7
    get_time(inode, 'c'); // #8
    get_time(inode, 'm'); // #9
    get_time(inode, 'a'); // #10
    printf ("%d,%d", file_size, block_size); // #11-12
    
    if (data_type != '?'){
        if ((data_type == 's' && file_size <= 60) || data_type != 's'){
            filedirectory_handler(inode, data_type, inode_number);
        }
    }
    
    if (data_type == 'd'){
        pre_directory_handler(inode, inode_number);
    }
    printf ("\n");
}


void pre_directory_handler(struct ext2_inode inode, int inode_number){
    int i;
    for (i = 0; i < 12; i++){
        if (inode.i_block[i] == 0){ // check to make sure it's bein used
            handle_directory_entries(inode_number, i); //inode_number is the parent entry
        }
    }
}

/*
 1. DIRENT
 2. parent inode number (decimal) ... the I-node number of the directory that contains this entry
 3. logical byte offset (decimal) of this entry within the directory
 4. inode number of the referenced file (decimal)
 5. entry length (decimal)
 6. name length (decimal)
 7. name (string, surrounded by single-quotes). Don't worry about escaping, we promise there will be no single-quotes or commas in any of the file names. */

void handle_directory_entries(int parent_inode, int current_block){
    struct ext2_dir_entry D;
    int dir_i = 0;
    int block_iter;
    int dir_len;
    int entry_len = 0;
    int name_len = 0;
    char buf[block_size];
    
    //iterate from current block -> blocksize, incrementing from length of directory
    for (block_iter = 0; block_iter < EXT2_NDIR_BLOCKS; block_iter += entry_len){
        //pread that block (offset = current_block * BLOCK_SIZE + off, & extract the information
        pread (FD, &D, sizeof(D), current_block * block_size + block_iter);
        entry_len = D.rec_len;
        name_len = D.name_len;
        printf ("global directory offset is :%d\n", block_size * current_block);
        printf ("DIRENT,%d,%d,%d,%d,%d,%s\n", parent_inode, GLOBAL_directory_offset, current_block,entry_len, name_len, D.name);
        break;
    }
}

char determine_filetype (struct ext2_inode inode){
    char data_type = '?';
    if (S_IFDIR & inode.i_mode){
        data_type = 'd';
    }
    else if (S_IFREG & inode.i_mode){
        data_type = 'f';
    }
    else if (S_IFLNK & inode.i_mode){
        data_type = 's';
    }
    return data_type;
}

void filedirectory_handler(struct ext2_inode inode, char data_type, int parent_inode){
    char temp_str [15];
    int i;
    for (i=0; i < 15; i++){
        printf (",%d", inode.i_block[i]);
    }
}
