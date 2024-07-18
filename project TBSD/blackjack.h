#pragma once

#define MAX_SIZE 11

typedef struct {
    int rank;
    int suit;
} Card;

typedef Card* PCard;

typedef struct {
    PCard hand;
    int handSize;
    int score;
    int chips;
} Player;

typedef Player* PPlayer;

