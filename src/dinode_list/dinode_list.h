/******************************************************************************
 * File : dinode_list.h
 * Purpose : Interface for the dinode list.
******************************************************************************/

/* System Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/********************/

/* User Libraries */
#include "../file_structure/file_structure.h"
/******************/

typedef struct Node {
  DiNode* info;
  struct Node* next_node;
} Node;

typedef struct List {
  int32_t numOf_nodes;
  Node* header_node;
} List;

bool list_init(List* list);

bool push_dinode(List* list, DiNode* info);

bool pop_dinode(List* list, DiNode** info);

bool print_list(List* list);
