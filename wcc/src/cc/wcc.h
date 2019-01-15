#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


enum{
	TID,
	TSTR,
	TNUM
	TKW,
	TTYPE,
	TSS // type syntax symbol -- '(','[',...
};


typedef struct {
	int line;
	int col;
	FILE *f;
}Location;


typedef struct{
	short int type;
	char *label;
	Location loc;
	union{
		int id; // TKW
		struct{
			char *idval;
			int idlen;
		};
		struct{ // TSTR
			char *sval;
			int slen;
		};
		struct{ // TNUM
			union{
				int64_t i64v;
				unsigned int64_t ui64v;
				int iv;
			};
		};
		int sym; // TSS
	};
}Token;

#define ast(tokname) AST_##tokname

enum{
	ast(LITERAL = 256),
	ast(LVAR),
	ast(GVAR),
	ast(FUNCALL),
	ast(FUNDEF),
	ast(FUNDEC)
};

typedef struct Node{
	int ast_kind;
	
};
