#include <iostream>
#include <string>
#include <windows.h>
using namespace std;


string getpass(const char *prompt, bool show_asterisk = true)
{
	const char BACKSPACE = 8;
	const char RETURN = 13;

	string password;
	unsigned char ch = 0;

	cout << prompt << endl;

	DWORD con_mode;
	DWORD dwRead;

	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hIn, &con_mode);
	SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

	while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
	{
		if (ch == BACKSPACE)
		{
			if (password.length() != 0)
			{
				if (show_asterisk)
					cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else
		{
			password += ch;
			if (show_asterisk)
				cout << '*';
		}
	}
	cout << endl;
	return password;
}



int main()
{
	const char *correct_password = "null";

	cout << "Test 1: echoing enabled" << endl;
	string password = getpass("Please enter the password: ", true); // Show asterisks
	if (password == correct_password)
		cout << "Correct password" << endl;
	else
		cout << "Incorrect password. Try again" << endl;

	cout << "\nTest 2: echoing disabled" << endl;
	password = getpass("Please enter the password: ", false); // Do not show asterisks
	if (password == correct_password)
		cout << "Correct password" << endl;
	else
		cout << "Incorrect password. Try again" << endl;

	return 0;
}