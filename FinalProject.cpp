// Developer:   Langley Elg & Kyle Fillhart
// Class:       COP2006-13969
// Date:        April 3, 2024
/* Description: C++ Program to play Tic-Tac-Toe against a human player and
                automated computer opponent within the CLion command prompt. */
/* Log:         April 3, 2024: Started working on final version of project
                April 5, 2024: Finished basic structure and logic
                April 7, 2024: Implemented advanced component and class concepts
                April 8, 2024: Finalized code and added to presentation
                April 21, 2024: Made additional improvements to program based
                off of student and teacher feedback from our presentation
                April 23, 2024: Finished improvements and project report */
/* Sources:     (www.geeksforgeeks.org/tic-tac-toe-game-in-cpp/), for overall
                starting concept to create Tic-Tac-Toe game
                (cplusplus.com/reference/thread/this_thread/sleep_for/), lines
                19-20, 180, 263, to include sleep functionality */

#include <iostream>
#include <chrono>
#include <thread>


// Declares user function that displays the board upon every new game and turn
void displayGame(char gameBoard[3][3])
{
    // Prints the top border of the board
    std::cout << std::endl << "   |  1  |  2  |  3  |" << std::endl <<
    "---|-----|-----|-----|" << std::endl;
    // For-loop iterates for each row of the tic-tac-toe board
    for (int rowCounter = 1; rowCounter < 4; rowCounter++)
    {
        // Prints the leftmost column border of each row
        std::cout << rowCounter << "  |  ";
        // For-loop iterates for each column of the tic-tac-toe board
        for (int columnCounter = 1; columnCounter < 4; columnCounter++)
        {
            // Prints the right border for each column
            std::cout << gameBoard[rowCounter - 1][columnCounter - 1] <<
            "  |  ";
        }
        // Prints the bottom border of each row
        std::cout << std::endl << "---|-----|-----|-----|" << std::endl;
    }
    std::cout << std::endl;
}

// Declares user function that checks if a player has made a winning move
bool checkForWin(char gameBoard[3][3], char playerMark)
{
    // For-loop iterates for each row of the tic-tac-toe board
    for (int rowCounter = 0; rowCounter < 3; rowCounter++)
    {
        // If-statement checks every horizontal three-in-a-row combination
        // If true, returns true and ends the game with the winning player
        if (gameBoard[rowCounter][0] == playerMark && gameBoard[rowCounter][0]
        == gameBoard[rowCounter][1] && gameBoard[rowCounter][1] ==
        gameBoard[rowCounter][2])
            return true;
        // If-statement checks every vertical three-in-a-row combination
        if (gameBoard[0][rowCounter] == playerMark && gameBoard[0][rowCounter]
        == gameBoard[1][rowCounter] && gameBoard[1][rowCounter] ==
        gameBoard[2][rowCounter])
            return true;
    }
    // If-statement checks northwest to southeast diagonal three-in-a-row win
    if (gameBoard[0][0] == playerMark && gameBoard[0][0] == gameBoard[1][1] &&
    gameBoard[1][1] == gameBoard[2][2])
        return true;
    // If-statement checks northeast to southwest diagonal three-in-a-row win
    if (gameBoard[0][2] == playerMark && gameBoard[0][2] == gameBoard[1][1] &&
    gameBoard[1][1] == gameBoard[2][0])
        return true;
    // If false, returns false and the game continues
    return false;
}

int playComputer()
{
    // Explains how gameplay against computer player will work
    std::cout << std::endl << "You will be playing against a computer opponent "
    "that will automatically make moves against you. Let's go!" << std::endl;

    // Declares the tic-tac-toe board and clears it so old games don't remain
    char gameBoard[3][3] = { { ' ', ' ', ' ' },
                             { ' ', ' ', ' ' },
                             { ' ', ' ', ' ' } };

    // Declares character variable to store the player's chosen mark
    char playerMark;

    // Declares character variable storing the player's choice of turn order
    char orderChoice = ' ';

    // Declares boolean variable for error checking user's turn order choice
    bool validInput;

    // Do-while loop iterates until user inputs valid turn order choice
    do
    {
        // Sets boolean variable as initially true
        validInput = true;
        // Asks user for the turn order to properly assign player marks
        std::cout << "Would you like to go first? (Y/N)" << std::endl;
        std::cin >> orderChoice;
        // If the human player wants to go first, their marker is X
        if (orderChoice == 'Y')
            playerMark = 'X';
        // If the human player wants to go second, their marker is O
        else if (orderChoice == 'N')
            playerMark = 'O';
        // Tells the user their input was invalid and sets variable as false
        else
        {
            std::cout << "Please try again with a valid input choice." <<
            std::endl;
            validInput = false;
        }
    }
    // While expression restarts loop if the else-statement executes
    while (!validInput);

    /* Declares integer variable to count turns, as a game of tic-tac-toe
       doesn't last for more than nine turns at most */
    int turnCounter;

    /* Declares integer variables to store the row and column numbers the
       user inputs to choose their desired mark space */
    int rowSelection, columnSelection;

    // Declares character variable to start tracking the current player
    char currentMark = 'X';

    /* For-loop iterates once per turn until the game ends in a draw or one of
       the players win */
    for (turnCounter = 0; turnCounter < 9; turnCounter++)
    {
        // Displays the current tic-tac-toe board at the start of every round
        displayGame(gameBoard);

        // If-statement checks if it is the human player's turn
        if (currentMark == playerMark)
        {
            /* Tells current player how to select a space and scans their
               inputs to the row and column number variables */
            std::cout << "Your move, player " << playerMark << ". Select the "
            "row number (1 - 3) of an open spot: " << std::endl;
            std::cin >> rowSelection;
            std::cout << "Now select the column number (1 - 3) to finish your "
            "move: " << std::endl;
            std::cin >> columnSelection;

            // Error checking for if the player's selection is already filled
            if (gameBoard[rowSelection - 1][columnSelection - 1] != ' ')
            {
                // Tells user to pick an empty space and resets the loop
                std::cout << "Please select an unoccupied space." << std::endl;
                continue;
            }
            // Error checking for if the player's selection is outside the board
            if (rowSelection < 1 || rowSelection > 3 || columnSelection < 1 ||
                columnSelection > 3)
            {
                // Tells user to pick a space in-range and resets the loop
                std::cout << "Please select a valid space on the board." <<
                std::endl;
                continue;
            }

            // The player's marker is placed in the selected space
            gameBoard[rowSelection - 1][columnSelection - 1] = playerMark;
        }

        // If-statement checks if it is the computer's turn
        if (currentMark != playerMark)
        {
            // Displays to user that it is the computer's turn to play
            std::cout << "Now, it's the computer player's (" << currentMark <<
            ") turn!" << std::endl;
            // Delays the output by one second to increase readability
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // Declares boolean variable for error checking computer's play
            bool validPlay;

            // Do-while loop iterates until computer generates a valid play
            do
            {
                // Sets boolean variable as initially true
                validPlay = true;
                // Randomly selects the computer's play position
                rowSelection = std::rand() % 3;
                columnSelection = std::rand() % 3;

                // Error checking for if the selection is already filled
                if (gameBoard[rowSelection][columnSelection] != ' ')
                    // Sets variable as false
                    validPlay = false;
            }
            // While expression restarts loop if the if-statement executes
            while (!validPlay);

            // The computer's marker is placed in the generated space
            gameBoard[rowSelection][columnSelection] = currentMark;
        }

        /* If-statement calls function to check if there are any winning
           patterns on the current board and which player has them */
        if (checkForWin(gameBoard, currentMark))
        {
            // Displays the final board if a win is detected
            displayGame(gameBoard);
            // Displays which player won based on the currently active mark
            std::cout << "Player " << currentMark << " wins!" << std::endl;
            break;
        }

        // Conditional operator checks the current mark
        /* If the current mark is X, change it to O, but if the current mark is
           O, change it to X */
        currentMark = (currentMark == 'X') ? 'O' : 'X';
    }

    // If-statement checks the game at turn 9 if either player hasn't won
    if (turnCounter == 9 && !checkForWin(gameBoard, 'X') &&
        !checkForWin(gameBoard, 'O'))
    {
        // Displays that there has been a draw and neither player has won
        std::cout << "The game's a draw!" << std::endl;
    }

    return 0;
}

// Declares user function that plays the actual game against an opponent
int playHuman()
{
    // Explains gameplay and implores players to choose their marks
    std::cout << std::endl << "You will be playing against a human opponent at "
    "the same computer, so make sure you each pick your own mark. Let's go!" <<
    std::endl;

    // Declares the tic-tac-toe board and clears it so old games don't remain
    char gameBoard[3][3] = { { ' ', ' ', ' ' },
                             { ' ', ' ', ' ' },
                             { ' ', ' ', ' ' } };

    // Declares the first player's mark as X, as X goes first in tic-tac-toe
    char playerMark = 'X';

    /* Declares integer variable to count turns, as a game of tic-tac-toe
       doesn't last for more than nine turns at most */
    int turnCounter;

    /* Declares integer variables to store the row and column numbers the
       user inputs to choose their desired mark space */
    int rowSelection, columnSelection;

    /* For-loop iterates once per turn until the game ends in a draw or
       someone wins */
    for (turnCounter = 0; turnCounter < 9; turnCounter++)
    {
        // Delays the output by one second to increase readability
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Displays the current tic-tac-toe board at the start of every round
        displayGame(gameBoard);

        /* While-loop allows for error checking and repeated turns between
           players */
        while (true)
        {
            /* Tells current player how to select a space and scans their
               inputs to the row and column number variables */
            std::cout << "Your move, player " << playerMark << ". "
            "Select the row number (1 - 3) of an open spot: " << std::endl;
            std::cin >> rowSelection;
            std::cout << "Now select the column number (1 - 3) to finish your "
            "move: " << std::endl;
            std::cin >> columnSelection;

            // Error checking for if the player's selection is already filled
            if (gameBoard[rowSelection - 1][columnSelection - 1] != ' ')
            {
                // Tells user to pick an empty space and resets the loop
                std::cout << "Please select an unoccupied space." << std::endl;
                continue;
            }
            // Error checking for if the player's selection is outside the board
            if (rowSelection < 1 || rowSelection > 3 || columnSelection < 1 ||
                columnSelection > 3)
            {
                // Tells user to pick a space in-range and resets the loop
                std::cout << "Please select a valid space on the board." <<
                std::endl;
                continue;
            }
            // The loop breaks to finalize the selection if no errors occur
            else
                break;
        }

        /* The specified space is changed from a blank space to the current
           player's mark */
        gameBoard[rowSelection - 1][columnSelection - 1] = playerMark;

        /* If-statement calls function to check if there are any winning
           patterns on the current board and which player has them */
        if (checkForWin(gameBoard, playerMark))
        {
            // Displays the final board if a win is detected
            displayGame(gameBoard);
            // Displays which player won based on the currently active mark
            std::cout << "Player " << playerMark << " wins!" << std::endl;
            break;
        }

        // Conditional operator checks the current mark
        /* If the current mark is X, change it to O, but if the current mark is
           O, change it to X */
        playerMark = (playerMark == 'X') ? 'O' : 'X';
    }

    // If-statement checks the game at turn 9 if either player hasn't won
    if (turnCounter == 9 && !checkForWin(gameBoard, 'X') &&
        !checkForWin(gameBoard, 'O'))
    {
        // Displays that there has been a draw and neither player has won
        std::cout << "The game's a draw!" << std::endl;
    }

    return 0;
}

// Declares main function that holds user choices and initial information
int main()
{
    // Declares boolean variable for checking if the game is still running
    bool playingGame = true;

    // Explains game instructions to user
    std::cout << "Welcome to Tic-Tac-Toe! Your goal is to get three of "
    "your marks (X's or O's) in a row before your opponent does!" << std::endl;

    // While-loop executes code until the user choose to not play again
    while (playingGame) {
        // Declares character variable storing the player's choices
        char playerChoice;

        // Explains the two gameplay options that the user can choose
        std::cout << "To play against another human player, type 1. To play "
        "against an automatic computer player, type 2: " << std::endl;
        std::cin >> playerChoice;

        // If-statement starts a game with a human opponent if user enters 1
        if (playerChoice == '1')
            playHuman();
        // If-statement starts a game with a computer opponent if user enters 2
        else if (playerChoice == '2')
            playComputer();
        // Final else-statement resets loop if the input is not 1 or 2
        else
        {
            // Tells user to try again before returning to the start of the loop
            std::cout << "Please try again with a valid input choice." <<
            std::endl;
            continue;
        }

        // Asks user if they want to play another game of tic-tac-toe
        std::cout << std::endl << "Would you like to play again? (Y/N)" <<
        std::endl;
        // Scans user's answer to character variable
        std::cin >> playerChoice;

        /* If the user's answer is anything other than yes, the while loop
           will be declared false and the program will end */
        if (playerChoice != 'Y')
        {
            // The boolean parameter of the while-loop is set as false
            playingGame = false;
            // Displays a final sign-off to the user
            std::cout << "Thanks for playing! Exiting program now..." <<
            std::endl;
        }
    }

    return 0;
}