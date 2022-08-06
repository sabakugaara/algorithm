#include <stdlib.h>
#include "binary_search_tree.h"

b_s_tree *search_tree(b_s_tree *l, int x) {

  if (l == NULL) {
    return NULL;
  }

  if (l->item == x) {
    return l;
  }

  if (x < l->item) {
    return search_tree(l->left, x);
  } else {
    return search_tree(l->right, x);
  }
}

b_s_tree *find_minimum(b_s_tree *t)
{
  if (t == NULL) {
    return NULL;
  }

  while(t->left != NULL) {
    return find_minimum(t->left);
  }
  return t;
}

b_s_tree *find_max(b_s_tree *t) {
  if (t == NULL) {
    return NULL;
  }

  while(t->right != NULL) {
    return find_max(t->right);
  }
  return t;
}

void traverse_tree(b_s_tree *t, void (*f)(int))
{
  if (t != NULL) {
    traverse_tree(t->left, f);
    f(t->item);
    traverse_tree(t->right, f);
  }
}

b_s_tree *create_tree(int x) {
  b_s_tree *p = malloc(sizeof(b_s_tree));
  if (p == NULL) {
    return NULL;
  }

  p->item = x;
  p->left = NULL;
  p->parent = NULL;
  p->right = NULL;
  return p;
}

// 插入一个值 x 的算法：
// 1. 如果值比当前节点大，则尝试插入其右子节点，否则尝试插入其左节点
// 2. 如果子节点为 NULL 则插入该位置，否则继续第一步。
void insert_tree(b_s_tree **current_node, int x, b_s_tree *parent_node) {
  if (*current_node == NULL) {
    b_s_tree *p;
    p = malloc(sizeof(b_s_tree));
    p->item = x;
    p->left = NULL;
    p->right = NULL;
    p->parent = parent_node;
    *current_node = p; // 之所以声明 **current_node 就是为了这一步把原来指向 NULL 的指针改为指向 p
    return;
  }
  if ((*current_node)->item > x) {
    insert_tree(&((*current_node)->left), x, *current_node);
  } else {
    insert_tree(&((*current_node)->right), x, *current_node);
  }
}

b_s_tree **get_parent_point_to_me(b_s_tree *node) {
  if (node->parent == NULL) {
    return NULL;
  }

  if (node->parent->left == node) {
    return &(node->parent->left);
  } else {
    return &(node->parent->right);
  }
}


void delete_tree(b_s_tree **delete_node) {
  if (delete_node == NULL || *delete_node == NULL) {
    return;
  }

  if ((*delete_node)->left == NULL && (*delete_node)->right == NULL) {
    // NOTE: delete node with zero children
    b_s_tree *parent = (*delete_node)->parent;
    if (parent == NULL) {
      free(*delete_node);
      *delete_node = NULL;
      return;
    }

    b_s_tree **left_or_right = get_parent_point_to_me(*delete_node);
    if (left_or_right != NULL) {
      *left_or_right = NULL;
    }

    free(*delete_node);
    *delete_node = NULL;
    return;
  }

  else if ((*delete_node)->left != NULL && (*delete_node)->right != NULL) {
    // NOTE: delete node with two children
    b_s_tree *min_node = find_minimum((*delete_node)->right);
    b_s_tree *min_parent_node = min_node->parent;

    // replace delete node by min_node
    b_s_tree **left_or_right = get_parent_point_to_me(*delete_node);
    if (left_or_right != NULL) {
      *left_or_right = min_node;
    }
    min_node->left = (*delete_node)->left;
    if ((*delete_node)->right != min_node) {
      min_node->right = (*delete_node)->right;
    }

    free(*delete_node);
    *delete_node = NULL;
    return;
  } else {
    // NOTE: delete node with one children
    b_s_tree **node = get_parent_point_to_me(*delete_node);
    if ((*delete_node)->left) {
      *node = (*delete_node)->left;
    } else {
      *node = (*delete_node)->right;
    }
    free(*delete_node);
    *delete_node = NULL;
    return;
  }
}
