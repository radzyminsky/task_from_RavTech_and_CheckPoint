#include "ListManagement.h"


//checks if the "id" already exist 
// if yes, returns pointer to pointer to "struct student"
student** exist_id(char* id) {
	student** ptrptr = &head;

	while (*ptrptr)
	{
		if (!strcmp((*ptrptr)->id, id))
			return ptrptr;
		ptrptr = &((*ptrptr)->next);
	}
	return NULL;
}

float avg(float* arr, int count) {
	int i = 0, num_tests = 0;
	float sum = 0;

	for (;i < count;i++)
		if (arr[i] > (float)0) {
			sum += arr[i];
			num_tests++;
		}
	return sum / num_tests;
}

//inserts item to the list in suitable location
void insert(student* item) {
	student* temp = head;

	if (!head || strcmp(head->lname, item->lname) > 0) { //i.e. list is empty,or the first node larger from item
		head = item;
		item->next = temp;
		return;
	}
	while (temp->next && strcmp(temp->next->lname, item->lname) < 0)
		temp = temp->next;

	item->next = temp->next;
	temp->next = item;
}

void freeList(student* stu) {
	if (stu->next)
		freeList(stu->next);
	free(stu->lname);
	free(stu->fname);
	free(stu);
}

void print_one(student* stu) {
	char cl[6] = "", cn[6] = "", cf[6] = "";

	if (stu->courseGrade[Clang] != -1)
		sprintf(cl, "%3.1f", stu->courseGrade[Clang]);

	if (stu->courseGrade[ComputerNet] != -1)
		sprintf(cn, "%3.1f", stu->courseGrade[ComputerNet]);

	if (stu->courseGrade[CsFund] != -1)
		sprintf(cf, "%3.1f", stu->courseGrade[CsFund]);

	printf("%-20s|%-20s|%-20s|%-20s|%-20s|%-20.1f\n",
		stu->fname, stu->lname, cl, cn, cf, stu->avg);
}

void print_title() {

	printf("%-20s|%-20s|%-20s|%-20s|%-20s|%-20s\n",
		"first name ", "second name", "C lang", "Computer Networks", "CS Fundamentals", "Average");
}

void printAll() {
	print_title();
	student* temp = head;
	while (temp) {
		print_one(temp);
		temp = temp->next;
	}
}

//First, we remove the updated node from the list (of course, we need save the its pointed),
// then we send it to the "insert" function to put it in its suitable place
void re_insert(student** ptrptr) {
	student* temp = *ptrptr;
	(*ptrptr) = (*ptrptr)->next;
	insert(temp);
}

int err_allocation() {
	freeList(head);
	printf("error in memory allocation \n");
	return FAILURE;
}

int createOrUpdate(char* id, char* fname, char* lname, courses course_name, float grade) {
	student* student_p;
	student** ptr_to_student_p;//i need this for a value that returned from "exist_id" func.
	char* fn, * ln;
	int i, need_re_insert = 0;

	//checks if already exist this id, if does, we just update details
	if (ptr_to_student_p = exist_id(id)) {

		//update details
//--------------------------------------//

		 //checks if "last name" was changed then we need to re insert, also we need to allocate memmory to the new "lname"
		if (strcmp((*ptr_to_student_p)->lname, lname)) {
			need_re_insert = 1;
			ln = (char*)realloc((*ptr_to_student_p)->lname, strlen(lname) + 1);
			if (!ln)
				return err_allocation();
			(*ptr_to_student_p)->lname = ln;
			strcpy((*ptr_to_student_p)->lname, lname);
		}

		//checks if "fname" changed, then we need to allocate memmory to the new "fname"  
		if (strcmp((*ptr_to_student_p)->fname, fname)) {
			fn = (char*)realloc((*ptr_to_student_p)->fname, strlen(fname) + 1);
			if (!fn)
				return err_allocation();
			(*ptr_to_student_p)->fname = fn;
			strcpy((*ptr_to_student_p)->fname, fname);
		}

		(*ptr_to_student_p)->courseGrade[course_name] = grade;
		(*ptr_to_student_p)->avg = avg((*ptr_to_student_p)->courseGrade, 3);

		if (need_re_insert)
			re_insert(ptr_to_student_p);//because now maybe the list isn't sort correct
		return 0;
	}
	// if not exist, we need to create new one
	student_p = malloc(sizeof(student));
	if (!student_p)
		return err_allocation();

	strcpy(student_p->id, id);
	fn = (char*)malloc(strlen(fname) + 1);
	ln = (char*)malloc(strlen(lname) + 1);
	if (!fn || !ln)
		return err_allocation();
	student_p->fname = fn;
	student_p->lname = ln;

	strcpy(student_p->fname, fname);
	strcpy(student_p->lname, lname);

	//firstly, we initialize items in array "courseGrade" to -1, then, we insert grade in suitable location 
	for (i = 0;i < 3;i++)
		student_p->courseGrade[i] = -1;
	student_p->courseGrade[course_name] = grade;
	student_p->avg = avg(student_p->courseGrade, 3);
	insert(student_p);
	return 0;
}
