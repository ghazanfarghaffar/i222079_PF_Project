// Ghazanfar Ghaffar 22i-2079 pf sec b final project
//=========================================================================================================
//
//   ####      ###    ###    ###  #####         #####   #####        ##      ##  #####  #####        ##
//  ##        ## ##   ## #  # ##  ##           ##   ##  ##           ##      ##  ##     ##           ##
//  ##  ###  ##   ##  ##  ##  ##  #####        ##   ##  #####        ##      ##  #####  #####        ##
//  ##   ##  #######  ##      ##  ##           ##   ##  ##           ##      ##  ##     ##
//   ####    ##   ##  ##      ##  #####         #####   ##           ######  ##  ##     #####        ##
//
//=========================================================================================================

// including libraries
#include <iostream> //for input/output
#include <unistd.h> // Include for usleep function
#include <cstdlib>  // Include for system function
#include <fstream>  // Include for ifstream and ofstream
#include <string>   // Include for string
using namespace std;

// Declaring functions' prototypes
void printGrid(bool **grid, int SIZE);
void display(int **neighbourCells, int **liveCells);
bool isNeighbour(int **neighbourCells, int x, int y);
bool isAlive(int **liveCells, int x, int y);
int countAliveCells(bool **grid, int x, int y, int **neighbourCells, int **liveCells);
void applyRules(bool **grid, int SIZE, int **neighbourCells, int **liveCells);
void populateNeighbours(int SIZE, int x, int y, int **neighbourCells, int *neighbourCellLast, int **liveCells);
void dynamicGrowth(bool **&grid, int &SIZE);
int populateLiveCells(bool **grid, int SIZE, int **liveCells);
void gameOfLife(bool **grid, int &SIZE, int numberOfGenerations, bool displayArray);
void writeFile(bool **grid, int SIZE, string fileName);
void readFile(bool **grid, int SIZE, string fileName);
void Info();
void welcome();

/*==================================================================*/
/*It is the so called MAIN function that is of no use here but hehe.*/
int main()
{
    welcome();
    return EXIT_SUCCESS;
}

/*==============================================================================*/
/*Prints a welcome message for the Game of Life program and starts the game.*/
void welcome()
{
    cout << "==================================" << endl;
    cout << "|          GAME OF LIFE          |" << endl;
    cout << "|     By : Ghazanfar Ghaffar     |" << endl;
    cout << "|        22i-2079 PF SEC B       |" << endl;
    cout << "==================================" << endl;
    cout << endl;

    cout << "Do you want to start the game? (Y/N): ";
    char choice; // variable for user's choice
    cin >> choice;
    // input validation
    while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
    {
        cout << "Invalid choice. Please try again." << endl;
        cout << "Do you want to start the game? (Y/N): ";
        cin >> choice;
    }
    system("clear"); // clears the screen
    if (choice == 'y' || choice == 'Y')
    {
        cout << "Starting the game .";
        usleep(1000000);

        cout << " ." << flush;
        usleep(1000000);

        cout << " ." << flush;
        usleep(1000000);

        cout << " ." << endl;
        usleep(1000000);
        cout << endl;

        system("clear"); // clears the screen
        Info();          // start the game
    }
    else
    {
        cout << "Exiting the game .";
        usleep(1000000);

        cout << " .";
        usleep(1000000);

        cout << " .";
        usleep(1000000);

        cout << " .";
        usleep(1000000);
        cout << endl;
        return;
    }

    cout << "Press ENTER to continue.";
    cin.ignore();
    cin.get();
    system("clear"); // clears the screen
    cout << "==================================" << endl;
    cout << "|      Thanks for playing :)     |" << endl;
    cout << "==================================" << endl;
}

/*========================================================================================*/
/*Collects all the necessary information from user for the game and call further functions*/
void Info()
{
    // ===============================Declaring variables===============================
    int SIZE = 20;
    bool **grid = new bool *[SIZE]; // the main grid
    for (int i = 0; i < SIZE; i++)
        grid[i] = new bool[SIZE];

    int numberOfGenerations(0);
    cout << "Enter the following information:" << endl;
    cout << "Enter the number of generations you want to simulate: ";
    cin >> numberOfGenerations;
    while (numberOfGenerations < 1) // input validation
    {
        cout << "Invalid number. Please try again." << endl;
        cout << "Enter the number of generations you want to simulate: ";
        cin >> numberOfGenerations;
    }

    // Inputting user's choice
    cout << "Do you want to write out the alive cells or do you want to select from one of the templates?\n(Type 'W' or 'T' respectively): ";
    char choice; // variable for user's choice
    cin >> choice;
    while (choice != 'W' && choice != 'w' && choice != 'T' && choice != 't') // input validation
    {
        cout << "Invalid choice. Please try again.\n(Type 'W' or 'T' respectively):" << endl;
        cin >> choice;
    }
    cout << endl;

    //===============================if user wants to write out===============================
    if (choice == 'W' || choice == 'w')
    {
        int numberOfCells(0);
        cout << "Enter the number of cells alive: ";
        cin >> numberOfCells;
        while (numberOfCells < 0 || numberOfCells > 400) // input validation
        {
            cout << "Invalid number. Please try again." << endl;
            cout << "Enter the number of cells alive: ";
            cin >> numberOfCells;
        }

        for (int i = 0; i < numberOfCells; i++)
        {
            int x, y;
            cout << "Enter the coordinates of the cell(1-20) :)\n";
            cout << "x: ";
            cin >> x;
            while (x < 1 || x > 20) // input validation
            {
                cout << "Invalid number. Please try again." << endl;
                cout << "x: ";
                cin >> x;
            }
            cout << "y: ";
            cin >> y;
            while (y < 1 || y > 20) // input validation
            {
                cout << "Invalid number. Please try again." << endl;
                cout << "y: ";
                cin >> y;
            }
            // setting the cell to alive
            grid[x - 1][y - 1] = true;
        }

        // printing the grid so user see what they added
        cout << "\n\nFollowing is your layout of alive cells: " << endl;
        printGrid(grid, SIZE);

        // Saving the layout in a file
        cout << "\n\nDo you want to save this layout for future use? (Y/N): ";
        char save;
        cin >> save;
        while (save != 'Y' && save != 'y' && save != 'N' && save != 'n')
        {
            cout << "Invalid choice. Please try again. (Y/N): ";
            cin >> save;
        }
        if (save == 'Y' || save == 'y')
        {
            string fileName = "";
            cout << "Enter the name of the file(add \".txt\" at the end): ";
            cin >> fileName;
            writeFile(grid, SIZE, fileName);
            cout << "Your layout has been saved in a file named '" << fileName << "'" << endl;
        }

        cout << "Press ENTER to continue.";
        cin.get();
        system("clear"); // clears the screen
    }

    //===================if user wants to select from one of the templates===================
    else
    {
        cout << "Following are some of the templates." << endl;

        // Glider
        cout << "\n1. Glider" << endl;
        readFile(grid, SIZE, "glider.txt"); // read template from file
        printGrid(grid, SIZE);              // print the freshly read template

        // Cross
        cout << "\n2. Cross" << endl;
        readFile(grid, SIZE, "cross.txt");
        printGrid(grid, SIZE);

        // Grenade
        cout << "\n3. Grenade" << endl;
        readFile(grid, SIZE, "grenade.txt");
        printGrid(grid, SIZE);

        // Inputting user's choice
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        while (choice < '1' || choice > '3') // input validation
        {
            cout << "Invalid choice. Please try again." << endl;
            cout << "Enter your choice: ";
            cin >> choice;
        }

        // user selected glider
        if (choice == '1')
        {
            readFile(grid, SIZE, "glider.txt");
            cout << "\nGlider has been selected.\n";
        }
        // user selected cross
        else if (choice == '2')
        {
            readFile(grid, SIZE, "cross.txt");
            cout << "\nCross has been selected.\n";
        }
        // user selected grenade
        else
        {
            readFile(grid, SIZE, "grenade.txt");
            cout << "\nGrenade has been selected.\n";
        }
    }

    // ask user if they want to print the alive cells and their neighbours with every generation
    bool displayArrays = false;
    cout << "\nDo you want to print the alive cells and their neighbours with every generation? (Y/N): ";
    char print;
    cin >> print;
    while (print != 'Y' && print != 'y' && print != 'N' && print != 'n')
    {
        cout << "Invalid choice. Please try again. (Y/N): ";
        cin >> print;
    }
    if (print == 'Y' || print == 'y')
        displayArrays = true;

    // clear the screen
    cin.ignore();
    cin.get();
    system("clear");

    // All the information has been collected. the real game starts now
    gameOfLife(grid, SIZE, numberOfGenerations, displayArrays);

    cout << "\nGame Over. Thanks for playing.\n"
         << endl;

    // freeing dynamicly allocated memory
    for (int i = 0; i < SIZE; i++)
        delete[] grid[i];
    delete[] grid;
}

/*===============================================*/
/*Reads the Game Grid from a text file in system*/
void readFile(bool **grid, int SIZE, string fileName)
{
    ifstream myTemplate(fileName);
    string line;
    int count = 0;
    while (getline(myTemplate, line))
    {
        if (count == 20)
            break;
        for (int i = 0; i < 20; i++)
        {
            if (line[i] == '1')
                grid[count][i] = true;
            else
                grid[count][i] = false;
        }
        count++;
    }
    myTemplate.close();
}

/*===============================================*/
/*Writes the Game Grid into a text file in system*/
void writeFile(bool **grid, int SIZE, string fileName)
{
    ofstream myTemplate(fileName);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j] == true)
                myTemplate << "1";
            else
                myTemplate << "0";
        }
        myTemplate << "\n";
    }
    myTemplate.close();
}

/*=====================================================*/
/*Runs the main game after the information is collected*/
void gameOfLife(bool **grid, int &SIZE, int numberOfGenerations, bool displayArray)
{
    // the array to store cordinates of live cells and their neighbours

    // Declaring 2D array for storing live cells
    int *aliveCellsSize = new int;
    *aliveCellsSize = 50;

    int **liveCells = new int *[*aliveCellsSize];
    for (int i = 0; i < *aliveCellsSize; i++)
        liveCells[i] = new int[2];

    // declaring 2D array for storing their neighbours
    int *neighbourCellsSize = new int;
    *neighbourCellsSize = 50;

    int **neighbourCells = new int *[*neighbourCellsSize];
    for (int i = 0; i < *neighbourCellsSize; i++)
        neighbourCells[i] = new int[2];

    // ==============================Loop through the generations==============================
    for (int i = 1; i <= numberOfGenerations; i++)
    {
        cout << "Generation: " << i << endl;
        // reseting/populating the arrays with -1
        for (int i = 0; i < *aliveCellsSize; i++)
        {
            liveCells[i][0] = -1;
            liveCells[i][1] = -1;
        }
        for (int i = 0; i < *neighbourCellsSize; i++)
        {
            neighbourCells[i][0] = -1;
            neighbourCells[i][1] = -1;
        }

        // populating the alive cell array
        int liveCellsLast = populateLiveCells(grid, SIZE, liveCells);

        // populating the neighbour cell array
        int *neighbourCellsLast = new int;
        *neighbourCellsLast = 0;
        for (int i = 0; i < liveCellsLast; i++)
            populateNeighbours(SIZE, liveCells[i][0], liveCells[i][1], neighbourCells, neighbourCellsLast, liveCells);

        // print game grid
        printGrid(grid, SIZE);

        // Dynamic growth of game grid
        for (int i = 0; i < SIZE; i++)
        {
            if (grid[0][i] || grid[i][0] || grid[SIZE - 1][i] || grid[i][SIZE - 1]) // If the cell is touching the boundary
            {
                dynamicGrowth(grid, SIZE);
                break;
            }
        }
        // displaying the arrays
        if (displayArray)
            display(neighbourCells, liveCells);

        // applying the rules
        applyRules(grid, SIZE, neighbourCells, liveCells);

        cout << "\nPress ENTER for next generation :) ";
        cin.get();
        system("clear"); // clears the screen

        // freeing up the memory
        delete neighbourCellsLast;
    }

    // deleting the arrays to free the memory
    for (int i = 0; i < *aliveCellsSize; i++)
        delete[] liveCells[i];
    delete[] liveCells;

    for (int i = 0; i < *neighbourCellsSize; i++)
        delete[] neighbourCells[i];
    delete[] neighbourCells;

    delete aliveCellsSize;
}

/*===============================*/
/*Dynamic growth of the game grid*/
// Function to dynamically grow the grid
void dynamicGrowth(bool **&grid, int &SIZE)
{
    // Increase the size of the grid by 2 in each dimension
    int newSize = SIZE + 2;

    // Create a new temporary grid with the updated size and initialize to false
    bool **newGrid = new bool *[newSize];
    for (int i = 0; i < newSize; i++)
    {
        newGrid[i] = new bool[newSize]();
    }

    // Copy the values from the old grid to the new grid, leaving a border of empty cells
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            newGrid[i + 1][j + 1] = grid[i][j];
        }
    }

    // Delete the old grid
    for (int i = 0; i < SIZE; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;

    // Assign the new grid and size to the original grid and size variables
    grid = newGrid;
    SIZE = newSize;
}

/*==============================*/
/*Populates the live cells array*/
int populateLiveCells(bool **grid, int SIZE, int **liveCells)
{
    int liveCellsLast = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j] == 1) // if sell is alive, add it to the array
            {
                liveCells[liveCellsLast][0] = i;
                liveCells[liveCellsLast][1] = j;
                liveCellsLast++;
            }
        }
    }
    return liveCellsLast;
}

/*==================================*/
/*Populates the neighbour cell array*/
void populateNeighbours(int SIZE, int x, int y, int **neighbourCells, int *neighbourCellLast, int **liveCells)
{
    // iterate on a 3x3 grid centered at (x, y)
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) // checking bounds
            {
                if (neighbourCells[*neighbourCellLast][0] == -1 && neighbourCells[*neighbourCellLast][1] == -1 && !(isAlive(liveCells, i, j)) && !(isNeighbour(neighbourCells, i, j))) // checking for dead neighbours
                {
                    neighbourCells[*neighbourCellLast][0] = i;
                    neighbourCells[*neighbourCellLast][1] = j;
                    *neighbourCellLast = *neighbourCellLast + 1;
                }
            }
        }
    }
}

/*==========================================*/
/*Checks if the cell is present in the array*/
bool isAlive(int **liveCells, int x, int y)
{
    for (int i = 0; liveCells[i][0] != -1 && liveCells[i][1] != -1; i++)
    {
        if (liveCells[i][0] == x && liveCells[i][1] == y)
            return true;
    }
    return false;
}

/*==========================================*/
/*Checks if the cell is present in the array*/
bool isNeighbour(int **neighbourCells, int x, int y)
{
    for (int i = 0; neighbourCells[i][0] != -1 && neighbourCells[i][1] != -1; i++)
    {
        if (neighbourCells[i][0] == x && neighbourCells[i][1] == y)
            return true;
    }
    return false;
}

/*=============================*/
/*Applies the rules of the game*/
void applyRules(bool **grid, int SIZE, int **neighbourCells, int **liveCells)
{
    // creating a temporary grid to work with
    bool **tempGrid = new bool *[SIZE];
    for (int i = 0; i < SIZE; i++)
        tempGrid[i] = new bool[SIZE];
    // copying the main grid to new grid
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            tempGrid[i][j] = grid[i][j];

    // ================================================applying the rules================================================
    // applying the rules on live cells array
    for (int i = 0; liveCells[i][0] != -1 && liveCells[i][1] != -1; i++)
    {
        int aliveNeighbours = countAliveCells(tempGrid, liveCells[i][0], liveCells[i][1], neighbourCells, liveCells); // counting live neighbours

        if (aliveNeighbours < 2) // if less than 2 live neighbours, kill the cell
            grid[liveCells[i][0]][liveCells[i][1]] = false;
        else if (aliveNeighbours > 3) // if more than 3 live neighbours, kill the cell
            grid[liveCells[i][0]][liveCells[i][1]] = false;
        else if (aliveNeighbours == 3) // if exactly 3 live neighbours, live the cell
            grid[liveCells[i][0]][liveCells[i][1]] = true;
    }
    //  applying the rules on neighbour cells array
    for (int i = 0; neighbourCells[i][0] != -1 && neighbourCells[i][1] != -1; i++)
    {
        int aliveNeighbours = countAliveCells(tempGrid, neighbourCells[i][0], neighbourCells[i][1], neighbourCells, liveCells); // counting live neighbours

        if (aliveNeighbours < 2)
            grid[neighbourCells[i][0]][neighbourCells[i][1]] = false;
        else if (aliveNeighbours > 3)
            grid[neighbourCells[i][0]][neighbourCells[i][1]] = false;
        else if (aliveNeighbours == 3)
            grid[neighbourCells[i][0]][neighbourCells[i][1]] = true;
    }

    // deleting the temporary grid to free the memory
    for (int i = 0; i < SIZE; i++)
        delete[] tempGrid[i];
    delete[] tempGrid;

    // copying the main grid to new grid
}

/*================================*/
/*Counts the number of alive cells*/
int countAliveCells(bool **grid, int x, int y, int **neighbourCells, int **liveCells)
{
    int count = 0;

    // iterate on a 3x3 grid centered at (x, y)
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i == x && j == y)
                continue;
            if (isAlive(liveCells, i, j))
                count++;
        }
    }

    return count;
}

/*==============================================*/
/*Displays both alive cells and their neighbours*/
void display(int **neighbourCells, int **liveCells)
{
    int last(-1);
    cout << endl;
    cout << "Alive Cells: " << endl;
    for (int i = 0; liveCells[i][0] != -1; i++)
    {
        cout << "(" << liveCells[i][0] << ", " << liveCells[i][1] << ") ";
        last++;
    }
    cout << "\t\tLAST = " << last;
    last = -1;
    cout << endl;
    cout << endl;
    cout << "Neighbour Cells: " << endl;
    for (int i = 0; neighbourCells[i][0] != -1; i++)
    {
        cout << "(" << neighbourCells[i][0] << ", " << neighbourCells[i][1] << ") ";
        last++;
    }
    cout << "\t\tLAST = " << last;
    cout << endl;
    cout << endl;
}

/*==========================================================*/
/*Prints the Game Grid in a good format for every generation*/
void printGrid(bool **grid, int SIZE)
{
    // ANSI escape code for white background and black text
    const string WHITE_BG_BLACK_TEXT = "\033[47;30m";
    // ANSI escape code for black background
    const string BLACK_BG = "\033[40m";
    // ANSI escape code for gray background
    const string GRAY_BG = "\033[48;5;240m";
    // ANSI escape code to reset text color and background
    const string RESET_COLOR = "\033[0m";

    // Loop through the grid
    for (int i = 0; i < SIZE; ++i)
    {
        // Print a line of gray blocks before each line
        for (int j = 0; j < SIZE * 2 + 1; ++j)
        {
            cout << GRAY_BG << "  ";
        }
        cout << RESET_COLOR << endl;

        // Print the cells of the current line
        for (int j = 0; j < SIZE; ++j)
        {
            // Print a gray block before each cell
            cout << GRAY_BG << "  ";

            // Print a white space if the element is 0 (white)
            if (!grid[i][j])
            {
                cout << WHITE_BG_BLACK_TEXT << "  ";
            }
            // Print a black box if the element is 1 (black)
            else
            {
                cout << BLACK_BG << "  ";
            }
        }
        // Print a gray block after the last cell of the line
        cout << GRAY_BG << "  ";
        cout << RESET_COLOR << endl;
    }
    // Print a line of gray blocks after the last line
    for (int j = 0; j < SIZE * 2 + 1; ++j)
    {
        cout << GRAY_BG << "  ";
    }
    cout << RESET_COLOR << endl;

    cout << endl;
}

/*===================================THE END===================================*/
