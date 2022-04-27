#include <list>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "player.cpp"
#include "roulette.cpp"


// Class that handles data and operations related to a game
class Play {
        
    public:

        char winBet[3][6]; // List with winning bets (ex: ["Red","Elder","Even"])

        Play() {}

        int Bets(list<Player*> players);

        void allLose(list<Player*> players);

        void checkWinners(list<Player*> players);

        void play(list<Player*> players, Roulette* roulette);

        int finalWinAmount(list<Player*> players);
};

// Calls all the players to calculate their bet
int Play::Bets(list<Player*> players) {
    int len = players.size();
    list<Player*>::iterator playerIt = players.begin();

    printf("\n\n");
    while (playerIt != players.end()) {
        (*playerIt)->calculatePlayerBet();
        printf("The player A bets %d on %s\n",(*playerIt)->getBetAmount(), (*playerIt)->getBet());
        playerIt++;
    }
}

// Inform to all the players that they lost
void Play::allLose(list<Player*> players) {
    int len = players.size();
    list<Player*>::iterator playerIt = players.begin();
    
    while (playerIt != players.end()) {
        (*playerIt)->Lose();
        playerIt++;
    }
}

// Verifies if each player won or lost.
void Play::checkWinners(list<Player*> players) {
    int len = players.size();
    list<Player*>::iterator playerIt = players.begin();

    while (playerIt != players.end()) {
        if (strcmp((*playerIt)->getBet(), winBet[0]) == 0 || strcmp((*playerIt)->getBet(), winBet[1]) == 0 || strcmp((*playerIt)->getBet(), winBet[2]) == 0) {
            
            (*playerIt)->Win(((*playerIt)->getBetAmount()) * 2);
        }
        else {
            (*playerIt)->Lose();
        }
        playerIt++;
    }
}

// Simulates a play
void Play::play(list<Player*> players, Roulette* roulette) {
            
    Bets(players);
    int winNumber = roulette->spin();

    bool isZero = winNumber == 0; 
    bool isEven = (winNumber % 2) == 0 ;
    bool isRed = roulette->numbers[winNumber] == 1;
    bool isMayor = winNumber > 18;

    if (isZero) {
        allLose(players);
    }

    else {
        isRed ?  strcpy(winBet[0],"Red") : strcpy(winBet[0],"Black");
        isMayor ?  strcpy(winBet[1],"Mayor") : strcpy(winBet[1],"Minor");
        isEven ?  strcpy(winBet[2],"Even") : strcpy(winBet[2],"Odd");
        for (int i = 0; i < 3; i++) {
            printf("*** %s\n",winBet[i]);
        }
        printf("\n");
        checkWinners(players);
    }
}

// Prints all players. For debugging.
void PrintPlayers(list<Player*> players) {
    list<Player*>::iterator playerIt = players.begin();

    while (playerIt != players.end()) {
        (*playerIt)->PrintPlayer();
        playerIt++;
    }
}

// Calculates the total amount won or lost by all the players together
int Play::finalWinAmount(list<Player*> players) {
    list<Player*>::iterator playerIt = players.begin();
    int totalAmount = 0;

    while (playerIt != players.end()) {
        totalAmount += (*playerIt)->getTotalWinAmount();
        playerIt++;
    }
    return totalAmount;
}

/*
// Use for debugging.
int main() {

    // Initialize a seed to latter obtain random numbers.
    srand(time(NULL));

    // Creates a Play
    Play* play = new Play();

    // Creates a roulette
    Roulette* roulette = new Roulette();

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

    printf("\n################################# TEST Bets() ##################################");
    play->Bets(players);
    printf("\n");
    PrintPlayers(players);

    printf("\n############################### TEST allLose() ################################\n\n");
    play->allLose(players);
    printf("\n");
    PrintPlayers(players);

    printf("\n############################ TEST checkWinners() #############################\n\n");
    PrintPlayers(players);
    strcpy(play->winBet[0],"Red");
    strcpy(play->winBet[1],"Mayor");
    strcpy(play->winBet[2],"Even");
    printf("Win bet:\n\n*** %s\n*** %s\n*** %s\n\n", play->winBet[0], play->winBet[1], play->winBet[2]);
    play->checkWinners(players);
    printf("\n");
    PrintPlayers(players);

    printf("\n################################ TEST play() ################################\n\n");
    PrintPlayers(players);
    play->play(players,roulette);
    printf("\n");
    PrintPlayers(players);

    printf("\n############################  TEST finalWinAmount() ###########################\n\n");
    PrintPlayers(players);
    printf("El monto final es: %d\n", play->finalWinAmount(players));
    printf("\n########################################################################\n");

    return 0;
}*/