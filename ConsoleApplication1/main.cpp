#include "ConsoleApplication1.h"
#include <array>
#include <numeric>
#include <random>
#include <iterator>
#include <conio.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <queue>
#include <chrono>

using namespace std;

class Message {

	string message_text;

public:

	Message(string msg) : message_text{ msg } {};

	string operator() () {

		return this->message_text;

	}

};

std::queue<Message> q;

condition_variable cv;

mutex m_queue;

class F1 {

public:

	F1() {};

	void operator() () {

		this_thread::sleep_for(chrono::seconds{ 3 });

		q.push(Message("Text of message in queue."));

		cv.notify_one();

	}

};

class F2 {

public:

	F2() {};

	void operator() () {

		unique_lock<mutex> lk(m_queue);

		cout << "\tWaiting for queue..." << endl;

		cv.wait(lk, []() {return !q.empty(); });

		Message m = q.front();

		q.pop();

		lk.unlock();

		cout << "\tMessage is: " << m() << endl << endl;

	}

};

// Part 1 - paralell processing

int thread_number = 0; // thread number's counter

constexpr const bool IS_PARALELL = true;
constexpr const int ARRAY_SIZE = 30; // length of the friquencies array
constexpr const int PART_SIZE = 10; // part of array that must be processed in a task
constexpr const int PARTS_COUNT = ARRAY_SIZE / PART_SIZE; // count of parts (30/10=3)
constexpr const int TRY_COUNT = 10'000'000; // the number of tries for the every part

constexpr const int STAR_LENGTH = 20; // count of stars in a every line in the final output picture

using my_distribution = uniform_int_distribution<>; // the uniform random distribution

using my_engine = default_random_engine; // the default random generator

mutex m; // Mutex for cout control

// ---------------------------------------------------------- //
// Function that process friquencies in the continueous order //
// ---------------------------------------------------------- //
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

// ------------------------------------------------------------- //
// Functional object (body) of the friquencies processing thread //
// ------------------------------------------------------------- //
class  ProcessWork {

private:

	vector<int>* values; // pointer to the values's vector
	int index_start; // the start index for the current thread
	int index_end; // the end index for the current thread
	int try_count; // how many tries to do
	int this_thread_number; // the current thread's number (inner)

public:

	// constructor
	ProcessWork(vector<int>* v, int s, int e, int t, int n) :
		values{ v },
		index_start{ s },
		index_end{ e },
		try_count{ t },
		this_thread_number{ n }
	{};

	// The functional operator
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

// ------------------------------------------------------- //
// Function that process friquencies in the paralell order //
// ------------------------------------------------------- //
void work_paralell(vector<int>& values) { // inline because it used global variables

	array<thread*, PARTS_COUNT> threads;

	for (int i = 0; i < PARTS_COUNT; ++i) { // cut the work on some number of parts

		// Calcs indexes in whole array (vector)

		int start_index = i * PART_SIZE;

		int end_index = start_index + PART_SIZE - 1;

		// Constructs the functional object

		auto threads_functional_object =
			ProcessWork{ &values, start_index, end_index, TRY_COUNT, thread_number++ };

		// Creates new thread by the functional object

		threads[i] = new thread{ threads_functional_object }; // starts thread number i

	}; // END: for

	// Starts the paralell processing...
	for (int i = 0; i < threads.size(); i++) {

		threads[i]->join();

	} // END: work_paralell
}

int main()
{

	array<int, ARRAY_SIZE> ar; // Creates the array by size

	fill(ar.begin(), ar.end(), 0); // Fill array by 0 values

	vector<int> values(ar.begin(), ar.end()); // Creates the vector from array

	cout << endl << "\t" << "Working..." << endl << endl;

	if (!IS_PARALELL) { // is parralell?

		work_countinuos(values);

	}
	else {

		work_paralell(values);

	}

	cout << endl;

	print_results(values); // output to the user

	// Part 2 - The condition varable (wall) example

	thread t1{ F1{} }; // the thread that fill some queue by messages

	thread t2{ F2{} }; // the thread that waiting for messages in queue

	t1.join();

	t2.join();

	// Exit from the program

	cout << "\tPress any key to exit.";

	_getch(); // wait for keypress

} // END: main()

// ------------------------- //
// Prints result to the user //
// ------------------------- //
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