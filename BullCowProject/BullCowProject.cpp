/*this is amakes use of BullCoe class ,
this acts as the view in mvc pattern, 
and this is responsible for all user interactions console executable,that */

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummery();

FBullCowGame BCGame;//instantiate a new game 

//the entry point of application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0;//exit application
}

void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}
//loop continually untill the user give a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		//get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		//check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowrecase letters\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::ok); //keep looping untill we get no errors
	return Guess;
}

//play a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for number of turn we want asking for guesses
	//is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		std::cout << "\nYour guess was: " << Guess << std::endl;//TODO make loop checking validation

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << " Cows: " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}

	PrintGameSummery();
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same Hidden Word? (y/n) ";
	std::cout << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummery()
{
	if (BCGame.IsGameWon())
	{
		std::cout << " WELL DONE _ YOU WIN THE GAME \n";
	}
	else
	{
		std::cout << "Better Luck Next Time\n";
	}
}