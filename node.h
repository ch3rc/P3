//======================================================
//Date:		Apr 24,2020
//Author:	Cody Hawkins
//Class:	CS4280
//Project:	P2
//File:		node.h
//======================================================

#ifndef NODE_H
#define NODE_H

struct Node{

	struct Node* child;
	char* token;
	int size;
};

struct Node *newNode(char*);
void getToken(struct Node*, struct Node*);
void preOrder(struct Node*, int);

#endif
