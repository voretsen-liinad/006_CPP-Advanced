// C++ advanced - Lesson 3 (17.10.2022)
// Homework 
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <deque>
#include <exception>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>

using namespace std;

//Task 1------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
void list_push_back_average(list<T>& List) {
	if (List.size() == 0) List.push_back(0);
	else if (List.size() == 1) List.push_back(*List.begin()); 
	else {
		double sum{ 0 }, counter{ 0 };
		for (const T& it : List) {
			sum += it;
			counter++;
		}
		List.push_back(static_cast<T>(sum / counter));
	}
}

//End of task 1-----------------------------------------------------------------------------------------------------------------------------


//Task 2------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
class SquareMatrix {
public:
	SquareMatrix(const size_t& n) {
		if (n > 0) {
			vector<T> row(n, 0);
			matrix.reserve(sizeof(row) * n);
			for (int i = 0; i < n; i++) {
				matrix.push_back(row);
			}
		}
		else {
			matrix.clear();
			matrix.shrink_to_fit();
		}
	}
	
	SquareMatrix(const size_t& n, const T& default_value) { 
		if (n > 0) {
			vector<T> row(n, default_value);
			matrix.reserve(sizeof(row) * n);
			for (int i = 0; i < n; i++) {
				matrix.push_back(row);
			}
		}
		else {
			matrix.clear(); 
			matrix.shrink_to_fit();
		}
	}
	
	~SquareMatrix() {
		for (vector<T>& it : matrix) {
			it.clear();
			it.shrink_to_fit();
		}
		matrix.clear();
		matrix.shrink_to_fit();
	}
	
	T& operator()(const size_t& _y, const size_t& _x) {
		try {
			return matrix[_y - 1][_x - 1]; 
		}
		catch (exception& e) {
			cerr << e.what() << ": Incorrect coordinates\n" << endl;
		}
	}

	double m_determinant() const {
		try {
			size_t size = matrix.size();
			if (size > 0) {
				if (size == 1) return static_cast<double>(matrix[0][0]);
				else if (size == 2) return static_cast<double>(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
				else {
					double determinant{ 0 };
					int sign{ 1 };
					for (int k = 0; k < size; k++) {
					size_t new_size = size - 1;
					SquareMatrix<T> submatrix(new_size);
					size_t row {0};
						for (int i = 0; i < size; i++) {
							if (i == k) continue;
							for (int j = 0; j < new_size; j++) {
								submatrix.matrix[row][j] = matrix[i][j + 1];
							}
							row++;
						}
						determinant += sign * matrix[k][0] * submatrix.m_determinant();
						sign *= -1;
					}
					return static_cast<double>(determinant);
				}
			}
			else throw exception{ ": Matrix size is less than 1\n" };
		}
		catch (exception& e) {
			cerr << e.what() << endl;
		}
	}
			
	void print() const {
		for (const vector<T>& it : matrix) {
			for (int i = 0; i < it.size(); i++) {
				cout << setw(5) << it[i];
			}
			cout << endl;
		}
	}

private:
	vector<vector<T>> matrix; 
};

//End of task 2-----------------------------------------------------------------------------------------------------------------------------


//Task 3------------------------------------------------------------------------------------------------------------------------------------

template<typename T>

class NumIterator : public iterator<input_iterator_tag, T> {
	friend class vector<T>;
	friend class deque<T>;   
	friend class list<T>;
public:
	NumIterator(T& value) { ptr = &value; }
	~NumIterator() { ptr = nullptr; }
	bool operator!= (const NumIterator& it) { return ptr != it.ptr; }
	NumIterator& operator++() { ptr++; return *this; } 
	NumIterator operator++(int) { T temp = *ptr; *this = ptr++; return temp; }
	T& operator*() const { return *ptr; }
private:
	T* ptr;
};

//End of task 3-----------------------------------------------------------------------------------------------------------------------------


int main() {
	
	cout << "Tasks 1-------------------------------------------------------------------------------------------\n";

	list <double> L1{ 3, 15.2, 10, 1.05, 8.4 };
	list <double> L2{ 3 };
	list <double> L3;
	cout << "List L1: ";
	for (auto& it : L1) {
		cout << it << " ";
	}
	cout << endl;
	
	cout << "List L2: ";
	for (auto& it : L2) {
		cout << it << " ";
	}
	cout << endl;
	
	cout << "List L3: ";
	for (auto& it : L3) {
		cout << it << " ";
	}
	cout << endl;

	list_push_back_average(L1);
	list_push_back_average(L2);
	list_push_back_average(L3);
	cout << "After list_push_back_average()" << endl;
	
	cout << "List L1: ";
	for (auto& it : L1) {
		cout << it << " ";
	}
	cout << endl;

	cout << "List L2: ";
	for (auto& it : L2) {
		cout << it << " ";
	}
	cout << endl;

	cout << "List L3: ";
	for (auto& it : L3) {
		cout << it << " ";
	}
	cout << endl;

	cout << "\n";
	cout << "End of tasks 1------------------------------------------------------------------------------------\n" << endl;

	
	cout << "Tasks 2-------------------------------------------------------------------------------------------\n";
	SquareMatrix<int> M(4);
	cout << "SquareMatrix M:\n";
	M(1, 1) = 4; M(1, 2) = 7; M(1, 3) = 2; M(1, 4) = 9;
	M(2, 1) = 1; M(2, 2) = 5; M(2, 3) = 3; M(2, 4) = 6;
	M(3, 1) = 9; M(3, 2) = 8; M(3, 3) = 4; M(3, 4) = 2;
	M(4, 1) = 5; M(4, 2) = 0; M(4, 3) = 1; M(4, 4) = 6;
	M.print();

	cout << "Determinant of matrix M : " << M.m_determinant() << endl;
	cout << endl; 
	
	SquareMatrix<int> M2(3);
	cout << "SquareMatrix M2:\n";
	M2(1, 1) = 9; M2(1, 2) = 3; M2(1, 3) = 1;
	M2(2, 1) = 2; M2(2, 2) = 4; M2(2, 3) = 6; 
	M2(3, 1) = 3; M2(3, 2) = 7; M2(3, 3) = 5; 
	M2.print();
	cout << "Determinant of matrix M2 : " << M2.m_determinant() << endl;

	cout << "\n";
	cout << "End of tasks 2------------------------------------------------------------------------------------\n" << endl;


	cout << "Tasks 3-------------------------------------------------------------------------------------------\n";

	vector<int> v{ 10, 20, 30, 40, 50, 60, 70, 80 };
	for (const NumIterator<int>& it : v) {
		cout << *it << " ";
	}
	cout << endl;

	list<double> l{ 1, 2, 3, 4, 5, 6, 7, 8 };
	for (NumIterator<double> it : l) {
		cout << *it << " ";
	}
	cout << endl; 

	cout << "\n";
	cout << "End of tasks 3------------------------------------------------------------------------------------\n" << endl;

	return 0;
}
