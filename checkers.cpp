/******************************************************************************
** Program Filename: Checkers.cpp
** Author: Ben Johnson
** Date: March 12, 2018
** Description: A text based version of checkers with standard rules. The
**  baord is stored as a 2D array and input is given through C-style strings.
** Input: Various C-style strings inputed by the user.
** Output: Prints of the board and prompts for what to do.
******************************************************************************/

#include <iostream>
#include <cstring>
#include <cmath>
#include <string>

using namespace std;

//prototypes of all functions in program.
int** init_board(int size);
void pop_board(int** board, int size);
void print_board(int** board, int size);
int check_args(int argc, char** argv);
void start_game(int size);
void play_game(int** board, int size);
void end_game(int** board, int size, int count);
bool is_game_over(int count, int** board, int size);
void next_turn(int count, int** board, int size);
void print_turn(int** board, int size, int count);
void tokens_captured(int** board, int size);
void make_kings(int** board, int size, int count);
void add_char(char** input, char character);
void preform_move(int** board, int size, char* input, int i);
void modify_board(int** board, int size, int from_row, int from_col, int to_row, int to_col);
void get_coords(char* input, int i, int size, int &from_row, int &from_col, int &to_row, int &to_col);
void get_coords_8(char* input, int i, int size, int &from_row, int &from_col, int &to_row, int &to_col);
void get_coords_10(char* input, int i, int size, int &from_row, int &from_col, int &to_row, int &to_col);
void get_coords_12(char* input, int i, int size, int &from_row, int &from_col, int &to_row, int &to_col);
char* get_input();
bool check_input(char* input, int size, int count, int** board);
bool check_input_8(char* input, int size, int count, int** board);
bool check_input_10(char* input, int size, int count, int** board);
bool check_input_12(char* input, int size, int count, int** board);
bool check_coords(char* input, int size, int count, int** board);
bool check_single(char* input, int size, int count, int** board);
bool check_single_move(char* input, int size, int count, int** board);
bool check_single_jump(char* input, int size, int count, int** board);
bool check_double(char* input, int size, int count, int** board);
bool check_jump(char* input, int size, int count, int** board, int row, int col, int i);
bool move_possible_red(int count, int** board, int size, int row, int col);
bool move_possible_red_jump(int count, int** board, int size, int row, int col);
bool move_possible_black(int count, int** board, int size, int row, int col);
bool move_possible_black_jump(int count, int** board, int size, int row, int col);
bool move_possible_red_king(int count, int** board, int size, int row, int col);
bool move_possible_black_king(int count, int** board, int size, int row, int col);
bool move_possible_red_king_jump(int count, int** board, int size, int row, int col);
bool move_possible_black_king_jump(int count, int** board, int size, int row, int col);

/******************************************************************************
** Function: Initialize Board
** Description: Creates and Intializes the game board.
** Parameters: int size: the length of the board.
** Pre-Conditions: Size is a valid size.
** Post-Conditions: The game board is intialized.
******************************************************************************/
int** init_board(int size)
{
  int** board = new int*[size];
  for(int i = 0; i < size; i++)
  {
    board[i] = new int[size];
  }
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      if((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))
        board[i][j] = -1;
      else
        board[i][j] = 0;
    }
  }
  return board;
}

/******************************************************************************
** Function: Populate Board
** Description: Populates the board with all of the players' tokens.
** Parameters: int size: the length of the board.
**  int** board: the actual board array to populate.
** Pre-Conditions: Size and is a valid size and board is initialized.
** Post-Conditions: The game board is populated.
******************************************************************************/
 void pop_board(int** board, int size)
 {
   for(int i = 0; i < size / 2 - 1; i++)
   {
     for(int j = 0; j < size; j++)
     {
       if((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
        board[i][j] = 1;
     }
   }
   for(int i = size / 2 + 1; i < size; i++)
   {
     for(int j = 0; j < size; j++)
     {
       if((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
        board[i][j] = 3;
     }
   }
 }

 /******************************************************************************
 ** Function: Print Board
 ** Description: Prints the current board to the terminal.
 ** Parameters: int size: the length of the board.
 **  int** board: the actual board array to print.
 ** Pre-Conditions: Size and is a valid size and board is initialized.
 ** Post-Conditions: The game board is printed.
 ******************************************************************************/
void print_board(int** board, int size)
{
  for(int i = 0; i < size; i++)
  {
    if(size - i >= 10)
      cout << size - i;
    else
      cout << size - i << " ";
    for(int j = 0; j < size; j++)
    {
      if (i % 2 == 0 && j % 2 == 0 || i % 2 == 1 && j % 2 == 1)
        cout << "\033[30;47m " << " " << " \033[0m";
      else if(board[i][j] == 1) cout << "\033[31;40m " << "O" << " \033[0m";
      else if(board[i][j] == 2) cout << "\033[31;40m " << "K" << " \033[0m";
      else if(board[i][j] == 3) cout << "\033[37;40m " << "O" << " \033[0m";
      else if(board[i][j] == 4) cout << "\033[37;40m " << "K" << " \033[0m";
      else cout << "\033[37;40m " << " " << " \033[0m";
    }
    cout << endl;
  }
  cout << "  ";
  for(int i = 0; i < size; i++)
    cout << " " << char(65 + i) << " ";
  cout << endl;
}

/******************************************************************************
** Function: Check Argumnents
** Description: returns the a correct size for the board based on user input.
** Parameters: int argc: the number of command line arguments.
**   char** argv: the actual array of command line arguments.
** Pre-Conditions: None
** Post-Conditions: size is a valid size..
******************************************************************************/
int check_args(int argc, char** argv)
{
  if(argc == 2 && strlen(argv[1]) == 1 && argv[1][0] == '8')
    return 8;
  else if(argc == 2 && strlen(argv[1]) == 2 && argv[1][0] == '1' && argv[1][1] == '0')
    return 10;
  else if(argc == 2 && strlen(argv[1]) == 2 && argv[1][0] == '1' && argv[1][1] == '2')
    return 12;
  else
  {
    string input = "";
    do
    {
      cout << "You entered an invalid command line argument." << endl;
      cout << "Please enter a valid size for the checker board: ";
      getline(cin, input);
    }while(input != "8" && input != "10" && input != "12");
    if(input == "8")
      return 8;
    else if(input == "10")
      return 10;
    else
      return 12;
  }
}

/******************************************************************************
** Function: Start Game
** Description: Initializes everything for the game.
** Parameters: int size: the length of the board.
** Pre-Conditions: Size and is a valid size.
** Post-Conditions: The game has started.
******************************************************************************/
void start_game(int size)
{
  int** board = init_board(size);
  pop_board(board, size);
  play_game(board, size);
}

/******************************************************************************
** Function: Plau Game
** Description: Holds the main game loop, runs until the game ends.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: The game is over.
******************************************************************************/
void play_game(int** board, int size)
{
  int count = 0;
  cout << "\n************************************************" << endl;
  cout <<   "              Welcome to Checkers!" << endl;
  cout <<   "                 By Ben Johnson" << endl;
  cout << "************************************************" << endl;
  while(true)
  {
    if(is_game_over(count, board, size))
      break;
    cout << "\n************************************************\n" << endl;
    next_turn(count, board, size);
    count++;
    if(count == 2)
    count = 0;
  }
  end_game(board, size, count);
}

/******************************************************************************
** Function: End Game
** Description: Prints out winner and cleans up memory.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: Memory is freed.
******************************************************************************/
void end_game(int** board, int size, int count)
{
    cout << "\n************************************************\n" << endl;
    print_board(board, size);
    cout << "\n************************************************\n" << endl;
    if(count == 0)
      cout << "White Player wins!\n" << endl;
    else
      cout << "Red Player wins!\n" << endl;

    for(int i = 0; i < size; i++)
      delete [] board[i];
    delete [] board;
}

/******************************************************************************
** Function: Is Game Over
** Description: Checks if the game is over.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool is_game_over(int count, int** board, int size)
{
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      if(count == 0)
      {
        if(move_possible_red(count, board, size, i, j) ||
           move_possible_red_jump(count, board, size, i, j) ||
           move_possible_red_king(count, board, size, i, j) ||
           move_possible_red_king_jump(count, board, size, i, j))
          return false;
      }
      else if(count == 1)
      {
        if(move_possible_black(count, board, size, i, j) ||
           move_possible_black_jump(count, board, size, i, j) ||
           move_possible_black_king(count, board, size, i, j) ||
           move_possible_black_king_jump(count, board, size, i, j))
          return false;
      }
    }
  }
  return true;
}

/******************************************************************************
** Function: Next Turn
** Description: Runs through an entire turn for one player.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: one more turn has been played.
******************************************************************************/
void next_turn(int count, int** board, int size)
{
  print_turn(board, size, count);
  char* input = new char[1];
  input[0] = '\0';
  do
  {
    delete[] input;
    input = get_input();
  }while(!check_input(input, size, count, board));
  int i = 0;
  while(strlen(input) - i > 3)
  {
    preform_move(board, size, input, i);
    make_kings(board, size, count);
    for(i; i < strlen(input); i++)
    {
      if(input[i] == ' ')
        break;
    }
    i++;
  }
  tokens_captured(board, size);
  delete[] input;
}

/******************************************************************************
** Function: Print Turn
** Description: Prints the current turn to the terminal.
** Parameters: int size: the length of the board.
**  int** board: the actual board array to print.
** Pre-Conditions: Size and is a valid size and board is initialized.
** Post-Conditions: The game board is printed.
******************************************************************************/
void print_turn(int** board, int size, int count)
{
  print_board(board, size);
  cout << "\n************************************************\n" << endl;
  if(count == 0) 
    cout << "Red Player's Turn" << endl;
  else 
    cout << "White Player's Turn" << endl;
}

/******************************************************************************
** Function: Tokens Captured
** Description: prints out the number of tokens captured.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: one more turn has been played.
******************************************************************************/
void tokens_captured(int** board, int size)
{
  int red_left = 0, black_left = 0, red_start, black_start;
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      if(board[i][j] == 1 || board[i][j] == 2)
        red_left++;
      if(board[i][j] == 3 || board[i][j] == 4)
        black_left++;
    }
  }
  if(size == 8) {red_start = 12; black_start = 12;}
  else if(size == 10) {red_start = 20; black_start = 20;}
  else if(size == 12) {red_start = 30; black_start = 30;}
  cout << endl;
  cout << "Number of captured Red tokens: " <<  red_start - red_left << endl;
  cout << "Number of captured Black tokens: " <<  black_start - black_left << endl;
}

/******************************************************************************
** Function: Make Kings
** Description: If a token got to the other side of the baord king it.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: all tokens that should be knigs become kings.
******************************************************************************/
void make_kings(int** board, int size, int count)
{
  for(int i = 0; i < size; i++)
  {
    if(board[0][i] == 3)
      board[0][i] = 4;
    if(board[size-1][i] == 1)
      board[size-1][i] = 2;
  }
}

/******************************************************************************
** Function: Preform Move
** Description: preforms all the moves for one players turn.
** Parameters: char* input: the input to check.
**  int size: the size of the board.
**  int** board: the board to modify.
**  int i: the index to start at for input.
** Pre-Conditions: input and size are valid and board is initialized.
** Post-Conditions: the moves have been preformed.
******************************************************************************/
void preform_move(int** board, int size, char* input, int i)
{
  int from_row, from_col, to_row, to_col;
  get_coords(input, i, size, from_row, from_col, to_row, to_col);
  modify_board(board, size, from_row, from_col, to_row, to_col);
}

/******************************************************************************
** Function: Modify board.
** Description: preforms a single move.
** Parameters: int size: the size of the board.
**  int** board: the board to modify.
**  int from_row: the from row of the from coord.
**  int from_col: the from column of the from coord.
**  int to_row: the to row of the to coord.
**  int to_col: the to column of the to coord.
** Pre-Conditions: input and size are valid and board is initialized.
** Post-Conditions: one move has been preformed.
******************************************************************************/
void modify_board(int** board, int size, int from_row, int from_col, int to_row, int to_col)
{
  board[to_row][to_col] = board[from_row][from_col];
  board[from_row][from_col] = 0;
  if(abs(from_row - to_row) == 2)
  {
    board[(from_row+to_row)/2][(from_col+to_col)/2] = 0;
  }
}

/******************************************************************************
** Function: Get Coordinates.
** Description: gets the coordinates from the user input.
** Parameters: int size: the size of the board.
**  char* input: the inputed coordinates.
**  int from_row: the from row of the from coord.
**  int from_col: the from column of the from coord.
**  int to_row: the to row of the to coord.
**  int to_col: the to column of the to coord.
**  int i: the index to start at for input.
** Pre-Conditions: input and size are valid and board is initialized.
** Post-Conditions: from_row, from_col, to_row, and to_col are valid.
******************************************************************************/
void get_coords(char* input, int i, int size, int &from_row, int &from_col, int &to_row, int &to_col)
{
  if(size == 8)
  {
    get_coords_8(input, i, size, from_row, from_col, to_row, to_col);
  }
  else if(size == 10)
  {
    get_coords_10(input, i, size, from_row, from_col, to_row, to_col);
  }
  else
  {
    get_coords_12(input, i, size, from_row, from_col, to_row, to_col);
  }
}

/******************************************************************************
** Function: Get Coordinates 8.
** Description: gets the coordinates from the user input if the size is 8.
** Parameters: int size: the size of the board.
**  char* input: the inputed coordinates.
**  int from_row: the from row of the from coord.
**  int from_col: the from column of the from coord.
**  int to_row: the to row of the to coord.
**  int to_col: the to column of the to coord.
**  int i: the index to start at for input.
** Pre-Conditions: input and size are valid and board is initialized.
** Post-Conditions: from_row, from_col, to_row, and to_col are valid.
******************************************************************************/
void get_coords_8(char* input, int i, int size, int &from_row, int &from_col, int &to_row, int &to_col)
{
  from_row = size - 1 - (input[i+1] - 49);
  from_col = input[i] - 65;
  to_row = size - 1 - (input[i+4] - 49);
  to_col = input[i+3] - 65;
}

/******************************************************************************
** Function: Get Coordinates 10.
** Description: gets the coordinates from the user input if the size is 10.
** Parameters: int size: the size of the board.
**  char* input: the inputed coordinates.
**  int from_row: the from row of the from coord.
**  int from_col: the from column of the from coord.
**  int to_row: the to row of the to coord.
**  int to_col: the to column of the to coord.
**  int i: the index to start at for input.
** Pre-Conditions: input and size are valid and board is initialized.
** Post-Conditions: from_row, from_col, to_row, and to_col are valid.
******************************************************************************/
void get_coords_10(char* input, int i, int size, int &from_row, int &from_col, int &to_row, int &to_col)
{
  if(input[i+2] == ' ')
  {
    from_row = size - 1 - (input[i+1] - 49);
    from_col = input[i] - 65;
    to_col = input[i+3] - 65;
    if(i+4 == strlen(input)-1 || (i+4 < strlen(input)-1 && input[i+5] == ' '))
      to_row = size - 1 - (input[i+4] - 49);
    else
      to_row = 0;
  }
  else
  {
      from_col = input[i] - 65;
      from_row = 0;
      to_col = input[i+4] - 65;
      if(i+5 == strlen(input)-1 || (i+5 < strlen(input)-1 && input[i+6] == ' '))
        to_row = size - 1 - (input[i+5] - 49);
      else
        to_row = 0;
  }
}

/******************************************************************************
** Function: Get Coordinates 12.
** Description: gets the coordinates from the user input if the size is 12.
** Parameters: int size: the size of the board.
**  char* input: the inputed coordinates.
**  int from_row: the from row of the from coord.
**  int from_col: the from column of the from coord.
**  int to_row: the to row of the to coord.
**  int to_col: the to column of the to coord.
**  int i: the index to start at for input.
** Pre-Conditions: input and size are valid and board is initialized.
** Post-Conditions: from_row, from_col, to_row, and to_col are valid.
******************************************************************************/
void get_coords_12(char* input, int i, int size, int &from_row, int &from_col, int &to_row, int &to_col)
{
  if(input[i+2] == ' ')
  {
    from_row = size - 1 - (input[i+1] - 49);
    from_col = input[i] - 65;
    to_col = input[i+3] - 65;
    if(i+4 == strlen(input)-1 || (i+4 < strlen(input)-1 && input[i+5] == ' '))
      to_row = size - 1 - (input[i+4] - 49);
    else if(input[i+5] == '0') to_row = 2;
    else if(input[i+5] == '1') to_row = 1;
    else if(input[i+5] == '2') to_row = 0;
  }
  else
  {
      from_col = input[i] - 65;
      if(input[i+2] == '0') from_row = 2;
      else if(input[i+2] == '1') from_row = 1;
      else if(input[i+2] == '2') from_row = 0;
      to_col = input[i+4] - 65;
      if(i+5 == strlen(input)-1 || (i+5 < strlen(input)-1 && input[i+6] == ' '))
        to_row = size - 1 - (input[i+5] - 49);
      else if(input[i+6] == '0') to_row = 2;
      else if(input[i+6] == '1') to_row = 1;
      else if(input[i+6] == '2') to_row = 0;
  }
}

/******************************************************************************
** Function: Check Input
** Description: checks if the input is a valid move.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: board is intialized and the same size as size.
** Post-Conditions: None.
******************************************************************************/
bool check_input(char* input, int size, int count, int** board)
{
  if(size == 8)
  {
    if(!check_input_8(input, size, count, board))
      return false;
  }
  else if(size == 10)
  {
    if(!check_input_10(input, size, count, board))
      return false;
  }
  else
  {
    if(!check_input_12(input, size, count, board))
      return false;
  }
  if(!check_coords(input, size, count, board))
    return false;
  return true;
}

/******************************************************************************
** Function: Check Coordinates
** Description: checks if the coordinates are valid for the player.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: board is intialized and the same size as size.
** Post-Conditions: None.
******************************************************************************/
bool check_coords(char* input, int size, int count, int** board)
{
  int counter = 0;
  for(int i = 0; i < strlen(input); i++)
  {
    if(input[i] >= 'A' && input[i] <= 'L')
      counter++;
  }
  if(counter == 2)
  {
    //move or single jump
    if(!check_single(input, size, count, board))
      return false;
  }
  else
  {
    //double jump
    if(!check_double(input, size, count, board))
      return false;
  }
  return true;
}

/******************************************************************************
** Function: Check Single
** Description: checks if the coordinates are valid for a single move or jump.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: board is intialized and the same size as size.
** Post-Conditions: None.
******************************************************************************/
bool check_single(char* input, int size, int count, int** board)
{
  int from_row = 0, from_col = 0, to_row = 0, to_col = 0;
  get_coords(input, 0, size, from_row, from_col, to_row, to_col);
  if(!(abs(from_row-to_row) == 1 && abs(from_col-to_col) == 1) && 
     !(abs(from_row-to_row) == 2 && abs(from_col-to_col) == 2))
     return false;
  else if(abs(from_row-to_row) == 1 && abs(from_col-to_col) == 1)
  {
    if(!check_single_move(input, size, count, board))
      return false;
  }
  else if(abs(from_row-to_row) == 2 && abs(from_col-to_col) == 2)
  {
    if(!check_single_jump(input, size, count, board))
      return false;
  }
  return true;
}

/******************************************************************************
** Function: Check Single Move
** Description: checks if the coordinates are valid for a single move.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: board is intialized and the same size as size.
** Post-Conditions: None.
******************************************************************************/
bool check_single_move(char* input, int size, int count, int** board)
{
  int from_row = 0, from_col = 0, to_row = 0, to_col = 0;
  get_coords(input, 0, size, from_row, from_col, to_row, to_col);
  if(board[to_row][to_col] != 0)
    return false;
  if(count == 0 && (board[from_row][from_col] != 1 && board[from_row][from_col] != 2))
    return false;
  if(count == 1 && (board[from_row][from_col] != 3 && board[from_row][from_col] != 4))
    return false;
  if(count == 0 && board[from_row][from_col] == 1 && from_row > to_row)
    return false;
  if(count == 1 && board[from_row][from_col] == 3 && from_row < to_row)
    return false;
  return true;
}

/******************************************************************************
** Function: Check Single Move
** Description: checks if the coordinates are valid for a single move.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: board is intialized and the same size as size.
** Post-Conditions: None.
******************************************************************************/
bool check_single_jump(char* input, int size, int count, int** board)
{
  int from_row = 0, from_col = 0, to_row = 0, to_col = 0;
  get_coords(input, 0, size, from_row, from_col, to_row, to_col);
  if(board[to_row][to_col] != 0)
    return false;
  if(count == 0 && (board[from_row][from_col] != 1 && board[from_row][from_col] != 2))
    return false;
  if(count == 1 && (board[from_row][from_col] != 3 && board[from_row][from_col] != 4))
    return false;
  if(count == 0 && board[from_row][from_col] == 1 && from_row > to_row)
    return false;
  if(count == 1 && board[from_row][from_col] == 3 && from_row < to_row)
    return false;
  if(count == 0 && board[(from_row+to_row)/2][(from_col+to_col)/2] != 3 && 
                   board[(from_row+to_row)/2][(from_col+to_col)/2] != 4)
    return false;
  if(count == 1 && board[(from_row+to_row)/2][(from_col+to_col)/2] != 1 && 
                   board[(from_row+to_row)/2][(from_col+to_col)/2] != 2)
    return false;
  return true;
}

/******************************************************************************
** Function: Check Double
** Description: checks if the coordinates are valid for a double jump and up.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: board is intialized and the same size as size.
** Post-Conditions: None.
******************************************************************************/
bool check_double(char* input, int size, int count, int** board)
{
  int start_row = 0, start_col = 0, to_row = 0, to_col = 0, i = 0;
  get_coords(input, 0, size, start_row, start_col, to_row, to_col);
  if(!(abs(start_row-to_row) == 2 && abs(start_col-to_col) == 2))
    return false;
  if(!check_single_jump(input, size, count, board))
    return false;
  for(i; i < strlen(input); i++)
  {
    if(input[i] == ' ')
      break;
  }
  i++;
  while(strlen(input) - i > 3)
  {
    if(!check_jump(input, size, count, board, start_row, start_col, i))
      return false;
    for(i; i < strlen(input); i++)
    {
      if(input[i] == ' ')
        break;
    }
    i++;
  }
  return true;
}

/******************************************************************************
** Function: Check Double Jump
** Description: checks if the coordinates are valid for a double jump.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: board is intialized and the same size as size.
** Post-Conditions: None.
******************************************************************************/
bool check_jump(char* input, int size, int count, int** board, int row, int col, int i)
{
  int from_row = 0, from_col = 0, to_row = 0, to_col = 0;
  get_coords(input, i, size, from_row, from_col, to_row, to_col);
  if(board[to_row][to_col] != 0)
    return false;
  if(count == 0 && (board[row][col] != 1 && board[row][col] != 2))
    return false;
  if(count == 1 && (board[row][col] != 3 && board[row][col] != 4))
    return false;
  if(count == 0 && board[row][col] == 1 && from_row > to_row)
    return false;
  if(count == 1 && board[row][col] == 3 && from_row < to_row)
    return false;
  if(count == 0 && board[(from_row+to_row)/2][(from_col+to_col)/2] != 3 && 
                   board[(from_row+to_row)/2][(from_col+to_col)/2] != 4)
    return false;
  if(count == 1 && board[(from_row+to_row)/2][(from_col+to_col)/2] != 1 && 
                   board[(from_row+to_row)/2][(from_col+to_col)/2] != 2)
    return false;
  return true;
}

/******************************************************************************
** Function: Check Input 8
** Description: checks if the input is a valid move with a size 8 board.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
bool check_input_8(char* input, int size, int count, int** board)
{
  if(strlen(input) < 5 || (strlen(input) - 5) % 3 != 0)
    return false;
  for(int i = 0; i < strlen(input); i++)
  {
    if(i % 3 == 0 && (input[i] < 'A' || input[i] > 'H'))
      return false;
    if(i % 3 == 1 && (input[i] < '1' || input[i] > '8'))
      return false;
    if(i % 3 == 3 && input[i] != ' ')
      return false;
  }
  return true;
}

/******************************************************************************
** Function: Check Input 10
** Description: checks if the input is a valid move with a size 10 board.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
bool check_input_10(char* input, int size, int count, int** board)
{
  if(strlen(input) < 5)
    return false;
  int i = 0;
  while(i < strlen(input))
  {
      if(input[i] < 'A' || input[i] > 'J')
        return false;
      if(input[i+1] < '1' || input[i+1] > '9')
        return false;
      if(i+2 < strlen(input) && input[i+2] != ' ')
        if(input[i+2] != '0')
          return false;
        else if(input[i+2] == '0' && input[i+1] != '1')
          return false;
      for(i; i < strlen(input); i++)
      {
        if(input[i] == ' ')
          break;
      }
      i++;
  }
  return true;
}

/******************************************************************************
** Function: Check Input 12
** Description: checks if the input is a valid move with a size 12 board.
** Parameters: char* input: the input to check.
**  int size: the size of the baord.
**  int count: the player whose turn it is.
**  int** board: the board to check throuh.
** Pre-Conditions: None.
** Post-Conditions: None.
******************************************************************************/
bool check_input_12(char* input, int size, int count, int** board)
{
  if(strlen(input) < 5)
    return false;
  int i = 0;
  while(i < strlen(input))
  {
      if(input[i] < 'A' || input[i] > 'L')
        return false;
      if(input[i+1] < '1' || input[i+1] > '9')
        return false;
      if(i+2 < strlen(input) && input[i+2] != ' ')
        if(input[i+2] != '0' && input[i+2] != '1' && input[i+2] != '2')
          return false;
        else if((input[i+2] == '0'|| input[i+2] == '1' || input[i+2] == '2') &&
                 input[i+1] != '1')
          return false;
      for(i; i < strlen(input); i++)
      {
        if(input[i] == ' ')
          break;
      }
      i++;
  }
  return true;
}

/******************************************************************************
** Function: Get Input
** Description: Gets the input from the user for a move.
** Parameters: None.
** Pre-Conditions: None.
** Post-Conditions: input is filled with user inputed string.
******************************************************************************/
char* get_input()
{
  char* input = new char;
  *input = '\0';
  cout << "Enter the coordinates of the move you want to do." << endl;
  cout << "Enter the coordinates as a letter for the column" << endl;
  cout << "followed by a number for the row. Each coordinate" << endl;
  cout << "should be seperated by spaces." << endl;
  while(cin.peek() != '\n')
  {
    add_char(&input, cin.get());
  }
  cin.ignore();
  cin.clear();
  return input;
}

/******************************************************************************
** Function: Add Character.
** Description: Adds the next charcter inputed by the user to the string.
** Parameters: char** input: the string to add to.
**  char charcter: the character to add.
** Pre-Conditions: None.
** Post-Conditions: charcter is appended to input.
******************************************************************************/
void add_char(char** input, char character)
{
  char* temp = new char[strlen(*input) + 2];
  for(int i = 0; i < strlen(*input); i++)
  {
    temp[i] = (*input)[i];
  }
  temp[strlen(*input)] = character;
  temp[strlen(*input) + 1] = '\0';
  delete[] *input;
  *input = new char[strlen(temp) + 1];
  strcpy(*input, temp);
  delete[] temp;
}

/******************************************************************************
** Function: Move Possible
** Description: Checks if the move is possible for a red piece.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
**  int row: the index of the row on the board.
**  int col: the index of the column on the board.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool move_possible_red(int count, int** board, int size, int row, int col)
{
  if(board[row][col] != 1)
    return false;
  if(row == size - 1)
    return false;
  else if(col == 0)
  {
    if(board[row+1][col+1] == 0)
      return true;
  }
  else if(col == size - 1)
  {
    if(board[row+1][col-1] == 0)
      return true;
  }
  else if(board[row+1][col+1] == 0 || board[row+1][col-1] == 0)
    return true;
  return false;
}

/******************************************************************************
** Function: Move Possible
** Description: Checks if the move is possible for a red pice with a jump.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
**  int row: the index of the row on the board.
**  int col: the index of the column on the board.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool move_possible_red_jump(int count, int** board, int size, int row, int col)
{
  if(board[row][col] != 1)
    return false;
  if(row >= size - 2)
    return false;
  else if(col <= 1)
  {
    if((board[row+1][col+1] == 3 || board[row+1][col+1] == 4) &&
        board[row+2][col+2] == 0)
      return true;
  }
  else if(col >= size - 2)
  {
    if((board[row+1][col-1] == 3 || board[row+1][col-1] == 4) &&
        board[row+2][col-2] == 0)
      return true;
  }
  else if(((board[row+1][col+1] == 3 || board[row+1][col+1] == 4) &&
            board[row+2][col+2] == 0) ||
          ((board[row+1][col-1] == 3 || board[row+1][col-1] == 4) &&
            board[row+2][col-2] == 0))
    return true;
  return false;
}

/******************************************************************************
** Function: Move Possible Black
** Description: Checks if the move is possible for a black piece.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
**  int row: the index of the row on the board.
**  int col: the index of the column on the board.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool move_possible_black(int count, int** board, int size, int row, int col)
{
  if(board[row][col] != 3)
    return false;
  if(row == size - 1)
    return false;
  else if(col == 0)
  {
    if(board[row-1][col+1] == 0)
      return true;
  }
  else if(col == size - 1)
  {
    if(board[row-1][col-1] == 0)
      return true;
  }
  else if(board[row-1][col+1] == 0 || board[row-1][col-1] == 0)
    return true;
  return false;
}

/******************************************************************************
** Function: Move Possible Black Jump
** Description: Checks if the move is possible for a black piece with a jump.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
**  int row: the index of the row on the board.
**  int col: the index of the column on the board.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool move_possible_black_jump(int count, int** board, int size, int row, int col)
{
  if(board[row][col] != 3)
    return false;
  if(row <= 1)
    return false;
  else if(col <= 1)
  {
    if((board[row-1][col+1] == 1|| board[row-1][col+1] == 2) &&
        board[row-2][col+2] == 0)
      return true;
  }
  else if(col >= size - 2)
  {
    if((board[row-1][col-1] == 1 || board[row-1][col-1] == 2) &&
        board[row-2][col-2] == 0)
      return true;
  }
  else if(((board[row-1][col+1] == 3 || board[row-1][col+1] == 4) &&
            board[row-2][col+2] == 0) ||
          ((board[row-1][col-1] == 3 || board[row-1][col-1] == 4) &&
            board[row-2][col-2] == 0))
    return true;
  return false;
}

/******************************************************************************
** Function: Move Possible King Red
** Description: Checks if the move is possible for a red king.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
**  int row: the index of the row on the board.
**  int col: the index of the column on the board.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool move_possible_red_king(int count, int** board, int size, int row, int col)
{
  if(board[row][col] != 2)
    return false;
  if((row != 0 && col != 0 && board[row-1][col-1] == 0) ||
     (row != 0 && col != size - 1 && board[row-1][col+1] == 0) ||
     (row != size - 1 && col != 0 && board[row+1][col-1] == 0) ||
     (row != size - 1 && col != size - 1 && board[row+1][col+1] == 0))
      return true;
  return false;
}

/******************************************************************************
** Function: Move Possible King Black
** Description: Checks if the move is possible for a black king.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
**  int row: the index of the row on the board.
**  int col: the index of the column on the board.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool move_possible_black_king(int count, int** board, int size, int row, int col)
{
  if(board[row][col] != 4)
    return false;
  if((row != 0 && col != 0 && board[row-1][col-1] == 0) ||
     (row != 0 && col != size - 1 && board[row-1][col+1] == 0) ||
     (row != size - 1 && col != 0 && board[row+1][col-1] == 0) ||
     (row != size - 1 && col != size - 1 && board[row+1][col+1] == 0))
      return true;
  return false;
}

/******************************************************************************
** Function: Move Possible King Red Jump
** Description: Checks if the move is possible for a red king with jumps.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
**  int row: the index of the row on the board.
**  int col: the index of the column on the board.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool move_possible_red_king_jump(int count, int** board, int size, int row, int col)
{
  if(board[row][col] != 2)
    return false;
  if((row > 1 && col > 1 && board[row-2][col-2] == 0
              && (board[row-1][col-1] == 3 || board[row-1][col-1] == 4)) ||
     (row > 1 && col < size - 2 && board[row-2][col+2] == 0
              && (board[row-1][col+1] == 3 || board[row-1][col+1] == 4)) ||
     (row < size - 2 && col > 1 && board[row+2][col-2] == 0
              && (board[row+1][col-1] == 3 || board[row+1][col-1] == 4)) ||
     (row < size - 2 && col < size - 2 && board[row+2][col+2] == 0
              && (board[row+1][col+1] == 3 || board[row+1][col+1] == 4)))
      return true;
  return false;
}

/******************************************************************************
** Function: Move Possible King Black Jump
** Description: Checks if the move is possible for a black king with jumps.
** Parameters: int size: the length of the board.
**  int** board: the game board array.
**  int count: the Player that won.
**  int row: the index of the row on the board.
**  int col: the index of the column on the board.
** Pre-Conditions: Size and is a valid size and board is intialized.
** Post-Conditions: None.
******************************************************************************/
bool move_possible_black_king_jump(int count, int** board, int size, int row, int col)
{
  if(board[row][col] != 2)
    return false;
  if((row > 1 && col > 1 && board[row-2][col-2] == 0
              && (board[row-1][col-1] == 3 || board[row-1][col-1] == 4)) ||
     (row > 1 && col < size - 2 && board[row-2][col+2] == 0
              && (board[row-1][col+1] == 3 || board[row-1][col+1] == 4)) ||
     (row < size - 2 && col > 1 && board[row+2][col-2] == 0
              && (board[row+1][col-1] == 3 || board[row+1][col-1] == 4)) ||
     (row < size - 2 && col < size - 2 && board[row+2][col+2] == 0
              && (board[row+1][col+1] == 3 || board[row+1][col+1] == 4)))
      return true;
  return false;
}

/******************************************************************************
** Function: Main
** Description: The main function of the program. Checks command line
**   arguments and starts game.
** Parameters: int argc: the number of command line arguments.
**   char** argv: the actual array of command line arguments.
** Pre-Conditions: None
** Post-Conditions: The game is started.
******************************************************************************/
int main(int argc, char** argv)
{
  int size = check_args(argc, argv);
  start_game(size);

  return 0;
}
