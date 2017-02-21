/******************************************************************************
 * File    : operations.c
 * Purpose : Implementation for the functions that provide the operations.
******************************************************************************/

/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/********************/

/* User Libraries */
#include "operations.h"
#include "../file_structure/file_structure.h"
/******************/

bool create_archive(const char* archive_name, const char** list_of_files, const int32_t numOf_files) {
  int32_t fd = open(archive_name, O_WRONLY | O_CREAT, 0777);
  Header* header = malloc(sizeof(Header));
  write(fd, header, sizeof(Header));
  
  //TODO: Iterate through the list_of_files.
  //While we iterate we will write the contents of the
  //files to the .di file and in parallel create and store
  //a dinode in a list of dinodes so we can write the
  //metadata afterwards.
  
  close(fd);
  return true;
}

bool append_file() {
  
  return true;
}

bool extract_archive() {
  
  return true;
}

bool compress_file(char* filename) {
int status;

  if (fork() == 0)
  {
    execvp("gzip",(char *[]){ "gzip",filename,NULL });
  }
  else
  {
    wait(&status);
  }
  return true;
}

bool uncompress_file(char* filename){
int status;

  if (fork() == 0)
  {
    execvp("gunzip",(char *[]){ "gzip",filename,NULL });
  }
  else
  {
    wait(&status);
  }

  return true;
}

bool delete_entity() {
  
  return true;
}

bool print_metadata() {
  
  return true;
}

bool file_exists() {
  
  return true;
}

bool print_hierarchy() {
  
  return true;
}
