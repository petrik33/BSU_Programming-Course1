#include "QueueP.h"

QueueP::QueueP()
{
	front = nullptr;
	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		rears[i] = nullptr;
		sizeByPriority[i] = 0;
	}
}

QueueP::~QueueP()
{
	erase();
}

QueueP::QueueP(const QueueP& other)
{
	front = nullptr;
	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		rears[i] = nullptr;
		sizeByPriority[i] = 0;
	}
	clone(other);
}

QueueP& QueueP::operator=(const QueueP& other)
{
	if (&other == this)
	{
		return *this;
	}
	else
	{
		erase();
		clone(other);
		return *this;
	}
}

QueueP::QueueP(QueueP&& other) noexcept
{
	move(front, other.front);
	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		move(rears[i], other.rears[i]);
		sizeByPriority[i] = other.sizeByPriority[i];
	}
}

QueueP& QueueP::operator=(QueueP&& other) noexcept
{
	if (&other == this)
	{
		return *this;
	}
	move(front, other.front);
	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		move(rears[i], other.rears[i]);
		sizeByPriority[i] = other.sizeByPriority[i];
	}
	return *this;
}

int QueueP::getTotalSize() const
{
	int totalSize = 0;
	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		totalSize += sizeByPriority[i];
	}
	return totalSize;
}

void QueueP::erase()
{
	while (pop())
	{
		//
	}
}

void QueueP::move(QPItem*& a, QPItem*& b)
{
	a = b;
	b = nullptr;
}

//void QueueP::moveQP(QueueP&& other) noexcept
//{
//	
//}

void QueueP::browse(void visit(int), QPItem* p)
{
	if (p != nullptr)
	{
		visit(p->value);
		browse(visit, p->next);
	}
}

void QueueP::browse(void visit(int))
{
	browse(visit, front);
}

bool QueueP::pop()
{
	if (getTotalSize() > 0)
	{
		QPItem* _tmp = front;
		front = front->next;
		sizeByPriority[int(_tmp->priority)]--;
		if (rears[int(_tmp->priority)] == _tmp)
		{
			rears[int(_tmp->priority)] = nullptr;
		}
		delete _tmp;
		return true;
	}
	else
	{
		return false;
	}
}

void QueueP::clear()
{
	erase();
}

bool QueueP::empty() const
{
	return (front == nullptr);
}

int QueueP::getPrioritySize(ITEM_PRIORITY _priority) const
{
	return sizeByPriority[int(_priority)];
}

int QueueP::getFrontValue() const
{
	if (!empty())
	{
		return front->value;
	}
	else
	{
		throw exception("There is no first element");
	}
}

ITEM_PRIORITY QueueP::getFrontPriority() const
{
	if (!empty())
	{
		return front->priority;
	}
	else
	{
		throw exception("There is no first element");
	}
}

//QPItem* QueueP::getFront() const
//{
//	return front;
//}

void QueueP::insert(int _value, ITEM_PRIORITY _priority)
{
	if (int(_priority) >= PRIORITY_COUNT || int(_priority) < 0)
	{
		throw exception("Wrong Item Priority.");
	}
	QPItem* _newItem = new QPItem(_value, _priority, nullptr);
	if (empty())
	{
		front = _newItem;
	}
	else
	{
		if (_priority > front->priority)
		{
			//Insert to front
			_newItem->next = front;
			front = _newItem;
		}
		else
		{
			if (getPrioritySize(_priority) != 0)
			{
				//Inserting in-between with the existing rear
				QPItem* _rear = rears[int(_priority)];
				_newItem->next = _rear->next;
				_rear->next = _newItem;
			}
			else
			{
				//Find Minimal Priority Rear Relative to the inserted one
				QPItem* _rearMin = front;
				for (int i = int(_priority) + 1; i < PRIORITY_COUNT; i++)
				{
					if (rears[i] != nullptr)
					{
						_rearMin = rears[i];
						break;
					}
				}
				_rearMin->next = _newItem;

				QPItem* _rearNext = nullptr; //Relative to the element we insert
				if (int(_priority) >= 1)
				{
					_rearNext = rears[int(_priority) - 1];
				}
				_newItem->next = _rearNext;//For the case we insert in the middle
			}
		}
		
	}
	rears[int(_priority)] = _newItem;
	sizeByPriority[int(_priority)]++;
}

void QueueP::insert(QPItem* _qpItem)
{
	insert(_qpItem->value, _qpItem->priority);
}

void QueueP::clone(const QueueP& other)
{
	if (other.getTotalSize() > 0)
	{
		QPItem* _tmp = other.front;
		while (_tmp->next != nullptr)
		{
			insert(_tmp);
			_tmp = _tmp->next;
		}
	}
}

ostream& QueueP::WriteToStream(ostream& stream)
{
	if (!empty())
	{
		QPItem* _tmp = front;
		while (_tmp != nullptr)
		{
			stream << _tmp->value;
			if (_tmp->next != nullptr)
			{
				stream << " -> ";
			}
			_tmp = _tmp->next;
		}
	}
	else
	{
		stream << "Queue is empty";
	}
	return stream;
}
