#include <stdlib.h>
#include <iostream>
#include <time.h>

void setup();
void run();
int successRolls(int dicePool, int difficulty, bool tenAgain);
int rollD10();
void reset();


char combat = '\0';
char tenAgain = '\0';
int baseDamage = -1;
int dicePool = -1;
int difficulty = -1;
int success = 0;
void setup(){
	while(combat != 'y' && combat != 'Y' && combat != 'n' && combat != 'N'){
		printf("Combat (Y) or Non-combat (N)? ");
		scanf ("%c",&combat);
		fflush(stdin);
		
		if(combat =='y' || combat == 'Y'){
			while(baseDamage < 1 || baseDamage > 10){
				printf("Base Weapon Damage (1-10) ");
				scanf ("%d",&baseDamage);
				fflush(stdin);
			}
		}
	}
	while(tenAgain != 'y' && tenAgain != 'Y' && tenAgain != 'n' && tenAgain != 'N'){
		printf("Ten again? (Y/N) ");
		scanf ("%c",&tenAgain);
		fflush(stdin);
	}

	while(dicePool < 1){
		printf("Base Dice Pool: ");
		scanf ("%d",&dicePool);
		fflush(stdin);
	}

	while(difficulty <= 1 || difficulty > 11){
		printf("Difficulty (1-11): ");
		scanf ("%d",&difficulty);
		fflush(stdin);
	}
}

void run(){
	if(difficulty < 0){
		printf("Either setup hasn't run, or difficulty is invalid\n");
		return; // (should do more checks, but works for now)
	}

	// Input done, logic:
	bool tenAgainBool = tenAgain == 'y' || tenAgain == 'Y';
	success = successRolls(dicePool, difficulty, tenAgainBool);
		
	// Output
	printf("\n");
	if(success == 0){
		printf("Action failed\n");
	} else if (success < 0){
		printf("Action botched\n");
	} else if (success >= 1){
		printf("Number of successes: %d",success);
		if(combat == 'y' || combat == 'Y'){
			printf("\n");
			printf("Damage dice rolled: ");
			int combatSuccess = 0;
			// Rerolls
			for(int i=0;i<(baseDamage+success-1);i++){
				int d10 = rollD10();
				printf("%d ",d10);
				if(d10 >= 6){
					combatSuccess++;
				}
			}
			printf("\nDamage successes: %d",combatSuccess);
		}
		printf("\n");
	}

	char runAgain = '\0';
	while(runAgain != 'y' && runAgain != 'Y' && runAgain != 'n' &&  runAgain != 'N' && runAgain != 'd' &&  runAgain != 'D'){
		printf("Run again with same settings? (Y/N/D) (D = Different data)");
		scanf ("%c",&runAgain);
		fflush(stdin);
	}
	if(runAgain == 'y' || runAgain == 'Y'){
		run();
	} else if(runAgain == 'd' || runAgain == 'D'){
		printf("\n");
		reset();
		setup();
		run();
	}
}

int successRolls(int dicePool, int difficulty, bool tenAgain){
	int success = 0;
	printf("\n");
	printf("Dice rolled: ");
	for(int i=0;i<dicePool;i++){
		int d10 = rollD10();
		printf("%d ",d10);
		if(tenAgain){
			if(d10 >= difficulty && d10 > 1 && d10 < 10){ 
				success++;
			} else if (d10 == 10){
				success += 2;
			} else if (d10 == 1){
				success--;
			}
		} else {
			if(d10 >= difficulty && d10 > 1){
				success++;
			} else if (d10 == 1){
				success--;
			}
		}
	}
	printf("\n");
	return success;
}
int rollD10(){
	return rand() % 10 + 1;
}
void reset(){
	combat = '\0';
	tenAgain = '\0';
	baseDamage = -1;
	dicePool = -1;
	difficulty = -1;
	success = 0;
}

int main(){
	srand (time(NULL));
	setup();
	run();
}

