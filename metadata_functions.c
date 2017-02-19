#include "metadata_functions.h"
#include <fcntl.h>

#define PERMS 0777

void metadata_add_file(char* filename,uint32_t last_block_pointer)
{
	FILE* fp;
	fp=fopen(filename,"r+");     /*r+ for reaing and writing*/
	fseek(fp,last_block_pointer,SEEK_SET);  /*SEEK SET starts from the begining of the file*/
	
}

void metadata_add_dir()
{

}