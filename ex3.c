#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct subjectNode {
	char subject[50];
	struct student *firstStudentPtr;

	struct subjectNode *next;
};

struct subjectNode *head;

struct student {
	char id[9];
	char firstName[20];
	char lastName[20];
	char city[20];
	int age;
	char subject[50];
	
	struct student *next;
};

struct student *studentArray[10];

/**
* Checks whether a subject is already inserted
* in the subjects linked list.
*
* Parameters
* 	subject - name of the subject to-be-added
*/
struct subjectNode *subjectExists(char subject[]) {
	struct subjectNode *subjectPtr = head;
	while (subjectPtr != NULL) {
		if (strcmp(subjectPtr->subject,subject) == 0) {
			return subjectPtr;
		}
		subjectPtr = subjectPtr->next;
	}
	return NULL;
}

/**
* Adds a student to the linked list of a
* subject's student list.
*
* Parameters
* 	studentPtr - pointer to the student to-be-added
*/
void addStudentToSubject(struct student *studentPtr) {
	struct subjectNode *p = subjectExists(studentPtr->subject);
	if (p == NULL) {
		struct subjectNode *newSubjectPtr = (struct subjectNode*) malloc(sizeof(struct subjectNode));
		strcpy(newSubjectPtr->subject,studentPtr->subject);
		newSubjectPtr->firstStudentPtr = studentPtr;
		newSubjectPtr->next = head;
		head = newSubjectPtr;
	} else {
		struct student *studentAttendingSubjectPtr = p->firstStudentPtr;
		while (studentAttendingSubjectPtr->next != NULL) {
			studentAttendingSubjectPtr = studentAttendingSubjectPtr->next;
		}
		studentAttendingSubjectPtr->next = studentPtr;
	}
}

/**
* Prints a student's information.
*
* Parameters
* 	studentPtr - pointer to the student to-be-printed
*/
void readStudent(struct student *studentPtr) {
	printf("===Student with id %s===\n",studentPtr->id);
	printf("Name: %s\nSurname: %s\nCity: %s\nAge: %d\nSubject: %s\n",studentPtr->firstName,studentPtr->lastName,studentPtr->city,studentPtr->age,studentPtr->subject);
	printf("\n");
	return;
}

/**
* Prints the information of all students.
*/
void readAllStudents() {
	printf("***All Students***\n\n");
	for (int i=0; i<10; i++) {
		if (*(studentArray + i) == NULL) {
			break;
		}
		readStudent(*(studentArray + i));
	}
}

/**
* Given the name of a subject, prints the information of all students studying it.
* In case the subject doesn't exist, informs the user accordingly.
*
* Parameters
* 	subject - name of the subject
*/
void readStudentsBySubject(char subject[]) {
	struct subjectNode *subjectPtr = subjectExists(subject);
	
	if (subjectPtr == NULL) {
		printf("***Subject Does Not Exist***\n\n");
		return;
	}
	printf("***%s***\n\n",subject);
	
	struct student *studentPtr = subjectPtr->firstStudentPtr;
	while (studentPtr != NULL) {
		readStudent(studentPtr);
		studentPtr = studentPtr->next;
	}
}

/* Initial Data Dump */
void insertData() {
	struct student *s1 = (struct student*) malloc(sizeof(struct student));	
	strcpy(s1->id,"mppl2204");
	strcpy(s1->firstName,"Minas");
	strcpy(s1->lastName,"Alvertis");
	strcpy(s1->city,"Glifada");
	s1->age = 26;
	strcpy(s1->subject,"Logic Programming");
	addStudentToSubject(s1);
	studentArray[0] = s1;
	
	struct student *s2 = (struct student*) malloc(sizeof(struct student));	
	strcpy(s2->id,"mppl2205");
	strcpy(s2->firstName,"John");
	strcpy(s2->lastName,"Doe");
	strcpy(s2->city,"Peristeri");
	s2->age = 20;
	strcpy(s2->subject,"Logic Programming");
	addStudentToSubject(s2);
	studentArray[1] = s2;
	
	struct student *s3 = (struct student*) malloc(sizeof(struct student));	
	strcpy(s3->id,"mppl2206");
	strcpy(s3->firstName,"Mary");
	strcpy(s3->lastName,"Christmas");
	strcpy(s3->city,"Koropi");
	s3->age = 24;
	strcpy(s3->subject,"Discrete Maths");
	addStudentToSubject(s3);
	studentArray[2] = s3;
}

int main() {
	insertData();
		
	readAllStudents();
	
	readStudentsBySubject("Logic Programming");
	readStudentsBySubject("Discrete Maths");
	readStudentsBySubject("Graphs");
	
	return 0;
}
