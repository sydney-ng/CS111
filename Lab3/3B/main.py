import json
import csv

sblock_dict = {}
group_dict = {}
inode_dict = {}
dirent_dict = {}
indirect_dict = {}
bfree_list = []
ifree_list = []

def create_all_dictionaries(all_lines):
    inode_dict_counter = 0
    dirent_dict_counter = 0
    indirect_dict_counter = 0
    for lines in all_lines:
        if lines[0] == 'SUPERBLOCK':
            create_sblock_dict(lines)
        elif lines[0] == 'GROUP':
            create_group_dict(lines)
        elif lines[0] == 'BFREE':
            bfree_list.append(int(lines[1]))
        elif lines[0] == 'IFREE':
            ifree_list.append(int(lines[1]))
        elif lines[0] == 'INODE':
            inode_dict_counter = create_inode_dict(lines, inode_dict_counter)
        elif lines[0] == 'DIRENT':
            dirent_dict_counter = create_dirent_dict(lines, dirent_dict_counter)
        elif lines[0] == 'INDIRECT':
            indirect_dict_counter = create_indirent_dict(lines, indirect_dict_counter)

def create_sblock_dict(line):
    sblock_dict['total_num_blocks'] = int(line[1])
    sblock_dict['total_num_inodes'] = line[2]
    sblock_dict['block_size'] = line[3]
    sblock_dict['inode_size'] = line[4]
    sblock_dict['blocks_per_group'] = line[5]
    sblock_dict['inodes_per_group'] = line[6]
    sblock_dict['first_non_res_inode'] = line[7]

def create_group_dict(line):
    group_dict['group_num'] = line[1]
    group_dict['num_blocks_per_group'] = line[2]
    group_dict['num_inodes_per_group'] = line[3]
    group_dict['num_free_blocks'] = line[4]
    group_dict['num_free_inodes'] = line[5]
    group_dict['free_block_bitmap'] = line[6]
    group_dict['free_inode_bitmap'] = line[7]
    group_dict["first_inode_block"] = line[8]

def create_inode_dict(line, entry_number):
    new_dict_entry = {}
    new_dict_entry['inode_num'] = line[1]
    new_dict_entry['file_type'] = line[2]
    new_dict_entry['mode'] = line[3]
    new_dict_entry['owner'] = line[4]
    new_dict_entry['group'] = line[5]
    new_dict_entry['link_count'] = line[6]
    new_dict_entry['time_last_changed'] = line[7]
    new_dict_entry['time_last_modified'] = line[8]
    new_dict_entry['time_last_accessed'] = line[9]
    new_dict_entry['file_size'] = line[10]
    new_dict_entry['num_blocks_taken'] = line[11]
    
    if len(line) > 12:
        counter = 12
        actual_index = 0
        while counter < 27:
            new_dict_entry[actual_index] = line[counter]
            counter = counter + 1
            actual_index = actual_index + 1

inode_dict[entry_number] = new_dict_entry
return entry_number + 1

def create_dirent_dict(line, entry_number):
    new_dict_entry = {}
    new_dict_entry['inode_parent'] = line[1]
    new_dict_entry['logical_block_offset'] = line[3]
    new_dict_entry['file_inode_number'] = line[4]
    new_dict_entry['entry_len'] = line[4]
    new_dict_entry['name_len'] = line[5]
    new_dict_entry['name'] = line[6]
    
    dirent_dict[entry_number] = new_dict_entry
    return entry_number + 1

def create_indirent_dict(line, entry_number):
    new_dict_entry = {}
    new_dict_entry['inode_parent'] = line[1]
    new_dict_entry['level_of_indirection'] = line[3]
    new_dict_entry['logical_block_offset'] = line[4]
    new_dict_entry['indirect_block_number'] = line[4]
    new_dict_entry['block_num_of_referenced_block'] = line[5]
    indirect_dict[entry_number] = new_dict_entry
    return entry_number + 1

def check_blocks():
    #handling INVALID/RESERVED
    seen_blocks = [] # list of seen blocks
    block_start, block_end = calc_block_start_end()
    for inode_keys in inode_dict:
        current_inode = inode_dict[inode_keys]
        if current_inode['file_type'] == 's':
            if current_inode[0] in current_inode:
                seen_blocks = check_inode_blocks(block_start, block_end, current_inode, seen_blocks)
        else:
            seen_blocks = check_inode_blocks(block_start, block_end, current_inode, seen_blocks)
        seen_blocks = check_indirect_blocks(block_start, block_end, seen_blocks)
        # handling UNREFERENCED & ALLOCATED BLOCKS
    handle_referenced_allocated_blocks (block_start, block_end, seen_blocks)

def handle_referenced_allocated_blocks(block_start, block_end, seen_blocks):
    temp = block_start
    while temp <= block_end:
        if (temp not in bfree_list) and (temp not in seen_blocks):
            print "UNREFERENCED BLOCK " + str(temp)
        elif (temp in bfree_list) and (temp in seen_blocks):
            print "ALLOCATED BLOCK " + str(temp) + " ON FREELIST"

def check_inode_blocks(block_start, block_end, current_inode, seen_blocks):
    for i in range(12):
        flag = True
        if int(current_inode[i]) != 0:
            if int(current_inode[i]) < block_start:
                handle_block_error("RESERVED", current_inode[i], "inode", current_inode["inode_num"], '0', None)
                flag = False
            elif int(current_inode[i]) > block_end:
                handle_block_error("INVALID", current_inode[i], "inode", current_inode["inode_num"], '0', None)
                flag = False
        if flag:
            seen_blocks.append(int(current_inode[i]))
    return seen_blocks

def check_indirect_blocks(block_start, block_end, seen_blocks):
    for indir_keys in indirect_dict:
        flag = True
        curr_indir_inode = indirect_dict[indir_keys]
        curr_indir_inode_block_num = int(curr_indir_inode ['block_num_of_referenced_block'])
        # check if the block is invalid
        if curr_indir_inode_block_num < block_start:
            handle_block_error("RESERVED", curr_indir_inode_block_num, "indir", curr_indir_inode["inode_parent"], curr_indir_inode["logical_block_offset"], curr_indir_inode["indirect_block_number"])
            flag = False
        elif curr_indir_inode_block_num > block_end:
            handle_block_error("INVALID", curr_indir_inode_block_num, "indir", curr_indir_inode["inode_parent"], curr_indir_inode["logical_block_offset"], curr_indir_inode["indirect_block_number"])
            flag = False
        if flag:
            seen_blocks.append(int(curr_indir_inode ['block_num_of_referenced_block']))
    return seen_blocks

def handle_block_error(err_type, invalid_block_num, data_type, inode_number, offset_number, indirection_level):
    if data_type == "inode":
        print err_type + " BLOCK " + invalid_block_num + " IN INODE " + inode_number + " AT OFFSET " + offset_number
    else:
        if indirection_level == '1':
            indirect_level_str = " INDIRECT "
        elif indirection_level == '2':
            indirect_level_str = " DOUBLE INDIRECT "
        else:
            indirect_level_str = " TRIPLE INDIRECT "
        if int(offset_number) > 1024:
            offset_number = offset_number % 1024
        print err_type + indirect_level_str + "BLOCK " + invalid_block_num + " IN INODE " + inode_number + " AT OFFSET " + offset_number

def calc_block_start_end():
    inode_bitmap_block_num = int (group_dict["first_inode_block"])
    # num blocks inode table takes = total number of inodes in a group/ # of inodes per block
    num_inode_table_blocks = int (sblock_dict['total_num_inodes']) / int(group_dict['num_inodes_per_group'])
    # where bitmap will start + N blocks of inode table
    data_block_start_num = inode_bitmap_block_num + num_inode_table_blocks
    data_block_end_num = sblock_dict['total_num_blocks']
    return data_block_start_num, data_block_end_num

def error_handler():
    print "this is an invalid node"

def open_file(file_name):
    with open (file_name, "rb") as f:
        all_lines = csv.reader(f, delimiter=',')
        create_all_dictionaries(all_lines)

def main ():
    open_file('trivial.csv')
    check_blocks()

main ()
