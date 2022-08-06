#include <stdlib.h>
#include <check.h>
#include "../src/binary_search_tree.h"

START_TEST(test_create)
{
  b_s_tree *t = create_tree(1);
  ck_assert_int_eq(t->item, 1);
  ck_assert(t->left == NULL);
  ck_assert(t->right == NULL);
  ck_assert(t->parent == NULL);
}
END_TEST

START_TEST(test_insert_tree)
{
  b_s_tree *t = create_tree(1);

  insert_tree(&t, 2, t->parent);
  insert_tree(&t, 3, t->parent);
  ck_assert_int_eq(t->item, 1);
  ck_assert_int_eq(t->right->item, 2);
  ck_assert_int_eq(t->right->right->item, 3);
}
END_TEST

START_TEST(test_insert_tree_2)
{
  b_s_tree *t = create_tree(2);

  insert_tree(&t, 1, t->parent);
  insert_tree(&t, 3, t->parent);
  insert_tree(&t, 4, t->parent);
  ck_assert_int_eq(t->item, 2);
  ck_assert_int_eq(t->left->item, 1);
  ck_assert_int_eq(t->right->item, 3);
  ck_assert_int_eq(t->right->right->item, 4);
}
END_TEST

START_TEST(test_find_only_one_node)
{
  b_s_tree *t = create_tree(5);
  b_s_tree *min = find_minimum(t);
  b_s_tree *max = find_max(t);
  ck_assert_int_eq(min->item, 5);
  ck_assert_int_eq(max->item, 5);
}
END_TEST

START_TEST(test_find_multi_nodes)
{
  b_s_tree *t = create_tree(5);

  insert_tree(&t, 1, t->parent);
  insert_tree(&t, 3, t->parent);
  insert_tree(&t, 4, t->parent);
  insert_tree(&t, -3, t->parent);
  insert_tree(&t, 0, t->parent);
  insert_tree(&t, -1, t->parent);
  insert_tree(&t, 10, t->parent);

  b_s_tree *min = find_minimum(t);
  b_s_tree *max = find_max(t);
  ck_assert_int_eq(min->item, -3);
  ck_assert_int_eq(max->item, 10);
}
END_TEST

int result[8];
int pos = 0;
void traverse_cb(int x)
{
  result[pos] = x;
  ++pos;
}

START_TEST(test_traverse_tree)
{
  b_s_tree *t = create_tree(5);

  insert_tree(&t, 1, t->parent);
  insert_tree(&t, 3, t->parent);
  insert_tree(&t, 4, t->parent);
  insert_tree(&t, -3, t->parent);
  insert_tree(&t, 0, t->parent);
  insert_tree(&t, -1, t->parent);
  insert_tree(&t, 10, t->parent);

  int expect[] = {-3, -1, 0, 1, 3, 4, 5, 10};
  traverse_tree(t, traverse_cb);

  for (int i = 0; i < 8; i++) {
    ck_assert_int_eq(expect[i], result[i]);
  }
}
END_TEST

START_TEST(test_delete_only_one_node)
{
  b_s_tree *t = create_tree(5);
  delete_tree(&t);
  ck_assert(t == NULL);
}
END_TEST

START_TEST(test_delete_zero_children_node)
{
  b_s_tree *t = create_tree(2);
  insert_tree(&t, 1, t->parent);
  insert_tree(&t, 7, t->parent);
  insert_tree(&t, 4, t->parent);
  insert_tree(&t, 8, t->parent);
  insert_tree(&t, 3, t->parent);
  insert_tree(&t, 6, t->parent);
  insert_tree(&t, 5, t->parent);

  b_s_tree *node4 = search_tree(t, 4);
  b_s_tree *delete_node = search_tree(t, 3);
  ck_assert(delete_node->item == 3);
  ck_assert(node4->left == delete_node);

  delete_tree(&delete_node);

  ck_assert(delete_node == NULL);
  ck_assert(search_tree(t, 3) == NULL);
  ck_assert(node4->left == NULL);
}
END_TEST


START_TEST(test_delete_one_children_node)
{
  b_s_tree *t = create_tree(2);
  insert_tree(&t, 1, t->parent);
  insert_tree(&t, 7, t->parent);
  insert_tree(&t, 4, t->parent);
  insert_tree(&t, 8, t->parent);
  insert_tree(&t, 3, t->parent);
  insert_tree(&t, 6, t->parent);
  insert_tree(&t, 5, t->parent);

  b_s_tree *node4 = search_tree(t, 4);
  b_s_tree *delete_node = search_tree(t, 6);
  b_s_tree *child_node = delete_node->left;
  ck_assert_int_eq(delete_node->item, 6);
  ck_assert(node4->right == delete_node);

  delete_tree(&delete_node);

  ck_assert(delete_node == NULL);
  ck_assert(search_tree(t, 6) == NULL);
  ck_assert_int_eq(node4->right->item, 5);
  ck_assert(node4->right == child_node);
}
END_TEST


START_TEST(test_delete_two_children_node)
{
  b_s_tree *t = create_tree(2);
  insert_tree(&t, 1, t->parent);
  insert_tree(&t, 7, t->parent);
  insert_tree(&t, 4, t->parent);
  insert_tree(&t, 8, t->parent);
  insert_tree(&t, 3, t->parent);
  insert_tree(&t, 6, t->parent);
  insert_tree(&t, 5, t->parent);

  b_s_tree *node7 = search_tree(t, 7);
  b_s_tree *delete_node = search_tree(t, 4);
  ck_assert(node7->left == delete_node);

  delete_tree(&delete_node);

  ck_assert(delete_node == NULL);
  ck_assert(search_tree(t, 4) == NULL);
  ck_assert_int_eq(node7->left->item, 5);
  ck_assert_int_eq(node7->left->left->item, 3);
  ck_assert_int_eq(node7->left->right->item, 6);
}
END_TEST

START_TEST(test_delete_two_children_node_and_only_one_right_node)
{
  b_s_tree *t = create_tree(2);
  insert_tree(&t, 1, t->parent);
  insert_tree(&t, 7, t->parent);
  insert_tree(&t, 4, t->parent);
  insert_tree(&t, 8, t->parent);
  insert_tree(&t, 3, t->parent);
  insert_tree(&t, 6, t->parent);
  insert_tree(&t, 5, t->parent);

  b_s_tree *delete_node = search_tree(t, 7);
  delete_tree(&delete_node);

  b_s_tree *node8 = search_tree(t, 8);
  ck_assert(delete_node == NULL);
  ck_assert(t->right == node8);
  ck_assert(node8->right == NULL);
  ck_assert_int_eq(node8->left->item, 4);
}
END_TEST

START_TEST(test_search_node)
{
  b_s_tree *t = create_tree(2);
  insert_tree(&t, 1, t->parent);
  insert_tree(&t, 7, t->parent);
  insert_tree(&t, 4, t->parent);
  insert_tree(&t, 8, t->parent);
  insert_tree(&t, 3, t->parent);
  insert_tree(&t, 6, t->parent);
  insert_tree(&t, 5, t->parent);
  b_s_tree *t1 = search_tree(t, 3);
  ck_assert_int_eq(t1->item, 3);

  b_s_tree *t2 = search_tree(t, 2);
  ck_assert_int_eq(t2->item, 2);

  b_s_tree *t3 = search_tree(t, 5);
  ck_assert_int_eq(t3->item, 5);
}
END_TEST


Suite * binary_search_tree_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("BinarySearchTree");
  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_create);
  tcase_add_test(tc_core, test_insert_tree);
  tcase_add_test(tc_core, test_insert_tree_2);
  tcase_add_test(tc_core, test_find_only_one_node);
  tcase_add_test(tc_core, test_find_multi_nodes);
  tcase_add_test(tc_core, test_traverse_tree);
  tcase_add_test(tc_core, test_search_node);
  tcase_add_test(tc_core, test_delete_only_one_node);
  tcase_add_test(tc_core, test_delete_zero_children_node);
  tcase_add_test(tc_core, test_delete_one_children_node);
  tcase_add_test(tc_core, test_delete_two_children_node);
  tcase_add_test(tc_core, test_delete_two_children_node_and_only_one_right_node);
  suite_add_tcase(s, tc_core);

  return s;
}



int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = binary_search_tree_suite();

  sr = srunner_create(s);
  // NOTE: debug need NOFORK
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
