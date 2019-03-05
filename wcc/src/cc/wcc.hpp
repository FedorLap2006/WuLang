//#pragma once
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "common.h"
#include <variant>
// #include <cstdbool>


// using namespace std;
using std::string;


#include "types.hpp"


#define nil nullptr

typedef long long int64_t;
typedef unsigned long long uint64_t;


// Lexer

class Lexer {
public:
	enum {
		TID,
		TKW,
		TNUM,
		TCH,
		TSTR,
		TEOF = -1,
		TEOL = -2
	}TokenType;
	typedef struct Token {
		File f;
		TokenType kind;
	};

	Lexer(string filename);

};


