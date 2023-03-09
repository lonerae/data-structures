#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct subjectNode {
	char subject[50];
	struct student *firstStudentPtr;

	struct subjectNode *next;
}
subjectNode;

subjectNode *head;

typedef struct student {
	char id[9];
	char firstName[20];
	char lastName[20];
	char city[20];
	int age;
	char subject[50];
	
	struct student *next;
}
student;

student *studentArray[3];

subjectNode *subjectExists(char subject[]);
void addStudentToSubject(student *studentPtr);
void readStudent(student *studentPtr);
void readAllStudents();
void readStudentsBySubject(char subject[]);
void insertData();

int main() {
	insertData();
		
	readAllStudents();
	
	readStudentsBySubject("Logic Programming");
	readStudentsBySubject("Discrete Maths");
	readStudentsBySubject("Graphs");
	
	return 0;
}

/* Initial Data Dump */
void insertData() {
	student *s1 = (student*) malloc(sizeof(student));	
	strcpy(s1->id,"mppl3000");
	strcpy(s1->firstName,"Nick");
	strcpy(s1->lastName,"Drake");
	strcpy(s1->city,"London");
	s1->age = 26;
	strcpy(s1->subject,"Logic Programming");
	addStudentToSubject(s1);
	studentArray[0] = s1;
	
	student *s2 = (student*) malloc(sizeof(student));	
	strcpy(s2->id,"mppl3001");
	strcpy(s2->firstName,"John");
	strcpy(s2->lastName,"Doe");
	strcpy(s2->city,"Peristeri");
	s2->age = 20;
	strcpy(s2->subject,"Logic Programming");
	addStudentToSubject(s2);
	studentArray[1] = s2;
	
	student *s3 = (student*) malloc(sizeof(student));	
	strcpy(s3->id,"mppl3002");
	strcpy(s3->firstName,"Mary");
	strcpy(s3->lastName,"Christmas");
	strcpy(s3->city,"Koropi");
	s3->age = 24;
	strcpy(s3->subject,"Discrete Maths");
	addStudentToSubject(s3);
	studentArray[2] = s3;
}

void readAllStudents() {
	printf("***All Students***\n\n");
	for (int i=0; i<10; i++) {
		if (*(studentArray + i) == NULL) {
			break;
		}
		readStudent(*(studentArray + i));
	}
}

void readStudent(student *studentPtr) {
	printf("===Student with id %s===\n",studentPtr->id);
	printf("Name: %s\nSurname: %s\nCity: %s\nAge: %d\nSubject: %s\n",studentPtr->firstName,studentPtr->lastName,studentPtr->city,studentPtr->age,studentPtr->subject);
	printf("\n");
	return;
}

/**
* Checks whether a subject is already inserted
* in the subjects linked list.
*
* Parameters
* 	subject - name of the subject to-be-added
*/
subjectNode *subjectExists(char subject[]) {
	subjectNode *subjectPtr = head;
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
void addStudentToSubject(student *studentPtr) {
	subjectNode *p = subjectExists(studentPtr->subject);
	if (p == NULL) {
		subjectNode *newSubjectPtr = (subjectNode*) malloc(sizeof(subjectNode));
		strcpy(newSubjectPtr->subject,studentPtr->subject);
		newSubjectPtr->firstStudentPtr = studentPtr;
		newSubjectPtr->next = head;
		head = newSubjectPtr;
	} else {
		student *studentAttendingSubjectPtr = p->firstStudentPtr;
		while (studentAttendingSubjectPtr->next != NULL) {
			studentAttendingSubjectPtr = studentAttendingSubjectPtr->next;
		}
		studentAttendingSubjectPtr->next = studentPtr;
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
	subjectNode *subjectPtr = subjectExists(subject);
	
	if (subjectPtr == NULL) {
		printf("***Subject Does Not Exist***\n\n");
		return;
	}
	printf("***%s***\n\n",subject);
	
	student *studentPtr = subjectPtr->firstStudentPtr;
	while (studentPtr != NULL) {
		readStudent(studentPtr);
		studentPtr = studentPtr->next;
	}
}
