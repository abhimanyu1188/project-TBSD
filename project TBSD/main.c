#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "datamanagement.h"
#include "gamelogic.h"
#include "ui.h"

//The maximum number of players that can play are 3 
#define MAX_PLAYERS 3

//Main function
int main() {
    PCard deck = NULL;
    int top = 0;
    Player players[MAX_PLAYERS];
    Player dealer = { .handSize = 0, .score = 0, .chips = 0 };

    // Initializing the players by dynamic memory allocation
    for (int i = 0; i < MAX_PLAYERS; i++) {
        players[i].hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
        players[i].handSize = 0;
        players[i].score = 0;
        players[i].chips = 0;
        if (players[i].hand == NULL) {
            printf("Memory allocation failed for player %d!\n", i + 1);
            exit(1);
        }
    }

    dealer.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
    if (dealer.hand == NULL) {
        printf("Memory allocation failed for dealer!\n");
        exit(1);
    }
    //using random function to generate random cards
    srand(time(NULL));

    initializeDeck(&deck);
    shuffleDeck(deck);

    int option;
    do {
        displayMainMenu();
        scanf("%d", &option);

        //For single player as of now
        switch (option) {
        case 1:
            addChipsToPlayer(&players[0]); 
            break;
        case 2:
            checkCurrentBalance(&players[0]); 
            break;
        case 3:
            displayPlayerCountMenu();
            int numPlayers;
            scanf("%d", &numPlayers);
            if (numPlayers == 1) {
                playGame(&players[0], &dealer, deck, &top); 
            }
            else {
                printf("Multiplayer functionality not yet implemented.\n");
            }
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 4);

    //Freeing the deck
    freeDeck(deck);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        freePlayer(&players[i]);
    }
    freePlayer(&dealer);

    return 0;
}