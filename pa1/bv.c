#include <stdio.h>
#include <stdlib.h>
#include "bv.h"


// Create a new vector of specified length
bitV * newVec ( uint32_t length) {
	bitV *bvect = (bitV*)malloc(sizeof(bitV));//allocate memory for the bit vector
	bvect->vector = (uint8_t*) malloc(sizeof(uint8_t)*length);//allocates memory for the vector pointer of the bit vector
	bvect->length = length;
	return bvect;
}

// Deletes a vector
void delVec ( bitV *bvect) {
	free(bvect->vector);
	free(bvect);
}

// Creates a vector of all 1
void oneVec ( bitV *bvect) {

	for (uint32_t i=0; i < lenVec(bvect); i++) {
		bvect->vector[i] = 1;
	}
	return;
}


// Sets a specified bit
void setBit ( bitV* bvect , uint32_t bit ) {
	bvect->vector[bit] =  1;
}

// Clears a specified bit
void clrBit (bitV* bvect , uint32_t bit ) {
	bvect->vector[bit] =  0;
}

// Returns the value of a specified bit
uint8_t valBit ( bitV *vector, uint32_t bit) {
	return vector->vector[bit];
}

// Return the length of the vector
uint32_t lenVec ( bitV *vector) {
	return vector->length;
}
