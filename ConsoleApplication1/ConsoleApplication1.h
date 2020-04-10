#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <istream>
#include <LogCatLog.h>
#include <unordered_set>
#include "TestRecord.h"
#include <LogCatLog.h>
#include <iterator>

#pragma comment(lib, "bhriguutilscpp.lib")

using namespace std;

vector<string::iterator> find_all(string& str, char  c);

void findinstring(std::string& text, char symbol);

void printmyfile();

int main();