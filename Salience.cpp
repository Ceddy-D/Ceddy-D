// I am pp. This is Cedric. It is pronounced "see dick".

/*
Salience: WorldBuilding Generator
indev 0.1.3.2.2
=================================
Roadmap:
Function for more character details.
Update UI.
	Menu
	Title screen
	Colors
(Optional) Another name generation method using more sophisticated methods
(Optional) Switching between generation methods for the same name.

Create debug window (either below, or seperate window.)

generate other things such as:
	planets
	solar systems
	continents/ islands
	countries
	materials/ elements (down to the quark)
	weapons
	castles
	and more 
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


class NameMinMax			//As its name suggests, defines the minimum and maximum letters of g_NameFinal.
{
	public:
	int NameMin;
	int NameMax;
};


//global variables
string g_NameFinal;
string g_FullNameFinal [100];	//This is completely overkill and probably hella memory inefficient, but I don't want to eff with vectors right now.
char g_LetterList [] = {	//Note: line split for readability.
'a','e','i','o','u','b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};	// 0/4 = vowels, 5/25 consonants
bool g_Debug = 0;	//0 = debug off, 1 = debug on.
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

//Color function (Yes this isn't doing anything right now, I know. I'll add calls to it in the future.)
void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Adds the letter determined in generateName() to g_NameFinal.
void letterAdd(int CurrentLetterInt)
{
	char CurrentLetter = g_LetterList [CurrentLetterInt];		

	g_NameFinal = g_NameFinal + CurrentLetter;
}

void generateName(int NAME_MIN, int NAME_MAX, int DoAbbreviate /*0 = Not Abr, 1 = Abr, 2 = rand*/, 		//line split for redability...
int StartVowel /*0= vowl, 1 = cons, 2 = rand*/, int NameGeneratorMethod /*0 = VCons, 1 = VCChunk*/ /*, int DoDiaretics /*Includes */)
{
	g_NameFinal = "";	//rests name each time function is called.
	
	//Variables
	int NameLengthFinal, CurrentLetterInt, ChunkSize;
	bool IsVowel, IsAbbreviated = false;
	
	
	//Determines whether to start name with consonant or vowel, or random.
	if (StartVowel < 2)
		IsVowel = StartVowel;
	else 
		IsVowel = rand() % 2 - 1;
	
	//Determines whether to abbreviate or not, primaraly for middle names. (Redundant as of now, but in place in case needed)
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
		
	//Generates name...
		
	if (NameGeneratorMethod == 0)	//Generates name VCons method.
	{
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
			
			letterAdd(CurrentLetterInt);
		}
	}
	
	if (NameGeneratorMethod == 1)	//Generates name VCChunk method. (It's a huge mess that I have to clean up.)
	{
		for (int i = 0; i < NameLengthFinal;)
		{
			ChunkSize = rand() % (2+IsVowel) + 1;	//(2+IsVowel) ensures that vowels can be in chunks of 3, but not consonants.
			
			if (IsAbbreviated) ChunkSize = 1;	//Makes it so abbreviations are only 1 letter.
			
			while (ChunkSize > 0)
			{
				if (IsVowel == true)
					CurrentLetterInt = rand() % 5;
				else CurrentLetterInt = rand() % 21 + 5;
				ChunkSize--;
				
				letterAdd(CurrentLetterInt);
				i++;
			}
			if (IsVowel) IsVowel = false;
			else IsVowel = true;
		}
	}
	
	//Adds period after abbreviation. Might make optional in future. Probably not.
	if (IsAbbreviated == true)
		g_NameFinal = g_NameFinal + ".";
		
	//Capitalizes first letter of name.
	g_NameFinal[0] = toupper(g_NameFinal[0]);
}

void generateFullName(bool DoMiddleName, bool DoSurname, int DoMiddleNameAbbreviated, //Line split for readability, same as generateName().
int DoSurnameAbbreviated, int FullNamePosition0to99, int NameGeneratorMethod)
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
	
	
	generateName(g_CharacterMinMax.NameMin, g_CharacterMinMax.NameMax, 0, 2, NameGeneratorMethod);	//Generates first name.
	g_FullNameFinal [FullNamePosition0to99] = g_FullNameFinal [FullNamePosition0to99] + g_NameFinal;	/*Adds first name to g_FullNameFinal.
																										Note: Repeats in this function so
																										that generateName() can be used for
																										things other than character names.
																										May change later, but unlikely.*/
	if (DoMiddleName)	//Generates middle name.
	{
		g_FullNameFinal [FullNamePosition0to99]  = g_FullNameFinal [FullNamePosition0to99]  + " ";
		generateName(g_CharacterMinMax.NameMin, g_CharacterMinMax.NameMax, DoMiddleNameAbbreviated, 2, NameGeneratorMethod);
		
		g_FullNameFinal [FullNamePosition0to99] = g_FullNameFinal [FullNamePosition0to99] + g_NameFinal;	//Adds middle name to g_FullNameFinal.
	}
	
	if (DoSurname)	//Generates surname.
	{
		if (DoMiddleNameAbbreviated == 0 or DoSurnameAbbreviated == 0)										//Adds space if either middle or surname aren't
			g_FullNameFinal [FullNamePosition0to99]  = g_FullNameFinal [FullNamePosition0to99] + " ";		//abbreviated eg. "Rigo M.O." not "Rigo M. O.".
		
		generateName(g_CharacterMinMax.NameMin, g_CharacterMinMax.NameMax, DoSurnameAbbreviated, 2, NameGeneratorMethod);
		
		g_FullNameFinal [FullNamePosition0to99] = g_FullNameFinal [FullNamePosition0to99] + g_NameFinal;	//Adds surname to g_FullNameFinal.
	}
}


int main()
{
	//Variables
	int FullNamePosition0to99 = 0;
	int NameGeneratorMethod = 1;		//0 = VCons, 1 = VCChunk
	
	srand (time(NULL)); //Initialize random seed.
	
	cout << "Salience 0.1.3.2.2" << endl;
	cout << "2022 Ceddy D" << endl << endl;
	cout << "Ultimate worldbuilding engine." << endl;
	cout << "Press any key to continue...";
	getch();
	
	
	g_CharacterMinMax.NameMin = 4;	//Add inputs at some point.
	g_CharacterMinMax.NameMax = 7;
	
	while(1)	//TERRIBLE syntax, change to variable ASAP.
	{
		cls();
		
		if (g_Debug) cout << g_CharacterMinMax.NameMin << " " << g_CharacterMinMax.NameMax << endl << endl;	//debug
		
		generateFullName(1,1,2,2,FullNamePosition0to99, NameGeneratorMethod);
		cout << "Character Name: " << g_FullNameFinal [FullNamePosition0to99] << endl;
		cout << "Press any key to continue...";
		getch();
	}
	
	return (0);
}


/*
Version History:
(Versions use the syntax "FullRelease.MajorUpdate.MinorUpdate.BugFix.CodeCleanup")
================
0.1.1.0.0)
Character name generator prototype.
Generates 7-10 letter long name of alternating vowels and consonants. Hereby considered "VCon" method.
0.1.2.0.0)
Add capital letter at start of name. 
Code cleanup. 
Debug variable added (set to false)
Loops VCon name every time a key is pressed.
Creates first, middle, and surname.
middle name and surname can be abbreviated.
0.1.3.0.0)
Added generation method where it generates random 1-3 character long chunk of alternating vowels and consonants. Hereby considered "VCChunk" method.
0.1.3.1.0)
Fixed VCChunk to actually work.
Updated roadmap.
Preparing to add diacritical characters in name generation. (eg. é).
0.1.3.1.1)
Does the following to make names more readable:
	Changes minimum name length from 7 to 4.
	Changes maximum name length from 10 to 7.
0.1.3.1.2
	Cleaned up code a bit.
	Edited comments.
*/
