/*
    This program encrypts text using a simple Caesar cipher.
    The user inputs the shift value as a command-line argument. All letters are shifted by 
    this amount. Non-alpha characters are preserved as they are.
    
    Written by Joshua Scott for Harvard's 'CS50' online course:
    http://online-learning.harvard.edu/course/cs50-introduction-computer-science
    GitHub: https://github.com/jscott313
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, string argv[])
{
    // Check 2 command line arguments were entered
    if (argc == 2)
    {   
        // Cast string to int
        int key = atoi(argv[1]);
        if (key == 0)
        {
            printf("Key is invalid, enter a number only!\n");
            return 1;
        }
        else
        {
            string textToEncrypt = GetString();
            
            for (int i = 0, length = strlen(textToEncrypt); i < length; i++)
            {
                // If uppercase
                if (isalpha(textToEncrypt[i]) && isupper(textToEncrypt[i]))
                {
                    // Must remove and add 65 since the formula is for index of char, not ascii value
                    textToEncrypt[i] = ((textToEncrypt[i] - 65 + key) % 26) + 65;
                    printf("%c", textToEncrypt[i]);
                }
                // If lowercase
                else if (isalpha(textToEncrypt[i]) && islower(textToEncrypt[i]))
                {
                    textToEncrypt[i] = ((textToEncrypt[i] - 97 + key) % 26) + 97;
                    printf("%c", textToEncrypt[i]);
                }
                // If not a letter, print it as-is
                else
                {
                    printf("%c", textToEncrypt[i]);
                }
            }
            printf("\n");
            return 0;
        }
    }
    // If the user inputs the wrong number of command line arguments, return an error
    else
    {
        printf("After entering './caeser, you must enter the number you wish to use to encrypt!\n");
        return 1;
    }
}
