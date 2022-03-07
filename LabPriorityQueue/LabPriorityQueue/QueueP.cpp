#include "QueueP.h"

QueueP::QueueP()
{
	front = nullptr;
	rears = new QPItem*[PRIORITY_COUNT];
	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		rears[i] = nullptr;
		sizes[i] = 0;
	}
}

QueueP::~QueueP()
{
	erase();
}

QueueP::QueueP(const QueueP& other) : QueueP()
{
	/*front = nullptr;
	for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		rears[i] = nullptr;
		sizes[i] = 0;
	}*/
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
	/*for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		move(rears[i], other.rears[i]);
		sizes[i] = other.sizes[i];
	}*/
	move(rears, other.rears);
}

QueueP& QueueP::operator=(QueueP&& other) noexcept
{
	if (&other == this)
	{
		return *this;
	}
	move(front, other.front);
	/*for (int i = 0; i < PRIORITY_COUNT; i++)
	{
		move(rears[i], other.rears[i]);
		sizes[i] = other.sizes[i];
	}*/
	move(rears, other.rears);
	return *this;
}

int QueueP::getTotalSize() const
{
	int totalSize = 0;
	for (auto& n : sizes)
		totalSize += n;
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

void QueueP::move(QPItem**& a, QPItem**& b)
{
	a = b;
	b = nullptr;
}

bool QueueP::pop()
{
	if (getTotalSize() == 0)
	{
		return false;
	}
	else
	{
		QPItem* _tmp = front;
		front = front->next;
		sizes[int(_tmp->priority)]--;
		if (rears[int(_tmp->priority)] == _tmp)
		{
			rears[int(_tmp->priority)] = nullptr;
		}
		delete _tmp;
		return true;
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
	return sizes[int(_priority)];
}

int QueueP::getFrontValue() const
{
	if (!empty())
	{
		return front->value;
	}
	throw QueueException("There is no first element");
}

ITEM_PRIORITY QueueP::getFrontPriority() const
{
	if (!empty())
	{
		return front->priority;
	}
	throw QueueException("There is no first element");
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
			if (rears[int(_priority)] != nullptr)
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
	sizes[int(_priority)]++;
}

void QueueP::insert(QPItem* _qpItem)
{
	insert(_qpItem->value, _qpItem->priority);
}

void QueueP::clone(const QueueP& other)
{
	if (other.getTotalSize() > 0)
	{
		return;
	}
	QPItem* _tmp = other.front;
	while (_tmp->next != nullptr)
	{
		insert(_tmp);
		_tmp = _tmp->next;
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
