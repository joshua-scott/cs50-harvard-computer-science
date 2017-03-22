/*
	This is Game of Fifteen (generalized to d x d)
	Usage: fifteen d
 	whereby the board's dimensions are to be d x d,
 	where d must be in [DIM_MIN,DIM_MAX]
	Written by Joshua Scott for Harvard's CS50 course
	http://online-learning.harvard.edu/course/cs50-introduction-computer-science
	
	GitHub: https://github.com/jscott313
	Email: jscott313@gmail.com
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d, iBlank, jBlank;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions and set blank tile
    d = atoi(argv[1]);
    iBlank = d-1;
    jBlank = iBlank;
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
        return 3;

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                    fprintf(file, "|");
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
            break;

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int k = d*d-1;
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            board[i][j] = k;
            k--;
        }
    }
    if(d % 2 == 0)  //swap 1 and 2 if d is even
    {
        int temp = board[d-1][d-3];
        board[d-1][d-3] = board[d-1][d-2];
        board[d-1][d-2] = temp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == 0)
                printf(" _ ");
            else
                printf("%2d ", board[i][j]);
        }
        printf("\n");
    }    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                //if it's next to the blank tile, swap them
                if ((i == iBlank && (j == jBlank + 1 || j == jBlank - 1)) || (j == jBlank && (i == iBlank + 1 || i == iBlank - 1)))
                {
                    board[iBlank][jBlank] = tile;
                    board[i][j] = 0;
                    iBlank = i;
                    jBlank = j;
                    return true;   
                }
                else
                    return false;
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    if (board[d-1][d-1] != 0)
        return false;

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if( (board[i][j] != (i*d+j+1)) && (board[i][j] != 0) )
                return false;
        }
    }
    return true;
}
