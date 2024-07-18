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
    free(player->hand);
}
