#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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
int GLOBAL_inode_offset;
/* based on documentation by IBM: https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/apis/pread.htm */
void setup(char **argv);
void superblock();
void group();
void free_block_entries();

int main (int argc, char **argv) {
    setup(argv);
    superblock();
    group();
    free_block_entries();
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

void free_block_entries(){
    int byte_iter; //iterate through byte (vertical)
    int bit_iter; //iterate through bit (horizontal)
    int curr_num = 0;
    char buf[block_size];
    off_t off = block_size * block_bitmap;
    
    //read entire bitmap into buffer
    pread(FD, buf, 1024, off);
    
    //iterate through everything
    for (byte_iter = 0; byte_iter < num_blocks; byte_iter++) {
        char curr_byte = buf[byte_iter];
        for (bit_iter = 0; bit_iter < 8; bit_iter++) {
            if ((curr_byte & (1<< bit_iter)) == 0) {
                printf("BFREE,%u\n", curr_num);
            }
            curr_num++;
        }
    }
}

void free_inode_entries() {
// same as free_block_entries but with inode as the start one
}

/* What we need:
 INODE
 inode number (decimal)
 ----- file type ('f' for file, 'd' for directory, 's' for symbolic link, '?" for anything else)
 mode (low order 12-bits, octal ... suggested format "%o")
 owner (decimal)
 group (decimal)
 link count (decimal)
 time of last I-node change (mm/dd/yy hh:mm:ss, GMT)
 modification time (mm/dd/yy hh:mm:ss, GMT)
 time of last access (mm/dd/yy hh:mm:ss, GMT)
 file size (decimal)
 number of (512 byte) blocks of disk space (decimal) taken up by this file
 */

/*void inode_summary(){
    GLOBAL_inode_offset = 0;
    struct ext2_inode inode;
    //char buf[num_inodes * inode_size];     // max = # of inodes * inode size
    
    for (i =0; i < num_inodes; i++){
        
        int offset = block_numof_first_inode_block * block_size;
        int i;
        char mod_time[8];
        char last_access_time[8];
        //int inode_mode = inode.i_mode;
        int owner = inode.i_uid;
        int group = inode.igid;
        int link_count = inode.i_links_count;
        struct tm * time_info_create = inode.i_ctime;
        strftime(timeString, 8, "%H:%M:%S", time_info_create);
        struct tm * time_info_mod = inode.m_mtime;
        strftime(timeString, 8, "%H:%M:%S", time_info_mod);
        struct tm * time_info_access = inode.i_atime;
        strftime(last_access_time, 8, "%H:%M:%S", time_info_access);
        int file_size = inode.i_size;
        int block_size = inode.i_blocks;
        
        pread (FD, &inode, sizeof(inode), offset + (inode_size *i));
        inode_num = i +1;
        char mode_type = '?';
        if (S_IFDIR & inode.i_mode){
            mode_type = 'd';
            printf ("INODE,%d,%c,%o,%d,%d,%d,%s,%s,%s,%d,%d", i, file_type, mode_type, owner, group, link_count, time_info_create, time_info_mod, time_info_access, file_size, block_size);
            filedirectory_handler(struct ext2_inode inode);
        }
        else if (S_IFREG & inode.i_mode){
            mode_type = 'f';
            printf ("INODE,%d,%c,%o,%d,%d,%d,%s,%s,%s,%d,%d", i, file_type, mode_type, owner, group, link_count, time_info_create, time_info_mod, time_info_access, file_size, block_size);
            filedirectory_handler(struct ext2_inode inode);
        }
        else if (S_IFLNK & inode.i_mode){
            mode_type = 's';
            if (file_size <= 60){
                filedirectory_handler(struct ext2_inode inode);
            }
        }
        else {
            printf ("INODE,%d,%c,%o,%d,%d,%d,%s,%s,%s,%d,%d", i, file_type, mode_type, owner, group, link_count, time_info_create, time_info_mod, time_info_access, file_size, block_size);
        }
    }
    // 1 - 12 are direct
    // 13- 268 -> follow the pointer and then iterate til 255
        //extract the information using ext2_inode from header file
}

char * filedirectory_handler(struct ext2_inode inode){
    char temp_str [15];
    int i = 0;
    printf ("DIRENT,");
    for (i; i < 14; i++){
        printf ("%d,", inode.i_blocks[i])
    }
    printf ("\n");
}
    
void handle_directory_entries(int parent_inode){
    struct ext2_dir_entry dir;
    int dir_len = dir.rec_len;
    int i;
    for (i; i < (num_blocks + 1) * block_size i; i += dir_len) {
        pread(fs_fd, &dir_entry, sizeof(struct ext2_dir_entry), num_blocks * block_size);
        }
    printf ("DIRENT", dir.parent_inode, dir_len, dir.name_len, dir.name,)
}
    
*/
