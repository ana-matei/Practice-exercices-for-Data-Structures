#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union Reference {
	unsigned char intRef;
	unsigned short extRef;
};

typedef union Reference Reference;

struct Student {
	char* name;
	float income;
	Reference reference;
};

typedef struct Student Student;

Student* createStudent(char* name, float income, unsigned short ref)
{
	Student* stud = NULL;
	stud = (Student*)malloc(sizeof(Student));
	stud->name = (char*)malloc(strlen(name) + 1);
	strcpy(stud->name, name);
	stud->income = income;
	stud->reference.extRef = ref;
	return stud;
}
void printStudent(Student* stud)
{
	if (stud != NULL)
	{
		printf("Name: %s, income: %f\n", stud->name, stud->income);
		if (stud->reference.extRef >> 15 == 1)
		{
			short uid = stud->reference.extRef >> 8 & 127;
			printf("University ref: %d\n", uid);
			printf("External ref: %d\n", stud->reference.extRef & 255);
		}
		else
		{
			printf("Internal ref: %d\n", stud->reference.intRef);
		}
	}
}


void deleteStudent(Student* stud) {
	if (stud != NULL) {
		free(stud->name);
		free(stud);
	}
}