#include "pch.h"
#include "CppUnitTest.h"
#include "blackjack.h"
#include "gamelogic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestCalculateScore)
        {
            Player player;
            Card hand[MAX_SIZE];

            player.hand = hand;
            player.handSize = 0;

            player.handSize = 0;
            Assert::AreEqual(calculateScore(&player), 0);

            // Test case: Hand with no aces
            player.hand[0].rank = 2; // 2
            player.hand[1].rank = 10; // 10
            player.handSize = 2;
            Assert::AreEqual(calculateScore(&player), 12);

            // Test case: Hand with one ace
            player.hand[0].rank = 1; // Ace
            player.hand[1].rank = 5; // 5
            player.handSize = 2;
            Assert::AreEqual(calculateScore(&player), 16);

            // Test case: Hand with multiple aces
            player.hand[0].rank = 1; // Ace
            player.hand[1].rank = 1; // Ace
            player.hand[2].rank = 9; // 9
            player.handSize = 3;
            Assert::AreEqual(calculateScore(&player), 21);

            // Test case: Hand with multiple aces resulting in score adjustment
            player.hand[0].rank = 1; // Ace
            player.hand[1].rank = 1; // Ace
            player.hand[2].rank = 9; // 9
            player.hand[3].rank = 2; // 2
            player.handSize = 4;
            Assert::AreEqual(calculateScore(&player), 13);
        }
    };
}
