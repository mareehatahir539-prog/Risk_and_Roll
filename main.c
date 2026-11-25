#include "game.h"

//Main start of the game
int main() {
	int choice;
	do {
		system("cls");
		showMenu();
		printf("Enter your choice: \n");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
			 startGame();
			 break;
			case 2:
			 viewLeaderboard();
			 break;
			case 3:
			 viewPlayerProfile();
			 break;
			case 4:
			 rules();
			 break;
			case 5:
			 printf("\nThanks for playing! Goodbye.\n");
			 break;
			default:
			 printf("\nInvalid choice! Please choose between 1 and 5.\n");
             printf("Press any key to continue...");
             getch();
			 break;
		}
	} while (choice != 5);
	return 0;
}


//Main game logic function
void startGame() {
	int playerScore[2] = {0, 0};
	char playersName[2][50];
	int shields[2] = {1,1};
	int rerolls[2] = {1,1};
	int doublePoints[2] = {1,1};
	int coins[2] = {6,6};
	char continueRolling;
	int playerTurn = 0;
	int rollDice;
	
	printf("\n------- PLAYERS REGISTRATION -------\n");
	printf("Enter player 1 name: \n");
	scanf("%s", playersName[0]);
	printf("Enter player 2 name: \n");
	scanf("%s", playersName[1]);

	printf("\n======= GAME START =======\n");
	
	
	while(playerScore[0] < 100 && playerScore[1] < 100) {
		start:
		printf("----------------------------------------\n");
		printf("\033[1;33m>>>%s's TURN <<<\033[0m\n", playersName[playerTurn]);
		printf("\033[1;33m%s's current score is: %d\033[0m\n", playersName[playerTurn], playerScore[playerTurn]);
		printf("\033[1;33m%s's Inventory -> Shields: %d | Rerolls: %d | Double Points: %d\033[0m\n",playersName[playerTurn], shields[playerTurn], rerolls[playerTurn], doublePoints[playerTurn]);

		char actionChoice = getTimedChoice(10, "[S] Open Shop | [Any Other Key] Roll Dice");

		if (actionChoice == 'S') {
			openShop(playersName[playerTurn], &coins[playerTurn], &shields[playerTurn], &rerolls[playerTurn], &doublePoints[playerTurn]);
			printf("----------------------------------------\n");
			printf("\033[1;33m>>>%s's TURN (Resuming) <<<\033[0m\n", playersName[playerTurn]);
			printf("\033[1;33m%s's score: %d | Coins: %d \033[0m\n", playersName[playerTurn], playerScore[playerTurn], coins[playerTurn]);
		}
		
		rollDice = rollTheDice(playersName[playerTurn]);
		coins[playerTurn] += 2;

		if (rerolls[playerTurn] > 0) {
            char useItemChoice = getTimedChoice(5, "Do you want to use your Reroll token? (Y/N)");
            
            if (useItemChoice == 'Y') {
                rerolls[playerTurn]--;
                printf("Reroll token used! Rolling again");
				for (int i = 0; i < 3; i++) {
					printf(".");
		            fflush(stdout);
		            Sleep(400);
	            }
                printf("\n");
                rollDice = rand() % 6 + 1; 
				printf("\033[1;36mYou rolled a: %d\033[0m\n", rollDice);
                printDice(rollDice);       
            }
        }

		if (doublePoints[playerTurn] > 0) {
			char useDoublePoint = getTimedChoice(5, "Do you want to use your Double Point token? (Y/N)");

			if (useDoublePoint == 'Y') {
				doublePoints[playerTurn]--;
				rollDice = rollDice * 2;
				printf("\033[1;32mDouble point token used! Roll value doubled.\033[0m\n");
			}
		}
		
		if(rollDice == 1) {
			if (shields[playerTurn] > 0) {
				printf("\033[1;32mOh no! You rolled a 1, but your Shield blocked the penalty!\033[0m\n");
                shields[playerTurn]--;
			} else {
				Beep(1000, 500);
				printf("\033[1;31mOh no! %s rolled a 1! Score resets to 0.\033[0m\n", playersName[playerTurn]);
				printf("Switching turn to the next player...\n\n");
				playerScore[playerTurn] = 0;
				playerTurn = switchTurn(playerTurn);
				goto start;
			}
	    } else {
	    	playerScore[playerTurn] += rollDice;
	    }
		
		if (playerScore[playerTurn] >= 100) {
			Beep(523, 200);
			Beep(659, 200);
			Beep(784, 400);
			printf("\033[1;32mCONGRATULATIONS! Player %s WINS the game with a score of %d!\033[0m\n", playersName[playerTurn], playerScore[playerTurn]);

			saveHighScore(playersName[playerTurn], playerScore[playerTurn]);

			//Update career profile for both players:
			//For winner
			updatePlayerProfile(playersName[playerTurn],playerScore[playerTurn],1);
			//For loser
			int loserTurn = switchTurn(playerTurn);
			updatePlayerProfile(playersName[loserTurn],playerScore[loserTurn],0);


			printf("\nPress any key to return to the main menu...");
            getch();

			break;		
		}
		
		printf("\nDo you want to hold score and switch turn [Y] or continue rolling [N]?: ");
		scanf(" %c", &continueRolling);
		
		if (continueRolling == 'Y' || continueRolling == 'y') {
			printf("\033[1;32m%s holds. Score %d is safely stored. Switching turn.\033[0m\n\n", playersName[playerTurn], playerScore[playerTurn]);
			playerTurn = switchTurn(playerTurn);
		} else if (continueRolling == 'N' || continueRolling == 'n') {
			printf("%s chooses to roll again!\n\n", playersName[playerTurn]);
			continue;
		}
	}
}
