#include <iostream>
#include "./userInput.h"
using namespace std;

int userIn(){
    int input;
     cin >> input;
    while(!((input <= 512) && (input >= 0))){
        printf("%s", "Invalid input. Please enter an integer between 0 and 512, inclusive: ");
        cin >> input;
    }
    return input;
}