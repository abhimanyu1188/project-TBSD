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
    const char* rankStrings[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const char* suitStrings[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    printf("%s of %s\n", rankStrings[card.rank - 1], suitStrings[card.suit]);
}

//Printing the hands of player

void printHand(PPlayer player, int reveal) {
    for (int i = 0; i < player->handSize; i++) {
        if (i == 1 && !reveal) {
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

//Playing of round 
void playRound(PPlayer players, int numPlayers, PPlayer dealer, PCard deck, int* top) {
   
}