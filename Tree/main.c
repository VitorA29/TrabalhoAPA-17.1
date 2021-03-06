#include <stdio.h>
#include <time.h>
#include "res/Tree.h"
#include "res/Employee.h"
#include "res/EmployeeList.h"
#include "algorithm.c"

Tree root = NULL, supervisor=NULL;
Employee e;
List l;
float cr;

int main(){
	char deci, auxAtoi[21];
	int index, new;
	printf("Import existent tree from archive?<s|n> ");
	scanf(" %c", &deci);
	if(deci=='s')root=read_file_tree();
	if(!root){
		root=create_tree();
		initialize_tree(root);
	}
	Tree t = root;
	e=NULL;
	clock_t start, end;
	double time;
	while(1){
		printf("\n");
		print_super_subs(t);
		printf("\n[1]Mark this employee as supervisor;\n[2]Insert employee in marked supervisor;\n[3]Print whole tree;\n[4]Go to a subordinate employee;\n[5]Back to supervisor;\n[6]PARTIU BAILE!!!\n[7]Export tree to archive;\n[e]Exit;\n");
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
					printf("Resolver comparativamente?");
					scanf(" %c", &deci);
					if(deci=='s')start = clock();
					l=resolver(root, 1);
					if(deci=='s')end = clock();
					print_list(l);
					printf("\n");
					exclude_list(l);
					if(deci=='s'){
						time=(double)(end - start);
						start = clock();
						l=resolver(root, 2);
						end = clock();
						printf("Execução dinamica: %f - Execução sem dinamica: %f", time, (double)(end-start));
						printf("\n");
						exclude_list(l);
					}
				}
				break;
			case '7':
				if(!empty_tree(root))write_file_tree(root);
				break;
			case 'e':
				exclude_tree(root);
				return 0;
		}
		printf("\n\nRepeating Cyclo\n");
	}
	return 0;
}
