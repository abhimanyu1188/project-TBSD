#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "datamanagement.h"
#include "gamelogic.h"

// Function to print a single card
void printCard(Card card) {
    const char* rankStrings[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const char* suitStrings[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    printf("%s of %s\n", rankStrings[card.rank - 1], suitStrings[card.suit]);
}

// Function to print a player's hand
void printHand(PPlayer player, int revealAll) {
    for (int i = 0; i < player->handSize; i++) {
        if (i == 1 && !revealAll) {
            printf("Hidden card\n");
        }
        else {
            printCard(player->hand[i]);
        }
    }
}

// Function to play the game
void playGame(PPlayer player, PPlayer dealer, PCard deck, int* top) {
    // Initialize hand sizes and scores
    player->handSize = dealer->handSize = 0;
    player->score = dealer->score = 0;

    // Deal initial cards
    player->hand[player->handSize++] = dealCard(deck, top);
    player->hand[player->handSize++] = dealCard(deck, top);
    dealer->hand[dealer->handSize++] = dealCard(deck, top);
    dealer->hand[dealer->handSize++] = dealCard(deck, top);

    // Calculate initial scores
    player->score = calculateScore(player);
    dealer->score = calculateScore(dealer);

    // Print initial hands
    printf("Player's hand:\n");
    printHand(player, 1);
    printf("Player's score: %d\n", player->score);

    printf("Dealer's hand:\n");
    printHand(dealer, 0);

    // Player's turn
    char choice;
    while (player->score < 21) {
        printf("Do you want to hit or stand? (h/s): ");
        scanf(" %c", &choice);

        if (choice == 'h') {
            player->hand[player->handSize++] = dealCard(deck, top);
            player->score = calculateScore(player);
            printf("Player's hand:\n");
            printHand(player, 1);
            printf("Player's score: %d\n", player->score);
        }
        else {
            break;
        }
    }

    // Dealer's turn
    if (player->score <= 21) {
        printf("Dealer's turn:\n");
        while (dealer->score < 17) {
            dealer->hand[dealer->handSize++] = dealCard(deck, top);
            dealer->score = calculateScore(dealer);
        }
    }

    // Print final hands
    printf("Dealer's hand:\n");
    printHand(dealer, 1);
    printf("Dealer's score: %d\n", dealer->score);

    // Determine the winner
    if (player->score > 21) {
        printf("Player busts! Dealer wins.\n");
    }
    else if (dealer->score > 21 || player->score > dealer->score) {
        printf("Player wins!\n");
    }
    else if (dealer->score > player->score) {
        printf("Dealer wins!\n");
    }
    else {
        printf("It's a tie!\n");
    }
}

int main() {
    PCard deck = NULL;
    int top = 0;
    Player player = { .handSize = 0, .score = 0, .chips = 0 };
    Player dealer = { .handSize = 0, .score = 0, .chips = 0 };

    // Allocate memory for hands
    player.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
    dealer.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
    if (player.hand == NULL || dealer.hand == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    srand(time(NULL));

    // Initialize and shuffle deck
    initializeDeck(&deck);
    shuffleDeck(deck);

    // Play game
    playGame(&player, &dealer, deck, &top);

    // Free allocated memory
    freeDeck(deck);
    freePlayer(&player);
    freePlayer(&dealer);

    return 0;
}
