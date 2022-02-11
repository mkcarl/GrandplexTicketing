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

	int currentPosition = 0;
	node<T>* currentNode = nullptr;

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

	void deleteFromEnd()
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

	void addAtIndex(T data, int index) 
	{
		// 0 based index
		if (index > this->size)
		{
			throw out_of_range("Index out of bound!");
		}

		node<T>* newNode = createNode(data);

		node<T>* current = this->head;

		if (this->head == nullptr)
		{
			this->head = this->tail = newNode;
		}
		else if (index == 0)
		{
			addToFront(data);
		}
		else if (index == this->size)
		{
			addToEnd(data);
		}
		else
		{
			for (int i = 0; i < index - 1; ++i)
			{
				current = current->next;
			}
			current->next->prev = newNode;
			newNode->next = current->next;
			newNode->prev = current;
			current->next = newNode; 
		}
		++this->size;
	}

	void deleteAtIndex(int index)
	{
		if (index >= this->size)
		{
			throw out_of_range("Index out of bound!");
		}
		if (this->head == nullptr)
		{
			throw out_of_range("List is empty!");
		}
		int i = 0;
		node<T>* current = this->head;

		if (index == 0)
		{
			deleteFromFront();
		}
		else if (index == this->size - 1)
		{
			deleteFromEnd();
		}
		else
		{
			for (int i = 0; i < index; ++i)
			{
				current = current->next; 
			}
			current->prev->next = current->next;
			current->next->prev = current->prev;
			delete current; 
		}
	}

	T* getAtIndex(int index)
	{
		if (currentNode == nullptr)
		{
			currentNode = this->head;
			currentPosition = index;
			for (int i = 0; i < index; ++i)
			{
				currentNode = currentNode->next; 
			}
		}
		else
		{
			if (index > currentPosition)
			{
				int j = index - currentPosition;
				for (int i = 0; i < j; ++i)
				{
					currentNode = currentNode->next;
					++currentPosition;
				}
			}
			else
			{
				int j = currentPosition - index;
				for (int i = 0; i < j; ++i)
				{
					currentNode = currentNode->prev;
					--currentPosition;
				}
			}
		}
		return &currentNode->data;
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
