// C++ advanced - Lesson 7 (11.11.2022)
// Homework 
// Created by Daniil Neserov (e-mail: maidanov1991@yandex.ru)

#include <iostream>
#include <fstream>
#include <string>
#include "University.pb.h"

using namespace std;

class IRepository {
	virtual void Open() = 0; //binary deserialization to file
	virtual void Save() = 0; //binary serialization to file
};

class IMethods {
	virtual double GetAverageScore(const University::FullName& name) = 0;
	virtual string GetAllInfo(const University::FullName& name) = 0;
	virtual string GetAllInfo() = 0;
};

class StudentsGroup : public IRepository, public IMethods {
public:
	virtual void Open() override {
		ifstream in("C:/StudentsGroupSerialized.bin", ios_base::binary);
		if (Group.ParseFromIstream(&in)) {
			ofstream out("C:/StudentsGroupDeserialized.bin", ios_base::binary);
			for (int i = 0; i < Group.students_size(); i++) {
				out << Group.students(i).fullname().name() << " "
					<< Group.students(i).fullname().surname() << " "
					<< Group.students(i).fullname().patronymic() << " ";
				for (int j = 0; j < Group.students(i).scores_size(); j++) {
					out << Group.students(i).scores(j) << " ";
				}
				out << Group.students(i).averagescore() << endl;
			}
		}
		else cerr << "Error!" << endl;
	}
	
	virtual void Save() override { 
		ofstream out("C:/StudentsGroupSerialized.bin", ios_base::binary);
		Group.SerializeToOstream(&out);
	}
	
	virtual double GetAverageScore(const University::FullName& name) override {
		for (int i = 0; i < Group.students_size(); i++) {
			if (name.name() == Group.students(i).fullname().name() &&
				name.surname() == Group.students(i).fullname().surname() &&
				name.patronymic() == Group.students(i).fullname().patronymic()) {
				return Group.students(i).averagescore();
			}
		}
		cerr << "Error: no average score for " << name.name() << " " << name.surname() << " " << name.patronymic() << endl;
		return 0;
	}
	
	virtual string GetAllInfo(const University::FullName& name) override {
		string result;
		for (int i = 0; i < Group.students_size(); i++) {
			if (name.name() == Group.students(i).fullname().name() &&
				name.surname() == Group.students(i).fullname().surname() &&
				name.patronymic() == Group.students(i).fullname().patronymic()) {
				result += name.name();
				result += " "; 
				result += name.surname();
				result += " ";
				result += name.patronymic();
				result += " ";
				for (int j = 0; j < Group.students(i).scores_size(); j++) {
					result += to_string(Group.students(i).scores(j)); 
					result += " ";
				}
				result += to_string(Group.students(i).averagescore());
				return result;
			}
		}
		cerr << "Error: no data for " << name.name() << " " << name.surname() << " " << name.patronymic() << endl;
		return result;
	}
	
	virtual string GetAllInfo() override {
		string result;
		for (int i = 0; i < Group.students_size(); i++) {
			result += Group.students(i).fullname().name();
			result += " ";
			result += Group.students(i).fullname().surname();
			result += " ";
			result += Group.students(i).fullname().patronymic();
			result += " ";
			for (int j = 0; j < Group.students(i).scores_size(); j++) {
				result += to_string(Group.students(i).scores(j));
				result += " ";
			}
			result += to_string(Group.students(i).averagescore());
			result += "\n";
		}
		return result;
	}
private:
	University::StudentsGroup Group;
};


int main() {

	return 0;
}
