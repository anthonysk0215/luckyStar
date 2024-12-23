//
//  utilities.h
//  Project luckyStar
//
//  Created by Anthony Do on 11/14/24.
//

const int MINWORDLEN = 4;
const int MAXWORDLEN = 6;

int getWords(char words[][MAXWORDLEN+1], int maxWords, const char wordfilename[]);
int randInt(int min, int max);
