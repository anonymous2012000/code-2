# PRF Invocations

Dependencies: 

  GMP: https://gmplib.org/
  
  Cryptopp: https://www.cryptopp.com
  
Runnig a Test:

 Clone the above libraries, and the PwDR file. Install the libraries and unzip "PwDR-main" file. Then, run the following command lines in order:

      g++  -c Rand.cpp  -lgmpxx -lgmp -std=c++11 -lcryptopp
      
      g++  Rand.o  main.cpp  -o main -lgmpxx -lgmp -std=c++11 -lcryptopp

      ./main
      



