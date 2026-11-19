#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//Every Player's profile structure
struct PlayerProfile {
    char name[50];
    int gamesPlayed;
    int wins;
    int highScore;
};

//Functions Prototypes
void showMenu();
void startGame();
int switchTurn(int currentTurn);
int rollTheDice(char player[]);
void printDice(int roll);
char getTimedChoice(int secondsLimit, const char *prompt);
void openShop(char name[], int *coins, int *shields, int *rerolls, int *doublePoints);
void saveHighScore(char playerName[], int score);
void viewLeaderboard();
void updatePlayerProfile(char playerName[], int finalScore, int isWinner);
void viewPlayerProfile();
void rules();

#endif