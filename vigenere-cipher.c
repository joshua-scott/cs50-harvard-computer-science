/*
    This program encrypts text using a Vigenere cipher, which uses a series of different 
    Caeser ciphers based on the letters of a keyword.
    The user inputs the key as a command-line argument. 
    Non-alpha characters are preserved as they are.
    
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
    // If the user inputs the wrong number of command line arguments, return an error
    if (argc != 2)
    {
        printf("After entering './vigenere', you must enter the key you wish to use to encrypt!\n");
        return -1;
    }
    // Else begin encrypting!
    else
    {   
        string key = argv[1];
        int keyLength = strlen(key);
        // e.g. for a 3-letter key, index locations are 0, 1, 2
        int maxIndex = keyLength - 1; 
        
        // Checks key is only letters, and ensures it's all lowercase (so ascii int is predictable)
        for (int i = 0; i < keyLength; i++)
        {
            if (!isalpha(key[i]))
            {
                printf("Key is invalid, enter letters only!\n");
                return 1;
            }
            else if (isupper(key[i]))
                key[i] = key[i] + 32;
        }
        
        // Get input string from user to encrypt        
        string textToEncrypt = GetString();

        //Encrypt input string using each letter of the key as the shift value
        for (int i = 0, textLength = strlen(textToEncrypt), keyLetter = 0; i < textLength; i++)
        {
            if (keyLetter > maxIndex)
                keyLetter = 0;
            
            // How many places to shift the current letter by
            // (it's -97 to change from ASCII value to index value, e.g a = 0, b = 1...)
            int shiftValue = key[keyLetter] - 97;
                    
            // If letter is uppercase
            if (isalpha(textToEncrypt[i]) && isupper(textToEncrypt[i]))
            {
                // Must remove and add 65 since the formula is for index of char, not ascii value
                textToEncrypt[i] = ((textToEncrypt[i] - 65 + shiftValue) % 26) + 65;
                printf("%c", textToEncrypt[i]);
                keyLetter++;
            }
            // If letter is lowercase
            else if (isalpha(textToEncrypt[i]) && islower(textToEncrypt[i]))
            {
                textToEncrypt[i] = ((textToEncrypt[i] - 97 + shiftValue) % 26) + 97;
                printf("%c", textToEncrypt[i]);
                keyLetter++;
            }
            // If not a letter, print it as-is
            else
                printf("%c", textToEncrypt[i]);
        }
        printf("\n");
        return 0;
    }

}
