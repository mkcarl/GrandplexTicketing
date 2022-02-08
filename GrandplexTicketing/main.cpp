#include <iostream>
#include <string>
#include <iomanip>
#include "DoublyLinkedList.h"
#include "Entities.h"
using namespace std;

// helper function to print title of the page
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


int main(int argc, char* argv[])
{
	// linked list for the entities, whole program only uses this 2 linked list 
	DoublyLinkedList<Movie> movie_list = DoublyLinkedList<Movie>();
	DoublyLinkedList<Transaction> transaction_list = DoublyLinkedList<Transaction>();

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
				system("pause"); system("cls");
				break;
			case 2:
				system("pause"); system("cls");
				break;
			case 3:
				system("pause"); system("cls");
				break;
			case 4:
				system("pause"); system("cls");
				break;
			case 5:
				system("pause"); system("cls");
				break;
			case 6:
				system("pause"); system("cls");
				break;
			case 7:
				system("pause"); system("cls");
				break;
			case 8:
				system("pause"); system("cls");
				break;
			case 9:
				system("pause"); system("cls");
				break;
			case 10:
				system("pause"); system("cls");
				break;
			case 11:
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

	


}
