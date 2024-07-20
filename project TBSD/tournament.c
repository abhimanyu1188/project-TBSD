#include "tournament.h"
#include <stdio.h>
#include <stdlib.h>

void initializeTournament(Tournament* tournament, int numPlayers) {
    tournament->players = (PPlayer)malloc(numPlayers * sizeof(Player));
    if (tournament->players == NULL) {
        printf("Memory allocation for tournament players failed!\n");
        exit(1);
    }
    tournament->numPlayers = numPlayers;
    for (int i = 0; i < numPlayers; i++) {
        tournament->players[i].hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
        if (tournament->players[i].hand == NULL) {
            printf("Memory allocation for player hand failed!\n");
            exit(1);
        }
        tournament->players[i].handSize = 0;
        tournament->players[i].score = 0;
        tournament->players[i].chips = 0;
    }
}

void registerPlayer(Tournament* tournament, PPlayer player, int playerIndex) {
    if (playerIndex < 0 || playerIndex >= tournament->numPlayers) {
        printf("Invalid player index!\n");
        return;
    }
    tournament->players[playerIndex] = *player;
}

void updateTournamentResults(Tournament* tournament) {
    printf("Tournament Results:\n");
    for (int i = 0; i < tournament->numPlayers; i++) {
        printf("Player %d - Chips: %d, Score: %d\n", i + 1, tournament->players[i].chips, tournament->players[i].score);
    }
}

void freeTournament(Tournament* tournament) {
    for (int i = 0; i < tournament->numPlayers; i++) {
        free(tournament->players[i].hand);
    }
    free(tournament->players);
}
