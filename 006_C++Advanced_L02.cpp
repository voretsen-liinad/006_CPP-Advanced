// C++ advanced - Lesson 2 (13.10.2022)
// Homework 
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <algorithm> 
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Task 1------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
void Swap(T& ptr1, T& ptr2) {
	T* temp = new T;
	*temp = move(ptr1);
	ptr1 = move(ptr2);
	ptr2 = move(*temp);
	delete temp;
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
void SortPointers(vector<T>& v) {
	sort(v.begin(), v.end(), [&](const T& a, const T& b) -> bool {return (*a < *b); });
}

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


//Task 3------------------------------------------------------------------------------------------------------------------------------------

int CountVowels_1(ifstream& ifs) {
	string Vowels = "АЕЁИОУЫЭЮЯаеёиоуыэюяAEIOUYaeiouy";
	int Counter{ 0 };
	string CurrentString;
	while (getline(ifs, CurrentString)) {
		for (const char& it : Vowels) {
			Counter += count_if(find(CurrentString.begin(), CurrentString.end(), it), CurrentString.end(),
				[&](const char& c)->bool {return (c == it); });
		}
	}
	return Counter;
}

int CountVowels_2(ifstream& ifs) {
	string Vowels = "АЕЁИОУЫЭЮЯаеёиоуыэюяAEIOUYaeiouy";
	int Counter{ 0 };
	string CurrentString;
	string::iterator end;
	while (getline(ifs, CurrentString)) {
		end = CurrentString.end();
		for (const char& it : Vowels) {
			for (string::iterator i = CurrentString.begin(); i < end; i++) {
				if (*i == it) {
					Counter += count_if(i, CurrentString.end(), [&](const char& c)->bool {return(c == it); });
					break;
				}
			}
		}
	}
	return Counter;
}

int CountVowels_3(ifstream& ifs) {
	string Vowels = "АЕЁИОУЫЭЮЯаеёиоуыэюяAEIOUYaeiouy";
	int Counter{ 0 };
	string CurrentString;
	string::iterator end;
	while (getline(ifs, CurrentString)) {
		end = CurrentString.end();
		for (const char& it : Vowels) {
			for (string::iterator i = find(CurrentString.begin(), CurrentString.end(), it); i < end; i++) {
				if (*i == it) Counter++;
			}
		}
	}
	return Counter;
}

int CountVowels_4(ifstream& ifs) {
	string Vowels = "АЕЁИОУЫЭЮЯаеёиоуыэюяAEIOUYaeiouy";
	int Counter{ 0 };
	string CurrentString;
	string::iterator end;
	while (getline(ifs, CurrentString)) {
		end = CurrentString.end();
		for (const char& it : Vowels) {
			for (string::iterator i = CurrentString.begin(); i < end; i++) {
				if (*i == it) {
					for (string::iterator j = i; j < end; j++) {
						if (*j == it) Counter++;
					}
					break;
				}
			}
		}
	}
	return Counter;
}

//End of task 3-----------------------------------------------------------------------------------------------------------------------------



int main() {

	cout << "Tasks 1-------------------------------------------------------------------------------------------\n";
	int x{ 10 }, y{ 20 };
	int *ptr1 = &x, *ptr2 = &y;
	cout << "Before Swap():\nptr1: " << ptr1 << " = " << *ptr1 << "\n"
		<< "ptr2: " << ptr2 << " = " << *ptr2 << endl;
	cout << endl;
	Swap(ptr1, ptr2); 
	cout << "After Swap():\nptr1: " << ptr1 << " = " << *ptr1 << "\n"
		<< "ptr2: " << ptr2 << " = " << *ptr2 << endl;

	cout << "\n";
	cout << "End of tasks 1------------------------------------------------------------------------------------\n" << endl;

	cout << "Tasks 2-------------------------------------------------------------------------------------------\n";
	double a{ 15.3 }, b{ 1 }, c{ 8.2 }, d{ -0.1 }, e{ 10 }, f{ 15 };
	double* pa = &a, * pb = &b, * pc = &c, * pd = &d, * pe = &e, * pf = &f; 
	vector<double*> pointers{ pa, pb, pc, pd, pe, pf };
	cout << "Before SortPointers():\n";
	for (auto& it : pointers) {
		cout << it << "=" << *it << endl;
	}
	cout << endl;
	SortPointers(pointers);
	cout << "After SortPointers():\n";
	for (auto& it : pointers) {
		cout << it << "=" << *it << endl;
	}

	cout << "\n";
	cout << "End of tasks 2------------------------------------------------------------------------------------\n" << endl;

	cout << "Tasks 3-------------------------------------------------------------------------------------------\n";

	ifstream file;
	file.open("C:\\War and Piece.txt");

	auto start = chrono::steady_clock::now();
	cout << "CountVowels_1(): Number of vowels = " << CountVowels_1(file) << " letter(s)" << endl;
	auto end = chrono::steady_clock::now();
	chrono::duration<double> time = end - start; 
	cout << "CountVowels_1(): Time of execution = " << time.count() << " second(s)\n" << endl;
	file.close();

	file.open("C:\\War and Piece.txt");
	start = chrono::steady_clock::now();
	cout << "CountVowels_2(): Number of vowels = " << CountVowels_2(file) << " letter(s)" << endl;
	end = chrono::steady_clock::now();
	time = end - start;
	cout << "CountVowels_2(): Time of execution = " << time.count() << " second(s)\n" << endl;
	file.close();

	file.open("C:\\War and Piece.txt");
	start = chrono::steady_clock::now();
	cout << "CountVowels_3(): Number of vowels = " << CountVowels_3(file) << " letter(s)" << endl;
	end = chrono::steady_clock::now();
	time = end - start;
	cout << "CountVowels_3(): Time of execution = " << time.count() << " second(s)\n" << endl;
	file.close();

	file.open("C:\\War and Piece.txt");
	start = chrono::steady_clock::now();
	cout << "CountVowels_4(): Number of vowels = " << CountVowels_4(file) << " letter(s)" << endl;
	end = chrono::steady_clock::now();
	time = end - start;
	cout << "CountVowels_4(): Time of execution = " << time.count() << " second(s)\n" << endl;
	file.close();

	//Function "CountVowels_3()" has the best time of execution. The time of function "CountVowels_1()" is almost the same (but a little bit more).
	//Functions "CountVowels_2()" and "CountVowels_4()" need much more time for execution (CountVowels_2() takes third place, CountVowels_4() - fourth place.

	cout << "\n";
	cout << "End of tasks 3------------------------------------------------------------------------------------\n" << endl;

	return 0;
}
