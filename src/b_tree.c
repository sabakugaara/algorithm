/**
 * @file b_tree.c
 * @author sabakugaara
 * @brief
 * @version 0.1
 * @date 2022-08-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#include<stdlib.h>
#include "b_tree.h"

b_tree *create_b_tree(int x, b_tree *root) {
  b_tree *node = malloc(sizeof(b_tree));
  if (node == NULL) {
    return node;
  }

  node->is_leaf = true;
  node->count = 1;
  node->values[1] = x;
  node->link[0] = root;
  // node->root = root;
  return node;
}

/**

 *
 * @param x
 * @param pval
 * @param root
 * @param child
 * @return int  如果产生新节点创建，则返回 1 ，否则返回 0
 */
int insert_b_tree(int x, int *pval, b_tree *root, b_tree **child) {

  if (root == NULL) {
    *pval = x;
    *child = NULL;
    return 1;
    // return create_b_tree(x, NULL);
  }

  int pos = root->count;
  if (x < root->values[1]) {
    pos = 0;
  } else {
    while(x < root->values[pos] && pos > 1) {
      pos--;
    }

    if (x == root->values[x]) {
      printf("Duplicates not allowed\n");
      return 0;
    }
  }


  // if (root->count < MAX && root->is_leaf == true) {
  //   add_value(x, pos, root, NULL);
  // }

  if (insert_b_tree(x, pval,root->link[pos], child)) {
    if (root->count < MAX) {
      add_value(x, pos, root, *child);
      return 0;
    } else {
      split_node(x, pval, pos, root, *child, child);
      return 1;
    }
  }
  return 0;
}


b_tree *add_value(int x, int pos, b_tree *node, b_tree *child) {
  int j = node->count;
  while(j > pos) {
    node->values[j + 1] = node->values[j];
    node->link[j + 1] = node->link[j];
    j--;
  }
  node->values[j + 1] = x;
  node->link[j + 1] = child;
  return;
}

void split_node(int x, int *pval, int pos, b_tree *node, b_tree *child, b_tree * new_node) {
  int median, j;
  // 确定分叉点 median 的位置
  if (pos > MIN)
  {
    median = MIN + 1;
  }
  else
  {
    median = MIN;
  }

  new_node = malloc(sizeof(b_tree));
  // 将分叉点右侧的值全部拷贝到新节点
  j = median + 1;
  while(j <= MAX) {
    new_node->values[j - median] = node->values[j];
    new_node->link[j - median] = node->link[j];
    j++;
  }
  node->count = median;
  new_node->count = MAX - median;


  if (pos <= MIN) {
    add_value(x, pos, node, child);
  } else {
    add_value(x, pos - median, new_node, child);
  }


  // 分叉点的值赋值到父节点
  *pval = node->values[node->count];
  // 设置父节点指针
  new_node->link[0] = node->link[0];
  node->count--;
}
