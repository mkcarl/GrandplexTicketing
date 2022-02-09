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


int main(int argc, char* argv[])
{
	// linked list for the entities, whole program only uses this 2 linked list 
	DoublyLinkedList<Movie> movie_list = DoublyLinkedList<Movie>();
	DoublyLinkedList<Transaction> transaction_list = DoublyLinkedList<Transaction>();

	// hard coded sample data
	// TODO : add code for creating sample data

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
				 * additional idea : format the output into a tabular format

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
				system("pause"); system("cls");
				break;
			case 7:
				/*
				 * Functionality : Delete movie
				 * Responsible : Tan Sheng Jeh
				 *
				 * follow flow chart
				 * but for the actual delete part, no need to go through the list one by one, just use the function to delete at specific index.
				 */
				system("pause"); system("cls");
				break;
			case 8:
				/*
				 * Functionality : Add new transaction 
				 * Responsible : Hor Shen Hau
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
				 * Responsible : Yan Mun Kye
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

	


}
