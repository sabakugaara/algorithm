
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct tree {
  int item;
  struct tree *parent;
  struct tree *left;
  struct tree *right;
} b_s_tree;

b_s_tree *create_tree(int x);
b_s_tree *search_tree(b_s_tree *l, int x);

b_s_tree *find_minimum(b_s_tree *t);
b_s_tree *find_max(b_s_tree *t);

void traverse_tree(b_s_tree *t, void (*f)(int));
void insert_tree(b_s_tree **current_node, int x, b_s_tree *parent_node);
void delete_tree(b_s_tree **delete_node);

#endif
