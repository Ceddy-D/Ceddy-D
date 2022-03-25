/*
Salience: WorldBuilding Generator
indev 0.2
=================================
Roadmap:
Better name generation method or methods.
Loop name generator
Update UI
Create debug window (either below, or seperate window.)
*/

#include <iostream>		//cout
#include <windows.h>	//SetConsoleTextAttribute, SetConsoleCursorPosition, GetStdHandle, 
#include <conio.h>		//getch
#include <string>		//string
#include <stdio.h>      //NULL
#include <stdlib.h>     //srand, rand
#include <time.h>       //time
#include <cctype>		//toupper

using namespace std;

//global variables
string g_NameFinal;
char g_LetterList [] = {'a','e','i','o','u','b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};	// 0/4 = vowels, 5/25 consonants
bool g_Debug = 0;	//0 = debug off, 1 = debug on.
string g_FullNameFinal [100];	//This is completely overkill and probably hella memory inefficient, but I don't want to eff with vectors right now.


class NameMinMax
{
	public:
	int NameMin;
	int NameMax;
};
NameMinMax g_CharacterMinMax;


//Windows.h function to replace screen with nulls. (aka clear screen) (1.1.2)
//Add to header at some point...
void cls()
{
  DWORD n;
  DWORD size;
  COORD coord = {0};
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
  GetConsoleScreenBufferInfo ( h, &csbi );
  size = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
  SetConsoleCursorPosition ( h, coord );
}

// color function
void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void generateName(int NAME_MIN, int NAME_MAX, int DoAbbreviate /*0 = Not Abr, 1 = Abr, 2 = rand*/, int StartVowel /*0= vowl, 1 = cons, 2 = rand*/)
{
	g_NameFinal = "";	//rests name each time function is called.
	
	//Variables.
	int NameLengthFinal, CurrentLetterInt;
	bool IsVowel, IsAbbreviated = false;
	char CurrentLetter;
	
	
	//Determines whether to start name with consonant or vowel, or random.
	if (StartVowel < 2)
		IsVowel = StartVowel;
	else 
		IsVowel = rand() % 2 - 1;
	
	//Determines weather to abbreviate or not, primaraly for middle names. (Redundant as of now, but in place in case needed)
	if (DoAbbreviate == 2)
		DoAbbreviate = rand() % 2;
	if (DoAbbreviate == 1)
		IsAbbreviated = true;
	else
		IsAbbreviated = false;
	
	//Sets name length.
	if (IsAbbreviated == true)
		NameLengthFinal = 1;	
	else
		NameLengthFinal = rand() % (NAME_MAX - NAME_MIN) + NAME_MIN;
		
	if (g_Debug) cout << NameLengthFinal << endl;		//Probably wanna remove at some point.
	
	//Generates name (VCon method which kinda sucks, will add variable to switch between this method and better methods)
	for (int i = 0; i< NameLengthFinal ; i++)
	{
		if (IsVowel == true)
		{
			CurrentLetterInt = rand() % 5;
			IsVowel = false;
		}
		else
		{
			CurrentLetterInt = rand() % 21 + 5;
			IsVowel = true;
		}
		CurrentLetter = g_LetterList [CurrentLetterInt];
		
		g_NameFinal = g_NameFinal + CurrentLetter;
	}
	
	//Adds period after abbreviation. Might make optional in future. Probably not.
	if (IsAbbreviated == true)
		g_NameFinal = g_NameFinal + ".";
		
	//Capitalizes first letter of name.
	g_NameFinal[0] = toupper(g_NameFinal[0]);
}

void generateFullName(bool DoMiddleName, bool DoSurname, int DoMiddleNameAbbreviated, int DoSurnameAbbreviated, int FullNamePosition0to99)
{	
	g_FullNameFinal [FullNamePosition0to99] = "";	//Initializes name.
	
	if (DoMiddleNameAbbreviated == 2)			//Determines whether to abbreviate or not.
		DoMiddleNameAbbreviated = rand() % 2;
	if (DoMiddleNameAbbreviated == 1)
		DoMiddleNameAbbreviated = 1;
	else
		DoMiddleNameAbbreviated = 0;
	
	if (DoSurnameAbbreviated == 2)				//Same as previous block. Could be optimized but I don't really care.
		DoSurnameAbbreviated = rand() % 2;
	if (DoSurnameAbbreviated == 1)
		DoSurnameAbbreviated = 1;
	else
		DoSurnameAbbreviated = 0;
	
	
	generateName(g_CharacterMinMax.NameMin, g_CharacterMinMax.NameMax, 0, 2);	//Generates first name.
	g_FullNameFinal [FullNamePosition0to99] = g_FullNameFinal [FullNamePosition0to99] + g_NameFinal;	/*Adds first name to g_FullNameFinal.
																										Note: Repeats in this function so
																										that generateName() can be used for
																										things other than character names.
																										May change later, but unlikely.*/
	if (DoMiddleName)	//Generates middle name.
	{
		g_FullNameFinal [FullNamePosition0to99]  = g_FullNameFinal [FullNamePosition0to99]  + " ";
		generateName(g_CharacterMinMax.NameMin, g_CharacterMinMax.NameMax, DoMiddleNameAbbreviated, 2);
		
		g_FullNameFinal [FullNamePosition0to99] = g_FullNameFinal [FullNamePosition0to99] + g_NameFinal;	//Adds middle name to g_FullNameFinal.
	}
	
	if (DoSurname)	//Generates surname.
	{
		if (DoMiddleNameAbbreviated == 0 or DoSurnameAbbreviated == 0)										//Adds space if either middle or surname aren't
			g_FullNameFinal [FullNamePosition0to99]  = g_FullNameFinal [FullNamePosition0to99] + " ";		//abbreviated eg. "Rigo M.O." not "Rigo M. O.".
		
		generateName(g_CharacterMinMax.NameMin, g_CharacterMinMax.NameMax, DoSurnameAbbreviated, 2);
		
		g_FullNameFinal [FullNamePosition0to99] = g_FullNameFinal [FullNamePosition0to99] + g_NameFinal;	//Adds surname to g_FullNameFinal.
	}
}


int main()
{
	//Variables
	int FullNamePosition0to99 = 0;
	
	
	srand (time(NULL)); //Initialize random seed.
	
	cout << "Salience 0.1.2" << endl;
	cout << "2022 Ceddy D" << endl << endl;
	cout << "Ultimate worldbuilding engine." << endl;
	cout << "Press any key to continue...";
	getch();
	
	
	g_CharacterMinMax.NameMin = 7;	//Add inputs at some point.
	g_CharacterMinMax.NameMax = 10;
	
	while(1)	//TERRIBLE syntax, change to variable ASAP.
	{
		cls();
		
		if (g_Debug) cout << g_CharacterMinMax.NameMin << " " << g_CharacterMinMax.NameMax << endl << endl;	//debug
		
		generateFullName(1,1,2,2,FullNamePosition0to99);
		cout << "Character Name: " << g_FullNameFinal [FullNamePosition0to99] << endl;
		cout << "Press any key to continue...";
		getch();
	}
	
	return (0);
}


/*
Version History)
================
0.1.1)
Character name generator prototype.
Generates 7-10 letter long name of alternating vowels and consonants. Hereby considered "VCon" method.
0.1.2)
Add capital letter at start of name. 
Code cleanup. 
Debug variable added (set to false)
Loops VCon name every time a key is pressed.
Creates first, middle, and surname.
middle name and surname can be abbreviated.
*/
