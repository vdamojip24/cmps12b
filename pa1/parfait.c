# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "bv.h"
# include "sieve.h"

// Returns 1 if num is perfect number or 0 if anything else
int isPerfectNumber(int num) {
	int sum = 0 ;   
 	for(int i = 1 ; i < num ; i++) {   
   		if(num % i == 0)   
     	sum = sum + i ;   
  	}    
 
 	if (sum == num) {
		 return 1;
	 }

	return 0; 
}

//Prints proper divisiors of the given number
void printPerfectNumber(int num) {
	
	printf("%d E: ", num);

    for (int i=1; i < num; i++) {
		if (num%i == 0) {
			printf("%d ",i);
		}
	}
    
	printf("\n");
            
}

//Prints prime factors of given number
void printPrimeFactors(int num) {
    

    for (int i = 2; i <= num; i++) {
        while (num%i == 0) {
            printf("%d ", i);
            num = num/i;
        }
    }
        
}

//main method with an optional commandline argument 
int main(int argc, char **argv) {

	//Default value
	unsigned int number = 100000;

	// If commandline arg is passed, override the default value
	if (argc == 3) {
		if (strcmp(argv[1],"-n") == 0) {
			number = atoi(argv[2]);//converts ascii to int
		}
	}

    bitV *vector = newVec(number);//creating new bit vector of given size

    sieve(vector);

    for (uint32_t i=2; i <= lenVec(vector); i++) {
		char *c;
		if(valBit(vector, i)) {
			c = "P";
			printf("%d %s\n", i, c);
		}
		else {
			c = "C: ";
			printf("%d %s", i, c);
			printPrimeFactors(i);
			printf("\n");
		}
		if (isPerfectNumber(i)) {
				printPerfectNumber(i);
		}
  	}

}
