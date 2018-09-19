Readme for HW1 Toy DES implementation

To use this program you just have to provide a file for it to encrypt and read through.
The user will be prompted for this and whether they wanted a file encrypted of decrypted.
After the encryption/ decryption is complete the program will write the results to a text file
called "encrypted.txt" or "decrypted.txt" respectively.

Key Creation:
The user enters a ten bit key for use during the encryption. The ten bit then undergoes the first
permutation of ten bits in which the values of the key are shuffled around and the position is
scrambled. For this permutation I used the P10 provided in the slides diagram. After the
permuted ten bit key is returned It will be the split into two five bit keys of positions of
1 to 5 and positions 6 to 10. Each respective 5 bit key is then left shifted. This is done by
taking the first value in the 5 bit sequence, appending it to the end, and then shifting every 
other value up by one. These two left shifted sequences are combined then permutated again by
the function p_eight. This permutation determines the first key (K1) needed for the first F
function. The two 5 bit left shifted sequences are left shifted one more time and then permuted
once again to obtain the second key (K2) for the second round of F functions. At this point
the key generation is complete.

Encryption:
We take the input text and break it down into individual 8 bit segments which are then passed
to the i_permutation function to be converted into binary and permuted. The new permutation
is then split into two 4 bit sequences. The left 4 bit sequence is passed directly to the XOR
and then the right one is passed into the F function. The 4 bit sequence from the F function and
the left 4 bit sequence are then XOR'ed with one another, the result is then passed into another
F function, this time using the second Key (K2). The 4 bit sequence returned by our second F
function is the XOR'ed with the right 4 bit sequence that was passed into the first F function.
This new 4 bit XOR'ed value is then concatentated with the XOR'ed value from the previous XOR
and then permuted into an 8 bit sequence which is our cipher text. It is then returned. 

Decryption:
This process is nearly identical to the encryption process except that it uses Key 2(K2) during
the first F function instead of Key 1(K1), and uses Key 1(K1) instead of Key 2(K2) during the 
second F function.

F Function:
The F Function takes in an 8 bit key (either K1 or K2) and a 4-bit input. The 4 bit input is
is then expanded into a an 8 bit function and permutated. This 8 bit sequence is then XOR'ed
with K1 or K2. The 8 bit key is then split into two 4 bit keys and passed either to Substitution
Matrix S0 (for the left 4 bit sequence) or to Sustitution Matrix S1 (for the right 4 bit sequence).
Each four bit sequence is then split into 2 new values to determine which value is returned by
the Substitution matrix. To determine which value the substitution matrix returns we take the 
2nd and 3rd bit from our 4 bit sequence and then we concatenate them to determine the column value.
we then take the 1st and 4th bit and perform the same process to determine the row of the
substitution matrix. the value at our row and column is then converted into its binary value
and returned as a 2 bit sequence. We then concatenate our 2 bit sequences from S0 and S1 and
pass this new 4 bit sequence into the last permutation which is then returned by the F function.
