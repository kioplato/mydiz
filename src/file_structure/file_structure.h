#ifndef FILE_STRUCTURE_H
#define FILE_STRUCTURE_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

#define BLOCK_SIZE 1024
typedef struct DirName{
	
	char name[30];

}DirName;

typedef struct DiNode{

	mode_t mode;    /* protection */
	uid_t uid;		/* user ID of owner */                 
	gid_t gid;		/* group ID of owner */
	off_t size;		/* time of last status change */
	time_t a_time;        /* time of last access */
    time_t m_time;        /* time of last modification */
    time_t c_time;	    /* time of last status change */

	bool isDir;           /* 0 -> is File , 1 -> is Directory*/

    uint32_t di_number[6];  /*  Directory's DiNode */
    DirName names[6];	  /* Directory's Name */

    uint32_t next;      /*DiNode Number*/

}DiNode;

typedef struct Block{
	
	DiNode* table;

}Block;

typedef struct Header{

	uint32_t MetaData_Start;       
	uint32_t MetaData_Last_DiNode;
	uint32_t Last_File; 
	uint32_t file_size;     
	
}Header;

#endif
