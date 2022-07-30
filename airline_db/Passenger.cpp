#include "Passenger.h"
#include <sstream>

Passenger::Passenger()
{


}

Passenger::Passenger(string f, string l, string a, string p, string s)
{
	firstName = f;
	lastName = l;
	address = a;
	phoneNum = p;
	seatNum = s;
}

// copy constructor 
Passenger::Passenger(const Passenger& p) {
	firstName = p.firstName;
	lastName = p.lastName;
	address = p.address;
	phoneNum = p.phoneNum;
}

// operator overloading
Passenger& Passenger::operator=(const Passenger& p)
{
	firstName = p.firstName;
	lastName = p.lastName;
	address = p.address;
	phoneNum = p.phoneNum;
	return *this;
}

string Passenger::getfirstName()
{
	return firstName;
}

string Passenger::getlastName()
{
	return lastName;
}

string Passenger::getAddress()
{
	return address;
}

string Passenger::getPhoneNum()
{
	return phoneNum;
}

string Passenger::getSeatNum()
{
	return seatNum;
}

void Passenger::setfirstName(string n)
{
	firstName = n;
}

void Passenger::setlastName(string n)
{
	lastName = n;
}

void Passenger::setAddress(string a)
{
	address = a;
}

void Passenger::setPhoneNum(string n)
{
	phoneNum = n;
}

void Passenger::setSeatNum(string s) {
	seatNum = s;
}

string Passenger::toString()
{
	stringstream ss;
	ss << phoneNum;

	return (firstName + " " + lastName + " " + address + " " + ss.str() + " " + seatNum);
}

string Passenger::basicInfo()
{

	return (firstName);
}