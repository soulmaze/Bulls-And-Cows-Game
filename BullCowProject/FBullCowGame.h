/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once

#include <string>

//to make syntax Unreal friendly
using int32 = int;
using FString = std::string;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid_Status,
	ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:

	FBullCowGame();//constructor
	int32 GetMaxTries()const;
	int32 GetCurrentTry()const;
	bool IsGameWon()const;
	EGuessStatus CheckGuessValidity(FString)const;
	int32 GetHiddenWordLength()const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
private:
	//initialisation in constructor
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString)const;
	bool IsLowercase(FString)const;
};