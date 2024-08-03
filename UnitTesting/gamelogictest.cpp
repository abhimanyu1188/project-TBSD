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

        TEST_METHOD(ShuffleDeckInitializationTest)
        {
            PCard deck = NULL;

            // Initialize and shuffle the deck
            initializeDeck(&deck);
            shuffleDeck(deck);

            // Verify the deck is shuffled by checking a few cards
            bool isShuffled = false;
            for (int i = 0; i < 10; i++) {
                if (deck[i].rank != (i % 13) + 1 || deck[i].suit != i / 13) {
                    isShuffled = true;
                    break;
                }
            }
            Assert::IsTrue(isShuffled);

            // Free the deck
            freeDeck(deck);
        }

        TEST_METHOD(ShuffleDeckAfterRoundTest)
        {
            PCard deck = NULL;

            // Initialize and shuffle the deck
            initializeDeck(&deck);
            shuffleDeck(deck);

            // Simulate the end of a game round and shuffle again
            shuffleDeck(deck);

            // Verify the deck is shuffled again by checking a few cards
            bool isShuffled = false;
            for (int i = 0; i < 10; i++) {
                if (deck[i].rank != (i % 13) + 1 || deck[i].suit != i / 13) {
                    isShuffled = true;
                    break;
                }
            }
            Assert::IsTrue(isShuffled);

            // Free the deck
            freeDeck(deck);
        }

        TEST_METHOD(ScoreCalculationWithoutAceTest)
        {
            Player player;
            player.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
            player.handSize = 3;

            // Add cards to the player's hand (2, 5, K)
            player.hand[0].rank = 2;
            player.hand[0].suit = 0;
            player.hand[1].rank = 5;
            player.hand[1].suit = 1;
            player.hand[2].rank = 13; // King
            player.hand[2].suit = 2;

            int score = calculateScore(&player);
            Assert::AreEqual(17, score);

            // Free allocated memory
            free(player.hand);
        }

        TEST_METHOD(ScoreCalculationWithAceTest)
        {
            Player player;
            player.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
            player.handSize = 3;

            // Add cards to the player's hand (A, 5, K)
            player.hand[0].rank = 1; // Ace
            player.hand[0].suit = 0;
            player.hand[1].rank = 5;
            player.hand[1].suit = 1;
            player.hand[2].rank = 13; // King
            player.hand[2].suit = 2;

            int score = calculateScore(&player);
            Assert::AreEqual(16, score); // 1 + 5 + 10

            // Free allocated memory
            free(player.hand);
        }

        TEST_METHOD(DealTopCardTest)
        {
            PCard deck = NULL;

            // Initialize and shuffle the deck
            initializeDeck(&deck);
            shuffleDeck(deck);

            // Deal the top card, assuming dealCard takes deck and card index as parameters
            Card topCard = dealCard(deck, 0); // Adjust the parameters as necessary

            // Verify the card is removed from the deck
            Assert::AreEqual(deck[0].rank, topCard.rank);
            Assert::AreEqual(deck[0].suit, topCard.suit);

            // Free the deck
            freeDeck(deck);
        }
    };
}
