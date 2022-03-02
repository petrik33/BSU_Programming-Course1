#include "QueueP.h"
#include <ctime>
#include <random>
using namespace std;

void swap(QueueP* a1, QueueP* a2) {
	QueueP* tmp = new QueueP(std::move(*a1));
	*a1 = std::move(*a2);
	*a2 = std::move(*tmp);
}

int randomNumber(int randMin, int randMax)
{
	return (randMin + (rand() % (randMax - randMin + 1)));
}


int main(){
	QueueP* queueP = new QueueP();
	QueueP* queueP1 = new QueueP();

	string menuExternal = \
		"1)Operate with\n" \
		"2)Automatic Show Change\n" \
		"3)Show manually\n" \
		"4)Swap\n";
		"5)End\n";

	string menuInternal = \
		"1)Insert\n" \
		"2)Pop\n" \
		"3)Head info\n" \
		"4)Get Size\n" \
		"5)Clear\n" \
		"6)Cancel\n";

	int button;
	int queueIdx;
	bool exit = false;
	bool queuesAutoShow = true;

	QueueP* queueOperated = nullptr;
	QueueP* queueOther = nullptr;

	time_t timeStart = 0;
	time_t timeEnd = 0;

	while (!exit)
	{
		if (queuesAutoShow)
		{
			cout << "\nQueue 1: ";
			queueP->WriteToStream(cout);
			cout << "\nQueue 2: ";
			queueP1->WriteToStream(cout);
			cout << "\n";
		}
		
		cout << "\n" << menuExternal << "\n";
		cin >> button;

		switch (button)
		{
		case 1://Operating with one queue
			cout << "Select the queue to operate with(1,2): ";
			cin >> queueIdx;
			while (queueIdx > 2 || queueIdx < 1)
			{
				cout << "Wrong input. Choose between 1 and 2: ";
				cin >> queueIdx;
			}
			if (queueIdx == 1)
			{
				queueOperated = queueP;
				queueOther = queueP1;
			}
			else
			{
				queueOperated = queueP1;
				queueOther = queueP;
			}
			cout << "\n" << menuInternal << "\n";
			int buttonInternal;
			cin >> buttonInternal;
			while (buttonInternal < 0 || buttonInternal > 6)
			{
				cout << "Wrong button. Enter again: ";
				cin >> buttonInternal;
			}
			switch (buttonInternal)
			{
			case 1://Insert
				cout << "1)Randomly\n2)Manually\nChoose the insert mode: ";
				int insertMode, priority;
				cin >> insertMode;
				while (insertMode < 1 || insertMode > 2)
				{
					cout << "Wrong input. Enter again: ";
					cin >> insertMode;
				}
				switch (insertMode)
				{
				case 1:
					int valuesNum, randomMin, randomMax;
					cout << "Enter the number of random values: ";
					cin >> valuesNum;
					while (valuesNum < 1)
					{
						cout << "Wrong input. Enter again: ";
						cin >> valuesNum;
					}
					cout << "Choose priority:\n";
					for (int i = 0; i < PRIORITY_COUNT; i++)
					{
						cout << to_string(i + 1) << ")" << PRIORITY_NAMES[i] << "\n";
					}
					cin >> priority;
					while (priority < 1 || priority > PRIORITY_COUNT)
					{
						cout << "Wrong input. Enter again: ";
						cin >> priority;
					}
					cout << "Enter minimal random value: ";
					cin >> randomMin;
					cout << "Enter maximum random value: ";
					cin >> randomMax;
					for (int i = 0; i < valuesNum; i++)
					{
						queueOperated->insert(randomNumber(randomMin, randomMax), ITEM_PRIORITY(priority - 1));
					}
					break;
				case 2:
					int value;
					cout << "Enter value: ";
					cin >> value;
					cout << "Choose priority:\n";
					for (int i = 0; i < PRIORITY_COUNT; i++)
					{
						cout << to_string(i + 1) << ")" << PRIORITY_NAMES[i] << "\n";
					}
					cin >> priority;
					while (priority < 1 || priority > PRIORITY_COUNT)
					{
						cout << "Wrong input. Enter again: ";
						cin >> priority;
					}
					queueOperated->insert(value, ITEM_PRIORITY(priority - 1));
					break;
				default:
					break;
				}
				break;
			case 2:
				if (queueOperated->pop())
				{
					cout << "Pop sucessful\n";
				}
				else
				{
					cout << "Pop failed\n";
				}
				break;
			case 3:
				try
				{
					cout << "Head value is: " << queueOperated->getFrontValue() << "\n";
					cout << "Head priority is: " << PRIORITY_NAMES[int(queueOperated->getFrontPriority())] << "\n";
				}
				catch (const exception ex)
				{
					cout << ex.what() << "\n";
				}
				//try
				//{
				//	
				//}
				//catch (const exception ex)
				//{
				//	cout << ex.what() << "\n";
				//}
				break;
			case 4:
				int sizeOption;
				for (int i = 0; i < PRIORITY_COUNT; i++)
				{
					cout << to_string(i + 1) << ")" << PRIORITY_NAMES[i] << "\n";
				}
				cout << to_string(PRIORITY_COUNT + 1) << ")Total";
				cin >> sizeOption;
				while (sizeOption < 1 || sizeOption > PRIORITY_COUNT + 1)
				{
					cout << "Wrong input. Enter again: ";
					cin >> sizeOption;
				}
				if (sizeOption <= PRIORITY_COUNT)
				{
					queueOperated->getPrioritySize(ITEM_PRIORITY(sizeOption - 1));
				}
				else
				{
					queueOperated->getTotalSize();
				}
				cout << "\n";
				break;
			case 5:
				queueOperated->clear();
				cout << "\n";
				break;
			case 6:
				cout << "\n";
				break;
			default:
				cout << "Wrong input\n";
				break;
			}
			break;
		case 2:
			queuesAutoShow = !queuesAutoShow;
			break;
		case 3:
			cout << "\nQueue 1: ";
			queueP->WriteToStream(cout);
			cout << "\nQueue 2: ";
			queueP1->WriteToStream(cout);
			cout << "\n";
			break;
		case 4:
			timeStart = clock();
			swap(queueP, queueP1);
			timeEnd = clock();
			cout << "Swap time: " << (timeEnd - timeStart) << "\n";
			break;
		case 5:
			exit = true;
			break;
		/*default:
			cout << "Wrong input.\n";
			break;*/
		}
		

	}
	
	/*queueP->insert(10, ITEM_PRIORITY::HIGH);
	queueP->insert(4, ITEM_PRIORITY::MEDIUM);
	queueP->insert(10, ITEM_PRIORITY::MEDIUM);
	queueP->insert(11, ITEM_PRIORITY::HIGH);
	queueP->insert(8, ITEM_PRIORITY::LOW);
	queueP->insert(12, ITEM_PRIORITY::HIGH);
	queueP->insert(6, ITEM_PRIORITY::LOW);
	queueP->insert(7, ITEM_PRIORITY::HIGH);
	queueP->insert(8, ITEM_PRIORITY::MEDIUM);
	queueP->insert(5, ITEM_PRIORITY::HIGH);
	queueP->insert(3, ITEM_PRIORITY::LOW);
	queueP->WriteToStream(cout);*/
	return 0;
}