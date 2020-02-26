#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>
#include<cstdio>
#include<limits>
#include<exception>
#include<ctime>

int error;
using namespace std;
// Structure to Store Book Details
struct Bookdetails
{
	int bookID;
	string category;
	string name;
	string description;
	double price;
	int quantity;
	string publisher;
	string author;
}book;
// Global Prototype Callings All Functions  
//=============================================================================
// Search Functions Prototype Calling Statements
void searchbycategory(Bookdetails Booklist[1000], int fileline);
void searchBooks(Bookdetails Booklist[1000], int fileline);
void searchBookbyName(Bookdetails Booklist[1000], int fileline);
void searchbyauthor(Bookdetails Booklist[1000], int fileline);
void searchBookbyPrice(Bookdetails Booklist[1000], int fileline);

//=============================================================================
// Update Functions Prototype Calling Statements
void Update(Bookdetails Booklist[1000], int x, int fileline);
void UpdateByName(Bookdetails Booklist[1000], int fileline);
void UpdateByID(Bookdetails Booklist[1000], int fileline);
void displayUpdate(Bookdetails Booklist[1000], int fileline);
void updateByAuthor(Bookdetails Booklist[1000], int fileline);
void UpdatebyCategory(Bookdetails Booklist[1000], int fileline);

//=============================================================================
// Delete Functions Prototype Calling Statements
void DeletebybID(Bookdetails Booklist[1000], int  bookID, int x, int& fileline);
void displaydelete(Bookdetails Booklist[1000], int& fileline);
void DeleteByID(Bookdetails Booklist[1000], int& fileline);
void DeletebyCategory(Bookdetails Booklist[1000], int& fileline);
void DeletebyAuthor(Bookdetails Booklist[1000], int& fileline);
void DeletebyBname(Bookdetails Booklist[1000], int& fileline);

//=============================================================================
// Adding Books to File & from file  Functions Prototype Calling Statements
int addBook(Bookdetails Booklist[1000], int fileline);
int addBooksfromFile(Bookdetails Booklist[1000]);

//=============================================================================
// Display Functions Prototype Calling Statements
void printBooks(Bookdetails Booklist[1000], int fileline);
void printBookOffers(Bookdetails Booklist[1000], int fileline);

//=============================================================================
// Login Related Functions Prototype Calling Statements
void loginreport(ofstream& adminloginreport);
void staffFunctions(string name, ofstream& loginreport, ofstream& guestlogin);
void adminMenu(ofstream& adminloginreport);
void staff(string& user, string& pass1);
void Login(string& admin, string& password);


//=============================================================================
// Other Calling Functions Prototype Calling Statements
void AdminOptions();
void HelpFunction();
string ConvertToLower(string str);
const std::string currentDateTime();
void timeconverter(float sec);

// Seconds to Hours or minutes converter
void timeconverter(float sec)
{
	int hours = 0;
	int mins = 0;
	int seconds = 0;
	while (sec > 3600)
	{
		hours++;
		sec = sec - 3600;
	}
	while (sec < 3600 && sec > 60)
	{
		mins++;
		sec = sec - 60;
	}
	while (sec < 60)
	{
		seconds = sec;
		break;
	}
	if (hours > 0)
		cout << hours << " Hours & " << mins << " Minutes & " << seconds << " Seconds" ;
	else if (mins > 0)
		cout << mins << " Minutes & " << seconds << " Seconds" ;
	else
		cout << seconds << " Seconds" ;
}

//password asterik generator
string getpass(const char *prompt, bool show_asterisk = true)
{
	const char BACKSPACE = 8;
	const char RETURN = 13;
	string password;
	unsigned char ch = 0;
	cout << "\n\n\t"<< prompt;
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

// Generate System Date & Time
const std::string currentDateTime() 
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

// convert all the strings to lower case
string ConvertToLower(string str)
{
	//Loop through the size of the string
	for (int i = 0; i< str.length(); i++)
	{
		//If the character is not a space
		if (str[i] != ' ')
		{
		   //Reset the value of the array position to the upper case letter
			str[i] = tolower(str[i]);
		}
	}
	return str;
}

// function to change font size 
void fontsize()
{
	int font, x, y;
	
	do
	{
		error = 0;
		cout << "\n\tEnter font size : ";
		cin >> font;
		if (font >= 25 || font <= 5)
		{
			cout << "\tPlease enter font size Less than 25 & greater than 5... " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
		if (cin.fail())
		{
			cout << "\tPlease enter a valid input... " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	x = font;
	y = 2 * x;
	HANDLE Hout = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD fsize = { x, y };
	CONSOLE_FONT_INFOEX Font = { sizeof(Font) };
	::GetCurrentConsoleFontEx(Hout, FALSE, &Font);

	Font.dwFontSize = fsize;
	SetCurrentConsoleFontEx(Hout, 0, &Font);
	cin.clear();
	system("cls");
	return;
	
}

// function to change the background theme
void color()
{
int col;
		cout << "\n\t1. Black and White theme " << endl;
		cout << "\n\t2. White and Black theme  \n\n\t0. Return" << endl;
		
		do {
			do
			{
				error = 0;
				cout << "\n\tEnter your selection here: ";
				cin >> col;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input. " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			if (col == 1)
			{
				system("color 0F");
				system("cls");
				return;
			}
			else if (col == 2)
			{
				system("color F0");
				system("cls");
				return;
			}
		} while (col != 0);
				
		system("cls");
		return;
	
}

// Main function
void main()
{
	cin.clear();
	system("cls");
	ofstream totalduration("totaldur.txt",ios::app);
	clock_t t1, t2;
	t1 = clock();
	int welcome = 0;
	string User, password;
	int choice;
	int font;
	cout << "\n\n************** WELCOME TO WISDOM BOOK SHOP *******************" << endl;
	cout << "\n(This Application Lets you to Display & Search \nAny Details You want about Books Available in Wisdom BookShop)" << endl;
	cout << "********************Please login to Access********************" << endl;
	do {
		cin.clear();
		if (welcome != 0)
			system("cls");
		welcome++;
		cout << "\n\n\tPlease Choose from the Following Login Options\n\n";
		cout << "\t1. Admin Login  \n\t2. Staff Login  \n\t3. Guest Login  \n\t4. Change Font Size \n\t5. Change Theme \n\t0. Exit \n";
		
		do
		{
			error = 0;
			cout << "\n\tPlease enter your selection : ";
			cin >> choice;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input. " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		

		switch (choice)
		{
		case 1:		{
					cout << "\n\tPlease enter the admin username : ";
					cin >> User;
					password = getpass("Please enter the password: ", true);
					Login(User, password); 
					} break;

		case 2:		{
					cout << "\n\tPlease enter the staff username : ";
					cin >> User;
					password = getpass("Please enter the password: ", true);
					staff(User, password); 
					} break;
		
		case 3:		{	
					User = "Guest";
					password = "guest2";
					staff(User, password);
					}break;

		case 4:		fontsize(); break;

		case 5:		color(); break;
		
		case 0:		{
					t2 = clock();
					float duration((float)t2 - (float)t1);
					float seconds = duration / CLOCKS_PER_SEC;
					cout << "\n\tTotal time of wisdom enquiry system used for ";
					timeconverter(seconds);
					cout << "\n\n\tWelcome Again\n";
					totalduration << seconds << endl;
					system("pause");
					return; }
		default:	cout << "\n\n\tInvalid entry!!! Please try again (Enter 1, 2, 3, 4, 5 or 6)" << endl; break;
		}
	} while (choice != 0);
	return;
}

// Login Function for Staffs 
void staff(string& user, string& pass1)
{
	ofstream loginreport("staff login report.txt",ios::app);
	ofstream guestlogin("guest login.txt",ios::app);
	string Users[200];
	string Pass[200];
	bool valid = false;

	int x = 0;
	ifstream UsFile;
	UsFile.open("user.txt");
	char choice;

	UsFile >> Users[x] >> Pass[x];
	while (UsFile)	// read user names and passwords from file and store them in arrays
	{
		x++;
		if (x >= 200)	// not to exeed the array limit
			break;
		UsFile >> Users[x] >> Pass[x];
	}
	
	for (int a = 0; a < x; a++)
	{
		if (user == Users[a] && pass1 == Pass[a])	// match user names and passwords with the array components
		{
			cout << "\tSuccessfully logged into staff account" << endl;
			loginreport << Users[a] << " Logged in " << currentDateTime();
			staffFunctions(Users[a], loginreport, guestlogin);
			valid = true;
			break;
		}
		if (user == "Guest" & pass1 == "guest2")
		{
			cout << "\n\tSuccessfully logged into guest account" << endl;
			guestlogin << user << " Logged in " << currentDateTime();
			staffFunctions(user, loginreport, guestlogin);
			valid = true;
			break;
		}
	}
	if (!valid)
	{		
		
			cout << "\n\tUsername & password is invalid \n\n";
			system("pause");
	}
}

// Login Function for Admin
void Login(string& admin, string& password)
{
	ofstream adminloginreport("adminloginreport.txt", ios::app);
	string Users[200];
	string Pass[200];
	bool valid = false;

	int x = 0;
	ifstream UsFile;
	UsFile.open("admin.txt");
	char choice;

	UsFile >> Users[x] >> Pass[x];
	while (UsFile)	// read user names and passwords from file and store them in arrays
	{
		x++;
		if (x >= 200)	// not to exeed the array limit
			break;
		UsFile >> Users[x] >> Pass[x];
	}
	

	for (int a = 0; a < x; a++)
	{
		if (admin == Users[a] && password == Pass[a])	// match user names and passwords with the array components
		{
			cout << "\n\tSuccessfully logged into admin account" << endl;
				adminloginreport << admin << " Logged in " << currentDateTime() ;
			adminMenu(adminloginreport);
			adminloginreport.close();
			valid = true;
			break;
		}
	}
	if (!valid)
	{
	
			cout << "\n\tUsername & password is invalid try again\t\t\n\n";
			system("pause");
	}
}

// List of all admin functions available 
void AdminOptions()
{
	system("pause");
	system("cls");
	
	cout << "\n\n	WELCOME TO WISDOM'S ADMINISTRATOR MENU" << endl;
	cout << "	======= == ======== ============= ====" << endl;
	cout << "\n\t1 : ADD NEW BOOKS" << endl;
	cout << "\n\t2 : DISPLAY ALL BOOKS" << endl;
	cout << "\n\t3 : SEARCH BOOKS" << endl;
	cout << "\n\t4 : DELETE BOOKS" << endl;
	cout << "\n\t5 : UPDATE BOOKS" << endl;
	cout << "\n\t6 : VIEW SPECIAL OFFERS " << endl;
	cout << "\n\t7 : VIEW LOGIN REPORT " << endl;
	cout << "\n\t8 : HELP " << endl;
	cout << "\n\t0 : RETURN TO MAIN MENU" << endl;
}

// List of Search Options
void SearchOptions()
{
	system("cls");
	cout << "\n\tSEARCH BOOKS" << endl;
	cout << "\t====== =====\n\n" << endl;
	cout << "\n\t1 : SEARCH BOOKS BY ID " << endl;
	cout << "\n\t2 : SEARCH BOOKS BY CATEGORY" << endl;
	cout << "\n\t3 : SEARCH BY BOOK NAME" << endl;
	cout << "\n\t4 : SEARCH BY BOOK AUTHOR " << endl;
	cout << "\n\t5 : SEARCH BY PRICE " << endl;
	cout << "\n\t0 : BACK TO ADMIN MENU " << endl;
}

// List of Update Options
void UpdateOptions()
{
	system("cls");
	cout << "\n\tUPDATE BOOKS" << endl;
	cout << "\t====== =====\n\n" << endl;
	cout << "\n\t1 : SEARCH & UPDATE BY BOOK ID " << endl;
	cout << "\n\t2 : SEARCH & UPDATE BY BOOK CATEGORY" << endl;
	cout << "\n\t3 : SEARCH & UPDATE BY BOOK NAME " << endl;
	cout << "\n\t4 : SEARCH & UPDATE BY BOOK AUTHOR " << endl;
	cout << "\n\t5 : DISPLAY LIST & UPDATE" << endl;
	cout << "\n\t0 : BACK TO ADMIN MENU " << endl;
}

// List of Delete Options 
void DeleteOptions()
{
	system("cls");
	cout << "\n\tDELETE BOOKS" << endl;
	cout << "\t====== =====\n\n" << endl;
	cout << "\n\t1 : SEARCH & DELETE BY BOOK ID " << endl;
	cout << "\n\t2 : SEARCH & DELETE BY BOOK CATEGORY" << endl;
	cout << "\n\t3 : SEARCH & DELETE BY BOOK NAME " << endl;
	cout << "\n\t4 : SEARCH & DELETE BY BOOK AUTHOR " << endl;
	cout << "\n\t5 : DISPLAY LIST & DELETE " << endl;
	cout << "\n\t0 : BACK TO ADMIN MENU " << endl;
}

//Admin Menu Contains all the calling functions of Admin Options 
void adminMenu(ofstream& adminloginreport)
{
	ofstream adminduration;
	adminduration.open("admindur.txt", ios::app);
	clock_t t1, t2;
	t1 = clock();
	int Sel,updateops, dltops,searchops;
	Bookdetails Booklist[1000];
	int fileline = addBooksfromFile(Booklist);
	
	do {
		AdminOptions();
		do
		{
			error = 0;
			cout << "\n\n\tPlease enter your selection : ";
			cin >> Sel;
			if (cin.fail())
			{
				cout << "\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);

		switch (Sel)
		{
		case 1:	fileline = addBook(Booklist, fileline); break;
		case 2: printBooks(Booklist, fileline); break;
		case 3: Sel = 3; break;
		case 4: Sel = 4; break;
		case 5: Sel = 5; break;
		case 6: printBookOffers(Booklist, fileline); break;
		case 7: loginreport(adminloginreport); break;
		case 8: HelpFunction(); break;
		case 0: {
				adminloginreport << " || Logged out - " << currentDateTime() << endl;
				adminloginreport.close();
				t2 = clock();
				float duration((float)t2 - (float)t1);
				float seconds = duration / CLOCKS_PER_SEC;
				cout << "\n\tDear Admin of Wisdom!!!..\n\tYou have spent ";
				timeconverter(seconds);
				cout<< " with Wisdom's enquiry system" << endl;
				cout << "\n\tSee you Soon......" << endl;
				adminduration << seconds << endl;
				system("pause");
				return;
				}break;
		default: cout << "\n\tInvalid selection... try again...." ;
		}
		if (Sel == 3)
		{
			do {
				SearchOptions();
				
				do
				{
					error = 0;
					cout << "\n\n\tPlease enter your selection : ";
					cin >> searchops;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				switch (searchops)
				{
				case 1: searchBooks(Booklist, fileline); break;
				case 2: searchbycategory(Booklist, fileline); break;
				case 3: searchBookbyName(Booklist, fileline); break;
				case 4: searchbyauthor(Booklist, fileline); break;
				case 5: searchBookbyPrice(Booklist, fileline); break;
				case 0:break ;
				default: cout << "\n\tInvalid selection... try again....";
				}
			} while (searchops != 0);
		}
		if (Sel == 4)
		{
			do {
				DeleteOptions();
				
				do
				{
					error = 0;
					cout << "\n\n\tPlease enter your selection : ";
					cin >> dltops;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				switch (dltops)
					{
				case 1: DeleteByID(Booklist, fileline); break;
				case 2: DeletebyCategory(Booklist,fileline); break;
				case 3: DeletebyBname(Booklist, fileline) ; break;
				case 4: DeletebyAuthor(Booklist, fileline); break;
				case 5: displaydelete(Booklist, fileline); break;
				case 0:break;
				default: cout << "\n\tInvalid selection... Try again....";
					}
				} while (dltops != 0);
		}
		if (Sel == 5)
		{
			
			do {
				UpdateOptions();
				
				do
				{
					error = 0;
					cout << "\n\n\tPlease enter your selection : ";
					cin >> updateops;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				switch (updateops)
					{
				case 1: UpdateByID(Booklist, fileline); break;
				case 2: UpdatebyCategory(Booklist, fileline) ; break;
				case 3: UpdateByName(Booklist, fileline); break;
				case 4: updateByAuthor(Booklist, fileline); break;
				case 5: displayUpdate( Booklist, fileline); break;
				case 0:break;
				default: cout << "\n\tInvalid selection... Try again....";
					}
			} while (updateops != 0);
		}
	} while (Sel != 0);
	
}

// Function to call Staff Functions 
void staffFunctions(string name, ofstream& loginreport, ofstream& guestlogin)
{
	clock_t t1, t2;
	t1 = clock();
	int Sel;
	ofstream guestdur, staffdur;
	guestdur.open("guestduration.txt", ios::app);
	staffdur.open("staffduration.txt", ios::app);
	Bookdetails Booklist[1000];
	int fileline = addBooksfromFile(Booklist);
	system("pause");
		
	do {
		system("cls");
		cout <<  "\n\n\tWELCOME TO WISDOM'S " << name <<"  USER "<< endl;
		cout <<  "\t======= == ======== ====== ====" << endl;
		cout <<  "\n	1 : DISPLAY ALL BOOKS" << endl;
		cout <<  "\n	2 : SEARCH BOOKS BY ID NUMBER" << endl;
		cout <<  "\n	3 : SEARCH BOOKS BY CATEGORY" << endl;
		cout <<  "\n	4 : SEARCH BY BOOK NAME" << endl;
		cout <<  "\n	5 : SEARCH BY BOOK AUTHOR " << endl;
		cout <<  "\n	6 : SEARCH BY PRICE " << endl;
		cout <<  "\n	7 : VIEW SPECIAL OFFERS " << endl;
		cout <<  "\n	8 : HELP " << endl;
		cout <<  "\n	0 : RETURN TO MAIN MENU" << endl;
		
		do
		{
			error = 0;
			cout << "\n\n\tPlease enter your selection : ";
			cin >> Sel;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);

		switch (Sel)
		{
		case 1: printBooks(Booklist, fileline); break;
		case 2: searchBooks(Booklist, fileline); break;
		case 3: searchbycategory(Booklist, fileline); break;
		case 4: searchBookbyName(Booklist, fileline); break;
		case 5: searchbyauthor(Booklist, fileline); break;
		case 6: searchBookbyPrice(Booklist, fileline); break;
		case 7: printBookOffers(Booklist, fileline); break;
		case 8: HelpFunction(); break;
		case 0: {if (name == "Guest")
				{
				guestlogin << " || Logged out - " << currentDateTime() << endl;
				guestlogin.close();
				t2 = clock();
				float duration((float)t2 - (float)t1);
				float seconds = duration / CLOCKS_PER_SEC;
				cout << "\n\tDear guest of Wisdom!!!..\n\tThank you for spent your precious ";
				timeconverter(seconds);
				cout<< "  with us" << endl;
				cout << "\n\tWelcome back soon again......!\n\n\t\t" << endl;
				guestdur << seconds << endl;
				system("pause");
				return;
				}
				else
				{
					loginreport << " || Logged out - " << currentDateTime() << endl;
					loginreport.close();
					t2 = clock();
					float duration((float)t2 - (float)t1);
					float seconds = duration / CLOCKS_PER_SEC;
					cout << "\n\tDear " << name << " of Wisdom!!!..\n\tYou have spent ";
					timeconverter(seconds);
					cout << " with Wisdom's enquiry system" << endl;
					cout << "\n\tSee you Soon......" << endl;
					staffdur << seconds << endl;
					system("pause");
				return;
				}
		}break;
		default: { while (Sel > 7)
			{
			cout << "\n\n\tInvalid selection... Try again...." << endl;
			
			do
			{
				error = 0;
				cout << "\n\tPlease enter your selection : ";
				cin >> Sel;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			}
				}
		}		
	} while (Sel != 0);
	
}

// Function to Adding login report to file
void loginreport(ofstream& adminloginreport)
{
	system("cls");
	ifstream admin, staff, guest,admindu,staffdu,guestdu,totalduration;
	admin.open("adminloginreport.txt");
	staff.open("staff login report.txt");
	guest.open("guest login.txt");
	admindu.open("admindur.txt");
	staffdu.open("staffduration.txt");
	guestdu.open("guestduration.txt");
	totalduration.open("totaldur.txt");

	string report;
	
	int x;
	cout << "\n\n\n\tLogin Report You Can Check Login Information of Each User" << endl;
	cout << "\t===== ====== === === ===== ===== =========== == ==== ====" << endl;
	char choice;
	do {
		bool file = false;
		float duration = 0;
		float total = 0;
		cout << "\n\n\t1. View Admin Login Report :  ";
		cout << "\n\n\t2. View Staff Login Report :  ";
		cout << "\n\n\t3. View Guest Login Report :  ";
		cout << "\n\n\t4. Total duration used by admin : ";
		cout << "\n\n\t5. Total duration used by staffs : ";
		cout << "\n\n\t6. Total duration used by guests : ";
		cout << "\n\n\t7. Overall duration used : ";
		cout << "\n\n\t8. Erase All Login Reports :  ";
		cout << "\n\n\t0. Return to Admin Menu :  ";
		do
		{
			error = 0;
			cout << " \n\n\tSelect an option from the above menu : ";
			cin >> x;
			if (cin.fail())
			{
				cout << "\n\tInvalid Entry Try Again ";
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		if (x == 1) {
			cout << " \n\nUser Name---Login Date & Time -----------------------Logout Date & Time "<<endl;
			while (admin)
			{
				getline(admin, report);
				cout << report << endl;
				file = true;
			}
			if (!file)
			{
				cout << "\n\tNo Login Reports found" << endl;
				break;
			}
		}
		else if (x == 2) {
			cout << " \n\nUser Name---Login Date & Time -----------------------Logout Date & Time " << endl;
			while (staff)
			{
				getline(staff, report);
				cout << report << endl;
				file = true;
			}
			if(!file)
			{
				cout << "\n\tNo Login Reports found" << endl;
				break;
			}
		}
		else if (x == 3)
		{
			cout << " \n\nUser Name---Login Date & Time -----------------------Logout Date & Time " << endl;
			while (guest)
			{
				getline(guest, report);
				cout << report << endl;
				file = true;
			}
			if (!file)
			{
				cout << "\n\tNo Login Reports found" << endl;
				break;
			}
		}
		else if (x == 4)
		{
			admindu >> duration;
			while (admindu)
			{				
				total = total+ duration;
				admindu >> duration;
				file = true;
			}
			if (file == true)
				cout << "\n\n\tTotal time used by admin : ";
				timeconverter(total);
				cout << endl;
			if (!file)
			{
				cout << "\n\tNo Login Reports found" << endl;
				break;
			}
		}
		else if (x == 5)
		{
			staffdu >> duration;
			while (staffdu)
			{
				total = total + duration;
				staffdu >> duration;
				file = true;
			}
			if (file == true)
				cout << "\n\n\tTotal time used by staffs : ";
				timeconverter(total);
				cout << endl; 
			if (!file)
			{
				cout << "\n\tNo Login Reports found" << endl;
				break;
			}
		}
		else if (x == 6)
		{
			guestdu >> duration;
			while (guestdu)
			{
				total = total + duration;
				guestdu >> duration;
				file = true;
			}
			if (file == true)
				cout << "\n\n\tTotal time used by staffs : "; 
				timeconverter(total);
				cout << endl;
			if (!file)
			{
				cout << "\n\tNo Login Reports found" << endl;
				break;
			}
		}
		else if (x == 7)
		{
			totalduration >> duration;
			while (totalduration)
			{
				total = total + duration;
				totalduration >> duration;
				file = true;
			}
			
			if (file == true)
				cout << "\n\n\tTotal of overall time used : ";
				timeconverter(total);
				cout << endl;
			if (!file)
			{
				cout << "\n\tNo Login Reports found" << endl;
				break;
			}
		}

		else if (x == 8)
		{
			adminloginreport.close();
			admin.close();
			staff.close();
			guest.close();
			admindu.close();
			staffdu.close();
			guestdu.close();
			totalduration.close();
			remove("adminloginreport.txt");
			remove("staff login report.txt");
			remove("guest login.txt");
			remove("admindur.txt");
			remove("staffduration.txt");
			remove("guestduration.txt");
			remove("totaldur.txt");
			cout << "\n\tErased Successfully" << endl;
			break;
		}
		else if(x != 0)
			cout << "\n\tInvalid Entry try again ";
	} while (x != 0);

	admin.close();
	staff.close();
	guest.close();
	admindu.close();
	staffdu.close();
	guestdu.close();
	totalduration.close();
}

// Function to Add Books from the User Input
int addBook(Bookdetails Booklist[1000], int fileline)
{
	void addAddnewBookstoFile(Bookdetails Addnew);
	int No, x;
	system("cls");
	cout << "\n\n\tADD NEW BOOK TO WISDOM'S DATABASE " << endl;
	cout << "\t=== === ==== == ======== ========" << endl;
	
	do
	{
		error = 0;
		cout << "\n\tHow many books you want to add : ";
		cin >> No;
		if (cin.fail())
		{
			cout << "\n\tPlease enter a valid input : " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	// Get inputs from the user
	cout << "\n\n\tPlease enter following details to add a new book to the system" << endl;
	
	int maximum = INT_MAX;
	if (No<1000)
	{
		cout<<"\n----------------------------------------------------------------------------";
			for (x = fileline; x < fileline + No; x++)
			{

				
				do
				{
					error = 0;
					cout << "\n\tBook ID : ";
					cin >> Booklist[x].bookID;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				for (int a = 0; a < fileline; a++)
				{
					while (Booklist[a].bookID == Booklist[x].bookID)
					{
						for (int q = 0; q < fileline; q++)
						{
							maximum = Booklist[q].bookID;
						}
						cout<<"\n----------------------------------------------------------------------------";
						cout << "\n\tEntered Book ID Existing Already!!!! \n\n\tPlease enter a different ID (Suggested ID is " << maximum + 1 << ") : ";
						do
						{
							error = 0;
							cout << "\n\n\tBook ID : ";
							cin >> Booklist[x].bookID;
							if (cin.fail())
							{
								cout << "\n\tPlease enter a valid input : ";
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
					}
				}
				cout<<"\n----------------------------------------------------------------------------";
				cout << "\n\tBook Category : ";
				cin.ignore();
				getline(cin, Booklist[x].category);
				cout<<"\n----------------------------------------------------------------------------";
				cout << "\n\tBook Name : ";
				cin.ignore();
				getline(cin, Booklist[x].name);
				cout<<"\n----------------------------------------------------------------------------";
				cout << "\n\tBook Description : ";
				getline(cin, Booklist[x].description);
				cout<<"\n----------------------------------------------------------------------------";
				cout << "\n\tBook Publisher : ";
				getline(cin, Booklist[x].publisher);
				cout<<"\n----------------------------------------------------------------------------";
				cout << "\n\tBook Author : ";
				getline(cin, Booklist[x].author);
				cout<<"\n----------------------------------------------------------------------------";
				do
				{
					error = 0;
					cout << "\n\tPrice of the Book : $";
					cin >> Booklist[x].price;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid Price : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
								
				cout<<"\n----------------------------------------------------------------------------";
				do
				{
					error = 0;
					cout << "\n\tQuantity in Store : ";
					cin >> Booklist[x].quantity;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid Price : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				cout << "\n\n\tBook details added successfully...." << endl;
				addAddnewBookstoFile(Booklist[x]);
			}
	}
	else
		cout << "\n\tNo enough space to store ..." << endl;
	return x;
}

// Help Function 
void HelpFunction()
{
	cin.clear();
	system("cls");
	cout << "\n\n\tWELCOME TO WISDOM DATABASE HELP SECTION " << endl;
	cout << "\t======= == ====== ======== ==== =======" << endl;
	cout << "\n\n\t# All the Functions mention in the numbered lists should be commanded in particular number according to choice " << endl;
	cout << "\n\t# If there any selection to be done you can choose by 'Y' for Yes and 'N' for No \n\n\t# It is not case sensitive therefore you can enter either capital or simple" << endl;
	cout << "\n\t# Search function is highly effective in this Program, You don't have to remember complete book name or category to search" << endl;
	cout << "\n\t# Just Enter first three letter of your Keywords to search, it is enough. You will get the accurate result" << endl;
	cout << "\n\t# You can update or delete any file using search function. Select the proper option to complete your task" << endl;
	cout << "\n\t# If you find an Error with this No.(1001) it means somehow main database file might be deleted or moved to another location. Please contact Your MIS team to Fix the Issue" << endl;
	cout << "\n\t# If You find any Book starts with ""Sp.""(this is not case sensitive) It means this book is listed under special Offers\n\n\t# To move from Special Offer to normal List remove this ""Sp."" from the Book Descriptionription (Applicable only for Admin)\n\n\n\n " << endl;
	system("pause");
}

// function to Insert addnew books details to file
void addAddnewBookstoFile(Bookdetails Addnew)
{

	ofstream bookfile;
	bookfile.open("list.txt", ios::app);

	bookfile << endl << Addnew.bookID << endl;
	bookfile << Addnew.category << endl;
	bookfile << Addnew.name << endl;
	bookfile << Addnew.description << endl;
	bookfile << Addnew.publisher << endl;
	bookfile << Addnew.author << endl;
	bookfile << Addnew.price << endl;
	bookfile << Addnew.quantity << endl;

	bookfile.close();
}

// Add books from the file to Array
int addBooksfromFile(Bookdetails Booklist[1000])
{
	int x = 0;
	ifstream bookfile;
	bookfile.open("list.txt");
	system("cls");
	if (bookfile) {
		cout << "\n\n\n\t==== ==== ===== === ================ " << endl;
		cout << "\tBOOK LIST FOUND AND LOADED.......... " << endl;
		cout << "\t==== ==== ===== === ================\n\n\n\n\t " << endl;
		do
		{
			bookfile >> Booklist[x].bookID;
			
			bookfile.ignore();
			getline(bookfile, Booklist[x].category);
			getline(bookfile, Booklist[x].name);
			getline(bookfile, Booklist[x].description);
			getline(bookfile, Booklist[x].publisher);
			getline(bookfile, Booklist[x].author);
			bookfile >> Booklist[x].price;
			bookfile >> Booklist[x].quantity;
			x++;
		} while (bookfile);
	}

	else
	{
		cout << "\n\n\t!!! Sorry Database not Found, Error Occured (1001) !!!" << endl;
		cout << "\n\tCheck in the Help section to find the Problem Cause  "<<endl;
					
		return 0;
	}
	return --x;
}

// Display Functions
//============================================================================================
// Display All books in the screen
void printBooks(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	system("cls");
	system("color 0f");
	cout << "\n\n\tAVAILABLE BOOKS IN WISDOM BOOK SHOP" << endl;
	cout << "\t========= ===== == ====== ==== ====" << endl;
	
	for (int x = 0; x<fileline; x++)
	{
		cout << "\n\n---------------------------------------------------------------"<<endl;
		cout << "\tBook ID : " << Booklist[x].bookID << endl;
		cout << "\n\tBook Category : " << Booklist[x].category << endl;
		cout << "\n\tBook Name : " << Booklist[x].name << endl;
		cout << "\n\tBook Descriptionription : " << Booklist[x].description << endl;
		cout << "\n\tBook Publisherlisher : " << Booklist[x].publisher << endl;
		cout << "\n\tBook Author : " << Booklist[x].author << endl;
		cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
		cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
		cout << "---------------------------------------------------------------"<<endl;
	}
	system("pause");
}

// Function to Display Special Offers 
void printBookOffers(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	cin.clear();
	cout << "\n\n\tSPECIAL OFFERS " << endl;
	cout << "\t======= ======" << endl;

	for (int x = 0; x<fileline; x++)
	{
		while (Booklist[x].description[0] == 'S' || Booklist[x].description[0] == 's' && Booklist[x].description[1] == 'P' || Booklist[x].description[1] == 'p' && Booklist[x].description[2] == '.')
		{
			cout << "\n\n---------------------------------------------------------------" << endl;
			cout << "\n\tBook ID : " << Booklist[x].bookID << endl;
			cout << "\n\tBook Category : " << Booklist[x].category << endl;
			cout << "\n\tBook Name : " << Booklist[x].name << endl;
			cout << "\n\tBook Descriptionription : " << Booklist[x].description << endl;
			cout << "\n\tBook Publisherlisher : " << Booklist[x].publisher << endl;
			cout << "\n\tBook Author : " << Booklist[x].author << endl;
			cout << "\n\tPrice of the Book : $" <<setprecision(10)<< Booklist[x].price << endl;
			cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
			cout << "---------------------------------------------------------------" << endl;
			x++;
		}
	}
	system("pause");
}

// Searching Functions
// ===========================================================================================
// Search Books by Book ID
void searchBooks(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	char choice;
	cout << "\n\n\tSEARCH BOOK BY ID" << endl;
	cout << "\t===== ==== == ==" << endl;
	int ID;
	do {
		
		bool found = false;
		
		do
		{
			error = 0;
			cout << "\n\tPlease enter the book ID : ";
			cin >> ID;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid number > '0' : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);

		for (int x = 0; x < fileline; x++)
		{
			if (ID == Booklist[x].bookID)
			{   cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "\tBook ID : " << Booklist[x].bookID << endl;
				cout << "\n\tBook Category : " << Booklist[x].category << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << setprecision(10)<< Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;
				break;
			}
		}

		do
		{
			error = 0;
			cout << "\n\tDo you want to search more books by ID? Y/N : ";
			cin >> choice;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);

		if (!found)
		{
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book Id is not found....\n\tWould you like to try again? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	
	cin.clear();
}

// Search Book by Author Name 
void searchbyauthor(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	string author;
	char choice;
	cout << "\n\n\tSEARCH BOOKS BY AUTHOR" << endl;
	cout << "\t====== ===== == ======" << endl;
	do {
		bool found = false;
		cout << "\n\n\tPlease enter the book Author to Search: ";
		cin >> author;

		author = ConvertToLower(author);

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].author = ConvertToLower(Booklist[x].author);
			for (int a = 0; a < Booklist[x].author.size(); a++)
			{
				if (author.length() <= 3)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
				if (author.length() == 4)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2] && author[3] == Booklist[x].author[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
				if (author.length() >= 5)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2] && author[3] == Booklist[x].author[a + 3] && author[4] == Booklist[x].author[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
			}
		}
		if (found)
		{
			do
			{
				error = 0;
				cout << "\n\tDo you want to search more books? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
		if (!found)
		{
			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book author is not found....\n\tWould you like to try again? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	cin.clear();
}

// Search Books by Name 
void searchBookbyName(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	string name;
	char choice;
	cout << "\n\n\tSEARCH BOOKS BY NAME" << endl;
	cout << "\t====== ====== == ====" << endl;
	do {
		bool found = false;
		cout << "\n\n\tPlease enter the book Name : ";
		cin.ignore();
		getline(cin, name);

		name = ConvertToLower(name);

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].name = ConvertToLower(Booklist[x].name);
			for (int a = 0; a < Booklist[x].name.size(); a++)
			{
				if (name.length() <= 3)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
				if (name.length() == 4)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2] && name[3] == Booklist[x].name[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
				if (name.length() >= 5)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2] && name[3] == Booklist[x].name[a + 3] && name[4] == Booklist[x].name[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
			}
		}
		if (found)
		{
			do
			{
				error = 0;
				cout << "\n\tDo you want to Search more books? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
		if (!found)
		{
			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book name is not found....\n\n\tRetry? Y/N :";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
}

// Search by Category
void searchbycategory(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	string category;
	char choice;

	cout << "\n\n\tSEARCH BOOKS BY CATEGORY" << endl;
	cout << "\t======= ===== == =======" << endl;
	do {
		bool found = false;
		cout << "\n\n\tPlease enter the book category to Search: ";
		cin.ignore();
		getline(cin, category);

		category = ConvertToLower(category);
		char sel, sel2;

		for (int x = 0; x < fileline; x++)
		{
			for (int a = 0; a < Booklist[x].category.size(); a++)
			{
				if (category.length() <= 3)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
				if (category.length() == 4)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2] && category[3] == Booklist[x].category[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
				if (category.length() >= 5)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2] && category[3] == Booklist[x].category[a + 3] && category[4] == Booklist[x].category[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;

					}
				}
			}
		}
		if (found)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want to search by any other categories? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);

		}
		if (!found)
		{
			
			do
			{
				error = 0;
				cout << "\tSorry... The given book category is not found....\n\tWould you like to try again? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');

}

// Search by Price
void searchBookbyPrice(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	double Bprice;
	int select, count = 0;
	char choice;
	cout << "\n\n\tSEARCH BOOKS BY PRICE" << endl;
	cout << "\t====== ====== == =====" << endl;
	do {
		count = 0;
		bool found = false;

		do
		{
			error = 0;
			cout << "\n\tPlease enter the book Price : $";
			cin >> Bprice;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		cout << "\n\tDo You want to Search Books  \n\n\t\t1. Less than $" << Bprice << "--\n\t\t2. Greater Than $" << Bprice << "--\n\t\t3. Exact to $" << Bprice << "\n\t\t0. Return to previous menu--";

		do
		{
			error = 0;
			cout << "\n\n\n\tSelect your choice : ";
			cin >> select;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		switch (select)
		{
		case 1: {
			for (int x = 0; x < fileline; x++)
			{
				if (Bprice >= Booklist[x].price)
				{
					cout << "\n\n---------------------------------------------------------------" << endl;
					cout << "\tBook ID : " << Booklist[x].bookID << endl;
					cout << "\n\tBook Name : " << Booklist[x].name << endl;
					cout << "\n\tBook Author : " << Booklist[x].author << endl;
					cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
					cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
					cout << "---------------------------------------------------------------" << endl;
					found = true;
					count = 1;
				}
			}
			if (found)
			{

				do
				{
					error = 0;
					cout << "\n\tDo you want to search more books? Y/N : ";
					cin >> choice;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				system("cls");
			}
			if (!found & count == 0)
			{

				do
				{
					error = 0;
					cout << "\n\tSorry... No books found Less than $" << Bprice << " ....\n\n\tRetry? Y/N :";
					cin >> choice;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				system("cls");
			}
		}break;
		case 2: {
			for (int x = 0; x < fileline; x++)
			{
				if (Bprice <= Booklist[x].price)
				{
					cout << "\n\n---------------------------------------------------------------" << endl;
					cout << "\tBook ID : " << Booklist[x].bookID << endl;
					cout << "\n\tBook Name : " << Booklist[x].name << endl;
					cout << "\n\tBook Author : " << Booklist[x].author << endl;
					cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
					cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
					cout << "---------------------------------------------------------------" << endl;
					found = true;
					count = 1;
				}
			}
			if (found)
			{

				do
				{
					error = 0;
					cout << "\n\tDo you want to search more books? Y/N : ";
					cin >> choice;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				system("cls");
			}
			if (!found && count == 0)
			{

				do
				{
					error = 0;
					cout << "\n\tSorry... No books found greater than $" << Bprice << " ....\n\n\tRetry? Y/N :";
					cin >> choice;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				system("cls");
			}
		}break;
		case 3: {
			for (int x = 0; x < fileline; x++)
			{
				if (Bprice == Booklist[x].price)
				{
					cout << "\n\n---------------------------------------------------------------" << endl;
					cout << "\tBook ID : " << Booklist[x].bookID << endl;
					cout << "\n\tBook Name : " << Booklist[x].name << endl;
					cout << "\n\tBook Author : " << Booklist[x].author << endl;
					cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
					cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
					cout << "---------------------------------------------------------------" << endl;
					found = true;
					count = 1;
				}
			}
			if (found)
			{

				do
				{
					error = 0;
					cout << "\n\tDo you want to search more books? Y/N : ";
					cin >> choice;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				system("cls");
			}
			if (!found && count == 0)
			{

				do
				{
					error = 0;
					cout << "\n\tSorry... No books found for price of $" << Bprice << " ....\n\n\tRetry? Y/N :";
					cin >> choice;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				system("cls");
			}
		}break;
		case 0: break;
		default: 
		{
			cout << "\n\tInvalid entry........" << endl;
			system("pause");
			break;
		}
		}
	} while (choice == 'y' || choice == 'Y');
}


// Deleting Functions
// ===========================================================================================
// Delete by Search Book ID
void DeleteByID(Bookdetails Booklist[1000], int& fileline)
{
	system("cls");
	char choice;
	cout << "\n\n\tDELETE BY SEARCH BOOK ID" << endl;
	cout << "\t====== == ====== ==== ==" << endl;
	do {
		int ID;
		bool found = false;
		bool again = false;
		char sel1;
		
		do
		{
			error = 0;
			cout << "\n\n\tPlease enter the book ID : ";
			cin >> ID;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		for (int x = 0; x < fileline; x++)
		{
			found = false;
			if (ID == Booklist[x].bookID)
			{
				cout << "\n\n---------------------------------------------------------------" << endl;
				cout << "\tBook Category : " << Booklist[x].category << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------" << endl;
				found = true;
			}
			if (found)
			{
				
				do
				{
					error = 0;
					cout << "\n\tDo you want to delete this book? Y/N : "<<endl;
					cin >> sel1;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				if (sel1 == 'y' || sel1 == 'Y')
				{
					for (int x = 0; x < fileline; x++)
					{
						if (ID == Booklist[x].bookID)
						{
							DeletebybID(Booklist, Booklist[x].bookID, x, fileline);
							cout << "\tSelected item Deleted Successfully..........." << endl;
							
							do
							{
								error = 0;
								cout << "\n\tDo you want to search more? Y/N : ";
								cin >> choice;
								if (cin.fail())
								{
									cout << "\n\tPlease enter a valid input : " << endl;
									error = 1;
									cin.clear();
									cin.ignore(80, '\n');
								}
							} while (error == 1);
							if (choice == 'n' || choice == 'N')
							{
								again = true;
								break;
							}
							else
								again = true;
						}
					}
				}
				if (sel1 == 'n' || sel1 == 'N')
				{
					return;
				}
			}
		}
		if (!found && !again)
		{
			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book ID is not found....\n\n\tWould you like to try again? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	system("pause");
}

// Delete books by Search Book Name
void DeletebyBname(Bookdetails Booklist[1000], int& fileline)
{
	string name;
	char choice;
	system("cls");
	cout << "\n\n\tSEARCH BOOKS BY NAME TO DELETE" << endl;
	cout << "\t====== ===== == ==== == ======" << endl;
	do {
		int detect = 0, find = 0;
		cout << "\n\n\tPlease enter the book Name : ";
		cin.ignore();
		getline(cin, name);

		name = ConvertToLower(name);
		char sel, sel2;
		bool found;
		bool again;
		for (int x = 0; x < fileline; x++)
		{
			found = false;
			again = true;
			Booklist[x].name = ConvertToLower(Booklist[x].name);
			for (int a = 0; a < Booklist[x].name.size(); a++)
			{
				if (name.length() <= 3)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
					}
				}
				if (name.length() == 4)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2] && name[3] == Booklist[x].name[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
					}
				}
				if (name.length() >= 5)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2] && name[3] == Booklist[x].name[a + 3] && name[4] == Booklist[x].name[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
					}
				}
			}
			if (found)
			{
				cout << "\n\tDo you want to delete this book details? Y/N : ";
				cin >> sel2;
				if (sel2 == 'y' || sel2 == 'Y')
				{
					DeletebybID(Booklist, Booklist[x].bookID, x, fileline);
					cout << "\n\n\t.....Deleted succesfully......" << endl;
					system("pause");
					found = false;
					x--;
				}
			}
			if (x == (fileline-1))
			{
				detect = 1;
				again = false;
			}
			
		}
		if (find == 1 && detect == 1)
		{
			
			do
			{
				error = 0;
				cout << "\n\n\tDo you want to search more books to delete by name? Y/N : ";
				cin >> sel;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			find--;
			detect--;
			if (sel == 'y' || sel == 'Y')
			{
				again = true;
				choice = 'y';
			}
			else if (sel == 'n' || sel == 'N')
			{
				again = true;
				break;
			}
		}
		
		if (!found && !again)
		{
			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book name is not found....\n\tWould you like to try again? Y/N :";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	system("pause");
}

// Delete by Search category
void DeletebyCategory(Bookdetails Booklist[1000], int& fileline)
{
	string category;
	bool found = false;
	bool again = false;
	int  bookid;
	char choice;
	system("cls");
	cout << "\n\n\tSEARCH BOOKS BY CATEGORY TO DELETE" << endl;
	cout << "\t====== ===== == ======== == ======" << endl;
	int count = 0;
	do {
		int detect = 0, find = 0;
		cout << "\n\n\tPlease enter the book category : ";
		cin.ignore();
		getline(cin, category);

		category = ConvertToLower(category);
		char sel, sel1;
		for (int x = 0; x < fileline; x++)
		{
			found = false;
			Booklist[x].category = ConvertToLower(Booklist[x].category);
			for (int a = 0; a < Booklist[x].category.size(); a++)
			{
				if (category.length() <= 3)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
				if (category.length() == 4)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2] && category[3] == Booklist[x].category[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
				if (category.length() >= 5)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2] && category[3] == Booklist[x].category[a + 3] && category[4] == Booklist[x].category[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
			}
						
			if ((fileline - 1) == x)
				detect = 1;
		}
		if (count == 1)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want to delete this book details? Y/N : ";
				cin >> sel1;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			if (sel1 == 'y' || sel1 == 'Y')
			{
				for (int x = 0; x < fileline; x++)
				{
					if (Booklist[x].bookID == bookid)
					{
						DeletebybID(Booklist, Booklist[x].bookID, x, fileline);
						cout << "\tBooklist deleted successfully............" << endl;
						found = true;
						
						do
						{
							error = 0;
							cout << "\n\tDo you want to delete any other categories? Y/N : ";
							cin >> choice;
							if (cin.fail())
							{
								cout << "\n\tPlease enter a valid input : " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
					}
				}
			}
			else
				break;
		}
		else if (count >= 2)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want to delete any of book details from the results? Y/N : ";
				cin >> sel1;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			if (sel1 == 'y' || sel1 == 'Y')
			{
				
				do
				{
					error = 0;
					cout << "\n\tEnter the book ID you want to delete : ";
					cin >> bookid;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				for (int x = 0; x < fileline; x++)
				{
					if (Booklist[x].bookID == bookid)
					{
						DeletebybID(Booklist, Booklist[x].bookID, x, fileline);
						cout << "\n\tSeleted book list deleted successfully............" << endl;
						found = true;
						
						do
						{
							error = 0;
							cout << "\n\tDo you want to delete any other categories? Y/N : ";
							cin >> choice;
							if (cin.fail())
							{
								cout << "\n\tPlease enter a valid input : " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
					}

				}
				if (!found)
				{
					
					do
					{
						error = 0;
						cout << "\tEntered book ID not found in the list --- \n\tWould you like to try again? Y/N : " << endl;
						cin >> choice;
						if (cin.fail())
						{
							cout << "\n\tPlease enter a valid input : " << endl;
							error = 1;
							cin.clear();
							cin.ignore(80, '\n');
						}
					} while (error == 1);
				}
			}
			else
				break;
		}
				
		if (!found && !again && detect == 1)
		{
			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book category is not found....\n\tWould you like to try again? Y/N :";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	system("pause");
}

//Delete by Search Author
void DeletebyAuthor(Bookdetails Booklist[1000], int& fileline)
{
	string author;
	char choice;

	system("cls");
	cout << "\n\n\tSEARCH BOOKS BY AUTHOR TO DELETE" << endl;
	cout << "\t====== ===== == ====== == ======" << endl;
	do {
		int detect = 0, find = 0;
		cout << "\n\n\tPlease enter the Name of book Auhtor  : ";
		cin.ignore();
		getline(cin, author);

		author = ConvertToLower(author);
		char sel, sel2;
		bool found = false;
		bool again = false;
		for (int x = 0; x < fileline; x++)
		{
			found = false;
			Booklist[x].author = ConvertToLower(Booklist[x].author);
			for (int a = 0; a < Booklist[x].author.size(); a++)
			{
				if (author.length() <= 3)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
					}
				}
				if (author.length() == 4)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2] && author[3] == Booklist[x].author[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
					}
				}
				if (author.length() >= 5)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2] && author[3] == Booklist[x].author[a + 3] && author[4] == Booklist[x].author[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
					}
				}
			}
			if (found)
			{
				
				do
				{
					error = 0;
					cout << "\n\tDo you want to delete this book details? Y/N : ";
					cin >> sel2;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				if (sel2 == 'y' || sel2 == 'Y')
				{
					DeletebybID(Booklist, Booklist[x].bookID, x, fileline);
					cout << "\n\n\tDeleted succesfully......" << endl;
					system("pause");
					x--;
				}
			}
			if ((fileline - 1) == x)
				detect = 1;
		}
		if (find == 1 && detect == 1)
		{
			
			do
			{
				error = 0;
				cout << "\n\n\tDo you want to search more books to delete by author? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			find--, detect--;
			if (choice == 'n' || choice == 'N')
			{
				again = true;
				break;
			}
			else if(choice == 'y' || choice == 'Y')
			{
				again = true;
			}

		}

		if (!found && !again)
		{
			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book author name is not found....\n\tWould you like to try again? Y/N :";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	system("pause");
}

// Display All Books & delete by ID
void displaydelete(Bookdetails Booklist[1000], int& fileline)
{
	system("cls");
	cout << "\n\n\nBOOKS AVAILABLE IN WISDOM BOOKSHOP" << endl;
	cout << "===== ========= == ====== ========" << endl;
	char sel1, choice;
	int select, bookid;
	do {
		bool found = false;
		for (int x = 0; x < fileline; x++)
		{
			cout << "\n\n---------------------------------------------------------------" << endl;
			cout << "\tBook ID : " << Booklist[x].bookID << endl;
			cout << "\n\tBook Category : " << Booklist[x].category << endl;
			cout << "\n\tBook Name : " << Booklist[x].name << endl;
			cout << "\n\tBook Descriptionription : " << Booklist[x].description << endl;
			cout << "\n\tBook Publisherlisher : " << Booklist[x].publisher << endl;
			cout << "\n\tBook Author : " << Booklist[x].author << endl;
			cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
			cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
			cout << "---------------------------------------------------------------" << endl;
		}
			
		do
		{
			error = 0;
			cout << "\n\tDo you want to delete any existing book details? Y/N : ";
			cin >> sel1;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		if (sel1 == 'y' || sel1 == 'Y')
		{
			
			do
			{
				error = 0;
				cout << "\n\tEnter the book ID you want to delete : ";
				cin >> bookid;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			for (int x = 0; x < fileline; x++)
			{
				if (bookid == Booklist[x].bookID)
				{
					found = true;
					DeletebybID(Booklist, Booklist[x].bookID, x, fileline);
					cout << "\n\tSelected item deleted successfully..........." << endl;
					cout << "\n\tWould you like to delete more books? Y/N :";
					cin >> choice;
				}
			}
			if (!found)
			{
				
				do
				{
					error = 0;
					cout << "\n\n\tEntered book ID not found in the list --- \n\n\tWould you like to try again? Y/N : " ;
					cin >> choice;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
			}
		}
		else
			break;
	} while (choice == 'y' || choice == 'Y');

	system("pause");
}

// Delete function to delete by Book ID
void DeletebybID(Bookdetails Booklist[1000], int  bookID, int x, int& fileline)
{
	ofstream ofile;
	ofile.open("list.txt");

	while (ofile)
	{
		for (int z = 0; z < fileline; z++)
		{
			if (Booklist[z].bookID != Booklist[x].bookID)
			{
				ofile << endl << Booklist[z].bookID << endl;
				ofile << Booklist[z].category << endl;
				ofile << Booklist[z].name << endl;
				ofile << Booklist[z].description << endl;
				ofile << Booklist[z].publisher << endl;
				ofile << Booklist[z].author << endl;
				ofile << Booklist[z].price << endl;
				ofile << Booklist[z].quantity << endl;
			}
		}
		ofile.clear();
		ofile.close();
	}
	addBooksfromFile(Booklist);
	fileline--;
}

// Updating Functions
// ===========================================================================================
// Search & Update by Category
void UpdatebyCategory(Bookdetails Booklist[1000], int fileline)
{
	string category;
	bool found = false;
	bool again = false;
	int  bookid;
	char choice;
	system("cls");
	cout << "\n\n\tSEARCH BOOKS BY CATEGORY TO UPDATE" << endl;
	cout << "\t====== ===== == ======== == ======" << endl;
	int count = 0;
	do {
		int detect = 0, find = 0;
		cout << "\n\tPlease enter the book Category  : ";
		cin >> category;
		char sel, sel1;
		category = ConvertToLower(category);
		found = false;
		again = false;
		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].category = ConvertToLower(Booklist[x].category);
			for (int a = 0; a < Booklist[x].category.size(); a++)
			{
				if (category.length() <= 3)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
				if (category.length() == 4)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2] && category[3] == Booklist[x].category[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
				if (category.length() >= 5)
				{
					if (category[0] == Booklist[x].category[a] && category[1] == Booklist[x].category[a + 1] && category[2] == Booklist[x].category[a + 2] && category[3] == Booklist[x].category[a + 3] && category[4] == Booklist[x].category[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
			}

			if ((fileline - 1) == x)
			{
				detect = 1;
				again = false;
			}
		}
		if (count == 1 && found == true)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want to update this book details? Y/N : ";
				cin >> sel1;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			if (sel1 == 'y' || sel1 == 'Y')
			{
				for (int x = 0; x < fileline; x++)
				{
					if (Booklist[x].bookID == bookid)
					{
						Update(Booklist, x, fileline);
												
						do
						{
							error = 0;
							cout << "\n\tDo you want to update any other categories? Y/N : ";
							cin >> choice;
							if (cin.fail())
							{
								cout << "\n\tPlease enter a valid input : " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
						if (choice == 'y' || choice == 'Y')
							count = 0;
					}
				}
			}
			else
				break;
		}
		else if (count >= 2 && found == true)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want update any of book details from the results? Y/N : ";
				cin >> sel1;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			if (sel1 == 'y' || sel1 == 'Y')
			{
				
				do
				{
					error = 0;
					cout << "\n\tEnter the book ID you want to update : ";
					cin >> bookid;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				for (int x = 0; x < fileline; x++)
				{
					if (Booklist[x].bookID == bookid)
					{
						Update(Booklist, x, fileline);
						again = true;
						
						do
						{
							error = 0;
							cout << "\n\tDo you want to update any other categories? Y/N : ";
							cin >> choice;
							if (cin.fail())
							{
								cout << "\n\tPlease enter a valid input : " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
						count = 0;
					}

				}
				if (found == true && again == false)
				{
					
					do
					{
						error = 0;
						cout << "\tEntered book ID not found in the list --- \n\tWould you like to try again? Y/N : " << endl;
						cin >> choice;
						if (cin.fail())
						{
							cout << "\n\tPlease enter a valid input : " << endl;
							error = 1;
							cin.clear();
							cin.ignore(80, '\n');
						}
					} while (error == 1);
					count = 0;
				}
			}
			else
				break;
		}

		if (!found && !again && detect == 1)
		{
			do
			{
				error = 0;
				cout << "\tSorry... The given book category is not found....Try again? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	system("pause");
}

// Search & Update by name  
void UpdateByName(Bookdetails Booklist[1000], int fileline)
{
	string name;
	bool found = false;
	bool again = false;
	int  bookid;
	char choice;
	system("cls");
	cout << "\n\n\tSEARCH BOOKS BY NAME TO UPDATE" << endl;
	cout << "\t====== ===== == ==== == ======" << endl;
	int count = 0;
	do {
		int detect = 0, find = 0;
		cout << "\n\tPlease enter the book name  : ";
		cin >> name;
		char sel, sel1;
		name = ConvertToLower(name);
		found = false;
		again = false;
		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].name = ConvertToLower(Booklist[x].name);
			for (int a = 0; a < Booklist[x].name.size(); a++)
			{
				if (name.length() <= 3)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
				if (name.length() == 4)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2] && name[3] == Booklist[x].name[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
				if (name.length() >= 5)
				{
					if (name[0] == Booklist[x].name[a] && name[1] == Booklist[x].name[a + 1] && name[2] == Booklist[x].name[a + 2] && name[3] == Booklist[x].name[a + 3] && name[4] == Booklist[x].name[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
			}
		if ((fileline - 1) == x)
			{
				detect = 1;
				again = false;
			}
		}
		if (count == 1 && found == true)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want to update this book details? Y/N : ";
				cin >> sel1;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			if (sel1 == 'y' || sel1 == 'Y')
			{
				for (int x = 0; x < fileline; x++)
				{
					if (Booklist[x].bookID == bookid)
					{
						Update(Booklist, x, fileline);
						
						do
						{
							error = 0;
							cout << "\n\tDo you want to update any other names? Y/N : ";
							cin >> choice;
							if (cin.fail())
							{
								cout << "\n\tPlease enter a valid input : " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
						if (choice == 'y' || choice == 'Y')
							count = 0;
					}
				}
			}
			else
				break;
		}
		else if (count >= 2 && found == true)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want to update any book details from the results? Y/N : ";
				cin >> sel1;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			if (sel1 == 'y' || sel1 == 'Y')
			{
				
				do
				{
					error = 0;
					cout << "\n\tEnter the book ID you want to update : ";
					cin >> bookid;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				for (int x = 0; x < fileline; x++)
				{
					if (Booklist[x].bookID == bookid)
					{
						Update(Booklist, x, fileline);
						again = true;
						
						do
						{
							error = 0;
							cout << "\n\tDo you want to update any other names? Y/N : ";
							cin >> choice;
							if (cin.fail())
							{
								cout << "\n\tPlease enter a valid input : " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
						count = 0;
					}

				}
				if (found == true && again == false)
				{
					
					do
					{
						error = 0;
						cout << "\n\tEntered book ID not found in the list --- \n\tWould you like to try again? Y/N : " << endl;
						cin >> choice;
						if (cin.fail())
						{
							cout << "\n\tPlease enter a valid input : " << endl;
							error = 1;
							cin.clear();
							cin.ignore(80, '\n');
						}
					} while (error == 1);
					count = 0;
				}
			}
			else
				break;
		}

		if (!found && !again && detect == 1)
		{
			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book name is not found....Try again? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	system("pause");
}

// Search and Update by Book ID
void UpdateByID(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	int BookID;
	string name;
	bool found = false;
	char choice;
	cout << "\n\n\tSEARCH BOOKS BY ID TO UPDATE" << endl;
	cout << "\t====== ===== == == == ======" << endl;
	do {
		
		do
		{
			error = 0;
			cout << "\n\tPlease enter the book ID : ";
			cin >> BookID;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		
		char sel;
		
		for (int x = 0; x < fileline; x++)
		{

			if (BookID == Booklist[x].bookID)
			{   cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "\tBook ID : " << Booklist[x].bookID << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;
				if (found = true)
				{
					
					do
					{
						error = 0;
						cout << "\n\n\tDo you want to update this book details? Y/N : ";
						cin >> sel;
						if (cin.fail())
						{
							cout << "\n\tPlease enter a valid input : " << endl;
							error = 1;
							cin.clear();
							cin.ignore(80, '\n');
						}
					} while (error == 1);
					if (sel == 'y' || sel == 'Y')
					{   
						Update(Booklist, x, fileline);
						break;
					}
					else
						break;
				}
			}
		}

		if (!found)
		{
			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book ID is not found....\n\t Would you like to try again? Y/N : " << endl;
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	system("pause");
}

// Search & Update by Author
void updateByAuthor(Bookdetails Booklist[1000], int fileline)
{
	string author;
	bool found = false;
	bool again = false;
	int  bookid;
	char choice;
	system("cls");
	cout << "\n\n\tSEARCH BOOKS BY AUTHOR TO UPDATE" << endl;
	cout << "\t====== ===== == ====== == ======" << endl;
	int count = 0;
	do {
		int detect = 0, find = 0;
		cout << "\n\tPlease enter the book author  : ";
		cin >> author;
		char sel, sel1;
		author = ConvertToLower(author);
		found = false;
		again = false;
		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].author = ConvertToLower(Booklist[x].author);
			for (int a = 0; a < Booklist[x].author.size(); a++)
			{
				if (author.length() <= 3)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
				if (author.length() == 4)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2] && author[3] == Booklist[x].author[a + 3])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
				if (author.length() >= 5)
				{
					if (author[0] == Booklist[x].author[a] && author[1] == Booklist[x].author[a + 1] && author[2] == Booklist[x].author[a + 2] && author[3] == Booklist[x].author[a + 3] && author[4] == Booklist[x].author[a + 4])
					{
						cout << "\n\n---------------------------------------------------------------" << endl;
						cout << "\tBook ID : " << Booklist[x].bookID << endl;
						cout << "\n\tBook Name : " << Booklist[x].name << endl;
						cout << "\n\tBook Author : " << Booklist[x].author << endl;
						cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
						cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
						cout << "---------------------------------------------------------------" << endl;
						found = true;
						find = 1;
						count++;
						bookid = Booklist[x].bookID;
					}
				}
			}
		if ((fileline - 1) == x)
			{
				detect = 1;
				again = false;
			}
		}
		if (count == 1 && found == true)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want update this book details? Y/N : ";
				cin >> sel1;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);

			if (sel1 == 'y' || sel1 == 'Y')
			{
				for (int x = 0; x < fileline; x++)
				{
					if (Booklist[x].bookID == bookid)
					{
						Update(Booklist, x, fileline);
						cout << "\n\tDo you want to update any other books by author? Y/N : ";
						cin >> choice;
						if (choice == 'y' || choice == 'Y')
							count = 0;
					}
				}
			}
			else
				break;
		}
		else if (count >= 2 && found == true)
		{
			
			do
			{
				error = 0;
				cout << "\n\tDo you want update any of book details from the results? Y/N : ";
				cin >> sel1;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			if (sel1 == 'y' || sel1 == 'Y')
			{
				
				do
				{
					error = 0;
					cout << "\n\tEnter the book Id you want to update : ";
					cin >> bookid;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				for (int x = 0; x < fileline; x++)
				{
					if (Booklist[x].bookID == bookid)
					{
						Update(Booklist, x, fileline);
						again = true;
						
						do
						{
							error = 0;
							cout << "\n\tDo you want to update any other books by author? Y/N : ";
							cin >> choice;
							if (cin.fail())
							{
								cout << "\n\tPlease enter a valid input : " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
						count = 0;
					}

				}
				if (found == true && again == false)
				{
					
					do
					{
						error = 0;
						cout << "\n\tEntered bookID not found in the list --- \n\tWould you like to try again? Y/N : " << endl;
						cin >> choice;
						if (cin.fail())
						{
							cout << "\n\tPlease enter a valid input : " << endl;
							error = 1;
							cin.clear();
							cin.ignore(80, '\n');
						}
					} while (error == 1);
					count = 0;
				}
			}
			else
				break;
		}

		if (!found && !again && detect == 1)
		{			
			do
			{
				error = 0;
				cout << "\n\tSorry... The given book author is not found....Try again? Y/N : ";
				cin >> choice;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
		}
	} while (choice == 'y' || choice == 'Y');
	system("pause");
}

// Display List & Update book details
void displayUpdate(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	cout << "\n\n\nBOOKS AVAILABLE IN WISDOM BOOKSHOP" << endl;
	cout << "===== ========= == ====== ========" << endl;
	char sel1, choice;
	int select, bookid;
	do {
		for (int x = 0; x < fileline; x++)
		{
			cout << "\n\n---------------------------------------------------------------" << endl;
			cout << "\tBook ID : " << Booklist[x].bookID << endl;
			cout << "\n\tBook Category : " << Booklist[x].category << endl;
			cout << "\n\tBook Name : " << Booklist[x].name << endl;
			cout << "\n\tBook Descriptionription : " << Booklist[x].description << endl;
			cout << "\n\tBook Publisherlisher : " << Booklist[x].publisher << endl;
			cout << "\n\tBook Author : " << Booklist[x].author << endl;
			cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
			cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
			cout << "---------------------------------------------------------------" << endl;
		}
		bool found = false;
		
		do
		{
			error = 0;
			cout << "\n\tDo you want to update any existing book details? Y/N : ";
			cin >> sel1;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		if (sel1 == 'y' || sel1 == 'Y')
		{
			
			do
			{
				error = 0;
				cout << "\n\tEnter the book ID you want to update : ";
				cin >> bookid;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid Input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			for (int x = 0; x < fileline; x++)
			{
				if (Booklist[x].bookID == bookid)
				{
					Update(Booklist, x, fileline);
					found = true;
				}

			}
			if (!found)
			{
				
				do
				{
					error = 0;
					cout << "\n\tEntered Book ID not found in the list --- \n\n\tWould you like to try again? Y/N : " << endl;
					cin >> choice;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
			}
		}
		else
			break;
	} while (choice == 'y' || choice == 'Y');

	system("pause");
}

// function to update book details to file
void adding(Bookdetails Booklist[1000], int x, int fileline)
{
	ofstream bookfile;
	bookfile.open("list.txt");
	for (int x = 0; x < fileline; x++)
	{
		bookfile << endl << Booklist[x].bookID << endl;
		bookfile << Booklist[x].category << endl;
		bookfile << Booklist[x].name << endl;
		bookfile << Booklist[x].description << endl;
		bookfile << Booklist[x].publisher << endl;
		bookfile << Booklist[x].author << endl;
		bookfile << Booklist[x].price << endl;
		bookfile << Booklist[x].quantity << endl;
	}
}

// Function to Update Existing Book Details
void Update(Bookdetails Booklist[1000], int x, int fileline)
{
	int select;
	int max = INT_MAX;
	int id = Booklist[x].bookID;
	
	do {
		error = 0;
		cout << "\n\tDo you want to update-- \n\n\t1. complete book details-- \n\n\t2. One or few details-- \n\n\t0. Return \n\n\tSelect your option : ";
		cin >> select;
		if (cin.fail())
		{
			cout << "\n\tPlease select a number 1 or 2 or 0 : " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
		while (select >= 3 || select < 0)
		{
			cout << "\n\tPlease select a number 1 or 2 or 0 : " << endl;
			cout << "\n\tDo you want to update-- \n\n\t1. complete book details-- \n\n\t2. One or few details-- \n\n\t0. Return \n\n\tSelect your option : ";
			cin >> select;
		}
	} while (error == 1);

	if (select == 1)
	 {
		cout << "\n\n\t---------------------------------------------------------------" << endl;

		do
		{
			error = 0;
			cout << "\tBook ID : Existing ID is " << "(" << id << ")" << "\n\tEnter the new ID : ";
			cin >> Booklist[x].bookID;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		for (int z = 0; z < fileline; z++)
		{
			while (Booklist[x].bookID != id & Booklist[z].bookID == Booklist[x].bookID)
			{
				for (int a = 0; a < fileline; a++)
				{
					while (Booklist[a].bookID == Booklist[x].bookID & Booklist[x].bookID != id)
					{
						for (int q = 0; q < fileline; q++)
						{
							max = Booklist[q].bookID;
						}
						cout << "\tEntered book ID is existing already!!!! \n\tPlease enter a different ID : ";
						cout << "\n\tBook ID : Existing ID is " << "(" << Booklist[x].bookID << ")" << endl;
						if (id != (max + 1))
						{
							do
							{
								error = 0;
								cout << "\tEnter new ID (Suggested ID is " << id << " or " << max + 1 << ") : ";
								cin >> Booklist[x].bookID;
								if (cin.fail())
								{
									cout << "\n\tPlease enter a valid input : " << endl;
									error = 1;
									cin.clear();
									cin.ignore(80, '\n');
								}
							} while (error == 1);
						}
						else
						{
							do
							{
								error = 0;
								cout << "\tEnter new ID (Suggested ID is " << id << ") : ";
								cin >> Booklist[x].bookID;
								if (cin.fail())
								{
									cout << "\n\tPlease enter a valid input : " << endl;
									error = 1;
									cin.clear();
									cin.ignore(80, '\n');
								}
							} while (error == 1);
						}
					}
				}
			}
		}
		cout << "---------------------------------------------------------------" << endl;
		cout << "\tBook Category : Existing category is " << "(" << Booklist[x].category << ")" << "\n\tEnter the new category Here : ";
		cin.ignore();
		getline(cin, Booklist[x].category);
		cout << "---------------------------------------------------------------" << endl;
		cout << "\tBook Name : Existing book name is " << "(" << Booklist[x].name << ")" << "\n\tEnter the new book Name Here : ";
		getline(cin, Booklist[x].name);
		cout << "---------------------------------------------------------------" << endl;
		cout << "\tBook Description : Existing description is " << "(" << Booklist[x].description << ")" << "\n\tEnter the new description Here : ";
		getline(cin, Booklist[x].description);
		cout << "---------------------------------------------------------------" << endl;
		cout << "\tBook Publisher : Existing publisher is " << "(" << Booklist[x].publisher << ")" << "\n\tEnter the new publisher Here : ";
		getline(cin, Booklist[x].publisher);
		cout << "---------------------------------------------------------------" << endl;
		cout << "\tBook Author : Existing author is " << "(" << Booklist[x].author << ")" << "\n\tEnter the new author Here : ";
		getline(cin, Booklist[x].author);
		cout << "---------------------------------------------------------------" << endl;

		do
		{
			error = 0;
			cout << "\tPrice of the book : Existing price is $" << "(" << Booklist[x].price << ")" << "\n\tEnter the new price here : ";
			cin >> Booklist[x].price;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		cout << "---------------------------------------------------------------" << endl;
		do
		{
			error = 0;
			cout << "\tQuantities in store : Existing quantities are " << "(" << Booklist[x].quantity << ")" << "\n\tEnter the new quantities here : ";
			cin >> Booklist[x].quantity;
			if (cin.fail())
			{
				cout << "\n\tPlease enter a valid input : " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		adding(Booklist, x, fileline);
		cout << "\n\tBook details updated successfully" << endl;
	}
	else if (select == 2)
	{
		int choice;
		do {
			
			cout << "\n\t1. Update book ID - " << endl;
			cout << "\n\t2. Update book category - " << endl;
			cout << "\n\t3. Update book name - " << endl;
			cout << "\n\t4. Update book description - " << endl;
			cout << "\n\t5. Update book publisher - " << endl;
			cout << "\n\t6. Update book auhtor - " << endl;
			cout << "\n\t7. Update book price $ - " << endl;
			cout << "\n\t8. Update book quantity - " << endl;
			cout << "\n\t0. Return - " << endl;
			cout << "\n\n\tInput your choice here : ";
			cin >> choice;
			switch (choice)
			{
			case 1: {
				do {
					error = 0;
					cout << "\tBook ID : Existing ID is " << "(" << id << ")" << "\n\tEnter the new ID : ";
					cin >> Booklist[x].bookID;
					if (cin.fail())
					{
						cout << "\n\tPlease enter a valid input : " << endl;
						error = 1;
						cin.clear();
						cin.ignore(80, '\n');
					}
				} while (error == 1);
				for (int z = 0; z < fileline; z++)
				{
					while (Booklist[x].bookID != id & Booklist[z].bookID == Booklist[x].bookID)
					{
						for (int a = 0; a < fileline; a++)
						{
							while (Booklist[a].bookID == Booklist[x].bookID & Booklist[x].bookID != id)
							{
								for (int q = 0; q < fileline; q++)
								{
									max = Booklist[q].bookID;
								}
								cout << "\tEntered book ID is existing already!!!! \n\tPlease enter a different ID : ";
								cout << "\n\tBook ID : Existing ID is " << "(" << Booklist[x].bookID << ")" << endl;
								if (id != (max + 1))
								{
									do
									{
										error = 0;
										cout << "\tEnter new ID (Suggested ID is " << id << " or " << max + 1 << ") : ";
										cin >> Booklist[x].bookID;
										if (cin.fail())
										{
											cout << "\n\tPlease enter a valid input : " << endl;
											error = 1;
											cin.clear();
											cin.ignore(80, '\n');
										}
									} while (error == 1);
								}
								else
								{
									do
									{
										error = 0;
										cout << "\tEnter new ID (Suggested ID is " << id << ") : ";
										cin >> Booklist[x].bookID;
										if (cin.fail())
										{
											cout << "\n\tPlease enter a valid input : " << endl;
											error = 1;
											cin.clear();
											cin.ignore(80, '\n');
										}
									} while (error == 1);
								}
							}
						}
					}
				}
				cout << "---------------------------------------------------------------" << endl;
				adding(Booklist, x, fileline);
				cout << "\n\tBook ID updated successfully" << endl;
			}break;
			case 2: {cout << "---------------------------------------------------------------" << endl;
				cout << "\tBook Category : Existing category is " << "(" << Booklist[x].category << ")" << "\n\tEnter the new category Here : ";
				cin.ignore();
				getline(cin, Booklist[x].category);
				cout << "---------------------------------------------------------------" << endl;
				adding(Booklist, x, fileline);
				cout << "\n\tBook category updated successfully" << endl;
			}break;
			case 3: {cout << "---------------------------------------------------------------" << endl;
				cout << "\tBook Name : Existing book name is " << "(" << Booklist[x].name << ")" << "\n\tEnter the new book Name Here : ";
				cin.ignore();
				getline(cin, Booklist[x].name);
				cout << "---------------------------------------------------------------" << endl;
				adding(Booklist, x, fileline);
				cout << "\n\tBook name updated successfully" << endl;
			}break;
			case 4: {cout << "---------------------------------------------------------------" << endl;
				cout << "\tBook Description : Existing description is " << "(" << Booklist[x].description << ")" << "\n\tEnter the new description Here : ";
				cin.ignore();
				getline(cin, Booklist[x].description);
				cout << "---------------------------------------------------------------" << endl;
				adding(Booklist, x, fileline);
				cout << "\n\tBook description updated successfully" << endl;
			}break;
			case 5: {cout << "---------------------------------------------------------------" << endl;
				cout << "\tBook Publisher : Existing publisher is " << "(" << Booklist[x].publisher << ")" << "\n\tEnter the new publisher Here : ";
				cin.ignore();
				getline(cin, Booklist[x].publisher);
				cout << "---------------------------------------------------------------" << endl;
				adding(Booklist, x, fileline);
				cout << "\n\tBook publisher updated successfully" << endl;
			}break;
			case 6: {cout << "---------------------------------------------------------------" << endl;
				cout << "\tBook Author : Existing author is " << "(" << Booklist[x].author << ")" << "\n\tEnter the new author Here : ";
				cin.ignore();
				getline(cin, Booklist[x].author);
				cout << "---------------------------------------------------------------" << endl;
				adding(Booklist, x, fileline);
				cout << "\n\tBook author updated successfully" << endl;
			}break;
			case 7: {do
			{
				error = 0;
				cout << "\tPrice of the book : Existing price is $" << "(" << Booklist[x].price << ")" << "\n\tEnter the new price here : ";
				cin.ignore();
				cin >> Booklist[x].price;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			cout << "---------------------------------------------------------------" << endl;
			adding(Booklist, x, fileline);
			cout << "\n\tBook price updated successfully" << endl;
			}break;
			case 8: {do
			{
				error = 0;
				cout << "\tQuantities in store : Existing quantities are " << "(" << Booklist[x].quantity << ")" << "\n\tEnter the new quantities here : ";
				cin.ignore();
				cin >> Booklist[x].quantity;
				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			adding(Booklist, x, fileline);
			cout << "\n\tBook quantities updated successfully" << endl;
			}break;
			case 0: return;
			}
		}while (choice != 0);
	}
system("pause");
}


