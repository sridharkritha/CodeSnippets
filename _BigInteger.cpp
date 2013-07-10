  
  
/************************************************************************
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************/

/*****************************************************************************

  This program is an implementation of the Karatsuba-Ofmann-Algorithm
  a.k.a. Karatsuba-Algorithm, for an asymptotically faster multiplication
  of big integer numbers.

  This program has been written as participation at a programming contest
  by the some peers of the students council of the Mathematicians at the
  University of Bonn, Germany (Rheinische Friedrich-Wilhelms-Universität Bonn)
  in winter of 2008

  It includes some basic algorithms like addition, subtraction and
  - of course - multiplication. My intention was to optimize it for speed,
  but nevertheless, I think the code is still easily to understand,
  well-documentend and features a very efficient usage of memory. And, well,
  I think this piece is pretty fast ;-)

  It's interresting to notice that the total amount of memory could be even
  reduced, in a tradeoff for speed, due to a additional copy-statement one
  would require to use. Yet, you cannot implement this algorithm in-place.

  This program is only capable of Big Integers whose number of digits is a
  power of 2 - whereas a digit is a 'unsigned long int'.

  The Karatsuba-multiplication method switches to naiv multiplication according
  to school method, once recursion tree has reached a depth where the number of
  digits of the factors falls bellow a certain length, thus making later method
  the more efficient algorithm. The threshold has been chosen empirically on my
  system, therefore you may want to modify it to improve your speed.

  I hope you enjoy!
  Martin Werner Licht
  
  XmaXXrtXinXX.lXigXht XaXt wXeXbXX.XdeX (remove the 'X's)

****************************************************************************/

/****************************************************************************

    You may want to visit:

    www.uni-bonn.de - University of Bonn
    www.math.uni-bonn.de - Institute for Mathematics
    www.iam.uni-bonn.de - Institute for Applied Mathematics
    www.ins.uni-bonn.de - Institute for Numerical Simulation
    www.or.uni-bonn.de - Institute for Discrete Mathematics
    www.hcm.uni-bonn.de - Hausdorff-Center for Mathematics

****************************************************************************/

/****************************************************************************

    I am a German native speaker, and most of the documentation in this file
    is a translation from German into English. Although I do my best to write
    in proper English, it may of course include grammatical or orthographical
    errors of any kind. 

****************************************************************************/
  
/****************************************************************************

  Compiling issues:
  This program has been tested on Kubuntu Linux, Gutsy Gibbon, and has
  been compiled with the gcc-compiler:
  gcc karatsuba.c -std=c99 -pedantic -W -Wall

  Runtime issues:
  There are no known errors

****************************************************************************/  

  

  /*********************************************/
  /* THE CODE                                  */
  /*********************************************/


  /*********************************************/
  /* Includes                                  */
  /*********************************************/

  #include <assert.h>
  #include <limits.h>
  #include <math.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h> 
  
  
  
  
  /*********************************************/
  /* Datatypes and constants                   */
  /*********************************************/
  

  typedef unsigned long int bigint;
  typedef unsigned long int bigintlength; 
  typedef unsigned char     bigintexpo;
  
  //typedef unsigned char bool;
  
  #define false ((bool)0)
  #define true ((bool)1)
  
  #define DIGIT_MAX ((bigint)ULONG_MAX)
  #define DIGTI_MIN ((bigint)0) 
  
  
  
  /*********************************************/
  /* Elementary operations                     */
  /*********************************************/
  
  
  
  /*
  * Outputs a Big Int.
  * Remark: z points to an array of digits of length n. The output is in
    hexadecimal, 8-Hexdigits per Bigint-digit. After the output there is a
    linebreak.
  */
  void OutputBigint( bigintlength n, const bigint* z )
  {
    assert( z != NULL );
    while( n >= 1 )
    {
      printf( "%lx ", *(z+(n-1)) );
      n--;
    }
    printf( "\n" );
  }
  
  

  /*
  * Copies a Big Int
  * Remark: Copies the array of n digits src points to into the n digits dest
    points to. 
  */
  void Copy( bigintlength n, bigint* dest, const bigint* src )
  {
    bigintlength i; 
    assert( dest != NULL );
    assert( src != NULL );  
    for( i = 0; i < n; i++ ) dest[i] = src[i];
  }
  
  /*
  * Sets a Big Number to zero
  * Remark: dest points to n digits, which will be set to zero, i.e. 0x00000000.
  */
  void SetZero( bigintlength n, bigint* dest )
  {
    bigintlength i;
    assert( dest != NULL );
    for( i = 0; i < n; i++ ) dest[i] = (bigint)0;
  }
  
  
  /*
  * Compares to Big Ints
  * Remark: z1 and z2 point to Big Integers with n digits each. In case of
    either z1 > z2, z1 = z2 or z1 < z2, the return is 1, 0 or -1, respectively.
  */
  int Compare( bigintlength n, const bigint* z1, const bigint* z2 )
  {
    for( ; n > 0; n-- )
      if( z1[n-1] > z2[n-1] )
        return 1;
      else if( z2[n-1] > z1[n-1] )
        return -1;
    
    return 0;
  } 
  
  
  /*
  * Adds a big int to another big int, taking into account the carry.
  * Remark: dest and add point to Big Int of length n. add is addup to dest.
    carry points to a boolean value which (i) gives input, whether 1 shall
    be added to the sum or not (ii) whether there has been an overflow has
    taken place during execution (1) or not (0). It's a simulation of a
    carry-save-adder.
  */
  bool Add( bigintlength n, bigint* dest, const bigint* add, bool* carry )
  {
    
    bigintlength i;
    for( i = 0; i < n; i++ )
    {
      dest[i] += add[i];
      if( *carry ) dest[i]++;
      if( ( !(*carry) && add[i] > dest[i] ) || ( *carry && add[i] >= dest[i] ) )
        *carry = true;
      else
        *carry = false;
    }
    
    return *carry;
  }
  
  
  
   /*
  * Adds to big ints, saves the result and takes into account the carry.
  * Remark: Works like Add, but with two summands and an argument for a
    pointer the sum is written to. dest and add1 are allowed to point to
    the same block of memory
  */
  bool CopyAdd( bigintlength n, bigint* dest, const bigint* add1, const bigint* add2, bool* carry )
  {
    assert( add2 != dest );
    bigintlength i;
    for( i = 0; i < n; i++ )
    {
      dest[i] = add1[i] + add2[i];
      if( *carry ) dest[i]++;
      
      if( ( !(*carry) && add2[i] > dest[i] ) || ( *carry && add2[i] >= dest[i] ) )
        *carry = true;
      else
        *carry = false;
    }
    
    return *carry;
  }
  
  
  /*
  * Increments a big int, taking into account the carry.
  * Remark: dest points to a Big Int of length n. dest is incremented by 1.
    carry points to a boolean value which (i) gives input, whether 1 shall be
    added to the sum or not (ii) whether there has been an overflow has taken
    place during execution (1) or not (0). It's a simulation of a
    carry-save-adder.
  */
  bool Inc( bigintlength n, bigint* dest, bool* carry )
  {
    
    bigintlength i;
    
    dest[0]++;
    if( dest[0] == (bigint)0 ) *carry = true;
    
    for( i = 1; *carry == true && i < n; i++ )
    {
      dest[i]++;
      if( dest[i] == (bigint)0 ) *carry = true;
      else *carry = false;
    }
    
    return *carry;
    
  }
  
  
  
  /*
  * Subtracts a big int from another big int, taking into account the carry.
  * Remark: dest and sub point to Big Int of length n. sub is subtracted
    from dest. carry points to a boolean value which (i) gives input,
    whether 1 shall be drawn from the difference or not (ii) whether there
    has been an overflow has taken place during execution (1) or not (0).
    It's a simulation of a carry-save-adder.
  */
  bool Sub( bigintlength n, bigint* dest, const bigint* sub, bool* carry )
  {
    
    bigint z;
    bigintlength i;
    for( i = 0; i < n; i++ )
    {
    
      z = dest[i];
      z -= sub[i];
      if( *carry ) z--;
      
      if( ( !*carry && dest[i] < z ) || ( *carry && dest[i] <= z ) )
        *carry = true;
      else
        *carry = false;
      
      dest[i] = z;
      
    }
    
    return *carry;
    
  }
  
  
  
  
  /*********************************************/
  /* Other multiplication operations           */
  /*********************************************/





  /*
  * Multiplies to Big ints according to basic school method
  * Remark: Bigints a and b must have the same length, which must be of
    form 2^{k}. p points to a Bigint of double size - 2^{k+1} - the
    result is saved in.
  */
  void NaivMultiplication( bigintexpo k, bigint* p, const bigint* a, const bigint* b )
  {
    
    bigintlength i, j;
    bigintlength length = 1 << k;
    
    SetZero( length*2, p );
    
    /* Collect the carries and add them later */
    bigint* overflows = (bigint*)malloc( sizeof(bigint)*length*2 );
    assert( overflows != NULL );
    SetZero( length*2, overflows );
    
    /* main part */
    for( i = 0; i < length; i++ )
    {
      for( j = 0; j < length; j++ ){
        
        long long w1, w2, w3;
        bool carry  = false;
        
        w1 = a[i];
        w2 = b[j];
        w3 = w1*w2;
        
        /*
        * If the rest of the code works properly
        * we can use the following line
        * without fear of memory corruption
        */
        Add( 2, p+(i+j), (bigint*)&w3, &carry );
        if(carry) overflows[i+j+2]++;
        
      }
    }
    
    /* evaluate the carries */
    bool carry = false;
    Add( 2*length, p, overflows, &carry );
    assert(!carry);
    
    free( overflows );
    
  }
 
 
  /*
  * Multiplies to Big ints of size <= 128 according to basic school method
  * Bemerkung: Works like a NaivMultiplication, but it has been optimized
    for and is restricted to the case of k <= 7.
  */
  void NaivMultiplicationRestricted( bigintexpo k, bigint* p, const bigint* a, const bigint* b )
  {
    
    assert( k <= 7 );
    
    unsigned char i, j;
    unsigned char length = 1 << k;
    
    /* Collect the carries and add them later */
    unsigned char overflows[256];
    memset( overflows, 0, length*2 * sizeof(unsigned char) );
    
    
    SetZero( length*2, p );
    
    /* main part */
    for( i = 0; i < length; i++ )
    {
      for( j = 0; j < length; j++ ){
        
        unsigned long long w = (unsigned long long)(a[i]) * (unsigned long long)(b[j]);
        
        *(unsigned long long*)(p+(i+j)) += w;
        if( *(unsigned long long*)(p+(i+j)) < w ) overflows[i+j+2]++;
        
      }
    }
    
    /* process carries */
    short int t;
    bool carry = false;
    for( t = 0; t < 2*length; t++ )
    {
      p[t] += overflows[t];
      if( carry ) p[t]++;
      if( ( !carry && overflows[i] > p[t] ) || ( carry && overflows[t] >= p[t] ) )
        carry = true;
      else
        carry = false;
    }
    assert(!carry);
    
  }
  
  
  
 
  
  
  
  
  
  /*******************************************************/
  /* Karatsuba-Ofmann-Algorithm                          */
  /*******************************************************/
  
  
  /*
  * Multiplies to Big ints according to Karatsuba-Ofmann
  * Bemerkung: Bigints a and b must have the same length, which must be of
    form 2^{k}. p points to a Bigint of double size - 2^{k+1} - the result
    is saved in.
  */
  void Multiply( bigintexpo k, bigint* p, const bigint* a, const bigint* b )
  {
    
    /* calculate length of a and b */
    bigintlength length = 1 << k;
    
    /*
    * if we are below the threshold, switch to school method
    * Die Wechselgrenze wurde empirisch ueber den Daumen geschaetzt
    */  
    if( k <= 5 ){
      NaivMultiplicationRestricted( k, p, a, b );
      return;
    }
    
    /***************************************/
    /* Declaration and initialization      */
    /***************************************/
    
    /* pointers to the low- and high-parts of the factors */
    const bigint *al,*ah,*bl,*bh;
    al = a;
    bl = b;
    ah = a + length/2;
    bh = b + length/2;
    
    /* Pointers to target memory */
    bigint *u1, *u2, *u3, *u4;
    u1 = p;
    u2 = p + length/2;
    u3 = p + length;
    u4 = p + length + length/2;
    
    /* Pointer to heap */
    bigint *heap = (bigint*)malloc( length * sizeof(bigint) );
    assert( heap != NULL );
    bigint *aux1, *aux2;
    aux1 = heap;
    aux2 = heap + length/2;
    
    /* Pointer to products ahbh and albl */
    bigint *ahbh = u3;
    bigint *albl = u1;
    
    /* Memory for some of the carries
    due to performance issues
    */
    bigint overflow = (bigint)0;
    
    
    /******************************/
    /* Calculations               */
    /******************************/
    
    /* Calculate middle product */
    
    /* Calculate (al + ah)(bl + bh) */
    
    /* Calculate the two sums */  
    bool carrya = false;
    bool carryb = false;
    CopyAdd( length/2, u4, al, ah, &carrya );
    CopyAdd( length/2, u1, bl, bh, &carryb );
    
    /* Multiply both */
      
    /* First recursion */  
    Multiply( k-1, aux1, u1, u4 );
    
    /* Do some additions, to calculate the high-part of the product */ 
    
    bool carryt = false;
      
    carryt = false;
    if( carryb ) Add( length/2, aux2, u4, &carryt );
    if( carryt ) overflow++;
  
    carryt = false;
    if( carrya ) Add( length/2, aux2, u1, &carryt );
    if( carryt ) overflow++;
    
    if( carrya && carryb ) overflow++;
    
    /*
    * Now the heap is (al+ah)(bl+bh)
    * We write al*bl and ah*bh directly into the target memory
    */  
    
    /* Calculate albl */
    Multiply( k-1, albl, al, bl );
    
    /* Calculate ahbh */
    Multiply( k-1, ahbh, ah, bh );
    
    /* Sub the two products from the heap */
    
    bool carrys = false;
     
    carrys = false;
    Sub( length, heap, albl, &carrys );
    if( carrys ) overflow--;
    
    carrys = false;
    Sub( length, heap, ahbh, &carrys );
    if( carrys ) overflow--;
    
    /*
    * Add the term at the heap to right place in the target
    * Evaluate the overflows
    */
    
    bool carryq = false;
    
    Add( length, u2, heap, &carryq );
    if( carryq ) overflow++;
    
    if( overflow == 1 ){
      carryq = false;
      Inc( length/2, u4, &carryq );
    }else if( overflow == 2 ){
      carryq = false;
      Inc( length/2, u4, &carryq );
      carryq = false;
      Inc( length/2, u4, &carryq );
    }
        
    /**********************************/
    /* Result is in the target memory */
    /**********************************/
    
    /* free all memory */
    free( heap );   
    
    
    /*{
      bigint* test = malloc( length*2 * sizeof(bigint) );
      NaivMultiplication( k, test, a, b );
      if( Compare( length*2, test, p ) ){
        printf( "Hauptrechnung: %d\n", length );
        OutputBigint( length, a );
        OutputBigint( length, b );
        OutputBigint( length*2, p );
        OutputBigint( length*2, test );
        assert(false);
      }
      free(test);
    }*/

  }
    
    
    
    
    
    
  /*********************************************/
  /* Non-essential operations                  */
  /* for an easier handling                    */
  /*********************************************/
    
  /*
  * Returns an exponent k, s.t. n <= 2^{k}
  * Bemerkung: Absolutely no optimization
  */
  inline bigintexpo getFittingExponent( bigintlength n )
  {
    bigintexpo k = 0;
    while ( (bigintlength)(1L<<k) < n && k <= (bigintexpo)254 ) k++;
    return k;
  }
  
  
    
  /*
  * Multiplies numbers of arbitrary length
  * Remark: It wraps the karatsuba-multiplication, s.t. we can multiply
    numbers whose length is not a power of 2. Absolutely no optimization
    for this
  */
  void Multiplikation( bigint* dest, bigintlength n1, const bigint* fak1, bigintlength n2, const bigint* fak2 )
  {
    
    assert( dest != NULL );
    assert( fak1 != NULL );
    assert( fak2 != NULL );
    
    bigintlength nmax = n1 > n2 ? n1 : n2;
    bigintexpo k = getFittingExponent( nmax );
    
    
    if( (1L<<k) == 0 ){
      printf( "Error: Summands are to long\n" );
      return;
    }
    
    bigint *tempfak1, *tempfak2;
    bigint *tempdest;
    
    tempfak1 = (bigint*)calloc( sizeof(bigint) , (1<<k) ); 
    tempfak2 = (bigint*)calloc( sizeof(bigint) , (1<<k) );
    tempdest = (bigint*)calloc( sizeof(bigint) , (1<<k)*2 );
    
    assert( tempdest != NULL );
    assert( tempfak1 != NULL );
    assert( tempfak2 != NULL );
    
    Copy( n1, tempfak1, fak1 );
    Copy( n2, tempfak2, fak2 );
    
    Multiply( k, tempdest, tempfak1, tempfak2 );
    
    Copy( n1+n2, dest, tempdest );
    
    free( tempfak1 );
    free( tempfak2 );
    free( tempdest );
  } 
  
  
  
  
  
  
  
  
    
    
  
  /*************************************/
  /*********** main program ************/
  /*************************************/
  int main()
  {
    printf( "\nBig Integer multiplication\n\n");
    
    
    /*******************************/
    /* Testing of functionality    */
    /*******************************/
    
    /*
    * For testing, we can use different patterns as control samples
    * Numbers of form 0xFFFFF...FF are fit, as you can immediatly check
      the result by yourself.
    */
    
    printf( "Checking consistency!\n" );
    
    {
      const bigintexpo k = 7;
      const bigintlength l = 1 << k; /* Length */
      
      /*Iteration*/
      long int v = 0, vmax = 10;
      
      for( v = 0; v < vmax; v++ ){
    
        bigint P[l], Q[l];
        bigint R1[2*l], R2[2*l];
        
        bigintlength i;
        srand( clock() + rand() + v );
        
        /* Fill in sample */
        for( i = 0; i < l; i++ )
        {
          /* P[i] = 0xFFFFFFFF; */
          P[i] = rand()*rand();
        }
        
        for( i = 0; i < l; i++ )
        {
          /* Q[i] = 0xFFFFFFFF; */
          Q[i] = rand()*rand();
        }
        
        /* Naiv method */
        NaivMultiplication( k, R1, P, Q );
        
        /* Karatsuba-Ofmann */
        Multiply( k, R2, P, Q );
        
        /* Comparing */
        if( Compare( l*2, R1, R2 ) != 0 )
        {
          printf("Error occurred!\n Length:%ld\n", l );
          printf("Naiv method:\n");
          OutputBigint( l*2, R1 );
          printf("Karatsuba-Ofmann:\n");
          OutputBigint( l*2, R2 );
          return 1;
        }
        
      }
      
    }
    
    printf( "Comparison ok\n\n" );
     
    
    
    /*******************************/
    /* Testing of functionality    */
    /* Numbers of arbitrary length */
    /*******************************/
    
    printf( "Testing multiplikation of arbitrary length numbers!\n" );
    
    {
      
      const bigintlength l_act = 32;
      /* Factors have size 32 in memory */
      /* Only a part of this will be used semantically */
      const bigintlength l_1 = 5;
      const bigintlength l_2 = 17;
      const bigintlength l_prod = l_1 + l_2;
      
      /* iteration*/
      long int v = 0, vmax = 10;
      
      for( v = 0; v < vmax; v++ ){
    
        bigint P[l_act], Q[l_act];
        bigint R1[l_act*2], R2[l_act*2];
        
        bigintexpo k = getFittingExponent( l_1 > l_2 ? l_1 : l_2 );
        
        assert( k == 5 );
        
        bigintlength i;
        srand( clock() + rand() + v );
        
        /* Fill in samples */
        SetZero( l_act, P );
        for( i = 0; i < l_1; i++ )
        {
          /* P[i] = 0xFFFFFFFF; */
          P[i] = rand()*rand();
        }
        
        SetZero( l_act, Q );
        for( i = 0; i < l_2; i++ )
        {
          /* Q[i] = 0xFFFFFFFF; */
          Q[i] = rand()*rand();
        }
        
        SetZero( l_act*2, R1 );
        SetZero( l_act*2, R2 );
        
        /* Naiv method */
        NaivMultiplication( k, R1, P, Q );
        
        /* Karatsuba-Ofmann */
        Multiplikation( R2, l_1, P, l_2, Q );
        
        /* Comparison */
        if( Compare( l_prod, R1, R2 ) != 0 && Compare( l_act*2, R1, R2 ) != 0 )
        {
          printf("Error occured with arbitrary length numbers\n" );
          printf("Naiv method:\n");
          OutputBigint( l_prod, R1 );
          printf("Karatsuba-Ofmann:\n");
          OutputBigint( l_prod, R2 );
          return 1;
        }
        
      }
      
    }
    
    printf( "Comparison ok\n\n" );
    
    
    
    
    /***************/
    /* Performance */
    /***************/
    
    printf( "performance test\n" );
    
    long int t1, t2;
    
    t1 = clock();
    
    {
      const bigintexpo k = 11;
      const bigintlength l = 1 << k; /* Number of digits */
      
      long int v = 0, vmax = 100;
      
      /* printf( "Multiply %ld-times two numbers of length %ld\n", vmax, l ); */
      printf( "Multiply %ld-times two numbers of length %ld in base 2^32-system\n", vmax, l );
      printf( "approx. %lld decimal digits\n", (long long) 9 * l );

      /*
      * We can use several samples:
      * Iterate one specific multiplication
      * A specific subset of mulitplications
      * random numbers
      * ...
      */
      
      for( v = 0; v < vmax; v++ ){
    
        bigint P[l], Q[l];
        bigint R[2*l];
        
        bigintlength i;
        
        srand( time(NULL) * rand() + v*v*v*v );
        for( i = 0; i < l; i++ )
        {
          /* P[i] = 0x12345678; */
          //P[i] = (v << 16) + v;
           P[i] = rand() * UINT_MAX * rand(); 
        }
        for( i = 0; i < l; i++ ){
          /* Q[i] = 0x12345678; */
          //Q[i] = (v << 16) + v;
          Q[i] = rand() * UINT_MAX * rand(); 
        }
        
        Multiply( k, R, P, Q );
        
      }
      
    }
    
    t2 = clock();
    
    printf( "time: %ld0 ms \n", (t2-t1)/10000 );
    
    return 0;
    
    
  }
  
  
  
  
  
  
  
  
