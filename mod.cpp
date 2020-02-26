#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>
#pragma comment(lib, "user32.lib")



using namespace std;

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
void Update(Bookdetails Booklist[1000], int x, int fileline);
void Delete(Bookdetails Booklist[1000], string name, int x, int& fileline);
void DeletebybID(Bookdetails Booklist[1000], int  bookID, int x, int& fileline);
void Deletebycat(Bookdetails Booklist[1000], string name, int x, int fileline);
void searchbycategory(Bookdetails Booklist[1000], int fileline);
void searchBName(Bookdetails Booklist[1000], int fileline);
void UpdateByName(Bookdetails Booklist[1000], int fileline);
void searchCategory(Bookdetails Booklist[1000], int fileline);
void UpdateByID(Bookdetails Booklist[1000], int fileline);
void printBooks(Bookdetails Booklist[1000], int fileline);
void searchBooks(Bookdetails Booklist[1000], int fileline);
void searchCategory(Bookdetails Booklist[1000], int fileline);
void searchBName(Bookdetails Booklist[1000], int fileline);
void displaydelete(Bookdetails Booklist[1000], int& fileline);
void searchBookbyName(Bookdetails Booklist[1000], int fileline);
void staffFunctions(string name);
int addBook(Bookdetails Booklist[1000], int fileline);
int addBooksfromFile(Bookdetails Booklist[1000]);
string ConvertToLower(string str);
void staff(string& user, string& pass1);
void adminMenu();
void Login(string& admin, string& password);
void AdminOptions();
void HelpFunction();
void printBookOffers(Bookdetails Booklist[1000], int fileline);
void searchbyauthor(Bookdetails Booklist[1000], int fileline);

// main function
void main()
{
	
	string User, password;
	char choice;
	cout << "************** WELCOME TO WISDOM BOOK SHOP *******************" << endl;
	cout << "**** This Application Lets you to Display & Search \nAny Details You want about Books Available in Wisdom BookShop****" << endl;
	cout << "*********Please login for More Functions to Access************" << endl;
	cout << "\n\n\nDo You Like to Login as Admin Y/N \n(if you select No it will Automatically direct you to Staff Login or Guest Login) :";
	cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		cout << "Please Enter Admin username : ";
		cin >> User;
		cout << "Please Enter your password : ";
		cin >> password;
		Login(User, password);
	}

	else
	{
		cout << "Please Enter Staffuser name : \nor\n### If your a Customer Type ""guest"" in both field ### \n(**Make sure to type in simple letters**) : ";
		cin >> User;
		cout << "Please Enter yourpass word : ";
		cin >> password;
		staff(User, password);
	}
}

// Login Function for Staffs 
void staff(string& user, string& pass1)
{
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
			staffFunctions(Users[a]);
			valid = true;
			break;
		}
		if (user == "guest" & pass1 == "guest")
		{
			cout << "Successfully Logged into guest Account" << endl;
			staffFunctions(user);
			valid = true;
			break;
		}
	}
	if (!valid)
	{
		cout << "User Name & Password is Invalid Try Again Y/N : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
			main();
	}
}

// Login Function for Admin
void Login(string& admin, string& password)
{
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
			cout << "Successfully Logged into Admin Account" << endl;
			adminMenu();
			valid = true;
			break;
		}
	}
	if (!valid)
	{
		cout << "User Name & Password is Invalid Try Again Y/N : ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
			main();
	}
}

// Functions to List all admin functions available 
void AdminOptions()
{
	
	/*
	cout << "\n\n	WELCOME TO WISDOM'S ADMINISTRATOR MENU" << endl;
	cout << "	======= == ======== ============= ====" << endl;
	cout << "\n	01 : ADD NEW BOOKS" << endl;
	cout << "\n	02 : DISPLAY ALL BOOKS" << endl;
	cout << "\n	03 : SEARCH BOOKS BY ID NUMBER" << endl;
	cout << "\n	04 : SEARCH BOOKS BY CATEGORY" << endl;
	cout << "\n	05 : SEARCH BY BOOK NAME" << endl;
	cout << "\n	06 : SEARCH BY BOOKAUTHOR " << endl;
	cout << "\n	07 : DELETE & UPDATE BY DISPLAY LIST" << endl;
	cout << "\n	08 : SEARCH & DELETE BY BOOK NAME" << endl;
	cout << "\n	09 : SEARCH & DELETE BY BOOK CATEGORY" << endl;
	cout << "\n	10 : SEARCH & UPDATE BY BOOK NAME " << endl;
	cout << "\n	11 : SEARCH & UPDATE BY BOOK ID " << endl;
	cout << "\n	12 : VIEW SPECIAL OFFERS " << endl;
	cout << "\n	13 : HELP " << endl;
	cout << "\n	00 : EXIT" << endl;
	*/
}

//Admin Menu Contains all the calling functions of Admin Options 
void adminMenu()
{
	Bookdetails Booklist[1000];
	int fileline = addBooksfromFile(Booklist);
	system("pause");
	system("cls");
	string Menu[14] = { "01 : ADD NEW BOOKS","02 : DISPLAY ALL BOOKS" , "03 : SEARCH BOOKS BY ID NUMBER", "04 : SEARCH BOOKS BY CATEGORY","05 : SEARCH BY BOOK NAME","06 : SEARCH BY BOOKAUTHOR","07 : DELETE & UPDATE BY DISPLAY LIST","08 : SEARCH & DELETE BY BOOK NAME","09 : SEARCH & DELETE BY BOOK CATEGORY","10 : SEARCH & UPDATE BY BOOK NAME","11 : SEARCH & UPDATE BY BOOK ID","12 : VIEW SPECIAL OFFERS","13 : HELP","14 : EXIT" };
	int pointer = 0;

	
		while (true)
		{
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << "\n\n	WELCOME TO WISDOM'S ADMINISTRATOR MENU\n\n" << endl;
			for (int i = 0; i < 14; i++)
			{
				if (i == pointer)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << Menu[i] << endl;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << Menu[i] << endl;
				}
			}
			while (true)
			{
				if (GetAsyncKeyState(VK_UP) != 0)
				{
					pointer--;
					if (pointer == -1)
					{
						pointer = 13;
					}
					break;
				}
				else if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					pointer++;
					if (pointer == 15)
					{
						pointer = 0;
					}
					break;
				}
				else if (GetAsyncKeyState(VK_RETURN) != 0)
				{
					switch (pointer)
					{
					case 0:
					{
						fileline = addBook(Booklist, fileline);
						Sleep(1000);
					}break;
					case 1:
					{
						printBooks(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 2:
					{
						searchBooks(Booklist, fileline);
						Sleep(1000);
					}break;
					case 3:
					{
						searchbycategory(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 4:
					{
						searchBookbyName(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 5:
					{
						searchbyauthor(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 6:
					{
						displaydelete(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 7:
					{
						searchBName(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 8:
					{
						searchCategory(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 9:
					{
						UpdateByName(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 10:
					{
						UpdateByID(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 11:
					{
						printBookOffers(Booklist, fileline);
						Sleep(1000);
						
					}break;
					case 12:
					{
						HelpFunction();
						Sleep(1000);
						
					}break;
					case 13:return;
					}
				}
			}Sleep(200);
			
		}
	

}

// Function to call Staff Functions 
void staffFunctions(string name)
{
	int Sel;
	Bookdetails Booklist[1000];
	int fileline = addBooksfromFile(Booklist);
	
	do {
		system("pause");
		system("cls");
		cout <<  "	\n\nWELCOME TO WISDOM'S USER " << name << endl;
		cout <<  "	======= == ======== ====" << endl;
		cout <<  "\n	01 : DISPLAY ALL BOOKS" << endl;
		cout <<  "\n	02 : SEARCH BOOKS BY ID NUMBER" << endl;
		cout <<  "\n	03 : SEARCH BOOKS BY CATEGORY" << endl;
		cout <<  "\n	04 : SEARCH BY BOOK NAME" << endl;
		cout <<  "\n	05 : SEARCH BY BOOK AUTHOR " << endl;
		cout <<  "\n	06 : VIEW SPECIAL OFFERS " << endl;
		cout <<  "\n	07 : HELP " << endl;
		cout <<  "\n	00 : EXIT" << endl;
		cout <<  "\n\nPlease enter your selection : " << endl;
		cin >> Sel;

		switch (Sel)
		{
		case 1: printBooks(Booklist, fileline); break;
		case 2: searchBooks(Booklist, fileline); break;
		case 3: searchbycategory(Booklist, fileline); break;
		case 4: searchBookbyName(Booklist, fileline); break;
		case 5: searchbyauthor(Booklist, fileline); break;
		case 6: printBookOffers(Booklist, fileline); break;
		case 7: HelpFunction(); break;
		case 0: return;
			break;
		default: cout << setw(10) << "Invalid selection... Try again...." << endl;
		}
	} while (Sel != 0);

}


// Function to Add Books from the User Input
int addBook(Bookdetails Booklist[1000], int fileline)
{
	void addAddnewBookstoFile(Bookdetails Addnew);

	int No, x;
	system("cls");
	cout << setw(10) << "\n\n\nADD NEW BOOK TO WISDOM'S DATABASE " << endl;
	cout << setw(10) << "=== === ==== == ======== ========" << endl;

	cout << setw(10) << "How many books you want to add : ";
	cin >> No;
	// Get inputs from the user
	cout << "\n\nPlease enter following details to add a new book to the system" << endl;

	if (No<1000)
	{
		for (x = fileline; x<fileline + No; x++)
		{

			cout << "\nBook ID : ";
			cin >> Booklist[x].bookID;
			for (int a = 0; a < fileline; a++)
			{
				if (Booklist[a].bookID == Booklist[x].bookID)
				{
					cout << "Entered Book ID Existing Already Please enter something else : ";
					cin >> Booklist[x].bookID;
				}
			}
			cout << setw(10) << "Book Category : ";
			cin >> Booklist[x].category;
			cout << setw(10) << "Book Name : ";
			cin.ignore();
			getline(cin, Booklist[x].name);
			cout << setw(10) << "Book Description : ";
			getline(cin, Booklist[x].description);
			cout << setw(10) << "Book Publisher : ";
			getline(cin, Booklist[x].publisher);
			cout << setw(10) << "Book Author : ";
			getline(cin, Booklist[x].author);
			cout << setw(10) << "Price of the Book : ";
			cin >> Booklist[x].price;
			cout << setw(10) << "Quantity in Store : ";
			cin >> Booklist[x].quantity;

			addAddnewBookstoFile(Booklist[x]);
		}
	}
	else
		cout << "No enough space to store ..." << endl;
	return x;
}

// Help Function 
void HelpFunction()
{
	cout << "# All the Functions Comes in the Numbered List are Able to select by the Particular Number in the List " << endl;
	cout << "\n# If there any selection Has to be Made You can Choose your choice by 'Y' for Yes and 'N' for No \nit is not case sensitive you can enter eighther Capital or Simple Doesn't Matter" << endl;
	cout << "\n# Search Function is Highly Effective in this Program, You don't have to remember Complete book Name or Category to Search" << endl;
	cout << " Just Enter first three letter of your Keywords to search is enough You will get the Accurate result" << endl;
	cout << "\n# You Can Update or Delete any file Using Search function. Select the Proper Option to Complete Your Task" << endl;
	cout << "\n# If you Find an Error with this No.(1001) it means somehow Main Database File Deleted Please contact Your MIS team to Fix the Issue" << endl;
	cout << "\n# If You Find any Book starts with ""St.""(this is not case sensitive) It Means This book is under Special Offers\nTo Move the Special Offer to Normal List Remove this ""Sp."" from the Book Descriptionription (Applicable only for Admin) " << endl;
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
	cin.clear();
	int x = 0;
	ifstream bookfile;
	bookfile.open("list.txt");
	char select;
	system("cls");
	if (bookfile) {
		cout << "\n\n\n==== ==== ===== === ================ " << endl;
		cout << "BOOK LIST FOUND AND LOADED.......... " << endl;
		cout << "==== ==== ===== === ================ " << endl;
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
		cout << "Sorry Database not Found, Error Occured (1001)" << endl;
		cout << "Do You Want to Continue and Check in the Help section to find the Problem Cause or Exit Y/N : ";
		cin >> select;
		if (select == 'n' || select == 'N')
			return 0;
	}
	return --x;
}

// Function to Display books in the screen
void printBooks(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	system("cls");
	cout << "\n\n\nBOOKS IN STORE" << endl;
	cout << "===== == =====" << endl;

	for (int x = 0; x<fileline; x++)
	{   cout << "\n\n---------------------------------------------------------------"<<endl;
		cout << "Book ID : " << Booklist[x].bookID << endl;
		cout << "\nBook Category : " << Booklist[x].category << endl;
		cout << "\nBook Name : " << Booklist[x].name << endl;
		cout << "\nBook Descriptionription : " << Booklist[x].description << endl;
		cout << "\nBook Publisherlisher : " << Booklist[x].publisher << endl;
		cout << "\nBook Author : " << Booklist[x].author << endl;
		cout << "\nPrice of the Book : " << Booklist[x].price << endl;
		cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
		cout << "---------------------------------------------------------------"<<endl;
	}
	system("pause");
}

// Search Books by Book ID
void searchBooks(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	char choice;
	do {
		int ID;
		bool found = false;
		system("cls");
		cout << "\n\n\nSEARCH BOOK USING ID" << endl;
		cout << "===== ==== ===== ==" << endl;
		cout << "Please enter the book ID : ";
		cin >> ID;

		for (int x = 0; x < fileline; x++)
		{
			if (ID == Booklist[x].bookID)
			{   cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "Book Category : " << Booklist[x].category << endl;
				cout << "\nBook Name : " << Booklist[x].name << endl;
				cout << "\nBook Author : " << Booklist[x].author << endl;
				cout << "\nPrice of the Book : " << Booklist[x].price << endl;
				cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;
				break;
			}
		}

		if (!found)
		{
			cout << "Sorry... The given book Id is not found....\n would you Like to Try again ? Y/N :: ";
			cin >> choice;

		}
	} while (choice == 'y' || choice == 'Y');

}

// Function to Search & Update by Category
void searchCategory(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	string category;
	bool found = false;
	char choice;
	//system("pause");
	do {
		system("cls");
		cout << "\n\n\nSEARCH BOOKS IN A GIVEN CATEGORY" << endl;
		cout << "====== ===== == = ===== =======" << endl;
		cout << "Please enter the book Category : ";
		cin >> category;
		char sel, sel2;
		category = ConvertToLower(category);

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].category = ConvertToLower(Booklist[x].category);
			if (category[0] == Booklist[x].category[0] && category[1] == Booklist[x].category[1] && category[2] == Booklist[x].category[2])
			{   cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "Book Name : " << Booklist[x].name << endl;
				cout << "\nBook Author : " << Booklist[x].author << endl;
				cout << "\nPrice of the Book : " << Booklist[x].price << endl;
				cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;
				if (found = true)
				{
					cout << "\n\nDo You want to Update this Book Details Y/N : ";
					cin >> sel;
					if (sel == 'y' || sel == 'Y')
					{
						Update(Booklist, x, fileline);
						cout << "Updating ....... Updated Successfully - " << endl;
					}

				}
			}
		}

		if (!found)
		{
			cout << "Sorry... The given book Category is not found...." << endl;
			cin >> choice;
		}
	} while (choice == 'y' || choice == 'Y');
}

// Function to Delete books by Searching by Name
void searchBName(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	string Bname;
	string name;
	bool found = false;
	char choice;

	//system("pause");
	do {
		system("cls");
		cout << "\n\n\nSEARCH BOOKS BY NAME TO DELETE" << endl;
		cout << "====== ===== == ==== == ======" << endl;
		cout << "Please enter the book Name : ";
		cin.ignore();
		getline(cin, Bname);

		Bname = ConvertToLower(Bname);
		char sel, sel2;
		// cout << Bname << endl ;

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].name = ConvertToLower(Booklist[x].name);
			// cout << Booklist[x].name << endl;
			if (Bname[0] == Booklist[x].name[0] && Bname[1] == Booklist[x].name[1] && Bname[2] == Booklist[x].name[2])
			{   cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "Book Name : " << Booklist[x].name << endl;
				cout << "\nBook Author : " << Booklist[x].author << endl;
				cout << "\nPrice of the Book : " << Booklist[x].price << endl;
				cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;
				if (found = true)
				{
					cout << "\n Do You Want to delete this Book Details Y/N : ";
					cin >> sel2;
					if (sel2 == 'y' || sel2 == 'Y')
					{
						Delete(Booklist, Booklist[x].name, x, fileline);
						cout << "Deleting in process .........  Deleted Succesfully" << endl;
					}
				}
			}
		}

		if (!found)
		{
			cout << "Sorry... The given book Name is not found....\nWould You like to try again Y/N :" << endl;
			cin >> choice;
		}
	} while (choice == 'y' || choice == 'Y');

}

// Search Books by Name 
void searchBookbyName(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	string Bname;
	string name;
	bool found = false;
	char choice;

	//system("pause");
	do {
		system("cls");
		cout << "\n\n\nSEARCH BOOKS BY NAME TO DELETE" << endl;
		cout << "====== ====== == ==== == ======" << endl;
		cout << "Please enter the book Name : ";
		cin.ignore();
		getline(cin, Bname);

		Bname = ConvertToLower(Bname);
		char sel, sel2;
		// cout << Bname << endl ;

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].name = ConvertToLower(Booklist[x].name);
			// cout << Booklist[x].name << endl;
			if (Bname[0] == Booklist[x].name[0] && Bname[1] == Booklist[x].name[1] && Bname[2] == Booklist[x].name[2])
			{cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "Book Name : " << Booklist[x].name << endl;
				cout << "\nBook Author : " << Booklist[x].author << endl;
				cout << "\nPrice of the Book : " << Booklist[x].price << endl;
				cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;

			}
		}

		if (!found)
		{
			cout << "Sorry... The given book Name is not found....\nWould You like to try again Y/N :" << endl;
			cin >> choice;
		}
	} while (choice == 'y' || choice == 'Y');

}
// Function to Search by book name and update the bookdetails

void UpdateByName(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	string Bname;
	string name;
	bool found = false;
	char choice;

	//system("pause");
	do {
		system("cls");
		cout << "\n\n\nSEARCH BOOKS BY NAME TO UPDATE" << endl;
		cout << "====== ===== == ==== == ======" << endl;
		cout << "Please enter the book Name : ";
		cin.ignore();
		getline(cin, Bname);

		Bname = ConvertToLower(Bname);
		char sel;
		// cout << Bname << endl ;

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].name = ConvertToLower(Booklist[x].name);
			// cout << Booklist[x].name << endl;
			if (Bname[0] == Booklist[x].name[0] && Bname[1] == Booklist[x].name[1] && Bname[2] == Booklist[x].name[2])
			{
				cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "Book Name : " << Booklist[x].name << endl;
				cout << "\nBook Author : " << Booklist[x].author << endl;
				cout << "\nPrice of the Book : " << Booklist[x].price << endl;
				cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
				found = true;
				if (found = true)
				{
					cout << "\n\nDo You want to Update this Book Details Y/N : ";
					cin >> sel;
					if (sel == 'y' || sel == 'Y')
					{
						Update(Booklist, x, fileline);
						cout << "Updating .............   Successfully Updated " << endl;
					}
				}
			}
		}

		if (!found)
		{
			cout << "Sorry... The given book Name is not found...." << endl;
			cin >> choice;
		}
	} while (choice == 'y' || choice == 'Y');

}

// Function to Search and Update by Book ID
void UpdateByID(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	int BookID;
	string name;
	bool found = false;
	char choice;

	//system("pause");
	do {
		system("cls");
		cout << "\n\n\nSEARCH BOOKS BY ID TO UPDATE" << endl;
		cout << "===== ==== ===== ==" << endl;
		cout << "Please enter the book ID : ";
		cin >> BookID;


		char sel;
		// cout << Bname << endl ;

		for (int x = 0; x < fileline; x++)
		{

			if (BookID == Booklist[x].bookID)
			{   cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "Book Name : " << Booklist[x].name << endl;
				cout << "\nBook Author : " << Booklist[x].author << endl;
				cout << "\nPrice of the Book : " << Booklist[x].price << endl;
				cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;
				if (found = true)
				{
					cout << "\n\nDo You want to Update this Book Details Y/N : ";
					cin >> sel;
					if (sel == 'y' || sel == 'Y')
					{
						Update(Booklist, x, fileline);
						cout << "Updating .............   Successfully Updated " << endl;
					}
				}
			}
		}

		if (!found)
		{
			cout << "Sorry... The given book ID is not found....\n Would You like to try Again Y/N : " << endl;
			cin >> choice;
		}
	} while (choice == 'y' || choice == 'Y');

}

// Function to Search by Category
void searchbycategory(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	string cname;
	string name;
	char choice;
	bool found = false;
	do {
		//system("pause");
		system("cls");
		cout << "\n\n\nSEARCH BOOKS BY CATEGORY" << endl;
		cout << "====== ===== == =======" << endl;
		cout << "Please enter the book Category to Search: ";
		cin.ignore();
		getline(cin, cname);

		cname = ConvertToLower(cname);
		char sel, sel2;
		// cout << Bname << endl ;

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].category = ConvertToLower(Booklist[x].category);
			// cout << Booklist[x].name << endl;
			if (cname[0] == Booklist[x].category[0] && cname[1] == Booklist[x].category[1] && cname[2] == Booklist[x].category[2])
			{   cout << "\n\n---------------------------------------------------------------"<<endl;
				cout << "Book Name : " << Booklist[x].name << endl;
				cout << "\nBook Author : " << Booklist[x].author << endl;
				cout << "\nPrice of the Book : " << Booklist[x].price << endl;
				cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------"<<endl;
				found = true;

			}
		}

		if (!found)
		{
			cout << "Sorry... The given book Category is not found....\n Would You like to try again Y/N : " << endl;
			cin >> choice;
		}
	} while (choice == 'y' || choice == 'Y');

}

// Function to Search Book by Author Name 
void searchbyauthor(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	string author;
	char choice;
	bool found = false;
	do {
		//system("pause");
		system("cls");
		cout << "\n\n\nSEARCH BOOKS BY AUTHOR" << endl;
		cout << "====== ===== == ======" << endl;
		cout << "Please enter the book Author to Search: ";
		cin.ignore();
		getline(cin, author);

		author = ConvertToLower(author);
		char sel, sel2;
		// cout << Bname << endl ;

		for (int x = 0; x < fileline; x++)
		{
			Booklist[x].author = ConvertToLower(Booklist[x].author);
			// cout << Booklist[x].name << endl;
			if (author[0] == Booklist[x].author[0] && author[1] == Booklist[x].author[1] && author[2] == Booklist[x].author[2])
			{
				cout << "\n\n---------------------------------------------------------------" << endl;
				cout << "Book ID : " << Booklist[x].bookID << endl;
				cout << "\nBook Name : " << Booklist[x].name << endl;
				cout << "\nBook Author : " << Booklist[x].author << endl;
				cout << "\nPrice of the Book : " << Booklist[x].price << endl;
				cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
				cout << "---------------------------------------------------------------" << endl;
				found = true;
			}
		}

		if (!found)
		{
			cout << "Sorry... The given book Author is not found....\n Would You like to try again Y/N : " << endl;
			cin >> choice;
		}
	} while (choice == 'y' || choice == 'Y');
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

// Function to Delete or Update by Diplay all booklist by selecting Book ID
void displaydelete(Bookdetails Booklist[1000], int& fileline)
{
	cin.clear();
	system("cls");
	cout << "\n\n\nBOOKS AVAILABLE IN WISDOM BOOKSHOP" << endl;
	cout << "===== ========= == ====== ========" << endl;
	char sel1, choice;
	int select, bookid;
	do {
		for (int x = 0; x < fileline; x++)
		{   cout << "\n\n---------------------------------------------------------------"<<endl;
			cout << "Book ID : " << Booklist[x].bookID << endl;
			cout << "\nBook Category : " << Booklist[x].category << endl;
			cout << "\nBook Name : " << Booklist[x].name << endl;
			cout << "\nBook Descriptionription : " << Booklist[x].description << endl;
			cout << "\nBook Publisherlisher : " << Booklist[x].publisher << endl;
			cout << "\nBook Author : " << Booklist[x].author << endl;
			cout << "\nPrice of the Book : " << Booklist[x].price << endl;
			cout << "\nQuantity in Store : " << Booklist[x].quantity << endl;
			cout << "---------------------------------------------------------------"<<endl;

		}
		bool found = false;
		cout << "\nDo You Want delete or Update any Existing Bookdetails Y/N : ";
		cin >> sel1;
		if (sel1 == 'y' || sel1 == 'Y') {
			cout << " 01) Delete -- : \n 02) Update -- : \n 03) Return to Main Menu -- :";
			cin >> select;
			if (select == 1)
			{
				cout << "Enter the book Id you want to delete : ";
				cin >> bookid;
				for (int x = 0; x < fileline; x++)
				{
					if (bookid == Booklist[x].bookID) {
						DeletebybID(Booklist, Booklist[x].bookID, x, fileline);
						cout << "Deleting .......... Selected item Deleted Successfully" << endl;
						found = true;
					}

				}
				if (!found)
				{
					cout << "Entered BookID not found in the list --- \nWould You like to Again Y/N : " << endl;
					cin >> choice;
				}
			}
			else if (select == 2)
			{
				cout << "Enter the book Id you want to Update : ";
				cin >> bookid;
				for (int x = 0; x < fileline; x++)
				{
					if (bookid == Booklist[x].bookID) {
						Update(Booklist, Booklist[x].bookID, fileline);
						cout << "Update .......... Selected item Updated Successfully" << endl;
						found = true;
					}

				}
				if (!found)
				{
					cout << "Entered BookID not found in the list --- \nWould You like to Again Y/N : " << endl;
					cin >> choice;
				}
			}
			else
				adminMenu();
		}
	} while (choice == 'y' || choice == 'Y');

	system("pause");
}

// Function to Update Existing Book Details
void Update(Bookdetails Booklist[1000], int x, int fileline)
{
	cin.clear();
	cout << "\n\n---------------------------------------------------------------"<<endl;
	cout << "\nBook ID : Existing ID is " <<"(" <<Booklist[x].bookID <<")" << " Enter New ID : " ;
	cin >> Booklist[x].bookID;
	cout << "---------------------------------------------------------------"<<endl;
	cout << "Book Category : Existing Category is " <<"("  << Booklist[x].category <<")"  << " Enter New Category Here : ";
	cin >> Booklist[x].category;
	cout << "---------------------------------------------------------------"<<endl;
	cout << "Book Name : Existing Book is " <<"("<< Booklist[x].name<<")"  << " Enter New Book Name Here : " ;
	cin.ignore();
	getline(cin, Booklist[x].name);
	cout << "---------------------------------------------------------------"<<endl;
	cout << "Book Descriptionription : Existing Description is "<<"("<< Booklist[x].description <<")" << " Enter New Description Here : ";
	getline(cin, Booklist[x].description);
	cout << "---------------------------------------------------------------"<<endl;
	cout << "Book Publisherlisher : Existing Publisher is "<<"("<< Booklist[x].publisher <<")"  << " Enter New Publisher Here : ";
	getline(cin, Booklist[x].publisher);
	cout << "---------------------------------------------------------------"<<endl;
	cout << "Book Author : Existing Author is "<<"("<<  Booklist[x].author <<")" << " Enter New Author Here : ";
	getline(cin, Booklist[x].author);
	cout << "---------------------------------------------------------------"<<endl;
	cout << "Price of the Book : Existing Price is $" <<"("<< Booklist[x].price <<")"  << " Enter New Price Here : " ;
	cin >> Booklist[x].price;
	cout << "---------------------------------------------------------------"<<endl;
	cout << "Quantity in Store : Existing Quantities Available is "<<"("<< Booklist[x].quantity <<")"  << " Enter New Quantities Here : " ;
	cin >> Booklist[x].quantity;

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
		cout << "Updating .............. Updated Successfully "<< endl;
	}
}

// Delete Function to delete bookdetails from the file
void Delete(Bookdetails Booklist[1000], string name, int x, int& fileline)
{
	cin.clear();
	int y = 0;
	ofstream ofile;
	ofile.open("list.txt");

	while (ofile) {
		for (int z = 0; z < fileline; z++)
		{
			if (Booklist[z].name != Booklist[x].name)
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
		addBooksfromFile(Booklist);
		fileline--;
	}
}

// Delete function to delete by Book ID
void DeletebybID(Bookdetails Booklist[1000], int  bookID, int x, int& fileline)
{
	cin.clear();
	int y = 0;
	ofstream ofile;
	ofile.open("list.txt");

	while (ofile) {
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
			if (Booklist[x].name == Booklist[1000].name)
				y = 1;
		}
		ofile.clear();
		//bookfile._Seekbeg(0, ios::beg);
		ofile.close();
			addBooksfromFile(Booklist);
			fileline--;
	}
}

// function to delete by Category
void Deletebycat(Bookdetails Booklist[1000], string name, int x, int fileline)
{
	cin.clear();
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
	}
}

// Adding Books to Special Offers file 
void addAddnewBookstoOffers(Bookdetails offers)
{
	ofstream bookfile;
	bookfile.open("list.txt", ios::app);
	bookfile << endl << offers.bookID << endl;
	bookfile << offers.category << endl;
	bookfile << offers.name << endl;
	bookfile << offers.description << endl;
	bookfile << offers.publisher << endl;
	bookfile << offers.author << endl;
	bookfile << offers.price << endl;
	bookfile << offers.quantity << endl;
	bookfile.close();
}


// Function to Display Special Offers 
void printBookOffers(Bookdetails Booklist[1000], int fileline)
{
	cin.clear();
	system("cls");
	cout << "\n\n\nSPECIAL OFFERS " << endl;
	cout << "===== == =====" << endl;

	for (int x = 0; x<fileline; x++)
	{
		while (Booklist[x].description[0] == 'S' || Booklist[x].description[0] == 's' && Booklist[x].description[1] == 'P' || Booklist[x].description[1] == 'p' && Booklist[x].description[2] == '.')
		{
			cout << "\n\nBook ID : " << Booklist[x].bookID << endl;
			cout << "Book Category : " << Booklist[x].category << endl;
			cout << "Book Name : " << Booklist[x].name << endl;
			cout << "Book Descriptionription : " << Booklist[x].description << endl;
			cout << "Book Publisherlisher : " << Booklist[x].publisher << endl;
			cout << "Book Author : " << Booklist[x].author << endl;
			cout << "Price of the Book : " << Booklist[x].price << endl;
			cout << "Quantity in Store : " << Booklist[x].quantity << endl;
			x++;
		}
	}
	system("pause");
}

