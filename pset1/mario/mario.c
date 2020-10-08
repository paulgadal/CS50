#include <cs50.h>
#include <stdio.h>

void height(int n);

int main(void)
{
    int n;
    // Ask user to set height between 1 and 8
    do
    {
        n = get_int("Height: \n");
    } 
    while (n < 1 || n > 8);
    
    // Plot the pyramid to the height set by user 
    height(n);
}


void height(int n)
{
    int i;
    int j;
    int k;
    int l;
    
    for (i = 0; i < n ; i++)
    {
        // print left side of the pyramid
        for (j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
            
        for (k = i; k >= 0; k--)
        {
            printf("#");
        }
        
        // print gap between adjacent pyramids    
        printf("  ");
        
        // print right side of the pyramid
        for (l = i; l >= 0; l--)
        {
            printf("#");
        }
        
        printf("\n");
    }
}

