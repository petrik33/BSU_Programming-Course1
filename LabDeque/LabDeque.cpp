#include "DQueue.cpp"
#include <string>

const int MAX_LEN = 100;

void varMakeAbs(int& a)
{
    a = abs(a);
}

void varMakeAbs(double& a)
{
    a = abs(a);
}

#pragma region DQueue Input Functions

void inputQueue(DQueue<int>& q)
{
    unsigned len;
    cout << "Enter the number of elements you want to add to your Dqueue: ";
    cin >> len;
    while (len < 1)
    {
        cout << "Why would you need an empty Dqueue? Enter again please: ";
        cin >> len;
    }

    cout << "Good. Now enter the values to your queue:\n";
    for (int i = 0; i < len; i++)
    {
        int var;
        cout << i << ": ";
        cin >> var;
        q.Push(var);
    }
}

void inputQueue(DQueue<double>& q)
{
    unsigned len;
    cout << "Enter the number of elements you want to add to your Dqueue: ";
    cin >> len;
    while (len < 1)
    {
        cout << "Why would you need an empty Dqueue? Enter again please: ";
        cin >> len;
    }

    cout << "Good. Now enter the values to your queue:\n";
    for (int i = 0; i < len; i++)
    {
        double var;
        cout << i << ": ";
        cin >> var;
        q.Push(var);
    }
}

void inputQueue(DQueue<const char*>& q)
{
    unsigned len;
    cout << "Enter the number of elements you want to add to your Dqueue: ";
    cin >> len;
    while (len < 1)
    {
        cout << "Why would you need an empty Dqueue? Enter again please: ";
        cin >> len;
    }

    cout << "Good. Now enter the values to your queue:\n";
    cin.ignore();
    for (int i = 0; i < len; i++)
    {
        cout << i << ": ";
        char* var = new char[MAX_LEN];
        cin.getline(var, MAX_LEN,'\n');
        q.Push(var);
    }
}

#pragma endregion

int main()
{
    cout << "Let's start working with your integer DQueue.\n";

    DQueue <int>* qInt = new DQueue<int>;
    inputQueue(*qInt);

    cout << "\nGreat. What would you like to do with your integer Dqueue now?\n";

    string DQueueMenu = "1)Output from front to rear\n" \
                        "2)Output backwards\n" \
                        "3)Get First\n" \
                        "4)Get Last\n" \
                        "5)Get Size\n" \
                        "6)Insert front\n" \
                        "7)Insert rear\n" \
                        "8)Delete\n";

    string DQueueNumbersMenu = (DQueueMenu + "9)Make all the elements positive(Browse)\n");

    int button;
    bool exit = false;

#pragma region Int Deque

    while (!exit)
    {
        cout << DQueueNumbersMenu;
        cin >> button;
        cout << "\n";
        switch (button)
        {
        case 1:
            qInt->WriteToStreamFrontToRear(cout);
            break;
        case 2:
            qInt->WriteToStreamRearToFront(cout);
            break;
        case 3:
            cout << qInt->GetFirst() << "\n";
            break;
        case 4:
            cout << qInt->GetLast() << "\n";
            break;
        case 5:
            cout << qInt->GetSize() << "\n";
            break;
        case 6:
            int num;
            cout << "Input number: ";
            cin >> num;
            qInt->InsertFront(num);
            break;
        case 7:
            int num2;
            cout << "Input number: ";
            cin >> num2;
            qInt->Push(num2);
            break;
        case 8:
            delete qInt;
            exit = true;
            break;
        case 9:
            qInt->BrowseForward(varMakeAbs);
            break;
        default:
            cout << "Wrong input.";
            break;
        }
        cout << "\n";
    }

#pragma endregion

#pragma region Double DQueue
    exit = false;
    DQueue<double>* qDouble = new DQueue<double>;

    cout << "\nNow DQueue of doubles.\n";
    inputQueue(*qDouble);

    cout << "\nGreat. What would you like to do with the Dqueue now?\n";

    while (!exit)
    {
        cout << DQueueNumbersMenu;
        cin >> button;
        cout << "\n";
        switch (button)
        {
        case 1:
            qDouble->WriteToStreamFrontToRear(cout);
            break;
        case 2:
            qDouble->WriteToStreamRearToFront(cout);
            break;
        case 3:
            cout << qDouble->GetFirst() << "\n";
            break;
        case 4:
            cout << qDouble->GetLast() << "\n";
            break;
        case 5:
            cout << qDouble->GetSize() << "\n";
            break;
        case 6:
            double num;
            cout << "Input number: ";
            cin >> num;
            qDouble->InsertFront(num);
            break;
        case 7:
            double num2;
            cout << "Input number: ";
            cin >> num2;
            qDouble->Push(num2);
            break;
        case 8:
            delete qDouble;
            exit = true;
            break;
        case 9:
            qDouble->BrowseForward(varMakeAbs);
            break;
        default:
            cout << "Wrong input.";
            break;
        }
        cout << "\n";
    }
#pragma endregion

#pragma region Const Char DQueue

    exit = false;
    DQueue<const char*>* qStrings = new DQueue<const char*>;

    cout << "\nNow DQueue of null-terminated strings.\n";

    inputQueue(*qStrings);

    cout << "\nGreat. What would you like to do with the Dqueue now?\n";

    while (!exit)
    {
        cout << DQueueMenu;
        cin >> button;
        cout << "\n";
        switch (button)
        {
        case 1:
            qStrings->WriteToStreamFrontToRear(cout);
            break;
        case 2:
            qStrings->WriteToStreamRearToFront(cout);
            break;
        case 3:
            cout << qStrings->GetFirst() << "\n";
            break;
        case 4:
            cout << qStrings->GetLast() << "\n";
            break;
        case 5:
            cout << qStrings->GetSize() << "\n";
            break;
        case 6:
        {
            char* str = new char[MAX_LEN];
            cout << "Input new string: ";
            cin.ignore();
            cin.getline(str, MAX_LEN, '\n');
            qStrings->InsertFront(str);
        }
        break;
        case 7:
        {
            char* str2 = new char[MAX_LEN];
            cout << "Input new string: ";
            cin.ignore();
            cin.getline(str2, MAX_LEN, '\n');
            qStrings->Push(str2);
        }
        break;
        case 8:
            delete qStrings;
            exit = true;
            break;
            /*       case 9:
                       double multNum;
                       cout << "Input multiplier: ";
                       cin >> multNum;
                       qInt->BrowseForward(varMakeAbs);
                       break;*/
        default:
            cout << "Wrong input.";
            break;
        }
        cout << "\n";
    }


    cout << "\n";

#pragma endregion

}