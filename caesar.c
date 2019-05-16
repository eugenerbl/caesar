/* Eugene Lucino
   COP 3223
   11/22/2016
   Caesar Cipher */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10000   // maximum message size

char message[MAX];  // message to change


/* shift = how many letters to shift, ed = encrypt (1) or decrypt (2);
   shifts each letter and prints complete message */
void cipher(int shift, int ed)
{
    int a;
    for(a=0; a<strlen(message); a++)
    {
        // print spaces and other characters
        if(!isalpha(message[a]))
            printf("%c", message[a]);

        // encryption
        else if(ed == 1)
        {
            // if letter is uppercase and adding shift results
            // in a value > 'Z' (90), subtract 26
            if(isupper(message[a]))
            {
                if(message[a] + shift > 90)
                    message[a] = message[a] + shift - 26;
                else
                    message[a] += shift;
                printf("%c", message[a]);   // print letter
            }
            // do same for lowercase 'z'
            else if(islower(message[a]))
            {
                if(message[a] + shift > 122)
                    message[a] = message[a] + shift - 26;
                else
                    message[a] += shift;
                printf("%c", message[a]);
            }
        }
        // decryption
        else if(ed == 2)
        {
            if(isupper(message[a]))
            {
                if(message[a] - shift < 65)  // 'A'
                    message[a] = message[a] - shift + 26;
                else
                    message[a] -= shift;
                printf("%c", message[a]);
            }
            else if(islower(message[a]))
            {
                if(message[a] - shift < 97)  // 'a'
                    message[a] = message[a] - shift + 26;
                else
                    message[a] -= shift;
                printf("%c", message[a]);
            }
        }
    }
}

/* ask user how many letters to shift message and encrypt */
void encrypt()
{
    int shift = 0;

    // ask user for shift value
    printf("Enter shift key (1-26).\n");
    scanf(" %d", &shift);

    while (shift < 1 || shift > 26)
    {
        printf("Invalid value. Enter another number.\n");
        scanf(" %d", &shift);
    }

    printf("\nEncrypted message:\n");
    cipher(shift, 1);       // call to cipher (encryption)
    printf("\n");
}

/* ask how many letters to shift message backwards;
   if shift is unknown, print all possible shifts */
void decrypt()
{
    int shift = 0, b;

    // temporary string that copies message
    char temp[MAX];
    strcpy(temp, message);

    // ask for a key number and check if it is valid
    printf("Enter shift key (1-26). ");
    printf("If key is unknown, enter '0' to print every shift.\n");
    scanf(" %d", &shift);

    while(shift < 0 || shift > 26)
    {
        printf("Invalid value. Enter another number.\n");
        scanf(" %d", &shift);
    }

    // if 0 is entered, run cipher for all values 1-25
    if(shift == 0)
    {
        printf("\nHere are all possible shifts:\n");
        for(b = 1; b < 26; b++)
        {
            printf(" -%2d: ", b);
            strcpy(message, temp);  // make sure original message is always used
            cipher(b, 2);
            printf("\n");
        }
    }
    else
    {
        printf("\nDecrypted message:\n");
        cipher(shift, 2);   // call to cipher (decryption)
        printf("\n");
    }
}

int main(void)
{
    char dir, fil;
    int x = 0, c;

    // introduction
    printf("\n");
    printf("+--------------------------------------------------+\n");
    printf("| Welcome to the Caesar Cipher! Encrypt or decrypt |\n");
    printf("|     an input message or file of your choice.     |\n");
    printf("+--------------------------------------------------+\n");
    printf("\n");

    printf("Would you like to encrypt (e) or decrypt (d) a message?\n");
    scanf(" %c", &dir);

    while(dir != 'e' && dir != 'd' && dir != 'E' && dir != 'D')
    {
        printf("Invalid choice. Encrypt = 'e' or 'E'. Decrypt = 'd' or 'D'.\n");
        scanf(" %c", &dir);
    }

    printf("Are you encrypting or decrypting from a text file? ('y' for yes)\n");
    scanf(" %c", &fil);

    if(fil == 'y' || fil == 'Y')
    {
        FILE *ifp;
        char filename[100];
        printf("Enter the file name.\n");
        scanf("%s", filename);
        ifp = fopen(filename, "r");
        if(ifp == NULL)
        {
            printf("Error: File not found.\n");
            return 0;
        }
        printf("\n");

        while(1)
        {
            c = fgetc(ifp);         // get next character
            if(feof(ifp))           // check for end of file
                break;
            else message[x] = c;    // put char into message
            x++;
        }
    }
    else
    {
        printf("Enter your message.\n");    // ask user to enter the string
        scanf(" %[^\n]s", message);         // avoids stopping at spaces
    }

    printf("\n");
    // encrypting or decrypting?
    if(dir == 'e' || dir == 'E')
        encrypt();
    else
        decrypt();

    return 0;
}
