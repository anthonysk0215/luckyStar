//
//  stars.cpp
//  Project luckyStar
//
//  Created by Anthony Do on 11/14/24.
//

#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "words.txt";

int runOneRound(const char words[][7], int nWords, int wordnum);

int main()
    {
    char w[8000][7];
    int n = getWords(w, 8000, WORDFILENAME);
        
    if (n < 1) { //invalid amount
        cout << "No words were loaded, so I can't play the game.";
        return -1;
    }
    
    int rounds;
    cout << "How many rounds do you want to play? ";
    cin >> rounds;
    cin.ignore(10000, '\n'); //ignore leftover input

    if (rounds <= 0) {
        cout << "The number of rounds must be positive.";
        return -1;
    }
    
    cout.setf(ios::fixed);
    cout.precision(2);
    double average = 0;
    int min = 0;
    int max = 0;
    for (int i = 0; i < rounds; i++) {
        cout << endl;
        int random = randInt(0, n-1);
        cout << "Round " << i+1 << endl;
        cout << "The secret word is " << strlen(w[random]) << " letters long." << endl;
        
        int x = runOneRound(w, n, random);
        
        if (x == -1) {
            cout << "Error: Invalid arguments passed, program will terminate." << endl;
            return -1;
        }
        
        if(x > 1) {
            cout << "You got it in " << x << " tries." << endl;
        } else {
            cout << "You got it in 1 try." << endl;
        }
        
        if (x > max) { //asigns x to max if greater
            max = x;
        }
        
        if (i == 0) { //sets x to min for the first round
            min = x;
        } else if (x < min) {
            min = x;
        }
        
        average += x; //counts total score
        cout << "Average: " << average/(i + 1) << ", minimum: " << min << ", maximum: " << max << endl;
    }
        
    return 0;
}

int runOneRound(const char words[][7], int nWords, int wordnum) {
    if (nWords < 0 || wordnum >= nWords || wordnum < 0) { //ensures inputs are valid and positive
        return -1;
    }
    
    int count = 0; // number of attempts
    while(true) {
        cout << "Trial word: ";
        char str[100] = {}; //99 char + newline
        cin.getline(str, 100);
        
        if (strlen(str) < 4 || strlen(str) > 6) { //ensures char array is 4 - 6 chars
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue; //loops again from top
        }
        
        bool isValid = true; // Flag to check if all characters are lowercase
        for (int i = 0; i < strlen(str); i++) {
            if (!islower(str[i])) {
                isValid = false; // Set flag to false if any character is not lowercase
                break;
            }
        }

        if (!isValid) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        int x = 0; // variable changes if word is not known so next if statements are not passed
        if (strlen(str) >= 4 && strlen(str) <= 6) { //ensures cout is not repeated
            for (int i = 0; i < nWords; i++) {
                if (words[i][0] == '\0') { // skip uninitialized entries
                        continue;
                    }
                if (strcmp(str, words[i]) == 0) {
                    break;
                } else if (i == nWords - 1 && strcmp(str, words[i]) != 0) {
                    cout << "I don't know that word." << endl;
                    x = 1;
                }
            }
        }
        
        if (strcmp(str, words[wordnum]) == 0) {
            count += 1;
            break;
        } else if (x == 0){ // x == 0 means the word is a known word
            int star = 0;
            int planet = 0;
            
            int test[26] = {0}; //declares int array of 0s
            int target[26] = {0};
            
            for (int j = 0; j < strlen(str); j++) {
                if (j < strlen(words[wordnum]) && str[j] == words[wordnum][j]) {
                    star += 1; //adds to star if they are the same char
                } else {
                    // check if the characters are valid lowercase letters
                   if (str[j] >= 'a' && str[j] <= 'z') {
                       test[str[j] - 'a']++; // update test array
                   }
                   if (j < strlen(words[wordnum]) && words[wordnum][j] >= 'a' && words[wordnum][j] <= 'z') {
                       target[words[wordnum][j] - 'a']++;
                   }
                }
            }
            
            for (int p = 0; p < 26; p++) { //loops through all 26 char of the alphabet
                if (test[p] < target[p]) { //compares the min value in both list as that would be the planet
                    planet += test[p];
                } else {
                    planet += target[p];
                }
            }
            
            cout << "Stars: " << star << ", Planets: " << planet << endl;
            count += 1;
        }
    }
        
    return count;
}
