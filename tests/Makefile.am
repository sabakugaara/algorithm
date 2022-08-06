## Process this file with automake to produce Makefile.in

TESTS = check_binary_search_tree
check_PROGRAMS = check_binary_search_tree
check_binary_search_tree_SOURCES = check_binary_search_tree.c $(top_builddir)/src/binary_search_tree.h
check_binary_search_tree_CFLAGS = @CHECK_CFLAGS@
check_binary_search_tree_LDADD = $(top_builddir)/src/libtree.la @CHECK_LIBS@
