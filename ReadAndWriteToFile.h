#ifndef ReadAndWriteToFile_h

#define ReadAndWriteToFile_h
#include "GlobalVariablesAndDeclarations.h"
#include "ListManagement.h"
#include "Commands.h"



char* trim_space(char* str);
void printError(char* err, int num_line);
char* check_id(char* id);
char* check_flname(char* fln);
int check_course_name(char* course_name);
float check_grade(char* grade);
int getLine(char* line, int num_line);
int readFile(FILE* f);
void writeFile(FILE* f);

#endif // !ReadAndWriteToFile_h