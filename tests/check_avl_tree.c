
#include <stdlib.h>
#include <check.h>
#include "../src/avl_tree.h"

START_TEST(test_create_avl_tree)
{
  avl_tree *t = create_avl_tree(1);
  ck_assert_int_eq(t->item, 1);
  ck_assert(t->right == NULL);
  ck_assert(t->left == NULL);
  ck_assert(t->parent == NULL);
}
END_TEST

START_TEST(test_insert_avl_tree_left_rotation)
{
  avl_tree *t = create_avl_tree(1);
  insert_avl_tree(&t, 5, t->parent);
  ck_assert_int_eq(t->right->item, 5);

  insert_avl_tree(&t, 10, t->parent);


  ck_assert_int_eq(t->item, 1);
  ck_assert(t->left == NULL);
  ck_assert(t->right == NULL);

  avl_tree *root = get_tree_root(t);

  ck_assert(t->parent == root);
  ck_assert_int_eq(root->item, 5);
  ck_assert(root->right != NULL);
  ck_assert_int_eq(root->right->item,  10);
  ck_assert(root->right->parent == root);
  ck_assert(root->parent == NULL);
}
END_TEST

START_TEST(test_insert_avl_tree_right_rotation)
{
  avl_tree *t = create_avl_tree(10);
  insert_avl_tree(&t, 5, t->parent);
  ck_assert_int_eq(t->left->item, 5);

  insert_avl_tree(&t, 1, t->parent);

  ck_assert_int_eq(t->item, 10);
  ck_assert(t->left == NULL);
  ck_assert(t->right == NULL);


  avl_tree *root = get_tree_root(t);
  ck_assert(t->parent == root);
  ck_assert_int_eq(root->item, 5);
  ck_assert(root->left != NULL);
  ck_assert_int_eq(root->left->item,  1);
  ck_assert(root->right == t);
  ck_assert(root->left->parent == root);
  ck_assert(root->parent == NULL);
}
END_TEST

START_TEST(test_insert_avl_tree_right_left_rotation)
{
  avl_tree *t = create_avl_tree(1);
  insert_avl_tree(&t, 10, t->parent);
  ck_assert_int_eq(t->right->item, 10);

  insert_avl_tree(&t, 5, t->parent);

  ck_assert_int_eq(t->item, 1);
  ck_assert(t->left == NULL);
  ck_assert(t->right == NULL);


  avl_tree *root = get_tree_root(t);
  ck_assert(t->parent == root);
  ck_assert_int_eq(root->item, 5);
  ck_assert(root->right != NULL);
  ck_assert_int_eq(root->right->item,  10);
  ck_assert(root->left == t);
  ck_assert(root->right->parent == root);
  ck_assert(root->parent == NULL);
}
END_TEST

START_TEST(test_insert_avl_tree_left_right_rotation)
{
  avl_tree *t = create_avl_tree(10);
  insert_avl_tree(&t, 1, t->parent);
  ck_assert_int_eq(t->left->item, 1);

  insert_avl_tree(&t, 5, t->parent);

  ck_assert_int_eq(t->item, 10);
  ck_assert(t->left == NULL);
  ck_assert(t->right == NULL);


  ck_assert(t->parent != NULL);
  ck_assert_int_eq(t->parent->item, 5);
  ck_assert(t->parent->left != NULL);
  ck_assert_int_eq(t->parent->left->item,  1);
  ck_assert(t->parent->right == t);
  ck_assert(t->parent->left->parent == t->parent);
  ck_assert(t->parent->parent == NULL);
}
END_TEST


START_TEST(test_insert_avl_tree_insert)
{
  avl_tree *t = create_avl_tree(10);
  avl_tree *root = NULL;
  insert_avl_tree(&t, 1, t->parent);
  insert_avl_tree(&t, 3, t->parent);

  root = get_tree_root(t);
  insert_avl_tree(&root, 4, root->parent);
  root = get_tree_root(t);
  insert_avl_tree(&root, 20, root->parent);
  root = get_tree_root(t);
  insert_avl_tree(&root, 15, root->parent);

  root = get_tree_root(t);
  ck_assert_int_eq(root->item, 10);
  ck_assert_int_eq(root->left->item, 3);
  ck_assert_int_eq(root->left->left->item, 1);
  ck_assert_int_eq(root->left->right->item, 4);
  ck_assert_int_eq(root->right->item, 20);
  ck_assert_int_eq(root->right->left->item, 15);


  insert_avl_tree(&root, 2, root->parent);
  root = get_tree_root(t);
  ck_assert_int_eq(root->left->left->right->item, 2);

  insert_avl_tree(&root, 11, root->parent);
  root = get_tree_root(t);
  ck_assert_int_eq(root->right->item, 15);
  ck_assert_int_eq(root->right->right->item, 20);
  ck_assert_int_eq(root->right->left->item, 11);

  insert_avl_tree(&root, 7, root->parent);
  root = get_tree_root(t);
  ck_assert_int_eq(root->left->right->right->item, 7);

  insert_avl_tree(&root, 8, root->parent);
  ck_assert_int_eq(root->left->right->left->item, 4);
  ck_assert_int_eq(root->left->right->right->item, 8);

  insert_avl_tree(&root, 9, root->parent);

  root = get_tree_root(t);
  ck_assert_int_eq(root->item, 7);
  ck_assert_int_eq(root->right->item, 10);
  ck_assert_int_eq(root->right->left->item, 8);
  ck_assert_int_eq(root->right->left->right->item, 9);
  ck_assert_int_eq(root->left->item, 3);
  ck_assert_int_eq(root->left->right->item, 4);
  ck_assert_int_eq(root->left->left->item, 1);
  ck_assert_int_eq(root->left->left->right->item, 2);
}
END_TEST


Suite * avl_tree_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("AvlTree");
  tc_core = tcase_create("avl_tree");
  tcase_add_test(tc_core, test_create_avl_tree);
  tcase_add_test(tc_core, test_insert_avl_tree_left_rotation);
  tcase_add_test(tc_core, test_insert_avl_tree_right_rotation);
  tcase_add_test(tc_core, test_insert_avl_tree_right_left_rotation);
  tcase_add_test(tc_core, test_insert_avl_tree_left_right_rotation);
  tcase_add_test(tc_core, test_insert_avl_tree_insert);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = avl_tree_suite();

  sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

