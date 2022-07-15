#pragma once

#include "FBullCowGame.h"
#include <map>

#define TMap std::map//to make syntax Unreal friendly

using FString = std::string;
using int32 = int;



FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int FBullCowGame::GetCurrentTry()const{ return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon()const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries()const
{
	TMap<int32, int32> WordLengthToMaxTriies{ {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 19} };
	return WordLengthToMaxTriies[MyHiddenWord.length()] ;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)const
{
	if (!IsIsogram(Guess))//if the Guess is not isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))//if the Guess is not all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())//if the guess length is  not right
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::ok;
	}
}


void FBullCowGame::Reset()
{
	bGameIsWon = false;

	const FString HiddenWord = "ant";//this MUST be an Isogram
	MyHiddenWord = HiddenWord;

	MyCurrentTry = 1;
	return;
}

//recieve a valid guess
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();//assuming same length as guess

	//loop through all the letters in the hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		//compare hiddenword against guess
		for (int32 j = 0; j < WordLength; j++)
		{
			if (MyHiddenWord[i] == Guess[j])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;//incriment bulls
				}
				else
				{
					BullCowCount.Cows++;//incriment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as Isogram
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen;//setup our map

	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true; //add letter to the map
		}
	}
	return true;// for example if the word \0 entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))  //if not a lowercase
		{
			return false;
		}
	}
	return true;
}

