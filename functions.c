#include "game.h"

//To show the complete menu of the game
void showMenu() {
    printf("\033[1;36m========================================\n");
	printf("         WELCOME TO THE DICE GAME       \n");
	printf("========================================\033[0m\n");
	printf("1. Play Game\n");
    printf("2. View Leaderboard\n");
    printf("3. View Players Profile\n");
	printf("4. View Rules\n");
    printf("5. Exit\n");
    printf("========================================\n");
}

//To switch the turn when user roll 1
int switchTurn(int currentTurn) {
    if (currentTurn == 0) {
        return 1;
    } else {
        return 0;
    }
}

//To visualize user the loading effect of rolling dice and generating random number
int rollTheDice(char player[]) {
    printf("Rolling the dice");
    for(int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        Sleep(400);
    }
    printf("\n");
    srand(time(NULL));
    int result = rand() % 6 + 1;
    printf("\033[1;36m%s rolled a: %d\033[0m\n",player, result);
	printDice(result);

	return result;
}

//To show the picture of dice based on the number rolled
void printDice(int roll) {
	if (roll == 1) {
		printf("\033[1;37m+-------+\n");
        printf("|       |\n");
        printf("|   O   |\n");
        printf("|       |\n");
        printf("+-------+\033[0m\n");
	} else if (roll == 2) {
		printf("\033[1;37m+-------+\n");
        printf("| O     |\n");
        printf("|       |\n");
        printf("|     O |\n");
        printf("+-------+\033[0m\n");
	} else if (roll == 3) {
		printf("\033[1;37m+-------+\n");
        printf("| O     |\n");
        printf("|   O   |\n");
        printf("|     O |\n");
        printf("+-------+\033[0m\n");
	} else if (roll == 4) {
		printf("\033[1;37m+-------+\n");
        printf("| O   O |\n");
        printf("|       |\n");
        printf("| O   O |\n");
        printf("+-------+\033[0m\n");
	} else if (roll == 5) {
		printf("\033[1;37m+-------+\n");
        printf("| O   O |\n");
        printf("|   O   |\n");
        printf("| O   O |\n");
        printf("+-------+\033[0m\n");
	} else if (roll == 6) {
		printf("\033[1;37m+-------+\n");
        printf("| O   O |\n");
        printf("| O   O |\n");
        printf("| O   O |\n");
        printf("+-------+\033[0m\n");
	}
}

//To put a time limit on any prompt, and after that specific time default choice will be executed
char getTimedChoice(int secondsLimit, const char *prompt) {
  time_t startTime = time(NULL);
  printf("%s (Timeout in %d seconds): ", prompt, secondsLimit);

  while (1) {
	if (kbhit()) {
		char c = getch();
        if (c >= 'a' && c <= 'z') c -= 32; 
        printf("%c\n", c);
        return c;
	}

	if ((int)(time(NULL) - startTime) >= secondsLimit) {
            printf("\n\033[1;31m[⏰ Time's up! Defaulting choice]\033[0m\n");
            return 'X'; 
    }
  }
}

//To open shop for user
void openShop(char name[], int *coins, int *shields, int *rerolls, int *doublePoints) {
	int shopChoice;
	do {
		system("cls");
		printf("\n========================================\n");
        printf("         WELCOME TO THE ITEM SHOP       \n");
        printf("========================================\n");
        printf("Player: %s | Available Coins: %d \n", name, *coins);
        printf("1. Buy Shield (+1)        - Cost: 5 coins\n");
        printf("2. Buy Reroll Token (+1)  - Cost: 4 coins\n");
        printf("3. Buy Double Points (+1) - Cost: 6 coins\n");
        printf("4. Exit Shop & Roll\n");
        printf("========================================\n");
        printf("Enter your choice (1-4): ");
		scanf("%d", &shopChoice);

		switch (shopChoice) {
			case 1:
			 if (*coins >= 5) {
				*coins -= 5;
				(*shields)++;
				printf("\033[1;32mSuccessfully bought a Shield!\033[0m\n");
			 } else {
				printf("\033[1;31mNot enough coins!\033[0m\n");
			 }
             Sleep(1000);
			 break;
			case 2:
			 if (*coins >= 4) {
				*coins -= 4;
				(*rerolls)++;
                printf("\033[1;32mSuccessfully bought a Reroll!\033[0m\n");
			 } else {
				printf("\033[1;31mNot enough coins!\033[0m\n");
			 }
			 Sleep(1000);
			 break;
			case 3:
			 if (*coins >= 6) {
				*coins -= 6;
				(*doublePoints)++;
                printf("\033[1;32mSuccessfully bought a Double Points!\033[0m\n");
			 } else {
				printf("\033[1;31mNot enough coins!\033[0m\n");
			 }
             Sleep(1000);
			 break;
			case 4:
			 break;
			default:
			 printf("\033[1;31mInvalid choice!\033[0m\n");
             Sleep(1000);
		}


	} while (shopChoice != 4);

	system("cls");
}

//To save winner's name and score
void saveHighScore(char playerName[], int score) {
	FILE *file = fopen("leaderboard.txt", "a");

	if (file == NULL) {
		printf("Error opening file for saving high score!\n");
		return;
	} 

	fprintf(file, "Winner: %s | Score: %d\n", playerName, score);
	fclose(file);
	printf("Game result successfully saved to 'leaderboard.txt' !\n");
}

//To view all the winners and their scores
void viewLeaderboard() {
	system("cls");
	printf("\n========================================\n");
    printf("            LEADERBOARD / HISTORY       \n");
    printf("========================================\n");

    FILE *file = fopen("leaderboard.txt", "r");
	if (file == NULL) {
		printf("No past game record found yet! \n");
	} else {
        char ch;
        while((ch=fgetc(file))!=EOF){
            putchar(ch);
        }
    }
        
    
	printf("\n========================================\n");
    printf("Press any key to return to the main menu...");
    getch();
}

//To display games rules to user
void rules() {
    system("cls");
    FILE *file = fopen("rules.txt", "r");
    if (file == NULL) {
        printf("Rules file doesn't exits!\n");
    } else {
        char ch;
        while((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
    }
    fclose(file);
    printf("\n========================================\n");
    printf("Press any key to return to the main menu...");
    getch();
}

//To update each players stats
void updatePlayerProfile(char playerName[],int finalScore,int isWinner){
 struct PlayerProfile profiles[100];
 int count, found;
 count = found = 0;
 FILE *file = fopen("profiles.txt", "r");
 if(file != NULL) {
    while(count < 100 && fscanf(file,"%s %d %d %d", profiles[count].name,&profiles[count].gamesPlayed,&profiles[count].wins,&profiles[count].highScore) == 4){
        count++;
    }
    fclose(file);
 }

 for(int i = 0; i < count; i++) {
    if (strcmp(profiles[i].name, playerName) == 0) {
        profiles[i].gamesPlayed++;
        
        if (isWinner){
            profiles[i].wins++;
        }
        if (finalScore > profiles[i].highScore) {
            profiles[i].highScore = finalScore;
        }

        found = 1;
        break;
    }
 }

 //New profile if player does not exist
 if (!found && count < 100) {
    strcpy(profiles[count].name, playerName);
    profiles[count].gamesPlayed = 1;
    profiles[count].wins = isWinner ? 1 : 0;
    profiles[count].highScore = finalScore;
    count++;
 }

 //Rewrite all profiles back to profiles.txt
 file = fopen("profiles.txt","w");
 if (file == NULL){
    printf("Error opening profiles file for updating!\n");
    return;
 }

 for (int i = 0;i <count; i++){
    fprintf(file, "%s %d %d %d\n", profiles[i].name,profiles[i].gamesPlayed,profiles[i].wins,profiles[i].highScore);
 }
 fclose(file);
}

void viewPlayerProfile(){
 system("cls");
 printf("\n========================================\n");
 printf("         PLAYER CAREER PROFILES         \n");
 printf("========================================\n");

 FILE *file = fopen("profiles.txt", "r");

 if (file == NULL) {
    printf("No player profiles recorded yet!\n");
 } else {
    struct PlayerProfile p;
    printf("%-15s | %-6s | %-5s | %-10s\n", "Name", "Played", "Wins", "High Score");
    printf("------------------------------\n");

    while(fscanf(file,"%s %d %d %d", p.name, &p.gamesPlayed, &p.wins, &p.highScore) == 4) {
        printf("%-15s | %-6d | %-5d | %-10d\n",p.name,p.gamesPlayed,p.wins,p.highScore);       
    }
    fclose(file);

 }
 
    printf("\n========================================\n");
    printf("Press any key to return to the main menu...");
    getch();
}
