#include <iostream>
using namespace std;

#ifndef Passenger_H
#define Passenger_H

class Passenger
{
private:
    string firstName, lastName, address, phoneNum, seatNum;

public:
    Passenger();
    Passenger(string f, string l, string a, string p, string s);
    Passenger(const Passenger& p);
    string getfirstName();
    string getlastName();
    string getAddress();
    string getPhoneNum();
    string getSeatNum();
    Passenger& operator=(const Passenger& p);
    void setfirstName(string n);
    void setlastName(string n);
    void setAddress(string a);
    void setPhoneNum(string n);
    void setSeatNum(string s);
    string toString();
    string basicInfo();

};

#endif