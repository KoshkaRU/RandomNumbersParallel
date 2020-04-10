#include "ConsoleApplication1.h"
#include <array>
#include <numeric>
#include <random>
#include <iterator>
#include <conio.h>

using namespace std;

constexpr const int ARRAY_SIZE = 30;
constexpr const int PART_SIZE = 10;
constexpr const int RAW_COUNT = ARRAY_SIZE / PART_SIZE;
constexpr const int TRY_COUNT = 10'000'000;
constexpr const int STAR_LENGTH = 20;

using my_distribution = uniform_int_distribution<>;
using my_engine = default_random_engine;

my_engine re{}; // the default generator

void work_countinuos(array<int, ARRAY_SIZE>& values) {

		for (int i = 0; i < RAW_COUNT; ++i) {

		int start_index = i * PART_SIZE;

		int end_index = start_index + PART_SIZE - 1;

		my_distribution distr(start_index, end_index);

		for (int y = 0; y != TRY_COUNT; ++y) {

			int index = distr(re);

			++values[index];

		} // END: for

	}; // END: for
}

int main()
{

	// Заполняем частотный диапазон в 1000 чисел в 1000 проходов
	// Выводим на экран 10 столбцов с средним значением из 100 чисел каждого из 10 диапазонов

	array<int, ARRAY_SIZE> values;

	cout << endl << "\t" << "Working..." << endl << endl;

	fill(values.begin(), values.end(), 0.0);

	work_countinuos(values);

	cout << endl;

	for (int i = 0; i < RAW_COUNT; i++) {

		float average = 0.0f;

		int index_start = i * PART_SIZE;
		int index_end = (i + 1) * PART_SIZE;

		auto iter_start = values.begin() + index_start;
		auto iter_end = values.begin() + index_end;

		for (int y = index_start; y < index_end; y++) {

			cout << "\t" << setfill('0') << setw(8) << values[y] << ": ";

			float scale = TRY_COUNT / PART_SIZE / STAR_LENGTH;

			int stars_size = values[y] / scale;

			for (int c = 0; c < stars_size; c++) {

				cout << "*";

			}

			cout << endl;

		}

		cout << endl << endl;

	
	
	}

	cout << "Press any key to exit.";

	string isend;

	_getch(); // wait for keypress

} // END: main()


