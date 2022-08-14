#include <stdbool.h>

#ifndef AVL_TREE_H
#define AVL_TREE_H


#define MAX 2
#define MIN 1

typedef struct b_tree
{
  // index start from 1, not zero
  int values[MAX + 1];
  bool is_leaf;
  int count;
  struct b_tree *link[MAX + 1];
} b_tree;

b_tree *create_b_tree(int x, b_tree *root);

#endif
