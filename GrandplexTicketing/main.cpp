#include <iostream>
#include <string>
#include <iomanip>
#include "DoublyLinkedList.h"
#include "Entities.h"
using namespace std;

// TODO : Add movie (airtime validation delim prob)
// TODO : editmovie (air time validation)
// TODO : sort transaction function some FATAL exception 



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
int MOVIE_ID=0, TICKET_ID=0, TRANSACTION_ID=0; 

void print_list()
{
	
	print_title("All movies");
	cout << setw(10) << right << "Movie ID"
		<< " | " << setw(35) << right << "Title"
		<< " | " << setw(15) << right << "Duration (hr)"
		<< " | " << setw(10) << right << "Genre"
		<< " | " << setw(8) << right << "Rating"
		<< " | " << setw(10) << right << "Air Time"
		<< " | " << setw(20) << right << "No. Available Seats"
		<< endl;
	cout << string(130, '-') << endl;
	for (int i = 0; i < movie_list.getSize(); ++i)
	{
		//cout << movie_list.getSize() << endl;
		//Sleep(1000);

		Movie* mov = movie_list.getAtIndex(i);
		cout << setw(10) << right << mov->movie_id
			<< " | " << setw(35) << right << mov->title
			<< " | " << setw(15) << right << mov->duration
			<< " | " << setw(10) << right << mov->genre
			<< " | " << setw(8) << left << string(mov->rating, '*')
			<< " | " << setw(10) << right << mov->air_time
			<< " | " << setw(20) << right << mov->number_of_available_seats
			<< endl;
	}
}

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
		newMovie.movie_id = ++MOVIE_ID;;
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
		tix.ticket_id = ++TICKET_ID;
		tix.seat = seat;
		tix.movie = *movie_list.getAtIndex(i);
		(movie_list.getAtIndex(i)->number_of_available_seats)--;
		tix.price = 13 + i;
		DoublyLinkedList<Ticket> ls = DoublyLinkedList<Ticket>();
		ls.addToEnd(tix);
		lists[i] = ls;
	}
	for (int i = 0; i < 5; ++i)
	{
		Transaction t = Transaction();
		t.transaction_id = ++TRANSACTION_ID;
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
	++TICKET_ID;
	tix1.seat = s1;
	tix1.movie = movie_list.getHead()->data;

	movie_list.getAtIndex(0)->number_of_available_seats--;
	tix1.price = 100;
	tix1.ticket_id = 7;
	transaction_list.getAtIndex(0)->list_of_tickets.addToEnd(tix1);

	//movie_list.display();
	//transaction_list.display();
}

void main1()
{
	DoublyLinkedList<string> ls = DoublyLinkedList<string>();
	ls.addToEnd("Hello");
	ls.addToEnd("World");
	ls.addToEnd("This");
	ls.addToEnd("IS");
	ls.addToEnd("a");
	ls.addToEnd("program");

	cout << *ls.getAtIndex(0) << endl;
	cout << *ls.getAtIndex(2) << endl;
	cout << *ls.getAtIndex(5) << endl;
}

template <>
auto node<Transaction>::valueOfData()
{
	double total = 0;
	for (int i = 0; i < this->data.list_of_tickets.getSize(); ++i)
	{
		Ticket* target = this->data.list_of_tickets.getAtIndex(i);
		total += (*target).price;
	}
	return total;
}

template <>
auto node<Movie>::valueOfData()
{
	return this->data.number_of_available_seats;
}

int main(int argc, char* argv[])
{
	createDummyData();
	// main program loop
	// hard coded login
	node<Transaction>* firstElem = transaction_list.getHead();
	node<Transaction> thirdElem = *firstElem->next->next;
	transaction_list.deleteAtIndex(2);
	transaction_list.addToEnd(thirdElem.data);

	//transaction_list.display();
	//DoublyLinkedList<Transaction> sorted = DoublyLinkedList<Transaction>::mergeSort(transaction_list);
	//sorted.display();
	string username;
	string password;

	print_title("Welcome to Grandplex Cinema");

	bool is_logged_in = false;
	while (!is_logged_in)
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
		string moviename;
		//while (true)
		//{
		cout << "Please input your choice (1-12) : ";
		cin >> choice;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (cin.fail())
			{
				cout << "Invalid input! Please type numbers only!" << endl << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			system("cls");
			
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
			{

				DoublyLinkedList<Movie> movieList = DoublyLinkedList<Movie>();
				print_title("New Movie");
				Movie newMovie = Movie();
				newMovie.movie_id = ++MOVIE_ID;
				node<Movie>* temp = movieList.getTail();
				Movie title;
				Movie duration;
				Movie genre;
				Movie rating;
				Movie air_time;
				Movie air_hour;
				Movie air_min;
				Movie number_of_available_seats;
				//int choice = 0;
				//while (choice == 0)
				do
				{
					while (true) {
						cout << "New Movie Title: ";
						getline(cin, newMovie.title);
						break;
					}
					while (true)
					{

						cout << "Duration in hours(eg 2.5): ";
						cin >> newMovie.duration;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						if (cin.fail()) {
							cout << "Invalid duration inputted, please try again !" << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
						if (newMovie.duration <= 0)
						{
							cout << "Invalid duration inputted, please try again !" << endl;
							continue;
						}
						break;
					}
					while (true)
					{
						string addGenre;
						cout << "Genre: ";
						getline(cin, addGenre);
						addGenre[0] = toupper(addGenre[0]);
						newMovie.genre = addGenre;

						break;
					}
					while (true)
					{
						cout << "Rating (from 1 to 5): ";
						cin >> newMovie.rating;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						if (cin.fail()) {
							cout << "Invalid duration inputted, please try again !" << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
						if (newMovie.rating <= 0 || newMovie.rating > 5)
						{
							cout << "Invalid rating value input, please try again with a value between 1 to 5 ! " << endl;
							continue;
						}
						break;

					}
					while (true)
					{	
						char delimiter = ':';
						cout << "Air time (24 hour format = hr:min): ";
						cin >> newMovie.air_hour >> delimiter >> newMovie.air_min;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						if (cin.fail()) {
							cout << "Invalid time format! Please use (24 hour format = hr:min)" << endl;
							cin.clear();
							continue;
						}
						if (newMovie.air_hour > 23 || newMovie.air_hour < 0 && newMovie.air_min < 0 || newMovie.air_min > 59)
						{
							cout << "Invalid time format input, please check and try again ! Press any key to continue..." << endl << endl;
							continue;
							//no input validation for if "string" is done.
						}
						string combTime = to_string(newMovie.air_hour) + to_string(newMovie.air_min);
						cout << "Time selected is " << setfill('0') << setw(2) << newMovie.air_hour << setw(2) << newMovie.air_min << " hours" << endl << setfill(' ');
						
						newMovie.air_time = combTime;
						break;
						
					}
					newMovie.number_of_available_seats = 100; // by default it has 100 seats
					movie_list.addToEnd(newMovie);
					cout << endl;


					//refer to case 8 add new transaction part for the input validation and continue loop 



					/*
					cout << "Genre: ";
					cin >> newMovie.genre;


					cout << "Rating (1-5): ";
					cin >> newMovie.rating;


					cout << "Air Time (in 24hr format eg:1400): ";
					cin >> newMovie.air_time;

					cout << "Number of available seats (maximum 100): ";
					cin >> newMovie.number_of_available_seats;
					*/
					//int choice = 1;
					break;
					//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				} while (true);


				system("pause"); system("cls");
				break;
			}

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
				//print_title("All movies");
				//cout << setw(10) << right << "Movie ID"
				//	<< " | " << setw(35) << right << "Title"
				//	<< " | " << setw(15) << right << "Duration (hr)"
				//	<< " | " << setw(10) << right << "Genre"
				//	<< " | " << setw(8) << right << "Rating"
				//	<< " | " << setw(10) << right << "Air Time"
				//	<< " | " << setw(20) << right << "No. Available Seats"
				//	<< endl;
				//cout << string(130, '-') << endl;
				////cin.ignore();

			 //for (int i = 0; i < movie_list.getSize(); ++i)
			 //{
			 //	Movie* mov = movie_list.getAtIndex(i);
			 //	cout << setw(10) << right << mov->movie_id
			 //		<< " | " << setw(35) << right << mov->title
			 //		<< " | " << setw(15) << right << mov->duration
			 //		<< " | " << setw(10) << right << mov->genre
			 //		<< " | " << setw(8) << left << string(mov->rating, '*')
			 //		<< " | " << setw(10) << right << mov->air_time
			 //		<< " | " << setw(20) << right << mov->number_of_available_seats
			 //		<< endl;
			 //}
			print_list();
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
			print_title("Search movies");
			cout << "Enter the movie name : ";
			cin >> moviename;
			cout << endl;
			int i;
			cout << setw(10) << right << "Movie ID"
				<< " | " << setw(35) << right << "Title"
				<< " | " << setw(15) << right << "Duration (hr)"
				<< " | " << setw(10) << right << "Genre"
				<< " | " << setw(8) << right << "Rating"
				<< " | " << setw(10) << right << "Air Time"
				<< " | " << setw(20) << right << "No. Available Seats"
				<< endl;
			cout << string(130, '-') << endl;
			for (i = 0; i < movie_list.getSize(); i++)
			{
				Movie* mov = movie_list.getAtIndex(i);
				if (moviename == mov->title)
				{
					cout << setw(10) << right << mov->movie_id
						<< " | " << setw(35) << right << mov->title
						<< " | " << setw(15) << right << mov->duration
						<< " | " << setw(10) << right << mov->genre
						<< " | " << setw(8) << left << string(mov->rating, '*')
						<< " | " << setw(10) << right << mov->air_time
						<< " | " << setw(20) << right << mov->number_of_available_seats
						<< endl;
					break;
				}
			}
			if (i == movie_list.getSize())
			{
				cout << "No such movie found in the list." << endl;
			}

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
				{
				print_title("Filter by Genre");
				string choiceGenre = "";
				cout << "What genre do you want to filter by?: ";
				cin >> choiceGenre;
				//implement input checking for choiceGenre
				choiceGenre[0] = toupper(choiceGenre[0]);
				cout << setw(10) << right << "Movie ID"
						<< " | " << setw(35) << right << "Title"
						<< " | " << setw(15) << right << "Duration (hr)"
						<< " | " << setw(10) << right << "Genre"
						<< " | " << setw(8) << right << "Rating"
						<< " | " << setw(10) << right << "Air Time"
						<< " | " << setw(25) << right << "No. Available Seats"
						<< endl;
				cout << string(130, '-') << endl;
				for (int i = 0;i < movie_list.getSize();++i)
				{
					Movie* mov = movie_list.getAtIndex(i);
					if (choiceGenre == mov->genre)
					{
					cout << setw(10) << right << mov->movie_id
						<< " | " << setw(35) << right << mov->title
						<< " | " << setw(15) << right << mov->duration
						<< " | " << setw(10) << right << mov->genre
						<< " | " << setw(8) << left << string(mov->rating, '*')
						<< " | " << setw(10) << right << mov->air_time
						<< " | " << setw(25) << right << mov->number_of_available_seats
						<< endl;
					}
					/*
					if (choiceGenre != mov->genre && mov->genre == "")
					{
						cout << "No movies for said genre found, please try again" << endl;
					}
					*/

					
				}
				system("pause"); system("cls");
				break;
				}
			case 5:
				/*
				 * Functionality : Edit movie details
				 * Responsible : Yan Mun Kye
				 *
				 * follow flow chart
				 */
				{
				print_title("Edit Movie Details");
					for (int i = 1; i <= movie_list.getSize(); ++i)
					{
						Movie* mov = movie_list.getAtIndex(i-1);
						cout << setw(3) << right << i << ". " <<
							setw(10) << left << mov->title << endl;
					}
					int movChoice_i;
					Movie* movChoice;
					while (true)
					{
						cout << "Please select the movie number which you want to edit : ";
						cin >> movChoice_i;
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				//validation
				if (cin.fail())
				{
					cout << "Invalid input! Please type numbers only!" << endl << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if (movChoice_i <= 0 || movChoice_i > movie_list.getSize())
				{
					cout << "Invalid choice! Please type numbers between 1 and " << movie_list.getSize() << " only!" << endl << endl;
					continue;
				}

				// all good
				break;
			}
			movChoice = movie_list.getAtIndex(movChoice_i - 1);
			cout << endl << "Movie chosen : " << movChoice->title << endl;

			cout << "Which detail do you want to edit?" << endl
				<< "1. Title" << endl
				<< "2. Duration" << endl
				<< "3. Genre" << endl
				<< "4. Rating" << endl
				<< "5. Air Time" << endl << endl;

			while (true) {
				cout << "Choice : ";
				cin >> choice;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


				if (cin.fail())
				{
					cout << "Invalid input! Please type numbers only!" << endl << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if (choice <= 0 || choice > 5)
				{
					cout << "Invalid choice! Please type numbers between 1 and " << 5 << " only!" << endl << endl;
					continue;
				}
				break;
			}


			string edited;
			switch (choice)
			{
			case 1:
			{
				print_title("Movie title");

				cout << "Old value : " << movChoice->title << endl;
				cout << "New value (leave blank to leave unchanged) : ";
				getline(cin, edited);

				if (!edited.empty())
				{
					movChoice->title = edited;
					cout << endl << "Movie title edited!" << endl;
				}
				else
				{
					cout << endl << "Nothing was changed." << endl;
				}
				break;
			}
			case 2:
			{
				print_title("Movie duration");

				cout << "Old value (hours) : " << movChoice->duration << endl;
				cout << "New value (leave blank to leave unchanged) : ";
				getline(cin, edited);

				if (!edited.empty())
				{
					movChoice->duration = stod(edited);
					cout << endl << "Movie duration edited!" << endl;
				}
				else
				{
					cout << endl << "Nothing was changed." << endl;
				}
				break;
			}
			case 3:
			{
				print_title("Movie genre");
				cout << "Old value : " << movChoice->genre << endl;
				cout << "New value (leave blank to leave unchanged) : ";
				getline(cin, edited);


				if (!edited.empty())
				{
					movChoice->genre = edited;
					cout << endl << "Movie genre edited!" << endl;
				}
				else
				{
					cout << endl << "Nothing was changed." << endl;
				}
				break;
			}
			case 4:
			{
				while (true) {
					print_title("Movie rating");

					cout << "Old value (stars) : " << movChoice->rating << endl;
					cout << "New value (leave blank to leave unchanged) : ";
					getline(cin, edited);


					if (!edited.empty())
					{
						if (stoi(edited) < 1 || stoi(edited) > 5)
						{
							cout << "Invalid input. Please input a whole number between 1 and 5 only!" << endl
								;
							continue;
						}
						movChoice->rating = stoi(edited);
						cout << endl << "Movie rating edited!" << endl;

					}
					else
					{
						cout << endl << "Nothing was changed." << endl;
					}
					break;
				}
				break;
			}
			case 5:
			{
				print_title("Movie air time");

				cout << "Old value (HHmm) : " << movChoice->air_time << endl;
				cout << "New value (leave blank to leave unchanged) : ";
				getline(cin, edited);


				if (!edited.empty())
				{
					movChoice->air_time = edited;
					cout << endl << "Movie air time edited!" << endl;
				}
				else
				{
					cout << endl << "Nothing was changed." << endl;
				}
				break;
			}
			}

			system("pause"); system("cls");
			break;
		}
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


		{
			print_title("Sort movie by available seats");
			DoublyLinkedList<Movie> sortedList = movie_list;
			sortedList.mergeSort();
			while (true) {
				cout << "How do you want to display the sorted list : " << endl
					<< "1. Ascending" << endl
					<< "2. Descending" << endl;
				cout << "Your choice : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "Invalid input! Please type numbers only!" << endl << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				if (choice != 1 && choice != 2)
				{
					cout << "Invalid input! Please type either 1 or 2 only!" << endl << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			switch (choice)
			{
			case 1:
			{
				node<Movie>* temp = sortedList.getHead();
				cout << setw(25) << "Movie Name" << setw(20) << "Available Seats" << endl;

				while (temp != nullptr)
				{
					cout << setw(25) << temp->data.title << setw(20) << temp->valueOfData() << endl;
					temp = temp->next;
				}
				cout << endl;
				break;
			}
			case 2:
			{
				node<Movie>* temp = sortedList.getTail();
				cout << setw(25) << "Movie Name" << setw(20) << "Available seats" << endl;

				while (temp != nullptr)
				{
					cout << setw(25) << temp->data.title << setw(20) << temp->valueOfData() << endl;
					temp = temp->prev;
				}
				cout << endl;
				break;
			}
			}
			system("pause"); system("cls");
			break;
		}
		case 7:
			/*
			 * Functionality : Delete movie
			 * Responsible : Tan Sheng Jeh
			 *
			 * follow flow chart
			 * but for the actual delete part, no need to go through the list one by one, just use the function to delete at specific index.
			 * user input : 3
			 */
		{
			print_list();

			int temp_movie_id;
			int j;
			int flag = 1;
			cout << "Enter the Movie ID that you wanted to delete:" << endl;
			cin >> temp_movie_id;
			for (j = 0; j < movie_list.getSize(); ++j)
			{
				Movie* mov = movie_list.getAtIndex(j);
				if (temp_movie_id == mov->movie_id)
				{
					movie_list.deleteAtIndex(j);
					cout << " Movie deleted successfully." << endl;
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				cout << "Movie ID not found." << endl;
			}
		}


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
		{
			print_title("New transaction (new purchase)");
			DoublyLinkedList<Ticket> tix_list = DoublyLinkedList<Ticket>();
			Transaction newTransaction = Transaction();
			newTransaction.transaction_id = ++TRANSACTION_ID;
			do
			{
				for (int i = 1; i <= movie_list.getSize(); ++i)
				{
					Movie* mov = movie_list.getAtIndex(i - 1);
					cout << setw(3) << right << i << ". " <<
						setw(10) << left << mov->title << " (" << mov->air_time << ")" << endl;
				}
				int movChoice_i;
				while (true) {
					cout << "Select your movie choice (Insert numbers only) : ";
					cin >> movChoice_i;
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					//validation
					if (cin.fail())
					{
						cout << "Invalid input! Please type numbers only!" << endl << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					if (movChoice_i <= 0 || movChoice_i > movie_list.getSize())
					{
						cout << "Invalid choice! Please type numbers between 1 and " << movie_list.getSize() << " only!" << endl << endl;
						continue;
					}

					// all good
					break;
				}
				Movie* movChoice = movie_list.getAtIndex(movChoice_i - 1);
				--movChoice->number_of_available_seats;
				Ticket tix = Ticket();
				Seat seat;
				tix.movie = *movChoice;
				while (true)
				{
					cout << "Enter row number (1 - 10) : ";
					cin >> seat.row;
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (cin.fail())
					{
						cout << "Invalid input! Please type numbers only!" << endl << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					if (seat.row <= 0 || seat.row > 10)
					{
						cout << "Invalid choice! Please type numbers between 1 and 10 only!" << endl << endl;
						continue;
					}

					// all good
					break;
				}
				while (true) {
					cout << "Enter column (A - J) : ";
					cin >> seat.column;
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (cin.fail())
					{
						cout << "Invalid input! Please type single character only!" << endl << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					if (seat.column < 'A' || seat.column > 'J')
					{
						cout << "Invalid choice! Please type character between A and J only!" << endl << endl;
						continue;
					}

					// all good
					break;
				}
				tix.seat = seat;
				while (true)
				{
					cout << "Enter price : ";
					cin >> tix.price;
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (cin.fail())
					{
						cout << "Invalid input! Please type numbers only!" << endl << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						continue;
					}
					if (tix.price <= 0)
					{
						cout << "Invalid price! Please type positive numbers only!" << endl << endl;
						continue;
					}

					// all good
					break;
				}
				tix.ticket_id = ++TICKET_ID;
				newTransaction.list_of_tickets.addToEnd(tix);

				cout << "Another entry? (0 - No, 1 - Yes) : ";
				cin >> choice;
				cout << endl; 
			} while (choice == 1);
			while (true) {
				char delim = '/';
				cout << "Enter date of purchase (format : dd/MM/YYYY) : ";
				cin >> newTransaction.day >> delim >> newTransaction.month >> delim >> newTransaction.year;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (cin.fail())
				{
					cout << "Invalid input! Please try again" << endl << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				// all good
				break;
			}
			cout << "Enter payment method : ";
			getline(cin, newTransaction.payment_method);

			transaction_list.addToEnd(newTransaction);

			system("pause"); system("cls");
			break;
				}
			case 9:
				{
				//DoublyLinkedList<Transaction> trans = DoublyLinkedList<Transaction>::getAtIndex(list_of_tickets);
				print_title("All Transactions");
				cout << setw(10) << right << "Transaction ID"
					<< " | " << setw(46) << right << "Date"
					<< " | " << setw(15) << right << "Payment Method"
					<< " | " <<setw(10) << right << "List of Tickets"
					<< endl;
				cout << string(130, '-') << endl;
				for (int i = 0; i < transaction_list.getSize(); ++i)
				{
					
					Transaction* t = transaction_list.getAtIndex(i);
					//implement for loop here to store all the strings of list of tickets 
					Ticket ticket;

					string str_list_tix_id = "";
					str_list_tix_id += "{ ";
					
					for (int j = 0; j < t->list_of_tickets.getSize(); ++j)
					{
						str_list_tix_id += to_string(t->list_of_tickets.getAtIndex(j)->ticket_id);
						if (j != t->list_of_tickets.getSize()-1)
						{
							str_list_tix_id += " ,";
						}
					}
					str_list_tix_id += " }";
					
					
					// [1,2,3,4]
					
					//for (i = 0; i < )
					if (t != nullptr)
					{
					cout << setw(14) << right << t->transaction_id
						<< " | " << setw(35) << right << t->day
						<< " / " << right << t->month
						<< " / " << right << t->year
						<< " | " << setw(15) << right << t->payment_method
						<< " | " << setw(20) << str_list_tix_id
						<< endl;
						
					
					}
				}
				system("pause"); system("cls");
				break;
				}
			case 10:
				/*
				 * Functionality : Sort transaction by purchase amount
				 * Responsible : Yan Mun Kye
				 *
				 * follow flow chart
				 * maybe can ask them if want ascend or descend
				 * use merge sort 
				 */
				{
					print_title("Sort transaction by purchase amount");
					DoublyLinkedList<Transaction> sortedList = transaction_list;
					sortedList.mergeSort();
					while (true) {
						cout << "How do you want to display the sorted list : " << endl
							<< "1. Ascending" << endl
							<< "2. Descending" << endl;
						cout << "Your choice : ";
						cin >> choice;
						if (cin.fail())
						{
							cout << "Invalid input! Please type numbers only!" << endl << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
						if (choice != 1 && choice != 2)
						{
							cout << "Invalid input! Please type either 1 or 2 only!" << endl << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							continue;
						}
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						break;
					}
					switch (choice)
					{
					case 1:
						{
							node<Transaction>* temp = sortedList.getHead();
							cout << setw(10) << "T. ID" << setw(20) << "Total price (RM)" << endl;

				while (temp != nullptr)
				{
					cout << setw(10) << temp->data.transaction_id << setw(20) << temp->valueOfData() << endl;
					temp = temp->next;
				}
				cout << endl;
				break;
			}
			case 2:
			{
				node<Transaction>* temp = sortedList.getTail();
				cout << setw(10) << "T. ID" << setw(20) << "Total price (RM)" << endl;

				while (temp != nullptr)
				{
					cout << setw(10) << temp->data.transaction_id << setw(20) << temp->valueOfData() << endl;
					temp = temp->prev;
				}
				cout << endl;
				break;
			}
			}
			system("pause"); system("cls");
			break;
		}
		case 11:
			/*
			 * Functionality : Show Specific Transaction Detail
			 * Responsible : Tan Sheng Jeh
			 *
			 * follow flow chart
			 * but i think can just show users the list of all transction, then straight ask which details they want to see
			 * DO ask if they want to repeat the same action.
			 */

			 //DoublyLinkedList<Transaction> trans = DoublyLinkedList<Transaction>::getAtIndex(list_of_tickets);
		{
			int choice;
			do
			{


				print_title("All Transactions");
				cout << setw(10) << right << "Transaction ID"
					<< " | " << setw(46) << right << "Date"
					<< " | " << setw(15) << right << "Payment Method"
					<< " | " << setw(10) << right << "List of Tickets"
					<< endl;
				cout << string(130, '-') << endl;
				for (int i = 0; i < transaction_list.getSize(); ++i)
				{

					Transaction* t = transaction_list.getAtIndex(i);
					//implement for loop here to store all the strings of list of tickets 
					Ticket ticket;

					string str_list_tix_id = "";
					str_list_tix_id += "{ ";

					for (int j = 0; j < t->list_of_tickets.getSize(); ++j)
					{
						str_list_tix_id += to_string(t->list_of_tickets.getAtIndex(j)->ticket_id);
						if (j != t->list_of_tickets.getSize() - 1)
						{
							str_list_tix_id += " ,";
						}
					}
					str_list_tix_id += " }";


					// [1,2,3,4]

					//for (i = 0; i < )
					if (t != nullptr)
					{
						cout << setw(14) << right << t->transaction_id
							<< " | " << setw(35) << right << t->day
							<< " / " << right << t->month
							<< " / " << right << t->year
							<< " | " << setw(15) << right << t->payment_method
							<< " | " << setw(20) << str_list_tix_id
							<< endl;

					}
				}
				int temp_transactionID;
				cout << "Enter the Transaction ID whose transaction details you wanted to view:" << endl;
				cin >> temp_transactionID;
				int i,j, flag = 0;
				string str_list_tix_id = "";
				str_list_tix_id += "{ ";
				for (i = 0; i < transaction_list.getSize(); ++i)
				{
					Transaction* t = transaction_list.getAtIndex(i);
					if (temp_transactionID == t->transaction_id)
					{
						flag = 1;
						//string str_list_tix_id = "";
						//str_list_tix_id += "{ ";
						//for (j = 0; j < t->list_of_tickets.getSize(); ++j)
						//{
							//str_list_tix_id += to_string(t->list_of_tickets.getAtIndex(j)->ticket_id);
							//if (j != t->list_of_tickets.getSize() - 1)
							//{
								//str_list_tix_id += " ,";
							//}
						//}
						//str_list_tix_id += " }";
						//cout << setw(14) << right << t->transaction_id
							//<< " | " << setw(25) << right << t->list_of_tickets.getAtIndex(0)->movie.title
							//<< " | " << setw(35) << right << t->day
							//<< " / " << right << t->month
							//<< " / " << right << t->year
							//<< " | " << setw(15) << right << t->payment_method
							//<< " | " << setw(20) << str_list_tix_id
							//<< endl;
						cout << "Transaction ID: " << t->transaction_id << endl;
						cout << "Payment Method: " << t->payment_method << endl;
						cout << "Payment Date: " << t->day << "/" << t->month << "/" << t->year << endl;
						cout << "Tickets Bought: " << endl;
						int total = 0;
						for (j = 0; j < t->list_of_tickets.getSize(); ++j)
						{
							cout << j + 1 << " -> " << t->list_of_tickets.getAtIndex(j)->movie.title << endl;
							total += t->list_of_tickets.getAtIndex(j)->price;
						}
						cout << "Total Price = RM " << total << endl<< endl;
					}
				}
				if (flag == 0)
					cout << "Invalid transaction ID" << endl;
				cout << "Do you want to continue viewing the transaction detail? (0 - No, 1 - Yes):" << endl;
				cin >> choice;
			} while (choice == 1);
		}



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


		//break; // break from the choice loop
	//}
	}
	return 0;
}


