#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person
{
	static int next_ID;
private:
	string name;
	bool isWoman;
	Person* dad;
	Person* mom;
	string dadName;
	string momName;
	int ID;

	void setSex(bool _isWoman);
public:
	void setDad(const Person* _dad);
	void setMom(const Person* _mom);
	void setName(string s);

	bool getIsWoman() const;
	string getSex() const;
	string getName() const;
	int getID() const;
	Person* getDad() const;
	Person* getMom() const;
	string getDadName() const;
	string getMomName() const;

	friend Person* giveBirth(string s, bool _isWoman, const Person* _mom, const Person* _dad);

	friend ostream& operator<<(ostream& s, const Person& p);

	Person(string s, bool _isWoman, const Person* _mom = nullptr, const Person* _dad = nullptr);
	Person(const Person&);
};

