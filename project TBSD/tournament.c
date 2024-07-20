#include "tournament.h"
#include <stdio.h>
#include <stdlib.h>

// Function to initialize tournament with the given number of players.

void initializeTournament(Tournament* tournament, int numPlayers) {

    // Allocate memory for the players

    tournament->players = (PPlayer)malloc(numPlayers * sizeof(Player));

    // Checking if memory allocation was successful
    if (tournament->players == NULL) {
        printf("Memory allocation for tournament players failed!\n");
        exit(1);
    }
    tournament->numPlayers = numPlayers;

    // Initializing each player.
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

// Registers a player at the given index in the tournament

void registerPlayer(Tournament* tournament, PPlayer player, int playerIndex) {
    if (playerIndex < 0 || playerIndex >= tournament->numPlayers) {
        printf("Invalid player index!\n");
        return;
    }

    // Register the player
    tournament->players[playerIndex] = *player;
}

// This part of the code prints the results of the tournament
void updateTournamentResults(Tournament* tournament) {
    printf("Tournament Results:\n");
    for (int i = 0; i < tournament->numPlayers; i++) {
        printf("Player %d - Chips: %d, Score: %d\n", i + 1, tournament->players[i].chips, tournament->players[i].score);
    }
}

// Frees the memory used by the tournament

void freeTournament(Tournament* tournament) {
    for (int i = 0; i < tournament->numPlayers; i++) {
        free(tournament->players[i].hand);
    }
    free(tournament->players);
}
