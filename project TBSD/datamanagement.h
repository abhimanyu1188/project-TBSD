#pragma once
#include "blackjack.h"

void initializeDeck(PCard* deck);
void freeDeck(PCard deck);
void freePlayer(PPlayer player);
void saveGame(PPlayer players, int numPlayers, PPlayer dealer, const char* filename);
void loadGame(PPlayer players, int numPlayers, PPlayer dealer, const char* filename);
