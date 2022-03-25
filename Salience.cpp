/*
Roadmap:
1.1) Character generator.
1.2) Work on country generation.
*/

#include <iostream>		//cout
#include <windows.h>	//Color (Not defined in header)
#include <conio.h>		//getch
#include <string>		//string
#include <stdio.h>      //NULL
#include <stdlib.h>     //srand, rand
#include <time.h>       //time

using namespace std;

string NameFinal = "";


// color function
void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void generateName(int NAME_MIN, int NAME_MAX, int DoAbbreviate /*0 = Not Abr, 1 = Abr, 2 = rand*/, int StartVowel /*0= vowl, 1 = cons, 2 = rand*/)
{
	//Variables.
	char LetterList [] = {'a','e','i','o','u','b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};	// 0/4 = vowels, 5/25 consonants
	int NameLengthFinal, CurrentLetterInt;
	bool IsVowel, IsAbbreviated = false;
	char CurrentLetter;
	
	srand (time(NULL)); //Initialize random seed.

	
	//Determines weather to start name with consonant or vowel, or random. I am still carrying my V-Card.
	if (StartVowel < 2)
		IsVowel = StartVowel;
	else 
		IsVowel = rand() % 2 - 1;
	
	//Determines weather to abbreviate or not, primaraly for middle names. I have blue balls too
	if (DoAbbreviate == 2)
		DoAbbreviate = rand() % 1;
	if (DoAbbreviate == 1)
		IsAbbreviated = true;
	else
		IsAbbreviated = false;
	
	//Sets name length.
	if (IsAbbreviated == true)
		NameLengthFinal = 1;	
	else
		NameLengthFinal = rand() % (NAME_MAX - NAME_MIN) + NAME_MIN;
	cout << NameLengthFinal << "   ";
	//Generates name (Pretty bad method, will add variable to switch between this method and better methods)
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
		CurrentLetter = LetterList [CurrentLetterInt];
		
		NameFinal = NameFinal + CurrentLetter;
	}
	
	//Adds period after abbreviation. Might make optional in future. Probably not.
	if (IsAbbreviated == true)
		NameFinal = NameFinal + ".";
	
	cout << NameFinal;
}


int main()
{
	//Variables
	
	
	srand (time(NULL)); //Initialize random seed.
	
	cout << "Salience 0.1.1" << endl;
	cout << "2022 Ceddy D" << endl << endl;
	cout << "Ultimate worldbuilding engine." << endl;
	cout << "Press any key to continue.";
	getch();
	system("CLS");
	
	generateName(7,10,0,2);
	cout << NameFinal;
	
	return (0);
}
0.1.1)
Character name generator prototype.
Generates 7-10 letter long name of alternating vowels and consonants. Hereby considered "VCon" method.
