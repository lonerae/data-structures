#include <stdio.h>
#include <string.h>

struct subjectNode {
	char subject[50];
	struct student *ptr;

	struct subjectNode *next;
};

struct subjectNode *head;

void addSubject(struct student *studentPtr) {
	if (head == NULL) {
		struct subjectNode *newSubjectPtr;
		strcpy(newSubjectPtr->subject,studentPtr->subject);
		newSubjectPtr->ptr = studentPtr;

		newSubjectPtr->next = NULL;
		head = newSubjectPtr;
	} 

}

int subjectExists(char *subject[50]) {
	struct subjectNode *temp;
	temp = head;

	if (temp == NULL) {
		return 1;
	} else {
		if (strcmp(temp->subject,subject) == 0) {
			return 1;
		}
	}
	return 0;
}

struct student {
	char id[9];
	char firstName[20];
	char lastName[20];
	char city[20];
	int age;
	char subject[50];
};

struct student studentArray[3];

void readStudent(struct student *s1) {
	printf("===Student with id %s===\n",s1->id);
	printf("Name: %s\nSurname: %s\nCity: %s\nAge: %d\nSubject: %s\n",s1->firstName,s1->lastName,s1->city,s1->age,s1->subject);
	printf("\n");
	return;
}

void readAllStudents() {
	for (int i=0; i<3; i++) {
		readStudent(studentArray + i);
	}
}

int main() {
	struct student s1;	
	strcpy(s1.id,"mppl2204");
	strcpy(s1.firstName,"Minas");
	strcpy(s1.lastName,"Alvertis");
	strcpy(s1.city,"Glifada");
	s1.age = 26;
	strcpy(s1.subject,"Logic Programming");
	addSubject(s1);

	struct student s2;	
	strcpy(s2.id,"mppl2205");
	strcpy(s2.firstName,"John");
	strcpy(s2.lastName,"Doe");
	strcpy(s2.city,"Peristeri");
	s2.age = 20;
	strcpy(s2.subject,"Logic Programming");
	addSubject(s2);

	struct student s3;	
	strcpy(s3.id,"mppl2206");
	strcpy(s3.firstName,"Mary");
	strcpy(s3.lastName,"Christmas");
	strcpy(s3.city,"Koropi");
	s3.age = 24;
	strcpy(s3.subject,"Discrete Maths");
	addSubject(s3);

	studentArray[0] = s1;
	studentArray[1] = s2;
	studentArray[2] = s3;
	
	readAllStudents();
	return 0;
}
