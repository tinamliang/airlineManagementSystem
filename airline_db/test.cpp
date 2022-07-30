#include <iostream>
#include <sstream> 
using namespace std;

int main() {

	stringstream ss;


	ss << "SELECT * FROM << dest << ";
	cout << ss.str() << endl;
}