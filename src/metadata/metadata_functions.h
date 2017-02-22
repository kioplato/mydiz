#ifndef METADATA_FUNCTIONS_H
#define METADATA_FUNCTIONS_H


#include "../file_structure/file_structure.h"

void metadata_add_DiNode(char* filename,Header* header,DiNode* DiNode_to_insert);
int metadata_get_block(char* filename,Header* header,int number_of_block,Block* my_block); // Numeber of Block starts with 0 
void write_header(char* filename,Header* header);
void read_header(char* filename,Header* header);
bool print_dinode(DiNode* dinode);
void insert_file(Header* header,char* our_file,char* file_to_add);
void export_file(uint32_t start, off_t size,char* filename,char* our_file);

#endif
