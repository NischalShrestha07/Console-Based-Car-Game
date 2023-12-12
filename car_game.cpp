#include <iostream> // to include input and output

#include <windows.h> // to include all of the function in windows

#include <stdlib.h> // to include standard library

#include <time.h> // to get and manipulate date and time information

#include <conio.h> //to include functions for console input/output like keyword controller.

using namespace std;

bool exitGame;

bool gameOver;

bool isMoving;

bool bombExplode;

bool dead;

int height;

int width;

int life = 5;

int speed;

int score;

int myCarX;

int myCarY;

int highScore;

int highestScore[5];

int enemyX[4];

int enemyY[4] = {-8, -18, -28, -38};
/*represent the Y coordinates of enemies in a game or some other graphical application.
initializes them with specific Y coordinates for enemies in a game or similar application.

->The array enemyY will have the following values:
enemyY[0] is initialized to -8.
enemyY[1] is initialized to -18.
enemyY[2] is initialized to -28.
enemyY[3] is initialized to -38.
*/

int enemyPostionX;

int enemyPostionY;

int enemyNum;

string bombParticle1[4] = {"o   o", " ooo ", " ooo ", "o   o"};

string bombParticle2[4] = {" ooo ", "o   o", "o   o", " ooo "};
//-------------------------------------------------------------------------------------
/*The arrays bombParticle1 and bombParticle2 are arrays of strings.
 In C++, the string type is used to represent sequences of characters.

Each string in the array represents a line of the visual pattern for the bomb particle.

For bombParticle1:
bombParticle1[0] is "o   o".
bombParticle1[1] is " ooo ".
bombParticle1[2] is " ooo ".
bombParticle1[3] is "o   o".

For bombParticle2:
bombParticle2[0] is " ooo ".
bombParticle2[1] is "o   o".
bombParticle2[2] is "o   o".
bombParticle2[3] is " ooo ".

The specific strings inside each array are designed to create
a visual representation of a bomb particle when printed to the screen.
*/
//-------------------------------------------------------------------------------------

string myCar[4] = {" * ",

                   "* *",

                   " * ", /*"In our project, we utilize a C++ string array named myCar to create a visual
                           representation of a car in a text-based or console environment."*/
                   "* *"};

//-------------------------------------------------------------------------------------
/*gotoxy is a function designed to set the console cursor to a specified position on the screen.
 It takes two parameters  x for the horizontal coordinate and y for the vertical coordinate.*/
void gotoxy(int x, int y) /*
                          ->  gotoxy function plays a crucial role in our project by providing a means to dynamically control
                           the console cursor position, adding flexibility and interactivity to our console-based user interface."
                           */

{

    COORD coord; /*COORD is a Windows API structure representing a coordinate in a console screen buffer.
                 The function utilizes SetConsoleCursorPosition to set the cursor position
                  using the standard output handle and the specified coordinates.

                  For example, calling gotoxy(10, 5) would move the console cursor
                  to the position (10, 5) on the screen.*/

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//-------------------------------------------------------------------------------------

void hideCursor()
{ /*designed to hide the console cursor.
   It achieves this by manipulating the CONSOLE_CURSOR_INFO structure and using the Windows API.*/

    CONSOLE_CURSOR_INFO cursor; //->  CONSOLE_CURSOR_INFO is a structure representing information about the console cursor."

    cursor.dwSize = 100; //  ->cursor.dwSize = 100; sets the cursor size. In this case, it's set to 100, making it effectively invisible.

    cursor.bVisible = false; // ->cursor.bVisible = false; sets the cursor visibility to false, hiding it from the console screen.

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    /*SetConsoleCursorInfo is a Windows API function used to set cursor information.
    It takes the standard output handle and a pointer to the CONSOLE_CURSOR_INFO structure as parameters.

    Calling hideCursor() will make the cursor effectively invisible on the console screen.    */
}
//-------------------------------------------------------------------------------------

void startUp() // all values once the game start.

{

    srand(time(NULL)); /*The srand(time(NULL)) seeds the random number generator with the current time, ensuring
                         different random values on each run."  */

    // Initialize game state variables
    exitGame = false;
    isMoving = false;
    gameOver = false;
    dead = false;

    // Setting game dimension
    height = 20;
    width = 19;

    // Setting initial player car position
    myCarX = 8;
    myCarY = 16;

    speed = 1;    // setting speed.
    enemyNum = 4; // setting the number of enemies.
    score = 0;    // initialize score

    for (int i = 0; i < enemyNum; i++) // loop to initialize the position of the enemy positioms
    {
        enemyPostionX = rand() % 3; // Generate random X position for each enemy

        if (enemyPostionX == 0) // Set enemy X position based on random value
            enemyX[i] = 2;

        else if (enemyPostionX == 1)
            enemyX[i] = 8;

        else if (enemyPostionX == 2)
            enemyX[i] = 14;
    }
    // Set initial Y positions for enemies
    enemyY[0] = -8;
    enemyY[1] = -18;
    enemyY[2] = -28;
    enemyY[3] = -38;
}
//----------------------------------------------------------------------------------------

void layout() // to print the game layout.
{
    for (int i = 0; i < height; i++) // Loop through each row of the game

    {
        // Move the cursor to the leftmost position of the current row
        gotoxy(0, i);

        // Print the left boundary of the game grid
        cout << "#                #"; // 16 gaps

        // Check if the current row is even and the game is in a moving state
        if (i % 2 == 0 && isMoving) /*--> FOR EVEN ROWS,the game is in a moving state (isMoving), it prints
                                   a visual representation of the player's car (| |)."*/
        {                           // FOR ODD ROWS, if the game is not in a moving state, it prints the same representation.

            // Move the cursor to a specific position
            gotoxy(6, i);
            // Print a component representing the player's car (for even rows)
            cout << "|     | "; // 5 gaps
        }

        // Check if the current row is odd and the game is not in a moving state
        else if (i % 2 != 0 && !isMoving)

        {
            // Move the cursor to a specific position
            gotoxy(6, i);
            // Print a component representing the player's car (for odd rows)
            cout << "|     | "; // 5 gaps
        }
    }
    // Print additional information at the bottom of the screen
    gotoxy(5, 21);
    cout << "Life:" << life;

    gotoxy(5, 22);
    cout << "Score:" << score;
}
//----------------------------------------------------------------------------------------

void drawMyCar() // "The drawMyCar function is responsible for rendering the player's car on the console screen."
{
    // Check if the player's car is not in a dead state
    if (!dead)
    {
        // Loop through each part of the player's car
        for (int i = 0; i < 4; i++)
        {
            // Move the cursor to the specified position.
            gotoxy(myCarX, myCarY + i);
            // Print a part of the player's car
            cout << myCar[i];
        }
    } /*  If the car is not dead, the function uses a loop to iterate through each part of the player's car
     (represented by strings in the myCar array)."It moves the cursor to the specified position and prints each part of the player's car."*/

    // If the player's car is in a dead state, the function prints empty spaces to represent the dead state
    else

    {
        // If the player's car is in a dead state, print empty spaces

        for (int i = 0; i < 4; i++)

        {
            // Move the cursor to the specified position
            gotoxy(myCarX, myCarY + i);
            // Print empty spaces to represent the dead state
            cout << "    "; // 4 gaps
        }
    }
}

//----------------------------------------------------------------------------------------
// THIS HASN'T CONSIST THE GOOD EXPLANATION SO  DO RESEARCH OTHER ANSWERS AS WELL.
void drawEnemyCar() // is a critical component of our project, responsible or rendering the enemy cars on the console screen.
{
    // Loop through each enemy car
    for (int i = 0; i < enemyNum; i++)

    {
        // Check if the enemy car is partially visible on the screen
        if (enemyY[i] + 3 > 0)

        {
            // Move the cursor to the specified position and print a part of the enemy car
            gotoxy(enemyX[i], enemyY[i] + 3);

            cout << " # ";
        }

        if (enemyY[i] + 2 > 0)

        {

            gotoxy(enemyX[i], enemyY[i] + 2);

            cout << "# #";
        }

        if (enemyY[i] + 1 > 0)

        {

            gotoxy(enemyX[i], enemyY[i] + 1);

            cout << " # ";
        }

        if (enemyY[i] > 0)

        {

            gotoxy(enemyX[i], enemyY[i]);

            cout << "# #";
        }
        // Check if the enemy car is partially outside the bottom of the screen
        if (enemyY[i] + 3 >= 20)

        {
            // Check if the enemy car is partially outside the bottom of the screen
            gotoxy(enemyX[i], enemyY[i] + 3);

            cout << "   "; // 3 gaps
        }

        if (enemyY[i] + 2 >= 20)

        {

            gotoxy(enemyX[i], enemyY[i] + 2);

            cout << "   ";
        }

        if (enemyY[i] + 1 >= 20)

        {

            gotoxy(enemyX[i], enemyY[i] + 1);

            cout << "   ";
        }

        if (enemyY[i] >= 20)

        {

            gotoxy(enemyX[i], enemyY[i]);

            cout << "   ";
        }
    }
}

void carController() // to control our car using keyboard input .Responsible for handling
// user input to control the movement of the player's car using keyboard commands.

{
    if (_kbhit()) // Check if a key is pressed This function is part of the <conio.h>
                  // header and returns a non-zero value if a key is pressed."
    {
        switch (getch()) // this is the switch case copied from tutorial which works.
                         // Use a switch statement to handle different keyboard inputs
        {
            /* ->Different cases in the switch statement correspond to different keys.
            'a': Move the car left by subtracting 6 from the current X coordinate (myCarX).
            'd': Move the car right by adding 6 to the current X coordinate.
            'w': Move the car up by subtracting 2 from the current Y coordinate (myCarY).
            's': Move the car down by adding 2 to the current Y coordinate.*/
        case 'a':

            myCarX = myCarX - 6;

            break;

        case 'd':

            myCarX = myCarX + 6;

            break;

        case 'w':

            myCarY = myCarY - 2;

            break;

        case 's':

            myCarY = myCarY + 2;

            break;
        }
    }
}
//----------------------------------------------------------------------------------

/*The carOperator function is the core of our project, responsible for managing game
 mechanics, rules, and logic to create a dynamic and engaging gameplay experience."*/
void carOperator() // all mechanics,rules and logics.
{
    srand(time(NULL)); // The function seeds the random number generator with the current time to ensure different random values on each run."

    if (isMoving) /// Toggle the game state between moving and not moving

        isMoving = false;

    else

        isMoving = true;

    for (int i = 0; i < enemyNum; i++) // Move each enemy car downward
    {

        enemyY[i]++;
    }
    /// Check if any enemy car has reached the bottom of the screen
    // If so, it resets its position and increments the score."
    for (int i = 0; i < enemyNum; i++)
    {
        if (enemyY[i] > 21)
        {
            // Reset the position of the enemy car and increment the score
            enemyPostionX = rand() % 3;

            if (enemyPostionX == 0)

                enemyX[i] = 2;

            else if (enemyPostionX == 1)

                enemyX[i] = 8;

            else if (enemyPostionX == 2)

                enemyX[i] = 14;

            enemyY[i] = -8;

            score++;
        } // Note: The carOperator function encapsulates the game's mechanics, rules, and logic to create a dynamic and challenging gameplay experience.
    }
    // Check for collision between the player's car and enemy cars
    // If a collision is detected, it sets the game state to indicate the player is dead.
    for (int i = 0; i < enemyNum; i++)
    {
        if ((myCarY <= enemyY[i] + 3 && myCarY >= enemyY[i] || enemyY[i] >= myCarY && enemyY[i] <= myCarY + 3) && myCarX == enemyX[i])
        // This block of code is crucial for determining whether a collision has occurred between the player's car and any of the enemy cars.
        /*It checks if the player's car, defined by its position and size, intersects with any enemy car on the screen.

  --->   The conditions within the if statement ensure that a collision is detected if either the player's car's Y-coordinate is within the vertical range of an enemy car or the enemy car's Y-coordinate is within the vertical range of the player's car."
  ---> Furthermore, it checks if the X-coordinates of the player's car and the enemy car are the same, indicating a collision in the horizontal direction.
If a collision is detected, it sets the dead variable to true, indicating that the player has lost the game.*/
        {
            // Set the game state to indicate the player is dead
            dead = true;
        }
    }
}

void bombExplosion() // to print bomb explosion effect
{
    /// Check if the bomb is set to explode
    if (bombExplode)
    {
        //// Print the first bomb particle pattern
        for (int i = 0; i < 4; i++)
        {
            gotoxy(myCarX - 1, myCarY - 1 + i);

            cout << bombParticle1[i] << endl;
        }
        // Toggle the bomb explode state
        bombExplode = false;
    }
    else
    {
        // Print the second bomb particle pattern
        for (int i = 0; i < 4; i++)
        {
            gotoxy(myCarX - 1, myCarY - 1 + i);

            cout << bombParticle2[i] << endl;
        }
        // Toggle the bomb explode state
        bombExplode = true;
    }

    Sleep(100); // Introduce a slight delay for a smooth visual effect
}
//------------------------------------------------------------------------------

void died() // The died function manages the game logic that occurs when our player's character crashes
{
    if (dead) // The function begins by checking if the player is dead.
    {
        life--; // If the player is dead, it decrements the player's life count (life).

        int count = 0; // Introduce a brief animation after the player's death

        /*To enhance the gaming experience, the function introduces a brief animation loop after the player's death."
        "The loop allows the player to control the car (carController) during the animation."
        "It displays a bomb explosion effect (bombExplosion).*/
        while (count != 10)
        {
            carController(); // Allow the player to control the car during the animation.
            bombExplosion(); // Display a bomb explosion effect

            count++;
        }
        // Clear the message at the bottom of the screen
        gotoxy(2, 22);

        cout << "                    "; // 20 gaps
        startUp();                      // Reset the game state and parameters preparing for the next round of the game.
    }
}

/*The transition function is responsible for creating a
visually appealing screen transition effect, adding a polished touch to our game.*/

/*
The first loop (phase) gradually fades out the screen from bottom to top.
It iterates through each row of the console window (from the bottom) and prints a line of 17 '#' characters.
A slight delay (Sleep(15)) between iterations ensures a smooth visual transition*/
void transition()
{
    for (int i = 19; i >= 0; i--) // First phase: Fading out
    {
        gotoxy(1, i);
        cout << "################"; // 17 #'s
        Sleep(15);
    }
    // Second phase: Fading in
    /*The second loop (phase) gradually fades in the screen from top to bottom."
"   It iterates through each row of the console window (from the top) and prints empty spaces to erase the previously drawn '#' characters.
    Again, a slight delay (Sleep(15)) between iterations ensures a smooth visual transition.*/

    for (int i = 1; i < 20; i++)
    {
        gotoxy(1, i);
        cout << "                "; // 17 spaces.
        Sleep(15);
    }
}
//--------------------------------------------------------------------------
/*The game_Over function manages the game logic that occurs when our character runs out of lives,
creating a concluding and interactive game over screen.*/
void game_Over()
{
    if (life == 0) // Check if the player has run out of lives (life == 0).
    {
        gameOver = true;

        // Display the game over screen and wait for the player to press 'x'
        do
        {
            // Print the game over screen
            // (Note: The screen is cleared in each iteration to simulate animation)
            gotoxy(0, 0);

            cout << "###################"; // 19 #'s

            gotoxy(0, 1);

            cout << "#                 #";

            gotoxy(0, 2);

            cout << "#                 #";

            gotoxy(0, 3);

            cout << "#                 #";

            gotoxy(0, 4);

            cout << "#                 #";

            gotoxy(0, 5);

            cout << "#                 #";

            gotoxy(0, 6);

            cout << "#   GAME OVER!!   #";

            gotoxy(0, 7);

            cout << "#                 #";

            gotoxy(0, 8);

            cout << "#   THANK YOU     #";

            gotoxy(0, 9);

            cout << "#     FOR         #";

            gotoxy(0, 10);

            cout << "#    PLAYING      #";

            gotoxy(0, 11);

            cout << "#      THE        #";

            gotoxy(0, 12);

            cout << "#    CAR GAME     #";

            gotoxy(0, 13);

            cout << "#                 #";

            gotoxy(0, 14);

            cout << "#   ( O _ O )     #";

            gotoxy(0, 15);

            cout << "#                 #";

            gotoxy(0, 16);

            cout << "#                 #";

            gotoxy(0, 17);

            cout << "#    PRESS 'x'    #";

            gotoxy(0, 18);

            cout << "#    TO EXIT!!    #";

            gotoxy(0, 19);

            cout << "###################";

            gotoxy(0, 20);

            cout << "                      ";

            gotoxy(0, 21);

            cout << "                      ";

        } while (getch() != 'x'); // Wait for the player to press 'x'

        exit(1); /// Exit the program
    }
}
//-----------------------------------------------------------------------

void circular_Effect() // to print the spiral effect

{
    // Define starting and ending positions for the spiral effect
    int row = 1, col = 1;

    int last_row = height - 2, last_col = width - 2;

    // Spiral Effect: Drawing the Spiral
    /*"During the drawing phase, the function iteratively places '#' characters in a spiral pattern, creating a visually appealing effect."
The drawing is performed row by row and column by column, progressing inwards towards the center of the screen.
Delays (Sleep) between characters add a sense of animation, making the spiral effect more dynamic.
*/
    while (row <= last_row && col <= last_col)

    {
        // Draw top row of the spiral
        for (int i = col; i <= last_col; i++)
        {

            gotoxy(i, row);

            cout << "#";

            Sleep(2);
        }
        row++;

        // Draw right column of the spiral
        for (int i = row; i <= last_row; i++)
        {

            gotoxy(last_col, i);

            cout << "#";
        }
        last_col--;

        // Draw bottom row of the spiral
        if (row <= last_row)
        {
            for (int i = last_col; i >= col; i--)
            {
                gotoxy(i, last_row);

                cout << "#";

                Sleep(1);
            }

            last_row--;
        }

        // Draw left column of the spiral
        if (col <= last_col)
        {
            for (int i = last_row; i >= row; i--)
            {
                gotoxy(col, i);

                cout << "#";
            }
            col++;
        }
    }

    // Clear the spiral: Removing the Spiral Effect
    /*In the clearing phase, the function iteratively removes the previously drawn '#' characters, creating a smooth disappearing effect.
Similar to the drawing phase, the clearing is performed row by row and column by column, progressing inwards towards the center."
Delays (Sleep) between characters ensure a gradual and visually appealing clearing animation.*/
    row = 1, col = 1;

    last_row = height - 2, last_col = width - 2;

    while (row <= last_row && col <= last_col)
    {
        // Clear top row of the spiral
        for (int i = col; i <= last_col; i++)

        {

            gotoxy(i, row);

            cout << " ";

            Sleep(2);
        }

        row++;

        // Clear right column of the spiral
        for (int i = row; i <= last_row; i++)
        {
            gotoxy(last_col, i);

            cout << " ";
        }
        last_col--;

        // Clear bottom row of the spiral
        if (row <= last_row)
        {
            for (int i = last_col; i >= col; i--)
            {

                gotoxy(i, last_row);

                cout << " ";

                Sleep(1);
            }
            last_row--;
        }

        // Clear left column of the spiral
        if (col <= last_col)
        {
            for (int i = last_row; i >= row; i--)
            {
                gotoxy(col, i);
                cout << " ";
            }
            col++;
        }
    }
}
//---------------------------------------------------------------------

/*"The frontScreen function is a vital component in creating a captivating first impression for our game. It generates a visually
 stunning splash screen that welcomes players as they enter the gaming experience."*/
void frontScreen() // to print splash screen.
{
    // Displaying the Splash Screen
    cout << endl

         << endl;
    gotoxy(0, 0);

    cout << "###################";

    gotoxy(0, 1);

    cout << "#                 #";

    gotoxy(0, 2);

    cout << "#         #       #";

    gotoxy(0, 3);

    cout << "#        ##       #";

    gotoxy(0, 4);

    cout << "#         #       #";

    gotoxy(0, 5);

    cout << "#         #       #";

    gotoxy(0, 6);

    cout << "#        ###      #";

    gotoxy(0, 7);

    cout << "#                 #";

    gotoxy(0, 8);

    cout << "#     #   #   #   #";

    gotoxy(0, 9);

    cout << "#     #   ##  #   #";

    gotoxy(0, 10);

    cout << "#     #   #  ##   #";

    gotoxy(0, 11);

    cout << "#     #   #   #   #";

    gotoxy(0, 12);

    cout << "#                 #";

    gotoxy(0, 13);

    cout << "#          #      #";

    gotoxy(0, 14);

    cout << "#         ##      #";

    gotoxy(0, 15);

    cout << "#          #      #";

    gotoxy(0, 16);

    cout << "#          #      #";

    gotoxy(0, 17);

    cout << "#         ###     #";

    gotoxy(0, 18);

    cout << "#                 #";

    gotoxy(0, 19);

    cout << "###################";

    Sleep(500); // Pause for a short duration to allow users to view the splash screen
}

void startGame() // to print game title

{
    // Displaying the Game Title Screen
    do

    {

        gotoxy(0, 0);

        cout << "###################"; // 19 #'s

        gotoxy(0, 1);

        cout << "#                 #";

        gotoxy(0, 2);

        cout << "#    BRICK GAME   #";

        gotoxy(0, 3);

        cout << "#     RACE CAR    #";

        gotoxy(0, 4);

        cout << "#                 #";

        gotoxy(0, 5);

        cout << "#    #   |   #    #"; // 4gaps and 3 gaps resp.

        gotoxy(0, 6);

        cout << "#    #   |   #    #";

        gotoxy(0, 7);

        cout << "#    #   |   #    #";

        gotoxy(0, 8);

        cout << "#    #   |   #    #";

        gotoxy(0, 9);

        cout << "#    #   |   #    #";

        gotoxy(0, 10);

        cout << "#    #   |   #    #";

        gotoxy(0, 11);

        cout << "#    #   |   #    #";

        gotoxy(0, 12);

        cout << "#    #   |   #    #";

        gotoxy(0, 13);

        cout << "#    #   |   #    #";

        gotoxy(0, 14);

        cout << "#    #   |   #    #";

        gotoxy(0, 15);

        cout << "#                 #";

        gotoxy(0, 16);

        cout << "#  PRESS 'Space'  #";

        gotoxy(0, 17);

        cout << "#     TO START    #";

        gotoxy(0, 18);

        cout << "#                 #";

        gotoxy(0, 19);

        cout << "###################";

 /*"do-while loop ensures that the title screen remains visible until the player initiates the game by pressing the 'Space' key."
while (getch() != 32); waits for the player to press the 'Space' key to exit the loop and start the game.*/

    } while (getch() != 32); // Wait for the player to press the 'Space' key to start the game
}
/*gotoxy(0, 0); positions the cursor at the top-left corner of the console to start building the game title screen."
A series of cout statements with strategically placed characters and gaps construct a visually appealing title screen."
Example: "cout << "# BRICK GAME #"; adds the title of the game with spaces for formatting.*/

int main(void)
{
    hideCursor(); // Hide the console cursor for a cleaner display

    startUp(); // Set up initial game values

    frontScreen(); // Display the splash screen

    circular_Effect(); // Present a captivating circular effect

    transition(); // Execute a transition effect

    startGame(); // Initiate the game

    // Main Game Loop
    while (!dead)
    {
        layout(); // Display the game layout

        carController(); // Control the player's car using keyboard input

        carOperator(); // Manage game mechanics, rules, and logics

        drawMyCar(); // Draw the player's car

        drawEnemyCar(); // Draw enemy cars

        died(); // Handle logic when the player's car crashes

        game_Over(); // Display game over screen if needed

        Sleep(50); // Pause for a short duration to control the game speed
    }

    system("cls");
}