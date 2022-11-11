// C++ advanced - Lesson 6 (09.11.2022)
// Homework 
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

mutex m, m2, m3;

//Task 1------------------------------------------------------------------------------------------------------------------------------------

struct Pcout{};
Pcout pcout;

template<typename T>
Pcout& operator<< (Pcout& s, const T& val) {
	lock_guard<mutex> guard(m);
	cout << val;
	return s;
}

Pcout& operator<< (Pcout& s, ostream& (*f)(ostream&)) {
	lock_guard<mutex> guard(m);
	f(cout);
	return s;
}

Pcout& operator<< (Pcout& s, ostream& (*f)(ios&)) {
	lock_guard<mutex> guard(m);
	f(cout);
	return s;
}

Pcout& operator << (Pcout& s, ostream& (*f)(ios_base&)) {
	lock_guard<mutex> guard(m);
	f(cout);
	return s;
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

bool IsPrime_ForPrimeOfNumber(const long int& number, vector<long int>& primes) {
	lock_guard<mutex> guard(m2);
	if (number < 2) return false;
	else if (number == 2 || number == 3) return true;
	else {
		long int limit = static_cast<long int>(sqrt(number));
		for (size_t i = 1; i < primes.size(); i++) {
			if (primes[i] > limit) break;
			if ((number % primes[i]) == 0) return false;
		}
		primes.push_back(number);
		return true;
	}
}

long int PrimeOfNumber(const size_t& number) {
	cout << "Search for " << number << "th prime\n";
	if (number < 1) {
		cerr << "Prime(): argument is less than 1\n";
		return 0;
	}
	else if (number == 1) {
		cout << "Computation completed\n";
		return 2;
	} 
	else if (number == 2) {
		cout << "Computation completed\n";
		return 3;
	}
	else {
		vector<long int> primes = { 2, 3 };
		long int current_number = primes[primes.size() - 1];
		double current_progress = 0.1;
		while (primes.size() < number) {
			current_number += 2;
			thread t(IsPrime_ForPrimeOfNumber, current_number, ref(primes));
			t.join();
			if ((primes.size() % number) >= (number * current_progress)) {
				cout << current_progress * 100 << "% of primes is found\n";
				current_progress += 0.1;
			}
		}
		cout << "Computation completed\n"; 
		return current_number;
	}
}

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


//Task 3------------------------------------------------------------------------------------------------------------------------------------

void Owner(vector<double>& v) {
	srand(time(NULL));
	while (v.size() > 0) {
		v.push_back(rand() % 1000);
		pcout << "After owner: ";
		for (const double & it : v) {
			pcout << it << " ";
		}
		cout << endl;
		this_thread::sleep_for(1s);
	}
}

void Thief(vector<double>& v) {
	this_thread::sleep_for(500ms);
	srand(time(NULL)); 
	size_t max_index;
	double max;
	while (v.size() > 0) {
		max_index = 0;
		max = v[max_index];
		for (int i = v.size() - 1; i >= 0; i--) {
			if (v[i] > max) {
				max_index = i;
				max = v[i];
			}
		}
		v.erase(v.begin()+max_index);
		pcout << "After thief: ";
		for (const double& it : v) {
			pcout << it << " ";
		}
		cout << endl;
		this_thread::sleep_for(500ms);
	}
}


//End of task 3----------------------------------------------------------------------------------------------------------------------------


int main() {
	cout << "Tasks 1-------------------------------------------------------------------------------------------\n";
	
	thread t1([]() {pcout << "This is " << "the first " << "thread." << endl; });
	thread t2([]() {pcout << "Here is " << "thread " << "number two." << endl; });
	thread t3([]() {pcout << "It is " << "the third " << "thread." << endl; });
	t1.join();
	t2.join();
	t3.join();
	
	cout << "\nEnd of tasks 1------------------------------------------------------------------------------------\n" << endl;


	cout << "Tasks 2-------------------------------------------------------------------------------------------\n";
	size_t position_of_the_prime{ 9876 };
	cout << PrimeOfNumber(position_of_the_prime) << endl;
	
	cout << "\nEnd of tasks 2------------------------------------------------------------------------------------\n" << endl;


	cout << "Tasks 3-------------------------------------------------------------------------------------------\n";
	vector<double> Stock = { 100, 200 ,500, 1000, 0, 400, 800, 900, 250, 80, 2000, 4300 };
	pcout << "That vector: ";
	for (const double& it : Stock) {
		pcout << it << " ";
	}
	pcout << endl;
	thread owner(Owner, ref(Stock));
	thread thief(Thief, ref(Stock));
	owner.join();
	thief.join();

	cout << "\nEnd of tasks 3------------------------------------------------------------------------------------\n" << endl;

	return 0;
}
