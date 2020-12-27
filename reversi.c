#include <stdio.h>
#include <stdbool.h>

//Function declarations
void printNewBoard(char board[][26], int n);
void printBoard(char board[][26], int n);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool positionInBounds(int n, int row, int col);
void printAvailableMoves(char board[][26], char colour, int n);
bool checkAllDirections(char board[][26], int n, int row, int col, char colour);
void flipTileinAllDirections(char board[][26], int n, int row, int col, char colour);
void flipTileInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
bool isValidMove(char board[][26], int row, int col, char colour, int n);
char returnFirstAvailableCol(char board[][26], char colour, int n);
char returnFirstAvailableRow(char board[][26], char colour, int n);
int checkValidAndFlip(char board[][26], int row, int col, char colour, int n, int deltaRow, int deltaCol);
int checkValidAndFlipAllDirectionsReturnCol(char board[][26], int row, int col, char colour, int n);
int checkValidAndFlipAllDirectionsReturnRow(char board[][26], int row, int col, char colour, int n);


// print the board
void printBoard(char board[][26], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            board[i][j] = 'U';
        }
    }

    //Put positions of black and white in centre
    int rowPlace = n / 2 - 1;
    int colPlace = n / 2;
    board[rowPlace][rowPlace] = 'W';
    board[colPlace][colPlace] = 'W';
    board[rowPlace][colPlace] = 'B';
    board[colPlace][rowPlace] = 'B';
    // print header horizontally

    printf("  ");
    for (i = 0; i < n; i++) {
        printf("%c", (i + 'a'));
    }
    printf("\n");

    // print header vertically with the board initialized earlier.
    for (i = 0; i < n; i++) {
        printf("%c", (i + 'a'));
        printf(" ");
        for (j = 0; j < n; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}
//Print new board with the tiles
void printNewBoard(char board[][26], int n) {
    int i, j;
    printf("  ");
    for (i = 0; i < n; i++) {
        printf("%c", (i + 'a'));
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%c", (i + 'a'));
        printf(" ");
        for (j = 0; j < n; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

//call this function in checkLegalInDirection and when you need to check if it is within bounds.
bool positionInBounds(int n, int row, int col) {
    if (((row >= 0) && (col >= 0)) && ((row < n) && (col < n))) {
        return true;
    }
    else {
        return false;
    }
}

//changes the color to know to continue moving in a particular direction 
char oppositeColour(char colour) {
    if (colour == 'B')
        return 'W';

    if (colour == 'W')
        return 'B';
}

//checking legality of positions including positioning, and if there is already an existing tile on one side of the straight line of opposite color.
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    //The idea is to call function 8 times, and list in increasing row then increasing col order the avalability
   
    int newRow, newCol;
    newRow = row + deltaRow;
    newCol = col + deltaCol;
    //Checking if the delta position is available by seeing if it is in boounds, and of an opposite colour when it continues walking in that direction. 
    //If the other side has the color in question, then it is legal.
    while (positionInBounds(n, newRow, newCol) && board[newRow][newCol] == oppositeColour(colour)) {
        newRow += deltaRow;
        newCol += deltaCol;
        if (positionInBounds(n, newRow, newCol) && board[newRow][newCol] == colour)
            return true;
    }
    return false;
}

//Checks all 8 directions, and if one diretion is available, that position on the board is legal.
bool checkAllDirections(char board[][26], int n, int row, int col, char colour) {
    bool legalBottomWest, legalBottom, legalBottomEast, legalEast, legalWest, legalNorthWest, legalNorthEast, legalNorth;
    int deltaRow, deltaCol;
    //current position has to be empty, or it won't be legal.
    if (board[row][col] != 'U') {
        return false;
    }
    deltaRow = -1;
    deltaCol = -1;
    legalNorthWest = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = -1;
    deltaCol = 0;
    legalNorth = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = -1;
    deltaCol = 1;
    legalNorthEast = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 0;
    deltaCol = -1;
    legalWest = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 0;
    deltaCol = 1;
    legalEast = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 1;
    deltaCol = -1;
    legalBottomWest = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 1;
    deltaCol = 0;
    legalBottom = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 1;
    deltaCol = 1;
    legalBottomEast = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    if (legalBottomEast || legalBottom || legalBottomWest || legalWest || legalEast || legalNorthEast || legalNorth || legalNorthWest) {
        return true;
    }

    else {
        return false;
    }
}

//Print all available moves after checking all 8 directions, prints in characters.
void printAvailableMoves(char board[][26], char colour, int n) {
    //call check valid function in here
    int row, col;
    for (row = 0; row < n; row++)
        for (col = 0; col < n; col++) {
            if (checkAllDirections(board, n, row, col, colour)) {
                printf("%c%c", row + 'a', col + 'a');
                printf("\n");
            }
        }
}

void computerPlayMove(char board[][26], char colour, int n) {
    int row, col;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (checkAllDirections(board, n, row, col, colour)) {
                board[row][col] = colour;
                return;
            }
        }
    }
}

char returnFirstAvailableRow(char board[][26], char colour, int n) {
    int row, col;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (checkAllDirections(board, n, row, col, colour)) {
                return row + 'a';

            }
        }

    }
}
char returnFirstAvailableCol(char board[][26], char colour, int n) {
    int row, col;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (checkAllDirections(board, n, row, col, colour)) {
                return col + 'a';
            }
        }
    }
}


//Same logic as checking legal in one direction, but this time we flip as we move in one direction.
void flipTileInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {

    int newRow, newCol;
    newRow = row + deltaRow;
    newCol = col + deltaCol;
    //checking for opposite color (white)

    //flips tiles as we continue moving
    while (positionInBounds(n, newRow, newCol) && board[newRow][newCol] == oppositeColour(colour)) {
        board[newRow][newCol] = colour;
        newRow += deltaRow;
        newCol += deltaCol;
    }
}

//Same logic as checking all 8 directions, but will change/flip the color to the the color in question in all 8 directions.
void flipTileinAllDirections(char board[][26], int n, int row, int col, char colour) {
    bool  legalBottomWest, legalBottom, legalBottomEast, legalEast, legalWest, legalNorthWest, legalNorthEast, legalNorth;
    int deltaRow, deltaCol;
    deltaRow = -1;
    deltaCol = -1;
    legalNorthWest = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    if (legalNorthWest)
        flipTileInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = -1;
    deltaCol = 0;

    legalNorth = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
    if (legalNorth)
        flipTileInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = -1;
    deltaCol = 1;

    legalNorthEast = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
    if (legalNorthEast)
        flipTileInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 0;
    deltaCol = -1;
    legalWest = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
    if (legalWest)
        flipTileInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 0;
    deltaCol = 1;
    legalEast = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
    if (legalEast)
        flipTileInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 1;
    deltaCol = -1;
    legalBottomWest = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
    if (legalBottomWest)
        flipTileInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 1;
    deltaCol = 0;
    legalBottom = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
    if (legalBottom)
        flipTileInDirection(board, n, row, col, colour, deltaRow, deltaCol);

    deltaRow = 1;
    deltaCol = 1;
    legalBottomEast = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
    if (legalBottomEast)
        flipTileInDirection(board, n, row, col, colour, deltaRow, deltaCol);
}


bool isValidMove(char board[][26], int row, int col, char colour, int n) {

    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (checkAllDirections(board, n, row, col, colour)) {
                return true;
            }
        }
    } return false;
}
bool isBoardFillable(char board[][26], int n) {
    int row, col;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (board[row][col] == 'U') {
                return true;
            }
        }
    }
    return false;
}

char countNumberOfTiles(char board[][26], char colour, int n) {
    int row, col;
    int countBlacks = 0, countWhites = 0;
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (board[row][col] == 'B') {

                countBlacks++;
            }
            if (board[row][col] == 'W') {
                countWhites++;
            }
        }
    }


    if (countBlacks > countWhites) {
        return 'B';
    }
    if (countWhites > countBlacks) {
        return 'W';

    }

    if (countBlacks = countWhites) {
        return 'D';
    }
}

//this is one direction
int checkValidAndFlip(char board[][26], int row, int col, char colour, int n, int deltaRow, int deltaCol) {
    //if flip = true we call flip function
    int counter = 0;
    int countTiles = 0;
    int newRow = 0, newCol = 0;
    newRow = row + deltaRow;
    newCol = col + deltaCol;

    //checking for opposite color (white)

    //flips tiles as we continue moving

    while (positionInBounds(n, newRow, newCol) && board[newRow][newCol] == oppositeColour(colour)) {
        counter++;
        newRow += deltaRow;
        newCol += deltaCol;

    }
    countTiles = counter;
    return countTiles;

}


int checkValidAndFlipAllDirectionsReturnRow(char board[][26], int row, int col, char colour, int n) {
    int topleft = 0, top = 0, topright = 0, left = 0, right = 0, bottomleft = 0, bottom = 0, bottomright = 0;
    bool  legalBottomWest, legalBottom, legalBottomEast, legalEast, legalWest, legalNorthWest, legalNorthEast, legalNorth;
    int finalTileCount = 0;
    int countTilesTotal = 0;
    int deltaRow = 0, deltaCol = 0;
    int maxRowPosition = 0, maxColPosition = 0;
    int rowCount, colCount;

    for (rowCount = 0; rowCount < n; rowCount++) {
        for (colCount = 0; colCount < n; colCount++) {

            if (board[rowCount][colCount] == 'U') {
                deltaRow = -1;
                deltaCol = -1;
                legalNorthWest = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalNorthWest)
                    topleft = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);


                deltaRow = -1;
                deltaCol = 0;
                legalNorth = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalNorth)
                    top = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = -1;
                deltaCol = 1;
                legalNorthEast = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalNorthEast)
                    topright = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 0;
                deltaCol = -1;
                legalWest = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalWest)
                    left = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 0;
                deltaCol = 1;
                legalEast = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalEast)
                    right = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 1;
                deltaCol = -1;
                legalBottomWest = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalBottomWest)
                    bottomleft = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 1;
                deltaCol = 0;
                legalBottom = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalBottom)
                    bottom = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 1;
                deltaCol = 1;
                legalBottomEast = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalBottomEast)
                    bottomright = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                countTilesTotal = topleft + top + topright + left + right + bottomleft + bottom + bottomright;

                if ((countTilesTotal > finalTileCount)) {
                    finalTileCount = countTilesTotal;
                    maxRowPosition = rowCount;
                    maxColPosition = colCount;

                }


                countTilesTotal = 0;
                topleft = 0, top = 0, topright = 0, left = 0, right = 0, bottomleft = 0, bottom = 0, bottomright = 0;

            }
          
        }
    }

    return maxRowPosition;

}

int checkValidAndFlipAllDirectionsReturnCol(char board[][26], int row, int col, char colour, int n) {

    int topleft = 0, top = 0, topright = 0, left = 0, right = 0, bottomleft = 0, bottom = 0, bottomright = 0;
    bool  legalBottomWest, legalBottom, legalBottomEast, legalEast, legalWest, legalNorthWest, legalNorthEast, legalNorth;
    int finalTileCount = 0;
    int countTilesTotal = 0;
    int deltaRow = 0, deltaCol = 0;
    int maxRowPosition = 0, maxColPosition = 0;
    int rowCount, colCount;



    for (rowCount = 0; rowCount < n; rowCount++) {
        for (colCount = 0; colCount < n; colCount++) {
            if (board[rowCount][colCount] == 'U') {

                deltaRow = -1;
                deltaCol = -1;
                legalNorthWest = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalNorthWest)
                    topleft = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);


                deltaRow = -1;
                deltaCol = 0;
                legalNorth = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalNorth)
                    top = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = -1;
                deltaCol = 1;
                legalNorthEast = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalNorthEast)
                    topright = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 0;
                deltaCol = -1;
                legalWest = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalWest)
                    left = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 0;
                deltaCol = 1;
                legalEast = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalEast)
                    right = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 1;
                deltaCol = -1;
                legalBottomWest = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalBottomWest)
                    bottomleft = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 1;
                deltaCol = 0;
                legalBottom = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalBottom)
                    bottom = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                deltaRow = 1;
                deltaCol = 1;
                legalBottomEast = checkLegalInDirection(board, n, rowCount, colCount, colour, deltaRow, deltaCol);
                if (legalBottomEast)
                    bottomright = checkValidAndFlip(board, rowCount, colCount, colour, n, deltaRow, deltaCol);

                countTilesTotal = topleft + top + topright + right + left + bottomleft + bottom + bottomright;



                if ((countTilesTotal > finalTileCount)) {
                    finalTileCount = countTilesTotal;
                    maxRowPosition = rowCount;
                    maxColPosition = colCount;


                }
                countTilesTotal = 0;
                topleft = 0, top = 0, topright = 0, left = 0, right = 0, bottomleft = 0, bottom = 0, bottomright = 0;
            }
        }
    }

    return maxColPosition;

}


int main(void) {

    //Dimension
    printf("Enter the board dimension: ");
    int n;
    //expects even number that is maximum 26
    scanf("%d", &n);
    //init variables 
    char colour, rowSelect, colSelect;
    int row=0, col=0;
    char board[26][26];
    char computerColour;
   
    int rowChar, colChar;

    //input computer colour and print board 
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);
    printBoard(board, n);


    //Black gets first turn, get human colour
    char currentTurn = 'B';
    char humanTurn = oppositeColour(computerColour);


    while (isBoardFillable(board, n) && ((isValidMove(board, row, col, oppositeColour(currentTurn), n)) || (isValidMove(board, row, col, currentTurn, n)))) {
        if (currentTurn == computerColour) {
            //make computer move 

            rowChar = checkValidAndFlipAllDirectionsReturnRow(board, row, col, computerColour, n);
            colChar = checkValidAndFlipAllDirectionsReturnCol(board, row, col, computerColour, n);


            printf("Computer places %c at %c%c. \n", computerColour, rowChar + 'a', colChar + 'a');


            board[rowChar][colChar] = computerColour;
            flipTileinAllDirections(board, n, rowChar, colChar, computerColour);
            printNewBoard(board, n);
            currentTurn = computerColour;
        }

        else {
            printf("Enter move for colour %c (RowCol): ", humanTurn);
            scanf(" %c%c", &rowSelect, &colSelect);
            rowSelect = rowSelect - 'a';
            colSelect = colSelect - 'a';


            //Checking legality of human move.
            //LOOK AT COLOUR.
            if (checkAllDirections(board, n, rowSelect, colSelect, humanTurn)) {
                board[rowSelect][colSelect] = humanTurn;
                flipTileinAllDirections(board, n, rowSelect, colSelect, humanTurn);
                printNewBoard(board, n);
                currentTurn = humanTurn;
            }

            else {
                printf("Invalid move.\n");
                printf("%c player wins.", computerColour);
                return 0;
            }
        }

        //Decide if computer or player turn.

        if (isBoardFillable(board, n) && ((isValidMove(board, row, col, oppositeColour(currentTurn), n)) || (isValidMove(board, row, col, currentTurn, n)))) {
            if (isValidMove(board, row, col, oppositeColour(currentTurn), n)) {
                currentTurn = oppositeColour(currentTurn);
            }


            else if (isValidMove(board, row, col, currentTurn, n)) {
                printf("%c player has no valid move.\n", oppositeColour(currentTurn));
                currentTurn = currentTurn;
            }

            //no one has a turn
        }

        //No one has a move, state winner.
        else {
            char declareWinner = countNumberOfTiles(board, colour, n);
            if (declareWinner == 'W') {
                printf("W player wins.");
            }
            if (declareWinner == 'B') {
                printf("B player wins.");
            }
            if (declareWinner == 'D') {
                printf("Draw!");
            }
            return 0;

        }
    }

    return 0;
}
