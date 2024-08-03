#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "blackjack.h"
#include "datamanagement.h"
#include "tournament.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(DATAMANAGEMENTMODULETEST)
    {
    public:

        TEST_METHOD(SaveGameTest)
        {
            Player players[2];
            Player dealer;

            // Initialize players and dealer
            for (int i = 0; i < 2; i++) {
                players[i].hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
                players[i].handSize = 2;
                players[i].score = 10 * (i + 1);
                players[i].chips = 100 * (i + 1);
                players[i].hand[0].rank = 1;
                players[i].hand[0].suit = 0;
                players[i].hand[1].rank = 13;
                players[i].hand[1].suit = 3;
            }
            dealer.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
            dealer.handSize = 2;
            dealer.score = 20;
            dealer.chips = 500;
            dealer.hand[0].rank = 1;
            dealer.hand[0].suit = 0;
            dealer.hand[1].rank = 13;
            dealer.hand[1].suit = 3;

            // Save the game state
            bool saveResult = saveGame(players, 2, &dealer, "test_save.dat");
            Assert::IsTrue(saveResult);

            // Free allocated memory
            for (int i = 0; i < 2; i++) {
                free(players[i].hand);
            }
            free(dealer.hand);
        }

        TEST_METHOD(LoadGameTest)
        {
            Player players[2];
            Player dealer;

            // Initialize players and dealer with default values to test loading
            for (int i = 0; i < 2; i++) {
                players[i].hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
                players[i].handSize = 0;
                players[i].score = 0;
                players[i].chips = 0;
            }
            dealer.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
            dealer.handSize = 0;
            dealer.score = 0;
            dealer.chips = 0;

            // Load the game state
            bool loadResult = loadGame(players, 2, &dealer, "test_save.dat");
            Assert::IsTrue(loadResult);

            // Verify the loaded state
            for (int i = 0; i < 2; i++) {
                Assert::AreEqual(2, players[i].handSize);
                Assert::AreEqual(10 * (i + 1), players[i].score);
                Assert::AreEqual(100 * (i + 1), players[i].chips);
                Assert::AreEqual(1, players[i].hand[0].rank);
                Assert::AreEqual(0, players[i].hand[0].suit);
                Assert::AreEqual(13, players[i].hand[1].rank);
                Assert::AreEqual(3, players[i].hand[1].suit);
            }
            Assert::AreEqual(2, dealer.handSize);
            Assert::AreEqual(20, dealer.score);
            Assert::AreEqual(500, dealer.chips);
            Assert::AreEqual(1, dealer.hand[0].rank);
            Assert::AreEqual(0, dealer.hand[0].suit);
            Assert::AreEqual(13, dealer.hand[1].rank);
            Assert::AreEqual(3, dealer.hand[1].suit);

            // Free allocated memory
            for (int i = 0; i < 2; i++) {
                free(players[i].hand);
            }
            free(dealer.hand);
        }

        TEST_METHOD(InitializeDeckTest)
        {
            PCard deck = NULL;

            // Initialize the deck
            initializeDeck(&deck);

            // Verify the deck has 52 cards
            Assert::IsNotNull(deck);
            int cardCount = 0;
            for (int suit = 0; suit < 4; suit++) {
                for (int rank = 1; rank <= 13; rank++) {
                    Assert::AreEqual(rank, deck[cardCount].rank);
                    Assert::AreEqual(suit, deck[cardCount].suit);
                    cardCount++;
                }
            }
            Assert::AreEqual(52, cardCount);

            // Free the deck
            freeDeck(deck);
        }

        TEST_METHOD(FreeDeckTest)
        {
            PCard deck = NULL;

            // Initialize the deck
            initializeDeck(&deck);

            // Verify the deck is initialized
            Assert::IsNotNull(deck);

            // Free the deck
            freeDeck(deck);

        }
    };
}
