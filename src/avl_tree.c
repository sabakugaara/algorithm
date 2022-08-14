/**
 * @file avl_tree.c
 * @author sabakugaara
 * @brief
 * @version 0.1
 * @date 2022-08-07
 * @see https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm
 *
 * @copyright Copyright (c) 2022
 *
 */
#include<stdlib.h>
#include "utility.h"
#include "avl_tree.h"

/**
 * get tree height
 * 1. height = 1 if current with zero child node
 * 2. height = 2 if current with one child node
 * @param node
 * @return int
 */
int height(avl_tree *node) {
  if (node == NULL) {
    return 0;
  }

  return 1 + max(height(node->left), height(node->right));
}

avl_tree *create_avl_tree(int x) {
  avl_tree *t = malloc(sizeof(avl_tree));
  if (t == NULL) {
    return NULL;
  }

  t->item = x;
  t->parent = NULL;
  t->left = NULL;
  t->right = NULL;
  return t;
}

int get_balance(avl_tree *node) {
  if (node == NULL) {
    return 0;
  }

  return height(node->left) - height(node->right);
}

void left_rotation(avl_tree *node) {
  avl_tree *a = node;
  avl_tree *b = node->right;
  if (a == NULL || b == NULL) {
    return;
  }
  avl_tree *parent = a->parent;

  if (parent != NULL) {
    if (parent->right == node) {
      parent->right = b;
    } else {
      parent->left = b;
    }
  }
  a->right = b->left;
  if (a->right != NULL) {
    a->right->parent = a;
  }
  b->left = a;
  a->parent = b;
  b->parent = parent;
}

void right_rotation(avl_tree *node) {
  avl_tree *a = node;
  avl_tree *b = node->left;
  avl_tree *parent = a->parent;
  if (a == NULL || b == NULL) {
    return;
  }
  if (parent != NULL) {
    if (parent->right == node) {
      parent->right = b;
    } else {
      parent->left = b;
    }
  }
  a->left = b->right;
  if (a->left != NULL) {
    a->left->parent = a;
  }

  b->right = a;

  b->parent = parent;
  a->parent = b;
}

void right_left_rotation(avl_tree *node) {
  right_rotation(node->right);
  left_rotation(node);
}

void left_right_rotation(avl_tree *node) {
  left_rotation(node->left);
  right_rotation(node);
}

void insert_avl_tree(avl_tree **root_node, int x, avl_tree *parent_node) {
  if (*root_node == NULL) {
    avl_tree *p = create_avl_tree(x);
    p->parent = parent_node;
    *root_node = p;
    return;
  }
  if ((*root_node)->item > x) {
    insert_avl_tree(&((*root_node)->left), x, *root_node);
  } else {
    insert_avl_tree(&((*root_node)->right), x, *root_node);
  }

  int balance = get_balance(*root_node);

  if (balance < -1 && x > (*root_node)->right->item) {
    // NOTE: right unbalanced, do left rotation
    left_rotation(*root_node);
    return;
  }

  else if (balance < -1 && x < (*root_node)->right->item) {
    // NOTE: right unbalanced, do right-left rotation
    right_left_rotation(*root_node);
    return;
  }

  else if (balance > 1 && x < (*root_node)->left->item) {
    // NOTE: left unbalanced, do right rotation
    right_rotation(*root_node);
    return;
  }

  else if (balance > 1 && x > (*root_node)->left->item) {
    // NOTE: left unbalanced, do left-right rotation
    left_right_rotation(*root_node);
    return;
  }
}

/**
 * pre-order traversal of the tree
 *
 * @param t
 * @param f
 */
void traverse_avl_tree(avl_tree *t, void (*f)(int))
{
  if (t != NULL) {
    traverse_avl_tree(t->left, f);
    f(t->item);
    traverse_avl_tree(t->right, f);
  }
}

avl_tree *get_tree_root(avl_tree *t) {
  if (t == NULL) {
    return NULL;
  }
  while(t->parent) {
    t = t->parent;
  }
  return t;
}
