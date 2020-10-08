#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string encrypt(string text, string key);
bool validkey(string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // check key validity
        if (validkey(argv[1]))
        {   
            // Get encryption key
            string key = argv[1];
            
            // Get plaintext
            string plainText = get_string("plaintext: ");
            
            // Display ciphertext
            string cipherText = encrypt(plainText, key);
            printf("ciphertext: %s\n", cipherText);
            return 0;
        }
        // if key is not valid return 1
        else 
        {
            printf("Key must contain 26 characters.\n");
            return 1; 
        }
    }
    // if no key provided return 1
    else if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // if many keys provided return 1
    else 
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
}

string encrypt(string s, string keys)
{
    // ASCII value of a
    int alphabet = 97;
    
    char encrypted;

    // for each character in the string we search for the corresponding value in the key
    for (int i = 0, n = strlen(s); i < n; i++)
    {   
        // 
        for (int j = 0; j < 26; j++)  
        {
            // if charcater of plaintext is lower case, return lower case
            if ((s[i] >= 'a' &&  s[i] <= 'z'))
            {
                // 
                if (s[i] == alphabet + j)
                {
                    encrypted = tolower(keys[j]);
                }

            }
                
            // if charcater of plaintext is upper case, return upper case
            if ((s[i] >= 'A' &&  s[i] <= 'Z'))
            {
                if (s[i] == alphabet - 32 + j)
                {
                    encrypted = toupper(keys[j]);
                }
            }
        }
            
        // replace the value of plaintext if it is an alpha character
        if ((s[i] >= 'a' &&  s[i] <= 'z') || (s[i] >= 'A' &&  s[i] <= 'Z'))
        {
            s[i] = encrypted;
        }
    }
    
    return s;
}


bool validkey(string key)
{
    bool test = 1;
    int count = 0;
    
    for (int i = 0; i < strlen(key); i++)
    {
        // count if a charcter is duplicated in the key 
        for (int j = 0; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                count += 1;
            }
            
        }
        
        // check if there are non-alpha characters in the key
        if (!(tolower(key[i]) >= 'a' &&  tolower(key[i]) <= 'z'))
        {
            test = 0;
        }

    }
    
    // check that the key is valid
    if (test && count == 26)
    {
        return true;
    }
    else 
    {
        return false;
    }

}