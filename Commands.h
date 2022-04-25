#ifndef Commands_h
#define Commands_h

#include "GlobalVariablesAndDeclarations.h"

#include "ListManagement.h"
#include "ReadAndWriteToFile.h"




int set_command(char* str);
void search_and_print(funPtr condition, char* val);
void init_str_right_left(char* ch, char* str, char** right, char** left);
int fname_equal(student* stu, char* str);
int lname_equal(student* stu, char* str);
int id_equal(student* stu, char* str);
int avg_equal(student* stu, char* str);
int clang_equal(student* stu, char* str);
int ComputerNet_equal(student* stu, char* str);
int CsFund_equal(student* stu, char* str);
int avg_larger(student* stu, char* str);
int clang_larger(student* stu, char* str);
int ComputerNet_larger(student* stu, char* str);
int CsFund_larger(student* stu, char* str);
int avg_smaller(student* stu, char* str);
int clang_smaller(student* stu, char* str);
int ComputerNet_smaller(student* stu, char* str);
int CsFund_smaller(student* stu, char* str);
int is_digits(char* c);
funPtr command_smaller(char* right, char* left);
funPtr command_larger(char* right, char* left);
funPtr command_equal(char* right, char* left);
void select_command(char* str);
int commands();

#endif // !Commands_h