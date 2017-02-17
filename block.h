#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define BLOCK_SIZE 512
typedef struct DirName{
	
	char name[64];

}DirName;

typedef struct DiNode{

	mode_t mode;    /* protection */
	uid_t uid;		/* user ID of owner */                 
	gid_t gid;		/* group ID of owner */
	off_t size;		/* time of last status change */
	time_t atime;        /* time of last access */
    time_t mtime;        /* time of last modification */
    time_t ctime;	    /* time of last status change */

	char isDir           /* 0 -> is File , 1 -> is Directory*/

    int32_t di_num[10];   /* Directory's DiNode */
    DirName names[10];	  /* Directory's Name */

    int32_t next;

}DiNode;

typedef struct Block{

	char list_diNode;
	

}Block;

