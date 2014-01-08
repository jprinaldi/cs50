/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// empty tile
#define EMPTY 0

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// position of a tile
typedef struct position {
    int i;
    int j;
} position;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

void swap(position pos1, position pos2);
void swapTiles(int tile1, int tile2);
position getTilePosition(int tile);
bool areAdjacent(position pos1, position pos2);
int getCorrectTile(int i, int j);
int getReverseTile(int i, int j);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
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
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            board[i][j] = getReverseTile(i, j);

    if (d % 2 == 0)
        swapTiles(1, 2);
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    int n;

    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            n = board[i][j];
            if (n == EMPTY)
                printf(" _ ");
            else if (n < 10)
                printf(" %d ", n);
            else
                printf("%d ", n);
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    position pos_tile = getTilePosition(tile);
    position pos_empty = getTilePosition(EMPTY);

    if (areAdjacent(pos_tile, pos_empty)) {
        swap(pos_tile, pos_empty);
        return true;
    } else
        return false;
}

void swap(position pos1, position pos2)
{
    int temp = board[pos1.i][pos1.j];
    board[pos1.i][pos1.j] = board[pos2.i][pos2.j];
    board[pos2.i][pos2.j] = temp;
}

void swapTiles(int tile1, int tile2)
{
    swap(getTilePosition(tile1), getTilePosition(tile2));
}

position getTilePosition(int tile)
{
    position pos;

    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            if (board[i][j] == tile) {
                pos.i = i;
                pos.j = j;
            }

    return pos;
}

bool areAdjacent(position pos1, position pos2)
{
    return ((abs(pos1.i - pos2.i) + abs(pos1.j - pos2.j)) == 1);
}

int getCorrectTile(int i, int j)
{
    return (d*i + j + 1) % (d*d);
}

int getReverseTile(int i, int j)
{
    return ((d*d - getCorrectTile(i, j)) % (d*d));
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            if (board[i][j] != getCorrectTile(i, j))
                return false;

    return true;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
