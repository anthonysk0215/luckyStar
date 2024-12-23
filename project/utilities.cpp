//
//  utilities.cpp
//  Project luckyStar
//
//  Created by Anthony Do on 11/14/24.
//

#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <random>
#include <utility>
using namespace std;


int getWords(char words[][MAXWORDLEN+1], int maxWords, const char wordfilename[])
{
    ifstream wordfile(wordfilename);
    if ( ! wordfile)
    {
        cout << "Cannot open " << wordfilename << "!" << endl;
        return -1;
    }
    const int MAXFILELINELEN = 10000;
    char line[MAXFILELINELEN];
    int numWords = 0;
    while (wordfile.getline(line, MAXFILELINELEN))
    {
          // Store only words with of the right number of lower case letters

        int k;
        for (k = 0; islower(line[k]); k++)
            ;

        if (line[k] == '\r')
                line[k] = '\0';

        if (numWords == maxWords)
        {
            cout << "Using only the first " << numWords << " words from "
                 << wordfilename << "." << endl;
            break;
        }

        if (line[k] == '\0'  &&  k >= MINWORDLEN  &&  k <= MAXWORDLEN)
        {
            strcpy(words[numWords], line);
            numWords++;
        }
    }
    return numWords;
}

  // Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}
