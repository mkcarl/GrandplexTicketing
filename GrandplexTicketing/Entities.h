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
};

struct Seat
{
	string seat_code; 
};

struct Ticket
{
	int ticket_id;
	Seat seat;
	Movie movie;
	string air_time;
	double price; 

};


struct Transaction
{
	int transaction_id;
	DoublyLinkedList<Ticket> list_of_tickets;
};