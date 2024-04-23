
//===========================
// Dependencies:

// GMP: https://gmplib.org/
// Cryptopp: https://www.cryptopp.com
//===========================
// Runnig a Test:
// clone the above libraries, and the PwDR file.
// install the libraries and unzip "PwDR-main" file.
// run the following command lines in order:

// g++  -c Rand.cpp  -lgmpxx -lgmp -std=c++11 -lcryptopp
// g++  Rand.o  main.cpp  -o main -lgmpxx -lgmp -std=c++11 -lcryptopp
// ./main

//

//===========================

#include <iostream>
#include <math.h>
#include <string>
#include <stdio.h>
#include <vector>
#include "gmp.h"
#include <gmpxx.h>
#include "Rand.h"
using namespace std;
typedef mpz_t bigint;
typedef unsigned char byte;


// description: Generates a pseudorandom value (by  encrypting "val" given the key and initial vector).
bigint* encrypt(int val, byte* key, int key_size, byte* iv, int byte_){

  string cipher, temp;
  CBC_Mode< AES >::Encryption e;
  bigint* res;
  res = (bigint*)malloc(1 * sizeof(mpz_t));
  unsigned char prn_[byte_];
  e.SetKeyWithIV(key, key_size, iv);
  StringSource sss(to_string(val), true, new StreamTransformationFilter(e, new StringSink(cipher)));
  temp = cipher.substr (0, byte_);
  memset(prn_, 0x00, byte_ + 1);
  strcpy((char*)prn_, temp.c_str());
  mpz_init(res[0]);
  mpz_import(res[0], byte_, 1, 1, 0, 0, prn_);

  return res;
}


int main(){

  //---gen PRF key
  byte key[AES::DEFAULT_KEYLENGTH];
  int key_size = AES::DEFAULT_KEYLENGTH;
  byte iv[AES::BLOCKSIZE];
  AutoSeededRandomPool prng;
	prng.GenerateBlock(key, key_size);// seed_: master seed for PRF
  double start_enc = 0;
  double end_enc = 0;
  double diff_enc = 0;
  float  count = 0;
  int loop_size = 100;// number of experiments
  int number_of_invocations = 2;
  bigint* res_2;
  res_2 = (bigint*)malloc(1 * sizeof(mpz_t));
  int byte_ = 32;// 16;
  int val_ = 10;
  for(int i = 0; i<loop_size; i++){
    start_enc = 0;
    start_enc = clock();
    for(int j = 0; j<number_of_invocations; j++){
      res_2 = encrypt(val_, key, key_size, iv, byte_);
    }
    end_enc = 0;
    end_enc = clock();
    diff_enc = 0;
    diff_enc = end_enc - start_enc;
    count += diff_enc/(double) CLOCKS_PER_SEC;
  }
  cout<<"\n average time for loopsize: "<<loop_size<<" and number of invocations: "<<number_of_invocations<<", the time: "<<count/loop_size<<endl;
  cout<<endl;
  return 0;
}

 // g++  -c Rand.cpp  -lgmpxx -lgmp -std=c++11 -lcryptopp
// g++  Rand.o  main.cpp  -o main -lgmpxx -lgmp -std=c++11 -lcryptopp
// ./main
