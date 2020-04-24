//============================================================
//Date:		Apr 21,2020
//Author:	Cody Hawkins
//Class:	CS4280
//Project:	P2
//File:		parser.c
//============================================================

#include "parser.h"

Token *tk = NULL;

void parser()
{
	tk = fsa_driver();
	printf("<Program>\n");
	vars();
	block();
	if(tk->id == EOF_tk)
	{
		return printf("Reached end of file\n");
	}
	else
	{
		printf("Tk received, encountered EOF error\n");
		free(tk);
		exit(1);
	}
}

void vars()
{
	printf("<vars> ");
	if(tk->id == KW_tk && strcmp(tk->string, "declare") == 0)
	{
		printf("%s ", tk->string);
		tk = fsa_driver();
		if(tk->id == ID_tk)
		{
			printf("%s ", tk->string);
			tk = fsa_driver();
			if(tk->id == OP_tk && strcmp(tk->string, ":=") == 0)
			{
				printf("%s ", tk->string);
				tk = fsa_driver();
				if(tk->id == NUM_tk)
				{
					printf("%s ", tk->string);
					tk = fsa_driver();
					if(tk->id == OP_tk && strcmp(tk->string, ";") == 0)
					{
						printf("%s \n", tk->string);
						tk = fsa_driver();
						vars();
						return;
					}
				}
			}
		}
	}
	else
	{
		printf("EMPTY\n");
	}
	return;
}

void block()
{
	printf("<block> ");
	if(tk->id == OP_tk && strcmp(tk->string, "{") == 0)
	{
		printf("%s\n", tk->string);
		tk = fsa_driver();
		vars();
		stats();
		if(tk->id == OP_tk && strcmp(tk->string, "}") == 0)
		{
			printf("<block> %s\n", tk->string);
			tk = fsa_driver();
			return;
		}
	}
}

void expr()
{
	printf("<expr>\n");
	if(tk->id == OP_tk || tk->id == ID_tk || tk->id == NUM_tk)
	{
		N();
		if(tk->id == OP_tk && strcmp(tk->string, "-") == 0)
		{
			printf("%s ", tk->string);
			tk = fsa_driver();
			expr();
			return;
		}
		else if(tk->id != OP_tk)
		{
			printf("THIS IS A TEST %s\n", tk->string);
			return;
		}
		return;
	}
	else
	{
		printf("None of these tokens work %s\n", tk->string);
		return;
	}
}

void N()
{

	printf("<N>\n");
	if(tk->id == OP_tk || tk->id == ID_tk || tk->id == NUM_tk)
	{
		A();
		if(tk->id == OP_tk && strcmp(tk->string, "/") == 0)
		{
			printf("%s ",tk->string);
			tk = fsa_driver();
			N();
			return;
		}

		else if(tk->id == OP_tk && strcmp(tk->string, "+") == 0)
		{
			printf("%s ", tk->string);
			tk = fsa_driver();
			N();
			return;
		}
		return;
	}
	else
	{
		printf("None of the tokens worked %s\n", tk->string);
		return;
	}
}

void A()
{
	printf("<A>\n");
	if(tk->id == OP_tk || tk->id == ID_tk || tk->id == NUM_tk)
	{
		M();
		if(tk->id == OP_tk && strcmp(tk->string, "+") == 0)
		{
			printf("%s ", tk->string);
			tk = fsa_driver();
			A();
			return;
		}
		return;
	}
	else
	{
		printf("Not in the tokens %s\n", tk->string);
		return;
	}

}


void M()
{
	printf("<M>\n");
	if(tk->id == OP_tk && strcmp(tk->string, "*") == 0)
	{
		printf("%s\n", tk->string);
		tk = fsa_driver();
		M();
		return;
	}
	
	if(tk->id == OP_tk && strcmp(tk->string, "(") == 0 || tk->id == ID_tk || tk->id == NUM_tk)
	{
		R();
		return;
	}
	else
	{
		printf("All dems tokens was wrong %s\n", tk->string);
		return;
	}
	return;
}


void R()
{
	printf("<R> ");
	if(tk->id == OP_tk && strcmp(tk->string, "(") == 0)
	{
		printf("%s ", tk->string);
		tk = fsa_driver();
		expr();
		if(tk->id == OP_tk && strcmp(tk->string, ")") == 0)
		{
			printf("%s\n",tk->string);
			tk = fsa_driver();
			return;
		}
		else
		{
			printf("OP token not closing parentheses %s\n", tk->string);
			return;
		}
	}

	if(tk->id == ID_tk)
	{
		printf("%s\n", tk->string);
		tk = fsa_driver();
		return;
	}

	if(tk->id == NUM_tk)
	{
		printf("%s\n", tk->string);
		tk = fsa_driver();
		return;
	}
}

void stats()
{
	printf("<stats>\n");
	stat();
	mStat();
	return;
}

void mStat()
{
	printf("<mStat>\n");
	if(tk->id == KW_tk)
	{
		stat();
		mStat();
		return;
	}
	else
	{
		printf("EMPTY\n");
		return;
	}
}

void stat()
{
	printf("<stat>\n");
	if(tk->id == KW_tk && strcmp(tk->string, "in") == 0)
	{	
		in();
		return;
	}
	else if(tk->id == KW_tk && strcmp(tk->string, "out") == 0)
	{
		out();
		return;
	}
	else if(tk->id == OP_tk && strcmp(tk->string, "}") == 0 || tk->id == OP_tk && strcmp(tk->string, "{") == 0)
	{
		block();
		return;
	}
	else if(tk->id == KW_tk && strcmp(tk->string, "iffy") == 0)
	{
		iffy();
		return;
	}
	else if(tk->id == KW_tk && strcmp(tk->string, "loop") == 0)
	{
		loop();
		return;
	}
	else if(tk->id == ID_tk)
	{
		assign();
		return;
	}
	else if(tk->id == KW_tk && strcmp(tk->string, "goto") == 0)
	{
		Goto();
		return;
	}
	else if(tk->id == KW_tk && strcmp(tk->string, "label") == 0)
	{
		label();
		return;
	}
	else
	{
		return printf("Error: no match %s\n", tk->string);
	}
}

void in()
{

	printf("<in> ");
	if(tk->id == KW_tk && strcmp(tk->string, "in") == 0)
	{
		printf("in ");
		tk = fsa_driver();
		if(tk->id == ID_tk)
		{
			printf("%s\n", tk->string);
			tk = fsa_driver();
			if(tk->id == OP_tk && strcmp(tk->string, ";") == 0)
			{
				printf("%s\n", tk->string);
				tk = fsa_driver();
				return;
			}
		}
		else
		{
			printf("Not an identifier %s\n", tk->string);
			return;
		}
	}
	else
	{
		printf("Incorrect keyword not IN %s\n", tk->string);
		return;
	}

}

void out()
{	
	printf("<out> ");
	if(tk->id == KW_tk && strcmp(tk->string, "out") == 0)
	{
		printf("out ");
		tk = fsa_driver();
		expr();
		if(tk->id == OP_tk && strcmp(tk->string, ";") == 0)
		{
			printf("%s\n", tk->string);
			tk = fsa_driver();
			return;
		}
	}
	else
	{
		printf("Keyword token not OUT %s\n", tk->string);
		return;
	}
}

void iffy()
{
	printf("<if> ");
	if(tk->id == KW_tk && strcmp(tk->string, "iffy") == 0)
	{
		printf("iffy ");
		tk = fsa_driver();
		if(tk->id == OP_tk && strcmp(tk->string, "[") == 0)
		{ 
			printf("%s ", tk->string);
			tk = fsa_driver();
			expr();
			RO();
			expr();
			if(tk->id == OP_tk && strcmp(tk->string, "]") == 0)
			{
				printf("%s ", tk->string);
				tk = fsa_driver();
				if(tk->id == KW_tk && strcmp(tk->string, "then") == 0)
				{
					printf("%s\n", tk->string);
					tk = fsa_driver();
					stat();
					if(tk->id == OP_tk && strcmp(tk->string, ";") == 0)
					{
						printf("%s\n", tk->string);
						tk = fsa_driver();
						return;
					}
				}
				else
				{
					printf("Keyword not THEN %s\n", tk->string);
					return;
				}
			}
			else
			{
				printf("OP token not closing brace %s\n", tk->string);
				return;
			}
		}
		else
		{
			printf("OP tken not opening brace %s\n", tk->string);
			return;
		}
	}
	else
	{
		printf("Keyword token not IFFY %s\n", tk->string);
		return;
	}
}

void loop()
{
	printf("<loop> ");
	if(tk->id == KW_tk && strcmp(tk->string, "loop") == 0)
	{
		printf("loop ");
		tk = fsa_driver();
		if(tk->id == OP_tk && strcmp(tk->string, "[") == 0)
		{
			printf("%s ", tk->string);
			tk = fsa_driver();
			expr();
			RO();
			expr();
			if(tk->id == OP_tk && strcmp(tk->string, "]") == 0)
			{
				printf("%s ", tk->string);
				tk = fsa_driver();
				stat();
				if(tk->id == OP_tk && strcmp(tk->string, ";") == 0)
				{
					printf("%s\n", tk->string);
					tk = fsa_driver();
					return;
				}
			}
			else
			{
				printf("Incorrect closing brace %s\n", tk->string);
				return;
			}
		}
		else
		{
			printf("incorrect opening bracket %s\n", tk->string);
			return;
		}
	}
	else
	{
		printf("Incorrect keyword for loop %s\n", tk->string);
		return;
	}
}

void assign()
{
	printf("<assign> ");
	if(tk->id == ID_tk)
	{
		printf("%s ", tk->string);
		tk = fsa_driver();
		if(tk->id == OP_tk && strcmp(tk->string, ":=") == 0)
		{
			printf("%s ", tk->string);
			tk = fsa_driver();
			expr();
			if(tk->id == OP_tk && strcmp(tk->string, ";") == 0)
			{
				printf("%s\n", tk->string);
				tk = fsa_driver();
				return;
			}
		}
		else
		{
			printf("incorrect token arrangement %s\n", tk->string);
			return;
		}
	}
	else
	{
		printf("Not an ID token %s\n", tk->string);
		return;
	}
}

void label()
{
	printf("<label> ");
	if(tk->id == KW_tk && strcmp(tk->string, "label") == 0)
	{
		printf("label ");
		tk = fsa_driver();
		if(tk->id == ID_tk)
		{
			printf("%s\n", tk->string);
			tk = fsa_driver();
			if(tk->id == OP_tk && strcmp(tk->string, ";") == 0)
			{
				printf("%s\n", tk->string);
				tk = fsa_driver();
				return;
			}
		}
	}
	else
	{
		printf("Error: incorrect keyword %s\n", tk->string);
		return;
	}
}

void Goto()
{
	printf("<goto> ");
	if(tk->id == KW_tk && strcmp(tk->string, "goto") == 0)
	{
		printf("in ");
		tk = fsa_driver();
		if(tk->id == ID_tk)
		{
			printf("%s\n", tk->string);
			tk = fsa_driver();
			if(tk->id == OP_tk && strcmp(tk->string, ";") == 0)
			{
				printf("%s\n", tk->string);
				tk = fsa_driver();
				return;
			}
		}
	}
	else
	{
		printf("incorrect keyword %s\n", tk->string);
		return;
	}
}

void RO()
{
	printf("<RO> ");
	if(tk->id == OP_tk && strcmp(tk->string, "<") == 0)
	{
		printf("%s",tk->string);
		tk = fsa_driver();
		if(tk->id == OP_tk && strcmp(tk->string, "<") == 0 || tk->id == OP_tk && strcmp(tk->string, ">") == 0)
		{
			//double <<
			printf("%s\n", tk->string);
			tk = fsa_driver();
			return;
		}
		else
		{
			//single <
			return;
		}
	}
	else if(tk->id == OP_tk && strcmp(tk->string, ">") == 0)
	{
		printf("%s", tk->string);
		tk = fsa_driver();
		if(tk->id == OP_tk && strcmp(tk->string, ">") == 0)
		{
			//double >>
			printf("%s\n", tk->string);
			tk = fsa_driver();
			return;
		}
		else
		{
			//single >
			return; 
		}
	}
	else if(tk->id == OP_tk && strcmp(tk->string, "==") == 0)
	{
		//double == 
		printf("%s\n", tk->string);
		tk = fsa_driver();
		return;
	}
	else 
	{
		//single =
		printf("%s\n", tk->string);
		tk = fsa_driver();
		return;
	}
}
