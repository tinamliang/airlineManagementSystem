#include "Passenger.h"
#include <iostream>
#include <vector>
#include <mysql.h>
using namespace std;

#ifndef FLIGHT_H
#define FLIGHT_H

class Flight {
private:

public:

    Flight();
    void displayFlightInfo(MYSQL* conn);
    void showFlightSeats(MYSQL *conn, string dest);
    void bookTickets(MYSQL* conn, string dest);
    void cancelTickets(MYSQL* conn);
    void cancelFlight(MYSQL* conn);
    void departingFlight(MYSQL* conn);
    Passenger getContactInfo(MYSQL* conn, string dest, string seatsLeft);
    void printTicket(MYSQL* conn, string dest, Passenger p);
};

#endif