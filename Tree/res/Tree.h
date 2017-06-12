#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"

typedef struct struct_employees_tree *Tree, STree;//NULL means no tree, a empty tree is different of NULL.

Tree create_tree(void);
void initialize_tree(Tree);
Tree search_tree(Tree, Employee);//Index is the index of the node of the tree.
int has_sub_tree(Tree);
Tree get_sub_tree(Tree, int index);//Index is the position of the subordinated employee in the list; return NULL if index not valid.
int get_index_tree(Tree);
Tree get_super_tree(Tree);
float get_conviviality_tree(Tree);
int get_qtd_nodes_tree(Tree);
Employee get_employee_tree(Tree);
int insert_tree(Tree root, Employee, Tree supervisor, float conviviality_rating);
int empty_tree(Tree);
void print_node_tree(Tree);
void print_super_subs(Tree);
void print_tree(Tree);
void write_file_tree(Tree);
Tree read_file_tree(void);
void exclude_tree(Tree);
