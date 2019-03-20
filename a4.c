#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
   Maksim Semchuk
   Program #4
   02/26/2019

   This program is for Mark Morrisey CS 201 Class
   The point of the program is to learn:
   Program arguments,
   data conversion,
   C structures,
   pointers to functions.
 */

typedef int func_ptr(int , char **); //defines the type of function return to exect. Return type of all functions is ints, and takes in a int and a char *.


//define the format of the function to be passed in:
typedef int func_ptr(int , char **);

//structure for dispatch table:
typedef struct{
	char *desc;
	func_ptr *func_name; //func_name is the function you want to call.
} disp_table;

//defining the functions that will do the operations.
int exito(int nums , char *strcons[]){
	printf("\n\nGoodbye!\n\n\n");
	return 0;
}


int add(int nums , char *strcons[]){

	int sum = 0;
	int i = 1; //initialize the variable that will hold the sum and the iterator.

	for(i = 1 ; i < nums && i < 6; ++i){
		if(strcons[i][1] == 'x' && i < 6){
			printf("Options 1-5 must be integer values!");
			exit(EXIT_FAILURE);
		}
		else{
			sum = sum + atoi(strcons[i]);
		}
	}
	if(nums >= 6){
		for(i = 6 ; i < nums ; ++i){
			if(strcons[i][1] == 'x'){
				sum = sum + strtol(strcons[i] , NULL , 16);
			}
			else{
				sum = sum + atoi(strcons[i]);
			}
		}
	}


	printf("\nThe sum of the numbers added up is: %d" , sum);

	return 0;
}
int sub(int nums , char *strcons[]){

	int diff = 0; //initialize to zero. This will hold the answer.
	int i = 1; //index counter

	for( i=1 ; i < nums && i < 6; ++i){
		if(strcons[i][1] == 'x' && i < 6){
			printf("Options 1-5 must be integer values!");
			exit(EXIT_FAILURE);
		}
		else{
			diff = diff - atoi(strcons[i]);
		}
	}
	if(nums >= 6){
		for(i = 6 ; i < nums ; ++i){
			if(strcons[i][1] == 'x'){
				diff = diff - strtol(strcons[i] , NULL , 16);
			}
			else{
				diff = diff - atoi(strcons[i]);
			}
		}
	}

	printf("\nThe sum of the numbers subtracted is: %d" , diff);

	return 0;
}
int mult(int nums , char *strcons[]){
	int prod = 1; //set to one because 0 * anything is 0;
	int i = 1;

	for(i=1 ; i < nums && i < 6 ; ++i){
		if(strcons[i][1] == 'x' && i < 6){
			printf("Options 1-5 must be integer values!");
			exit(EXIT_FAILURE);
		}
		else{
			prod = prod * atoi(strcons[i]);
		}
	}
	if(nums >= 6){
		for(i = 6 ; i < nums ; ++i){
			if(strcons[i][1] == 'x'){
				prod = prod * strtol(strcons[i] , NULL , 16);
			}
			else{
				prod = prod * atoi(strcons[i]);
			}
		}
	}

	printf("\nThe product of the numbers is: %d" , prod);

	return 0;
}
int division(int nums , char *strcons[]){

	float quot = 0;

	//for the first number
	if(strcons[1][1] == 'x'){
		quot = strtol(strcons[1] , NULL , 16);
	}
	else{
		quot = atoi(strcons[1]);
	}
	//for the second number
	if(strcons[2][1] == 'x'){
		quot = quot / strtol(strcons[2] , NULL , 16);
	}
	else{
		quot = quot / atoi(strcons[2]);
	}

	printf("\nThe quotient of first two numbers in the list is: %lf" , quot);


	return 0;
}
int mod(int nums , char *strcons[]){
	int rem = 0;

	//for the second number
	if(strcons[1][1] == 'x'){
		rem = strtol(strcons[1] , NULL , 16);
	}
	else{
		rem = atoi(strcons[1]);
	}
	//for the second number
	if(strcons[2][1] == 'x'){
		rem = rem % strtol(strcons[2] , NULL , 16);
	}
	else{
		rem = rem % atoi(strcons[2]);
	}

	printf("\nThe remainder of first two numbers in the list is: %d" , rem);

	return 0;
}
int reverse(int nums , char *strcons[]){
	int i , r;

	char ** revstr = malloc((nums - 1) * sizeof(*revstr));

	for(i=1 , r = nums-2 ; i < nums ; ++i , --r){
		revstr[r] = strcons[i];
	}

	for(r = 0 ; r < nums-1 ; ++r){
		printf(" %s " , revstr[r]);
	}
	free(revstr);

	return 0;
}

//defining all of the functions I will call, into the dispatch table.
disp_table ftd[] = {
	{"Exit" , exito} ,
	{"Addition" , add} ,
	{"Subtraction" , sub} ,
	{"Multiplication" , mult} ,
	{"Division" , division} ,
	{"Modulo" , mod} ,
	{"Reverse Input" , reverse}
};



int main_menu(int count , char *argv[]){

	if(count < 3 || count > 16){
		printf("\nEnter between 2 and 15 arguments at the command line\n");
		exit(EXIT_FAILURE);
	}
	int i;
	for(i = 1 ; i < count; ++i){
		if(argv[i][1] == 'x' && i < 6){
			printf("\n\nThe First 5 arguments MUST be decimal numbers, then up to 15 aguments can be decimal or hex\n\n");
			exit(EXIT_FAILURE);
		}
	}

	int choice = 100;
	char *choices[] = {"Exit", "Addition", "Subtraction", "Multiplication", "Division", "Modulo", "Reverse Input"};

	printf("\n########################\n\n\n");
	while( choice != 0 ){
		printf("\nPlease Make a selection:\n");
		for(int i = 0 ; i < 7 ; ++i){
			printf("\n%d) %s" , i , choices[i]);
		}
		printf("\n\n");
		printf("\n########################\n\n\n");

		//scans for user input.
		int res0 = scanf("%d" , &choice);
		if(res0 < 0){
			exit(EXIT_FAILURE); //if error occurs while scanning in answer, exit program.
		}

		(*ftd[choice].func_name)(count , argv); //calls the function with a pointer.
	}

	return 0;
}

int ftdcount = sizeof(ftd)/sizeof(ftd[0]); //determines the size of ftd count.




int main( int argc , char * argv[]){
	main_menu(argc , argv);

	return 0;
}
