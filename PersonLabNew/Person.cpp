#include "Person.h"

int Person::next_ID = 0;

void Person::setSex(bool _isWoman)
{
	isWoman = _isWoman;
}

void Person::setDad(const Person* _dad)
{
	dad = (Person*)_dad;
	if (_dad == nullptr)
	{
		dadName = "Unknown";
	}
	else
	{
		dadName = dad->name;
	}
}

void Person::setMom(const Person* _mom)
{
	mom = (Person*)_mom;
	if (_mom == nullptr)
	{
		momName = "Unknown";
	}
	else
	{
		momName = mom->name;
	}
}

void Person::setName(string s)
{
	name = s;
}

bool Person::getIsWoman() const
{
	return isWoman;
}

Person::Person(string s, bool _isWoman, const Person* _mom, const Person* _dad) : ID(next_ID++)
{
	setName(s);
	setSex(_isWoman);
	setMom(_mom);
	setDad(_dad);
}

string Person::getSex() const
{
	if (isWoman)
	{
		return "woman";
	}
	else
	{
		return "man";
	}
}

Person::Person(const Person& p) : ID(next_ID++)
{
	setName(p.name);
	setSex(p.isWoman);
	setDad(p.dad);
	setMom(p.mom);
}

int Person::getID() const
{
	return ID;
}

string Person::getName() const
{
	return name;
}

Person* Person::getDad() const
{
	return dad;
}

Person* Person::getMom() const
{
	return mom;
}

string Person::getDadName() const
{
	return dadName;
}

string Person::getMomName() const
{
	return momName;
}

ostream& operator<<(ostream& s, const Person& p)
{
	s << p.name << " - " << p.getSex() << "\nFather: " << \
	p.dadName << "   Mother: " << p.momName;
	return s;
}

Person* giveBirth(string s, bool _isWoman, const Person* _mom, const Person* _dad = nullptr)
{
	if (_dad != nullptr)
	{
		if (_dad->getIsWoman())
		{
			throw exception("Error. Father isn't male. ");
		}
	}

	if (_mom != nullptr)
	{
		if (!_mom->getIsWoman())
		{
			throw exception("Error. Mother isn't male.");
		}
	}

	return (new Person(s, _isWoman, _mom, _dad));
}
