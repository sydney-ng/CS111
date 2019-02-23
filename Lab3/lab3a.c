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

struct ext2_group_desc G;

/* based on documentation by IBM: https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/apis/pread.htm */
void setup(char **argv);
void superblock();
void group();

int main (int argc, char **argv) {
    setup(argv);
    superblock();
    group();
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

void group(){
    off_t off = 1024 + 1024; //add an extra 1024 for size of superblock
    pread (FD, &G, sizeof(G), off);
    int group_number = 0;
    int num_blocks_in_group = num_blocks;
    int inodes_in_group = num_inodes;
    int free_blocks_in_group = G.bg_free_blocks_count;
    int free_inodes_in_group = G.bg_free_inodes_count;
    int block_num_of_free_block_bitmap = G.bg_block_bitmap;
    int block_num_of_free_inode_bitmap = G.bg_inode_bitmap;
    int block_numof_first_inode_block = G.bg_inode_table;
printf ("GROUP,%d,%d,%d,%d,%d,%d,%d,%d\n", group_number, num_blocks_in_group, inodes_in_group, free_blocks_in_group,free_inodes_in_group, block_num_of_free_block_bitmap,block_num_of_free_inode_bitmap, block_numof_first_inode_block);
}
