#include "stdio.h"
#include "string.h"
#include "stdlib.h"
//#include <iostream>

#define DATASIZE 10

typedef struct stringdata
{
	char* string;
	int iscontinuing;
	struct stringdata* next;
} mydata;

mydata* append(mydata* start, char* input);
void displaydata(mydata* start);
void freedata(mydata* start);

int main(int argc, char** argv)
{
	char input[DATASIZE];
	mydata* start = NULL;
	int  count = 0;

	printf("ENTER SOME DATA PRESS Ctrl + D WHEN DONE.\n");
	
	while (fgets(input,sizeof(input),stdin))
	{
		start = append(start, input);
		count++;
		if (count>10)
		{
			break;
		}
	}
	displaydata(start);
	freedata(start);

	return 0;
}

mydata* append(mydata* start, char* input)
{
	mydata* cur = start, * prev = NULL, *new = NULL;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
	}

	cur = prev;
	new = malloc(sizeof(mydata));
	if (!new)
	{
		printf("COULDN'T ALLOCATE MEMORY!\n");
		exit(255);
	}
	if (cur)
		cur->next = new;
	else
		start = new;
	cur = new;
	if (NULL == (cur->string = malloc(sizeof(input) + 1)))
	{
		printf("ERROR ALLOCATION MEMORY!\n");
		exit(255);
	}
	strcpy(cur->string, input);
	cur->iscontinuing = !(input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\r');
	cur->next = NULL;
	return start;
}

void displaydata(mydata* start)
{
	mydata* cur;
	int linecounter = 0, structcounter = 0;
	int newline = 1;
	cur = start;
	while (NULL != cur)
	{
		if (newline)
			printf("LINE %d:", ++linecounter);
		structcounter++;
		printf("%s", cur->string);
		newline = cur->iscontinuing;
		cur = cur->next;
	}
	printf("THE DATA COUNTAINED %d LINES AND WAS STORED IN %d STRUCTS.\n",linecounter,structcounter);
}

void freedata(mydata* start)
{
	mydata* cur, * next = NULL;
	cur = start;
	while (cur)
	{
		next = cur->next;
		free(cur->string);
		free(cur);
		cur = next;
	}
}