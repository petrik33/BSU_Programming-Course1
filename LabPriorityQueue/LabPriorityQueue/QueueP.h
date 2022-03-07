#pragma once

#include <exception>
#include <string>
#include <iostream>
using namespace std;

constexpr auto START_LINE = __LINE__;
enum class ITEM_PRIORITY{
	LOW = 0,
	MEDIUM,
	HIGH
};
constexpr auto PRIORITY_COUNT = __LINE__ - START_LINE - 3;
const string PRIORITY_NAMES[] = {"LOW","MEDIUM","HIGH"};

class QueueP
{
private:
	struct QPItem
	{
		int value;
		ITEM_PRIORITY priority;
		QPItem* next;
		QPItem(int _value, ITEM_PRIORITY _priority, QPItem* _next = nullptr)
		{
			value = _value;
			priority = _priority;
			next = _next;
		}
	};
	QPItem* front;
	QPItem** rears;
	int sizes[PRIORITY_COUNT];
	void insert(QPItem*);
	void erase();
	void move(QPItem*& a, QPItem*& b);
	void move(QPItem**& rearsA, QPItem**& rearsB);
public:
	QueueP();
	~QueueP();
	QueueP(const QueueP&);
	QueueP& operator = (const QueueP&);
	QueueP(QueueP&&) noexcept;
	QueueP& operator = (QueueP&&) noexcept;

	int getTotalSize() const;
	int getPrioritySize(ITEM_PRIORITY _priority) const;

	int getFrontValue() const;
	ITEM_PRIORITY getFrontPriority() const;

	void insert(int _value, ITEM_PRIORITY _priority);
	bool pop();
	void clear();
	bool empty() const;
	void clone(const QueueP&);

	ostream& WriteToStream(ostream& s);
};

class QueueException : public exception {
private:
	string m_error;

public:
	QueueException(std::string error)
		: m_error(error)
	{
	}

	const char* what() const noexcept { return m_error.c_str(); }
};

