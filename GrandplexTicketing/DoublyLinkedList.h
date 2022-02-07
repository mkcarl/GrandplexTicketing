#include <iostream>
using namespace std; 
#pragma once

template <typename T>
struct node
{
	T data;
	node<T>* next;
	node<T>* prev;
};

template <typename T>
class DoublyLinkedList
{
	node<T>* head;
	node<T>* tail;
	int size;

	node<T>* createNode(T data)
	{
		node<T>* newNode = new node<T>();
		newNode->next = nullptr;
		newNode->prev = nullptr;
		newNode->data = data;
		return newNode;
	}

public:
	DoublyLinkedList()
	{
		// constructor - instantiating the linked list
		head = tail = nullptr;
		size = 0;
	}

	int getSize()
	{
		return this->size;
	}

	node<T>* getHead()
	{
		return this->head;
	}

	node<T>* getTail()
	{
		return this->tail;
	}

	void addToFront(T data)
	{
		node<T>* newNode = createNode(data);

		if (this->head == nullptr)
		{
			this->head = this->tail = newNode;
		}
		else
		{
			newNode->next = this->head;
			this->head->prev = newNode;
			this->head = newNode;
		}
		++this->size;
	}

	void addToEnd(T data)
	{
		node<T>* newNode = createNode(data);

		if (this->head == nullptr)
		{
			this->head = this->tail = newNode; 
		}
		else
		{
			this->tail->next = newNode;
			newNode->prev = this->tail;
			this->tail = newNode; 
		}
		++this->size;
	}

	void deleteFromFront()
	{
		if (this->head == nullptr)
		{
			throw out_of_range("List is empty!");
		}

		node<T>* temp = this->head; 
		this->head = this->head->next; //set the head to the second element
		this->head->prev = nullptr; // set the prev pointer of head to null
		delete temp; 

		--this->size;
	}

	void deteleFromEnd()
	{
		if (this->head == nullptr)
		{
			throw out_of_range("List is empty!");
		}

		node<T>* temp = this->tail;
		this->tail = this->tail->prev; //set the tail to the second last element
		this->tail->next = nullptr; // set the next pointer of tail to null
		delete temp;

		--this->size;
	}

	static DoublyLinkedList mergeSort(DoublyLinkedList list)
	{ 
		// returns a sorted list, does not sort the list itself
	}

	void display()
	{
		// mainly for debugging purposes
		cout << "[";
		node<T>* current = this->head; 
		while (current != nullptr)
		{
			cout << current->data;
			if (current->next != nullptr)
				cout << ", ";
			current = current->next; 
		}
		cout << "]" << endl ;
	}
};
