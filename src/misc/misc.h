/******************************************************************************
 * File: misc.h
 * Purpose: Interface for misc functions.
 * Authors:
 *   Platon-Nikolaos Kiorpelidis
 *   Giannis Efthymiou
 * Date: 16/02/17
******************************************************************************/

#ifndef MISC_H
#define MISC_H

/* System Libraries */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
/********************/

/* User Structures */
typedef struct Cli_args {
  bool c;
  bool a;
  bool x;
  bool j;
  bool d;
  bool m;
  bool q;
  bool p;
  
  char* archive_name;
  char** list_of_files;
  int32_t numOf_files;
} Cli_args;
/*******************/


const char *get_filename_ext(const char *filename);

bool decode_cli_flags(int32_t, char**, Cli_args*);

#endif
