#!/usr/bin/env python

import csv
import sys
import os

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
    sblock_dict['total_num_inodes'] = int(line[2])
    sblock_dict['block_size'] = int(line[3])
    sblock_dict['inode_size'] = int(line[4])
    sblock_dict['blocks_per_group'] = int(line[5])
    sblock_dict['inodes_per_group'] = int(line[6])
    sblock_dict['first_non_res_inode'] = int(line[7])


def create_group_dict(line):
    group_dict['group_num'] = line[1]
    group_dict['num_blocks_per_group'] = line[2]
    group_dict['num_inodes_per_group'] = line[3]
    group_dict['num_free_blocks'] = line[4]
    group_dict['num_free_inodes'] = line[5]
    group_dict['free_block_bitmap'] = line[6]
    group_dict['free_inode_bitmap'] = line[7]
    group_dict['first_inode_block'] = line[8]

def create_inode_dict(line, entry_number):
    new_dict_entry = {}
    new_dict_entry['inode_num'] = int(line[1])
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
    entry_number = entry_number + 1
    return entry_number


def create_dirent_dict(line, entry_number):
    new_dict_entry = {}
    new_dict_entry['inode_parent'] = line[1]
    new_dict_entry['logical_block_offset'] = line[2]
    new_dict_entry['file_inode_number'] = line[3]
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
    # handling INVALID/RESERVED
    valid_indir_blocks = []  # valid indirect blocks to make processing faster
    all_valid_block_num_only = []
    block_start, block_end = calc_block_start_end()
    # handle inodes
    for inode_keys in inode_dict:
        current_inode = inode_dict[inode_keys]
        if current_inode['file_type'] == 's':
            if current_inode[0] not in current_inode:
                continue  # will bring you back to the top of the block
        all_valid_block_num_only = handle_inode_blocks(block_start, block_end, current_inode, all_valid_block_num_only)
    # handle indirect blocks
    valid_indir_blocks, all_valid_block_num_only = handle_indirect_blocks(block_start, block_end, valid_indir_blocks,
                                                                          all_valid_block_num_only)
    # handling UNREFERENCED & ALLOCATED BLOCKS
    handle_referenced_allocated_blocks(block_start, block_end, valid_indir_blocks)
    # handling DUPLICATE BLOCKS
    handle_duplicate_blocks(valid_indir_blocks, all_valid_block_num_only)


def is_valid_block(block_num, start, end):
    if (block_num < start) or (block_num >= end):
        return False
    return True


def handle_duplicate_blocks(valid_indir_blocks, all_valid_block_num_only):
    for inode_blocks in inode_dict:
        curr_entry = inode_dict[inode_blocks]
        for i in range(15):
            if curr_entry[i]:
                x = int(curr_entry[i])
                if (x!= 0) and (all_valid_block_num_only.count(x) > 1):
                    if i >= 12:
                        offset, indir_level_str = calc_13_to_15_stuff(i)
                    else:
                        offset = '0'
                        indir_level_str = ''
                    print "DUPLICATE " + indir_level_str + "BLOCK " + str(x) + " IN INODE " + str(curr_entry['inode_num']) + " AT OFFSET " + offset

def handle_referenced_allocated_blocks(block_start, block_end, valid_indir_blocks):
    i1 = block_start  # will iterate from first -> last block
    while i1 < block_end:
        found_block = True
        # check 1:
        if i1 not in bfree_list:  # if it isn't in the bfree list, must be in inode or indir list
            for inode_blocks in inode_dict:  # check to see if it's in the list of valid inodes
                for i in range(15):
                    if int(inode_dict[inode_blocks][i]) == i1:
                        found_block = False
                        break
                if found_block:  # if it wasn't found in inode list
                    for indir_blocks in valid_indir_blocks:
                        if int(indir_blocks['block_num_of_referenced_block']) == i1:
                            found_block = False
            if found_block:  # if flag is still true, then it is unreferenced
                print "UNREFERENCED BLOCK " + str(i1)
        elif i1 in bfree_list:  # if it is in the bfree list, then it shouldn't be in inode/indir blocks
            found_block2 = True
            for inode_blocks in inode_dict:  # check to see if it's in the list of valid inodes
                for i in range(15):
                    if int(inode_dict[inode_blocks][i]) == i1:
                        found_block2 = False
                        print "ALLOCATED BLOCK " + str(i1) + " ON FREELIST"
            if found_block2:
                for indir_blocks in valid_indir_blocks:
                    if int(indir_blocks["block_num_of_referenced_block"]) == i1:
                        print "ALLOCATED BLOCK " + str(i1) + " ON FREELIST"
        i1 = i1 + 1


def handle_inode_blocks(block_start, block_end, current_inode, all_valid_block_num_only):
    for i in range(15):
        flag = True
        if int(current_inode[i]) != 0:
            if int(current_inode[i]) < block_start:
                if i < 12:
                    handle_block_error("RESERVED ", current_inode[i], "inode", current_inode["inode_num"], '0', '')
                else:  # 13 - 15
                    offset, indir_lvl_str = calc_13_to_15_stuff(i)
                    handle_block_error("RESERVED ", current_inode[i], "inode", current_inode["inode_num"], offset,
                                       indir_lvl_str)
                flag = False
            elif int(current_inode[i]) > block_end:
                if i < 12:
                    handle_block_error("INVALID ", current_inode[i], "inode", current_inode["inode_num"], '0', '')
                else:  # 13 - 15
                    offset, indir_lvl_str = calc_13_to_15_stuff(i)
                    handle_block_error("INVALID ", current_inode[i], "inode", current_inode["inode_num"], offset,
                                       indir_lvl_str)
                flag = False
        if flag:
            all_valid_block_num_only.append(int(current_inode[i]))
    return all_valid_block_num_only


def calc_13_to_15_stuff(i):
    offset = str(12)
    indir_level_str = ""
    if i + 1 == 13:
        indir_level_str = "INDIRECT "
    elif i + 1 == 14:
        offset = str(256 + 12)
        indir_level_str = "DOUBLE INDIRECT "
    elif i + 1 == 15:
        offset = str((256 * 256) + 256 + 12)
        indir_level_str = "TRIPLE INDIRECT "
    else:
        sys.stderr.write("invalid node being checked")
        exit(1)
    return offset, indir_level_str

def handle_indirect_blocks(block_start, block_end, valid_indir_blocks, all_valid_block_num_only):
    for indir_keys in indirect_dict:
        flag = True
        curr_indir_inode = indirect_dict[indir_keys]
        curr_indir_inode_block_num = int(curr_indir_inode['block_num_of_referenced_block'])
        # check if the block is invalid
        if curr_indir_inode_block_num < block_start:
            handle_block_error("RESERVED", curr_indir_inode_block_num, "indir", curr_indir_inode["inode_parent"],
                               curr_indir_inode["logical_block_offset"], curr_indir_inode["indirect_block_number"])
            flag = False
        elif curr_indir_inode_block_num > block_end:
            handle_block_error("INVALID", curr_indir_inode_block_num, "indir", curr_indir_inode["inode_parent"],
                               curr_indir_inode["logical_block_offset"], curr_indir_inode["indirect_block_number"])
            flag = False
        if flag:
            valid_indir_blocks.append(curr_indir_inode)
            all_valid_block_num_only.append(curr_indir_inode_block_num)
    return valid_indir_blocks, all_valid_block_num_only


def handle_block_error(err_type, invalid_block_num, data_type, inode_number, offset_number, indirection_level):
    if data_type == "inode":
        print  err_type + indirection_level + "BLOCK " + str(invalid_block_num) + " IN INODE " + str(inode_number) + " AT OFFSET " + str(
            offset_number)
    else:
        if indirection_level == '1':
            indirect_level_str = "INDIRECT "
        elif indirection_level == '2':
            indirect_level_str = "DOUBLE INDIRECT "
        else:
            indirect_level_str = "TRIPLE INDIRECT "
        if int(offset_number) > 1024:
            offset_number = offset_number % 1024
            print err_type + indirect_level_str + "BLOCK " + invalid_block_num + " IN INODE " + inode_number + " AT OFFSET " + offset_number

def calc_block_start_end():
    group_size = (sblock_dict['total_num_blocks'] / sblock_dict['blocks_per_group']) + 1
    inode_table_size = ((sblock_dict['total_num_inodes'] * sblock_dict['inode_size']) / sblock_dict['block_size']) + 1
    data_block_start_num = 1 + group_size + 1 + 1 + inode_table_size  # 1 for super block, 1 for block free, 1 for inode free
    data_block_end_num = sblock_dict['total_num_blocks']
    return data_block_start_num, data_block_end_num

def open_file(file_name):
    if os.path.isfile(file_name):
        with open(file_name, "rb") as f:
            all_lines = csv.reader(f, delimiter=',')
            create_all_dictionaries(all_lines)
        return True
    else:
        sys.stderr.write(file_name + " is not a valid file ")
        return False

def check_inodes():
    seen_inodes = []
    for inode_entry in inode_dict:
        curr_entry_type = inode_dict[inode_entry]['file_type']
        curr_entry_value = inode_dict[inode_entry]['inode_num']
        if curr_entry_type == 'f' or curr_entry_type == 'd' or curr_entry_type != 's':
            #if curr_entry_value not in ifree_list:
            #    print "UNALLOCATED INODE " + str(curr_entry_value) + " NOT ON FREELIST"
            if curr_entry_value in ifree_list:
                print "ALLOCATED INODE " + str(curr_entry_value) + " ON FREELIST"
        seen_inodes.append(inode_dict[inode_entry]['inode_num'])
    starting_inode = sblock_dict['first_non_res_inode']
    nodes_to_see = sblock_dict['total_num_inodes']
    while starting_inode < nodes_to_see:
        if starting_inode not in seen_inodes:
            if starting_inode not in ifree_list:
                print "UNALLOCATED INODE " + str(starting_inode) + " NOT ON FREELIST"
        starting_inode = starting_inode + 1
    return seen_inodes

def check_directories(seen_inodes):
    handle_bogus_entries()
    handle_invalid_nodes(seen_inodes) 
    check_roots()

def check_roots():
    link_dict = {}
    for directories in dirent_dict:
        parent = int(dirent_dict[directories]['inode_parent'])
        inode_referenced = int (dirent_dict[directories]['file_inode_number'])
        if '.' not in dirent_dict[directories]['name']:
            if inode_referenced not in link_dict:
                link_dict[inode_referenced] = parent

    for directories in dirent_dict:
        x = dirent_dict[directories]
        inode_referenced = int (dirent_dict[directories]['file_inode_number'])
        parent_dir = int (dirent_dict[directories]['inode_parent'])
        file_name = dirent_dict[directories]["name"]
        flag = True
        if '.' in file_name:
            if '..' in file_name:
                if parent_dir in link_dict:
                    if link_dict[parent_dir] != inode_referenced:
                        parent_dir = link_dict[inode_referenced]
                        flag = False
                elif parent_dir != inode_referenced:          
                    flag = False
            else:
                if inode_referenced != parent_dir:
                    flag = False
        if not flag:            
            print "DIRECTORY INODE " + str(parent_dir) + " NAME " + dirent_dict[directories]['name'] + " LINK TO INODE " + str(inode_referenced) + " SHOULD BE " + str(link_dict[inode_referenced])


def handle_invalid_nodes(seen_inodes):
    starting_inode = sblock_dict['first_non_res_inode']
    nodes_to_see = sblock_dict['total_num_inodes']
    for directories in dirent_dict:
        inode_referenced = int (dirent_dict[directories]['file_inode_number'])
        if inode_referenced > nodes_to_see or inode_referenced < 1: # or inode_referenced < starting_inode:
            print "DIRECTORY INODE " + str(dirent_dict[directories]['inode_parent']) + " NAME " + dirent_dict[directories]["name"] + " INVALID INODE " + str(inode_referenced)
        elif inode_referenced not in seen_inodes:
            print "DIRECTORY INODE " + str(dirent_dict[directories]['inode_parent']) + " NAME " + dirent_dict[directories]["name"] + " UNALLOCATED INODE " + str(inode_referenced)

def handle_bogus_entries():
    link_dict = {}
    for directories in dirent_dict:
        inode_referenced = int (dirent_dict[directories]['file_inode_number'])
        if inode_referenced in link_dict:
            link_dict [inode_referenced] = link_dict [inode_referenced] + 1
        else:
            link_dict[inode_referenced] = 1
    for inodes in inode_dict:
        curr_inode_num = inode_dict[inodes]['inode_num']
        inode_link_count = inode_dict[inodes]['link_count']
        if curr_inode_num in link_dict:
            x = int(link_dict[curr_inode_num])
            y = int(inode_link_count)
            if int(link_dict[curr_inode_num]) != int(inode_link_count):
                print "INODE " + str(curr_inode_num) + " HAS " + str(link_dict[curr_inode_num]) + " LINKS BUT LINKCOUNT IS " + str(inode_link_count)
                return
        else:
            print "INODE " + str(curr_inode_num) + " HAS " + '0' + " LINKS BUT LINKCOUNT IS " + str(inode_link_count)

def main():
    if len(sys.argv) >= 2:
        if open_file(sys.argv[1]):
            check_blocks()
            seen_inodes = check_inodes()
            check_directories(seen_inodes)
        else:
            exit(1)
    else:
        sys.stderr.write("error, system has only " + str(len(sys.argv)) + " args")
        exit(1)


main()
