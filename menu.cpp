#include<iostream>
#include<string>
#include<Windows.h>
#pragma comment(lib, "user32.lib")


using namespace std;

void main()
{
	
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
					cout << "You Have Selected Number 1 Option" <<endl;
					Sleep(1000);
					
				}break;
				case 1:
				{
					cout << "You Have Selected Number 2 Option" << endl;
					Sleep(1000);
					
				}break;
				case 2:
				{
					cout << "You Have Selected Number 3 Option" << endl;
					Sleep(1000);
				
				}	break;
				case 3:
				{
					cout << "You Have Selected Number 4 Option" << endl;
					Sleep(1000);
					
				}break;
				case 4:
				{
					cout << "You Have Selected Number 5 Option" << endl;
					Sleep(1000);
					
				}break;
				case 5:
				{
					cout << "You Have Selected Number 6 Option" << endl;
					Sleep(1000);
					
				}break;
				case 6:
				{
					cout << "You Have Selected Number 7 Option" << endl;
					Sleep(1000);
					
				}break;
				case 7:
				{
					cout << "You Have Selected Number 8 Option" << endl;
					Sleep(1000);
					
				}break;
				case 8:
				{
					cout << "You Have Selected Number 9 Option" << endl;
					Sleep(1000);
					
				}break;
				case 9:
				{
					cout << "You Have Selected Number 10 Option" << endl;
					Sleep(1000);
					
				}break;
				case 10:
				{
					cout << "You Have Selected Number 11 Option" << endl;
					Sleep(1000);
					
				}break;
				case 11:
				{
					cout << "You Have Selected Number 12 Option" << endl;
					Sleep(1000);
					
				}break;
				case 12:
				{
					cout << "You Have Selected Number 13 Option" << endl;
					Sleep(1000);
					
				}break;
				case 13:return;
				}
			}
		}Sleep(200);
	}
		
}
