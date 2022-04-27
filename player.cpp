#include <iostream>
#include <string.h>
#include <list>

using namespace std;

// Class that handles data and operations related to a player
class Player {
    
    private:  

        char name; // Player's name, in the case of the example is only one char
        list<int> betList; // List that represents the paper with the bets
        char bet[6]; //current Bet (Ex: Red, Black...)
        int betAmount; // Current amount of money to bet
        int totalWinAmount; // Total amount won or lost by a player. If it's positive it's win amount, if it's negative it's lose amount.

        int minBet = 5;
        int maxBet = 4000;
        
        void checkCorrectSum(int amount);

    public:

        Player(char currentName, char currentBet[6]);

        char getName();

        char* getBet();

        int getBetAmount();

        int getTotalWinAmount();

        void PrintPlayer();

        void PrintBetList();

        void initBetList();

        int calculatePlayerBet();

        void Win (int winAmount);

        void Lose();
};

/* Costructor. Creates a player with the name and bet received. 
Set the amount of money to bet and the win money to zero. 
And sets the bet list on {1,2,3,4}.*/
Player::Player(char currentName, char* currentBet) {
    name = currentName;
    strcpy(bet, currentBet);
    initBetList();
    betAmount = 0;
    totalWinAmount = 0;  
}

// Returns the name of a player.
char Player::getName(){
    return name;
}

// Returns a player's bet.
char* Player::getBet() {
    return bet;
}

// Returns the amount of money bet by a player.
int Player::getBetAmount() {
    return betAmount;
}

// Returns the total amount won or lost by a player.
int Player::getTotalWinAmount(){
    return totalWinAmount;
}

// Initialize the list of bets to {1,2,3,4}
void Player::initBetList() {
    betList.push_back(1);
    betList.push_back(2);
    betList.push_back(3);
    betList.push_back(4);
}

/* Returns the current amount of money that a player will bet. 
It calculates the amount to bet by adding the first and last element
of the list of bets.
If the list has only one element, this is returned. 
If the list has no elements, the list is restarted and the sum is 
calculated again.*/
int Player::calculatePlayerBet() {
    int len = betList.size();
            
    if (len > 1) {
        int sum = betList.front() + betList.back();
        checkCorrectSum(sum);
        return betAmount;
    } 

    else if (len == 1) {
        int sum = betList.front();
        checkCorrectSum(sum);
        return betAmount;
    }

    else if (len == 0) {
        betList.clear();
        initBetList();
        betAmount = betList.front() + betList.back();
        return betAmount;
    }
}

/* Verifies that the current amount to bet is smaller than the maximum 
and greater than the minimum. If it's not, the list of bets it's 
restarted and the amount to bet is calculated again.*/
void Player::checkCorrectSum(int amount) {
    if (amount <= maxBet && amount >= minBet) {
        betAmount = amount;
    } 

    else {
        betList.clear();
        initBetList();
        betAmount = betList.front() + betList.back();
    }
}

/* Concats the won amount to the bet list and adds it to the total won
by a player*/
void Player::Win (int winAmount) {
    betList.push_back(winAmount - betAmount);
    totalWinAmount += winAmount - betAmount;
    printf("Player %c win %d!!\n", name, winAmount - betAmount);
}

/* Removes the first and las element from the list of bets.
If the list turns empty, it restart the list. Also, it substract the 
amount lost from the total amount won by a player.*/
void Player::Lose() {
    int len = betList.size();

    if (len > 1) {
        betList.pop_back();
        betList.pop_front();
    }

    else if (len == 1) {
        betList.clear();
        initBetList();
    }

    totalWinAmount -= betAmount;
    printf("Player %c lose %d\n", name, betAmount);
}

// Prints a player. For debugging.
void Player::PrintPlayer() {
    list<int>::iterator it = betList.begin();
    
    cout <<"Name: "<< name << endl;
    cout << "Type of bet: "<< bet << endl;
    cout << "Bet List: ";
    while (it != betList.end()) {
        cout << *it << '-';
        it++;
    }
    cout << "\nBet amount: "<< betAmount <<endl;
    if (totalWinAmount >= 0) {
        cout << "Win: "<< totalWinAmount <<endl;
    } 
    
    else {
        cout << "Lose: "<< -totalWinAmount <<endl;
    }
    printf("\n\n");
}

// Prints the list of bets. For debugging.
void Player::PrintBetList() {
    list<int>::iterator it = betList.begin();
    while (it != betList.end()) {
        cout << *it << '-';
        it++;
    }
    printf("\n");
}

/*
// Use for debugging.
int main() {

    // Defines a bet
    char red[] = "Red";

    // Creates 2 players
    Player* playerA = new Player('A', red);
    Player* playerB = new Player('B',red);

    printf("\n################ TEST Player(), initBetList() and PrintPlayer() ################\n\n");
    playerA->PrintPlayer();

    printf("############################### TEST getName() #################################\n\n");
    printf("Name: %c\n\n", playerA->getName());

    printf("################################ TEST getBet() #################################\n\n");
    printf("Bet: %s\n\n", playerA->getBet());

    printf("############################## TEST getBetAmount() #############################\n\n");
    printf("Bet amount: %d\n\n", playerA->getBetAmount());

    printf("########################### TEST getTotalWinAmount() ###########################\n\n");
    printf("Total win amount: %d\n\n", playerA->getTotalWinAmount());

    printf("############################## TEST PrintBetList() #############################\n\n");
    printf("Init BetList: ");
    playerA->PrintBetList();

    printf("\n################################# TEST Win() ###################################\n\n");
    playerB->calculatePlayerBet();
    playerB->Win(playerB->getBetAmount() * 2);
    playerB->PrintPlayer();

    printf("############################## TEST Lose() len > 1 #############################\n\n");
    playerB->calculatePlayerBet();
    playerB->Lose();
    playerB->PrintPlayer();

    printf("############################# TEST Lose() len == 1 #############################\n\n");
    playerB->calculatePlayerBet();
    playerB->Lose();
    playerB->PrintPlayer();
    playerB->calculatePlayerBet();
    playerB->Lose();
    playerB->PrintPlayer();

    printf("\n######### TEST calculatePlayerBet()  with len > 1 and checkcorrectSum() ########\n\n");
    playerA->calculatePlayerBet();
    playerA->PrintBetList();
    printf("Bet amount: %d\n", playerA->getBetAmount());

    printf("\n######## TEST calculatePlayerBet()  with len == 1 and checkcorrectSum() ########\n\n");
    playerA->PrintBetList();
    playerA->Win(400);
    playerA->Win(500);
    playerA->Win(600);
    playerA->Win(700);
    playerA->Win(800);
    playerA->PrintBetList();
    playerA->Lose();
    playerA->Lose();
    playerA->Lose();
    playerA->Lose();
    playerA->calculatePlayerBet();
    playerA->PrintBetList();
    printf("Bet amount: %d\n", playerA->getBetAmount());

    printf("\n##################  TEST calculatePlayerBet()  with len == 0  ##################\n\n");
    playerA->PrintBetList();
    playerA->Lose();
    playerA->PrintBetList();
    playerA->Lose();
    playerA->PrintBetList();
    playerA->Lose();
    playerA->PrintBetList();
    playerA->calculatePlayerBet();
    playerA->PrintBetList();
    printf("Bet amount: %d\n", playerA->getBetAmount());

    printf("\n########################  TEST checkCorrectSum > maxBet  #######################\n\n");
    playerA->Win(4005);
    playerA->calculatePlayerBet();
    playerA->PrintBetList();
    printf("Bet amount: %d\n", playerA->getBetAmount());

    printf("\n########################  TEST checkCorrectSum < minBet ########################\n\n");
    playerA->Win(playerA->getBetAmount() * 2);
    playerA->PrintBetList();
    playerA->Lose();
    playerA->PrintBetList();
    playerA->Lose();
    playerA->PrintBetList();
    playerA->calculatePlayerBet();
    playerA->PrintBetList();
    printf("Bet amount: %d\n", playerA->getBetAmount());
    printf("\n###############################################################################\n");
}*/