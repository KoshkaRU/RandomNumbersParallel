#include "ConsoleApplication1.h"

int main()
{

	printmyfile();

	string text = "У меня есть кружка с цикорием";

	char symbol = 'к';

	findinstring(text, symbol);

}

void findinstring(std::string& text, char symbol)
{
	bhrigutext::reset_locale();

	auto vector_of_results = find_all(text, symbol);

	cout
		<< endl
		<< "\t+-------------------------------------------------------------------------------+" << endl
		<< "\t|\tСписок вхождений символа \'" << symbol << "\'"
		<< " в строку \"" << text << "\"\t|" << endl
		<< "\t+-------------------------------------------------------------------------------+" << endl;

	if (!vector_of_results.size()) {

		cout
			<< "\t|\tНет данных\t\t\t\t\t\t\t\t|" << endl
			<< "\t+-------------------------------------------------------------------------------+" << endl;
	}
	else {

		for (auto p = vector_of_results.begin(); p != vector_of_results.end(); ++p) {
			cout
				<< "\t|\t" << p._Ptr << "\t\t\t\t\t\t\t|" << endl
				<< "\t+-------------------------------------------------------------------------------+" << endl;
		}

	}
}

/*
Print content of text file in sorted order by words
*/
void printmyfile()
{
	std::filesystem::path from;
	std::filesystem::path to;

	cin >> from;

	bhrigutext::reset_locale();

	if (!exists(from)) {

		cout << "Нет такого файла";

	}
	else {		

		cout << "Файл обнаружен" << endl << "----------------" << endl;
		
		bhrigutext::setUTF8();
		
		ifstream fs{ from };
		istream_iterator<string> isi{ fs };
		istream_iterator<string> eos{};
		vector<string> ls{ isi, eos };
		
		sort(ls.begin(), ls.end());
	
		for (auto p = ls.begin(); p != ls.end(); ++p) {
			cout << *p << endl;
		}
	}
} // END: void printmyfile()

/**
* Checks the presence of a char in the string
*/
vector<string::iterator> find_all(string& str, char  c) {

	vector<string::iterator> result;

	for (auto p = str.begin(); p != str.end(); ++p) {


		if (*p == c) {
			result.push_back(p);
		}

	}

	return result;

} // end: find_all()