#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Class that handles the data and operations related to a casino roulette.
class Roulette {
    
    public:

        // 0 represents 0; 1 represents red; 2 represents black
        int numbers[37] = {0,1,2,1,2,1,2,1,2,1,2,2,1,2,1,2,1,2,1,1,2,1,2,1,2,1,2,1,2,2,1,2,1,2,1,2,1};

        Roulette() {}
    
        int spin();
};

// Simulates the spin of a casino roulette
int Roulette::spin() {
    int winNumber = rand() % 37;
            
    printf("\nThe winner number is: %d !!!\n\n", winNumber);// Use for debuggin.
    return winNumber;
}

/*
// Use for debugging.
int main() {

    // Initialize a seed to latter obtain random numbers.
    srand(time(NULL));

    // Create a roulette
    Roulette* roulette = new Roulette();

    printf("\n####################### Simulates 10.000 roulette spins #######################\n");
    for (int i = 0; i < 10000; i++) {
        roulette->spin();
    }
    printf("\n###############################################################################\n");
}*/