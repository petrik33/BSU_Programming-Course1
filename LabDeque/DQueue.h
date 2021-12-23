#pragma once
#ifndef __DQueue_defined_
#define __DQueue_defined_
#include <iostream>
using namespace std;

template <typename InfoType = int>
class DQueue
{
private:
    struct QItem {
        InfoType info;
        QItem* next;
        QItem* prev;
        QItem(InfoType Ainfo,QItem* _next = NULL, QItem* _prev = NULL) : info(Ainfo), next(_next), prev(_prev) {}
 /*       QItem(InfoType Ainfo,QItem* _prev) : info(Ainfo), next(NULL), prev(_prev) {}
        QItem(InfoType Ainfo, QItem* _next) : info(Ainfo), next(_next), prev(NULL) {}*/
    };
    QItem* front, *rear;
    unsigned size;
    void Erase();
    void Clone(const DQueue<InfoType>&);
    void* PtrByIndex(unsigned k) const;
public:
    DQueue() : front(NULL), rear(NULL), size(0) {};
    DQueue(const DQueue<InfoType>&);
    ~DQueue();
    DQueue<InfoType>& operator = (const DQueue<InfoType>&);

    void Push(InfoType AInfo);
    void InsertFront(InfoType AInfo);
    bool Pop();
    bool PopEnd();
    
    InfoType GetFirst() const;
    InfoType GetLast() const;
    bool IsEmpty() const;
    unsigned GetSize() const;

    InfoType operator [] (unsigned) const;
    const InfoType& GetByIndex(unsigned) const;
    void SetByIndex(InfoType AInfo, unsigned k);
    void BrowseForward(void ItemWork(InfoType)) const;
    void BrowseForward(void ItemWork(InfoType&));

    void BrowseBackwards(void ItemWork(InfoType)) const;
    void BrowseBackwards(void ItemWork(InfoType&));

    ostream& WriteToStreamFrontToRear(ostream& s);
    ostream& WriteToStreamRearToFront(ostream& s);

    /*friend ostream& operator << (ostream& s, const DQueue<InfoType>&);*/
};

template <>
DQueue<const char*>::QItem::QItem(const char* AInfo, QItem* _next, QItem* _prev) : next(_next), prev(_prev)
{
    info = new char[strlen(AInfo) + 1];
    strcpy((char*)info, AInfo);
}

#endif