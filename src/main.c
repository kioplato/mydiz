/******************************************************************************
 * File: main.c
 * Purpose: Implementation of main function.
******************************************************************************/

/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
/********************/

/* User Libraries */
#include "misc/misc.h"
#include "file_structure/file_structure.h"
#include "metadata/metadata_functions.h"
/******************/

int32_t main(int32_t argc, char** argv) {
  Cli_args cli_args;
  if(!decode_cli_flags(argc, argv, &cli_args))
    return EXIT_FAILURE;

  /*DEBUG*/
  //fprintf(stderr, "cli_args.c:%d\n", cli_args.c);
  //fprintf(stderr, "cli_args.a:%d\n", cli_args.a);
  //fprintf(stderr, "cli_args.x:%d\n", cli_args.x);
  //fprintf(stderr, "cli_args.j:%d\n", cli_args.j);
  //fprintf(stderr, "cli_args.d:%d\n", cli_args.d);
  //fprintf(stderr, "cli_args.m:%d\n", cli_args.m);
  //fprintf(stderr, "cli_args.q:%d\n", cli_args.q);
  //fprintf(stderr, "cli_args.p:%d\n", cli_args.p);
  //fprintf(stderr, "cli_args.archive_name:%s\n", cli_args.archive_name);
  //for(int32_t file_candidate = 0; file_candidate < cli_args.numOf_files; file_candidate++) {
  //  fprintf(stderr, "cli_args->list_of_files[%d]:%s.\n", file_candidate, cli_args.list_of_files[file_candidate]);
  //}
  /*END OF DEBUG*/

  Block* my_block;
  int fd,DiNodes_per_Block;
  char filename[50];
  Header* header=malloc(sizeof(Header));
  

  header->MetaData_Start=sizeof(Header);
  header->MetaData_Last_DiNode=header->MetaData_Start;   // Initialize Header

  strcpy(filename,"myfile.di");

  fd=open(filename,O_CREAT|O_RDONLY,0777);
  close(fd);

  write_header(filename,header);                 // Write Header in file

  my_block=malloc(sizeof(Block));
  DiNodes_per_Block=BLOCK_SIZE / sizeof(DiNode);
  my_block->table=malloc(DiNodes_per_Block*sizeof(DiNode));     // Initialize space for the Block

  
  printf("Holla Amigo, Que Tal ?\n");

  return EXIT_SUCCESS;
}
