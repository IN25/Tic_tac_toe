//TIC-TAC-TOE [game]

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;

void displayBoard(string b[][SIZE]);
bool userFirst();
bool currentPlayerWon(string b[][SIZE], string symbol);
void generateComputerMove(string b[][SIZE]);
void randomMove(string b[][SIZE]);

int main()
{
  //construct board
  string board[SIZE][SIZE];

  int position_id = 1;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      board[i][j] = to_string(position_id);
      /*  stringstream ss;
        ss << position_id;
        board[i][j] = ss.str();
        */
      position_id++;
    }
  }

  //Initial game output
  cout << "Welcome to Tic-Tac-Toe" << endl;

  bool userTurn = userFirst();
  if (userTurn == true)
  {
    cout << "Player goes first!" << endl;
  }
  else
  {
    cout << "Computer goes first!" << endl;
  }

  //Loop for turn taking in game
  int positionsRemaining = SIZE * SIZE;
  bool userWon = false;
  bool computerWon = false;

  while ((positionsRemaining > 0) && (!userWon) && (!computerWon))
  {
    displayBoard(board);

    //User's turn
    if (userTurn)
    {
      bool validMove = false;
      while (!validMove)
      {
        int position_id;
        cout << "Enter a position: ";
        cin >> position_id;
        if ((position_id <= (SIZE * SIZE)) && (position_id > 0))
        {
          int row = (position_id - 1) / SIZE;
          int col = (position_id - 1) % SIZE;
          //cout << "row = " << row << " col = " << col << endl;
          if ((board[row][col] != "X") && (board[row][col] != "O"))
          {
            board[row][col] = "X";
            validMove = true;
          }
          else
          {
            cout << "Position already used. Try again." << endl;
          }
        }
        else
        {
          cout << "Position invalid. Try again." << endl;
        }
      }
      positionsRemaining--;
      userWon = currentPlayerWon(board, "X");
      userTurn = false;
    }

    //Computer's turn
    else
    {
      //The row and col are both passed as call-by-reference
      generateComputerMove(board);

      positionsRemaining--;
      computerWon = currentPlayerWon(board, "O");
      userTurn = true;
    }
  }

  //Display game result
  displayBoard(board);
  if (userWon)
  {
    cout << "Congratulations! You have won!" << endl;
  }
  else if (computerWon)
  {
    cout << "The computer has won. Try again." << endl;
  }
  else
  {
    cout << "Out of moves. Try again." << endl;
  }

  return 0;
}

void displayBoard(string b[][SIZE])
{
  cout << "Tic-tac-toe board:" << endl
       << endl;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      cout << b[i][j] << "\t";
    }
    cout << endl;
  }
  cout << endl;
}

bool userFirst()
{
  //set seed for random number generation
  srand(time(NULL));

  //generate a random number
  //0 for computer
  //1 for user
  int num = rand() % 2;
  if (num == 0)
  {
    return false;
  }
  return true;
}

//Return true if player/computer with symbol (X or O) has won
bool currentPlayerWon(string b[][SIZE], string symbol)
{
  //Horizontal case
  //Loop through each row
  for (int i = 0; i < SIZE; i++)
  {
    bool rowWinDetected = true;
    //Check all positions in row and see if they are the same symbol
    for (int j = 0; j < SIZE; j++)
    {
      if (b[i][j] != symbol)
      {
        rowWinDetected = false;
      }
    }
    if (rowWinDetected)
    {
      return true;
    }
  }

  //Vertical case
  //Loop through each column
  for (int i = 0; i < SIZE; i++)
  {
    bool colWinDetected = true;
    //Check all positions in column and see if they are the same symbol
    for (int j = 0; j < SIZE; j++)
    {
      if (b[j][i] != symbol)
      {
        colWinDetected = false;
      }
    }
    if (colWinDetected)
    {
      return true;
    }
  }

  //Diagonal case #1
  bool diagonal1WinDetected = true;
  for (int i = 0; i < SIZE; i++)
  {
    if (b[i][i] != symbol)
    {
      diagonal1WinDetected = false;
    }
  }
  if (diagonal1WinDetected)
  {
    return true;
  }

  //Diagonal case #2
  bool diagonal2WinDetected = true;
  for (int i = 0; i < SIZE; i++)
  {
    if (b[(SIZE - 1) - i][i] != symbol)
    {
      diagonal2WinDetected = false;
    }
  }
  if (diagonal2WinDetected)
  {
    return true;
  }

  //otherwise win not diagonal2WinDetected
  return false;
}

void generateComputerMove(string b[][SIZE])
{

  //This code puts third 0 in a row, column, and 2 diagonal cases
  //Horizontal strategy
  //Loop through each row
  for (int i = 0; i < SIZE; i++)
  {
    int positionOccupied = 0;
    //loop through each position in the row
    for (int j = 0; j < SIZE; j++)
    {
      if (b[i][j] == "O")
      {
        //increment if O is detected
        positionOccupied += 1;
      }
    }

    //check if 2 positions in that row is occupied
    if (positionOccupied == 2)
    {
      //loop through each position in the row and put O on that row
      for (int j = 0; j < SIZE; j++)
      {
        if ((b[i][j] != "O") && (b[i][j] != "X"))
        {
          //put O if position not occupied by X or O
          b[i][j] = "O";
          return;
        }
      }
    }
  }

  //vertical strategy
  //loop through each column
  for (int i = 0; i < SIZE; i++)
  {
    int positionOccupied = 0;
    //loop through each position in a column
    for (int j = 0; j < SIZE; j++)
    {
      if (b[j][i] == "O")
      {
        //increment if O is detected
        positionOccupied += 1;
      }
    }

    //put O if there are 2 consecutive Os
    if (positionOccupied == 2)
    {
      for (int j = 0; j < SIZE; j++)
      {
        if ((b[j][i] != "X") && (b[j][i] != "O"))
        {
          //put O if position not occupied by X or O
          b[j][i] = "O";
          return;
        }
      }
    }
  }

  //Diagonal strategy
  //case 1
  int occupiedDiagonal1 = 0;
  for (int i = 0; i < SIZE; i++)
  {
    //loop through each position in a diagonal line
    if (b[i][i] == "O")
    {
      //increment by 1 if O is detected
      occupiedDiagonal1 += 1;
    }

    if (occupiedDiagonal1 == 2)
    {
      //loop through each position in a diagonal line
      for (int i = 0; i < SIZE; i++)
      {
        if ((b[i][i] != "X") && (b[i][i] != "O"))
        {
          //put O if not occupied by O or X
          b[i][i] = "O";
          return;
        }
      }
    }
  }

  //case 2
  int occupiedDiagonal2 = 0;
  //loop through each position in a diagonal line
  for (int i = 0; i < SIZE; i++)
  {
    if (b[(SIZE - 1) - i][i] == "O")
    {
      //increment by 1 if O is detected
      occupiedDiagonal2 += 1;
    }

    if (occupiedDiagonal2 == 2)
    {
      //loop through each position in a diagonal line
      for (int i = 0; i < SIZE; i++)
      {
        if ((b[(SIZE - 1) - i][i] != "X") && (b[(SIZE - 1) - i][i] != "O"))
        {
          //put O if not occupied by O or X
          b[(SIZE - 1) - i][i] = "O";
          return;
        }
      }
    }
  }

  //This code prevents enemy from winning(from putting 3X in a row, column and 2 diagonals)
  //Horizontal prevention
  //Loop through each row
  for (int i = 0; i < SIZE; i++)
  {
    int positionOccupied = 0;
    //loop through each position in the row
    for (int j = 0; j < SIZE; j++)
    {
      if (b[i][j] == "X")
      {
        //increment by 1 is X is detected
        positionOccupied += 1;
      }
    }

    //check if 2 position in that row is occupied
    if (positionOccupied == 2)
    {
      //loop through each position in the row and put O on that row
      for (int j = 0; j < SIZE; j++)
      {
        if ((b[i][j] != "X") && (b[i][j] != "O"))
        {
          //put O if a position is not occupied by O or X
          b[i][j] = "O";
          return;
        }
      }
    }
  }

  //vertical prevention
  for (int i = 0; i < SIZE; i++)
  {
    int positionOccupied = 0;
    //loop through each position in a column
    for (int j = 0; j < SIZE; j++)
    {
      if (b[j][i] == "X")
      {
        positionOccupied += 1;
      }
    }

    if (positionOccupied == 2)
    {
      //loop through each position in a column
      for (int j = 0; j < SIZE; j++)
      {
        if ((b[j][i] != "X") && (b[j][i] != "O"))
        {
          //put O if a position is not occupied by O or X
          b[j][i] = "O";
          return;
        }
      }
    }
  }

  //Diagonal prevention
  //case 1
  int occupiedDiagonalPrevention1 = 0;
  //loop through each position in a diagonal line
  for (int i = 0; i < SIZE; i++)
  {

    if (b[i][i] == "X")
    {
      //increment by 1 if X is detected
      occupiedDiagonalPrevention1 += 1;
    }

    if (occupiedDiagonalPrevention1 == 2)
    {
      //loop through each position in a diagonal line
      for (int i = 0; i < SIZE; i++)
      {
        if ((b[i][i] != "X") && (b[i][i] != "O"))
        {
          //put O if a position is not occupied by O or X
          b[i][i] = "O";
          return;
        }
      }
    }
  }

  //case 2
  int occupiedDiagonalPrevention2 = 0;
  //loop through each position in a diagonal line
  for (int i = 0; i < SIZE; i++)
  {
    if (b[(SIZE - 1) - i][i] == "X")
    {
      //increment by 1 if X is detected
      occupiedDiagonalPrevention2 += 1;
    }

    if (occupiedDiagonalPrevention2 == 2)
    {
      //loop through each position in a diagonal line
      for (int i = 0; i < SIZE; i++)
      {
        if ((b[(SIZE - 1) - i][i] != "X") && (b[(SIZE - 1) - i][i] != "O"))
        {
          //put O if a position is not occupied by O or X
          b[(SIZE - 1) - i][i] = "O";
          return;
        }
      }
    }
  }

  //make a random move if you don't have a strategy to make or anything to prevent 
  randomMove(b);
}

void randomMove(string b[][SIZE])
{
  bool validMove = false;
  while (!validMove)
  {
    int row = rand() % SIZE;
    int col = rand() % SIZE;
    if ((b[row][col] != "X") && (b[row][col] != "O"))
    {
      b[row][col] = "O";
      validMove = true;
    }
  }
}