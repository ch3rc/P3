//==========================================================
//Date:		Apr 24,2020
//Author:	Cody Hawkins
//Class:	CS4280
//Project:	P2
//File:		parseTree.c
//==========================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "node.h"

//added memory to word tokens and things started working
struct Node *newNode(char* token)
{
	struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
	temp->token = (char*)malloc(sizeof(token) + 1);
	strcpy(temp->token, token);
	temp->size = 0;
	temp->child = NULL;
	return temp;
}

//increase the size of the parent node for each additional child that attaches
//to it
void getNode(struct Node* parent, struct Node* child)
{
	struct Node *temp = newNode("");

	temp->child = (struct Node*)malloc(sizeof(struct Node) * (parent->size + 1));
	int i;
	for(i = 0; i < parent->size; i++)
	{
		temp->child[i] = parent->child[i];
	}

	temp->child[parent->size] = *child;
	parent->child = temp->child;
	parent->size++;
}

//print out all parents and children
void preOrder(struct Node *root, int level)
{
	if(root->token != NULL)
	{
		printf("%*c%s\n", level * 2, ' ', root->token);
		
		int i;
		for(i = 0; i < root->size; i++)
		{
			preOrder(&root->child[i], level + 1);
		}
	}

}
