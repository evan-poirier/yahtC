/* 
 yahtC
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void seed(int argc, char ** argv){
    srand(time(NULL)); // Initialize random seed
    if (argc>1){
        int i;
        if (1 == sscanf(argv[1],"%d",&i)){
            srand(i);
        }
    }
}
void instructions(){
    printf("\n\n\n\n"
           "\t**********************************************************************\n"
           "\t*                         Welcome to YahtC                            *\n"
           "\t**********************************************************************\n"
           "\tYahtC is a dice game (very) loosely modeled on Yahtzee\n"
           "\tBUT YahtC is not Yahtzee.\n\n"
           "\tRules:\n"
           "\t5 dice are rolled\n"
           "\tThe user selects which dice to roll again.\n"
           "\tThe user may choose to roll none or all 5 or any combination.\n"
           "\tAnd then the user selects which dice to roll, yet again.\n"
           "\tAfter this second reroll the turn is scored.\n\n"
           "\tScoring is as follows:\n"
           "\t\t*\t50 points \t5 of a kind scores 50 points.\n"
           "\t\t*\t45 points \tNo pairs (all unique) scores 45 points.\n"
           "\t\t*\t40 points \t4 of a kind scores 40 points.\n"
           "\t\t*\t30 points \t3 of a kind scores 30 points.\n"
           "\t\t*\tTotal Dice\tOtherwise score the dice total.\n\n"
           "\tTo indicate nothing to reroll the user will input 0\n"
           "\tThis should end the players turn.\n"
           "\tOtherwise the user will indicate which dice to reroll by position\n"
           "\t135 would indicate to reroll the first, third and last die.\n"
           "\tThe numbers do not have to be given in order\n"
           "\tThe game ends after 7 turns.\n"
           "\t**********************************************************************\n\n\n");
}

int main(int argc, char ** argv){
    seed(argc, argv);
    //instructions();
    
    int dice[5];
    int score[7];
    int reroll;
    int reverseReroll = 0;
    int totalScore = 0;
    
    //loops 7 times, for the 7 rounds of the game
    for (int j = 0; j < 7; j ++) {
       //first roll
       for (int i = 0; i < 5; i ++) {
          dice[i] = (rand() % 6) + 1;
       }
    
       //print results for first roll
       printf("~~~ Turn %d ~~~\n", j + 1);
       printf("First Roll = ");
       
       for (int i = 0; i < 5; i ++) {
          printf("%d", dice[i]);  
       }
       
       printf("\n");
       
       //get input for second roll
       printf("Select dice to reroll:\n");
       scanf("%d", &reroll);
       printf("%d\n", reroll);
       
       //reroll selected dice if input != 0
       if (reroll != 0) {
          //set reverseReroll back to zero, then assign it with the reverse of reroll
          reverseReroll = 0;
          while (1) {
             reverseReroll += reroll % 10;
             reroll /= 10;
             if (reroll > 0) {
               reverseReroll *= 10;
             } else {
               break;
             }
          }

          //reroll each die
          while (1) {
             int temp = reverseReroll % 10;
             dice[temp - 1] = (rand() % 6) + 1;
             
             reverseReroll /= 10;
             
             if (reverseReroll == 0) {
                break;
             }
          }
          
          //print second roll
          printf("second:");
          
          for (int i = 0; i < 5; i ++) {
             printf("%d", dice[i]);  
          }
          
          printf("\n");
          
          //get input for third roll
          printf("Select dice to reroll:\n");
          scanf("%d", &reroll);
          printf("%d\n", reroll);
          
          //reroll selected dice if input != 0
          if (reroll != 0) {
             //set reverseReroll back to zero, then assign it with the reverse of reroll
             reverseReroll = 0;
             while (1) {
                reverseReroll += reroll % 10;
                reroll /= 10;
                if (reroll > 0) {
                   reverseReroll *= 10;
                } else {
                   break;
                }
             }

             //reroll each die
             while (1) {
                int temp = reverseReroll % 10;
                dice[temp - 1] = (rand() % 6) + 1;
               
                reverseReroll /= 10;
               
                if (reverseReroll == 0) {
                   break;
                }
             }
             
             //print final roll
             printf("final:");
             
             for (int i = 0; i < 5; i ++) {
                printf("%d", dice[i]);  
             }
             
             printf("\n");
          }
       }
       
       //determine n of a kind
       int maxOfAKind = 0;
       for (int i = 0; i < 5; i ++) {
          int ofAKind = 0;
          for (int k = 0; k < 5; k ++) {
             if (dice[i] == dice[k]) {
                ofAKind ++;
             }
          }
          if (ofAKind > maxOfAKind) {
             maxOfAKind = ofAKind;
          }
       }
       
       //determine score for round
       score[j] = 0;
       
       if (maxOfAKind == 5) {
          score[j] = 50;
       } else if (maxOfAKind == 1) {
          score[j] = 45;
       } else if (maxOfAKind == 4) {
          score[j] = 40;
       } else if (maxOfAKind == 3) {
          score[j] = 30;
       } else {
          for (int i = 0; i < 5; i ++) {
             score[j] += dice[i];
          }
       }
       
       int rawDice = 0;
       for (int i = 0; i < 5; i ++) {
          rawDice += dice[4 - i] * pow(10, i);
       }
       
       printf("score for %d is %d\n\n", rawDice, score[j]);
    }
    
    //print scoresheet
    printf("\n----------\n"
           "SCORESHEET\n"
           "----------\n");
    
    for (int i = 0; i < 7; i ++) {
       printf("Turn %d: %d\n", i + 1, score[i]);
    }
    
    printf("==========\n");
    
    for (int i = 0; i < 7; i ++) {
       totalScore += score[i];
    }
    
    printf("Total: %d\n", totalScore);
    
    return 0;
}
