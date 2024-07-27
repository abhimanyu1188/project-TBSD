_crt_secure_no_warnings
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "datamanagement.h"
#include "gamelogic.h"
#include "ui.h"

#define MAX_PLAYERS 3

int main() {
    // Pointer to hold the deck of cards
    PCard deck = NULL;
    // Index for the top card in the deck
    int decktop = 0;
    // Array to hold player information
    Player players[MAX_PLAYERS];
    // Initialize dealer information
    Player dealer = { .handSize = 0, .score = 0, .chips = 0 };

    // Allocate memory for each player's hand and initialize player details
    for (int i = 0; i < MAX_PLAYERS; i++) {
        players[i].hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
        players[i].handSize = 0;
        players[i].score = 0;
        players[i].chips = 0;
        if (players[i].hand == NULL) {
            printf("Memory allocation failed for player %d!\n", i + 1);
            exit(1);  // Exit if memory allocation fails
        }
    }

    // Allocate memory for the dealer's hand
    dealer.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
    if (dealer.hand == NULL) {
        printf("Memory allocation failed for dealer!\n");
        exit(1);  // Exit if memory allocation fails
    }

    // Seed the random number generator
    srand(time(NULL));

    // Initialize and shuffle the deck
    initializeDeck(&deck);
    shuffleDeck(deck);

    int option;
    // Main loop for user menu
    do {
        displayMenu();  // Display the menu options
        scanf("%d", &option);  // Read user input

        switch (option) {
        case 1:
            // Add chips to each player
            for (int i = 0; i < MAX_PLAYERS; i++) {
                addChips(&players[i]);
            }
            break;
        case 2:
            // Check and display the balance of each player
            for (int i = 0; i < MAX_PLAYERS; i++) {
                printf("Player %d's ", i + 1);
                checkBalance(&players[i]);
            }
            break;
        case 3:
            // Allow the user to play a round of blackjack
            displayPlayerCountMenu();  // Show options for number of players
            int numPlayers;
            scanf("%d", &numPlayers);  // Read number of players
            if (numPlayers >= 1 && numPlayers <= MAX_PLAYERS) {
                playRound(players, numPlayers, &dealer, deck, &top);
            }
            else {
                printf("Invalid number of players. Please choose between 1 and %d.\n", MAX_PLAYERS);
            }
            break;
        case 4:
            // Exit the program
            printf("Exiting...\n");
            break;
        default:
            // Handle invalid menu options
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 4);  // Repeat until the user chooses to exit

    // Free allocated memory
    freeDeck(deck);  // Free memory allocated for the deck
    for (int i = 0; i < MAX_PLAYERS; i++) {
        freePlayer(&players[i]);  // Free memory allocated for each player
    }
    freePlayer(&dealer);  // Free memory allocated for the dealer

    return 0;  // Exit the program successfully
}
