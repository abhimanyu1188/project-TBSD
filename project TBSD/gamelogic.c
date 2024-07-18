#include "gamelogic.h"
#include <stdlib.h>
#include <time.h>

// shuffling the deck
void shuffleDeck(PCard deck) {
    for (int i = 0; i < 52; i++) {
        // for 1 to all 52 card we choose a random number cards
        int r = rand() % 52;
        Card temp = deck[i];
        // deck[i] is replaced with deck[r]
        deck[i] = deck[r];
        // and then deck [r] is made equal to temp
        deck[r] = temp;
    }
}

Card dealCard(PCard deck, int* top) {
    // deal the top card 
    return deck[(*top)++];
}

// calculating the score of the player 
int calculateScore(PPlayer player) {
    int score = 0, aces = 0;
    for (int i = 0; i < player->handSize; i++) {
        int rank = player->hand[i].rank;

        // for 10, j , q, k score has to be 10
        if (rank > 10) {
            score += 10;
        }
        // if rank 1 which is ace then count it as 11 
        else if (rank == 1) {
            aces++;
            score += 11;
        }
        // otherwise add the face value of the card 
        else {
            score += rank;
        }
    }

    // if adding an ace as an 11 makes the score more than 21 then subtract 10
    while (score > 21 && aces > 0) {
        score -= 10;
        aces--;
    }
    return score;
}
