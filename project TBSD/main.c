#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "datamanagement.h"
#include "gamelogic.h"
#include "ui.h"

#define MAX_PLAYERS 3 // Maximum number of players

int main() {
    PCard deck = NULL;
    int top = 0;
    Player players[MAX_PLAYERS];
    Player dealer = { .handSize = 0, .score = 0, .chips = 0 };

    // Allocate memory for players' hands
    for (int i = 0; i < MAX_PLAYERS; i++) {
        players[i].hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
        if (players[i].hand == NULL) {
            printf("Memory allocation failed for player %d!\n", i + 1);
            exit(1);
        }
    }

    // Allocate memory for dealer's hand
    dealer.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
    if (dealer.hand == NULL) {
        printf("Memory allocation failed for dealer!\n");
        exit(1);
    }

    // Initialize and shuffle the deck
    srand(time(NULL));
    initializeDeck(&deck);
    shuffleDeck(deck);

    int option;
    do {
        displayMenu(); // Show the main menu
        scanf("%d", &option);

        switch (option) {
        case 1:
            // Add chips to all players
            for (int i = 0; i < MAX_PLAYERS; i++) {
                addChips(&players[i]);
            }
            break;
        case 2:
            // Display balance for all players
            for (int i = 0; i < MAX_PLAYERS; i++) {
                printf("Player %d's balance: ", i + 1);
                checkBalance(&players[i]);
            }
            break;
        case 3:
            // Play the game with the specified number of players
            displayPlayerCountMenu();
            int numPlayers;
            scanf("%d", &numPlayers);
            if (numPlayers >= 1 && numPlayers <= MAX_PLAYERS) {
                playRound(players, numPlayers, &dealer, deck, &top);
            }
            else {
                printf("Invalid number of players. Please choose between 1 and %d.\n", MAX_PLAYERS);
            }
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 4);

    // Free allocated memory
    freeDeck(deck);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        freePlayer(&players[i]);
    }
    freePlayer(&dealer);

    return 0;
}
