// Ghazanfar Ghaffar 22i-2079 pf sec b final project
// Game of life

// including libraries
#include <iostream> //for input/output
#include <unistd.h> // Include for usleep function
#include <cstdlib>  // Include for system function
#include <fstream>  // Include for ifstream and ofstream
#include <string>   // Include for string
using namespace std;

// Declaring functions' prototypes
void printGrid(bool **grid, int SIZE);
void gameOfLife(bool **grid, int *SIZE, int numberOfGenerations);
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
    int *SIZE = new int;
    *SIZE = 20;
    bool **grid = new bool *[*SIZE]; // the main grid
    for (int i = 0; i < *SIZE; i++)
        grid[i] = new bool[*SIZE];

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
        printGrid(grid, *SIZE);

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
            writeFile(grid, *SIZE, fileName);
            cout << "Your layout has been saved in a file named '" << fileName << "'" << endl;
        }

        cout << "Press ENTER to continue.";
        cin.ignore();
        cin.get();
        system("clear"); // clears the screen
    }
    //===================if user wants to select from one of the templates===================
    else
    {
        cout << "Following are some of the templates." << endl;

        // Glider
        cout << "\n1. Glider" << endl;
        readFile(grid, *SIZE, "glider.txt"); // read template from file
        printGrid(grid, *SIZE);              // print the freshly read template

        // Cross
        cout << "\n2. Cross" << endl;
        readFile(grid, *SIZE, "cross.txt");
        printGrid(grid, *SIZE);

        // Grenade
        cout << "\n3. Grenade" << endl;
        readFile(grid, *SIZE, "grenade.txt");
        printGrid(grid, *SIZE);

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
            readFile(grid, *SIZE, "glider.txt");
            cout << "\nGlider has been selected.\n";
        }
        // user selected cross
        else if (choice == '2')
        {
            readFile(grid, *SIZE, "cross.txt");
            cout << "\nCross has been selected.\n";
        }
        // user selected grenade
        else
        {
            readFile(grid, *SIZE, "grenade.txt");
            cout << "\nGrenade has been selected.\n";
        }
    }

    cout << "Press ENTER to continue.";
    cin.ignore();
    cin.get();
    system("clear"); // clears the screen

    // All the information has been collected. the real game starts now
    gameOfLife(grid, SIZE, numberOfGenerations);
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
void gameOfLife(bool **grid, int *SIZE, int numberOfGenerations)
{
    for (int i = 0; i < numberOfGenerations; i++)
    {
        printGrid(grid, *SIZE);
    }
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
}

/*===================================THE END===================================*/
