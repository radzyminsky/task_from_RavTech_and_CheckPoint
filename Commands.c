#include "Commands.h"


//function creates line separated in ',' just like a line in file.csv, then sends it to "getLine" func 
int set_command(char* str) {
	int i;
	char* fname = NULL, * lname = NULL, * id = NULL, * course_name = NULL, * grade = NULL, * temp = NULL, * ch = NULL;
	char line[200] = "";



	temp = strtok(str, ",");

	for (i = 0;i < 4; i++)  //because if has more than 4 values, then is mistake
	{
		if (!temp) {//i.e. it has lass than 4 values
			printf("Error! Missing data, please try again\n");
			return 1;
		}
		if ((ch = strchr(temp, '=')) == NULL) {
			printf("error in command, at \"%s\", please try again\n", temp);
			return 1;
		}

		*ch = '\0';  //replace character '=' at '\0',because i need to trem spaces by call "trim_space" func
		temp = trim_space(temp);

		if (!strcmp(temp, "first name")) {
			fname = ch + 1;//send to "trim_space"  the right of the '='
		}
		else if (!strcmp(temp, "second name")) {
			lname = ch + 1;
		}
		else if (!strcmp(temp, "ID")) {
			id = ch + 1;
		}
		else
		{
			course_name = temp;
			grade = ch + 1;
		}

		temp = strtok(NULL, ",");
	}

	if (temp) { // if the command contain more than 4 ','
		printf("error in command, at \"%s\", its containe too mauch detailes, please try again\n", temp);
		return 1;
	}

	if (id && fname && lname && course_name && grade) {
		strcat(line, id);
		strcat(line, ",");
		strcat(line, fname);
		strcat(line, ",");
		strcat(line, lname);
		strcat(line, ",");
		strcat(line, course_name);
		strcat(line, ",");
		strcat(line, grade);
	}
	else {
		printf("error, Missing data, may be one or mor value is duplicate, Or syntax of one or more data not valid\n");
		return 1;
	}

	return getLine(line, 0);//send to "getLine", and return what returned
}

void search_and_print(funPtr condition, char* val) {
	student* current = head;

	print_title();
	while (current)
	{
		if (condition(current, val))
			print_one(current);
		current = current->next;
	}
}


void init_str_right_left(char* ch, char* str, char** right, char** left) {
	*ch = '\0';
	*right = trim_space(str);
	*left = trim_space(ch + 1);
}

int fname_equal(student* stu, char* str) {
	return !strcmp(stu->fname, str);
}
int lname_equal(student* stu, char* str) {
	return !strcmp(stu->lname, str);
}
int id_equal(student* stu, char* str) {
	return !strcmp(stu->id, str);
}
int avg_equal(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->avg == f;
}
int clang_equal(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[Clang] == f;
}
int ComputerNet_equal(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[ComputerNet] == f;
}
int CsFund_equal(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[CsFund] == f;
}

int avg_larger(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->avg > f;
}
int clang_larger(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[Clang] > f;
}
int ComputerNet_larger(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[ComputerNet] > f;
}
int CsFund_larger(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[CsFund] > f;
}

int avg_smaller(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->avg < f;
}
int clang_smaller(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[Clang] < f;
}
int ComputerNet_smaller(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[ComputerNet] < f;
}
int CsFund_smaller(student* stu, char* str) {
	float f = (float)atof(str);
	return stu->courseGrade[CsFund] < f;
}

int is_digits(char* c) {
	int i, len = strlen(c);

	for (i = 0;i < len;i++)
		if (c[i] < '0' || c[i]>'9') {
			printf("error:  \"%s\" isn't digits\n", c);
			return 0;
		}
	return 1;
}

funPtr command_smaller(char* right, char* left) {
	if (!strcmp(right, "Average")) {
		if (is_digits(left))
			return &avg_smaller;
	}
	else if (!strcmp(right, "C lang")) {
		if (is_digits(left))
			return &clang_smaller;
	}
	else if (!strcmp(right, "CS Fundamentals")) {
		if (is_digits(left))
			return &CsFund_smaller;
	}
	else if (!strcmp(right, "Computer Networks")) {
		if (is_digits(left))
			return &ComputerNet_smaller;
	}
	else {
		printf("error,\"%s<\" isn't valid", right);
	}
	return NULL;

}
funPtr command_larger(char* right, char* left) {
	if (!strcmp(right, "Average")) {
		if (is_digits(left))
			return &avg_larger;
	}
	else if (!strcmp(right, "C lang")) {
		if (is_digits(left))
			return &clang_larger;
	}
	else if (!strcmp(right, "CS Fundamentals")) {
		if (is_digits(left))
			return &CsFund_larger;
	}
	else if (!strcmp(right, "Computer Networks")) {
		if (is_digits(left))
			return &ComputerNet_larger;
	}
	else {
		printf("error,\"%s>\" isn't valid", right);
	}
	return NULL;

}

funPtr command_equal(char* right, char* left) {
	if (!strcmp(right, "Average")) {
		if (is_digits(left))
			return &avg_equal;
	}
	else if (!strcmp(right, "C lang")) {
		if (is_digits(left))
			return &clang_equal;
	}
	else if (!strcmp(right, "CS Fundamentals")) {
		if (is_digits(left))
			return &CsFund_equal;
	}
	else if (!strcmp(right, "Computer Networks")) {
		if (is_digits(left))
			return &ComputerNet_equal;
	}
	else if (!strcmp(right, "ID")) {
		if (check_id(left))
			return &id_equal;
		printf("\"%s\" isn't valid ID\n", left);
	}
	else if (!strcmp(right, "first name")) {
		if (check_flname(left))
			return &fname_equal;
		printf("\"%s\" isn't valid name\n", left);

	}
	else if (!strcmp(right, "second name")) {
		if (check_flname(left))
			return &lname_equal;
		printf("\"%s\" isn't valid name\n", left);
	}
	else {
		printf("error,\"%s\" isn't valid", right);
	}
	return NULL;
}

void select_command(char* str) {
	funPtr fun = NULL;
	char* ch = NULL, * strright = NULL, * strleft = NULL;

	if (ch = strchr(str, '<')) {
		init_str_right_left(ch, str, &strright, &strleft);
		fun = command_smaller(strright, strleft);
	}
	else if (ch = strchr(str, '>')) {
		init_str_right_left(ch, str, &strright, &strleft);
		fun = command_larger(strright, strleft);
	}
	else if (ch = strchr(str, '=')) {
		init_str_right_left(ch, str, &strright, &strleft);
		fun = command_equal(strright, strleft);
	}
	else {
		printf("error in select command\n");
	}

	if (fun) {
		search_and_print(fun, strleft);
	}
}

int commands() {
	char buffer[300] = "";//we suppose, that300 is max characters of each command
	char* buffer2 = buffer;//we need "char* buffer2", for what returns from "trim_space"
	int success;

	while (1)
	{
		printf("\n>>");
		fgets(buffer, 300, stdin);

		if (buffer[strlen(buffer) - 1] != '\n') { //checks if line is too much long
			printError("greater than 300 characters ", 0);
			while (getc(stdin) != '\n');// ignores to the end of the line, 
			continue;
		}

		buffer2 = trim_space(buffer);

		if (!strncmp(buffer2, "select ", 7)) {
			select_command(buffer2 + 7);
		}
		else if (!strncmp(buffer2, "set ", 4)) {
			success = set_command(buffer2 + 4);
			if (success == -1)//i.e. it was error with allocation
				return success;
		}
		else if (!strcmp(buffer2, "print")) {
			printAll();
		}
		else if (!strcmp(buffer2, "quit")) {
			break;
		}
		else {
			printf("error in command \"%s\"", buffer2);
		}
	}
	return 0;
}
