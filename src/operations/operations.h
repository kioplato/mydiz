/******************************************************************************
 * File    : operations.h
 * Purpose : Provides the interface for the operation.c functions.
******************************************************************************/
#ifndef OPERATIONS_H
#define OPERATIONS_H
/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/********************/

/* User Libraries */
#include "../misc/misc.h"
#include "../file_structure/file_structure.h"
#include "../dinode_list/dinode_list.h"
/******************/

/* Make nessecary updates for the DiNodes*/
bool update(List* list,DiNode* current_dinode,DiNode* new_dinode);

/* Recursive functions that makes updates the List with Metadata and the archive-file with files */
bool add_files_recursive(List* list, DiNode* current_dinode, Header* header, bool zipit,char* archive_file_name_path);

/* Creates archive using a list_of_files. */
bool create_archive(Cli_args cli_args);

/* Appends the file or directory to the archive. */
bool append_file();

/* Extracts the arhive. */
bool extract_archive();

/* Comresses a file. */
bool compress_file(char* filename);

/* Uncomresses a file. */
bool uncompress_file(char* filename);

/* Deletes a file or directory. */
bool delete_entity();

/* Prints the metadata. */
bool print_metadata(char* filename);

/* Returns true if the file exists and false if it does not. */
bool file_exists(Cli_args* cli_args,char* filename);

/* Recursive function for print hierarchy*/
bool print_inside(char* filename,Header* header,DiNode* root,int spaces,uint32_t fetch);

/* Prints the archive's hierarchy. */
bool print_hierarchy(char* filename);

/* Copys to DiNode the Stat we want to keep*/
bool copy_to_DiNode(struct stat* the_stat,DiNode* my_dinode);

#endif
