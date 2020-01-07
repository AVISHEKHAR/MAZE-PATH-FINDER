#include <stdio.h>
void print_maze(char[][8]);                                                       /*It will print the given maze*/
void check_movement(int *, int *, int, int, int, int, char[][8]);                 /*When it encounters block then this function is called and give new correct direction.*/
int search(char[][8], char[][8], char[][8], int, int, int, int, int, int, int *); /*When we have to search for path from given source to destination then this function is being callled*/
void find_path(char[][8], char[][8], int, int);                                   /*This will print path from source to destination in a 8X8 matrix.*/
/*Here Few symbols represent following meaning
  drow=Destination row.
  dcolumn=Destination column.
  srow=source row.
  scolumn=source column.
  prow=previous row.
  pcolumn=previous column.
*/
void main()
{
    int row, column, flag = 0, srow, scolumn, drow, dcolumn;
    char maze[8][8] = {{' ', ' ', 'X', 'X', ' ', ' ', 'X', ' '}, //This is required maze in which we have to find path from source to destination.
                       {' ', ' ', ' ', 'X', 'X', ' ', ' ', ' '},
                       {' ', ' ', ' ', 'X', ' ', ' ', 'X', ' '},
                       {' ', ' ', 'X', ' ', ' ', ' ', 'X', ' '},
                       {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                       {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                       {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                       {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}},
         maze_cpy[8][8], maze_path[8][8];
    for (row = 0; row < 8; row++) //Here we are copying maze to another 8X8 maze.
    {
        for (column = 0; column < 8; column++)
        {
            maze_cpy[row][column] = maze[row][column];
            maze_path[row][column] = 'X'; //Here maze_path is matrix which will trace the path from source to destination.
        }
    }
    printf("Enter the source value of row and column>"); //Taking source and destination location  as input.
    scanf("%d %d", &srow, &scolumn);
    printf("Enter the destination value of row and column>");
    scanf("%d %d", &drow, &dcolumn);                    //Final destination is marked as D.
    maze[drow][dcolumn] = 'D';
    maze_cpy[drow][dcolumn] = 'D';
    search(maze, maze_cpy, maze_path, srow, scolumn, drow, dcolumn, 0, 0, &flag);  //Calling search method for finding destination location.
    if (flag != 1)  
    {                         
                                //It will tell whether search function able to reach to destination location from source or not.
        printf("not reached");
    }
    else
    {
                                //It will tell whether search function able to reach to destination location from source or not.  
        printf("Reached the destination row=%d  column=%d\n", drow, dcolumn);
        find_path(maze_path, maze, drow, dcolumn); //This will find path from source to destination
        print_maze(maze_path);                     //printing path from source to destination.
    }
}
int search(char maze[][8], char maze_cpy[][8], char path_cpy[][8], int row, int column, int drow, int dcolumn, int prow, int pcolumn, int *flag)
{
    int temprow, tempcolumn;
    if (maze[row][column] == 'D') //checking whether current location is same as destination location.
    {                             //If it is then it will return 1.
        *flag = 1;
        return 1;
    }
    else if (maze[row][column] == 'X' || maze_cpy[row][column] == 'C') //It  will check whether current position is block or come before or not.
    {
        maze_cpy[prow][pcolumn] = 'C'; //If it is block then position before current position is marked as C so again it will not encounter it.
        return -1;
    }
    else if (row > 7 || column > 7 || row < 0 || column < 0) //Current position is valid or not.
    {
        return -1;
    }
    else
    { //In this block we given direction so we will able to get to final destination.
        if (row < drow)
        {
            temprow = row + 1;
            tempcolumn = column;
        }
        else if (row == drow && column < drow)
        {
            tempcolumn = column + 1;
            temprow = row;
        }
        else if (row == drow && column > dcolumn)
        {
            tempcolumn = column - 1;
            temprow = row;
        }
        path_cpy[row][column] = ' ';
        if (search(maze, maze_cpy, path_cpy, temprow, tempcolumn, drow, dcolumn, row, column, flag) == 1) //using recursion technique to find destination location.
            return 1;
        else
        { //Here we are correcting  current position.
            temprow = row;
            tempcolumn = column;
            check_movement(&row, &column, prow, pcolumn, drow, dcolumn, maze_cpy);
            path_cpy[row][column] = 'X';
            search(maze, maze_cpy, path_cpy, row, column, drow, dcolumn, temprow, tempcolumn,flag);
        }
    }
}
void print_maze(char maze[][8])
{ //Printing the given matrix
    int row, column;
    for (row = 0; row < 8; row++)
    {
        for (column = 0; column < 8; column++)
        {
            printf("%c ", maze[row][column]);
        }

        printf("\n");
    }
}
void check_movement(int *temprow, int *tempcolumn, int row, int column, int drow, int dcolumn, char maze[][8])
{ /*
        Correcting current location.Directng it to different alternative path.
    */
    if (*temprow < drow && maze[*temprow + 1][*tempcolumn] != 'X' && maze[*temprow + 1][*tempcolumn] != 'C' && *temprow + 1 < 8)
    {
        ++*temprow;
    }
    else if (*tempcolumn < dcolumn && maze[*temprow][*tempcolumn + 1] != 'X' && maze[*temprow][*tempcolumn + 1] != 'C' && *tempcolumn + 1 < 8)
    {
        ++*tempcolumn;
    }
    else
    {
        *temprow = row;
        *tempcolumn = column;
    }
}
void find_path(char path[][8], char maze[][8], int drow, int dcolumn)
{
    int row = 0, column = 0;
    int flag = 0;
    for (column = 0; column < dcolumn; column++) //Checking whether current position is block or not.
    {
        if (maze[drow][column] == 'X')
        {
            flag = 1;
        }
    }
    if (flag == 1)
    { //Making all 1's in path matrix to 0's.
        for (column = 0; column < dcolumn; column++)
        {
            if (path[drow][column] == 'X')
                path[drow][column] == ' ';
        }
    }        
    path[drow][dcolumn] = ' ';
}
