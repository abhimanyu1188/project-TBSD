#pragma once

#include "blackjack.h"

int displayMainMenu();
int displayPlayerCountMenu();
void addChipsToPlayer(PPlayer player);
int checkCurrentBalance(PPlayer player);
void printCard(Card card);
void printHand(PPlayer player);
void playGame(PPlayer player, PPlayer dealer, PCard deck, int* top);
void playRound(PPlayer players, int numPlayers, PPlayer dealer, PCard deck, int* top); // Placeholder for future implementation

