# include <stdio.h>
# include <stdlib.h>

typedef enum faciem {LEFT , RIGHT , CENTER , PASS } faces ;
faces die [] = {LEFT , RIGHT , CENTER , PASS , PASS , PASS };
const char * names [] = {" Whoopi ", " Dale ", " Rosie ", " Jimmie ", 
						 " Barbara ", " Kyle ", " Raven ", " Tony ",
						 " Jenny ", " Clint "};

int playersMoney[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
int numPlayers;
int pot = 0;
int currentPlayerIndex = 0;

void playGame();
void updateCurrentPlayerIndex();
int payLeftPlayer();
int payRightPlayer();
void payPot();
int trackNumberOfActivePlayers();
int findWinner();



int main(){

		unsigned int seed;
    	
    	printf("Enter Seed: ");
    	scanf("%u", &seed);

    	printf("How many players? ");
    	scanf("%d", &numPlayers);
		
		srand(seed);
    	
		playGame();

	}


void playGame() {
	int activePlayers = trackNumberOfActivePlayers();
	while (activePlayers > 1) {
		int numOfRolls = playersMoney[currentPlayerIndex];

		if (numOfRolls == 0) {
			updateCurrentPlayerIndex();
			continue;
		}

		if(numOfRolls > 3) {
			numOfRolls = 3;
		}

		printf("%s rolls...", names[currentPlayerIndex]);
		for (int i=0; i < numOfRolls; i++) {
			int rollResult = rand() % 6;

			if (die[rollResult] ==  LEFT) {
				int index = payLeftPlayer();
				printf("gives $1 to %s ", names[index]);
			}
			else if (die[rollResult] ==  RIGHT) {
				int index = payRightPlayer();
				printf("gives $1 to %s ", names[index]);
			}
			else if (die[rollResult] ==  CENTER) {
				payPot();
				printf("puts $1 in the pot ");
			}
			else if (die[rollResult] ==  PASS) {
				printf("gets a pass ");
				continue;
			}
		}
		printf("\n");
		activePlayers = trackNumberOfActivePlayers();
        updateCurrentPlayerIndex();
	}
	if(activePlayers == 1) {
		int winnerIndex = findWinner();
		printf("%s wins the $%d pot with $%d left in the bank!\n", names[winnerIndex], pot, playersMoney[winnerIndex]);

	}
}

void updateCurrentPlayerIndex() {
	currentPlayerIndex++;
	if (currentPlayerIndex == numPlayers) {
		currentPlayerIndex = 0;
	}
}

int payLeftPlayer() {
	int leftPlayerIndex = currentPlayerIndex - 1;
	if (leftPlayerIndex < 0) {
		leftPlayerIndex = numPlayers - 1;
	}
	playersMoney[leftPlayerIndex] += 1 ;
	playersMoney[currentPlayerIndex]  -= 1;

	return leftPlayerIndex;
} 

int payRightPlayer() {
	int rightPlayerIndex = currentPlayerIndex + 1;
	if (rightPlayerIndex == numPlayers) {
		rightPlayerIndex = 0;
	}
	playersMoney[rightPlayerIndex] += 1 ;
	playersMoney[currentPlayerIndex]  -= 1;

	return rightPlayerIndex;
} 

void payPot() {
	pot += 1;
	playersMoney[currentPlayerIndex]  -= 1;
}

int trackNumberOfActivePlayers() {
	int count = 0;
	for(int i = 0; i < numPlayers; i ++ ){
      if(playersMoney[i] > 0) {
		  count ++;
	  }
   }
   return count;
}

int findWinner() {
	int index = -1;
	for(int i = 0; i < numPlayers; i ++ ){
      if(playersMoney[i] > 0) {
		  index = i;
		  break; 
	  }
   }
   return index;
}

