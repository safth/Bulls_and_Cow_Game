/*
    This is the console executable that make use of the BullCowGame class
    it is respondible for all user interaction.
    For game logic: view FBullCowGame
*/

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"


using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void GetValidDifficulty();

FBullCowGame BCGame; //instantiate a new game

//##############################################
//############ ##################################
//##############################################
 // Constant
bool bPlayAgain = false;

int main()
{
    do {
        PrintIntro();
        PlayGame();
        PrintGameSummary();
        bPlayAgain = AskToPlayAgain();
        
    }
    while(bPlayAgain);
    return 0;
        
}






// introduce the game
void PrintIntro() {
    std::cout << "Welcome to Bulls and Cows a fun word game!!\n" ;
    std::cout <<"         }___{                 (__)   \n";
    std::cout <<"  /------(o o)          `\------(oo)   \n";
    std::cout <<"   ||    |\\^/            ||    (__)   \n";
    std::cout <<"*  ||---||               ||w--||   \n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letters isogram i'm thinking of? \n";
    return;
}

// Loop le jeux
void PlayGame()
{
    //Get valid difficulties
    GetValidDifficulty();
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess();
        

        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << "  Cows = " << BullCowCount.Cows << "\n\n";
    }
}


// Get a guess from the user
FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status; // par default
    do {
        //Get the Guess
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " <<BCGame.GetMaxTries() <<". Enter your guess: ";
        //print the guess
        getline(std::cin,Guess);
        //Check guess Validity
        Status = BCGame.CheckGuessValidity(Guess);
        
        switch(Status){
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() <<" Letters word\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters\n" ;
            break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Just Lowercases!!\n";
                break;
            default:
                //assume the guess is valid
                break;
        }
    } while (Status != EGuessStatus::Ok); // Keep looping until we get Valid input
    return Guess;
 }
// ask if they want to play again
bool AskToPlayAgain()
{
    std::cout << "do you want to play again? (y/n)";
    FText Response = "";
    getline(std::cin,Response);
    return Response[0] == 'y' || Response[0] == 'Y';
    //TODO: test test
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon()) // if its true par default... c'est un Bool
    {
        std::cout << "Well Done you Won!! \n\n";
    }
    else
    {
        std::cout << "you loose... SUCKER!!'' \n";

    }
}

void GetValidDifficulty(){
      int32 Choice=0;
    while(Choice < 3 || Choice > 7){
            std::cout << "\nChoose your word length (3 4 5 6 7)\n";
            std::cin >> Choice;
        
        if (std::cin.fail()) { // si il met une lettre!!
            std::cin.clear();
            std::cin.ignore(256,'\n');
            std::cout << "\nPut an integer";
        }
    }
    BCGame.GetDifficulty(Choice);
}
    
