#include "Flight.h"
#include "Passenger.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <algorithm>
#include <typeinfo>
#include <mysql.h>
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;


Flight::Flight() {

}

void Flight::displayFlightInfo(MYSQL* conn)
{
	int qstate = 0;
	MYSQL_ROW row;
	MYSQL_RES* res;

	string query = "select * from flights";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);


	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			if (atoi(row[1]) != 0)
			{
				printf("Id: %s, Destination: %s \n", row[0], row[3]);
			}
		}
	}
	else {
		cout << "Flight not found" << mysql_error(conn) << endl;
	}
}

void Flight::showFlightSeats(MYSQL* conn, string dest) {

	int qstate = 0;
	MYSQL_ROW row;
	MYSQL_RES* res;

	string query = "select * from flights";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);


	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			char* c = row[3];
			if (string(c) == dest) {
				printf("Seats Available: %s\n", row[1]);
			}
		}
	}
	else {
		cout << "Query failed: " << mysql_error(conn) << endl;
	}


}

void Flight::bookTickets(MYSQL* conn, string dest) {

	Passenger p;
	Flight f;
	int qstate = 0;
	stringstream ss;
	MYSQL_ROW row;
	MYSQL_RES* res;

	string query = "select * from flights";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);


	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			char* ch = row[3];
			char* seatsLeft = row[1];
			if (string(ch) == dest) {
				string seatsRemaining = string(seatsLeft);
				p = f.getContactInfo(conn, dest, seatsRemaining);
				
				ss << "UPDATE flights SET seatsAvailable = seatsAvailable - 1 WHERE destination = '" << dest << "'";

				string seats_query = ss.str();
				const char* q2 = seats_query.c_str();
				int qstate2 = mysql_query(conn, q2);

				if (!qstate2) {
					f.printTicket(conn, dest, p);
				}

			}
		}
	}
	else {
		cout << "Query failed: " << mysql_error(conn) << endl;
	}


}

Passenger Flight::getContactInfo(MYSQL* conn, string dest, string seatsLeft) {

	string firstName;
	string lastName;
	string address;
	string phoneNum;

	cout << "Firstname: " << endl;
	cin >> firstName;

	cout << "Lastname: " << endl;
	cin >> lastName;

	cout << "Address: " << endl;
	cin >> address;

	cout << "Phone Number: " << endl;
	cin >> phoneNum;

	Passenger p;

	p.setfirstName(firstName);
	p.setlastName(lastName);
	p.setAddress(address);
	p.setPhoneNum(phoneNum);
	p.setSeatNum(seatsLeft);

	cout << "System accepted login" << endl;
	cout << p.toString() << endl;

	
	int qstate = 0;
	stringstream ss;

	ss << "INSERT INTO passengers (firstName, lastName, address, phoneNum, destination, seatNum) VALUES('" << firstName << "', '" << lastName << "', '" << address << "', '" << phoneNum << "', '" << dest << "', '" << stoi(seatsLeft) << "')";

	string query = ss.str();
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate) {
		cout << "Passenger added to database" << endl;

	}

	else {
		cout << "Query failed: " << mysql_error(conn) << endl;
	}

	return p;
	
}

void Flight::cancelTickets(MYSQL* conn) {

	string firstName;
	string lastName;

	cout << "Firstname: " << endl;
	cin >> firstName;

	cout << "Lastname: " << endl;
	cin >> lastName;

	int qstate = 0;
	MYSQL_ROW row;
	MYSQL_RES* res;
	stringstream ss, ss1;

	string query = "select * from passengers";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);


	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			char* first = row[0];
			char* last = row[1];
			if (string(first) == firstName && string(last) == lastName) {

				ss << "DELETE FROM passengers WHERE firstName = '" << firstName << "'";
				string query = ss.str();
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate) {

					cout << "Deleted flight!" << endl;

					ss1 << "UPDATE flights SET seatsAvailable = seatsAvailable + 1 WHERE destination = '" << string(row[4]) << "'";

					string seats_query = ss1.str();
					const char* q2 = seats_query.c_str();
					int qstate2 = mysql_query(conn, q2);

					if (!qstate2) {
						cout << "Flight added the seat back!" << endl;
					}
				}
				
			}
			else {
				cout << "No passengers matching your info exists, sorry" << endl;
			}
			
		}
	}
	else {
		cout << "Query failed: " << mysql_error(conn) << endl;
	}


}

void Flight::cancelFlight(MYSQL* conn) {

	string flightNum;

	cout << "What flight would you like to cancel (flightNum)? " << endl;
	cin >> flightNum;

	int qstate, qstate1 = 0;
	MYSQL_ROW row;
	MYSQL_RES* res;
	stringstream ss, ss1;
	string destination;

	string query = "select * from flights";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);


	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			char* c = row[2];
			char* d = row[3];
			if (string(c) == flightNum) {
				destination = string(d);

				string query1 = "select * from passengers";
				const char* q = query1.c_str();
				qstate1 = mysql_query(conn, q);


				if (!qstate1)
				{
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res))
					{
						if (string(row[4]) == destination)
						{
							printf("First Name: %s, Last Name: %s, Phone number: %s \n", row[0], row[1], row[3]);

							ss << "DELETE FROM passengers WHERE firstName = '" << string(row[0]) << "'";

							string query1 = ss.str();
							const char* q = query1.c_str();
							qstate = mysql_query(conn, q);

							if (!qstate) {
								cout << "Flight has been canceled!" << endl;
								
								ss1 << "DELETE FROM flights WHERE flightNum = '" << flightNum << "'";

								string query2 = ss1.str();
								const char* q = query2.c_str();
								qstate = mysql_query(conn, q);

								if (!qstate) {
									cout << "Whole flight has been deleted!" << endl;
								}
							}
						}
					}
				}
				else {
					cout << "Query failed: " << mysql_error(conn) << endl;
				}
			}
		}
	}
	else {
		cout << "Query failed: " << mysql_error(conn) << endl;
	}


}

void Flight::departingFlight(MYSQL* conn) {

	string flightNum;

	cout << "Which flight is departing? " << endl;
	cin >> flightNum;

	int qstate, qstate1 = 0;
	MYSQL_ROW row;
	MYSQL_RES* res;
	stringstream ss, ss1;
	string destination;

	string query = "select * from flights";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);


	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			char* c = row[2];
			char* d = row[3];
			if (string(c) == flightNum) {
				destination = string(d);

				string query1 = "select * from passengers ORDER BY seatNum ASC";
				const char* q = query1.c_str();
				qstate1 = mysql_query(conn, q);


				if (!qstate1)
				{
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res))
					{
						if (string(row[4]) == destination)
						{
							printf("First Name: %s, Last Name: %s, Phone number: %s, Seat number: %s \n", row[0], row[1], row[3], string(row[5]));
						}
					}
				}
			}
		}
	}

}

void Flight::printTicket(MYSQL* conn, string dest, Passenger p) {

	
	int qstate = 0;
	MYSQL_ROW row;
	MYSQL_RES* res;
	stringstream ss, ss1;

	string query = "select * from flights";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			char* flightNum = row[2];
			char* gateNum = row[4];
			char* time = row[5];

			if (string(row[3]) == dest) {

				ofstream myfile;
				myfile.open("ticket.txt");

				myfile << "======================== AIRLINE BOOKING TICKET ===============================" << endl;
				myfile << "###############################################################################" << endl;
				myfile << "-------------------------------------------------------------------------------" << endl;
				myfile << "       First Name                                             Last Name        " << endl;
				myfile << "      --------------                                        ----------------   " << endl;
				myfile << "        " << p.getfirstName() + "                                               " + p.getlastName() << endl;
				myfile << "-------------------------------------------------------------------------------" << endl;
				myfile << "Flight No : " << flightNum << "Gate: " << gateNum << "  \n" << endl;
				myfile << "-------------------------------------------------------------------------------" << endl;
				myfile << "Departure Time : " << time << "  Destination : " << dest << endl;
				myfile << "###############################################################################" << endl;

				myfile.close();

				cout << "Ticket was written" << endl;

				system("printTicket.bat");
				cout << "Starting Batch File...\n";
			}
		}
	}
}