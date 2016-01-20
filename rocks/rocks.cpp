//
//  rocks.cpp
//  rocks
//
//  Created by Chuyue Zhang on 11/16/15.
//  Copyright © 2015 Camille Zhang. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstring>
#include <iomanip>
#include "utilities.h"
using namespace std;

//check if the position index of the shorter string already exists in the integer array
bool alreadyExists(int a[], int n, int x)
{
    for ( int m = 0 ; m < n ; m ++ )
    {
        if (a[m] == x)
            return true;
    }
    return false;
}


int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
    //initialize rocks and pebbles to zero before each round of game
    int rocks = 0;
    int pebbles = 0;
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
        return -1;
    
    //while loop that controls user's each probe word, increments number of tries whenever number of rocks and pebbles get output or when user gets the secret word
    int r = 0;
    while (rocks!=strlen(words[wordnum]))
    {
        rocks = 0;
        pebbles = 0;

        cout << "Probe word: ";
        char probeWord[10000];
        cin.getline(probeWord, 10000);

        if (strlen(probeWord) < 4 || strlen(probeWord) > 6 )
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." <<endl;
            continue;
        }

        bool allLower = true;
        for (int i = 0 ; i < strlen(probeWord); i ++)
        {
            if (!islower(probeWord[i]))
            {
                allLower = false;
                cout << "Your probe word must be a word of 4 to 6 lower case letters." <<endl;
                break;
            }
        }
        if (!allLower)
            continue;

        bool foundWord = false;
        for (int k = 0; k < nWords; k ++ )
        {
            if (strcmp(words[k], probeWord) == 0)
            {
                foundWord = true;
     
                char longOne[7];
                char shortOne[7];
                if (strlen(probeWord)>= strlen(words[wordnum]))
                {
                    strcpy(longOne, probeWord);
                    strcpy( shortOne, words[wordnum]);
                }
                else
                {
                    strcpy ( longOne, words[wordnum]);
                    strcpy ( shortOne, probeWord);
                    
                }
                int markedPos[6] = {-1,-1,-1,-1,-1,-1};
                int p = 0;
       
                for (int i=0; i < strlen(longOne); i ++ )
                {
                    for (int j = 0; j < strlen(shortOne); j ++ )
                    {
                        if (longOne[i] == shortOne [j])
                        {
                            if ( shortOne [j] == longOne [j] )
                            {
                                if (!alreadyExists(markedPos, 6, j))
                                {
                                    markedPos[p] = j;
                                    p++;
                                    rocks ++ ;
                                    break;
                                }
                            }
                            else if (!alreadyExists(markedPos, 6, j))
                            {
                                markedPos[p] = j;
                                p++;
                                pebbles ++ ;
                                break;
                            }
                        }
                    }
                }
                if (rocks == strlen(words[wordnum]))
                {
                    r++;
                    break;
                }
                cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl;
                r++;
                break;
            }
        }
        if (!foundWord)
        {
            cout << "I don't know that word." << endl;
        }
        continue;
    }
    return r;
}


int main()
{

    //declare array and fill in using loadWords function
    const int MAXWORDS = 10000;
    char wordList[MAXWORDS][MAXWORDLEN+1];
    int nWords = loadWords(wordList, MAXWORDS);
    if (nWords < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }
    
    //ask how many rounds user wants to play
    cout << "How many rounds do you want to play? ";
    int rounds;
    cin >> rounds;
    cin.ignore(10000, '\n');
    cout << endl;
    
    //create integer array to store number of tries for each round
    const int MAX_NUMBER_OF_TRIES = 10000;
    int tries[MAX_NUMBER_OF_TRIES];
    int total = 0;
    int p = 0;
    
    //for loop that controls outputs of number of rounds user wants to play
    for (int t = 1; t <= rounds; t ++ )
    {
        cout << "Round " << t << endl;
        int index = randInt(0, nWords-1); //secure position index of the random word
        cout << "The secret word is "<< strlen(wordList[index])<< " letters long." << endl;
        
        //output user's performance
        int r = manageOneRound(wordList, nWords, index);
        if ( r == 1)
        {
            cout << "You got it in 1 try." <<endl;
            tries[p] = r;
            p++;
            total += r;
        }
        else
        {
            cout << "You got it in " << r << " tries." << endl;
            tries[p] = r;
            p ++;
            total += r;
        }
        double dtotal = total;
        double average = dtotal/p;

        int q = 0;
        int minimum = tries[q];
        int s = 0;
        int maximum = tries[s];
        for ( q = 0 ; q < p; q ++)
        {
            if ( tries[q] < minimum)
                minimum = tries[q];
            else if ( tries [q] > maximum)
                maximum = tries [q];
        }
        cout << "Average: " << fixed << std::setprecision(2) << average << ", minimum: " << minimum << ", maximum: " << maximum << endl;
        cout << endl;
    }
}


