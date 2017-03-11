#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;


string rlencode(ifstream& input){
	string result = "";
	int count = 1;
	char currentChar;
	char nextChar;
	input.get(currentChar);


	while(!input.eof()){
		nextChar = input.get();
		if(nextChar == currentChar){
			count++;
			currentChar = nextChar;
		}else{
			result += currentChar;
			if(count > 2){
				result += "[" + to_string(count - 2) + "]";
			}else if (count == 2){
				result += currentChar;
			}
			count = 1;
			currentChar = nextChar;
		}
	}
	
	return result;
}

void rlencode(ifstream& input, ofstream* ptrFileOutput){
	unsigned int count = 1;
	// char firstChar;
	unsigned char currentChar;
	unsigned char nextChar;
	unsigned int num;
	unsigned char seg1, seg2, seg3, seg4;
	
	currentChar = (unsigned char)input.get();

	while(!input.eof()){
		nextChar = (unsigned char)input.get();
		if(nextChar == currentChar){
			count++;
			currentChar = nextChar;
		}else{
			// *ptrFileOutput.write((unsigned char)currentChar, sizeof(char));
			*ptrFileOutput << currentChar;
			if(count > 2){
				num = count - 2;
				// cout << "DEBUG1: " << num << endl;
				if(num >= 1 && num <= 127){
					seg1 = (num & 0x7F) | 0x80;
					*ptrFileOutput << seg1;
				}else if(num > 127 && num <= (pow(2, 14) - 1)){
					seg1 = ((num >> 7) & 0x7F) | 0x80;
					seg2 = ((num >> 0) & 0x7F) | 0x80;
					*ptrFileOutput << seg1 << seg2;
				}else if(num > (pow(2, 14) - 1) && num <= (pow(2, 21) - 1)){
					// cout << "DEBUG2: " << num << endl;
					seg1 = ((num >> 14) & 0x7F) | 0x80;
					seg2 = ((num >> 7)  & 0x7F) | 0x80;
					seg3 = ((num >> 0)  & 0x7F) | 0x80;
					*ptrFileOutput << seg1 << seg2 << seg3;
				}else if(num > (pow(2, 21) - 1) && num <= (pow(2, 28) - 1)){
					seg1 = ((num >> 21) & 0x7F) | 0x80;
					seg2 = ((num >> 14) & 0x7F) | 0x80;
					seg3 = ((num >> 7)  & 0x7F) | 0x80;
					seg4 = ((num >> 0)  & 0x7F) | 0x80;
					*ptrFileOutput << seg1 << seg2 << seg3 << seg4;
				}
				

			}else if (count == 2){
				*ptrFileOutput << currentChar;
				// result += currentChar;
			}
			count = 1;
			currentChar = nextChar;
		}
	}
}


int main(int argc, char **argv){
	ifstream fileInput(argv[1], ios::in);
	if(argc == 2){
		string result;
		result = rlencode(fileInput);
		cout << result << endl;
	}else if(argc == 3){
		char num = 28;
		ofstream fileOutput(argv[2], ios::out | ios::binary);
		ofstream* ptrFileOutput = &fileOutput;
		rlencode(fileInput, ptrFileOutput);
		// fileOutput.write(&num, sizeof(char));
		fileOutput.close();
	}
	

	

	return 0;

}
