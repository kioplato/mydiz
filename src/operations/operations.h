/******************************************************************************
 * File    : operations.h
 * Purpose : Provides the interface for the operation.c functions.
******************************************************************************/

/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/********************/

/* Creates archive using a list_of_files. */
bool create_archive();

/* Appends the file or directory to the archive. */
bool append_file();

/* Extracts the arhive. */
bool extract_archive();

/* Comresses a file. */
bool compress_file();

/* Uncomresses a file. */
bool uncompress_file();

/* Deletes a file or directory. */
bool delete_entity();

/* Prints the metadata. */
bool print_metadata();

/* Returns true if the file exists and false if it does not. */
bool file_exists();

/* Prints the archive's hierarchy. */
bool print_hierarchy();
