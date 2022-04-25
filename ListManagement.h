#ifndef ListManagement_H

#define ListManagement_H

#include "GlobalVariablesAndDeclarations.h"

#include "Commands.h"
#include "ReadAndWriteToFile.h"


student** exist_id(char* id);
float avg(float* arr, int count);
void insert(student* item);
void freeList(student* stu);
void print_one(student* stu);
void print_title();
void printAll();
void re_insert(student** ptrptr);
int err_allocation();
int createOrUpdate(char* id, char* fname, char* lname, courses course_name, float grade);


#endif 
