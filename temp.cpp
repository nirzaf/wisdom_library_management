#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>
#include<cstdio>
#include<limits>
#include<iomanip>
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
void searchbycategory(Bookdetails Booklist[fileline], int fileline);
void searchBooks(Bookdetails Booklist[fileline], int fileline);
void searchBookbyName(Bookdetails Booklist[fileline], int fileline);
void searchbyauthor(Bookdetails Booklist[fileline], int fileline);
void searchBookbyPrice(Bookdetails Booklist[fileline], int fileline);

//=============================================================================
// Update Functions Prototype Calling Statements
void Update(Bookdetails Booklist[fileline], int x, int fileline);
void UpdateByName(Bookdetails Booklist[fileline], int fileline);
void UpdateByID(Bookdetails Booklist[fileline], int fileline);
void displayUpdate(Bookdetails Booklist[fileline], int fileline);
void updateByAuthor(Bookdetails Booklist[fileline], int fileline);
void UpdatebyCategory(Bookdetails Booklist[fileline], int fileline);

//=============================================================================
// Delete Functions Prototype Calling Statements
void DeletebybID(Bookdetails Booklist[fileline], int  bookID, int x, int& fileline);
void Deletebycat(Bookdetails Booklist[1000], string name, int x, int& fileline);
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
const std::string currentDateTime() {
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

void fontsize()
{
	int font, x, y;
	
	do
	{
		error = 0;
		cout << "\n\tEnter font size : ";
		cin >> font;
		if (font >= 25)
		{
			cout << "\tPlease enter font size Less than 25... " << endl;
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

void color()
{
	char y;
	do
	{
		error = 0;
		cout << "\n\tDo you want to change the theme? Y/N :";
		cin >> y;
		if (cin.fail())
		{
			cout << "\n\tPlease enter a valid input. " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);

	if (y == 'y' || y == 'Y')
	{
		int col;
		cout << "\n\t1. Black and White theme " << endl;
		cout << "\n\t2. White and Black theme  \n\n\t3. Return" << endl;
		do
		{
			error = 0;
			cout << "\n\tEnter your Selection here: ";
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
			else
				system("cls");
				return;	
	}
	else
		system("cls");
		return;
	
}

// Main function
void main()
{
	cin.clear();
	system("cls");
	//system("color 0F");
	// 5F Pink
	// 4F Bage
	// 3F green
	// 2F light Green
	// 1F Blue
	// F0 White Bgrd with black text
	
	string User, password;
	int choice;
	int font;
	cout << "\n\n************** WELCOME TO WISDOM BOOK SHOP *******************" << endl;
	cout << "\n(This Application Lets you to Display & Search \nAny Details You want about Books Available in Wisdom BookShop)" << endl;
	cout << "********************Please login to Access********************" << endl;
	do {
		cin.clear();
		cout << "\n\nPlease Choose from the Following Login Options\n\n";
		cout << "\t1. Admin Login  \n\t2. Staff Login  \n\t3. Guest Login  \n\t4. Change Font Size \n\t5. Change Theme \n\t6. Exit \n";
		
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
					cout << "\n\tPlease Enter Admin username : ";
					cin >> User;
					password = getpass("Please enter the password: ", true);
					Login(User, password); 
					} break;

		case 2:		{
					cout << "\n\tPlease Enter Staff username : ";
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
		
		case 6: return;
		default:	cout << "\n\n\tInvalid entry!!! Please try again (Enter 1, 2, 3, 4, 5 or 6)" << endl; break;
		}
	} while (choice != 6);
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
			cout << "Successfully Logged into staff Account" << endl;
			loginreport << Users[a] << " Logged in " << currentDateTime();
			staffFunctions(Users[a], loginreport, guestlogin);
			valid = true;
			break;
		}
		if (user == "Guest" & pass1 == "guest2")
		{
			cout << "\n\tSuccessfully Logged into guest Account" << endl;
			guestlogin << user << " Logged in " << currentDateTime();
			staffFunctions(user, loginreport, guestlogin);
			valid = true;
			break;
		}
	}
	if (!valid)
	{
		cout << "\n\tUser Name & Password is invalid try again? Y/N : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
			main();
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
		cout << "Username & Password is invalid try again? Y/N : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
			main();
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
	cout << "\n\t0 : EXIT" << endl;
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
	cout << "\n\t6 : BACK TO MAIN MENU " << endl;
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
	cout << "\n\t6 : BACK TO MAIN MENU " << endl;
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
	cout << "\n\t6 : BACK TO MAIN MENU " << endl;
}

//Admin Menu Contains all the calling functions of Admin Options 
void adminMenu(ofstream& adminloginreport)
{
	// ofstream adminloginreport("adminloginreport.txt", ios::app);
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
				case 6:break ;
				default: cout << "\n\tInvalid selection... try again....";
				}
			} while (searchops != 6);
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
				case 6:break;
				default: cout << "\n\tInvalid selection... Try again....";
					}
				} while (dltops != 6);
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
				case 6:break;
				default: cout << "\n\tInvalid selection... Try again....";
					}
			} while (updateops != 6);
		}
	} while (Sel != 0);
	
}

// Function to call Staff Functions 
void staffFunctions(string name, ofstream& loginreport, ofstream& guestlogin)
{
	int Sel;
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
		cout <<  "\n	0 : EXIT" << endl;
		
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
				return;
				}
				else
				{
					loginreport << " || Logged out - " << currentDateTime() << endl;
					loginreport.close();
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
	ifstream admin, staff, guest;
	admin.open("adminloginreport.txt");
	staff.open("staff login report.txt");
	guest.open("guest login.txt");
	string report;
	int x;
	cout << "\n\n\n\tLogin Report You Can Check Login Information of Each User" << endl;
	cout << "\t===== ====== === === ===== ===== =========== == ==== ====" << endl;
	cout << "\n\n\t1. View Admin Login Report :  ";
	cout << "\n\t2. View Staff Login Report :  ";
	cout << "\n\t3. View Guest Login Report :  ";
	cout << "\n\t4. Erase All Login Reports :  ";
	cout << "\n\t5. Return to Main Menu :  ";
	char choice;
	do {
		bool file = false;
		
		do
		{
			error = 0;
			cout << " \n\n\tSelect an option from the above menu : ";
			cin >> x;
			if (cin.fail())
			{
				cout << "\n\tEnter your choice here : ";
				cin >> choice;
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
			adminloginreport.close();
			admin.close();
			staff.close();
			guest.close();
			remove("adminloginreport.txt");
			remove("staff login report.txt");
			remove("guest login.txt");
			cout << "\n\tErase Successfully" << endl;
			break;
		}
		else if(x != 5)
			cout << "\n\tInvalid Entry try again ";
	} while (x != 5);

	admin.close();
	staff.close();
	guest.close();
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
								cout << "\n\tPlease enter a valid input : " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);
					}
				}
				cout<<"\n----------------------------------------------------------------------------";
				cout << "\n\tBook Category : ";
				cin >> Booklist[x].category;
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
			bookfile >> Booklist[x].category;

			bookfile.ignore();
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
				cout << "\tBook Category : " << Booklist[x].category << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << setprecision(10)<< Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;
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

			}
		}

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
			if (author[0] == Booklist[x].author[0] && author[1] == Booklist[x].author[1] && author[2] == Booklist[x].author[2])
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
}

// Search Books by Name 
void searchBookbyName(Bookdetails Booklist[1000], int fileline)
{
	system("cls");
	string Bname;
	char choice;
	cout << "\n\n\tSEARCH BOOKS BY NAME" << endl;
	cout << "\t====== ====== == ====" << endl;
	do {
		bool found = false;
		cout << "\n\n\tPlease enter the book Name : ";
		cin.ignore();
		getline(cin, Bname);

		Bname = ConvertToLower(Bname);

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].name = ConvertToLower(Booklist[x].name);
			if (Bname[0] == Booklist[x].name[0] && Bname[1] == Booklist[x].name[1] && Bname[2] == Booklist[x].name[2])
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
	string cname;
	string name;
	char choice;

	cout << "\n\n\tSEARCH BOOKS BY CATEGORY" << endl;
	cout << "\t======= ===== == =======" << endl;
	do {
		bool found = false;
		cout << "\n\n\tPlease enter the book Category to Search: ";
		cin.ignore();
		getline(cin, cname);

		cname = ConvertToLower(cname);
		char sel, sel2;

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].category = ConvertToLower(Booklist[x].category);
			if (cname[0] == Booklist[x].category[0] && cname[1] == Booklist[x].category[1] && cname[2] == Booklist[x].category[2])
			{
				cout << "\n\n---------------------------------------------------------------" << endl;
				cout << "\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << setprecision(10) << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------" << endl;
				found = true;
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
		{	error = 0;
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
		cout << "\n\tDo You want to Search Books  \n\n\t\t1. Less than $" << Bprice << "--\n\t\t2. Greater Than $" << Bprice << "--\n\t\t3. Exact to $" << Bprice << "\n\t\t4. Return to Main Menu--";
		
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
		if (select == 1) 
		{
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
		}
		if (select == 2)
		{
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
		}
		if (select == 3)
		{
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
			if (found )
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
		}
		if (select == 4)
			break;
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
			cout << "\tPlease enter the book ID : ";
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
					cout << "\n\tDo you want to delete this book? Y/N : ";
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
	string Bname;
	char choice;
	system("cls");
	cout << "\n\n\tSEARCH BOOKS BY NAME TO DELETE" << endl;
	cout << "\t====== ===== == ==== == ======" << endl;
	do {
		int detect = 0, find = 0;
		cout << "\n\n\tPlease enter the book Name : ";
		cin.ignore();
		getline(cin, Bname);

		Bname = ConvertToLower(Bname);
		char sel, sel2;
		bool found = false;
		bool again = false;
		for (int x = 0; x < fileline; x++)
		{
			found = false;
			again = true;
			Booklist[x].name = ConvertToLower(Booklist[x].name);
			if (Bname[0] == Booklist[x].name[0] && Bname[1] == Booklist[x].name[1] && Bname[2] == Booklist[x].name[2])
			{   cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "\t Book ID : " << Booklist[x].bookID << endl;
				cout << "\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;
				find = 1;
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
	string cname;
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
		getline(cin, cname);

		cname = ConvertToLower(cname);
		char sel, sel1;
		for (int x = 0; x < fileline; x++)
		{
			found = false;
			Booklist[x].category = ConvertToLower(Booklist[x].category);
			if (cname[0] == Booklist[x].category[0] && cname[1] == Booklist[x].category[1] && cname[2] == Booklist[x].category[2])
			{
				cout << "\n\n---------------------------------------------------------------" << endl;
				cout << "\tBook ID : " << Booklist[x].bookID << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------" << endl;
				found = true;
				find = 1;
				count++;
				bookid = Booklist[x].bookID;
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
	string aname;
	char choice;

	system("cls");
	cout << "\n\n\tSEARCH BOOKS BY AUTHOR TO DELETE" << endl;
	cout << "\t====== ===== == ====== == ======" << endl;
	do {
		int detect = 0, find = 0;
		cout << "\n\n\tPlease enter the Name of book Auhtor  : ";
		cin.ignore();
		getline(cin, aname);

		aname = ConvertToLower(aname);
		char sel, sel2;
		bool found = false;
		bool again = false;
		for (int x = 0; x < fileline; x++)
		{
			found = false;
			Booklist[x].author = ConvertToLower(Booklist[x].author);
			if (aname[0] == Booklist[x].author[0] && aname[1] == Booklist[x].author[1] && aname[2] == Booklist[x].author[2])
			{
				cout << "\n\n---------------------------------------------------------------" << endl;
				cout << "\tBook ID : " << Booklist[x].bookID << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------" << endl;
				found = true;
				find = 1;
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
				cout << "\tEnter the book ID you want to delete : ";
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
					DeletebybID(Booklist, Booklist[x].bookID, x, fileline);
					cout << "\tSelected item deleted successfully..........." << endl;
					fileline++;
					found = true;
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

// function to delete by Category
void Deletebycat(Bookdetails Booklist[1000], string name, int x, int& fileline)
{
	int y = 0;
	ofstream ofile;
	ofile.open("list.txt");

	while (ofile) {
		for (int z = 0; z < fileline; z++)
		{
			if (Booklist[z].category != Booklist[x].category)
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
			if (Booklist[x].name == Booklist[1000].name)
				y = 1;
		}
		ofile.clear();
		ofile.close();
		fileline--;
	}
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
			if (category[0] == Booklist[x].category[0] && category[1] == Booklist[x].category[1] && category[2] == Booklist[x].category[2])
			{
				cout << "\n\n---------------------------------------------------------------" << endl;
				cout << "\tBook ID : " << Booklist[x].bookID << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------" << endl;
				found = true;
				find = 1;
				count++;
				bookid = Booklist[x].bookID;
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
						cout << "\tBook list updated successfully............" << endl;
						
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
						cout << "\tBook list updated successfully............" << endl;
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
			if (name[0] == Booklist[x].name[0] && name[1] == Booklist[x].name[1] && name[2] == Booklist[x].name[2])
			{
				cout << "\n\n---------------------------------------------------------------" << endl;
				cout << "\tBook ID : " << Booklist[x].bookID << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------" << endl;
				found = true;
				find = 1;
				count++;
				bookid = Booklist[x].bookID;
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
						cout << "\tBook list updated successfully............" << endl;
						
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
				cout << "\n\tDo you want to update any of book details from the results? Y/N : ";
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
						cout << "\n\tBook list updated successfully............" << endl;
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
			cout << "Please enter the book ID : ";
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
				cout << "\tBook Name : " << Booklist[x].name << endl;
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
						cout << "\n\nDo you want to update this book details? Y/N : ";
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
						cout << "\n\t...Successfully updated " << endl;
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
				cout << "Sorry... The given book ID is not found....\n\t Would you like to try again? Y/N : " << endl;
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
			if (author[0] == Booklist[x].author[0] && author[1] == Booklist[x].author[1] && author[2] == Booklist[x].author[2])
			{
				cout << "\n\n---------------------------------------------------------------" << endl;
				cout << "\tBook ID : " << Booklist[x].bookID << endl;
				cout << "\n\tBook Name : " << Booklist[x].name << endl;
				cout << "\n\tBook Author : " << Booklist[x].author << endl;
				cout << "\n\tPrice of the Book : $" << Booklist[x].price << endl;
				cout << "\n\tQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------" << endl;
				found = true;
				find = 1;
				count++;
				bookid = Booklist[x].bookID;
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
						cout << "\n\t.....Booklist updated successfully............" << endl;
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
						cout << "\n\t.....Book list updated successfully............" << endl;
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
					cout << "\tBook list updated successfully............" << endl;
					found = true;
				}

			}
			if (!found)
			{
				
				do
				{
					error = 0;
					cout << "\tEntered Book ID not found in the list --- \n\tWould you like to try again? Y/N : " << endl;
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

// Function to Update Existing Book Details
void Update(Bookdetails Booklist[1000], int x, int fileline)
{
	int max = INT_MAX;
	int id = Booklist[x].bookID;
	cout << "\n\n\t---------------------------------------------------------------"<<endl;
	
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
					cout << "\tEntered Book ID Existing Already!!!! \n\tPlease enter a different ID : ";
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
	cout << "---------------------------------------------------------------"<<endl;
	cout << "\tBook Category : Existing Category is " <<"("  << Booklist[x].category <<")"  << "\n\tEnter New Category Here : ";
	cin >> Booklist[x].category;
	cout << "---------------------------------------------------------------"<<endl;
	cout << "\tBook Name : Existing Book is " <<"("<< Booklist[x].name<<")"  << "\n\tEnter New Book Name Here : " ;
	cin.ignore();
	getline(cin, Booklist[x].name);
	cout << "---------------------------------------------------------------"<<endl;
	cout << "\tBook Descriptionription : Existing Description is "<<"("<< Booklist[x].description <<")" << "\n\tEnter New Description Here : ";
	getline(cin, Booklist[x].description);
	cout << "---------------------------------------------------------------"<<endl;
	cout << "\tBook Publisherlisher : Existing Publisher is "<<"("<< Booklist[x].publisher <<")"  << "\n\tEnter New Publisher Here : ";
	getline(cin, Booklist[x].publisher);
	cout << "---------------------------------------------------------------"<<endl;
	cout << "\tBook Author : Existing Author is "<<"("<<  Booklist[x].author <<")" << "\n\tEnter New Author Here : ";
	getline(cin, Booklist[x].author);
	cout << "---------------------------------------------------------------"<<endl;
	
	do
	{
		error = 0;
		cout << "\tPrice of the Book : Existing Price is $" << "(" << Booklist[x].price << ")" << "\n\tEnter New Price Here : ";
		cin >> Booklist[x].price;
		if (cin.fail())
		{
			cout << "\n\tPlease enter a valid input : " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	cout << "---------------------------------------------------------------"<<endl;
	do
	{
		error = 0;
		cout << "\tQuantity in Store : Existing Quantities Available is " << "(" << Booklist[x].quantity << ")" << "\n\tEnter New Quantities Here : ";
		cin >> Booklist[x].quantity;
		if (cin.fail())
		{
			cout << "\n\tPlease enter a valid input : " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	

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
system("pause");
}


