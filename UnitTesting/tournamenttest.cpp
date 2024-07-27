#include "pch.h"
#include "CppUnitTest.h"
#include <cstdio>
#include <cstdlib>

extern "C" {
#include "blackjack.h"
#include "tournament.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(TournamentTest)
    {
    public:

        //Testing requirement TC001 

        TEST_METHOD(InitializationValidNumberOfPlayers)
        {
            Tournament tournament;
            initializeTournament(&tournament, 3);

            Assert::IsNotNull(tournament.players);
            Assert::AreEqual(3, tournament.numPlayers);
            for (int i = 0; i < 3; i++) {
                Assert::IsNotNull(tournament.players[i].hand);
                Assert::AreEqual(0, tournament.players[i].handSize);
                Assert::AreEqual(0, tournament.players[i].score);
                Assert::AreEqual(0, tournament.players[i].chips);
            }

            freeTournament(&tournament);
        }

        //Testing requirement TC002

        TEST_METHOD(InitializationInvalidNumberOfPlayers)
        {
            Tournament tournament;
            initializeTournament(&tournament, -1);

            Assert::IsNull(tournament.players);
            Assert::AreEqual(0, tournament.numPlayers);
        }

        //Testing requirement TC003

        TEST_METHOD(RegisterPlayerValidIndex)
        {
            Tournament tournament;
            initializeTournament(&tournament, 3);

            Player player;
            player.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
            player.handSize = 0;
            player.score = 10;
            player.chips = 5;

            registerPlayer(&tournament, &player, 2);

            Assert::AreEqual(10, tournament.players[2].score);
            Assert::AreEqual(5, tournament.players[2].chips);

            free(player.hand);
            freeTournament(&tournament);
        }

        //Testing requirement TC004

        TEST_METHOD(RegisterPlayerInvalidIndex)
        {
            Tournament tournament;
            initializeTournament(&tournament, 3);

            Player player;
            player.hand = (PCard)malloc(MAX_SIZE * sizeof(Card));
            player.handSize = 0;
            player.score = 10;
            player.chips = 5;

            registerPlayer(&tournament, &player, 5);

            // Ensure no change in any of the players within valid index range
            for (int i = 0; i < 3; i++) {
                Assert::AreEqual(0, tournament.players[i].score);
                Assert::AreEqual(0, tournament.players[i].chips);
            }

            free(player.hand);
            freeTournament(&tournament);
        }

        //Testing requirement TC005

/*
        TEST_METHOD(UpdateTournamentResults)
        {
            Tournament tournament;
            initializeTournament(&tournament, 3);

            tournament.players[0].score = 10;
            tournament.players[0].chips = 5;
            tournament.players[1].score = 20;
            tournament.players[1].chips = 15;
            tournament.players[2].score = 5;
            tournament.players[2].chips = 0;

            // Redirect stdout to a file
            FILE* file = freopen("test_output.txt", "w", stdout);
            updateTournamentResults(&tournament);
            fclose(file);

            // Restore stdout and read the file content
            file = fopen("test_output.txt", "r");
            char buffer[256];
            fread(buffer, sizeof(char), 255, file);
            fclose(file);
            buffer[255] = '\0';

            // Define the expected output
            const char* expectedOutput = "Tournament Results:\nPlayer 1 - Chips: 5, Score: 10\nPlayer 2 - Chips: 15, Score: 20\nPlayer 3 - Chips: 0, Score: 5\n";

            // Compare the actual output with the expected output
            Assert::AreEqual(expectedOutput, buffer);

            freeTournament(&tournament);
        }

*/
    };
}