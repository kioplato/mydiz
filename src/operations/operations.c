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
#include <dirent.h>
/********************/

/* User Libraries */
#include "operations.h"
#include "../file_structure/file_structure.h"
#include "../misc/misc.h"
#include "../dinode_list/dinode_list.h"
/******************/

//bool add_files_recursive(List* list, DiNode* root, ) {
//
//  return true;
//}

bool create_archive(Cli_args cli_args) {
  int32_t fd = open(cli_args.archive_name, O_WRONLY | O_CREAT, 0777);
  Header* header = malloc(sizeof(Header));
  write(fd, header, sizeof(Header));
  
  //TODO: Iterate through the list_of_files.
  //While we iterate we will write the contents of the
  //files to the .di file and in parallel create and store
  //a dinode in a list of dinodes so we can write the
  //metadata afterwards.
  
  List list;
  list_init(&list);
  
  DiNode* root = malloc(sizeof(DiNode));
  root->isDir = true;
  strcpy(root->names[0].name, ".");
  root->di_number[0] = 0;
  strcpy(root->names[1].name, "..");
  root->di_number[1] = 0;
  strcpy(root->name, cli_args.archive_name);
  push_dinode(&list, root);

  print_list(&list);

  DIR* opened_dir = NULL;
  opened_dir = opendir(cli_args.list_of_files[0]);
  struct dirent* file = NULL;
  while((file = readdir(opened_dir)) != NULL) {
    printf("Got from the %s dir the filename: %s\n", cli_args.list_of_files[0], file->d_name);
    struct stat my_stat;
    if(stat(file->d_name, &my_stat) == 0) {
      printf("Success on stat.\n");
    } else {
      printf("Failed on stat.\n");
    }
    printf("It's a dir: %d.\n", S_ISDIR(my_stat.st_mode));
  }



  //for(int32_t candidate = 0; candidate < cli_args.numOf_files; candidate++) {
  //  /*DEBUG*/printf("Working on %d %s list_of_files.\n", candidate, cli_args.list_of_files[candidate]);
  //  
  //  //Update root.
  //  //Create new di node and store it in the list.
  //  //If it's a dir open it.
  //}

  //print_list(&list);
  
  close(fd);
  return true;
}

bool append_file() {
  
  return true;
}

bool extract_archive() {
  
  return true;
}

bool compress_file() {
  
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
