#include "res/Tree.h"
#include "res/EmployeeList.h"

float resolver(Tree t, List l){
	if(!has_sub_tree(t)){
		add_list(l, get_employee_tree(t));
		return get_conviviality_tree(t);
	}
	int i=0, j;
	float A=0.0, B=get_conviviality_tree(t);
	List lA = create_list(), lB = create_list();
	initialize_list(lA);
	initialize_list(lB);
	while(get_sub_tree(t, i)){
		A+=resolver(get_sub_tree(t, i), lA);
		j=0;
		while(get_sub_tree(get_sub_tree(t, i), j))
			B+=resolver(get_sub_tree(get_sub_tree(t, i), j++), lB);
		i++;
	}
	if(B>A){
		add_list(lB, get_employee_tree(t));
		join_list(l, lB);
		return B;
	}
	join_list(l, lA);
	return A;
}
