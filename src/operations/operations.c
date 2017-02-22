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
    new_for_current->isExtended=true;

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

bool add_files_recursive(List* list, DiNode* current_dinode, Header* header, bool zipit, char* archive_file_name_path) {
  char working_dir[256];
  getcwd(working_dir, 256);
  
  printf("Working dir:%s.\n", working_dir);
  
  DIR* opened_dir = NULL;
  opened_dir = opendir(current_dinode->name);
  chdir(current_dinode->name);
  struct dirent* file_inDir = NULL;
  while((file_inDir = readdir(opened_dir)) != NULL) {
    if(strcmp(file_inDir->d_name, ".") != 0 && strcmp(file_inDir->d_name, "..") != 0) {
      printf("Got from the %s dir the filename:%s\n", current_dinode->name, file_inDir->d_name);
      DiNode* new_dinode = malloc(sizeof(DiNode));
      struct stat my_stat;
      if(stat(file_inDir->d_name, &my_stat) != 0) {
        printf("Failed on stat.\n");
      }
      copy_to_DiNode(&my_stat, new_dinode);
      strcpy(new_dinode->name, file_inDir->d_name);
      new_dinode->next=0;
      new_dinode->numOf_free=NUMOF_CHILDS;
      
      update(list,current_dinode,new_dinode);
      
      bool is_dir = S_ISDIR(my_stat.st_mode);
      if(is_dir == true)
      {
        new_dinode->isDir = true;
        add_files_recursive(list, new_dinode, header, zipit, archive_file_name_path);
        chdir("..");
        
        char working_dir[256];
        getcwd(working_dir, 256);
        
        printf("Working dir:%s.\n", working_dir);
      }
      else // It's not a dir.
      {
        new_dinode->file_begining = header->Last_File;
        new_dinode->isDir = false;
        if(zipit)
        {
          //cwd Kolpa v2.
          compress_file(new_dinode->name);
          strcat(new_dinode->name,".gz");
          //Path of the achive_file Kolpa twra.
          insert_file(header, archive_file_name_path, new_dinode->name);
        }
        else
        {
          //Path of the achive_file Kolpa twra.
          insert_file(header, archive_file_name_path, new_dinode->name);
        }
      }
    }
  }

  closedir(opened_dir);

  return true;
}

bool create_archive(Cli_args cli_args) {
  int32_t fd = open(cli_args.archive_name, O_WRONLY | O_CREAT |O_APPEND, 0777);
  uint32_t total_file_size,percent;
  char filename[50];

  Header* header = malloc(sizeof(Header));

  header->MetaData_Start=sizeof(Header);
  header->MetaData_Last_DiNode=header->MetaData_Start;
  header->Last_File=header->MetaData_Start;      // Initialize Header
  header->numOf_DiNodes=100;

  strcpy(filename,cli_args.archive_name);

  write_header(filename,header);                 // Write Header in file
  printf("Size of header: %lu\n",sizeof(Header) );
  

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
  
  
  for(int32_t candidate = 0; candidate < cli_args.numOf_files; candidate++) {
    
    bool zipit = cli_args.j;
    
    struct stat my_stat;

    stat(cli_args.list_of_files[candidate], &my_stat);
    bool is_dir = S_ISDIR(my_stat.st_mode);
    
    char working_dir[256];
    getcwd(working_dir,256);
    printf("----------->The Working Directory is: %s\n",working_dir);

    if(is_dir)
    {
      DiNode* dir_inRoot = malloc(sizeof(DiNode));
      
      copy_to_DiNode(&my_stat, dir_inRoot);
      strcpy(dir_inRoot->name, cli_args.list_of_files[candidate]);
      dir_inRoot->next = 0;
      dir_inRoot->numOf_free = NUMOF_CHILDS;
      
      update(&list, root, dir_inRoot);
      dir_inRoot->isDir = true;
      add_files_recursive(&list, dir_inRoot, header, zipit, cli_args.archive_name);
      chdir("..");
    } 
    else  // It's not a dir, it's a file.
    {
      char working_dir[256];
      getcwd(working_dir, 256);
      
      printf("Working dir:%s.\n", working_dir);
      DiNode* file_inRoot = malloc(sizeof(DiNode));
      
      copy_to_DiNode(&my_stat, file_inRoot);
      strcpy(file_inRoot->name, cli_args.list_of_files[candidate]);
      file_inRoot->next = 0;
      file_inRoot->numOf_free = NUMOF_CHILDS;
      
      update(&list, root, file_inRoot);
      file_inRoot->isDir = false;
      
      file_inRoot->file_begining = header->Last_File;
      
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
  
  // print_list(&list);

  header->numOf_DiNodes=list.numOf_nodes;
  printf("MetaData Start: %d, File End: %d, Meta Data End: %d, Num of DiNodes: %d\n",header->MetaData_Start,header->Last_File,header->MetaData_Last_DiNode,header->numOf_DiNodes );

  //closedir(opened_dir);
  total_file_size=header->Last_File - sizeof(Header);
  
  
  printf("Total Size: %d \n",total_file_size);
  
  percent=total_file_size*0.25;
  printf("Percent = %d\n",percent );
  char* buf=malloc(percent*sizeof(char));

  write(fd,buf,(percent*sizeof(char)));

  header->MetaData_Start=header->Last_File + (percent*sizeof(char));
  header->MetaData_Last_DiNode=header->MetaData_Start;

  printf("Meta: %d\n",header->MetaData_Start );

  DiNode* temp;
  while(pop_dinode(&list,&temp))
  {
    metadata_add_DiNode(cli_args.archive_name,header,temp);
  }

  
  close(fd);
  write_header(filename,header);                 // Write Header in file


  return true;
}

bool append_file() {
  
  return true;
}

bool extract_file_recurcive(char* filename, Header* header, DiNode* root, uint32_t fetch) {
  mkdir(root->name, 0777);
  chdir(root->name);

  Block* main_block = malloc(sizeof(Block));
  Block* auxiliary_block = malloc(sizeof(Block));
  int32_t DiNodes_per_Block = BLOCK_SIZE/sizeof(DiNode);

  main_block->table = malloc(sizeof(DiNode) * DiNodes_per_Block);
  auxiliary_block->table = malloc(sizeof(DiNode) * DiNodes_per_Block);

  int32_t current_block = fetch;

  int32_t ret = metadata_get_block(filename, header, current_block, auxiliary_block);

  int32_t block_to_fetch = 0;
  int32_t di_node_to_fetch = 0;

  for(int32_t witness = 2; witness < (NUMOF_CHILDS - root->numOf_free); witness++) {
    block_to_fetch = root->di_number[witness] / DiNodes_per_Block;
    di_node_to_fetch = root->di_number[witness] % DiNodes_per_Block;
    if(block_to_fetch != current_block) {
      ret = metadata_get_block(filename, header, block_to_fetch, auxiliary_block);
      if(ret == -1) {
        perror("Read in block from file metadata");
      }
      current_block = block_to_fetch;
    }

    if(auxiliary_block->table[di_node_to_fetch].isDir)
    {
      extract_file_recurcive(filename, header, &auxiliary_block->table[di_node_to_fetch], current_block);
      chdir("..");
    }
    else // It's not a dir, it's a file.
    {
      export_file(auxiliary_block->table[di_node_to_fetch].file_begining, auxiliary_block->table[di_node_to_fetch].size, auxiliary_block->table[di_node_to_fetch].name, filename);
    }
  }

  while(root->next != 0) {
    block_to_fetch = root->next / DiNodes_per_Block;
    di_node_to_fetch = root->next % DiNodes_per_Block;
    ret = metadata_get_block(filename, header, block_to_fetch, main_block);
    root = &main_block->table[block_to_fetch];
    
    for(int32_t witness = 2; witness < (NUMOF_CHILDS - root->numOf_free); witness++) {
      block_to_fetch = root->di_number[witness] / DiNodes_per_Block;
      di_node_to_fetch = root->di_number[witness] % DiNodes_per_Block;
      if(block_to_fetch != current_block) {
        ret = metadata_get_block(filename, header, block_to_fetch, auxiliary_block);
        if(ret == -1) {
          perror("Read in block from file metadata");
        }
        current_block = block_to_fetch;
      }
      
      if(auxiliary_block->table[di_node_to_fetch].isDir)
      {
        extract_file_recurcive(filename, header, &auxiliary_block->table[di_node_to_fetch], current_block);
        chdir("..");
      }
      else // It's not a dir, it's a file.
      {
        export_file(auxiliary_block->table[di_node_to_fetch].file_begining, auxiliary_block->table[di_node_to_fetch].size, auxiliary_block->table[di_node_to_fetch].name, filename);
      }
    }
  }

  free(main_block->table);
  free(main_block);
  free(auxiliary_block->table);
  free(auxiliary_block);

  return true;
}

bool extract_archive(Cli_args cli_args) {
  Header* header = malloc(sizeof(Header));
  int32_t fd = open(cli_args.archive_name, O_RDONLY, 0777);
  read(fd, header, sizeof(Header));
  close(fd);

  Block* main_block = malloc(sizeof(Block));
  Block* auxiliary_block = malloc(sizeof(Block));
  int32_t DiNodes_per_Block = BLOCK_SIZE/sizeof(DiNode);

  main_block->table = malloc(sizeof(DiNode) * DiNodes_per_Block);
  auxiliary_block->table = malloc(sizeof(DiNode) * DiNodes_per_Block);

  int32_t current_block = 0;

  int32_t ret = metadata_get_block(cli_args.archive_name, header, current_block, main_block);
  ret = metadata_get_block(cli_args.archive_name, header, current_block, auxiliary_block);

  int32_t block_to_fetch = 0;
  int32_t di_node_to_fetch = 0;

  DiNode* root = NULL;
  if(ret != -1) {
    root = &main_block->table[0];

    for(int32_t witness = 2; witness < (NUMOF_CHILDS - root->numOf_free); witness++) {
      block_to_fetch = root->di_number[witness] / DiNodes_per_Block;
      di_node_to_fetch = root->di_number[witness] % DiNodes_per_Block;
      if(block_to_fetch != current_block) {
        ret = metadata_get_block(cli_args.archive_name, header, block_to_fetch, auxiliary_block);
        current_block = block_to_fetch;
      }
      
      if(auxiliary_block->table[di_node_to_fetch].isDir)
      {
        extract_file_recurcive(cli_args.archive_name, header, &auxiliary_block->table[di_node_to_fetch], current_block);
        chdir("..");
      }
      else // It's not a dir, it's a file.
      {
        export_file(auxiliary_block->table[di_node_to_fetch].file_begining, auxiliary_block->table[di_node_to_fetch].size, auxiliary_block->table[di_node_to_fetch].name, cli_args.archive_name);
      }
    }
    
    while(root->next != 0) {
      block_to_fetch = root->next / DiNodes_per_Block;
      di_node_to_fetch = root->next % DiNodes_per_Block;
      ret = metadata_get_block(cli_args.archive_name, header, block_to_fetch, main_block);
      root = &main_block->table[block_to_fetch];
      
      for(int32_t witness = 2; witness < (NUMOF_CHILDS - root->numOf_free); witness++) {
        block_to_fetch = root->di_number[witness] / DiNodes_per_Block;
        di_node_to_fetch = root->di_number[witness] % DiNodes_per_Block;
        if(block_to_fetch != current_block) {
          ret = metadata_get_block(cli_args.archive_name, header, block_to_fetch, auxiliary_block);
          current_block = block_to_fetch;
        }
        
        if(auxiliary_block->table[di_node_to_fetch].isDir)
        {
          extract_file_recurcive(cli_args.archive_name, header, &auxiliary_block->table[di_node_to_fetch], current_block);
          chdir("..");
        }
        else // It's not a dir, it's a file.
        {
          export_file(auxiliary_block->table[di_node_to_fetch].file_begining, auxiliary_block->table[di_node_to_fetch].size, auxiliary_block->table[di_node_to_fetch].name, cli_args.archive_name);
        }
      }
    }
  }

  free(header);
  free(main_block->table);
  free(main_block);
  free(auxiliary_block->table);
  free(auxiliary_block);

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

bool print_metadata(char* filename) {

  int32_t i,ret_getblock,count,DiNodes_per_Block,fd;
  Block* my_block;
  struct group *grp;
  struct passwd *pwd;
  Header* header=malloc(sizeof(Header));

  fd=open(filename,O_RDONLY,0777);
  read(fd,header,sizeof(Header));
  close(fd);

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
      if(my_block->table[j].isExtended == false)
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
      }
      else
      {
        printf("DiNode %d: is an extension\n",my_block->table[j].di_number[0]);
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
  while(ret_getblock != -1)
  {
    for(int j=0;j<DiNodes_per_Block;j++)
    {
      if(count < header->numOf_DiNodes)
      {
        if(my_block->table[j].isExtended == false)
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
        }
        else
        {
          printf("DiNode %d: is an extension\n",my_block->table[j].di_number[0]);
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
  
  if(count == 1)
  {
    printf("No Meta Data is found, file .di is empty\n");
  }

  free(header);
  free(my_block->table);
  free(my_block);
  return true;
}

bool file_exists(Cli_args* cli_args,char* filename) {
  
  int32_t i,ret_getblock,count,DiNodes_per_Block,fd;
  Block* my_block;
  Header* header=malloc(sizeof(Header));

  fd=open(filename,O_RDONLY,0777);
  read(fd,header,sizeof(Header));
  close(fd);

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

  free(header);
  free(my_block->table);
  free(my_block);
  return true;
}

bool print_inside(char* filename,Header* header,DiNode* root,int spaces,uint32_t fetch)
{
  
  Block* my_block,*my_block2;
  uint32_t current=fetch,block_to_fetch,di_node_to_fetch,ret_getblock;
  int DiNodes_per_Block;

  my_block=malloc(sizeof(Block));
  DiNodes_per_Block=BLOCK_SIZE / sizeof(DiNode);
  my_block->table=malloc(DiNodes_per_Block*sizeof(DiNode)); 

  my_block2=malloc(sizeof(Block));
  my_block2->table=malloc(DiNodes_per_Block*sizeof(DiNode));   // Too Blocks to keep my Di Node and Find the next one
  
  ret_getblock=metadata_get_block(filename,header,current,my_block2);
  
  for(int l=2;l<(NUMOF_CHILDS - root->numOf_free);l++)
  {
    for(int i=0; i<(spaces*2); i++)
    {
      printf(" ");
    }
    printf("%s\n",root->names[l].name);
    block_to_fetch=root->di_number[l] / DiNodes_per_Block;
    di_node_to_fetch=root->di_number[l] % DiNodes_per_Block;

    if(block_to_fetch != current)
    {
      ret_getblock=metadata_get_block(filename,header,block_to_fetch,my_block2);
      current=block_to_fetch;
    }

    if(my_block2->table[di_node_to_fetch].isDir == true)
    {
      print_inside(filename,header,&my_block2->table[di_node_to_fetch],spaces+1,block_to_fetch);
    }
  }
  while(root->next != 0)
  {
    block_to_fetch=root->next / DiNodes_per_Block;
    di_node_to_fetch=root->next % DiNodes_per_Block;

    ret_getblock=metadata_get_block(filename,header,block_to_fetch,my_block);

    if(ret_getblock == -1)
    {
      perror("Error finding the block");
      break;
    }
    root=&my_block->table[di_node_to_fetch];

    for(int l=2;l<(NUMOF_CHILDS - root->numOf_free);l++)
    {
      for(int i=0; i<(spaces*2); i++)
      {
        printf(" ");
      }
      printf("%s\n",root->names[l].name);
      block_to_fetch=root->di_number[l] / DiNodes_per_Block;
      di_node_to_fetch=root->di_number[l] % DiNodes_per_Block;

      if(block_to_fetch != current)
      {
        ret_getblock=metadata_get_block(filename,header,block_to_fetch,my_block2);
        current=block_to_fetch;
      }

      if(my_block2->table[di_node_to_fetch].isDir == true)
      {
        print_inside(filename,header,&my_block2->table[di_node_to_fetch],spaces+1,block_to_fetch);
      }
    }
  }

  free(my_block->table);
  free(my_block);
  free(my_block2->table);
  free(my_block2);
  return true;
}

bool print_hierarchy(char* filename) {
  int32_t fd,ret_getblock,DiNodes_per_Block,di_node_to_fetch;
  uint32_t block_to_fetch,current=0;
  Block* my_block,*my_block2;
  DiNode* root;

  Header* header=malloc(sizeof(Header));

  fd=open(filename,O_RDONLY,0777);
  read(fd,header,sizeof(Header));
  close(fd);

  my_block=malloc(sizeof(Block));
  DiNodes_per_Block=BLOCK_SIZE / sizeof(DiNode);
  my_block->table=malloc(DiNodes_per_Block*sizeof(DiNode)); 

  my_block2=malloc(sizeof(Block));
  my_block2->table=malloc(DiNodes_per_Block*sizeof(DiNode));    // Two Blocks to keep my Di Node and Find the next one

  ret_getblock=metadata_get_block(filename,header,0,my_block);
  ret_getblock=metadata_get_block(filename,header,0,my_block2);  

  if(ret_getblock != -1)
  {
    root=&my_block->table[0];
    
    for(int l=2;l<(NUMOF_CHILDS - root->numOf_free);l++)
    {
      printf("%s\n",root->names[l].name);
      block_to_fetch=root->di_number[l] / DiNodes_per_Block;
      di_node_to_fetch=root->di_number[l] % DiNodes_per_Block;

      if(block_to_fetch != current)
      {
        ret_getblock=metadata_get_block(filename,header,block_to_fetch,my_block2);
        current=block_to_fetch;
      }
      
      if(my_block2->table[di_node_to_fetch].isDir == true)
      {
        print_inside(filename,header,&my_block2->table[di_node_to_fetch],1,block_to_fetch);
      }
    }
    while(root->next != 0)
    {
      block_to_fetch=root->next / DiNodes_per_Block;
      di_node_to_fetch=root->next % DiNodes_per_Block;

      ret_getblock=metadata_get_block(filename,header,block_to_fetch,my_block);
      if(ret_getblock == -1)
      {
        perror("Error finding the block");
        break;
      }
      root=&my_block->table[di_node_to_fetch];

      for(int l=2;l<(NUMOF_CHILDS - root->numOf_free);l++)
      {
        printf("%s\n",root->names[l].name);
        block_to_fetch=root->di_number[l] / DiNodes_per_Block;
        di_node_to_fetch=root->di_number[l] % DiNodes_per_Block;

        if(block_to_fetch != current)
        {
          ret_getblock=metadata_get_block(filename,header,block_to_fetch,my_block2);
          current=block_to_fetch;
        }
        if(my_block2->table[di_node_to_fetch].isDir == true)
        {
          print_inside(filename,header,&my_block2->table[di_node_to_fetch],1,block_to_fetch);
        }
      }
    }
    
  }

  free(header);
  free(my_block->table);
  free(my_block);
  free(my_block2->table);
  free(my_block2);

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
  my_dinode->isExtended=false;

  for(int32_t candidate = 0; candidate < NUMOF_CHILDS; candidate++) {
    my_dinode->di_number[candidate] = 0;
  }

  return true;
}
