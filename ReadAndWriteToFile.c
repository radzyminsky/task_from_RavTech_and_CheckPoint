#include "ReadAndWriteToFile.h"



//trim spaces from start string, and '\n', spaces from end string
char* trim_space(char* str) {
	int i = 0;

	while (str[i] && (str[i] == ' ' || str[i] == '\t')) {
		str++;
	}
	i = strlen(str) - 1;
	while (i > 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')) {
		str[i] = '\0';
		i--;
	}
	return str;
}

//func that print  errors
void printError(char* err, int num_line) {
	if (num_line)
		printf("%s in line: %d\n", err, num_line);
	else
		printf("%s\n", err);
}

char* check_id(char* id) {
	int i;

	id = trim_space(id);
	if (strlen(id) > 9)
		return NULL;
	for (i = 0;i < 9;i++)
		if (id[i] < '0' || id[i]>'9')
			return NULL;
	return id;
}
char* check_flname(char* fln) {
	int i, len;

	fln = trim_space(fln);
	if (!(len = strlen(fln)))//taht is, fln is empty
		return NULL;
	for (i = 0;i < len;i++)
		if (fln[i] < 'A' || fln[i]>'z')
			return NULL;
	return fln;
}

//this function checks pramater "course_name" if is suitable to enum,
//if is, it returns number of enum otherwise returns -1
int check_course_name(char* course_name) {
	int i;

	course_name = trim_space(course_name);
	for (i = 0;i < 3;i++)
		if (!strcmp(course_name, courses_name[i])) {
			return i;
		}
	return -1;
}

//this function checks validity of parameter "grade" 
//if isn't, returns -1
float check_grade(char* grade) {
	float f;
	int i, len;

	grade = trim_space(grade);
	len = strlen(grade);
	for (i = 0;i < len;i++)
		if ((grade[i] < '0' || grade[i]>'9') && grade[i] != '.')
			return -1;
	f = (float)atof(grade);
	if (f >= 0 && f <= 100)
		return f;
	return -1;
}

//this func get one line (string),and number of line while "readFile" func calls it,
//if "commands" func calls, "num_line"=0
//function returns 0 on success, 1 on data mistake, -1 on memory allocation error
int getLine(char* line, int num_line) {
	int i = 1, success;
	float grade;
	char* temp, fname[20] = "", lname[20] = "", id[10] = "";
	courses	cour_name;

	temp = strtok(line, ",\n");
	while (temp)
	{
		switch (i)
		{
		case IDinput:
			if (temp = check_id(temp)) {
				strncpy(id, temp, 9);
				break;
			}
			printError("error in id", num_line);
			return MISTAKE;
		case FNAMEinput:
			if (temp = check_flname(temp)) {
				strncpy(fname, temp, 19);
				break;
			}
			printError("error in first name", num_line);
			return MISTAKE;
		case LNAMEinput:
			if (temp = check_flname(temp)) {
				strncpy(lname, temp, 19);
				break;
			}
			printError("error in last name", num_line);
			return MISTAKE;
		case COURSEinput:
			if ((cour_name = check_course_name(temp)) != -1)
				break;
			printError("error in cours name", num_line);
			return MISTAKE;
		case GRADEinput:
			if ((grade = check_grade(temp)) >= 0) {
				break;
			}
			printError("error in grade", num_line);
			return MISTAKE;
		default:
			printError("ERROR! it has too much data", num_line);
			return MISTAKE;
		}

		temp = strtok(NULL, ",\n");
		i++;
	}
	if (i < 6) {//that is, it has few data
		printError("Error! Missing data ", num_line);
		return MISTAKE;
	}
	success = createOrUpdate(id, fname, lname, cour_name, grade);
	if (success)
		return FAILURE;
	return SUCCESS;
}

int readFile(FILE* f) {
	int num_line = 1, success;
	char buffer[200] = "";//we suppose, that 200 is max characters of each line 

	fgets(buffer, 200, f);//ignores from high line

	while (fgets(buffer, 200, f))
	{
		if (buffer[strlen(buffer) - 1] != '\n') { //checks if line is too much long
			printError("greater than 200 characters ", num_line);
			while (fgetc(f) != '\n');// ignores to the end of the line, 
			num_line++;
			continue;
		}
		success = getLine(buffer, num_line);
		if (success == MISTAKE)
			printf("line %d isn't insert\n", num_line);
		if (success == FAILURE)
			return FAILURE;
		num_line++;
	}
	return SUCCESS;
}

void writeFile(FILE* f) {
	student* current = head;
	int i;

	rewind(f);
	fprintf(f, "ID,First Name,Second Name,Course Name,Grade\n");//print title
	while (current)
	{
		for (i = 0;i < 3;i++)
			if (current->courseGrade[i] > -1)
				fprintf(f, "%s,%s,%s,%s,%f\n", current->id, current->fname, current->lname, courses_name[i], current->courseGrade[i]);

		current = current->next;
	}
}