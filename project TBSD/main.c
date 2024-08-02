#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "datamanagement.h"
#include "gamelogic.h"
#include "ui.h"

#define MAX_PLAYERS 3
#define MAX_SIZE 52  // Assuming a standard deck size

int main() {
    // Pointer to hold the deck of cards
    PCard deck = NULL;
    // Index for the top card in the deck
    int decktop = 0;
    // Array to hold player information
    Player players[MAX_PLAYERS];
    // Initialize dealer information
    Player dealer = { .hand = NULL, .handSize = 0, .score = 0, .chips = 0 };

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
    srand((unsigned int)time(NULL));

    // Initialize and shuffle the deck
    initializeDeck(&deck);
    shuffleDeck(deck);

    int option;
    int numPlayers;
    int top = 0; 
    int menu = 0;
    int count = 0;
    // Main loop for user menu
    do {
        menu=displayMainMenu();  // Display the menu options
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        loadGame(players, MAX_PLAYERS, &dealer, "game_save.dat");


        switch (option) {
        case 1:
            // Add chips to each player
            for (int i = 0; i < MAX_PLAYERS; i++) {
                addChipsToPlayer(&players[i]);
            }
            break;
        case 2:
            // Check and display the balance of each player
            for (int i = 0; i < MAX_PLAYERS; i++) {
                printf("Player %d's ", i + 1);
                checkCurrentBalance(&players[i]);
            }
            break;
        case 3:
            // Allow the user to play a round of blackjack
            count=displayPlayerCountMenu();  // Show options for number of players
            if (scanf("%d", &numPlayers) != 1) {
                printf("Invalid input. Please enter an integer.\n");
                while (getchar() != '\n'); // Clear invalid input
                continue;
            }
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
            saveGame(players, MAX_PLAYERS, &dealer, "game_save.dat");
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
