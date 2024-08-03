#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "blackjack.h"
#include "datamanagement.h"
#include "gamelogic.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(GAMELOGICMODULETEST)
    {
    public:

        // GLM 001 
        // Verify that the deck is shuffled correctly after initializing the game
        TEST_METHOD(ShuffleDeckInitializationTest)
        {
            PCard deck = NULL;
            initializeDeck(&deck);
            shuffleDeck(deck);

            bool isShuffled = false;
            for (int i = 0; i < 10; i++) {
                if (deck[i].rank != (i % 13) + 1 || deck[i].suit != i / 13) {
                    isShuffled = true;
                    break;
                }
            }
            Assert::IsTrue(isShuffled);
            freeDeck(deck);
        }

        // GLM 002 
        // Verify that the deck is shuffled correctly after a game has ended
        TEST_METHOD(ShuffleDeckAfterRoundTest)
        {
            PCard deck = NULL;
            initializeDeck(&deck);
            shuffleDeck(deck);
            shuffleDeck(deck);  // Shuffle again to simulate end of a round

            bool isShuffled = false;
            for (int i = 0; i < 10; i++) {
                if (deck[i].rank != (i % 13) + 1 || deck[i].suit != i / 13) {
                    isShuffled = true;
                    break;
                }
            }
            Assert::IsTrue(isShuffled);
            freeDeck(deck);
        }

        // GLM 003 
        // Verify score calculation without an Ace
        TEST_METHOD(ScoreCalculationWithoutAceTest)
        {
            Player player;
            player.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
            player.handSize = 3;

            player.hand[0].rank = 2;
            player.hand[0].suit = 0;
            player.hand[1].rank = 5;
            player.hand[1].suit = 1;
            player.hand[2].rank = 13;
            player.hand[2].suit = 2;

            int score = calculateScore(&player);
            Assert::AreEqual(17, score);  // Expected score without Ace
            free(player.hand);
        }

        // GLM 004 
        // Verify score calculation with an Ace
        TEST_METHOD(ScoreCalculationWithAceTest)
        {
            Player player;
            player.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
            player.handSize = 3;

            player.hand[0].rank = 1;  // Ace
            player.hand[0].suit = 0;
            player.hand[1].rank = 5;
            player.hand[1].suit = 1;
            player.hand[2].rank = 13;
            player.hand[2].suit = 2;

            int score = calculateScore(&player);
            Assert::AreEqual(16, score);  // Expected score with Ace 
            free(player.hand);
        }
    };
}
