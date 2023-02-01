#include <iostream>
#include <cctype>
#include <random>
#include <ctime>
#include <windows.h>

using u32    = uint_least32_t; 
using engine = std::mt19937;
using namespace std;

void playGame(int, int);

int getRandomInRange(engine& generator, int min, int max){
    uniform_int_distribution< u32 > distribute( min,  max );
    return distribute(generator);
}

int main( void )
{
    engine generator( time(0) );
    
    int MIN_PILE_SIZE = 0;
    int MAX_PILE_SIZE = 20;

    int countPile1 = getRandomInRange(generator, MIN_PILE_SIZE,MAX_PILE_SIZE);
    int countPile2 = getRandomInRange(generator, MIN_PILE_SIZE,MAX_PILE_SIZE);
    
    cout <<"Welcome to candies game!" << endl;
    cout << "Every pile has a random number of candies." << endl;
    cout << "Your mission is to win and take the last candy." <<endl;
    cout << "You can take candies as much as you want out of one pile on every turn." << endl;

    cout << "--------------------------------------------"<< endl;

    playGame(countPile1, countPile2);
  
  return 0;
}


void playGame(int countPile1, int countPile2){
    bool userTurn = false;
    int chosenPile, chosenCandies;
    int* piles[] = {&countPile1, &countPile2};
    if (countPile1 == countPile2){
        userTurn = true;
    }

    while (countPile1 + countPile2 != 0){
        cout << "--------------------------------------------"<< endl;
        cout << "Candies status :\n  Pile1 : " << countPile1 << ", Pile2 : " << countPile2 << endl;
        if (userTurn){
            while(1){
                cout << "YOUR TURN: choose a pile number (1/2), and number of candies" << endl;
                cin >> chosenPile >> chosenCandies;
                if (cin.fail() || chosenPile > 2 || chosenPile <= 0 ||
                    chosenCandies <= 0 || chosenCandies > *piles[chosenPile-1]){
                    cout << "INVALID INPUT. TRY AGAIN" << endl;
                    std::cin.clear();
                    std::cin.ignore();
                }
                else {break;}
            }
            *piles[chosenPile-1] -= chosenCandies;
        }
        else{
            cout << "MY TURN!" << endl;
            int greaterPile = (countPile1 > countPile2) ? 1 : 2;
            int diff = std::abs(countPile1 - countPile2);
            cout << "I'm taking " << diff << " candies out of pile #" << greaterPile  << endl;
            *piles[greaterPile-1] -= diff;
        }
        userTurn = !userTurn;
    }

    if (userTurn){
        cout << "YOU LOST!" << endl;
    }
    else{
        cout << "YOU WON!" << endl;
    }

    system("pause");
}