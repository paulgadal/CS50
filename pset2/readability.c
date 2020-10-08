#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int count_letters(string s);
int count_words(string s);
int count_sentences(string s);


int main(void)
{
    // Get input text from user
    string text = get_string("Text: ");

    // Compute the different variable used to compute the index
    float l = (float) count_letters(text) * 100 / count_words(text);
    float s = (float) count_sentences(text) * 100 / count_words(text);

    // Compute the index (rounded value)
    int index = round(0.0588 * l - 0.296 * s - 15.8);
    
    // Display Grade depending on index value
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else 
    {
        printf("Grade %i\n", index);
    }

}


int count_letters(string s)
{   
    int letters = 0;
    
    // Count number of letters that are like [a-zA-Z]
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 'a' &&  s[i] <= 'z') || (s[i] >= 'A' &&  s[i] <= 'Z'))
        {
            letters += 1;
        }
    }
    return letters;
}

int count_words(string s)
{   
    // Always one word before a space
    int words = 1;
    
    // Count the number of spaces 
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ')
        {
            words += 1;
        }
    }
    return words;
}

int count_sentences(string s)
{   
    int sentences = 0;
    
    // Count the number of characters like . ! ?
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            sentences += 1;
        }
    }
    return sentences;
}