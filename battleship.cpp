/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

static FILE* battleshipMy;
static FILE* battleshipOp;
static CellContent mine[FIELDSIZE][FIELDSIZE];
static CellContent op[FIELDSIZE][FIELDSIZE];
static CellContent guess[FIELDSIZE][FIELDSIZE];


void load_game()
{
  battleshipMy = fopen("battleship.my", "r");
  battleshipOp = fopen("battleship.op", "r");

 fread(mine, sizeof(mine), FIELDSIZE, battleshipMy);
 fread(op, sizeof(op), FIELDSIZE, battleshipOp);

 for (int i = 0; i < FIELDSIZE; i++) {
   for (int j = 0; j < FIELDSIZE; j++) {
     guess[i][j] = Unknown;
   }
}

}
/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
  if (row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)
  {
    return OutOfRange;
  }
  return mine[row][col];

}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/



bool shoot(int row, int col)
{
  if (row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)
  {
    return false;
  }
  if(op[row][col] == Boat)
  {

    CheckBorder(row-1, col-1);
    CheckBorder(row-1, col);
    CheckBorder(row-1, col+1);
    CheckBorder(row, col-1);
    CheckBorder(row, col+1);
    CheckBorder(row+1, col-1);
    CheckBorder(row+1, col);
    CheckBorder(row+1, col+1);
  }

  guess[row][col] = op[row][col];
  return true;
}

void CheckBorder(int row, int col)
{
  if(row < 0 || col < 0 || row >= FIELDSIZE || col >= FIELDSIZE)
  {
    return;
  }
  else
  {
    guess[row][col] = Water;
  }
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
  if (row < 0 || row >= FIELDSIZE || col < 0 || col >= FIELDSIZE)
  {
    return OutOfRange;
  }
  return guess[row][col];
}
