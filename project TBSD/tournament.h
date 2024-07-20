#pragma once

#pragma once
#include "blackjack.h"

typedef struct {
    PPlayer players;
    int numPlayers;
} Tournament;

void initializeTournament(Tournament* tournament, int numPlayers);
void registerPlayer(Tournament* tournament, PPlayer player, int playerIndex);
void updateTournamentResults(Tournament* tournament);
void freeTournament(Tournament* tournament);

