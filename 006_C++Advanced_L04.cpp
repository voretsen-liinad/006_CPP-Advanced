// C++ advanced - Lesson 4 (20.10.2022)
// Homework 
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

//Task 1------------------------------------------------------------------------------------------------------------------------------------

template<typename T1, typename T2>
void insert_sorted(T1& container, const T2& value) {
	container.insert(lower_bound(container.begin(), container.end(), value), value);
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

double squared_difference(double x, int y) {
	return (x - static_cast<double>(y)) * (x - static_cast<double>(y));
}

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


int main() {

	cout << "Tasks 1-------------------------------------------------------------------------------------------\n";
	vector<int> v1{ 10, 20, 30, 40, 50, 60, 70, 80 };
	for_each(v1.begin(), v1.end(), [](const int& i) { cout << i << " "; }); cout << endl;
	insert_sorted<vector<int>, int>(v1, 35); 
	for_each(v1.begin(), v1.end(), [](const int& i) {cout << i << " "; }); cout << endl;

	deque<double> d1{ 10.1, 12.2, 15.3, 17.4, 20.5, 21.6 };
	for_each(d1.begin(), d1.end(), [](auto& i) { cout << i << " "; }); cout << endl;
	insert_sorted<deque<double>, double>(d1, 14.7);
	for_each(d1.begin(), d1.end(), [](auto& i) { cout << i << " "; }); cout << endl;

	list<string> l1{ "Alex", "Andrew", "Bonnie", "Leo", "Max", "Sophie"};
	for_each(l1.begin(), l1.end(), [](auto& i) { cout << i << " "; }); cout << endl;
	insert_sorted<list<string>, string>(l1, "Marie");
	for_each(l1.begin(), l1.end(), [](auto& i) { cout << i << " "; }); cout << endl;

	cout << "\n";
	cout << "End of tasks 1------------------------------------------------------------------------------------\n" << endl;


	cout << "Tasks 2-------------------------------------------------------------------------------------------\n";
	srand(time(NULL));
	vector<double> a(100);
	generate(a.begin(), a.end(), []() {return (double)(rand() % 10000 - 5000) / 100; });
	ostream_iterator<double> os_it_double = { cout, " " };
	cout << "Vector a:\n";
	copy(a.begin(), a.end(), os_it_double); cout << endl;
	cout << endl;
	vector<int> b(100);
	transform(a.begin(), a.end(), b.begin(), [](int i) { return i; });
	ostream_iterator<int> os_it_int = { cout, " " };
	cout << "Vector b:\n";
	copy(b.begin(), b.end(), os_it_int); cout << endl;

	double error = inner_product(a.begin(), a.end(), b.begin(), double(0), plus<double>(), [](const double& a, const int& b) {return pow((a - static_cast<double>(b)), 2); });

	cout << "\nAn error value = " << error << endl;

	cout << "\n";
	cout << "End of tasks 2------------------------------------------------------------------------------------\n" << endl;

	return 0;
}
