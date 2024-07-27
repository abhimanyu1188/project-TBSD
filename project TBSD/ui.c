#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include "gamelogic.h"
#include <stdio.h>

//Displaying the main menu 
void displayMainMenu() {
    printf("1. Add 100 chips\n");
    printf("2. Check balance\n");
    printf("3. Play game\n");
    printf("4. Exit\n");
    printf("Choose an option: ");
}
//Displaying the Player Count Menu
void displayPlayerCountMenu() {
    printf("Select number of players:\n");
    printf("1. One player\n");
    printf("2. Two players\n");
    printf("3. Three players\n");
    printf("Choose an option: ");
}

//Adding 100 chips to the player
void addChipsToPlayer(PPlayer player) {
    player->chips += 100;
    printf("Added 100 chips. New balance: %d\n", player->chips);
}

//Checking of the current balance
void checkCurrentBalance(PPlayer player) {
    printf("Current balance: %d\n", player->chips);
}

//Printing cards from suits
void printCard(Card card) {
    const char* rankLabels[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const char* suitlabels[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    printf("%s of %s\n", rankLabels[card.rank - 1], suitlabels[card.suit]);
}

//Printing the hands of player

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

//Checking if the chips are enough to play 
//If the chips are less than 10 it will automatically add 100 chips 
void ensureEnoughChips(PPlayer player) {
    if (player->chips < 10) {
        addChipsToPlayer(player);
        printf("Not enough chips. Automatically added 100 chips to Player's balance.\n");
    }
}

//Function for playing the game
void playGame(PPlayer player, PPlayer dealer, PCard deck, int* top) {
    // Ensuring if the player has enough chips
    ensureEnoughChips(player);
    player->chips -= 10;

    // Reset hands and scores
    player->handSize = 0;
    player->score = 0;
    dealer->handSize = 0;
    dealer->score = 0;

    // Dealing the cards from the deck
    player->hand[player->handSize++] = dealCard(deck, top);
    player->hand[player->handSize++] = dealCard(deck, top);
    dealer->hand[dealer->handSize++] = dealCard(deck, top);
    dealer->hand[dealer->handSize++] = dealCard(deck, top);
    player->score = calculateScore(player);
    dealer->score = calculateScore(dealer);

    // Printting the hands of player and displaying the score
    printf("Player's hand:\n");
    printHand(player, 1);
    printf("Player's score: %d\n", player->score);

    //Printing the hands of the dealer
    printf("Dealer's hand:\n");
    printHand(dealer, 0);

    // Player's Chance
    char choice;
    //Player score should be less than 21 
    while (player->score < 21) {
        //Asking the user for hitting or stand
        printf("Do you want to hit or stand? (h/s): ");
        scanf(" %c", &choice);
        //If player hits it will again deal cards and will calculate the new score
        if (choice == 'h') {
            player->hand[player->handSize++] = dealCard(deck, top);
            player->score = calculateScore(player);
            //  Print player's hand
            printf("Player's hand:\n");
            //Print player's score
            printHand(player, 1);
            printf("Player's score: %d\n", player->score);
        }
        else {
            break;
        }
    }

    // Dealer's Chance
     //if player's score is less than 21 it will be dealer's turn
    if (player->score <= 21) {
        printf("Dealer's turn:\n");
        while (dealer->score < 17) {
            dealer->hand[dealer->handSize++] = dealCard(deck, top);
            dealer->score = calculateScore(dealer);
        }
    }

    // Print the final hands and scores
    printf("Dealer's hand:\n");
    printHand(dealer, 1);
    printf("Dealer's score: %d\n", dealer->score);

    // Deciding the winner
    //if player's score is more than 21 the player will bust and the dealer will win
    if (player->score > 21) {
        printf("Player busts! Dealer wins.\n");
    }
    //otherwise the player will win if dealer's score goes more than 21
    else if (dealer->score > 21 || player->score > dealer->score) {
        player->chips += 20;
        printf("Player wins!\n");
    }
    //of dealer's score is more than player's score and less than 21
    //then the dealer wins 
    else if (dealer->score > player->score) {
        printf("Dealer wins!\n");
    }
    //And if both the scores are same it will be a tie
    else {
        player->chips += 10;
        printf("It's a tie!\n");
    }

    // Displaying the  balance of chips
    printf("Player's balance: %d chips\n", player->chips);
}

// Implementation of playing in rounds
void playRound(PPlayer players, int numPlayers, PPlayer dealer, PCard deck, int* top) {

    // Ensure all players have enough chips and deduct initial bet
    for (int i = 0; i < numPlayers; i++) {
        ensureEnoughChips(&players[i]);
        players[i].chips -= 10; // Deduct bet from each player's chips
    }

    // Reset hands and scores for all players and the dealer
    for (int i = 0; i < numPlayers; i++) {
        players[i].handSize = 0; // Resets the player hand size
        players[i].score = 0;    // Resets the player score
    }
    dealer->handSize = 0; // Resets the  dealer hand size
    dealer->score = 0;    // Resets the dealer score

    // Deal initial two cards to each player and dealer
    for (int i = 0; i < numPlayers; i++) {
        players[i].hand[players[i].handSize++] = dealCard(deck, top); 
        players[i].hand[players[i].handSize++] = dealCard(deck, top); 
        players[i].score = calculateScore(&players[i]); // Calculate players initial score
    }
    dealer->hand[dealer->handSize++] = dealCard(deck, top); 
    dealer->hand[dealer->handSize++] = dealCard(deck, top); 
    dealer->score = calculateScore(dealer); // Calculate dealer's initial score

    // Print dealer's initial hand with one card hidden
    printf("Dealer's hand:\n");
    printHand(dealer, 0); // to Show one card hidden

    // Each player's turn
    char choice;
    for (int i = 0; i < numPlayers; i++) {
        printf("Player %d's turn:\n", i + 1);
        printHand(&players[i], 1); // to Print player's hand
        printf("Player's score: %d\n", players[i].score);

        // Allow player to hit or stand
        while (players[i].score < 21) {
            printf("Do you want to hit or stand? (h/s): ");
            scanf(" %c", &choice);
            if (choice == 'h') {
                players[i].hand[players[i].handSize++] = dealCard(deck, top); // Deal another card
                players[i].score = calculateScore(&players[i]); // Update score
                printHand(&players[i], 1); // Print updated hand
                printf("Player's score: %d\n", players[i].score);
            }
            else {
                break; // End turn if player stands
            }
        }
    }

    // Dealer's turn to draw cards until reaching at least 17
    while (dealer->score < 17) {
        dealer->hand[dealer->handSize++] = dealCard(deck, top); // Deal card to dealer
        dealer->score = calculateScore(dealer); // Update dealer score
    }

    // Print dealer's final hand and score
    printf("Dealer's turn:\n");
    printHand(dealer, 1); // Show dealer's full hand
    printf("Dealer's score: %d\n", dealer->score);

    // Determine results and update chips
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].score > 21) {
            // Player busts
            printf("Player %d busts! Dealer wins.\n", i + 1);
        }
        else if (dealer->score > 21 || players[i].score > dealer->score){
            // Player wins
            players[i].chips += 20; // Win reward
            printf("Player %d wins!\n", i + 1);
    }
 else if (dealer->score > players[i].score) {
        // Dealer wins
        printf("Dealer wins against Player %d.\n", i + 1);
        }
 else {
            // Tie
            players[i].chips += 10; // Tie reward
            printf("Player %d ties with the dealer.\n", i + 1);
            }
}

// Display remaining chips balance for each player
for (int i = 0; i < numPlayers; i++) {
    printf("Player %d's balance: %d chips\n", i + 1, players[i].chips);
}
}
