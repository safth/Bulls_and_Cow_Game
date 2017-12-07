//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Simon Boivin on 2017-11-10.
//  Copyright © 2017 Simon Boivin. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map


using int32 = int;


FBullCowGame::FBullCowGame(){ Reset(); } // Default constructor


// des "getters" ils font juste retourner des Valeurs Privates.
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{ return bIsGameWon ;}
int32 FBullCowGame::GetDifficulty(int32 Val) {
    Choice=Val;
    return Choice;
}

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32,int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,16}, {7,20}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
    TMap<int32,FString> Hidden_Word = {{3,"bar"},{4,"aids"},{5,"plane"},{6,"agoras"},{7,"isogram"}};// changer par une autre function
    MyHiddenWord = Hidden_Word[Choice];
    MyCurrentTry=1;
    bIsGameWon = false;

    return ;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
   if (!IsIsogram(Guess)) // if the guess is not a isogram
   {
       return EGuessStatus::Not_Isogram;
   }
   else if (!IsLowerCase(Guess)) // if the guess is not lowercase
   {
       return EGuessStatus::Not_Lowercase;
   }
   else if (Guess.length() != GetHiddenWordLength()  ) //if the length is wrong
   {
       return EGuessStatus::Wrong_Length;
   }
   else
   {
       return EGuessStatus::Ok;
   }
    
}

//count Bulls and Count, incerse nb of guess assuming valid guess.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    //increment the turn number
    MyCurrentTry++;
    //setup a return variable
    FBullCowCount BullCowCount;
    
    int32 WordLength = MyHiddenWord.length();
    //loop through all the letters in the guess
    for (int32 i=0; i < WordLength; i++){
        for (int32 j = 0; j < WordLength;  j++){
            if ( Guess[i] == MyHiddenWord[j] ) { //if they match then
                if(i==j) {
                    BullCowCount.Bulls++; // increment Bull if they are in the same position
                }
                else {
                    BullCowCount.Cows++;  // increment cows if not
                }
            }
        }
    }
    if(BullCowCount.Bulls == WordLength)
    {
        bIsGameWon = true;
    }else
    {
        bIsGameWon = false;
    }
        
        
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    if(Word.length() <=1 ) {return true;}
    TMap<char,bool> LetterSeen; // on fait une map des lettre et de bool.
    for(auto Letter:Word) // on loop sur toutes les lettres.
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]){
            return false; // its not a isogram
        } else {
            LetterSeen[Letter] = true; // on met un 1 ou la lettre se trouve, si elle est la 2 fois on va avoir true au if avant et ce ne sera pas un istogram!!
        }
        
    }
    
    return true; // c'est un isogram
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
    for (auto Letter : Word)
    {
        if(!islower(Letter))
        {
            return false;
        }
    }
    
    return true;
}



