//This project was developed for personal research and education purposes.
//Do not use this tool to scan networks or ports that you do not have permission to scan.

//Date Created: 14 Jun 2022
//Author: Kyle Noel

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <SFML/Network.hpp>

#define WINDOWS

using namespace std;
using namespace sf;

//Global var
const int PORT_LIMIT = 65535;
//Prototypes
void singleScan(string);
void rangeScan(string);
string portStatus(const string&, int);
void clearConsole();

int main()
{
	int op1;
	int op2;
	char remote[16];
	bool flag;
	char cont;
	const char header[62] = "-------------------- SIMPLE PORT SCANNER --------------------";
	const char footer[62] = "-------------------- PROGRAM  TERMINATED --------------------";
	string scanHost;
	const string LOCAL = "localhost";

	do {
		//Display header
		cout << header << endl << endl;

		//Local scan and remote scan menu
		cout << "Would you like to perform a local scan or enter a remote IP?" << endl;
		cout << "1. Scan localhost" << endl << "2. Enter an IP" << endl;
		cout << ">> ";
		cin >> op1;
		while (op1 != 1 && op1 != 2)
		{
			cout << "Invalid response. Try again." << endl << ">> ";
			cin >> op1;
		}
		switch (op1) {
		case 1:
			scanHost = LOCAL;
			break;
		case 2:
			cout << endl << "Enter an IPv4 address (ex: 255.255.255.255) or a valid URL." << endl << ">> ";
			cin.ignore();
			cin.getline(remote, 16);
			scanHost = remote;
			break;
		}

		//Single scan and range scan menu
		cout << endl;
		cout << "Would you like to scan a single port or a range of ports?" << endl;
		cout << "1. Single" << endl << "2. Range" << endl;
		cout << ">> ";
		cin >> op2;
		while (op2 != 1 && op2 != 2)
		{
			cout << "Invalid response. Try again." << endl << ">> ";
			cin >> op2;
		}
		cout << endl;

		switch (op2) {
		case 1:
			singleScan(scanHost);
			break;
		case 2:
			rangeScan(scanHost);
			break;
		}

		//Restart option
		cout << endl << "Would you like to perform another scan? Y/N" << endl << ">> ";
		cin >> cont;

		while (cont != 'Y' && cont != 'y' && cont != 'N' && cont != 'n')
		{
			cout << "Invalid response. Try again." << endl << ">> ";
			cin >> cont;
		}

		if (cont == 'Y' || cont == 'y')
		{
			flag = true;
			clearConsole();
		}
		else
			flag = false;

	} while (flag == true);

	//Display footer
	cout << endl << footer << endl;

	return 0;
}

void singleScan(string host)
{
	int portNum;

	cout << "Enter a port number to scan." << endl << ">> ";
	cin >> portNum;
	while (portNum < 0 || portNum > PORT_LIMIT)
	{
		cout << "Invalid response. Enter a valid port number:  ";
		cin >> portNum;
	}

	//Displaying single scan result
	cout << endl << "Scanning " << host << "..." << endl;
	cout << "Port " << portNum << " is " << portStatus(host, portNum) << endl;
}

void rangeScan(string host)
{
	int beg;
	int end;
	vector<int> range;

	cout << "Enter the first port number in the scan range." << endl << ">> ";
	cin >> beg;
	while (beg < 0 || beg > PORT_LIMIT)
	{
		cout << "Invalid response. Try again." << endl << ">> ";
		cin >> beg;
	}
	cout << endl << "Enter the last port number in the scan range." << endl << ">> ";
	cin >> end;
	while (end < 0 || end > PORT_LIMIT)
	{
		cout << "Invalid response. Try again." << endl << ">> ";
		cin >> end;
	}

	//Err checking
	if (beg > end)
		swap(beg, end);
	if (beg == end)
	{
		end = beg;
		beg = 0;	//displays ports 0-beg if beg and end are equal
	}


	for (; beg <= end; beg++)
	{
		range.push_back(beg);
	}

	//Displaying range scan results
	cout << endl << "Scanning " << host << "..." << endl;
	for (auto i = range.begin(); i != range.end(); ++i)
	{
		cout << "Port " << *i << setw(12) << portStatus(host, *i) << endl;
	}

}

string portStatus(const string& ip, int port)
{
	string status;

	//Scanning ports
	if (TcpSocket().connect(ip, port) == Socket::Done)
		status = "open";
	else
		status = "closed";
	return status;
}

void clearConsole()
{
#ifdef WINDOWS
	system("cls");
#endif
#ifdef LINUX
	system("clear")
#endif
}
