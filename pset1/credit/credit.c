#include <cs50.h>
#include <stdio.h>

bool checksum(long n);
int card_len(long n);
int first_digits(long n);

int main(void)
{
    // Ask user to set his card number
    long n = get_long("Number: \n");
    
    // Check if the credit card is valid
    bool test = checksum(n);
    int card = card_len(n);
    int digits = first_digits(n);

    if (test)
    {
        if (card == 15 && (digits == 34 || digits == 37))
        {
            printf("AMEX\n");
        }
        else if (card == 16 && (digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((card == 16 || card == 13) && ((digits - digits % 10) / 10) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
        
    }
    else
    {
        printf("INVALID\n");
    }
}


bool checksum(long n)
{
    int a = 0;
    int checksum = 0;
    bool multiplied = false;
    bool test;

    // compute checksum
    do
    {
        // digit multiplied by 2 
        if (multiplied)
        {
            a = 2 * (n % 10);
            if (a >= 10)
            {
                a = 1 + a % 10;
            }
            multiplied = false;
            
        }
        // digit not multiplied 
        else
        {
            a = n % 10;
            multiplied = true;
        }
        
        n = (n - n % 10) / 10;
        checksum = checksum + a;
        
    }
    while (n > 0);
    
    
    // check if checksum last digit is 0
    if (checksum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}    
    
int card_len(long n)
{
    // count digits in the card number
    int i = 0;
    do
    {
        n = (n - n % 10) / 10;
        i++;
    }
    while (n > 0);    
    
    return i;
}

int first_digits(long n)
{
    // get the first 2 digits
    do
    {
        n = (n - n % 10) / 10;
    }
    while (n > 100);    
    
    return n;
}