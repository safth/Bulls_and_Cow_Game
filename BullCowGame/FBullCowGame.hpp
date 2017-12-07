


#include <stdio.h>
#include <string>

using FString = std::string;
using int32 = int;


struct FBullCowCount // une classe avec toute public par défaut
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    Ok,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); // constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    int32 GetDifficulty(int32) ;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    FBullCowCount SubmitValidGuess(FString);
     
    
private:
    //See constructor for their initialisation
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bIsGameWon;
    int32 Choice;
    
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
};

