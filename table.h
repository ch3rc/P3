//==============================================================
//Date:		April 5,2020
//Author:	Cody Hawkins
//Class:	CS4280
//Project:	P1
//File:		table.h
//==============================================================

#ifndef TABLE_H
#define TABLE_H
#include "token.h"

extern int lineCount;
extern FILE *file;

enum State{
	START_st,
	ID_st,
	NUM_st,
	FIN_ID_st = 1000,
	FIN_NUM_ST = 1001,
	EOF_st = -1,
	ERROR_st = -2,
};

int tableLookup(enum State, char );
int getSpecial(char);
#endif
