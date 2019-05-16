/* Eugene Lucino
   12/22/2017	Update: 5/9/2018
   Caesar Cipher Version 2 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 10000   // maximum message size

char message[MAX];  // message to decrypt/encrypt

// table of expected frequencies of the alphabet
double table[] = {8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0,
0.2, 0.8, 4.0, 2.4, 6.7, 7.5, 1.9, 0.1, 6.0,
6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1 };

double freqs[26];       // observed frequencies
double origin[26];      // constant list
double chilist[26];     // chi squares

void cracked();

/* shift = how many letters to shift, ed = encrypt (1) or decrypt (2) */
void cipher(int shift, int ed)
{
    int a;
    for(a=0; a<strlen(message); a++)
    {
        // encryption
        if(ed == 1)
        {
            // if letter is uppercase and adding shift results
            // in a value > 90 ('Z'), subtract 26; else, print letter
            if(isupper(message[a]))
            {
                if(message[a] + shift > 90)
                    message[a] = message[a] + shift - 26;
                else message[a] += shift;
            }
            // do same for lowercase 'z' (> 122)
            else if(islower(message[a]))
            {
                if(message[a] + shift > 122)
                    message[a] = message[a] + shift - 26;
                else message[a] += shift;
            }
        }
        // decryption
        else if(ed == 2)
        {
            if(isupper(message[a]))
            {
                if(message[a] - shift < 65)  // 65 = 'A'
                    message[a] = message[a] - shift + 26;
                else message[a] -= shift;
            }
            else if(islower(message[a]))
            {
                if(message[a] - shift < 97)  // 97 = 'a'
                    message[a] = message[a] - shift + 26;
                else message[a] -= shift;
            }
        }
		printf("%c", message[a]);   // print letter
    }
}

/* ask user how many letters to shift message and encrypt */
void encrypt()
{
    int shift = 0;
    // ask user for shift value
    printf("Enter shift key (number from 1-26). ");
    scanf(" %d", &shift);

    while (shift < 1 || shift > 26)
    {
        printf("Invalid value. Enter a number from 1 to 26. ");
        scanf(" %d", &shift);
    }

    printf("\nEncrypted message:\n");
    cipher(shift, 1);
    printf("\n");
}

/* ask how many letters to shift message backwards */
void decrypt()
{
	int shift = 0;
    char temp[MAX];         // temporary string that copies message
    strcpy(temp, message);

    // ask for a key number and check if it is valid
    printf("Enter shift key (number from 1-26). If key is unknown, enter '0' to decode. ");
    scanf(" %d", &shift);

    while(shift < 0 || shift > 26)
    {
        printf("Invalid value. Enter another number. ");
        scanf(" %d", &shift);
    }

    // if 0 is entered, run special codebreaker
    if(shift == 0)
    {
        printf("\nDecrypted message: ");
        cracked();
    }
	// else run codebreaker with key number
    else
    {
        printf("\nDecrypted message:\n");
        cipher(shift, 2);
        printf("\n");
    }
}

// count number of letters in a string
int letters()
{
    int count = 0, x;
    for(x=0; x < strlen(message); x++)
        if (isalpha(message[x])) count++;
    return count;
}

// counts number of a given character in a string
int count(char key)
{
    int freq = 0, c;
    for(c=0; c < strlen(message); c++)
        if (message[c] == key) freq++;
    return freq;
}

// calculates percentage of one int with respect to another
double percent(int a, int b)
{
    double x = (double)a, y = (double)b;
    if (a > b) return ((y / x) * 100);
    return ((x / y) * 100);
}

// returns a list of percentage frequencies for each letter in a string
void frequency(int total)
{
    int y = 0;
    char x;
    for(x = 'a'; x <= 'z'; x++)
    {
        freqs[y] = percent(count(x), total);
        y++;
    }
}

// rotates a list of doubles n places to the left, wrapping around list
void rotate(int n)
{
    int x, i;
    for(x = 0; x < n; x++)
    {
        double temp = freqs[0];
        for (i = 0; i < 25; i++)
            freqs[i] = freqs[i + 1];
        freqs[25] = temp;
    }
}

// calculates the chi square statistic
double chisqr()
{
    int i = 0;
    double result = 0.0;
    for(i = 0; i < 26; i++)
        result += (pow(freqs[i] - table[i], 2)) / table[i];
    return result;
}

// returns index of the smallest value of a list
int position()
{
    int c, location = 0;
    double min = chilist[0];

    for (c=1; c<26; c++)
    {
        if(chilist[c] < min)
        {
            min = chilist[c];
            location = c;
        }
    }
    return location;
}

// swap two lists of frequencies
void swap(double old[26], double next[26])
{
    int x;
    for(x = 0; x < 26; x++)
        old[x] = next[x];
}

// decodes a string based on chi square calculations
void cracked()
{
    int n, total = letters();
    swap(origin, freqs);        // get original frequencies

    for(n = 0; n < 26; n++)
    {
        frequency(total);       // calculate letter frequencies
        rotate(n);              // rotate n spaces
        chilist[n] = chisqr();  // calculate chi square of each rotation
        swap(freqs, origin);    // get back original frequencies
    }

    // use position of min value of list as shift factor to decode
    printf("(%d letters back)\n", position());
    cipher(position(), 2);
    printf("\n");
}

int main(void)
{
    // introduction
    printf("\n");
    printf("+--------------------------------------------+\n");
    printf("|  Caesar Cipher Ver. 2.0 by Eugene Lucino.  |\n");
	printf("| Encrypt or decrypt a message or text file. |\n");
    printf("+--------------------------------------------+\n");
    printf("\n");
	
	char dir, fil;
    int x = 0, c;
    printf("Would you like to encrypt (e) or decrypt (d) a message?\n");
    scanf(" %c", &dir);

    while(dir != 'e' && dir != 'd' && dir != 'E' && dir != 'D')
    {
        printf("Invalid choice. Encrypt = 'e' or 'E'. Decrypt = 'd' or 'D'.\n");
        scanf(" %c", &dir);
    }

    printf("Are you using a text file? ('y'/'Y' for yes)\n");
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
            if(feof(ifp)) break;	// check for end of file
            else message[x] = c;    // put char into message
            x++;
        }
    }
    else
    {
        printf("Enter your message.\n");    // ask user to enter the string
        scanf(" %[^\n]s", message);         // avoids stopping at spaces
    }

    // encrypting or decrypting?
    if(dir == 'e' || dir == 'E') encrypt();
    else decrypt();

    return 0;
}
