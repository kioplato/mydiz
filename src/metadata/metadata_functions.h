#ifndef METADATA_FUNCTIONS_H
#define METADATA_FUNCTIONS_H


#include "../file_structure/file_structure.h"

void metadata_add_DiNode(char* filename,Header* header,DiNode* DiNode_to_insert);
int metadata_get_block(char* filename,Header* header,int number_of_block,Block* my_block); // Numeber of Block starts with 0 
void write_header(char* filename,Header* header);
void read_header(char* filename,Header* header);


#endif