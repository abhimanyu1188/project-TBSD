#include "datamanagement.h"
#include "blackjack.h"
#include <stdlib.h>
#include <stdio.h>

// initializing deck with multiple suites and rank using dynamic memory allocation
void initializeDeck(PCard* deck) {
    *deck = (PCard)malloc(52 * sizeof(Card));
    if (*deck == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    int k = 0;
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 1; rank <= 13; rank++) {
            (*deck)[k].rank = rank;
            (*deck)[k].suit = suit;
            k++;
        }
    }
}

// freeing deck
void freeDeck(PCard deck) {
    free(deck);
}

// freeing player 
void freePlayer(PPlayer player) {
    if (player->hand) {
        free(player->hand);
    }
}

// saving the game state to a file
bool saveGame(PPlayer players, int numPlayers, PPlayer dealer, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for saving!\n");
        return false;
    }

    fwrite(&numPlayers, sizeof(int), 1, file);
    for (int i = 0; i < numPlayers; i++) {
        fwrite(&players[i], sizeof(Player), 1, file);
        fwrite(players[i].hand, sizeof(Card), players[i].handSize, file);
    }
    fwrite(dealer, sizeof(Player), 1, file);
    fwrite(dealer->hand, sizeof(Card), dealer->handSize, file);

    fclose(file);
    printf("Game saved successfully.\n");
    return true;
}

// loading the game state from a file
bool loadGame(PPlayer players, int numPlayers, PPlayer dealer, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for loading!\n");
        return false;
    }

    int loadedNumPlayers;
    fread(&loadedNumPlayers, sizeof(int), 1, file);
    if (loadedNumPlayers != numPlayers) {
        printf("Mismatch in number of players!\n");
        fclose(file);
        return false;
    }

    for (int i = 0; i < numPlayers; i++) {
        fread(&players[i], sizeof(Player), 1, file);
        players[i].hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
        if (players[i].hand == NULL) {
            printf("Memory allocation failed for player hand!\n");
            fclose(file);
            return false;
        }
        fread(players[i].hand, sizeof(Card), players[i].handSize, file);
    }
    fread(dealer, sizeof(Player), 1, file);
    dealer->hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
    if (dealer->hand == NULL) {
        printf("Memory allocation failed for dealer hand!\n");
        fclose(file);
        return false;
    }
    fread(dealer->hand, sizeof(Card), dealer->handSize, file);

    fclose(file);
    printf("Game loaded successfully.\n");
    return true;
}
