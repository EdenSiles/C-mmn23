#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void convert_num(int *num, char *words[]);
void print_to_stdout(int *num, char *words[]);
void init_arrays(int *num, char *words[]);
void print_to_file(int *num, char *words[], FILE *output);
void stdin_to_stdout(int *num, char *words[]);
void stdin_to_file(int *num, char *words[],char *file_name);
void file_to_file(int *num, char *words[], char *file_name1, char *file_name2);

int main(int argc, char *argv[])
{
	int num[2]; /*num[0] represents the tens and num[1] represents the units*/
	char *words[2]; /*same as num[2] but represents the numbers in letters*/
	
	init_arrays(num, words);
	
	/*case:input is stdin and output is stdout*/
	if (argc == 1) {
		stdin_to_stdout(num, words);
	}

	/*case:input is file and output is stdout*/
	else if (argc == 2) {
		stdin_to_file(num, words,argv[1]);
	}
	
	/*case:input is file and output is file*/
	else if (argc == 3) {
		file_to_file(num, words, argv[1],argv[2]);
	}
	
	else { 
		fprintf(stderr, "Error: too many argumanets\n");
		exit(7);
	}
	return 0;
}

/*this function save the converted numbers in words array*/
void convert_num(int *num, char *words[]) {

	/*init arrays that represent all number options*/
	char *one_digits[] = { "zero", "one", "two", "three", "four","five","six", "seven", "eight", "nine" };
	char *two_digits[] = { "ten", "eleven", "twelve", "thirteen", "fourteen","fifteen", "sixteen","seventeen", "eighteen", "nineteen" };
	char *tens_multiple[] = { " " ," ", "twenty", "thirty", "fourty", "fifty","sixty", "seventy", "eighty", "ninety" };

	/*one digit number*/
	if (num[0] == -1) {
		words[0] = NULL;
		words[1]= one_digits[num[1]];
		return;
	}

	/*number between 10-19*/
	else if (num[0] == 1) {
		words[0] = NULL;
		words[1] = two_digits[num[1]];
		return;
	}
	
	/*number which is a multiple of 10 (not include 10)*/
	 else if ((num[0] != -1) && (num[1] == 0)) {
		words[0] = tens_multiple[num[0]];
		words[1] = NULL;
		return;
	}
	/*regular number with 2 digits*/
	else {
		words[0] = tens_multiple[num[0]];
		words[1] = one_digits[num[1]];
		
		return;
	}
}

void print_to_stdout(int *num, char *words[]) {
	
	if ((words[0] != NULL) && (words[1] == NULL)) /*print number which is a multiple of 10*/
		printf("%s\n", words[0]);
	else if ((words[0] != NULL) && (words[1] != NULL)) { /*print number with 2 digits which is not a multiple of 10*/
		printf("%s ", words[0]);
		printf("%s\n", words[1]);
	}
	else if ((words[0] == NULL) && (words[1] != NULL)) { /*print one digit number*/
		printf("%s\n", words[1]);
	}
}

/*this function init the arrays*/
void init_arrays(int *num, char *words[]) {
	
	int i;
	for (i = 0; i < 2; i++) {
		num[i] = -1;
		words[i] = NULL;
	}
}

/*this function print the words to file using fprint.*/
void print_to_file(int *num, char *words[], FILE *output) {
	
	if ((words[0] != NULL) && (words[1] == NULL)) { /*print number which is a multiple of 10*/
		fprintf(output, "%s\n", words[0]);
	}
	else if ((words[0] != NULL) && (words[1] != NULL)) { /*print number with 2 digits which is not a multiple of 10*/
		fprintf(output, "%s ", words[0]);
		fprintf(output, "%s\n", words[1]);
	}
	else if ((words[0] == NULL) && (words[1] != NULL)) { /*print one digit number*/
		fprintf(output, "%s\n", words[1]);
	}
}

void stdin_to_stdout(int *num, char *words[]) {
	
	char c;
	int digit, flag = 0;  /*flag=0 ->we search for the tens in the number/ flag=1 -> we search for the units in the number*/
	
	while ((c = getchar()) != EOF) {
		if (isdigit(c)) { /*check if the char is a number*/
			digit = c - '0';
			if (flag == 0) { /*tens case, save the digit in num[0]*/
				num[0] = digit;
				flag = 1;
			}
			else if (flag == 1) {/*units case, save the digit in num[1]*/
				num[1] = digit;
				convert_num(num, words); /*convert number with 2 digits*/
				print_to_stdout(num, words); /*print the convert number to stdout*/


				init_arrays(num, words);
				flag = 0;
			}
		}
		else if ((num[0] != -1) && (!isdigit(c))) { /*convert and print number with one digit only*/
			num[1] = num[0];
			num[0] = -1;
			convert_num(num, words);
			printf("%s\n", words[1]);
			init_arrays(num, words);
			flag = 0;
		}

	}
}

void stdin_to_file(int *num, char *words[], char *file_name) {

	char c;
	int digit, flag = 0; /*flag=0 ->we search for the tens in the number/ flag=1 -> we search for the units in the number*/
	FILE *input;

	input = fopen(file_name, "r"); /*open input file*/
	if (input == NULL) { /*check if open successed*/
		fprintf(stderr, "Error: open input file failed\n");
		exit(7);
	}

	while ((c = fgetc(input)) != EOF) { 
		if (isdigit(c)) { /*check if the char is a number*/
			digit = c - '0';
			if (flag == 0) { /*tens case, save the digit in num[0]*/
				num[0] = digit;
				flag = 1;
			}
			else if (flag == 1) { /*units case, save the digit in num[1]*/
				num[1] = digit;
				convert_num(num, words); /*convert number with 2 digits*/
				print_to_stdout(num, words); /*print the convert number to stdout*/

				init_arrays(num, words); 
				flag = 0;
			}
		}
		else if ((num[0] != -1) && (!isdigit(c))) { /*convert and print number with one digit only*/
			num[1] = num[0];
			num[0] = -1;
			convert_num(num, words);
			printf("%s\n", words[1]);
			init_arrays(num, words);
			flag = 0;
		}

	}

	fclose(input); /*close input file*/
}

void file_to_file(int *num, char *words[], char *file_name1, char *file_name2) {
	char c;
	int digit, flag = 0; /*flag=0 ->we search for the tens in the number/ flag=1 -> we search for the units in the number*/
	FILE *input, *output;
	
	input = fopen(file_name1, "r"); /*open input file*/
	output = fopen(file_name2, "w"); /*open output file*/
	if (input == NULL) { /*check if open successed*/
		fprintf(stderr, "Error: open input file failed\n");
			exit(7);
	}
	if(output == NULL) { /*check if open successed*/
		fprintf(stderr, "Error: open output file failed\n");
		exit(7);
		
	}

	while ((c = fgetc(input)) != EOF) {
		if (isdigit(c)) { /*check if the char is a number*/
			digit = c - '0';
			if (flag == 0) { /*tens case, save the digit in num[0]*/
				num[0] = digit;
				flag = 1;
			}
			else if (flag == 1) { /*units case, save the digit in num[1]*/
				num[1] = digit;
				convert_num(num, words); /*convert number with 2 digits*/
				print_to_file(num, words, output); /*print the convert number to file*/

				init_arrays(num, words);
				flag = 0;
			}
		}
		else if ((num[0] != -1) && (!isdigit(c))) { /*convert and print number to file with one digit only*/
			num[1] = num[0];
			num[0] = -1;
			convert_num(num, words);
			fprintf(output, "%s\n", words[1]);
			init_arrays(num, words);
			flag = 0;
		}
	}
	fclose(input); /*close input file*/
	fclose(output); /*close output file*/
}