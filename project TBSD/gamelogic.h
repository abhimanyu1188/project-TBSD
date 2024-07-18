#pragma once
#include "blackjack.h"

void shuffleDeck(PCard deck);
Card dealCard(PCard deck, int* top);
int calculateScore(PPlayer player);
