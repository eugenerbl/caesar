# Caesar Ciphers
A set of two Caesar Cipher programs written in C. Encrypts and decrypts phrases and text files.

Caesar cipher- shifts each letter in a message by a specific number (a key value) of letters

Author: **Eugene Lucino**

## Features
- encryption
- decryption
- reading text files (.txt)
- can decrypt with or without knowing the key value

## Files Included

### caesar.c
- Decrypts using brute force if key is unknown.
- Prints out all 26 possible shifts on the terminal window.

### caesar2.c
- A more advanced mode of decryption.
- Uses letter frequencies and the chi square statistic to mathematically determine the key number.
- **NOTE:** This method may not decrypt properly for messages that are very short or contain an unusual distribution of letters.

## Setup

- Clone this repo using ```https://github.com/eugenerbl/caesar```
- Open a terminal window.
- Navigate to the folder containing the caesar file.
- Compile:
```
gcc -lm -o caesar caesar.c
```
- Execute:
```
caesar
```
- Follow the prompts on the terminal to complete the program.

## Using text files

- Create a text file (with extension .txt).
- Move the text file into the same folder as the caesar files.
- Follow the Setup steps above.

## License

This project is licensed under the MIT License - see [LICENSE.md](LICENSE.md)
