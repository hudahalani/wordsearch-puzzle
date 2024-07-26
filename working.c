#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int SOUTH_EAST = 0;
const int SOUTH = 1;
const int SOUTH_WEST = 2;
const int WEST = 3;
const int NORTH_WEST = 4;
const int NORTH = 5;
const int NORTH_EAST = 6;
const int EAST = 7;

void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);
bool check1D(const int Size, char puzzle[][Size], const int wordSize, char* word, int rowLoc, int colLoc, int dir);
char* getDirection (int dir);

void search(const int Size,
            char puzzle[][Size],
            const int wordSize,
            char* word);

bool inBounds(int row, int col, const int Size);

int main(void) {
    const int Size = 20;
    char puzzle[Size][Size];
    readWordPuzzle(Size, puzzle);
    int wordSize = 0;
    char* word = readWord(&wordSize);
    printWordPuzzle(Size, puzzle);
    printf("The word you are looking for is\n");
    printWord(word, wordSize);
    printf("\n");
    printf("Do you want to search? (Y or N)\n");
    char isSearch;
    scanf(" %c", &isSearch);
    if (isSearch == 'Y' || isSearch == 'y') {
        search(Size, puzzle, wordSize, word);
    }
    free(word);
    return 0;
}

void search(const int Size,
            char puzzle[][Size],
            const int wordSize,
            char* word) {
    char firstCharOfWord = word[0];
    bool wordAlreadyFound;
    int rowLocationWhereWordFound;
    int colLocationWhereWordFound;
    int directionWhereWordFound;
    for (int row = 0; row < Size; row++) {   // go through all raws
        for (int col = 0; col < Size; col++) {  // go through all columns
            char currentLetter = puzzle[row][col];
            if (currentLetter == firstCharOfWord) {
                for (int direction = 0; direction < 8; direction++) {   // go through all direction for current row
                                                                        // and current column since first char matched
                    if (check1D(Size, puzzle, wordSize, word, row, col, direction)) {
                        wordAlreadyFound = true;
                        rowLocationWhereWordFound = row;
                        colLocationWhereWordFound = col;
                        directionWhereWordFound = direction;
                        break;   //do not check any more direction.
                    }
                }  //direction loop end.
            } //checking to see if at least first char matching end.
            if (wordAlreadyFound) {  // do not go through any more columns.
                break;
            }
        }  //column loop end.
        if (wordAlreadyFound) {  // do not go through any more Rows.
            break;
        }
    }   //row loop end.

    if(wordAlreadyFound) {
        printf("%s can be found at row, col = (%d, %d) in the %s direction.\n",
               word, rowLocationWhereWordFound + 1, colLocationWhereWordFound + 1, getDirection(directionWhereWordFound));
    } else {
        printf("%s cannot be found !\n", word);
    }
}

bool check1D(const int Size, char puzzle[][Size], const int wordSize, char* word, int rowLoc, int colLoc, int dir) {
    bool wordFound = false ;
    if (dir == EAST) {  //row constant, column increase
        if (inBounds(rowLoc, colLoc + wordSize, Size)) {
            int index = 0;
            for (int col = colLoc; col < colLoc + wordSize; col++) {
                if (word[index] == puzzle[rowLoc][col]) {
                    wordFound = true;
                } else {
                    wordFound = false;
                    break;// atleast one char is not matching
                }
                index++;
            }
        }
    } else if (dir == WEST) { //row constant, column Decrease
        if (inBounds(rowLoc, colLoc - wordSize, Size)) {
            int index = 0;
            for (int col = colLoc; col > colLoc - wordSize; col--) {
                if (word[index] == puzzle[rowLoc][col]) {
                    wordFound = true;
                } else {
                    wordFound = false;
                    break;// atleast one char is not matching
                }
                index++;
            }
        }
    } else if (dir == NORTH) {  //row decrease column constant
        if (inBounds(rowLoc - wordSize, colLoc , Size)) {
            int index = 0;
            for (int row = rowLoc; row > rowLoc - wordSize; row--) {
                if (word[index] == puzzle[row][colLoc]) {
                    wordFound = true;
                } else {
                    wordFound = false;
                    break;// atleast one char is not matching
                }
                index++;
            }
        }
    } else if (dir == SOUTH) {  //row increase column constant
        if (inBounds(rowLoc + wordSize, colLoc , Size)) {
            int index = 0;
            for (int row = rowLoc; row < rowLoc + wordSize; row++) {
                if (word[index] == puzzle[row][colLoc]) {
                    wordFound = true;
                } else {
                    wordFound = false;
                    break;// atleast one char is not matching
                }
                index++;
            }
        }
    } else if (dir == NORTH_EAST) {  //row decrease and column increase
        if (inBounds(rowLoc - wordSize, colLoc, Size)
            && inBounds(rowLoc, colLoc + wordSize, Size)) {

            int index = 0;
            for (int row = rowLoc; row > rowLoc - wordSize; row--) {
                if (word[index] == puzzle[row][colLoc + index]) {
                    wordFound = true;
                } else {
                    wordFound = false;
                    break;// atleast one char is not matching
                }
                index++;
            }
        }
    }else if (dir == NORTH_WEST) { //row decrease and column decrease
        if (inBounds(rowLoc - wordSize, colLoc, Size)
            && inBounds(rowLoc, colLoc - wordSize, Size)) {
            int index = 0;
            for (int row = rowLoc; row > rowLoc - wordSize; row--, index++) {
                if (word[index] == puzzle[row][colLoc - index]) {
                    wordFound = true;
                } else {
                    wordFound = false;
                    break;// atleast one char is not matching
                }
            }
        }
    }else if (dir == SOUTH_EAST) { // row increase and column increase
        if (inBounds(rowLoc + wordSize, colLoc, Size)
            && inBounds(rowLoc, colLoc + wordSize, Size)) {
            int index = 0;
            for (int row = rowLoc; row < rowLoc + wordSize; row++) {
                if (word[index] == puzzle[row][colLoc + index]) {
                    wordFound = true;
                } else {
                    wordFound = false;
                    break;// atleast one char is not matching
                }
                index++;
            }
        }
    }else if (dir == SOUTH_WEST) { // row increase and column decrease
        if (inBounds(rowLoc + wordSize, colLoc, Size)
            && inBounds(rowLoc, colLoc - wordSize, Size)) {
            int index = 0;
            for (int row = rowLoc; row < rowLoc + wordSize; row++, index++) {
                if (word[index] == puzzle[row][colLoc - index]) {
                    wordFound = true;
                } else {
                    wordFound = false;
                    break;// atleast one char is not matching
                }
            }
        }
    }
    else {
        wordFound = false;
    }
    return wordFound;
}

char* getDirection (int dir) {
    if (dir == EAST)  {
        return "east" ;
    } else if (dir == WEST) {
        return "west" ;
    } else if (dir == NORTH) {
        return "north" ;
    } else if (dir == SOUTH) {
        return "south";
    } else if (dir == NORTH_EAST) {
        return "north-east";
    } else if (dir == NORTH_WEST) {
        return "north-west" ;
    } else if (dir == SOUTH_EAST) {
        return "south-east";
    } else if (dir == SOUTH_WEST){
        return "south-west";
    }
    return NULL;
}

char* readWord(int* wordSize) {
    printf("How many characters are there in the word ?\n");
    scanf("%d", wordSize);
    char* word = (char*)malloc((*wordSize) * sizeof(char));
    printf("What is the word that you are looking for ?\n");
    scanf("%s", word);
    return word ;
}

void readWordPuzzle(const int Size, char puzzle[][Size]) {
        printf("Please enter the word puzzle :\n");
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                scanf("%s", &puzzle[i][j]);
            }
        }
}

bool inBounds(int row, int col, const int Size) {
    return ! (row >= Size  || row < -1 || col >= Size, col < -1) ;  //todo check edge case to see we need -1 or not.
}

void printWordPuzzle(const int Size, char puzzle[][Size]) {
    printf("The word puzzle entered is\n");
    for (int row = 0; row < Size; row++) {
        for (int col = 0; col < Size; col++) {
            printf("%c ", puzzle[row][col]);
        }
        printf("\n");
    }
}

void printWord(char* word, const int wordSize) {
    for (int index = 0; index < wordSize; index++) {
        printf("%c", word[index]);
    }
}

//gcc lab6.c -o lab6
//~aps105i/public/exercise 6 lab6