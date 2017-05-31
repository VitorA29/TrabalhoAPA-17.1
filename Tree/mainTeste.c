#include "algorithm.c"

int main(void){
	Tree t = create_tree();
	Employee e = create_employee(), s = create_employee();
	char str[11];
	initialize_tree(t);
	initialize_employee(e);
	initialize_employee(s);
	set_employee_name(e, "0");
	set_employee_name(s, "0");
	insert_tree(t, e, NULL, 666.0);
	float f=1;
	while(f<11){
		e = create_employee();
		initialize_employee(e);
		sprintf(str, "%.0f", f);
		set_employee_name(e, str);
		insert_tree(t, e, s , f++);
	}
	set_employee_name(s, "4");
	while(f<21){
		e = create_employee();
		initialize_employee(e);
		sprintf(str, "%.0f", f);
		set_employee_name(e, str);
		insert_tree(t, e, s , f++);
	}
	set_employee_name(s, "15");
	while(f<31){
		e = create_employee();
		initialize_employee(e);
		sprintf(str, "%.0f", f);
		set_employee_name(e, str);
		insert_tree(t, e, s , f++);
	}
	print_tree(t);
	List l=create_list();
	initialize_list(l);
	printf("%.2f", resolver(t, l));
	print_list(l);
	exclude_tree(t);
	//exclude_list(l);
	exclude_employee(s);
	return 0;
}
