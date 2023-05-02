#include "Flight.h"
#include <iostream>
#include <mysql.h>
using namespace std;

void sysAdminType() {

	cout << "\n\n\n";
	cout << "\t\t\t**********************************************************************\n";
	cout << "\t\t\t               Welcome to the AIRLINE BOOKING USER GUIDE   \n";
	cout << "\t\t\t**********************************************************************\n";

	cout << endl;
	cout << endl;

	cout << "\t\t\tAre you a?\n";

	cout << "\t\t\t1. Admin\t\t\t2. User\n";
	cout << "\n\t\t\t\tEnter Your Choice : ";
}

void displayMenu() {

	cout << endl;
	cout << endl;

	cout << "\t\t\tPlease Choose from the following MENU\n";
	cout << "\t\t\t-------------------------------------\n";
	cout << "\t\t\t1. BOOKING\t\t\t2. CANCEL TICKET\n";
	cout << "\t\t\t4. EXIT\n";

	cout << "\n\t\t\t\t\tEnter Your Choice : ";

}

void displayAdminMenu() {

	cout << endl;
	cout << endl;

	cout << "\t\t\tPlease Choose from the following MENU\n";
	cout << "\t\t\t-------------------------------------\n";
	cout << "\t\t\t1. CANCEL FLIGHT\t\t\t2. FLIGHT INFORMATION\n";
	cout << "\t\t\t3. ADD FLIGHT\t\t\t\t4. EXIT\n";

	cout << "\n\t\t\t\t\tEnter Your Choice : ";

}

int main()
{
	MYSQL* conn;
	conn = mysql_init(0);//Intializating the connection
	conn = mysql_real_connect(conn, "", "", "", "", 3306, NULL, 0);

	string destination;
	char bookTicket, cancelFlight, cancelEntireFlight, boolPlaneDepart, flightAdd;
	Flight flight;
	int input;
	int userType;

	if (conn)
	{

		do {

			sysAdminType();
			cin >> userType;

			if (userType == 2) {

				displayMenu();
				cin >> input;

				if (input == 1) {

					cout << endl;
					cout << "\t\t\tWhere is your destination?: \n";
					flight.displayFlightInfo(conn);
					cout << "\t\t\tEnter destination name: ";
					cin >> destination;

					flight.showFlightSeats(conn, destination);

					cout << "\t\t\tWould you like to book a ticket? (y/n) ";
					cin >> bookTicket;

					if (bookTicket == 'y') {
						flight.bookTickets(conn, destination);
					}
				}

				if (input == 2) {

					cout << "\t\t\tWould you like to cancel a ticket? (y/n) ";
					cin >> cancelFlight;

					if (cancelFlight == 'y') {
						flight.cancelTickets(conn);
					}
				}
			}
			else {
				displayAdminMenu();
				cin >> input;

				if (input == 1) {
					cout << "\t\t\tWould you like to cancel an entire flight? (y/n) ";
					cin >> cancelEntireFlight;

					if (cancelEntireFlight == 'y') {
						flight.cancelFlight(conn);
					}
				}
				
				if (input == 2) {
					cout << "\t\t\tFlight ready about to depart? (y/n) ";
					cin >> boolPlaneDepart;

					if (boolPlaneDepart == 'y') {
						flight.departingFlight(conn);
					}
				}

				if (input == 3) {
					cout << "\t\t\tAdd a flight? (y/n) ";
					cin >> flightAdd;

					if (flightAdd == 'y') {
						flight.addFlight(conn);
					}
				}
			}
		} while (input != 4);
	}

}
