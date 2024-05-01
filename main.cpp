// Ghazanfar Ghaffar 22i-2079 pf sec b final project
// Game of life

// including libraries
#include <iostream> //for input/output
#include <unistd.h> // Include for usleep function
#include <cstdlib>  // Include for system function
#include <fstream>  // Include for ifstream and ofstream
using namespace std;

// Declaring functions' prototypes
void printGrid(bool **grid, int SIZE);
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
    cout << "Press ENTER to continue.";
    cin.ignore();
    cin.get();
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

        cout << "Press ENTER to continue.";
        cin.ignore();
        cin.get();
        system("clear"); // clears the screen
        Info();          // start the game
    }
    else
    {
        cout << "Exiting the game ." << endl;
        usleep(1000000);

        cout << " ." << flush;
        usleep(1000000);

        cout << " ." << flush;
        usleep(1000000);

        cout << " ." << endl;
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
    // Declaring variables
    int *SIZE = new int;
    *SIZE = 20;
    bool **grid = new bool *[*SIZE]; // the main grid
    for (int i = 0; i < *SIZE; i++)
    {
        grid[i] = new bool[*SIZE];
    }

    int numberOfGenerations(0);
    int numberOfCells(0);
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
    cout << "Do you want to write out the alive cells or "
         << "do you want to select from one of the templates? "
         << "\n(Type 'W' or 'T' respectively): ";
    char choice; // variable for user's choice
    cin >> choice;
    while (choice != 'W' && choice != 'w' && choice != 'T' && choice != 't') // input validation
    {
        cout << "Invalid choice. Please try again.\n(Type 'W' or 'T' respectively):" << endl;
        cin >> choice;
    }

    if (choice == 'W' || choice == 'w') // if user wants to write out
    {
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
            cout << "Enter the coordinates of the cell(1-20) :)";
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
            grid[x + 1][y + 1] = true;
        }
    }
    else // if user wants to select from one of the templates
    {
        cout << "Following are some of the templates." << endl;

        // Glider
        cout << "\n1. Glider" << endl;
        ifstream gliderFile("glider.txt");
        string line;
        int count = 0;
        while (getline(gliderFile, line))
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
        gliderFile.close();
        printGrid(grid, *SIZE);

        // Cross
        cout << "\n2. Cross" << endl;
        ifstream crossFile("cross.txt");
        count = 0;
        while (getline(crossFile, line))
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
        crossFile.close();
        printGrid(grid, *SIZE);

        // Grenade
        cout << "\n3. Grenade" << endl;
        ifstream grenadeFile("grenade.txt");
        count = 0;
        while (getline(grenadeFile, line))
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
        grenadeFile.close();
        printGrid(grid, *SIZE);

        // Inputting user's choice
        cout << "\n\nEnter your choice: ";
        cin >> count;
        while (count < 1 || count > 3) // input validation
        {
            cout << "Invalid choice. Please try again." << endl;
            cout << "Enter your choice: ";
            cin >> count;
        }

        // user selected glider
        if (count == 1)
        {
            numberOfCells = 5;
            ifstream theTemplate("glider.txt");
            string line;
            count = 0;
            while (getline(theTemplate, line))
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
            theTemplate.close();
            cout << "\nGlider has been selected.\n";
        }
        // user selected cross
        else if (count == 2)
        {
            numberOfCells = 3;
            ifstream theTemplate("cross.txt");
            count = 0;
            while (getline(theTemplate, line))
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
            theTemplate.close();
            cout << "\nCross has been selected.\n";
        }
        // user selected grenade
        else
        {
            numberOfCells = 28;
            ifstream theTemplate("grenade.txt");
            count = 0;
            while (getline(theTemplate, line))
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
            theTemplate.close();
            cout << "\nGrenade has been selected.\n";
        }
    }

    cout << "Press ENTER to continue.";
    cin.ignore();
    cin.get();
    system("clear"); // clears the screen
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
