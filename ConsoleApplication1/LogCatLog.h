#pragma once
#include <string>
#include <iostream>
#include <fstream>

// handle_exception() - handle current exception and save the log

class LogCatLog 
{
public:
	
	LogCatLog();

	~LogCatLog();

	static void handle_exceptions(std::string description, std::exception_ptr e); // A static exception handle
	
	bool print_text_file(std::filesystem::path p);
	
	bool print_text_file(std::wstring filename);

};

namespace bhrigutext {

	void setUTF8(); // switch console to utf8	

	void reset_locale(); // reset console to defaul

}