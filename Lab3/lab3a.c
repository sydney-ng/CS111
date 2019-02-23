#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

//Global Variables
int FD;
char system_image[100];
//for SuperBlock:
    int num_blocks;
    int num_inodes;
    int block_size;
    int inode_size;
    int blocks_per_group;
    int inodes_per_group;
    int first_non_reserved_inode;

/* based on documentation by IBM: https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/apis/pread.htm */
void setup(char **argv);
void superblock();

int main (int argc, char **argv) {
    setup(argv);
    superblock();
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
