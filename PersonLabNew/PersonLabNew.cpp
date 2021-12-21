// PersonLabNew.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Person.h"
#include <vector>

template <typename T>
void cinInput(T& var)
{
    cin >> var;
}

int stringFindInVector(string s, vector <string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (s == vec[i])
        {
            return i;
        }
    }
    return -1;
}

template <>
void cinInput<string>(string& var)
{
    getline(cin, var);
}

template <>
void cinInput(unsigned& var)
{
    while (true)
    {
        try
        {
            string varS;
            getline(cin, varS);
            int varInt = stoi(varS);
            if (varInt < 0)
            {
                throw exception("Wrong input. Expecting non-negative only. ");
            }
            var = (unsigned)varInt;
            break;
        }
        catch (...)
        {
            cout << "Wrong input. Enter Again.\n";
        }
    }
}

void inputButton(unsigned& var, unsigned min, unsigned max)
{
    cinInput(var);
    while (var < min || var > max)
    {
        cout << "Input out of range. Enter again: ";
        cinInput(var);
    }
}

template <>
void cinInput<int>(int& var)
{
    while (true)
    {
        try
        {
            string varS;
            getline(cin, varS);
            var = stoi(varS);
            break;
        }
        catch (...)
        {
            cout << "Wrong input. Enter Again.\n";
        }
    }
}

vector <Person*> peopleGetMen(vector <Person*>& people)
{
    vector <Person*> men;
    for (int i = 0; i < people.size(); i++)
    {
        if (!people[i]->getIsWoman())
        {
            men.push_back(people[i]);
        }
    }
    return men;
}

vector <Person*> peopleGetWomen(vector <Person*>& people)
{
    vector <Person*> women;
    for (int i = 0; i < people.size(); i++)
    {
        if (people[i]->getIsWoman())
        {
            women.push_back(people[i]);
        }
    }
    return women;
}

void birthInput(vector <Person*> &people)
{
    string name;
    cout << "Name: ";
    while (true)
    {
        try
        {
            cinInput(name);
            if (name.empty())
            {
                throw exception("Empty Input. ");
            }
            break;
        }
        catch (const exception e)
        {
            cout << e.what() << "Enter again.\n";
        }
    }

    cout << "Sex: 1)Man   2)Woman\n";
    unsigned input;
    inputButton(input, 1, 2);

    bool isWoman = (input == 2);


    cout << "Do you know the father? 1)Yes   2)No\n";
    inputButton(input,1,2);

    Person* dad = nullptr;

    if (input == 1)
    {
        cout << "Father: ";
        vector <Person*> men = peopleGetMen(people);
        while (true)
        {
            try
            {
                cout << "\n";
                for (int i = 0; i < men.size(); i++)
                {
                    cout << i + 1 << ") " << men[i]->getName() << "\n";
                }

                unsigned fatherInput;
                inputButton(fatherInput, 1, men.size());
                dad = men[fatherInput - 1];
                break;
            }
            catch (const std::exception& e)
            {
                cout << e.what();
            }
        }
    }

    cout << "Mother: ";
    Person* mom;
    vector <Person*> women = peopleGetWomen(people);
    while (true)
    {
        try
        {
            cout << "\n";
            for (int i = 0; i < women.size(); i++)
            {
                cout << i + 1 << ") " << women[i]->getName() << "\n";
            }

            unsigned motherInput;
            inputButton(motherInput, 1, women.size());
            mom = women[motherInput - 1];
            break;
        }
        catch (const std::exception& e)
        {
            cout << e.what();
        }
    }

    try
    {
        Person* child = giveBirth(name, isWoman, mom, dad);
        people.push_back(child);
    }
    catch (const std::exception& e)
    {
        cout << e.what() << "Birth failed.\n";
    }
    cout << "\n";
}

int main()
{
    vector <Person*> people;
    people.push_back(new Person("Adam", false));
    people.push_back(new Person("Eve", true));

    cout << "Further actions?  1)Born new person.   2)See all the people.\n";

    unsigned buttonIn;
    inputButton(buttonIn,1,2);

    while (buttonIn != 2)
    {
        cout << "\n";
        birthInput(people);
        cout << "Further actions?  1)Born new person.   2)See all the people.\n";
        inputButton(buttonIn, 1, 2);
    }

    cout << "\n";

    for (int i = 0; i < people.size(); i++)
    {
        cout << (*people[i]) << "\n\n";
    }
}
