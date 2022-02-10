#include <iostream>
#include <string>
#include <iomanip>
#include "DoublyLinkedList.h"
#include "Entities.h"
using namespace std;

// helper function to print title of the page
// no real functionality, just nicer print
void print_title(string text)
{
	const int LENGTH = 50;
	cout << string(LENGTH, '*') << endl;
	if (text.size()%2 ==0)
		cout << left << setw((LENGTH - text.size()) / 2) << "*" << text << right << setw((LENGTH - text.size()) / 2) << "*" << endl; 
	else
		cout << left << setw((LENGTH - text.size()) / 2) << "*" << text << right << setw((LENGTH - text.size()) / 2 + 1) << "*" << endl;
	cout << string(LENGTH, '*') << endl;

}

// linked list for the entities, whole program only uses this 2 linked list 
DoublyLinkedList<Movie> movie_list = DoublyLinkedList<Movie>();
DoublyLinkedList<Transaction> transaction_list = DoublyLinkedList<Transaction>();


// hard coded sample data
void createDummyData()
{
	string titles[] = { "Spiderman: No way home", "Avengers : End game", "Titanic", "Chucky", "KongFu Hustle", "Frozen" };
	double durations[] = { 3, 2.5, 1.5, 1.5, 1.5, 1 };
	string genres[] = { "Action","Action","Romance","Horror","Comedy","Cartoon" };
	int ratings[] = { 5,5,3,1,3,1 };
	string airtimes[] = { "0900", "1200", "1100", "1130", "2300", "0200" };

	for (int i = 0; i < 6; ++i)
	{
		Movie newMovie = Movie();
		newMovie.movie_id = i;
		newMovie.title = titles[i];
		newMovie.duration = durations[i];
		newMovie.genre = genres[i];
		newMovie.rating = ratings[i];
		newMovie.air_time = airtimes[i];
		newMovie.number_of_available_seats = 100;
		movie_list.addToEnd(newMovie);
	}

	int days[] = { 12,23,30,5,23 };
	int months[] = { 1,2,3,4,5,6 };
	string methods[] = { "Cash","Cash", "Cash", "E-wallet", "Credit Card","Credit Card" };
	string seats[] = { "A1", "B1", "B9", "B10", "J4", "D4", "D5", "D6", "D7", "A3","D3", "A7" };
	DoublyLinkedList<Ticket> lists[6];
	for (int i = 0; i < 6; ++i)
	{
		Seat seat = Seat();
		seat.column = seats[i][0];
		seat.row = seats[i][1] - '0';

		Ticket tix = Ticket();
		tix.ticket_id = i;
		tix.seat = seat;
		tix.movie = *movie_list.getAtIndex(i);
		(movie_list.getAtIndex(i)->number_of_available_seats)--;
		tix.price = 13;
		DoublyLinkedList<Ticket> ls = DoublyLinkedList<Ticket>();
		ls.addToEnd(tix);
		lists[i] = ls;
	}
	for (int i = 0; i < 5; ++i)
	{
		Transaction t = Transaction();
		t.transaction_id = i;
		t.day = days[i];
		t.month = months[i];
		t.year = 2021;
		t.payment_method = methods[i];
		t.list_of_tickets = lists[i];
		transaction_list.addToEnd(t);
	}
	Seat s1 = Seat();
	s1.column = 'J';
	s1.row = 10;
	Ticket tix1 = Ticket();
	tix1.seat = s1;
	tix1.movie = movie_list.getHead()->data;
	tix1.price = 13;
	tix1.ticket_id = 7;
	transaction_list.getTail()->data.list_of_tickets.addToEnd(tix1);

	//movie_list.display();
	//transaction_list.display();
}

int main()
{
	createDummyData();
}

int main1(int argc, char* argv[])
{
	// main program loop
	// hard coded login
	string username;
	string password;

	print_title("Welcome to Grandplex Cinema");

	bool is_logged_in = false;
	while(!is_logged_in)
	{
		cout << "Username : ";
		getline(cin, username);
		cout << "Password : ";
		getline(cin, password);
		if (username == "admin" && password == "123")
		{
			is_logged_in = true; // breaks the loop 
			cout << endl << "Login successful!" << endl;
			system("pause");
			system("cls");
			break;
		}
		cout << endl << "Invalid credentials! Please try again.." << endl;
	}

	// main menu
	bool menu_loop = true;

	while (menu_loop)
	{
		print_title("Main menu");
		cout << "Please choose the function to execute." << endl;

		cout << "1. Add new movie" << endl
			<< "2. Display all movie" << endl
			<< "3. Search movie by movie name" << endl
			<< "4. Filter movie by genre" << endl
			<< "5. Edit movie details" << endl
			<< "6. Sort movie by available seats" << endl
			<< "7. Delete movie" << endl
			<< "8. Add new transaction" << endl
			<< "9. Display all transactions" << endl
			<< "10. Sort transaction by purchase amount" << endl
			<< "11. Show specific transaction details" << endl
			<< "12. Log out" << endl;

		int choice = 0;

		while (true)
		{
			cout << "Please input your choice (1-12) : ";
			cin >> choice;

			if (cin.fail())
			{
				cout << "Invalid input! Please type numbers only!" << endl << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			switch (choice)
			{
			case 1:
				/*
				 * Functionality : Add movie
				 * Responsible : Hor Shen Hau
				 *
				 * follow what you have did in your flow chart
				 * for product details (movie details), refer to the Entities.h file and see what attributes needed for Movie
				 *
				 * *Queue idea*
				 * for inserting, just use the function from movie_list.addToEnd()
				 * for deletion, just use function movie_list.deleteFromFront()
				 */
				system("pause"); system("cls");
				break;
			case 2:
				/*
				 * Functionality : Display all movie
				 * Responsible : Yan Mun Kye
				 *
				 * DO NOT follow flow chart
				 * ditch the idea that have advance option
				 * just show everything in the list and done
				 *
				 * additional idea : format the output into a tabular format

				 */
				system("pause"); system("cls");
				break;
			case 3:
				/*
				 * Functionality : Search movie by name 
				 * Responsible : Tan Sheng Jeh
				 *
				 * follow flow chart, EXCEPT, after found the product, no need to prompt if the user wan to search another item,
				 * just go straight back to the main menu
				 *

				 */
				system("pause"); system("cls");
				break;
			case 4:
				/*
				 * Functionality : Filter movie by genre
				 * Responsible : Hor Shen Hau
				 *
				 * follow flow chart
				 * when prompting for the genre,
				 * i think its better to have the users to select 1,2,3,4,5 instead of them typing literally "Horror" (possible typo)
				 * however, for the initial implementation, just do the latter first, the former might need to introduce a new variable, ask mk when in doubt
				 *
				 */
				system("pause"); system("cls");
				break;
			case 5:
				/*
				 * Functionality : Edit movie details
				 * Responsible : Yan Mun Kye
				 *
				 * follow flow chart
				 */
				system("pause"); system("cls");
				break;
			case 6:
				/*
				 * Functionality : Sort movie by available seats
				 * Responsible : Tan Sheng Jeh
				 *
				 * follow flow chart.. but dont need to ask them so many things, after they click this function,
				 * just print out the sorted list thats all (maybe can ask them if they wan ascending or descending) 
				 *
				 * Note : i think its best NOT to sort the original list, maybe create a new temp list, then sort the temp list. 
				 */
				// ori = [3,2,6,4,9]
				// sorted = sort(ori)
				// print(ori) -> [2,3,4,6,9]
				// print(sorted) -> [2,3,4,6,9]

				//instead, use this 
				// sorted = sort(ori)
				// print(ori) -> [3,2,6,4,9]
				// print(sorted) -> [2,3,4,6,9]

				system("pause"); system("cls");
				break;
			case 7:
				/*
				 * Functionality : Delete movie
				 * Responsible : Tan Sheng Jeh
				 *
				 * follow flow chart
				 * but for the actual delete part, no need to go through the list one by one, just use the function to delete at specific index.
				 * user input : 3
				 */
				system("pause"); system("cls");
				break;
			case 8:
				/*
				 * Functionality : Add new transaction 
				 * Responsible : Yan Mun Kye
				 *
				 * follow flow chart, but in the end no need to ask if they want to make another purchase, just go straight back to main menu
				 * also need to ask them the seat they want, which you also need to check if the particular seat is available
				 * also for this particular function, when inserting, will insert to sorted list (sorted by transaction ID) 
				 */

				system("pause"); system("cls");
				break;
			case 9:
				/*
				 * Functionality : Show all transactions
				 * Responsible : Hor Shen Hau
				 *
				 * follow flow chart, but don't need for advance feature, just print all and thats it
				 *
				 * additional idea : maybe format the output as a table
				 */
				system("pause"); system("cls");
				break;
			case 10:
				/*
				 * Functionality : Sort transaction by purchase amount
				 * Responsible : Yan Mun Kye
				 *
				 * follow flow chart
				 * maybe can ask them if want ascend or descend
				 * use merge sort 
				 */
				system("pause"); system("cls");
				break;
			case 11:
				/*
				 * Functionality : Show Specific Transaction Detail
				 * Responsible : Tan Sheng Jeh
				 *
				 * follow flow chart
				 * but i think can just show users the list of all transction, then straight ask which details they want to see
				 * DO ask if they want to repeat the same action. 
				 */
				system("pause"); system("cls");
				break;
			case 12:
				menu_loop = false;
				cout << "You have been logged out..." << endl; 
				system("pause"); system("cls");
				break;
			default:
				cout << "Invalid choice.. Please try again.." << endl << endl;
				continue;
			}


			break; // break from the choice loop
		}
	}
	return 0; 
}
