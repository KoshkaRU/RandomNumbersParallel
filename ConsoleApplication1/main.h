#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <istream>
#include "LogCatLog.h"
#include <unordered_set>
#include "TestRecord.h"
#include <iterator>

#pragma comment(lib, "bhriguutilscpp.lib")

using namespace std;

int main();

void print_results(std::vector<int>& values);