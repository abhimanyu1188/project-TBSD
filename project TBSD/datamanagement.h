#pragma once
#include "blackjack.h"
#include <stdbool.h>

void initializeDeck(PCard* deck);
void freeDeck(PCard deck);
void freePlayer(PPlayer player);
bool saveGame(PPlayer players, int numPlayers, PPlayer dealer, const char* filename);
bool loadGame(PPlayer players, int numPlayers, PPlayer dealer, const char* filename);
