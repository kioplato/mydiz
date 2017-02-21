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
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
/********************/

/* User Libraries */
#include "operations.h"
#include "../file_structure/file_structure.h"
#include "../misc/misc.h"
#include "../dinode_list/dinode_list.h"
/******************/
bool update(List* list,DiNode* current_dinode,DiNode* new_dinode)
{
  DiNode* temp;
  Node* temp_node;
  // Initialize itself.
  strcpy(new_dinode->names[0].name,".");          
  new_dinode->di_number[0]=list->numOf_nodes;
  new_dinode->numOf_free--;
  // Set Parent.
  strcpy(new_dinode->names[1].name,"..");
  new_dinode->di_number[1]=current_dinode->di_number[0];
  new_dinode->numOf_free--;

  push_dinode(list,new_dinode);

  temp=current_dinode;
  
  while(temp->next != 0)
  {
    temp_node=list->header_node;
    int32_t Node_id=0;

    while(Node_id < temp->next)
    {
      temp_node=temp_node->next_node;
      Node_id++;
    }

    temp=temp_node->info;
  }
  if(temp->numOf_free > 0)
  {
    //Put Child's Name.
    strcpy(temp->names[NUMOF_CHILDS - temp->numOf_free].name,new_dinode->name);
    //Put Child's DiNode ID.
    temp->di_number[NUMOF_CHILDS - temp->numOf_free]=new_dinode->di_number[0];
    //Reduce free spaces.
    temp->numOf_free--;
  }
  else // Parent Dir doesn't have space for the Child.
  {
    DiNode* new_for_current=malloc(sizeof(DiNode));
    new_dinode->numOf_free=NUMOF_CHILDS;
    //Put Child's Name.
    strcpy(new_for_current->names[0].name,new_dinode->name);
    //Put Child's DiNode ID.
    new_for_current->di_number[0]=new_dinode->di_number[0];

    new_for_current->numOf_free--;

    temp->next=list->numOf_nodes;

    push_dinode(list,new_for_current);
  }

  return true;
}

bool add_files_recursive(List* list, DiNode* current_dinode, Header* header, bool zipit,char* archive_file_name) {

  //OpenDir
  while(readdir)
  {
    DiNode* new_dinode=malloc(sizeof(DiNode));
    //Stat Here.
    copy_to_DiNode(the_status,new_dinode);
    strcpy(filename,new_dinode->name);
    new_dinode->next=0;
    new_dinode->numOf_free=NUMOF_CHILDS;

    update(list,current_dinode,new_dinode);
    if(isDir)
    {
      //Kolpa Platonas.
      new_dinode->isDir=true;
      add_files_recursive(list,new_dinode,header,zipit,archive_file_name);
    }
    else
    {
      new_dinode->isDir=false;
      if(zipit)
      {
        //cwd Kolpa v2.
        compress_file(current_dinode->name);
        strcat(current_dinode->name,".gz");
        //Path of the achive_file Kolpa twra.
        insert_file(header,archive_file_name,current_dinode->name);
      }
      else
      {
        //Path of the achive_file Kolpa twra.
        insert_file(header,archive_file_name,current_dinode->name);
      }
    }
  }


  return true;
}

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

bool copy_to_DiNode(struct stat* the_stat,DiNode* my_dinode)
{
  my_dinode->mode=the_stat->st_mode;
  my_dinode->uid=the_stat->st_uid;
  my_dinode->gid=the_stat->st_gid;
  my_dinode->size=the_stat->st_size;
  my_dinode->a_time=the_stat->st_atime;
  my_dinode->m_time=the_stat->st_mtime;
  my_dinode->c_time=the_stat->st_ctime;

  return true;
}
