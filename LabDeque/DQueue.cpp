#include "DQueue.h"

template <typename InfoType>
void DQueue<InfoType>::Erase()
{
    while (Pop());
    size = 0;
}

template <typename InfoType>
void DQueue<InfoType>::Clone(const DQueue<InfoType>& Q)
{
    QItem* tmp = Q.front;
    for (unsigned i = 0; i < Q.size; i++)
    {
        Push(tmp->info);
        tmp = tmp->next;
    }
}

template<typename InfoType>
void* DQueue<InfoType>::PtrByIndex(unsigned k) const
{
    if (k < 0 || k >(size - 1))
    {
        throw exception("Impossible to obtain Dqueue item: wrong index.");
    }
    QItem* tmp = front;
    for (unsigned i = 0; i < k; i++)
    {
        tmp = tmp->next;
    }
    return tmp;
}

template <typename InfoType>
DQueue<InfoType>::DQueue(const DQueue<InfoType>& Q)
{
    size = 0;
    Clone(Q);
}

template <typename InfoType>
DQueue<InfoType>::~DQueue()
{
    Erase();
}

template <typename InfoType>
DQueue<InfoType>& DQueue<InfoType>::operator=(const DQueue<InfoType>& Q)
{
    if (this != &Q)
    {
        Erase();
        Clone(Q);
    }
    return (*this);
}

template <typename InfoType>
void DQueue<InfoType>::Push(InfoType Ainfo)
{
    QItem* tmp = new QItem(Ainfo,NULL,rear);
    if (size > 0)
    {
        rear->next = tmp;

    }
    else
    {
        front = tmp;
    }
    rear = tmp;
    size++;
}

template<typename InfoType>
void DQueue<InfoType>::InsertFront(InfoType AInfo)
{
    QItem* tmp = new QItem(AInfo,front,NULL);
    front = tmp;
    size++;
}

template <typename InfoType>
bool DQueue<InfoType>::Pop()
{
    if (size == 0)
    {
        return false;
    }
    QItem* tmp = front;
    front = front->next;
    delete tmp;
    size--;
    if (size == 0)
    {
        rear = NULL;
    }
    return true;
}

template <>
bool DQueue<const char*>::Pop()
{
    if (size == 0)
    {
        return false;
    }
    QItem* tmp = front;
    front = front->next;
    delete[](tmp->info);
    delete tmp;
    size--;
    if (size == 0)
    {
        rear = NULL;
    }
    return true;
}

template <typename InfoType>
bool DQueue<InfoType>::PopEnd()
{
    if (size == 0)
    {
        return false;
    }
    QItem* tmp = rear;
    rear = rear->prev;
    delete tmp;
    size--;
    if (size == 0)
    {
        front = NULL;
    }
    return true;
}

template <>
bool DQueue<const char*>::PopEnd()
{
    if (size == 0)
    {
        return false;
    }
    QItem* tmp = front;
    front = front->next;
    delete[] tmp->info;
    delete tmp;
    size--;
    if (size == 0)
    {
        front = NULL;
    }
    return true;
}

template <typename InfoType>
InfoType DQueue<InfoType>::GetFirst() const
{
    if (size == 0)
    {
        throw exception("");
    }
    else
    {
        return front->info;
    }
}

template <typename InfoType>
InfoType DQueue<InfoType>::GetLast() const
{
    if (size == 0)
    {
        throw exception("");
    }
    else
    {
        return rear->info;
    }
}

template <typename InfoType>
bool DQueue<InfoType>::IsEmpty() const
{
    return (size == 0);
}

template <typename InfoType>
unsigned DQueue<InfoType>::GetSize() const
{
    return size;
}

template <typename InfoType>
InfoType DQueue<InfoType>::operator[](unsigned k) const
{
    if ((k < 0) || (k >= size))
    {
        throw exception("Impossible to execute \
            operator[]: invalid index");
    }
    if (typeid(InfoType) == typeid(const char*))
    {
        throw exception("Using of [] operator is prohibited with const char* type. \
        Use SetByIndex or GetByIndex instead.");
        return (InfoType&)((QItem*)PtrByIndex(k));
    }
    QItem* tmp = front;
    for (unsigned i = 0; i < k; i++)
    {
        tmp = tmp->next;
    }
    return tmp->info;
}

template <typename InfoType>
const InfoType& DQueue<InfoType>::GetByIndex(unsigned k) const
{
    /*if ((k < 0) || (k >= size))
    {
        throw exception("Impossible to execute \
            operator[]: invalid index");
    }
    QItem* tmp = front;
    for (unsigned i = 0; i < k; i++)
    {
        tmp = tmp->next;
    }
    return tmp->info;*/
    return ((QItem*)PtrByIndex(k))->info;
    
}

template <typename InfoType>
void DQueue<InfoType>::SetByIndex(InfoType AInfo, unsigned k)
{
    /*if ((k < 0) || (k >= size))
    {
        throw exception("Impossible to execute \
            operator[]: invalid index");
    }
    QItem* tmp = front;
    for (unsigned i = 0; i < k; i++)
    {
        tmp = tmp->next;
    }*/
   ((QItem*)PtrByIndex(k))->info = AInfo;
}

template <>
void DQueue<const char*>::SetByIndex(const char* AInfo, unsigned k)
{
    /*if ((k < 0) || (k >= size))
    {
        throw exception("Impossible to execute \
            operator[]: invalid index");
    }
    QItem* tmp = front;
    for (unsigned i = 0; i < k; i++)
    {
        tmp = tmp->next;
    }*/
    char* currInfo = (char*)((QItem*)PtrByIndex(k))->info;
    delete[] currInfo;
    currInfo = new char[strlen(AInfo) + 1];
    strcpy(currInfo, AInfo);
    ((QItem*)PtrByIndex(k))->info = currInfo;
}

template <typename InfoType>
void DQueue<InfoType>::BrowseForward(void ItemWork(InfoType)) const
{
    if (typeid(InfoType) == typeid(const char*))
    {
        throw exception("Using of Browse is prohibited with const char* type.");
    }
    QItem* tmp = front;
    for (unsigned i = 0; i < size; i++)
    {
        ItemWork(tmp->info);
        tmp = tmp->next;
    }
}

template <typename InfoType>
void DQueue<InfoType>::BrowseForward(void ItemWork(InfoType&))
{
    if (typeid(InfoType) == typeid(const char*))
    {
        throw exception("Using of [] operator is prohibited with const char* type. \
        Use SetByIndex or GetByIndex instead.");
    }
    QItem* tmp = front;
    for (unsigned i = 0; i < size; i++)
    {
        ItemWork(tmp->info);
        tmp = tmp->next;
    }
}

template <typename InfoType>
void DQueue<InfoType>::BrowseBackwards(void ItemWork(InfoType)) const
{
    if (typeid(InfoType) == typeid(const char*))
    {
        throw exception("Using of Browse is prohibited with const char* type.");
    }
    QItem* tmp = rear;
    for (unsigned i = size - 1; i >= 0; i--)
    {
        ItemWork(tmp->info);
        tmp = tmp->prev;
    }
}

template <typename InfoType>
void DQueue<InfoType>::BrowseBackwards(void ItemWork(InfoType&))
{
    if (typeid(InfoType) == typeid(const char*))
    {
        throw exception("Using of [] operator is prohibited with const char* type. \
        Use SetByIndex or GetByIndex instead.");
    }
    QItem* tmp = rear;
    for (unsigned i = size - 1; i >= 0; i--)
    {
        ItemWork(tmp->info);
        tmp = tmp->prev;
    }
}

template<typename InfoType>
ostream& DQueue<InfoType>::WriteToStreamFrontToRear(ostream& s)
{
    if (size == 0)
    {
        return s;
    }
    for (unsigned i = 0; i < size; i++)
    {
        s << "^ " << GetByIndex(i) << "\n";
    }
    return s;
}

template<typename InfoType>
ostream& DQueue<InfoType>::WriteToStreamRearToFront(ostream& s)
{
    if (size == 0)
    {
        return s;
    }
    for (int i = size - 1; i >= 0; i--)
    {
        s << "v " << GetByIndex(i) << "\n";
    }
    return s;
}


//template<typename InfoType>
//ostream& operator<<(ostream& s, const DQueue<InfoType>& q)
//{
//    
//}
