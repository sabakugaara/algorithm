#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_tree
{
  int item;
  struct avl_tree *left;
  struct avl_tree *right;
  struct avl_tree *parent;
} avl_tree;


avl_tree *create_avl_tree(int x);

avl_tree *find_minimum(avl_tree *t);
avl_tree *find_max(avl_tree *t);

void traverse_avl_tree(avl_tree *t, void (*f)(int));
void insert_avl_tree(avl_tree **current_node, int x, avl_tree *parent_node);
avl_tree *get_tree_root(avl_tree *t);

#endif
