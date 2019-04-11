#pragma once

#include "ListExceptions.h"
#include <iso646.h>		

template <typename Type>
class List 
{

    class Node
	{
        Node* prev;
        Node* next;
        Type data;

        explicit Node(const Type& data);
        template <typename ...Args>
        Node(Args...args);

    public:
        ~Node() = default;
        friend class List;
    };

public:
	class iterator
	{
		Node* current;
		
	public:

		iterator& operator++ (); // prefix
		iterator operator++ (int); // postfix
		iterator& operator-- ();
		iterator operator-- (int);
		bool operator== (const iterator& right);
		bool operator!= (const iterator& right);		
		iterator& operator= (const iterator& right);
		Type& operator* () { return current->data; }

		iterator(const iterator& original) { current = original.current; }
		iterator(Node* set) { current = set; }
		iterator() { current = nullptr; }
		~iterator() = default;
	};

private:
    Node* begin_;
    Node* end_;

    int size;

    public:  bool IsEmpty() const { return size == 0; }
             int Len() const { return this->size; }
             bool IsInRange(int n) const { return n >= 0 and n < size; }
			 iterator begin() { return iterator(begin_); }
			 iterator end() { return iterator(end_); }

	friend class listIterator;

    public:  void PushBack(const Type& toPush);
    private: void GenericPushBack(const Type& toPush);
    public:  void PushFront(const Type& toPush);
    private: void GenericPushFront(const Type& toPush);
    private: void PushIfEmpty(const Type& toPush);

    public:  void PopBack();
    private: void GenericPopBack();
    public:  void PopFront();
    private: void GenericPopFront();
    private: void PopIfOneLast();

    public:  template <typename ...Args>
             void EmplaceBack(Args...args);
    private: template <typename ... Args>
             void GenericEmplacBack(Args ... args);
    public:  template <typename ...Args>
             void EmplaceFront(Args...args);
    private: template <typename ... Args>
             void GenericEmplacFront(Args ... args);
    private: template <typename ... Args>
             void EmplaceIfEmpty(Args ... args);

    public:  Type& operator [] (int n);
    private: Type& Find(int n);
    private: Type& SearchFromFront(int n);
    private: Type& SearchFromBack(int n);

    public:  List();
    public: ~List();
    private: void Flush();

}; // List


template <typename Type>
void List<Type>::PushBack(const Type& toPush) 
{

    if (this->IsEmpty())
        this->PushIfEmpty(toPush);
    else
        this->GenericPushBack(toPush);

}


template <typename Type>
template <typename ... Args>
void List<Type>::EmplaceBack(Args...args) 
{

    if (this->IsEmpty())
        this->EmplaceIfEmpty(args...);
    else
        this->GenericEmplacBack(args...);

}


template <typename Type>
void List<Type>::PushFront(const Type &toPush) 
{

    if (this->IsEmpty())
        this->PushIfEmpty(toPush);
    else
        this->GenericPushFront(toPush);

}


template <typename Type>
template <typename ... Args>
void List<Type>::EmplaceFront(Args...args) 
{

    if (this->IsEmpty())
        this->EmplaceIfEmpty(args...);
    else
        this->GenericEmplacFront(args...);

}


template <typename Type>
void List<Type>::PopBack()
{

    if (this->size == 1)
        this->PopIfOneLast();
    else
        this->GenericPopBack();

}


template <typename Type>
void List<Type>::PopFront() 
{
    if (this->size == 1)
        this->PopIfOneLast();
    else
        this->GenericPopFront();
}


template <typename Type>
Type& List<Type>::operator [](int n)
{
    if (IsInRange(n))
        return Find(n);
    else
        throw OutOfRangeException();
}


template <typename Type>
Type& List<Type>::Find(int n)
{
    if (n >= this->size / 2.)
        return SearchFromBack(n);
    else
        return SearchFromFront(n);
}


template <typename Type>
Type& List<Type>::SearchFromFront(int n) {

    Node* iter = begin_;
    for (auto i = 0; i != n; i ++)
        iter = iter->next;

    return iter->data;
}


template <typename Type>
Type& List<Type>::SearchFromBack(int n) {

    Node* iter = this->end_;
    for (auto i = this->size - 1; i != n; --i)
        iter = iter->prev;

    return iter->data;
}


template <typename Type>
void List<Type>::PushIfEmpty(const Type& toPush)
{
    auto newNode = new Node(toPush);
    this->begin_ = this->end_ = newNode;
    ++this->size;
}


template <typename Type>
void List<Type>::GenericPushBack(const Type& toPush)
{
    auto newNode = new Node(toPush);
    newNode->prev = this->end_;
    this->end_->next = newNode;
    this->end_ = newNode;
    ++this->size;
}


template <typename Type>
void List<Type>::GenericPushFront(const Type &toPush)
{
    auto newNode = new Node(toPush);
    newNode->next = this->begin_;
    this->begin_->prev = newNode;
    this->begin_ = newNode;
    ++this->size;
}


template <typename Type>
void List<Type>::PopIfOneLast() 
{
    delete this->begin_;
    this->begin_ = nullptr;
    this->end_ = nullptr;
    this->size = 0;
}


template <typename Type>
void List<Type>::GenericPopBack()
{
    auto toDelete = this->end_;
    this->end_ = this->end_->prev;
    this->end_->next = nullptr;
    delete toDelete;
    --this->size;
}


template <typename Type>
void List<Type>::GenericPopFront()
{
    auto toDelete = this->begin_;
    this->begin_->next->prev = nullptr;
    this->begin_ = this->begin_->next;
    delete toDelete;
    --this->size;
}


template <typename Type>
template <typename ...Args>
void List<Type>::EmplaceIfEmpty(Args... args) 
{
    auto newNode = new Node(args...);
    this->begin_ = this->end_ = newNode;
    ++this->size;
}


template <typename Type>
template <typename ...Args>
void List<Type>::GenericEmplacBack(Args... args)
{
    auto newNode = new Node(args...);
    newNode->prev = this->end_;
    this->end_->next = newNode;
    this->end_ = newNode;
    ++this->size;
}


template <typename Type>
template <typename ...Args>
void List<Type>::GenericEmplacFront(Args... args) 
{
    auto newNode = new Node(args...);
    newNode->next = this->begin_;
    this->begin_->prev = newNode;
    this->begin_ = newNode;
    ++this->size;
}


template <typename Type>
List<Type>::List() 
{
    this->begin_ = nullptr;
    this->end_ = nullptr;
    this->size = 0;
}


template <typename Type>
List<Type>::~List() 
{
    if (this->size == 1)
        this->PopIfOneLast();
    else if (this->size != 0)
        this->Flush();
}


template <typename Type>
void List<Type>::Flush()
{
    Node* iter = this->end_;
    while (iter != this->begin_) {

        Node* toDelete = iter;
        iter = iter->prev;
        delete toDelete;
    }
    this->PopIfOneLast();
}


template <typename Type>
typename List<Type>::iterator& List<Type>::iterator::operator++()
{
	if (current->next != nullptr)
		current = current->next;
	return *this;
}


template <typename Type>
typename List<Type>::iterator List<Type>::iterator::operator++(int)
{
	auto toReturn = List<Type>::iterator(*this);
	if (current->next != nullptr)
		current = current->next;
	return toReturn;
}


template <typename Type>
typename List<Type>::iterator& List<Type>::iterator::operator--()
{
	if (current->prev != nullptr)
		current = current->prev;
	return  *this;
}


template <typename Type>
typename List<Type>::iterator List<Type>::iterator::operator--(int)
{
	auto toReturn = List<Type>::iterator(*this);
	if (current->prev != nullptr)
		current = current->prev;
	return toReturn;
}


template <typename Type>
bool List<Type>::iterator::operator==(const iterator& right)
{
	return current == right.current;
}


template <typename Type>
bool List<Type>::iterator::operator!=(const iterator& right)
{
	return current != right.current; 	
}


template <typename Type>
typename List<Type>::iterator& List<Type>::iterator::operator=(const iterator& right)
{
	current = right.current;
	return *this;
}


template <typename Type>
List<Type>::Node::Node(const Type& data) : data(data)
{
	next = nullptr;
	prev = nullptr;
}


template <typename Type>
template <typename ...Args>
List<Type>::Node::Node(Args... args) : data(args...)
{
	next = nullptr;
	prev = nullptr;
}
