#include "sieve.h"
#include <math.h>
//Author: Professor Darelle Long

void sieve ( bitV *v) {
  oneVec (v) ; // Assume all are prime
  clrBit (v, 0) ; // 0 is , well , zero
  clrBit (v, 1) ; // 1 is unity
  setBit (v, 2) ; // 2 is prime

  for ( uint32_t i = 2; i <= sqrtl ( lenVec (v) ) ; i += 1) {
    // It ’s prime
    if ( valBit (v, i) ) {
      for ( uint32_t k = 0; (k + i) * i <= lenVec (v) ; k += 1) {
        clrBit (v, (k + i) * i) ; // Its multiple are composite
      }
    }
  }
  return ;
}
