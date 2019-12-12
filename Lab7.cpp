/*
Nolan Thoms
C++ Fall Semester, 2019
Lab 7
BattleShip Game
*/

#include<iostream>
#include<time.h>
#include<assert.h>

using namespace std;

//This enum has different enumerators for each ship type, it's purpose
//is to help show which ship is being used.
enum shipType{carrier, battleship, cruiser, submarine, destroyer};

//This struct holds all of the differnt variables that will later define
//the ships for both the player and the computer.
struct fleet
{
	int xCord;
	int yCord;
	shipType ship;
	int size;
	int direction;
	int health;
};

/*preconditions: In order for the function work, the only precondition is that
one of the four arrays should be succesfully passed through to the function.*/

/*postconditions: After the function runs, the values of the array passed
through should be outputed to the screen.*/
void gridDisplay(char grid[][10]);

/*preconditions: Before this function runs the values of friendlyShips needs to
be initialized and the array grid should be passed through.*/

/*postconditions: After the function, x, y, and direction values should be
assigned to all of the friendly ships and the values of the ship should
be intialzed to grid1.*/
void placingFriendlyShips(fleet friendlyShips[], char grid1[][10]);

/*preconditions: The Preconditions are the same as the placing friendlyShip
function, but with enemyShips and grid2.*/

/*postconditions: The Postconditions are the same as the placing friendlyShip
function, but with enemyShips and grid2.*/
void placingEnemyShips(fleet enemyShips[], char grid2[][10]);

/*preconditions: In order for this function to work, the values in either
placingFriendlyShips or placingEnemyShips must be passed through to this function.*/

/*postconditions: After this function either the value of the ship passed should
be initialized on the grid passed or the value of crash should be increased.*/
void initializeShips(fleet Ships[], char grid[][10], int& crash, int i);

/*preconditions: In order for this function to work all previous functions
must have ran properly and all of the arrays and variables must be passed through
successfully.*/

/*postconditions: After this function either playerPoints or comPoints should
equal 17 and the value of either wins or losses should be updated.*/
void battlePhase(fleet friendlyShips[], fleet enemyShips[], char grid1[][10], char grid2[][10], char grid3[][10], char grid4[][10], int& wins, int& losses);

void checkShip(fleet Ships[], char grid[][10], int X, int Y);

/*preconditions: The only preconditions are that winCheck and losses are
passed by reference into the function.*/

/*postconditions: After the function either nothing should be differnt or if
surrender is selected than both main function loops should be exited.*/
void surrender(bool& winCheck, int& losses);

/*precontitions: The only precondition for this function to work is that
if any user input corrupts the stream.*/

/*postconditions: An error message is outputted to a the screen.*/
void malfunction();

int main()
{
	//This helpss gnerates all of the random numbers.
	srand(unsigned int(time(NULL)));

	//These variables keep track of the number of wins and losses.
	int wins = 0;
	int losses = 0;

	//This bool holds the value that will termine if the game loop runs again.
	bool playAgain = true;

	//This is the game loop.
	do
	{
		// This is initializing the information in the sructs for both friendly and enemy ships.
		fleet friendlyShips[5]; //This declares an array of the struct for the player's ships.
		fleet enemyShips[5]; //This declares an array of the struct for the enemy's ships.
		for (int i = 0; i < 5; i++) //This loop goes through the five ships.
		{
			friendlyShips[i].xCord = 0, enemyShips[i].xCord = 0; //This initializes all the x coordinates.
			friendlyShips[i].yCord = 0, enemyShips[i].yCord = 0; //This initializes all the y coordinates.
			friendlyShips[i].direction = 0, enemyShips[i].direction = 0; //This initializes the direction.

			//This switch statment intializes all off the specific information
			//for each ship, such as type, size, and health.
			switch (i)
			{
			case 0: friendlyShips[i].ship = carrier, enemyShips[i].ship = carrier;
				friendlyShips[i].size = 5, enemyShips[i].size = 5;
				friendlyShips[i].health = 5, enemyShips[i].health = 5;
				break;
			case 1: friendlyShips[i].ship = battleship, enemyShips[i].ship = battleship;
				friendlyShips[i].size = 4, enemyShips[i].size = 4;
				friendlyShips[i].health = 4, enemyShips[i].health = 4;
				break;
			case 2: friendlyShips[i].ship = cruiser, enemyShips[i].ship = cruiser;
				friendlyShips[i].size = 3, enemyShips[i].size = 3;
				friendlyShips[i].health = 3, enemyShips[i].health = 3;
				break;
			case 3: friendlyShips[i].ship = submarine, enemyShips[i].ship = submarine;
				friendlyShips[i].size = 3, enemyShips[i].size = 3;
				friendlyShips[i].health = 3, enemyShips[i].health = 3;
				break;
			case 4: friendlyShips[i].ship = destroyer, enemyShips[i].ship = destroyer;
				friendlyShips[i].size = 2, enemyShips[i].size = 2;
				friendlyShips[i].health = 2, enemyShips[i].health = 2;
				break;
			}
		}

		// This is the declaration of the grids that will be used
		char grid1[10][10];
		char grid2[10][10];
		char grid3[10][10];
		char grid4[10][10];

		//This initializes the values of the grids to be water.
		for (int rows = 0; rows < 10; rows++)
		{
			for (int colms = 0; colms < 10; colms++)
			{
				grid1[rows][colms] = '~';
				grid2[rows][colms] = '~';
				grid3[rows][colms] = '~';
				grid4[rows][colms] = '~';
			}
		}

		// This outputs the welcome screen.
		cout << "Welcome to BattleShip, this is the grid you will be placing your ships on." << endl;
		cout << "when you place your ships they will automaticaly be placed to the right of the coordinate if \nthe horrizontal direction is selcted, and below the coordinate if vertical is selected. \n";
		cout << "Also if the ship runs off of the grid it, instead will just be placed in \nthe opposite direction. \n \n";
		gridDisplay(grid1);

		//This function is used to place the friendly ships on grid1
		placingFriendlyShips(friendlyShips, grid1);

		//This function is used to place the enemy ships on grid2.
		placingEnemyShips(enemyShips, grid2);

		//This function allows the player and computer to input guesses
		//and continues untill either side's ships are completely destroyed.
		battlePhase(friendlyShips, enemyShips, grid1, grid2, grid3, grid4, wins, losses);

		//This variable holds the user input that determines if
		//the player would like to play again.
		int again;

		//This asks if the user would like to play again and has them
		// input a value in to again.
		cout << "\nWould you like to play again?\n";
		cout << "press 1 for yes and 2 for no: ";
		cin >> again; malfunction(); assert(cin);
		//If the user inputs a 2 playAgain becomes false and the loop will exit.
		if (again == 2)
			playAgain = false;

	} while (playAgain);

	//This displays the times won and lost.
	cout << "\ntimes won: " << wins;
	cout << "\ntimes lost: " << losses;

	return 0;
}

//This function displays a grid depending on which array is passed through.
void gridDisplay(char grid[][10])
{
	cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
	int yAxis = 1;
	for (int rows = 0; rows < 10; rows++) //This for loop runs through the rows of the array
	{
		if (yAxis == 10)
			cout << yAxis << " ";
		else
			cout << yAxis << "  ";
		yAxis++;
		for (int colms = 0; colms < 10; colms++) //This for loop runs through the columns of the array.
		{
			cout << grid[rows][colms] << " "; //This outputs the value stored in a coordinate of the array.
		}
		cout << "\n";
	}
}

//This function takes a user input and puts the information into an array,
//which display as ships on water.
void placingFriendlyShips(fleet friendlyShips[], char grid1[][10])
{
	for (int i = 0; i < 5; i++)//This for loop runs through the different ships.
	{
		//Each time the for loop is executed the player input an x coordinate
		//a y coordinate and a direction, then there is a check to make sure
		//the input is valid. Then both coordinates are subtracted so the
		//array can use them correctly.
		switch (i)
		{
		case 0: cout << "\n You will now be placing the Carrier Ship, it is 5 spaces long. \n";
			cout << "\n select a x coordinate (top number) between one and ten: "; cin >> friendlyShips[i].xCord; malfunction(); assert(cin); --friendlyShips[i].xCord;
			cout << "\n select a y coordinate (side number) between one and ten: "; cin >> friendlyShips[i].yCord; malfunction(); assert(cin); --friendlyShips[i].yCord;
			cout << "\n select a direction, enter 1 for vertical and 2 for horizontal: "; cin >> friendlyShips[i].direction; malfunction(); assert(cin);
			break;
		case 1: cout << "\n You will now be placing the Battle Ship, it is 4 spaces long. \n";
			cout << "\n select a x coordinate (top number) between one and ten: "; cin >> friendlyShips[i].xCord; malfunction(); assert(cin); --friendlyShips[i].xCord;
			cout << "\n select a y coordinate (side number) between one and ten: "; cin >> friendlyShips[i].yCord; malfunction(); assert(cin); --friendlyShips[i].yCord;
			cout << "\n select a direction, enter 1 for vertical and 2 for horizontal: "; cin >> friendlyShips[i].direction; malfunction(); assert(cin);
			break;
		case 2: cout << "\n You will now be placing the Cruiser, it is 3 spaces long. \n";
			cout << "\n select a x coordinate (top number) between one and ten: "; cin >> friendlyShips[i].xCord; malfunction(); assert(cin); --friendlyShips[i].xCord;
			cout << "\n select a y coordinate (side number) between one and ten: "; cin >> friendlyShips[i].yCord; malfunction(); assert(cin); --friendlyShips[i].yCord;
			cout << "\n select a direction, enter 1 for vertical and 2 for horizontal: "; cin >> friendlyShips[i].direction; malfunction(); assert(cin);
			break;
		case 3: cout << "\n You will now be placing the Submarine, it is 3 spaces long. \n";
			cout << "\n select a x coordinate (top number) between one and ten: "; cin >> friendlyShips[i].xCord; malfunction(); assert(cin); --friendlyShips[i].xCord;
			cout << "\n select a y coordinate (side number) between one and ten: "; cin >> friendlyShips[i].yCord; malfunction(); assert(cin); --friendlyShips[i].yCord;
			cout << "\n select a direction, enter 1 for vertical and 2 for horizontal: "; cin >> friendlyShips[i].direction; malfunction(); assert(cin);
			break;
		case 4: cout << "\n You will now be placing the Destroyer, it is 2 spaces long. \n";
			cout << "\n select a x coordinate (top number) between one and ten: "; cin >> friendlyShips[i].xCord; malfunction(); assert(cin); --friendlyShips[i].xCord;
			cout << "\n select a y coordinate (side number) between one and ten: "; cin >> friendlyShips[i].yCord; malfunction(); assert(cin); --friendlyShips[i].yCord;
			cout << "\n select a direction, enter 1 for vertical and 2 for horizontal: "; cin >> friendlyShips[i].direction; malfunction(); assert(cin);
			break;
		}

		//This section detects bad inputs.
		//This makes sure that the direction inputed is either one or two.
		switch (friendlyShips[i].direction) 
		{
		 case 1: break;
		 case 2: break;
		 default: cout << "\n that was a bad direction please try again \n";  --i; continue;
			break;
		}
		//This makes sure the inputed x is valid.
		if (friendlyShips[i].xCord < 0 || friendlyShips[i].xCord > 9)
		{
			cout << "\n that was a bad x coordinate please try again \n";  --i; continue;
		}
		//This makes sure the inputed y is valid.
		if (friendlyShips[i].yCord < 0 || friendlyShips[i].yCord > 9)
		{
			cout << "\n that was a bad y Cordinate please try again \n";  --i; continue;
		}

		//This section initializes ships to the grid.
		//This int helps determine if the ships placed overlap.
		int crash = 0;

		//The initializeShips function is called.
		initializeShips(friendlyShips, grid1, crash, i);

		//If there is a crash, then i is minuses and the loop starts over.
		if (crash > 0)
		{
			cout << "\nYou can not overlap ships, please try again\n";
			i--;
			continue;
		}
		// gridDisplay is called and the ship on the grid is outputed.
		gridDisplay(grid1);
	}
}

//This function takes a computer generated input and puts the information 
//into an array, which display as ships on water. 
void placingEnemyShips(fleet enemyShips[], char grid2[][10])
{
	cout << "\nThe enemy ships are now being randomized. \n \n"; 

	for (int i = 0; i < 5; i++) //This for loop runs through the different ships.
	{
		// These random ints are initialized.
		int randomX = rand() % 10;
		int randomY = rand() % 10;
		int randomDirection = rand() % 2+1;

		//Each time the loop executes the new ship is assigned with
		//random coordinates and a random direction.
		switch (i)
		{
		 case 0: enemyShips[i].xCord = randomX; enemyShips[i].yCord = randomY; enemyShips[i].direction = randomDirection;
			 break;
		 case 1: enemyShips[i].xCord = randomX; enemyShips[i].yCord = randomY; enemyShips[i].direction = randomDirection;
			 break;
		 case 2: enemyShips[i].xCord = randomX; enemyShips[i].yCord = randomY; enemyShips[i].direction = randomDirection;
			 break;
		 case 3: enemyShips[i].xCord = randomX; enemyShips[i].yCord = randomY; enemyShips[i].direction = randomDirection;
			 break;
		 case 4:; enemyShips[i].xCord = randomX; enemyShips[i].yCord = randomY; enemyShips[i].direction = randomDirection;
			 break;
		}

		//This section initializes ships to the grid.
		//This int helps determine if the ships placed overlap.
		int crash = 0;

		//The initializeShips function is called.
		initializeShips(enemyShips, grid2, crash, i);

		//If there is a crash, then i is minuses and the loop starts over.
		if (crash > 0)
		{
			cout << "The computer is bad at placing ships it is now trying again\n";
			i--;
			continue;
		}
	
	}
}
	
//This function determines how the ship will be placed, prevents ships from
//overlaping, and lastly assigns all of the coordinates of the ship to the grid.
void initializeShips(fleet Ships[], char grid[][10], int& crash, int i)
{
	//This helps determine which direction the ship will be placed.
	int boundCheck = (10 - Ships[i].size);

	//The switch statement determines if the ship is being placed
	//horrizontal or vertical.
	switch (Ships[i].direction)
	{
	case 1:
		if (Ships[i].yCord <= boundCheck) //This means the ship is going to the right.
		{
			for (int n = 1; n <= Ships[i].size; n++) //This loop checks to see if the ships overlap.
			{
				if (grid[Ships[i].yCord][Ships[i].xCord] == '#')
				{
					crash++;
				}

				Ships[i].yCord++;

			}
			if (crash > 0) //If there is an overlap, than the function is exited
			{
				break;
			}
			for (int n = 1; n <= Ships[i].size; n++) //The coordinates of the ship are changed back to the first coordinate.
			{
				Ships[i].yCord--;
			}
			for (int n = 1; n <= Ships[i].size; n++) //This loop goes through each ship coordinate and sets the grid value equal to a ship.
			{
				grid[Ships[i].yCord][Ships[i].xCord] = '#';
				Ships[i].yCord++;
			}
			--Ships[i].yCord;
		}
		else //If the ship can not be placed to the right it will go to the left.
		{
			for (int n = 1; n <= Ships[i].size; n++) //This loop checks to see if the ships overlap
			{
				if (grid[Ships[i].yCord][Ships[i].xCord] == '#') 
				{
					crash++;
				}

				Ships[i].yCord--;

			}
			if (crash > 0) //If there is an overlap, than the function is exited
			{
				break;
			}
			for (int n = 1; n <= Ships[i].size; n++) //The coordinates of the ship are changed back to the first coordinate.
			{
				Ships[i].yCord++;
			}
			for (int n = 1; n <= Ships[i].size; n++) //This loop goes through each ship coordinate and sets the grid value equal to a ship.
			{
				grid[Ships[i].yCord][Ships[i].xCord] = '#';
				Ships[i].yCord--;
			}
			++Ships[i].yCord;
		}
		break;
	case 2:
		if (Ships[i].xCord <= boundCheck) //This means the ship is going down.
		{
			for (int n = 1; n <= Ships[i].size; n++) //This loop checks to see if the ships overlap
			{
				if (grid[Ships[i].yCord][Ships[i].xCord] == '#')
				{
					crash++;
				}

				Ships[i].xCord++;

			}
			if (crash > 0) //If there is an overlap, than the function is exited
			{
				break;
			}
			for (int n = 1; n <= Ships[i].size; n++) //The coordinates of the ship are changed back to the first coordinate.
			{
				Ships[i].xCord--;
			}
			for (int n = 1; n <= Ships[i].size; n++) //This loop goes through each ship coordinate and sets the grid value equal to a ship.
			{
				grid[Ships[i].yCord][Ships[i].xCord] = '#';
				Ships[i].xCord++;
			}
			--Ships[i].xCord;
		}
		else //If the ship can not go down it will go up.
		{
			for (int n = 1; n <= Ships[i].size; n++) //This loop checks to see if the ships overlap
			{
				if (grid[Ships[i].yCord][Ships[i].xCord] == '#')
				{
					crash++;
				}

				Ships[i].xCord--;

			}
			if (crash > 0) //If there is an overlap, than the function is exited
			{
				break;
			}
			for (int n = 1; n <= Ships[i].size; n++) //The coordinates of the ship are changed back to the first coordinate.
			{
				Ships[i].xCord++;
			}
			for (int n = 1; n <= Ships[i].size; n++) //This loop goes through each ship coordinate and sets the grid value equal to a ship.
			{
				grid[Ships[i].yCord][Ships[i].xCord] = '#';
				Ships[i].xCord--;
			}
			++Ships[i].xCord;
		}
		break;
	}
}

//This function runs a loop where the player and com take turns guessing 
//coordinates trying to destroy each others ships. This function also
//checks to see if either the player or computer wins.
void battlePhase(fleet friendlyShips[], fleet enemyShips[], char grid1[][10], char grid2[][10], char grid3[][10], char grid4[][10], int& wins, int& losses)
{
	//The point system is initialized.
	int playerPoints = 0;
	int comPoints = 0;
	bool winCheck = true;//winCheck is set to true.

	//This outputs instructions.
	cout << "You are now entering the battle phase, where you will input\ncoordinates in order to guess the location of the enemy ships.\n";
	cout << "Also, H stands for hit and M stands for miss.\n";

	//The guessing loop is entered.
	while (winCheck)
	{
		int guessX;
		int guessY;

		//This outputs a reference grid to the screen, so the player can look at
		//ther guesses.
		cout << "\nThis grid displays your guesses.\n";
		gridDisplay(grid3);

		//This allows the player to input their guesses, and then
		//brings them down to the array value.
		cout << "\nIt is time to attack!" << "\n\nplease enter a x coordinate: ";
		cin >> guessX; guessX--; malfunction(); assert(cin);
		cout << "\nplease enter a y coordinate: ";
		cin >> guessY; guessY--; malfunction(); assert(cin);

		//This checks to make sure all guesses are valid.
		if (guessX < 0 || guessX > 9)
		{
			cout << "\nThat is a bad x coordinate, pleas try again.\n"; continue;
		}
		if (guessY < 0 || guessY > 9)
		{
			cout << "\nThat is a bad y coordinate, pleas try again.\n"; continue;
		}

		//This checks to see if a enemy ship was hit, or if water was hit,
		//or if the player guessed the same coordinate.
		switch (grid2[guessY][guessX])
		{
		case '~': grid2[guessY][guessX] = 'M'; grid3[guessY][guessX] = 'M';
			cout << "\nMiiiissss!!\n";
			 break;
		case '#': playerPoints++;  grid2[guessY][guessX] = 'H'; grid3[guessY][guessX] = 'H';
			checkShip(enemyShips, grid2, guessX, guessY);
			cout << "\nYou hit the enemy ship, nice!\n";
			break;
		 default: cout << "\nYou already guessed there, please try again\n"; continue;
			 break;
		}
		//This shows where the player guessed
		gridDisplay(grid3);

		// This outputs a message to the screen telling the player that they
		//destroyed the enemy Ship
		for (int i = 0; i < 5; i++)
		{
			if (enemyShips[i].health == 0)
			{
				cout << "\nYou made an enemy ship go boom!\n ";
				enemyShips[i].health++;
			}
		}
		
		//This calls surrender function.
		surrender(winCheck, losses);
		if (winCheck == false)
		{
			break;
		}

		bool redo = true;
		while(redo)
		{
			int randGuessX = rand() % 10;
				int randGuessY = rand() % 10;

			cout << "\nthe enemy guessed the coordinates: " << randGuessX << ", " << randGuessY;

			// This checks to see if the enemy hits the player's ships, water
			// or if they guessed the same spot twice.
			switch (grid1[randGuessY][randGuessX])
			{
			case '~': grid1[randGuessY][randGuessX] = 'M'; grid4[randGuessY][randGuessX] = 'M';
				cout << "\nThe computer missed!!\n"; redo = false;
				break;
			case '#': comPoints++; grid1[randGuessY][randGuessX] = 'H'; grid4[randGuessY][randGuessX] = 'H';
				checkShip(friendlyShips, grid1, randGuessX, randGuessY);
				cout << "\nYou were hit by the enemy, haha.\n"; redo = false;
				break;
			default: cout << "\nThe computer messed up and is now guesssing again.\n"; 
				break;
			}

		} 
		//This displays enemy guess by itself.
		cout << "\nThis is where the enemy guessed. \n";
		gridDisplay(grid4);

		//This displays enemy guess on the players grid.
		cout << "\nThis is where the enemy hit. \n";
		gridDisplay(grid1);

		//This checks to see if the player won.
		if (playerPoints == 17)
		{
			cout << "\nCongratulations you win!\n";
			winCheck = false;
			wins++;
		}
		//This checks to see if the computer won.
		if (comPoints == 17)
		{
			cout << "\nHow could you possibly lose? I would reccomend you take a long walk and think about life.\n";
			winCheck = false;
			losses++;
		}
		//This calls the srrender function.
		surrender(winCheck, losses);
	}
}

void checkShip(fleet Ships[], char grid[][10], int X, int Y)
{
	for (int i = 0; i < 5; i++)
	{
		int boundCheck = (10 - Ships[i].size);

		switch (Ships[i].direction)
		{
		case 1:
			if (Ships[i].yCord > boundCheck)
			{
				for (int n = 1; n <= Ships[i].size; n++)
				{
					if (Ships[i].xCord == X && Ships[i].yCord == Y)
					{
						Ships[i].health--;
					}
					Ships[i].yCord--;
				}
				for (int n = 1; n <= Ships[i].size; n++)
				{
					Ships[i].yCord++;
				}
			}
			else
			{
				for (int n = 1; n <= Ships[i].size; n++)
				{
					if (Ships[i].xCord == X && Ships[i].yCord == Y)
					{
						Ships[i].health--;
					}
					Ships[i].yCord++;
				}
				for (int n = 1; n <= Ships[i].size; n++)
				{
					Ships[i].yCord--;
				}
			}
		 case 2:
			if (Ships[i].xCord > boundCheck)
			{
				for (int n = 1; n <= Ships[i].size; n++)
				{
					if (Ships[i].xCord == X && Ships[i].yCord == Y)
					{
						Ships[i].health--;
					}
					Ships[i].xCord--;
				}
				for (int n = 1; n <= Ships[i].size; n++)
				{
					Ships[i].xCord++;
				}
			}
			else
			{
				for (int n = 1; n <= Ships[i].size; n++)
				{
					if (Ships[i].xCord == X && Ships[i].yCord == Y)
					{
						Ships[i].health--;
					}
					Ships[i].xCord++;
				}
				for (int n = 1; n <= Ships[i].size; n++)
				{
					Ships[i].xCord--;
				}
			}
			break;
		}
	}
}

//This function asks the player if they want to surrender or continue
// and then has them input a c or a s.
void surrender(bool& winCheck, int& losses)
{
	//This loop runs untill a valid option is entered.
	bool redo = true;
	while (redo)
	{
		char surrender;
		cout << "\npress c to continue or press s to surrender: ";
		cin >> surrender; assert(cin);

		switch (surrender)
		{
		case 'c': redo = false; //Nothing happens except the loop is exited.
			break;
		case 's': winCheck = false; redo = false; //The loop is exited and winCheck is changed to false.
			losses++;
			break;
		default: cout << "\nThat was not an option please try again.\n";
			break;
		}
	} 
}

// This function outputs an error message.
void malfunction()
{
	if (!cin)
	{
		cout << "\nMalfuunction!! Malfunction!! This device will now explode.";
	}
}