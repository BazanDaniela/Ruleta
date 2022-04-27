#include <list>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "play.cpp"


/* We simulate 6 players playing in a casino roulette. Everyone 
always bets the same. Each one carries a list that initially starts 
at {1,2,3,4} and bets the sum of the first and last elements of the 
list. If a player win add the amount won to the bottom of the list. 
If a player loses it removes the first and last element from the list. 
If the list has only one element, bet that value. The minimum bet 
amount is 5 and the maximum is 4000. If the list runs out of elements, 
the bet exceeds the maximum bet or does not reach the minimum bet, 
the list is reset to {1,2,3,4}. We simulate 10.000 games and give the 
final amount won or lost by the 6 players (who are supposed to play as 
a team)*/
int main () {

    // To save the total amount won or lost by all players
    int totalAmount = 0;

    // Initializes a seed to latter obtain random numbers.
    srand(time(NULL));

    // Create a roulette
    Roulette* roulette = new Roulette();

    // Create a game
    Play* play = new Play();

    // Defines the bets that we are going to use
    char red[] = "Red";
    char black[] = "Black";
    char mayor[] = "Mayor";
    char menor[] = "Minor";
    char even[] = "Even";
    char odd[] = "Odd";

    // Creates 6 players that always bet the same
    Player* playerA = new Player('A', red);
    Player* playerB = new Player('B', black);
    Player* playerC = new Player('C', mayor);
    Player* playerD = new Player('D', menor);
    Player* playerE = new Player('E', even);
    Player* playerF = new Player('F', odd);

    // Creates a list with the 6 players
    list<Player*> players;
    players.push_back(playerA);
    players.push_back(playerB);
    players.push_back(playerC);
    players.push_back(playerD);
    players.push_back(playerE);
    players.push_back(playerF);

    // Plays 10000 times
    for (int i = 0; i < 10000; i++) {
        printf("\n######################## Jugada %d ########################\n",i+1);
        play->play(players, roulette);
    }

    // Calculates the final amount won or lost
    totalAmount = play->finalWinAmount(players);

    printf("\n######################## Total Win/Lose Amount ########################\n");
    if (totalAmount >= 0) {
        printf("\nThey win %d\n",totalAmount);
    }
    else {
        printf("\nThey lose %d\n",-totalAmount);
    }
    printf("\n########################################################################\n");

    return 0;
}