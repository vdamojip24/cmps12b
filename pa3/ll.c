# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include "ll.h"//includes header file

//variables for statistics and flag
extern bool moveToFront;
extern uint32_t seeks;
extern uint32_t attemptToFind;

typedef struct listNode listNode ;
//int counter = 0;

//creates a new node, allocates memory, and sets the words
listNode *newNode ( const char *bad , const char *good)
{
	listNode *node = malloc(sizeof(listNode));
	node->oldspeak = calloc(strlen(bad) + 1, sizeof(char));
    strcpy(node->oldspeak, bad);
	node->newspeak = calloc(strlen(good) + 1, sizeof(char));
    strcpy(node->newspeak, good);

	return node; 
}

//deletes node and frees up memory
void delNode(listNode *current)
{
	free(current->oldspeak);
	free(current->newspeak);
	free(current);
	current->oldspeak = NULL;
	current->newspeak = NULL;
	current = NULL;
}

//deletes the entire linked list starting from the first node
void delLL ( listNode *current)
{
	while(current != NULL)
	{
		listNode *temp = current;
		delNode(temp);
		current = current->next;
	}
	free(current);
}

//inserts a node to the front of the linked list
listNode * insertLL(listNode **linkedList , const char *bad , const char *good)
{
	listNode *new = newNode(bad, good);
	new->next = *linkedList;
	*linkedList = new;
	return new;
}

//finds the node inside the linked list
listNode * findLL(listNode **linkedList , const char *bad)
{
	listNode *node;
    
    attemptToFind++;//increments for the statistics

	for(node = *linkedList; node != NULL; node = node->next)//increments through nodes
	{
        seeks++;
		if(strcmp(bad, node->oldspeak)==0)
		{
			if((moveToFront == true) && (node != *linkedList))
			{
				//counter++;
				listNode *temp = node;
				insertLL(linkedList,node->oldspeak,node->newspeak);
				node->next = node->next->next;
				delNode(temp->next);
			}
			return node;
		}
	}
	return NULL;
}
//prints the current node that contains the old word and new word
void printLL ( listNode *current)
{
    while (current != NULL)	
	{
		printf("oldSpeak = %s newSpeak = %s \n", current->oldspeak, current->newspeak); 
		current = current->next;
	}
	
}
