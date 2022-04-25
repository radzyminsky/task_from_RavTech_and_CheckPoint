#include "GlobalVariablesAndDeclarations.h"
#include "ListManagement.h"
#include "Commands.h"
#include "ReadAndWriteToFile.h"

//global string array for courses name
char* courses_name[] = {
	[Clang] = "C lang",
	[CsFund] = "CS Fundamentals",
	[ComputerNet] = "Computer Networks"
};

//global pointer to list
student* head = NULL;

int main(int argc, char* argv[]) {
	int success;
	FILE* f;
	char* file_name = "taskRavatech2.csv";//Default file name, (it should appear in the same folder of the program)

	if (argc > 1)//that if user inserts pass name of .csv file
		file_name = argv[1];

	if (!(f = fopen(file_name, "r+"))) {
		printf("error in open file");
		return FAILURE;
	}

	success = readFile(f);
	if (success == -1)
		return FAILURE;
	printAll();
	commands();

	writeFile(f);
	fclose(f);

	freeList(head);

	return SUCCESS;

}
