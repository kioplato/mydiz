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
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
/********************/

/* User Libraries */
#include "misc/misc.h"
#include "file_structure/file_structure.h"
#include "metadata/metadata_functions.h"
#include "operations/operations.h"
/******************/

int32_t main(int32_t argc, char** argv) {
  Cli_args cli_args;
  if(!decode_cli_flags(argc, argv, &cli_args))
    return EXIT_FAILURE;

  /*DEBUG*/
  // fprintf(stderr, "cli_args.c:%d\n", cli_args.c);
  // fprintf(stderr, "cli_args.a:%d\n", cli_args.a);
  // fprintf(stderr, "cli_args.x:%d\n", cli_args.x);
  // fprintf(stderr, "cli_args.j:%d\n", cli_args.j);
  // fprintf(stderr, "cli_args.d:%d\n", cli_args.d);
  // fprintf(stderr, "cli_args.m:%d\n", cli_args.m);
  // fprintf(stderr, "cli_args.q:%d\n", cli_args.q);
  // fprintf(stderr, "cli_args.p:%d\n", cli_args.p);
  // fprintf(stderr, "cli_args.archive_name:%s\n", cli_args.archive_name);
  // for(int32_t file_candidate = 0; file_candidate < cli_args.numOf_files; file_candidate++) {
  //   fprintf(stderr, "cli_args->list_of_files[%d]:%s.\n", file_candidate, cli_args.list_of_files[file_candidate]);
  // }
  // /*END OF DEBUG*/

  Block* my_block;
  int DiNodes_per_Block;
  
   
  my_block=malloc(sizeof(Block));
  DiNodes_per_Block=BLOCK_SIZE / sizeof(DiNode);
  my_block->table=malloc(DiNodes_per_Block*sizeof(DiNode));     // Initialize space for the Block

  if(cli_args.c)
  {
    create_archive(cli_args);
  }
  else if(cli_args.a)
  {
    append_file();
  }
  else if(cli_args.x)
  {
    extract_archive();
  }
  else if(cli_args.m)
  {
    print_metadata(cli_args.archive_name);
  }
  else if(cli_args.q)
  {
    file_exists(&cli_args,cli_args.archive_name);
  }
  else if(cli_args.p)
  {
    print_hierarchy(cli_args.archive_name);
  }
  

  free(my_block->table);
  free(my_block);
  
  
  printf("Holla Amigo, Que Tal ?\n");

  return EXIT_SUCCESS;
}
