#include "ConsoleApplication1.h"
#include <array>
#include <numeric>
#include <random>
#include <iterator>
#include <conio.h>
#include <thread>
#include <mutex>

using namespace std;

int thread_number = 0; // thread number's counter

constexpr const bool IS_PARALELL = true;
constexpr const int ARRAY_SIZE = 30; // length of the friquencies array
constexpr const int PART_SIZE = 10; // part of array that must be processed in a task
constexpr const int PARTS_COUNT = ARRAY_SIZE / PART_SIZE; // count of parts (30/10=3)
constexpr const int TRY_COUNT = 10'000'000; // the number of tries for the every part

constexpr const int STAR_LENGTH = 20; // count of stars in a every line in the final output picture

using my_distribution = uniform_int_distribution<>; // the uniform random distribution

using my_engine = default_random_engine; // the default random generator

mutex m; // experimental

template<typename T>
std::vector<T> range(const std::vector<T>& source, const int index_start, const int index_end) {

	std::vector<T> sub(&source[index_start], &source[index_end]);

	return sub;

} // END: range

inline void work_countinuos(vector<int>& values) { // inline because it used global variables

	my_engine re{};

	for (int i = 0; i < PARTS_COUNT; ++i) {

		int start_index = i * PART_SIZE;

		int end_index = start_index + PART_SIZE - 1;

		my_distribution distr(start_index, end_index);

		for (int y = 0; y != TRY_COUNT; ++y) {

			int index = distr(re);

			++values[index];

		} // END: for

	}; // END: for
}
class  ProcessWork {

private:

	vector<int>* values;
	int index_start;
	int index_end;
	int try_count;
	int this_thread_number;

public:

	// constructor
	ProcessWork(vector<int>* v, int s, int e, int t, int n) :
		values{ v },
		index_start{ s },
		index_end{ e },
		try_count{ t },
		this_thread_number{ n }
	{}

	// the functional operator
	void operator() () {

		const bool IS_LOG = false;

		my_engine re{}; // the local object
		my_distribution distr(index_start, index_end); // the local object

		m.lock();
		cout << "\tTread " << this_thread_number << " started..." << endl; // not safety but
		m.unlock();

		for (int y = 0; y != try_count; ++y) {

			int index = distr(re);
		
			if (IS_LOG) {
			m.lock();
			cout << "\tTread " << this_thread_number << " index " << index << endl;						
			m.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}

			++((*values)[index]);
			
		} // END: for

		m.lock();
		cout << "\tThread end his work." << endl;	// not safety but
		m.unlock();

	} // END: process_work 

};

// Paralell 
void work_paralell(vector<int>& values) { // inline because it used global variables

	array<thread*, PARTS_COUNT> threads;

	for (int i = 0; i < PARTS_COUNT; ++i) {

		// index of part

		int start_index = i * PART_SIZE;

		int end_index = start_index + PART_SIZE - 1;

		auto threads_functional_object =
			ProcessWork{ &values, start_index, end_index, TRY_COUNT, thread_number++ };

		threads[i] = new thread{ threads_functional_object }; // starts thread number i

	}; // END: for

	// wait for every the thread ends...

	for (int i = 0; i < threads.size(); i++) {

		threads[i]->join();

	} // END: work_paralell
}

int main()
{

	array<int, ARRAY_SIZE> ar;
	fill(ar.begin(), ar.end(), 0);
	vector<int> values(ar.begin(), ar.end());

	cout << endl << "\t" << "Working..." << endl << endl;

	if (!IS_PARALELL) {

		work_countinuos(values);

	}
	else {

		work_paralell(values);

	}

	cout << endl;

	print_results(values);

	cout << "Press any key to exit.";

	string isend;

	//_getch(); // wait for keypress

} // END: main()

void print_results(std::vector<int>& values)
{
	for (int i = 0; i < PARTS_COUNT; i++) {

		float average = 0.0f;

		int index_start = i * PART_SIZE;
		int index_end = (i + 1) * PART_SIZE;

		auto iter_start = values.begin() + index_start;
		auto iter_end = values.begin() + index_end;

		for (int y = index_start; y < index_end; y++) {

			cout << "\t" << setfill('0') << setw(8) << values[y] << ": ";

			float scale = TRY_COUNT / PART_SIZE / STAR_LENGTH;

			int stars_size = (int)(values[y] / scale);

			for (int c = 0; c < stars_size; c++) {

				cout << "*";

			}

			cout << endl;

		} // END: for

		cout << endl << endl;

	} // END: for

} // END: print_results


