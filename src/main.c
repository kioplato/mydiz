/******************************************************************************
 * File: main.c
 * Purpose: Implementation of main function.
******************************************************************************/

/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
/********************/

/* User Libraries */
#include "misc/misc.h"
#include "file_structure/file_structure.h"
/******************/

int32_t main(int32_t argc, char** argv) {
  Cli_args cli_args;
  if(!decode_cli_flags(argc, argv, &cli_args))
    return EXIT_FAILURE;

  /*DEBUG*/
  fprintf(stderr, "cli_args.archive_name:%s\n", cli_args.archive_name);
  fprintf(stderr, "cli_args.list_of_files:%s\n", cli_args.list_of_files);
  fprintf(stderr, "cli_args.c:%d\n", cli_args.c);
  fprintf(stderr, "cli_args.a:%d\n", cli_args.a);
  fprintf(stderr, "cli_args.x:%d\n", cli_args.x);
  fprintf(stderr, "cli_args.j:%d\n", cli_args.j);
  fprintf(stderr, "cli_args.d:%d\n", cli_args.d);
  fprintf(stderr, "cli_args.m:%d\n", cli_args.m);
  fprintf(stderr, "cli_args.q:%d\n", cli_args.q);
  fprintf(stderr, "cli_args.p:%d\n", cli_args.p);
  /*END OF DEBUG*/

  uint32_t k;

  k=0xFFFFFFFF;

  printf("Sizes: %lu %d\n",sizeof(DiNode),BLOCK_SIZE);



  printf("This is the start of a new page , Karibu :D \n");

  return EXIT_SUCCESS;
}
