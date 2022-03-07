#include "QueueP.h"
#include <ctime>
#include <random>

void swap(QueueP* a1, QueueP* a2) {
	QueueP* tmp = new QueueP(std::move(*a1));
	*a1 = std::move(*a2);
	*a2 = std::move(*tmp);
}

int randomNumber(int randMin, int randMax)
{
	return (randMin + (rand() % (randMax - randMin + 1)));
}

void QueuesToCout(QueueP* queueP,QueueP* queueP1) {
	cout << "\nQueue 1: ";
	queueP->WriteToStream(cout);
	cout << "\nQueue 2: ";
	queueP1->WriteToStream(cout);
	cout << "\n";
}

void OperateWithQueues(int button, QueueP* queueOperated, QueueP* queueOther){
	switch (button)
	{
	case 1://Insert
		cout << "1)Randomly\n2)Manually\nChoose the insert mode: ";
		int insertMode, priority, valuesNum;
		cin >> insertMode;
		while (insertMode < 1 || insertMode > 2)
		{
			cout << "Wrong input. Enter again: ";
			cin >> insertMode;
		}
		switch (insertMode)
		{
		case 1:
			int randomMin, randomMax;
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
			cout << "Enter the number of values: ";
			cin >> valuesNum;
			while (valuesNum < 1)
			{
				cout << "Wrong input. Enter again: ";
				cin >> valuesNum;
			}
			while (valuesNum-- > 0)
			{
				int value;
				cout << "Enter value: ";
				cin >> value;
				cout << "Choose priority:\n";
				for (int i = 0; i < PRIORITY_COUNT; i++)
				{
					cout << to_string(i + 1) << ")" << PRIORITY_NAMES[i] << "\n";
				}
				cin >> priority;
				cout << "(" << PRIORITY_NAMES[priority - 1] << ")\n";
				while (priority < 1 || priority > PRIORITY_COUNT)
				{
					cout << "Wrong input. Enter again: ";
					cin >> priority;
				}
				queueOperated->insert(value, ITEM_PRIORITY(priority - 1));
			}
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
		catch (const QueueException& ex)
		{
			cout << ex.what() << "\n";
		}
		catch (const exception& ex)
		{
			cout << ex.what() << "\n";
		}
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
}

int main(){
	QueueP* queueP = new QueueP();
	QueueP* queueP1 = new QueueP();

	string menuExternal = \
		"1)Operate with\n" \
		"2)Automatic Show Change\n" \
		"3)Show manually\n" \
		"4)Swap\n" \
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

	while (!exit)
	{
		QueueP* queueOperated = nullptr;
		QueueP* queueOther = nullptr;
		if (queuesAutoShow)
		{
			QueuesToCout(queueP, queueP1);
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
			OperateWithQueues(buttonInternal, queueOperated, queueOther);
			break;
		case 2:
			queuesAutoShow = !queuesAutoShow;
			break;
		case 3:
			QueuesToCout(queueP, queueP1);
			break;
		case 4:
			swap(queueP, queueP1);
			cout << "Queues swapped successfully.\n";
			break;
		case 5:
			exit = true;
			break;
		/*default:
			cout << "Wrong input.\n";
			break;*/
		}
		

	}
	delete queueP;
	delete queueP1;
	return 0;
}