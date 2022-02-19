#include <iostream>
using namespace std;
#pragma once

template <typename T>
struct node
{
	T data;
	node<T>* next;
	node<T>* prev;

	auto valueOfData();
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

	node<T>* merge(node<T>* first, node<T>* second)
	{
		// If first linked list is empty
		if (!first)
			return second;

		// If second linked list is empty
		if (!second)
			return first;

		// Pick the smaller value
		if ((*first).valueOfData() < (*second).valueOfData())
		{
			first->next = merge(first->next, second);
			first->next->prev = first;
			first->prev = NULL;
			return first;
		}
		else
		{
			second->next = merge(first, second->next);
			second->next->prev = second;
			second->prev = NULL;
			return second;
		}
	}

	node<T>* split(node<T>* head)
	{
		node<T>* fast = head, * slow = head;
		while (fast->next && fast->next->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		node<T>* temp = slow->next;
		slow->next = NULL;
		return temp;
	}

	node<T>* _mergeSort(node<T>* head)
	{
		if (!head || !head->next)
			return head;
		node<T>* second = split(head);

		// Recur for left and right halves
		head = _mergeSort(head);
		second = _mergeSort(second);

		// Merge the two sorted halves
		return merge(head, second);
	}


public:
	DoublyLinkedList()
	{
		// constructor - instantiating the linked list
		head = tail = nullptr;
		size = 0;
		currentPosition = 0;
		currentNode = nullptr;
	}

	DoublyLinkedList(const DoublyLinkedList& other)
	{
		if (other.head == nullptr)
		{
			head = tail = nullptr;
			return; 
		}

		node<T>* temp = other.head;

		head = tail = new node<T>;
		head->data = T(temp->data);
		head->next = nullptr;
		head->prev = nullptr;
		currentNode = head;

		temp = temp->next;

		while (temp!=nullptr)
		{
			currentNode->next = new node <T>;
			currentNode->next->prev = currentNode;
			currentNode = currentNode->next;
			currentNode->data = T(temp->data);
			currentNode->next = nullptr;
			tail = temp; 
			temp = temp->next;
		}
		currentNode = nullptr;
		currentPosition = 0;
		size = other.size; 

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
		if (this->head == this->tail)
		{
			this->head = nullptr;
			this->tail = nullptr;
		}
		else
		{
			this->head = this->head->next; //set the head to the second element
			this->head->prev = nullptr; // set the prev pointer of head to null
		}
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
		if (this->head == this->tail)
		{
			this->head = nullptr;
			this->tail = nullptr; 
		}
		else
		{
			this->tail = this->tail->prev; //set the tail to the second last element
			this->tail->next = nullptr; // set the next pointer of tail to null
		}
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
		//cout << index << endl;
		if (index >= this->size)
		{
			throw out_of_range("Index out of bound!");
		}
		if (this->head == nullptr)
		{
			throw out_of_range("List is empty!");
		}
		
		node<T>* current = this->head;

		if (index == 0)
		{
			currentNode = head->next;
			deleteFromFront();
		}
		else if (index == this->size - 1)
		{
			currentNode = tail->prev;
			--currentPosition;
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
			if (this->currentNode == current)
			{
				this->currentNode = this->currentNode->next;
			}
			delete current;
			--this->size;
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
			else if (index < currentPosition)
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
		cout << "]" << endl;
	}

	void mergeSort()
	{
		this->head = _mergeSort(this->head);

		node<T>* temp = this->head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		this->tail = temp; 
	}

};