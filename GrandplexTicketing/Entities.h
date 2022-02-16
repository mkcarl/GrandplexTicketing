#pragma once
#include <iostream>
#include "DoublyLinkedList.h"
using namespace std; 

struct Movie
{
	int movie_id;
	string title;
	double duration;
	string genre;
	int rating;
	string air_time;
	int air_hour;
	int air_min;

	int number_of_available_seats;

	friend ostream& operator<<(ostream& os, const Movie& dt)
	{
		os << "{" << dt.movie_id << ", " << dt.title << "}";
		return os;
	}

};

struct Seat
{
	int row;
	char column;
};

struct Ticket
{
	int ticket_id;
	Seat seat;
	Movie movie;
	double price; 
};


struct Transaction
{
	int transaction_id;
	int day;
	int month;
	int year;
	string payment_method; 
	DoublyLinkedList<Ticket> list_of_tickets;

	friend ostream& operator<<(ostream& os, Transaction& dt)
	{
		os << "{" << dt.transaction_id << ", " << dt.day << "/" << dt.month << "/" << dt.year << ", " << dt.list_of_tickets.getSize() << "}";
		return os;
	}

};