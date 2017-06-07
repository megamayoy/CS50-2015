#include <stdio.h> 
#include <cs50.h> // needed to use GetFloat() function
#include <math.h> // math library is needed to use the round function
int main(void)
{
    float dollars; 
    int cents;
    int  num_of_coins = 0;

  // prompt the user to input a psoitive value 

    do
    {    
        printf("O hai! How much change is owed?\n");
        // input money in dollars
        dollars = GetFloat(); 
    }
    while ( dollars < 0 );

    // converting from dollars to cents
    
    dollars = dollars * 100;
    // rounding the cents to get an integer 
    cents = ( int ) round( dollars ) ;
    
    
// divide the cents to the largest possible currency
      // cents is equal to zero
    while ( cents != 0 )
    {  
    // quarters=25 cents,dimes=10cents,nickles=5 cents,pennies=1 cent
        if ( cents >= 25 ) 
        {
            num_of_coins += cents / 25; 
            cents = cents % 25;
        }
    
       else if ( cents < 25 && cents >= 10 )
        {
            num_of_coins += cents / 10;
            cents = cents % 10;
        }
       
       else if ( cents < 10 && cents >= 5 )
        {      
            num_of_coins += cents / 5;
            cents = cents % 5;
        }
       
       else if ( cents < 5 && cents >= 1 )
        {
            num_of_coins += cents;
            cents = cents % 1;
        }
    
    }
    
    // print the minimum number of coins
    printf("%d\n", num_of_coins);   
 }   
    
   
