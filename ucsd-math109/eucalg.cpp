/* Euclidean algorithm in C++ */
/* Compile with: g++ eukalg.cpp -o eucalg */
/* Copyright: Martin Licht, 2018 */
 
#include <iostream>

/* declare a short cut for the unsigned integer datatype */
typedef unsigned long long int unsigned_integer;
 
int main()
{
  std::cout << "---------Euclidean Algorithm---------" << std::endl;
  
  /* declare variables a and b */
  
  unsigned_integer a;
  unsigned_integer b;
  
  /* read input values */
  
  std::cout << "Enter first non-negative unsigned integer: ";
  std::cin  >> a;
  std::cout << "Enter second non-negative unsigned integer: ";
  std::cin  >> b;
  
  /* check input values */
  
  if( ! std::cin.good() ){
    std::cout << "Invalid input. Good bye!" << std::endl;
    return 0;
  }
  
  /* without loss of generality, a >= b */
  
  if( a < b ){
    unsigned_integer t = a; a = b; b = t;
  }
  
  std::cout << "Pair for this run: " << "\n\t a = " << a << "\n\t b = " << b << std::endl;
  
  /* check for the special case a=b=0 */
  
  if( a == 0 && b == 0 ){
    std::cout << "Greatest Common Divisor of 0 and 0 is undefined. Good bye!" << std::endl;
    return 0;
  }
  
  /* save original variables for later */
  /* only needed to get a pretty output */
  
  unsigned_integer a_original = a;
  unsigned_integer b_original = b;
  
  /* MAIN LOOP: Euclidean algorithm */
  std::cout << "Computation:" << std::endl;
  
  while( b != 0 ){
    
    unsigned int q = a / b;
    unsigned int r = a % b;
    
    std::cout << "\t" << a << " = " << q << " * " << b << " + " << r << std::endl;
    
    a = b; b = r;
    
  }
    
  
  /* Finished: output the results of thecomputation */
  
  std::cout << "Greatest common divisor:\n\t g = "
            << a
            << std::endl;
  std::cout << "Reduced pair: "
            << "\n\t a/g = "
            << a_original/a
            << "\n\t b/g = " 
            << b_original/a
            << std::endl;
  
  
  std::cout << "---------Euclidean Algorithm---------" << std::endl;
  return 0;
}