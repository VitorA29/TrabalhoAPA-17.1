#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"

typedef struct struct_employees_list *List, SList;

List create_list(void);

void initialize_list(List);

void clear_list(List);

void add_list(List, Employee);

void join_list(List destiny, List origin);

void print_list(List);

void exclude_list(List);
