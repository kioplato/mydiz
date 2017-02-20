/******************************************************************************
 * File    : dinode_list.c
 * Purpose : Implementation of the list's behaviour/functions.
******************************************************************************/

/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/********************/

/* User Libraries */
#include "dinode_list.h"
#include "../file_structure/file_structure.h"
/******************/

bool list_init(List* list) {
  list->numOf_nodes = 0;
  list->header_node = NULL;
  list->header_node = malloc(sizeof(Node));
  if(list->header_node == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory header node.\n");
    return false;
  }
  
  list->header_node->info = NULL;
  list->header_node->next_node = NULL;
  
  return true;
}

bool push_dinode(List* list, DiNode* info) {
  Node* new_node = malloc(sizeof(Node));
  if(new_node == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory for the new node.\n");
    return false;
  }
  
  new_node->info = info;
  new_node->next_node = NULL;
  
  Node* tmp_node = NULL;
  tmp_node = list->header_node;
  while(tmp_node->next_node != NULL)
    tmp_node = tmp_node->next_node;
  
  tmp_node->next_node = new_node;
  
  list->numOf_nodes++;
  
  return true;
}

bool pop_dinode(List* list, DiNode** info) {
  if(list->numOf_nodes == 0) {
    printf("Error: The list is empty.\n");
    return false;
  }
  
  *info = list->header_node->next_node->info;
  Node* tmp_node = NULL;
  tmp_node = list->header_node->next_node;
  list->header_node->next_node = tmp_node->next_node;
  free(tmp_node);
  
  list->numOf_nodes--;
