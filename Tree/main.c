#include <stdio.h>
#include "res/Tree.h"
#include "algorithm.c"

Tree root, supervisor=NULL;
Employee e;
List l;
float cr;

int main(){
	root=create_tree();
	initialize_tree(root);
	l=create_list();
	char deci, auxAtoi[21];
	int index, new;
	Tree t = root;
	e=NULL;
	while(1){
		printf("\n");
		print_super_subs(t);
		printf("\n[1]Mark this employee as supervisor;\n[2]Insert employee in marked supervisor;\n[3]Print whole tree;\n[4]Go to a subordinate employee;\n[5]Back to supervisor;\n[6]PARTIU BAILE!!!\n[e]Exit;\n");
		scanf(" %c", &deci);
		switch(deci){
			case '1':
				if(!empty_tree(t))supervisor=t;
				break;
			case '2':
				new=1;
				if(e){
					printf("Use the employee ( ");
					print_employee(e);
					printf(" - %.5f ) in buffer?<s|n> ", cr);
					scanf(" %c", &deci);
					if(deci=='s')new=0;
					else exclude_employee(e);
				}
				if(new){
					e=gerate_employee();
					printf("Type the conviviability rating of this employee: ");
					scanf("%s", auxAtoi);
					cr = atof(auxAtoi);
				}
				if(supervisor){
					printf("Insert a employee to this superior ");
					print_node_tree(supervisor);
					printf(" ?<s|n> ");
					scanf(" %c", &deci);
				}
				else deci='n';
				if(deci=='s'){if(insert_tree(root, e, supervisor, cr))e=NULL;}
				else{
					if(empty_tree(root)){
							printf("Insert as root?<s|n> ");
							scanf(" %c", &deci);
							if(deci=='s'){if(insert_tree(root, e, NULL, cr))e=NULL;}
					}
					else printf("No marked supervisor.\n");
				}
				break;
			case '3':
				print_tree(root);
				break;
			case '4':
				if(has_sub_tree(t)){
					do{
						printf("Choose the subordinate index: ");
						scanf("%s", auxAtoi);
						index=atoi(auxAtoi);
					}while(!get_sub_tree(t, index));
					t=get_sub_tree(t, index);
				}
				break;
			case '5':
				if(get_super_tree(t))t=get_super_tree(t);
				break;
			case '6':
				if(!empty_tree(root)){
					initialize_list(l);
					printf("%.5f\t", resolver(root, l));
					print_list(l);
				}
				break;
			case 'e':
				exclude_tree(root);
				exclude_list(l);
				return 0;
		}
		printf("\n\nRepeating Cyclo\n");
	}
	return 0;
}
