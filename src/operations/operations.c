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

#include <grp.h>
#include <pwd.h>
/********************/

/* User Libraries */
#include "operations.h"
#include "../file_structure/file_structure.h"
#include "../misc/misc.h"
#include "../dinode_list/dinode_list.h"
#include "../metadata/metadata_functions.h"
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
    temp_node=list->header_node->next_node;
    
    while(temp_node != NULL)
    {
      if(temp_node->info->di_number[0] == temp->next)
      {
        break;
      }    
      temp_node=temp_node->next_node;
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
    new_for_current->numOf_free=NUMOF_CHILDS;

    strcpy(new_for_current->names[0].name,".");
    new_for_current->di_number[0]=list->numOf_nodes;
    new_for_current->numOf_free--;
    // Set Parent.
    strcpy(new_for_current->names[1].name,"..");
    new_for_current->di_number[1]=current_dinode->di_number[0];
    new_for_current->numOf_free--;


    //Put Child's Name.
    strcpy(new_for_current->names[2].name,new_dinode->name);
    //Put Child's DiNode ID.
    new_for_current->di_number[2]=new_dinode->di_number[0];
    
    new_for_current->numOf_free--;
    
    temp->next=list->numOf_nodes;

    push_dinode(list,new_for_current);
    
    temp_node=list->header_node;
    
  }
  
  return true;
}

bool add_files_recursive(List* list, DiNode* current_dinode, Header* header, bool zipit,char* archive_file_name) {
  printf("INSIDE ADD_FILES_RECURSIVE.\n");
  //OpenDir
  // while(readdir)
  // {
  //  DiNode* new_dinode=malloc(sizeof(DiNode));
  //  //Stat Here.
  //  copy_to_DiNode(the_status,new_dinode);
  //  strcpy(filename,new_dinode->name);
  //  new_dinode->next=0;
  //  new_dinode->numOf_free=NUMOF_CHILDS;

  //  update(list,current_dinode,new_dinode);
  //  if(isDir)
  //  {
  //    //Kolpa Platonas.
  //    new_dinode->isDir=true;
  //    add_files_recursive(list,new_dinode,header,zipit,archive_file_name);
  //  }
  //  else
  //  {
  //    new_dinode->isDir=false;
  //    if(zipit)
  //    {
  //      //cwd Kolpa v2.
  //      compress_file(current_dinode->name);
  //      strcat(current_dinode->name,".gz");
  //      //Path of the achive_file Kolpa twra.
  //      insert_file(header,archive_file_name,current_dinode->name);
  //    }
  //    else
  //    {
  //      //Path of the achive_file Kolpa twra.
  //      insert_file(header,archive_file_name,current_dinode->name);
  //    }
  //  }
  // }


  return true;
}

bool create_archive(Cli_args cli_args) {
  int32_t fd = open(cli_args.archive_name, O_WRONLY | O_CREAT, 0777);
  char filename[50];

  Header* header = malloc(sizeof(Header));

  header->MetaData_Start=sizeof(Header);
  header->MetaData_Last_DiNode=header->MetaData_Start;
  header->Last_File=header->MetaData_Start;      // Initialize Header
  header->numOf_DiNodes=100;

  strcpy(filename,cli_args.archive_name);

  fd=open(filename,O_CREAT|O_RDONLY,0777);        // Create the file
  close(fd);

  write_header(filename,header);                 // Write Header in file

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
  root->next=0;
  root->numOf_free=NUMOF_CHILDS - 2;

  
  // print_list(&list);
  
  /* TESTING */
  //DIR* opened_dir = NULL;
  //opened_dir = opendir(cli_args.list_of_files[0]);
  //chdir(cli_args.list_of_files[0]);
  //struct dirent* file = NULL;
  //while((file = readdir(opened_dir)) != NULL) {
  //  if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0) {
  //    printf("Got from the %s dir the filename: %s\n", cli_args.list_of_files[0], file->d_name);
  //    struct stat my_stat;
  //    if(stat(file->d_name, &my_stat) == 0) {
  //      printf("Success on stat.\n");
  //    } else {
  //      printf("Failed on stat.\n");
  //    }
  //    printf("It's a dir: %d.\n", S_ISDIR(my_stat.st_mode));
  //  }
  //}
  /* END OF TESTING */

  for(int32_t candidate = 0; candidate < cli_args.numOf_files; candidate++) {
    
    bool zipit = cli_args.j;
    
    struct stat my_stat;

    stat(cli_args.list_of_files[candidate], &my_stat);
    bool is_dir = S_ISDIR(my_stat.st_mode);
    

    if(is_dir) 
    {
      add_files_recursive(&list, root, header, zipit, cli_args.archive_name);
    } 
    else 
    { // It's not a dir.
      char working_dir[256];
      getcwd(working_dir, 256);
      
      DiNode* new_dinode = malloc(sizeof(DiNode));


      copy_to_DiNode(&my_stat, new_dinode);
      strcpy(new_dinode->name, cli_args.list_of_files[candidate]);
      new_dinode->next = 0;
      new_dinode->numOf_free = NUMOF_CHILDS;
      
      update(&list, root, new_dinode);
      new_dinode->isDir = false;
      
      if(zipit == true) {
        
        compress_file(cli_args.list_of_files[candidate]);
        strcat(cli_args.list_of_files[candidate], ".gz");

        insert_file(header, cli_args.archive_name, cli_args.list_of_files[candidate]);
      } else {
        
        //Path of the achive_file Kolpa twra.
        
        insert_file(header, cli_args.archive_name, cli_args.list_of_files[candidate]);
      }
    }
  }
  
  print_list(&list);
  
  //closedir(opened_dir);
  close(fd);
  
  header->numOf_DiNodes=list.numOf_nodes;
  write_header(filename,header);                 // Write Header in file

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

bool print_metadata(char* filename,Header* header) {

  int32_t i,ret_getblock,count,DiNodes_per_Block;
  Block* my_block;
  struct group *grp;
  struct passwd *pwd;

  my_block=malloc(sizeof(Block));
  DiNodes_per_Block=BLOCK_SIZE / sizeof(DiNode);
  my_block->table=malloc(DiNodes_per_Block*sizeof(DiNode));     // Initialize space for the Block
  

  i=0;
  count=1;
  ret_getblock=metadata_get_block(filename,header,i,my_block);
  for(int j=1;j<DiNodes_per_Block;j++)
  {
    if(count < header->numOf_DiNodes)
    {
      printf("DiNode %d: %s ",count,my_block->table[j].name);
      if(my_block->table[j].isDir == true)
      {
        printf("is directory ");
      }
      else
      {
        printf("is file ");
      }

      grp = getgrgid(my_block->table[j].gid);

      pwd = getpwuid(my_block->table[j].uid);

      printf("with owner: %s, group: %s, access rights: ",pwd->pw_name,grp->gr_name);
      
      printf( (my_block->table[j].mode & S_IRUSR) ? "r" : "-");
      printf( (my_block->table[j].mode & S_IWUSR) ? "w" : "-");
      printf( (my_block->table[j].mode & S_IXUSR) ? "x" : "-");
      printf( (my_block->table[j].mode & S_IRGRP) ? "r" : "-");
      printf( (my_block->table[j].mode & S_IWGRP) ? "w" : "-");
      printf( (my_block->table[j].mode & S_IXGRP) ? "x" : "-");
      printf( (my_block->table[j].mode & S_IROTH) ? "r" : "-");
      printf( (my_block->table[j].mode & S_IWOTH) ? "w" : "-");
      printf( (my_block->table[j].mode & S_IXOTH) ? "x" : "-");
      printf("\n");

      count++;
    }
    else
    {
      break;
    }
  }
  i++;
  ret_getblock=metadata_get_block(filename,header,i,my_block);
  while(ret_getblock != -1)
  {
    for(int j=0;j<DiNodes_per_Block;j++)
    {
      if(count < header->numOf_DiNodes)
      {
        printf("DiNode %d: %s ",count,my_block->table[j].name);
        if(my_block->table[j].isDir == true)
        {
          printf("is directory ");
        }
        else
        {
          printf("is file ");
        }
        grp = getgrgid(my_block->table[j].gid);

        pwd = getpwuid(my_block->table[j].uid);

        printf("with owner: %s, group: %s, access rights: ",pwd->pw_name,grp->gr_name);

        printf( (my_block->table[j].mode & S_IRUSR) ? "r" : "-");
        printf( (my_block->table[j].mode & S_IWUSR) ? "w" : "-");
        printf( (my_block->table[j].mode & S_IXUSR) ? "x" : "-");
        printf( (my_block->table[j].mode & S_IRGRP) ? "r" : "-");
        printf( (my_block->table[j].mode & S_IWGRP) ? "w" : "-");
        printf( (my_block->table[j].mode & S_IXGRP) ? "x" : "-");
        printf( (my_block->table[j].mode & S_IROTH) ? "r" : "-");
        printf( (my_block->table[j].mode & S_IWOTH) ? "w" : "-");
        printf( (my_block->table[j].mode & S_IXOTH) ? "x" : "-");
        printf("\n");

        count++;
      }
      else
      {
        break;
      }
    }
    i++;
    ret_getblock=metadata_get_block(filename,header,i,my_block);
  }
  
  if(count == 1)
  {
    printf("No Meta Data is found, file .di is empty\n");
  }

  free(my_block->table);
  free(my_block);
  return true;
}

bool file_exists(Cli_args* cli_args,Header* header,char* filename) {
  
  int32_t i,ret_getblock,count,DiNodes_per_Block;
  Block* my_block;

  my_block=malloc(sizeof(Block));
  DiNodes_per_Block=BLOCK_SIZE / sizeof(DiNode);
  my_block->table=malloc(DiNodes_per_Block*sizeof(DiNode));     // Initialize space for the Block
  
  bool* found=malloc(sizeof(bool)*cli_args->numOf_files);
  for(int l=0; l<cli_args->numOf_files; l++)
  {
    found[l]=false;
  }

  i=0;
  count=0;
  ret_getblock=metadata_get_block(filename,header,i,my_block);
  while(ret_getblock != -1)
  {
    for(int j=0;j<DiNodes_per_Block;j++)
    {
      if(count < header->numOf_DiNodes)
      {
        
        for(int l=0; l<cli_args->numOf_files; l++)
        {
          if(strcmp(cli_args->list_of_files[l],my_block->table[j].name) == 0)
          {
            found[l]=true;
            break;
          }
        }

        count++;
      }
      else
      {
        break;
      }
    }
    i++;
    ret_getblock=metadata_get_block(filename,header,i,my_block);
  }
  
  if(count == 0)
  {
    printf("No Meta Data is found, file .di is empty\n");
  }
  else
  {
    for(int l=0; l<cli_args->numOf_files; l++)
    {
      printf("%s",cli_args->list_of_files[l] );
      if(found[l] == true)
      {
        printf(" exists\n");
      }
      else
      {
        printf(" doesn't exists\n");
      }
    }
  }

  free(my_block->table);
  free(my_block);
  return true;
}

bool print_inside(char* filename,Header* header,uint32_t id_of_dinode,Block* my_block)
{

  return true;
}

bool print_hierarchy(char* filename,Header *header) {
  int ret_getblock,DiNodes_per_Block;
  Block* my_block;
  DiNode* root;

  my_block=malloc(sizeof(Block));
  DiNodes_per_Block=BLOCK_SIZE / sizeof(DiNode);
  my_block->table=malloc(DiNodes_per_Block*sizeof(DiNode)); 

  ret_getblock=metadata_get_block(filename,header,0,my_block);
  if(ret_getblock != -1)
  {
    root=&my_block->table[0];
    do
    {
      for(int l=2;l<NUMOF_CHILDS;l++)
      {
        // root->isDir
      }

    }while(root->next != 0);
  }

    free(my_block->table);
    free(my_block);

  return true;
}

bool copy_to_DiNode(struct stat* the_stat,DiNode* my_dinode) {
  my_dinode->mode=the_stat->st_mode;
  my_dinode->uid=the_stat->st_uid;
  my_dinode->gid=the_stat->st_gid;
  my_dinode->size=the_stat->st_size;
  my_dinode->a_time=the_stat->st_atime;
  my_dinode->m_time=the_stat->st_mtime;
  my_dinode->c_time=the_stat->st_ctime;

  return true;
}
