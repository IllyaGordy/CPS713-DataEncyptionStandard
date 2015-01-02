/* CPS713 - Lab #1
 *      Building a mini-DES encryption/decryption
 *
 *      By: Illya Gordiyenko
 *
 *      The Code produces an input initially for the plaintext, the key and a default 
 *      null valued ciphertext. It then runs the encryption algorithm and produces the 
 *      final key. Comments are made though the code to make it easier to understand. 
 *      As well there is a function showbits to allow for easy bit level view of the 
 *      values.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BIT(hex, i) ((hex >> i) & 1)

unsigned int encipher(int startBlock, int keyBlock);
unsigned int PC1(int starterKey);
unsigned int PC2(int left, int right);
unsigned int functionF(int rightSidePlaintext, int key);
void printbitssimple(int n, int size);

/*
 * Mainly used for debuging of code
 *
 */
void showbits(unsigned int x)
{
    int i;
    for(i=(sizeof(int)*8)-1; i>=0; i--)
        (x&(1<<i))?putchar('1'):putchar('0');
    
    printf("\n");
}
/*
 *  Main Class
 * The plaintext and the key are hard coded inside here
 * to change them just re-write them inside
 *
 */
int main(int argc, char *argv[]) { //start of app
   
    
    //Initialize the 3 int which will represent plaintext, key, ciphertext
    
    unsigned int plaintext = 0x31;
    unsigned int key = 0xfa;
    unsigned int ciphertext = 0x00;
    
    printf("Initial Set-up of plaintext, key, and default ciphertext: ");
    printf("\n");
    showbits(plaintext);
    showbits(key);
    showbits(ciphertext);
    printf("\n");
    
    printf("Running the Encryption...\n");
    ciphertext = encipher(plaintext,key);
    
    printf("\n");
    printf("Final versions of plaintext, key, and ciphertext: ");
    printf("\n");
    showbits(plaintext);
    showbits(key);
    showbits(ciphertext);
    printf("\n");
    
}

/*
 * encipher runs the encipher code
 * includes the 16 permutation in a for loop from S-Boxes
 *
 */
unsigned int encipher(int startBlock, int keyBlock){
    int i;
    
    unsigned int text = startBlock;
    
    unsigned int keyArray[16];
    
    int key = PC1(keyBlock); //call PC1
    
    for(i=0; i<16;i++){ //loop for all the keys
        
        //split the key in to two
        unsigned int leftSideKey = key & 0xf;
        unsigned int rightSideKey = (key>>4) & 0xf;
        
        keyArray[i] = PC2(leftSideKey, rightSideKey); //call PC2
        
        key = PC1((leftSideKey << 4) | rightSideKey);
        
    }
    
    
    for(i=0; i<16;i++){ //call one more loop for the text
        unsigned int leftSidePlaintext = text & 0xf;
        unsigned int rightSidePlaintext = (text>>4) & 0xf;
        
        unsigned int returnOfFuntion = functionF(rightSidePlaintext, keyArray[i]);//function
        text = (returnOfFuntion << 4) | rightSidePlaintext; //combine left and right
        
    }
    
    return text;
    
}

/*
 * Takes the key provided and returns permuted keys based on:
 * 12345678
 * ↓↓↓↓↓↓↓↓
 * 23456781
 *
 */
unsigned int PC1(int starterKey){

    int shifted = ((starterKey << 1) | (starterKey >> (8 - 1))) & 0xff;
    
    return shifted;

}

/*
 * Takes the key provided and returns permuted keys based on:
 * 123456
 * ↓↓↓↓↓↓
 * 654321
 *
 */
unsigned int PC2(int left, int right){
    
    int leftSection = left & 0x7;
    int rightSection = right & 0x7;
    
    unsigned int combined = (leftSection << 3) | rightSection;
    //showbits(leftSection);
    //showbits(rightSection);
    //showbits(combined);
    
    return combined;
    
}

/*
 * Does the S-box encryption
 *
 */
unsigned int functionF(int rightSidePlaintext, int key){
    
    int a[4][16] = {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    }; //array of permutations
    
    //slit the right side into seperate bits
    int part0 = rightSidePlaintext & 0x1;
    int part1 = (rightSidePlaintext & 0x2) >> 1;
    int part2 = (rightSidePlaintext & 0x4) >> 2;
    int part3 = (rightSidePlaintext & 0x8) >> 3;
    
    unsigned int combined = (part3 << 5) | (part0 << 4) | (part1 << 3) | (part2 << 2) | (part3 << 1) | part1;
    
    combined = combined ^ key; //XOR on the combines 6 bit text and the 6 bit key
    
    //slit the combined in two individual bits
    int combinedPart0 = combined & 0x1;
    int combinedPart1 = (combined & 0x2) >> 1;
    int combinedPart2 = (combined & 0x4) >> 2;
    int combinedPart3 = (combined & 0x8) >> 3;
    int combinedPart4 = (combined & 0x16) >> 4;
    int combinedPart5 = (combined & 0x32) >> 5;
    
    //Combine into Row and Column numbers
    unsigned int column = (combinedPart4 << 3) | (combinedPart3 << 2) | (combinedPart2 << 1) | combinedPart1;
    unsigned int row = (combinedPart0 << 1) | combinedPart5;
    
    //printf("column: %d, row: %d\n", column, row); Extra Print Function for testing
    
    unsigned int output = a[row][column]; //get the value from array
    
    //split the array out into seperate bits
    int outputPart0 = output & 0x1;
    int outputPart1 = (output & 0x2) >> 1;
    int outputPart2 = (output & 0x4) >> 2;
    int outputPart3 = (output & 0x8) >> 3;
    
    //get the final computed result for the S-box cipher
    int final = (outputPart2 << 3) | (outputPart1 << 2) | (outputPart0 << 1) | outputPart3;
    
    return final;
    
}
