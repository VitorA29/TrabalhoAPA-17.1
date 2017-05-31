#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struct_employee *Employee, SEmployee;

Employee create_employee(void);
Employee gerate_employee(void);
void set_employee_name(Employee, char *name);
char* get_employee_name(Employee);
Employee copy_employee(Employee origin);
int compare_employee(Employee employee_1, Employee employee_2);
void print_employee(Employee);
void exclude_employee(Employee);
