/******************************************************************************
 * File    : operations.h
 * Purpose : Provides the interface for the operation.c functions.
******************************************************************************/

/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/********************/

/* User Libraries */
#include "../file_structure/file_structure.h"
/******************/

/* Creates archive using a list_of_files. */
bool create_archive(const char* archive_name, const char** list_of_files, const int32_t numOf_files);

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
bool print_metadata();

/* Returns true if the file exists and false if it does not. */
bool file_exists();

/* Prints the archive's hierarchy. */
bool print_hierarchy();

/* Copys to DiNode the Stat we want to keep*/
bool copy_to_DiNode(struct stat* the_stat,DiNode* my_dinode);
