//Lab 3 - Dice Game - Jed Davies
#include <iostream>
#include <string>
using namespace std;

//Structure Definitions
struct Player {
	string name;
	int score;
	int total;

	//Constructor
	Player(string n = "", int s = 0, int t = 0) {
		name = n;
		score = s;
		total = t;
	}
};

struct Dice {// With one member for each dice and another for the value of the total throw
	int dice1;
	int dice2;
	int throw_value;//This member name is required by the question. I found no need to calculate the value of a throw in total, so I use it to count how many throws the players have each had. If the question did not require this name I would use roll_counter
	int target_score;
	int winner_or_tie;

	//Constructor
	Dice(int d1 = 0, int d2 = 0, int tv = 0, int ts = 0, int wot = 0) {
		dice1 = d1;
		dice2 = d2;
		throw_value = tv;
		target_score = ts;
		winner_or_tie = wot;
	}
};

//Function Prototypes
void asterisks(int* number);//This function demonstrates use of pointers as arguments
void main_menu(Player* p1, Player* p2, Dice* d);
void roll(Player* p1, Player* p2, Dice* d);
Dice* target_check(Player* p1, Player* p2, Dice* d);

int main() {
	Player player1, player2;
	Dice dice;
	main_menu(&player1, &player2, &dice);//I pass these arguments through my functions to keep the data at all stages of the program
}

//Function Definitions
void asterisks(int* number) {
	cout << "\n";
	for (int i = 0; i < *number; i++){//The asterisk is the dereference operator, accessing the value of num for the comparison
		cout << "*";
	}
	cout << "\n";
}

//Main Menu Function, including game title
void main_menu(Player* p1, Player* p2, Dice* d) {
	Player player1 = *p1;//Within each function I dereference these instances of structures so I can use them easily
	Player player2 = *p2;
	Dice dice = *d;

	srand(time(NULL));//Sets the randon seed based on time

	//Header
	cout << "\n\nTwo Player Dice Game - Pre set Maximum Score";//I have preserved some peculiarities of the example output throughout, such as the odd capitalisation here, many spaces either side of colons and more.
	int num = 53;//Number of asterisks we want
	int* number = &num;//Creates pointer to memory addess of num
	asterisks(number);//Passes that memory address into the function
	
	//Menu display and input
	string selection;//Although the only valid inputs for the menu are integers, the code recursed when I entered anyhting other than an int into this variable when it had the int datatype. By making it a string I could use an else at the end of my if menu to alert users when they entered the wrong input.
	cout << "\n1. Instructions\n2. Set Maximum Score\n3. Read Players\n4. Play\n5. Display ScoreBoard\n6. End\n\nEnter your option :  ";
	cin >> selection;//No getline is needed because any unput with a space between words would be invalid anyway and they are still sent to the else statement
	
	//Menu logic
	if (selection == "1") {
		cout << "\n\n\t\t\tInstruction\n";
		num = 70;
		asterisks(number);//This pointer will still point to the correct memory address even though the value has changed - no need to reassign it
		//The line below is a long output for instructions
		cout << "1. Players must feed their names and pre-set the Maximum score before game starts.\n2. Each player has two 6 face dice to roll, and the players get turns to earn score.\n3. For each roll, dice 1 and dice 2 values will be added for the corresponding player.\n4. If both dice values are same then the score will be two times the sum of the value\n\tEg : dice 1 returns 2 and dice 2 returns 2 then 2+2 = 4 *2 = 8 .\n5. Whoever reaches the maximum score first will be declared winner,\n\tand the game will be finished.\n6. After each roll, each player score board will be updated and displayed.";
		asterisks(number);
		main_menu(&player1, &player2, &dice);
	}
	else if (selection == "2") {
		cout << "Enter the Maximum score : ";
		cin >> dice.target_score;
		cout << "\n";
		main_menu(&player1, &player2, &dice);
	}
	else if (selection == "3") {
		cout << "Enter Player1 name : ";
		Player player1;
		cin.ignore();
		getline(cin, player1.name);
		cout << "Enter Player2 name : ";
		Player player2;
		getline(cin, player2.name);
		main_menu(&player1, &player2, &dice);
	}
	else if (selection == "4") {
		if (dice.target_score == 0) {//Maximum score validation
			asterisks(number);
			cout << "You need to set a target score first";
			asterisks(number);
			main_menu(&player1, &player2, &dice);
		}
		if (player1.name == "" || player2.name == "") {//Name validation
			asterisks(number);
			cout << "You need to set names for both players first";
			asterisks(number);
			main_menu(&player1, &player2, &dice);
		}
		roll(&player1, &player2, &dice);
		main_menu(&player1, &player2, &dice);
	}
	else if (selection == "5") {
		if (dice.winner_or_tie == 0) {//Game played validation
			asterisks(number);
			cout << "You must play a game before viewing the scoreboard.";
			asterisks(number);
			main_menu(&player1, &player2, &dice);
		}
		else {
			cout << "\n\n\n\t\t\tScore Board\n";
			asterisks(number);
			cout << "\nFinal score of " << player1.name << "  is " << player1.total << "\n\nFinal score of " << player2.name << "  is " << player2.total << "\n\n Winner\t";
			if (dice.winner_or_tie == 1) {//This value is a flag for who won or if there was a tie
				cout << player1.name;
			}
			else if (dice.winner_or_tie == 2) {
				cout << player2.name;
			}
			else {
				cout << "TIE";
			}
			cout << " Congrats !!!!!";
		}
		main_menu(&player1, &player2, &dice);
	}
	else if (selection == "6") {
		exit(0);//Exits the program
	}
	else {//Happens when someone enters anything other than a number 1-6 inclusive tot he main menu
	asterisks(number);
	cout << "Error: Unrecognized input. Please make sure to enter only a number from 1 to 6 inclusive and press enter.\n";
	asterisks(number);
	main_menu(&player1, &player2, &dice);
	}
}

//Dice Rolling Function
void roll(Player* p1, Player* p2, Dice* d) {
	Player player1 = *p1;
	Player player2 = *p2;
	Dice dice = *d;
	dice.throw_value++;//Counter for how many rolls each

	//Rolling and outptuting for player 1
	dice.dice1 = rand() % 6 + 1;
	dice.dice2 = rand() % 6 + 1;
	cout << "\n\n\n" << player1.name << " Roll " << dice.throw_value << "\n\n Dice1 : " << dice.dice1 << "\n Dice2 : " << dice.dice2;
	player1.score = dice.dice1 + dice.dice2;
	if (dice.dice1 == dice.dice2) {//Doubles score if rolling a pair
		player1.score = player1.score * 2;
	}
	player1.total = player1.total + player1.score;//Tracks total score over multiple rolls
	cout << "\n Player1 Score : " << player1.score << "\n Player1 total : " << player1.total;

	//Rolling and outputting for player 2
	dice.dice1 = rand() % 6 + 1;//Totals are stored and roll values output already, so we can overwrite these same values
	dice.dice2 = rand() % 6 + 1;
	cout << "\n\n\n" << player2.name << " Roll " << dice.throw_value << "\n\n Dice1 : " << dice.dice1 << "\n Dice2 : " << dice.dice2;
	player2.score = dice.dice1 + dice.dice2;
	if (dice.dice1 == dice.dice2) {
		player2.score = player2.score * 2;
	}
	player2.total = player2.total + player2.score;
	cout << "\n Player1 Score : " << player2.score << "\n Player1 total : " << player2.total;

	//Winner check
	if (player1.total < dice.target_score && player2.total < dice.target_score) {//No winner yet
		cout << "\n";
		system("pause");//This function create a 'press any key to continue'. For macs, it would need to take the argument "read" instead. I am not certain how to code exactly what we see in the example output - a custom message for a "press any key" prompt. I found myself choosing between this and a cin for a variable. The latter would only continue if the enter key was pressed so I felt this was the beeter reflection of the requested program.
		roll(&player1, &player2, &dice);
	}
	else {//If someone wins this runs a function to determine who then records that info via a flag in the dice instance of the Dice structure
		Dice* winner_info = target_check(&player1, &player2, &dice);//This function returns a memory address as requested in the assignment brief
		dice = *winner_info;//This dereferences the address so we can use the value
	}
	main_menu(&player1, &player2, &dice);
}

//Winner Flag Function
Dice* target_check(Player * p1, Player * p2, Dice * d){
	Player player1 = *p1;
	Player player2 = *p2;
	Dice dice = *d;
	if (player1.score > player2.score) {
		dice.winner_or_tie = 1;
	}
	else if (player1.score < player2.score) {
		dice.winner_or_tie = 2;
	}
	else {//This else statement covers instances where the scores are tied
		dice.winner_or_tie = 3;
	}
	return (&dice);//Returning address. The other functions tend to 'end' by running functions, passing the instances of structures as arguments for continuity of data, however this function only makes chages on the dice instance of the Dice structure, making it the best candidate for
}