#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

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
	char string[BLOCK_SIZE];

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

		ret_read=read(fd,my_block->table,((BLOCK_SIZE/sizeof(DiNode)) * sizeof(DiNode)));
		
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
  printf("\n");
  printf("Name: %s , Mode: %d , Uid: %d , Gid: %d , Size: %jd , A_time: %d , #0: %d , #1: %d , #2: %d , #3: %d, #4: %d , #5: %d \n", dinode->name, dinode->mode, dinode->uid, dinode->gid, dinode->size ,dinode->a_time, dinode->di_number[0],dinode->di_number[1],dinode->di_number[2],dinode->di_number[3],dinode->di_number[4],dinode->di_number[5]);
  printf("F/D_Name[0]: %s, F/D_Name[1]: %s, F/D_Name[2]: %s,F/D_Name[3]: %s,F/D_Name[4]: %s,F/D_Name[5]: %s , %d\n",dinode->names[0].name, dinode->names[1].name, dinode->names[2].name, dinode->names[3].name, dinode->names[4].name, dinode->names[5].name, dinode->next );
  printf("\n");
  
  return true;
}

void insert_file(Header* header,char* our_file,char* file_to_add)  // ---- SOS ---- Check if there is space before inserting
{
	int from,to,ret;
	char buffer[256];

	

	from=open(file_to_add, O_RDONLY,PERMS);
	to=open(our_file,O_WRONLY,PERMS);

	
	lseek(to,header->Last_File,SEEK_SET);

	ret=read(from,buffer,sizeof(buffer));
	if(ret < 0)
	{
		perror("Error in Reading a file\n");
		exit(2);
	}

	header->Last_File+=ret;                    // Changing the pointer
	while(ret > 0)
	{
		write(to,buffer,ret);
		ret=read(from,buffer,sizeof(buffer));
		if(ret < 0)
		{
			perror("Error in Reading a file\n");
			exit(2);
		}

		header->Last_File+=ret;                  // Changing the pointer
		
	}
	
	close(from);
	close(to);
}

void export_file(uint32_t start, off_t size,char* filename,char* our_file)
{
	off_t count;
	int out,in;
  off_t ret;
	char buffer[256];

	out=open(filename,O_RDWR|O_APPEND|O_CREAT,PERMS);
	in=open(our_file,O_RDONLY,PERMS);
  if(in == -1) {
    perror("OPEN IN EXPORT FILE");
  }

	lseek(in,start,SEEK_SET);
	count=0;
	while(count < size)
	{
		if((size-count) < 256)
		{
			ret=read(in,buffer,(size-count));
		}
		else
		{
			ret=read(in,buffer,sizeof(buffer));
		}
		
		if(ret < 0)
		{
			perror("Error in Reading a file\n");
			exit(2);
		}
		write(out,buffer,ret);

		count+= ret;
	}

	close(out);
	close(in);
}
