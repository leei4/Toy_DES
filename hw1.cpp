//	Homework 1 for Network Cryptography
//	Written by Ian Lee
//	9/8/2018

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include <bitset>
#include <bits/stdc++.h>

using namespace std;

//this functions is the initial P-box for the DES
string i_permutation(bitset<8> b_s ){
	string return_s;
	string temp = b_s.to_string();
	//reconstructs the string in the order based upon the permutation
	return_s.push_back(temp[1]);
	return_s.push_back(temp[5]);
	return_s.push_back(temp[2]);
	return_s.push_back(temp[0]);
	return_s.push_back(temp[3]);
	return_s.push_back(temp[7]);
	return_s.push_back(temp[4]);
	return_s.push_back(temp[6]);

	return return_s;
}
//this function takes in a 4 bit sequence and permutes & expands it to an 8 bit sequence
string four_bit_expansion(string p1){
	string eight_string;

	eight_string.push_back(p1[3]);
	eight_string.push_back(p1[0]);
	eight_string.push_back(p1[1]);
	eight_string.push_back(p1[2]);

	eight_string.push_back(p1[1]);
	eight_string.push_back(p1[2]);
	eight_string.push_back(p1[3]);
	eight_string.push_back(p1[0]);

	return eight_string;
}
//permutes the key after the initial key generation
string p_ten(bitset<10> b_s){
	string temp = b_s.to_string();
	string return_s;

	return_s.push_back(temp[2]);
	return_s.push_back(temp[4]);
	return_s.push_back(temp[1]);
	return_s.push_back(temp[6]);
	return_s.push_back(temp[3]);
	return_s.push_back(temp[9]);
	return_s.push_back(temp[0]);
	return_s.push_back(temp[8]);
	return_s.push_back(temp[7]);
	return_s.push_back(temp[5]);

	return return_s;
}
//permutes 2 4 bit expansions and then concatenates them
string p_eight(string sub_key1, string sub_key2){
	string temp = sub_key1 + sub_key2;
	string return_s;

	return_s.push_back(temp[5]);
	return_s.push_back(temp[2]);
	return_s.push_back(temp[6]);
	return_s.push_back(temp[3]);
	return_s.push_back(temp[7]);
	return_s.push_back(temp[4]);
	return_s.push_back(temp[8]);
	return_s.push_back(temp[9]);

	return return_s;
}
string p_eight_final(string input){
	string return_s;

	return_s.push_back(input[3]);
	return_s.push_back(input[0]);
	return_s.push_back(input[2]);
	return_s.push_back(input[4]);
	return_s.push_back(input[6]);
	return_s.push_back(input[1]);
	return_s.push_back(input[7]);
	return_s.push_back(input[5]);

	return return_s;
}
//permutes the 4 bit sequence
string p_four(string input){
	string return_s;

	return_s.push_back(input[1]);
	return_s.push_back(input[3]);
	return_s.push_back(input[2]);
	return_s.push_back(input[0]);

	return return_s;
}
//left shifts the 5 bit sequences
string left_shift(string input){
	string shifted;

	shifted.push_back(input[1]);
	shifted.push_back(input[2]);
	shifted.push_back(input[3]);
	shifted.push_back(input[4]);
	shifted.push_back(input[0]);

	return shifted;
}
//This function performs necessary calls, and substitions for to permute
string F_function(string right_input, string key){
	//S boxes are set to compare the binary strings
	string s0[4][4] = { {"01","00","11","10"}, {"11","10","01","00"}, {"00","10","01","11"}, {"11","01","11","10"}};
	string s1[4][4] = { {"00","01","10","11"}, {"10","00","01","11"}, {"11","00","01","00"}, {"10","01","00","11"} }; 

	string eight_bit = four_bit_expansion(right_input);
	bitset<8> pre_key = bitset<8>(eight_bit);
	bitset<8> k1 = bitset<8>(key);

	//insert XOR
	pre_key ^=  k1;
	//eight_bit now contains the 8 bit string after XOR
	eight_bit = pre_key.to_string();

	string four_bit1 = eight_bit.substr(0,4);
	string four_bit2 = eight_bit.substr(4,4);
	
	string two_bit1 = "";
	string two_bit2 = "";
	
	//converts the first 2 bits
	two_bit1.push_back(four_bit1[1]);
	two_bit1.push_back(four_bit1[2]);

	bitset<2> two_bit_col = bitset<2>(two_bit1);
	int col = (two_bit_col.to_ulong());
	
	//converts the second 2 bits
	two_bit2.push_back(four_bit1[0]);
	two_bit2.push_back(four_bit1[3]);
	bitset<2> two_bit_row = bitset<2>(two_bit2);
	int row = (two_bit_row.to_ulong());
	
	//plug into S-box
	string left = s0[row][col];

	bitset<2> two_bit_left = bitset<2>(left);

	two_bit1 = "";
	two_bit2 = "";
	//pass to S1
	two_bit1.push_back(four_bit1[1]);
	two_bit1.push_back(four_bit1[2]);

	two_bit_col = bitset<2>(two_bit1);
	col = (two_bit_col.to_ulong());
	
	two_bit2.push_back(four_bit1[0]);
	two_bit2.push_back(four_bit1[3]);
	
	two_bit_row = bitset<2>(two_bit2);
	row = (two_bit_row.to_ulong());
	
	//plug into S-box
	string right = s1[row][col];

	bitset<2> two_bit_right = bitset<2>(right);

	string second = s1[row][col];
	//concatenate strings
	string four_preperm = left + right; 

	//combine to 4 bit
	string four_bit_final = p_four(four_preperm);

	return four_bit_final;
}
int main(int argc, char* argv[]){
///////////////////////////////////////////////////////////////////

	string key = "1010011010";//user's secret key
	bitset<10> key_bs = bitset<10>(key);
	string p_key = p_ten(key_bs);

	//break permuted 10 bit key into 2 5 bit keys
	string sub_key1 = p_key.substr(0,5);
	string sub_key2 = p_key.substr(5,5);

	//left shift each key, by wrapping around
	sub_key1 = left_shift(sub_key1);
	sub_key2 = left_shift(sub_key2);

	//first permutation of eight
	string key1 = p_eight(sub_key1, sub_key2);

	//second left shift
	sub_key1 = left_shift(sub_key1);
	sub_key2 = left_shift(sub_key2);

	//second permutation of eight
	string key2 = p_eight(sub_key1, sub_key2);
///////////////////////////////////////////////////////////////////
	vector<bitset<8>> string_bits;
	vector<string> message;
	string temp;

	string encrypt_decrypt = "";
	string line;
	string user_input;

	//print statements for UI
	cout << "choose whether you want to encrypt or decrypt a file" << endl;
	cout << "1--Encrypt" << endl;
	cout << "2--Decrypt" << endl;
	cout << "3--Quit" << endl;
	cin >> encrypt_decrypt;

	if(encrypt_decrypt == "1"){
		cout << "please enter the name of the file you want encrypted" << endl;
		cin >> user_input;

		ifstream myfile;
		myfile.open(user_input);
		//iterates through file and breaks each line into sets of 8.
		if(myfile.is_open()){
			while(getline(myfile,line)){
				//code to iterate through everything about 
				for(int i = 0; i < line.size(); ++i){
					string_bits.push_back(bitset<8>(line.c_str()[i]));
				}
			}
		myfile.close();
		}
		//saves them as binary strings of sequence 8
		for(int i = 0; i < string_bits.size(); i++){
			message.push_back(i_permutation(string_bits[i]));
		}

		//begin F function
		string cipher_message = "";
		for(int i = 0; i < message.size(); i++){
			//cout << message[i] << endl;
			string four_bits1 = message[i].substr(0,4);
			string four_bits2 = message[i].substr(4,4);

			//F function call
			string four_bit_f = F_function(four_bits2, key1);

			//converts left and right bit sequences into bitsets
			//to XOR the two
			bitset<4> four_bitset_L = bitset<4>(four_bits1);
			bitset<4> four_bitset_R = bitset<4>(four_bit_f);

			four_bitset_R ^= four_bitset_L;
			//runs second round of F function and coverts the previous
			// 4 bit sequence into a string
			string second_F = four_bitset_R.to_string();
			string second_FR = F_function(second_F, key2);

			//converts the second round of cycle into bitsets
			//to perform XOR operation
			four_bitset_L = bitset<4>(four_bits2);
			four_bitset_R = bitset<4>(second_FR);
			four_bitset_L ^= four_bitset_R;

			//converts bitset into a string and the runs the final inverse
			//permutations.
			string left_final = four_bitset_L.to_string();
			string cipher = left_final + second_F;
			cipher = p_eight_final(cipher);

			//converts binary values into characters then
			//concatenates for final string.
			bitset<8> cipher_final = bitset<8>(cipher);
			int c = int(cipher_final.to_ulong());
			cipher_message += c;
		}
		ofstream file1;
		file1.open("encrypt.txt");
		file1 << cipher_message + "\n";
		file1.close();
	}
	else if(encrypt_decrypt == "2"){
		cout << "please enter the name of the file you want decrypted" << endl;
		cin >> user_input;

		ifstream myfile;
		myfile.open(user_input);

		if(myfile.is_open()){
			while(getline(myfile,line)){
				for(int i = 0; i < line.size(); ++i){
					string_bits.push_back(bitset<8>(line.c_str()[i]));
				}
			}
		myfile.close();
		}

		for(int i = 0; i <  string_bits.size(); i++){
			message.push_back(i_permutation(string_bits[i]));
		}
		//begin F function
		string cipher_message = "";
		for(int i = 0; i < message.size(); i++){
			string four_bits1 = message[i].substr(0,4);
			string four_bits2 = message[i].substr(4,4);

			string four_bit_f = F_function(four_bits2, key2);

			bitset<4> four_bitset_L = bitset<4>(four_bits1);
			bitset<4> four_bitset_R = bitset<4>(four_bit_f);

			four_bitset_R ^= four_bitset_L;

			string second_F = four_bitset_R.to_string();
			string second_FR = F_function(second_F, key1);

			four_bitset_L = bitset<4>(four_bits2);
			four_bitset_R = bitset<4>(second_FR);
			four_bitset_L ^= four_bitset_R;

			string left_final = four_bitset_L.to_string();
			string cipher = left_final + second_F;
			cipher = p_eight_final(cipher);

			bitset<8> cipher_final = bitset<8>(cipher);
			int c = int(cipher_final.to_ulong());
			cipher_message += c;
		}
		ofstream file1;
		file1.open("decrypt.txt");
		file1 << cipher_message + "\n";
		file1.close();
	}
	//option 3 has been choosen, exit the program.
	else{
		exit(0);
	}
}