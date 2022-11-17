// C++ advanced - Lesson 8 (14.11.2022)
// Homework 
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)


#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>

using namespace std;

struct Person {
	Person() : Surname(""), Name(""), Patronymic(nullopt) {}
	Person(const string& s, const string& n) : Surname(s), Name(n), Patronymic(nullopt) {}
	Person(const string& s, const string& n, const string& p) : Surname(s), Name(n), Patronymic(p) {}
	~Person() {}
	string Surname, Name;
	optional<string> Patronymic;
};


ostream& operator<< (ostream& os, const Person& P) {
	os << setw(14) << left << P.Surname << setw(12) << left << P.Name;
	if (P.Patronymic.has_value()) os << setw(17) << left << P.Patronymic.value();
	else os << setw(17) << left << "";
	return os;
}

bool operator< (const Person& P1, const Person& P2) {
	return (tie(P1.Surname, P1.Name, P1.Patronymic) < tie(P2.Surname, P2.Name, P2.Patronymic));
}

bool operator== (const Person& P1, const Person& P2) {
	return (tie(P1.Surname, P1.Name, P1.Patronymic) == tie(P2.Surname, P2.Name, P2.Patronymic));
}


struct PhoneNumber {
	PhoneNumber() : CountryCode(0), CityCode(0), Number(""), Extension(nullopt) {}
	PhoneNumber(const int& _CountryCode, const int& _CityCode, const string& _Number) :
		CountryCode(_CountryCode), CityCode(_CityCode), Number(_Number), Extension(nullopt) {}
	PhoneNumber(const int& _CountryCode, const int& _CityCode, const string& _Number, const nullopt_t& n) :
		CountryCode(_CountryCode), CityCode(_CityCode), Number(_Number), Extension(nullopt) {}
	PhoneNumber(const int& _CountryCode, const int& _CityCode, const string& _Number, const int& _Extension) :
		CountryCode(_CountryCode), CityCode(_CityCode), Number(_Number), Extension(_Extension) {}
	~PhoneNumber() {}
	int CountryCode, CityCode;
	string Number;
	optional<int> Extension;
};

ostream& operator<< (ostream& os, const PhoneNumber& PN) {
	os << "+" << PN.CountryCode << "(" << PN.CityCode << ")" << PN.Number;
	if (PN.Extension.has_value()) os << " " << setw(10) << left << PN.Extension.value();
	else os << " " << setw(10) << left << "";
	return os;
}

bool operator< (const PhoneNumber& PN1, const PhoneNumber& PN2) {
	return (tie(PN1.CountryCode, PN1.CityCode, PN1.Number, PN1.Extension) < tie(PN2.CountryCode, PN2.CityCode, PN2.Number, PN2.Extension));
}

bool operator== (const PhoneNumber& PN1, const PhoneNumber& PN2) {
	return (tie(PN1.CountryCode, PN1.CityCode, PN1.Number, PN1.Extension) == tie(PN2.CountryCode, PN2.CityCode, PN2.Number, PN2.Extension));
}


bool CompareByName(const pair<Person, PhoneNumber>& Pair1, const pair<Person, PhoneNumber>& Pair2) {
	return (Pair1.first < Pair2.first);
}

bool CompareByPhone(const pair<Person, PhoneNumber>& Pair1, const pair<Person, PhoneNumber>& Pair2) {
	return (Pair1.second < Pair2.second);
}

class PhoneBook {
public:
	PhoneBook(ifstream& ifs) {
		Person CurrentPerson;
		PhoneNumber CurrentPhoneNumber;
		string CurrentString = "-";
		char CurrentChar;
		while (ifs) {
			if (CurrentString == "-") ifs >> CurrentPerson.Surname;
			else CurrentPerson.Surname = CurrentString;
			ifs >> CurrentPerson.Name >> CurrentString;
			if (isalpha(CurrentString[0])) {
				CurrentPerson.Patronymic = CurrentString;
				ifs >> CurrentPhoneNumber.CountryCode;
			}
			else {
				CurrentPerson.Patronymic = nullopt;
				CurrentPhoneNumber.CountryCode = stoi(CurrentString);
			}
			ifs >> CurrentPhoneNumber.CityCode >> CurrentPhoneNumber.Number;
			if (ifs >> CurrentString) {
				if (isdigit(CurrentString[0])) {
					CurrentPhoneNumber.Extension = stoi(CurrentString);
					CurrentString = "-";
				}
				else CurrentPhoneNumber.Extension = nullopt;
				PhoneBookRecords.push_back({ CurrentPerson, CurrentPhoneNumber });
				while (isspace(ifs.peek())) ifs.get(CurrentChar);
				if (ifs.eof()) break;
			}
			else {
				CurrentPhoneNumber.Extension = nullopt;
				PhoneBookRecords.push_back({ CurrentPerson, CurrentPhoneNumber });
				break;
			}
		}
	}
	~PhoneBook() {}

	friend ostream& operator<< (ostream& os, const PhoneBook& PB);

	void SortByName() {
		sort(PhoneBookRecords.begin(), PhoneBookRecords.end(), CompareByName);
	}

	void SortByPhone() {
		sort(PhoneBookRecords.begin(), PhoneBookRecords.end(), CompareByPhone);
	}

	tuple<string, PhoneNumber> GetPhoneNumber(const string& surname) {
		int counter{ 0 };
		PhoneNumber answer;
		for (const auto& [person, phoneNumber] : PhoneBookRecords) {
			if (person.Surname == surname) {
				counter++;
				if (counter > 1) return tie("found more than one", answer);
				answer = phoneNumber;
			}
		}
		if (counter == 0) return tie("not found", answer);
		if (counter == 1) return tie("", answer);
	}

	void ChangePhoneNumber(const Person& P, const PhoneNumber& PN) {
		for (auto& [person, phoneNumber] : PhoneBookRecords) {
			if (person == P) phoneNumber = PN;
		}
	}
private:
	vector<pair<Person, PhoneNumber>> PhoneBookRecords;
};

ostream& operator<< (ostream& os, const PhoneBook& PB) {
	for (const pair<Person, PhoneNumber>& CurrentPair : PB.PhoneBookRecords) {
		os << CurrentPair.first << CurrentPair.second << endl;
	}
	return os;
}


ifstream file("C:\\PhoneBook.txt");
PhoneBook book(file);


TEST(PhoneBook_conten_test, PhoneNumber_Full_test_Makeev) {
	ASSERT_TRUE(PhoneNumber(77, 4521, "8880876", 999) == get<1>(book.GetPhoneNumber("Makeev")));
}

TEST(PhoneBook_data_test, PhoneNumber_Number_test_Egorov) {
	ASSERT_EQ(PhoneNumber(77, 4521, "8880876"), get<1>(book.GetPhoneNumber("Egorov"))); //this test has to fail (Egorov's phone number has extension)  
}

TEST(PhoneBook_method_test, SortByPhone_NoException_test) {
	ASSERT_NO_THROW(book.SortByPhone());
}

TEST(PhoneBook_method_test, SortByName_RuntimeError_test) {
	ASSERT_THROW(book.SortByName(), runtime_error);  //this test has to fail (book.SortByName() throw nothing)
}

TEST(Lambda_test, Lambda_print_phone_number_AnyException_test) {
	ASSERT_ANY_THROW(							   //this test has to fail (lambda print_phone_number throw nothing)
		auto print_phone_number = [&](const string& surname) {
			cout << surname << "\t";
			auto answer = book.GetPhoneNumber(surname);
			if (get<0>(answer).empty())
				cout << get<1>(answer);
			else
				cout << get<0>(answer);
			cout << endl;
		};
		print_phone_number("Ivanov");
	);
}

int main() {
	setlocale(LC_ALL, "Rus");

	cout << book;

	cout << "------SortByPhone-------" << endl;
	book.SortByPhone();
	cout << book;

	cout << "------SortByName--------" << endl;
	book.SortByName();
	cout << book;

	cout << "------GetPhoneNumber-----" << endl;
	//lambda
	auto print_phone_number = [&](const string& surname) {
		cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (get<0>(answer).empty())
			cout << get<1>(answer);
		else
			cout << get<0>(answer);
		cout << endl;
	};
	//call of lambda
	print_phone_number("Ivanov");
	print_phone_number("Petrov");

	cout << "-----ChangePhoneNumber----" << endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
	cout << book;

	cout << "\n";

	testing::InitGoogleTest();
	return RUN_ALL_TESTS();

	return 0;
}
