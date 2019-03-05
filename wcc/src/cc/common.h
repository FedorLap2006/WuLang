#pragma once

#include <cstdio>
#include <fstream>

struct File {
	fstream f;
	size_t curl;
	size_t curc;
	int tokc;
};