#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "../metadata/metadata_functions.h"

#define PERMS 0777

void write_header(char* filename,Header* header)
{
	int fd;
	fd=open(filename,O_WRONLY,PERMS);
	write(fd,header,sizeof(Header));
	close(fd);
}

void read_header(char* filename,Header* header)
{
	int fd;
	fd=open(filename,O_RDONLY,PERMS);
	read(fd,header,sizeof(Header));
	close(fd);
}

void metadata_add_DiNode(char* filename,Header* header,DiNode* DiNode_to_insert)
{
	int fd,diff,dinode_index;
	char string[1024];

	diff=header->MetaData_Last_DiNode - header->MetaData_Start;
	dinode_index=diff % BLOCK_SIZE;


	if( (dinode_index == 0)  || ((dinode_index + sizeof(DiNode)) > BLOCK_SIZE) )     /* If there is not space in the Block */   
	{	
		fd=open(filename,O_RDWR|O_APPEND,PERMS);

		if(dinode_index != 0)
		{
			lseek(fd,(header->MetaData_Last_DiNode + (BLOCK_SIZE - dinode_index)),SEEK_SET);  // Write on a next new Block
			header->MetaData_Last_DiNode+=BLOCK_SIZE - dinode_index;
		}

		write(fd,DiNode_to_insert,sizeof(DiNode));         /* write in the file*/

		header->MetaData_Last_DiNode+= sizeof(DiNode);	      /* Update the pointer */

		write(fd,string,(BLOCK_SIZE - sizeof(DiNode)));  
	
	}
	else
	{
		
		fd=open(filename,O_RDWR,PERMS);     
		lseek(fd,header->MetaData_Last_DiNode,SEEK_SET);	  

		write(fd,DiNode_to_insert,sizeof(DiNode));         /* write in the file*/

		header->MetaData_Last_DiNode+= sizeof(DiNode);	      /* Update the pointer */
		
	}

	close(fd);
}

int metadata_get_block(char* filename,Header* header,int block_number,Block* my_block) // Numeber of Block starts with 0
{
	int fd,ret_read,diff;
	
	diff=header->MetaData_Last_DiNode - header->MetaData_Start;

	diff=diff / BLOCK_SIZE;

	if(block_number <= diff)
	{
		fd=open(filename,O_RDONLY,PERMS);

		lseek(fd,header->MetaData_Start + (block_number*BLOCK_SIZE),SEEK_SET);

		ret_read=read(fd,my_block->table,BLOCK_SIZE);
		
		if( ret_read > 0)
		{
			close(fd);
			return 1;
		}
		else
		{
			perror("Error in Reading a file\n");
			close(fd);
			exit(2);
		}
	}
	else
	{
		return -1;  // If the block requested is out of bounds
	}

	
}

bool print_dinode(DiNode* dinode) {
  
  
  return true;
}
