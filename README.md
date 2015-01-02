CPS713 - Lab #1 - Data Encyption Standard

Building a mini-DES encryption/decryption

By: Illya Gordiyenko

The Code produces an input initially for the plaintext, the key and a default null valued ciphertext. It then runs the encryption algorithm and produces the final key. Comments are made though the code to make it easier to understand. As well there is a function showbits to allow for easy bit level view of the values.

============================

Assignment Description: 

<b>Background</b>: The main purpose of this lab is for you to gain hands-on experience in the basic cryptographic algorithms covered in class, in par- ticular block ciphers such as Data Encryption Standard (DES). The block cipher to be used for this lab is described below and referred to as Mini-DES (m-DES).

<b>Mini-DES (m-DES)</b>: This block cipher is intended to mimic a simplified DES encryption algorithm. It is strongly recommended that you review your notes about DES from the lectures, the textbook, and the description of DES algorithm in FIPS 46. m-DES is an 8-bit block cipher that uses an 8-bit key (all the bits in the key are used in generating the 6-bit round keys). For simplicity, the initial IP and the final IP−1 permutations are NOT used in m-DES.

Key Schedule: The key schedule of m-DES uses the following Permutation Choice 1 (PC1) in its initialization stage:

1 2 3 4 5 6 7 8<br>
↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓<br>
2 3 4 5 6 7 8 1

That is PC1 will map the first bit of the key to the second bit position, the second bit is moved to the third position, the third bit moved to the forth, and so on.


The eight bit output of PC1 is then divided to two four-bit halves, which will shift to the left by one or two position similar to that of DES (Consult FIPS 46 for details). The key schedule will produce 16 round keys (the number of iteration in m-DES). The output of the shifts in each round will be followed by the following Permutation Choice 2 (PC2), which will select the last three bits of each half and permutes the resulting six concatenated bits using the following transformation:

1 2 3 4 5 6<br>
↓ ↓ ↓ ↓ ↓ ↓<br>
6 5 4 3 2 1

Enciphering Algorithm: m-DES is a Feistel cipher similar to DES, that is the 8-bit input plaintext is divided to two four-bit halves, where after each iteration
Ln = Rn−1
Rn = Ln−1 ⊕ f(Rn−1,Kn)
Where n ranges from 1 to 16, Kn is the n-th round key, and the output of the algorithm (i.e. the ciphertext) is R16L16.
The round function f uses the following expansion function E: E(b<sub>0</sub>b<sub>1</sub>b<sub>2</sub>b<sub>3</sub>) = <sub>b3</sub>b<sub>0</sub>b<sub>1</sub>b<sub>2</sub>b<sub>3</sub>b<sub>1</sub>.
The result is XORed with the corresponding round key, and is inputed to the following S-box (m-DES uses only one S-box):

                S
14  4  13  1  2  15  11  8  3  10  6  12  5  9  0  7<br>
0  15  7  4  14  2  13  1  10  6  12  11  9  5  3  8 <br>
4  1  14  8  13  6  2  11  15  12  9  7  3  10  5  0 <br>
15  12  8  2  4  9  1  7  5  11  3  14  10  0  6  13<br>

The output of the S-box is the element in the table (4-bits) is determined by the input (the first and the last bit determines the row and the middle 4-bits determines the column), and will be permuted using the following transformation:

1 2 3 4<br>
↓ ↓ ↓ ↓<br>
2 3 4 1


Implement code that enciphers and deciphers using m-DES block cipher. Add suitable and clear comments to your code to make it more readable (and easier to debug for yourself!). Your submission should include all source files used, the binary generated (if any), sample files, and clear documentation on what is included and how the code can be executed. For your code development, you have to use C. You can assume that the plaintext is already in a binary form.
