#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "metadata_functions.h"

#define PERMS 0777

void metadata_add_DiNode(char* filename,Header* header,DiNode* DiNode_to_insert)
{
	int fd,append,diff,dinode_index;
	DiNode* buffer;
	int* zero_string;
	
	zero_string=calloc(BLOCK_SIZE/sizeof(int),sizeof(int));

	diff=header->MetaData_Last_DiNode - header->MetaData_Start;   
	dinode_index=diff % BLOCK_SIZE;

	if( (dinode_index == 0)  || ((dinode_index + sizeof(DiNode)) > BLOCK_SIZE) )     /* If there is not space in the Block */   
	{	
		fd=open(filename,O_APPEND,PERMS);

		if(dinode_index != 0)
		{
			lseek(fd,(header->MetaData_Last_DiNode + (BLOCK_SIZE - dinode_index)),SEEK_SET);  // Write on a next new Block	
		}

		write(fd,DiNode_to_insert,sizeof(DiNode));         /* write in the file*/

		header->MetaData_Last_DiNode+= sizeof(DiNode);	      /* Update the pointer */

		write(fd,zero_string,(BLOCK_SIZE - dinode_index + sizeof(DiNode)));   /* Zeros until the end of file */
	
	}
	else
	{

		fd=open(filename,O_RDWR,PERMS);     
		lseek(fd,header->MetaData_Last_DiNode,SEEK_SET);	  

		write(fd,DiNode_to_insert,sizeof(DiNode));         /* write in the file*/

		header->MetaData_Last_DiNode+= sizeof(DiNode);	      /* Update the pointer */

		write(fd,zero_string,(BLOCK_SIZE - dinode_index + sizeof(DiNode)));   /* Zeros until the end of file */
	}


	free(zero_string);

}

