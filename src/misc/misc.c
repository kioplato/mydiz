/*******************************************************************************
 * File: misc.c
 * Purpose: Implementation of misc functions.
*******************************************************************************/

/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/********************/

/* User Libraries */
#include "misc.h"
/******************/

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void print_flags() {
  printf("The flags are:\n");
  printf("  -c : Archives the file system entities that are provided by the <list_of_files/dirs>");
  printf(" into the <archive-file>. Directories and files that are nested in <list_of_files/dirs>");
  printf(" are stored in a recursive manner in the <archive-file>.\n");
  printf("\n");
  printf("  -a : Appends the files and directories from the <list-of-files/dirs>");
  printf(" to the probably already existing <archive-file>. If there are nested");
  printf(" directories in the <list-of-files/dirs> they are included in");
  printf(" a recursive manner with all their content in the <archive-file>.\n");
  printf("\n");
  printf("  -x : Extracts all the files and directories that are stored in <archive-file>.\n");
  printf("\n");
  printf("  -j : Compresses the files before archiving them in the <archive-file>.\n");
  printf("\n");
  printf("  -d : Deletes the entities described in the <list-of-files/dirs> from the");
  printf(" already existing <archive-file>.\n");
  printf("\n");
  printf("  -m : Prints the metadata (owner, group, access rights) for each");
  printf(" entity that is stored in the <archive-file>.\n");
  printf("\n");
  printf("  -q : Interpellation about whether or not the files from the");
  printf(" <list-of-files/dirs> exist in the <archive-file>. For each entity");
  printf(" of the <list-of-files/dirs> a yes or no answer will be provided.\n");
  printf("\n");
  printf("  -p : Prints the hierarchy of the directories and files that exist");
  printf(" in the <archive-file> in a way that is understandable.\n");
  
  return;
}

bool decode_cli_flags(int32_t numOf_args, char** args, Cli_args* cli_args) {
  if(numOf_args < 3) {
    fprintf(stderr, "Error: Invalid command line flags. Required 2 to 3 flags.\n");
    fprintf(stderr, "Note: Only %d were provided.\n", numOf_args);
    print_flags();
    return false;
  }
  
  /*DEBUG*/printf("The flags are:%s\n", args[1]);
  /*DEBUG*/printf("The length of the args[1] is:%ld\n", strlen(args[1]));
  
  cli_args->c = false;
  cli_args->a = false;
  cli_args->x = false;
  cli_args->j = false;
  cli_args->d = false;
  cli_args->m = false;
  cli_args->q = false;
  cli_args->p = false;
  
  // We start counting from 1 because of the dash at the 0th position.
  for(int32_t flag_candidate = 1; flag_candidate < strlen(args[1]); flag_candidate++) {
    if(args[1][flag_candidate] == 'c') {
      if(cli_args->x == true) {
        fprintf(stderr, "Error: Can't create archive and extract simultaneously.\n");
        return false;
      }
      else if(cli_args->a == true) {
        fprintf(stderr, "Error: Can't create archive and append files simultaneously.\n");
        return false;
      }
      else if(cli_args->d == true) {
        fprintf(stderr, "Error: Can't create archive and delete entity simultaneously.\n");
        return false;
      }
      else if(cli_args->m == true) {
        fprintf(stderr, "Error: Can't create archive and print the metadata simultaneously");
        return false;
      }
      else if(cli_args->q == true) {
        fprintf(stderr, "Error: Can't create archive and interpellate if a file exists simultaneously.\n");
        return false;
      }
      else if(cli_args->p == true) {
        fprintf(stderr, "Error: Can't create archive and print the hierarchy of the archive simultaneously.\n");
        return false;
      }
      cli_args->c = true;
    }
    else if(args[1][flag_candidate] == 'a') {
      if(cli_args->c == true) {
        fprintf(stderr, "Error: Can't append files and create archive simultaneously.\n");
        return false;
      }
      else if(cli_args->x == true) {
        fprintf(stderr, "Error: Can't append files and create archive simultaneously.\n");
        return false;
      }
      else if(cli_args->d == true) {
        fprintf(stderr, "Error: Can't append files and delete entity simultaneously.\n");
        return false;
      }
      else if(cli_args->m == true) {
        fprintf(stderr, "Error: Can't append files and print the metadata simultaneously.\n");
        return false;
      }
      else if(cli_args->q == true) {
        fprintf(stderr, "Error: Can't append files and interpellate if a file exists simultaneously.\n");
        return false;
      }
      else if(cli_args->p == true) {
        fprintf(stderr, "Error: Can't append files and print the archive's hierarchy simultaneously.\n");
        return false;
      }
      cli_args->a = true;
    }
    else if(args[1][flag_candidate] == 'x') {
      if(cli_args->c == true) {
        fprintf(stderr, "Error: Can't extract archive and create archive simultaneously.\n");
        return false;
      }
      else if(cli_args->a == true) {
        fprintf(stderr, "Error: Can't extract archive and append files simultaneously.\n");
        return false;
      }
      else if(cli_args->j == true) {
        fprintf(stderr, "Error: Can't extract archive and compress files simultaneously.\n");
        return false;
      }
      else if(cli_args->d == true) {
        fprintf(stderr, "Error: Can't extract archive and delete entity simultaneously.\n");
        return false;
      }
      else if(cli_args->m == true) {
        fprintf(stderr, "Error: Can't extract archive and print metadata simultaneously.\n");
        return false;
      }
      else if(cli_args->q == true) {
        fprintf(stderr, "Error: Can't extract archive and interpellate if a file exists simultaneously.\n");
        return false;
      }
      else if(cli_args->p == true) {
        fprintf(stderr, "Error: Can't extract archive and print the archive's hierarchy simultaneously.\n");
      }
      cli_args->x = true;
    }
    else if(args[1][flag_candidate] == 'j') {
      if(cli_args->x == true) {
        fprintf(stderr, "Error: Can't compress files and extract archive simultaneously.\n");
        return false;
      }
      else if(cli_args->d == true) {
        fprintf(stderr, "Error: Can't compress files and delete entity simultaneously.\n");
        return false;
      }
      else if(cli_args->m == true) {
        fprintf(stderr, "Error: Can't compress files and print metadata simultaneously.\n");
        return false;
      }
      else if(cli_args->q == true) {
        fprintf(stderr, "Error: Can't compress files and interpellate if a file exists simultaneously.\n");
        return false;
      }
      else if(cli_args->p == true) {
        fprintf(stderr, "Error: Can't compress files and print the archive's hierarchy simultaneously.\n");
        return false;
      }
      cli_args->j = true;
    }
    else if(args[1][flag_candidate] == 'd') {
      if(cli_args->c == true) {
        fprintf(stderr, "Error: Can't delete entity and create archive simultaneously.\n");
        return false;
      }
      else if(cli_args->a == true) {
        fprintf(stderr, "Error: Can't delete entity and append files simultaneously.\n");
        return false;
      }
      else if(cli_args->x == true) {
        fprintf(stderr, "Error: Can't delete entity and extract archive simultaneously.\n");
        return false;
      }
      else if(cli_args->j == true) {
        fprintf(stderr, "Error: Can't delete entity and compress files simultaneously.\n");
        return false;
      }
      else if(cli_args->m == true) {
        fprintf(stderr, "Error: Can't delete entity and print metadata simultaneously.\n");
        return false;
      }
      else if(cli_args->q == true) {
        fprintf(stderr, "Error: Can't delete entity and interpellate if a file exists simultaneously.\n");
        return false;
      }
      else if(cli_args->p == true) {
        fprintf(stderr, "Error: Can't delete entity and print the archive's hierarchy simultaneously.\n");
        return false;
      }
      cli_args->d = true;
    }
    else if(args[1][flag_candidate] == 'm') {
      if(cli_args->c == true) {
        fprintf(stderr, "Error: Can't print metadata and create archive simultaneously.\n");
        return false;
      }
      else if(cli_args->a == true) {
        fprintf(stderr, "Error: Can't print metadata and append files simultaneously.");
        return false;
      }
      else if(cli_args->x == true) {
        fprintf(stderr, "Error: Can't print metadata and extract archive simultaneously.\n");
        return false;
      }
      else if(cli_args->j == true) {
        fprintf(stderr, "Error: Can't print metadata and compress files simultaneously.\n");
        return false;
      }
      else if(cli_args->d) {
        fprintf(stderr, "Error: Can't print metadata and delete entity simultaneously.\n");
        return false;
      }
      else if(cli_args->q == true) {
        fprintf(stderr, "Error: Can't print metadata and interpellate if a file exists simultaneously.\n");
        return false;
      }
      else if(cli_args->p == true) {
        fprintf(stderr, "Error: Can't print metadata and print the archive's hierarchy simultaneously.\n");
        return false;
      }
      cli_args->m = true;
    }
    else if(args[1][flag_candidate] == 'q') {
      if(cli_args->c == true) {
        fprintf(stderr, "Error: Can't interpellate if a file exists and create archive simultaneously.\n");
        return false;
      }
      else if(cli_args->a == true) {
        fprintf(stderr, "Error: Can't interpellate if a file exists and append file simultaneously.\n");
        return false;
      }
      else if(cli_args->x == true) {
        fprintf(stderr, "Error: Can't interpellate if a file exists and extract archive simultaneously.\n");
        return false;
      }
      else if(cli_args->j == true) {
        fprintf(stderr, "Error: Can't interpellate if a file exists and compress files simultaneously.\n");
        return false;
      }
      else if(cli_args->d == true) {
        fprintf(stderr, "Error: Can't interpellate if a file exists and delete entity simultaneously.\n");
        return false;
      }
      else if(cli_args->m == true) {
        fprintf(stderr, "Error: Can't interpellate if a file exists and print metadata simultaneously.\n");
        return false;
      }
      else if(cli_args->p == true) {
        fprintf(stderr, "Error: Can't interpellate if a file exists and print the archive's hierarchy");
        fprintf(stderr, " simultaneously.\n");
        return false;
      }
      cli_args->q = true;
    }
    else if(args[1][flag_candidate] == 'p') {
      if(cli_args->c == true) {
        fprintf(stderr, "Error: Can't print the archive's hierarchy and create archive simultaneously.\n");
        return false;
      }
      else if(cli_args->a == true) {
        fprintf(stderr, "Error: Can't print the archive's hierarchy and append files simultaneously.\n");
        return false;
      }
      else if(cli_args->j == true) {
        fprintf(stderr, "Error: Can't print the archive's hierarchy and compress files simultaneously.\n");
        return false;
      }
      else if(cli_args->d == true) {
        fprintf(stderr, "Error: Can't print the archive's hierarchy and delete entities simultaneously.\n");
        return false;
      }
      else if(cli_args->m == true) {
        fprintf(stderr, "Error: Can't print the archive's hierarchy and print metadata simultaneously.\n");
        return false;
      }
      else if(cli_args->q == true) {
        fprintf(stderr, "Error: Can't print the archive's hierarchy and interpellate if a file exists.\n");
        return false;
      }
      cli_args->p = true;
    }
    else {
      fprintf(stderr, "Error: Unknown flag %c.\n", args[1][flag_candidate]);
      return false;
    }
  }
  
  if(numOf_args >= 3)
    cli_args->archive_name = args[2];
  
  if(numOf_args >= 4) {
    fprintf(stderr, "We have %d list_of_files.\n", numOf_args - 3);
    cli_args->numOf_files = numOf_args - 3;
    cli_args->list_of_files = malloc(sizeof(char*) * numOf_args - 3);
    for(int32_t file_candidate = 3; file_candidate < numOf_args; file_candidate++) {
      cli_args->list_of_files[file_candidate - 3] = args[file_candidate];
    }
  }
  
  return true;
}

