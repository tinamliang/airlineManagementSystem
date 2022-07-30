#include "Flight.h"
#include <iostream>
#include <mysql.h>
using namespace std;

void displayMenu() {

	cout << endl;
	cout << endl;

	cout << "\t\t\tPlease Choose from the following MENU\n";
	cout << "\t\t\t-------------------------------------\n";
	cout << "\t\t\t1. BOOKING\t\t\t2. CANCEL TICKET\n";
	cout << "\t\t\t3. CANCEL FLIGHT\t\t4. FLIGHT TIME!\n";
	cout << "\t\t\t5. EXIT";

	cout << "\n\t\t\t\t\tEnter Your Choice : ";

}

int main()
{
	MYSQL* conn;
	conn = mysql_init(0);//Intializating the connection
	conn = mysql_real_connect(conn, "localhost", "root", "password", "airline_db", 3306, NULL, 0);

	string destination;
	char bookTicket, cancelFlight, cancelEntireFlight, boolPlaneDepart;
	Flight flight;
	int input;
	if (conn)
	{

		cout << "\n\n\n";
		cout << "\t\t\t**********************************************************************\n";
		cout << "\t\t\t               Welcome to the AIRLINE BOOKING USER GUIDE   \n";
		cout << "\t\t\t**********************************************************************\n";

		cout << endl;

		cout << "\t\t1: Books and prints ticket" << endl;

		cout << "\t\t2: Input your first name and last name to cancel your flight. " << endl;

		cout << "\t\t3: Cancel an entire flight using the flight's number. " << endl;

		cout << "\t\t4: Flight's departure, choose the flight's number that outputs all the passengers sorted by seat number. " << endl;

		cout << "\t\t5: QUIT. " << endl;

		cout << endl;
		cout << "\t\tAny problems / issues with this program please contact through email: problemswithsystem@gmail.com " << endl;

		cout << "\n\n";

		cout << "\t\t\t**********************************************************************\n";

		cout << endl;

		cout << endl;

		// The program menu


		do {

			displayMenu();
			cin >> input;

			if (input == 1) {

				cout << "Where is your destination?: " << endl;
				flight.displayFlightInfo(conn);
				cin >> destination;

				flight.showFlightSeats(conn, destination);

				cout << "Would you like to book a ticket? (y/n)" << endl;
				cin >> bookTicket;

				if (bookTicket == 'y') {
					flight.bookTickets(conn, destination);
				}
			}

			if (input == 2) {

				cout << "Would you like to cancel a flight? (y/n)" << endl;
				cin >> cancelFlight;

				if (cancelFlight == 'y') {
					flight.cancelTickets(conn);
				}
			}

			if (input == 3) {
				cout << "Would you like to cancel an entire flight? (y/n)" << endl;
				cin >> cancelEntireFlight;

				if (cancelEntireFlight == 'y') {
					flight.cancelFlight(conn);
				}
			}

			if (input == 4) {

				cout << "Flight is about to depart? (y/n)" << endl;
				cin >> boolPlaneDepart;

				if (boolPlaneDepart == 'y') {
					flight.departingFlight(conn);
				}
			}

		} while (input != 5);
	}

}