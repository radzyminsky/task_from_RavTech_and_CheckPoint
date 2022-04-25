#ifndef Global_h
#define Global_h

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define SUCCESS 0
#define FAILURE -1
#define MISTAKE 1

typedef enum { Clang, CsFund, ComputerNet } courses;

typedef enum { IDinput = 1, FNAMEinput, LNAMEinput, COURSEinput, GRADEinput } inputs;

typedef struct student {
	float courseGrade[3];//for each cell that its value <0, so, student hasn't course that its index suitable to "enum"
	float avg;
	char* fname, * lname, id[10];
	struct student* next;
}student;

typedef int (*funPtr)(student* stu, char* str);

extern student* head;
extern char* courses_name[];

#endif // !Global_h
