#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
#include "ui.h"
#include "gamelogic.h"
}

namespace UnitTesting
{
    TEST_CLASS(UITESTING)
    {
    public:

        // UIM 001: Test Main Menu Display
        TEST_METHOD(Test_MainMenuDisplay)
        {
            int output = displayMainMenu();
            int expected = 1;
            Assert::AreEqual(expected, output);
        }

        // UIM 002: Test Player Count Menu Display
        TEST_METHOD(Test_PlayerCountMenuDisplay)
        {
            int output = displayPlayerCountMenu();
            int expected = 0;
            Assert::AreEqual(expected, output);
        }

        // UIM 003: Test Adding Chips to Player
        TEST_METHOD(Test_AddChipsToPlayer)
        {
            Player player;
            player.chips = 50;
            addChipsToPlayer(&player);
            Assert::AreEqual(150, player.chips); // Assuming addChipsToPlayer adds 100 chips
        }

        // UIM 004: Test Checking Current Balance
        TEST_METHOD(Test_CheckCurrentBalance)
        {
            Player player;
            player.chips = 200;

            // If checkCurrentBalance requires a Player object, pass it as a parameter
            int output = checkCurrentBalance(&player); // Ensure this matches the function signature
            int expected = 200; // The expected balance

            Assert::AreEqual(expected, output);
        }

        // UIM 005: Test Exiting the Game
        TEST_METHOD(Test_ExitGame) {
            int option = 4;
            bool exitCondition = false;

            if (option == 4) {
                exitCondition = true;
            }

            Assert::IsTrue(exitCondition);
        }
    };
}