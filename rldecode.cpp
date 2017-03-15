#include <iostream>
#include <fstream>

using namespace std;



void rldecode(ifstream& input){
	// string result;
	unsigned char currentChar, nextChar;
	// unsigned int count = 0;
	unsigned int num[4];
	unsigned char seg[4];
	unsigned int totalNum = 0;
	int nextOne = input.peek();
	int length = 1;

	int next;
	while(input.peek() != EOF){
		currentChar = input.get();
		if((currentChar >> 7) & 1){
			seg[0] = currentChar;
			
			for(int i = 1; i < 4; i++){
				nextOne = input.peek();
				if(nextOne == EOF){
					break;
				}

				if((nextOne >> 7) & 1){
					seg[i] = input.get();
					length++;
				}else{
					break;
				}
			}

			for(int j = 0; j < length; j++){
				num[j] = (seg[j] & 0x7F) << ((length - j - 1) * 7);
				totalNum |= num[j];
			}
			cout << "[" << to_string(totalNum) << "]";
			// result += "[" + to_string(totalNum) + "]";
			totalNum = 0;
			length = 1;
			
			
		}else{
			cout << currentChar;
			// result += currentChar;
			nextOne = input.peek();

		}
	}

	// return result;
}

void rldecode(ifstream& input, ofstream* ptrFileOutput){
	unsigned char currentChar, nextChar;
	unsigned int num[4];
	unsigned char seg[4];
	unsigned int totalNum = 0;
	int nextOne = input.peek();
	int length = 1;

	unsigned char charPrint;
	unsigned int number;

	int next;
	while(input.peek() != EOF){
		currentChar = input.get();
		if((currentChar >> 7) & 1){
			seg[0] = currentChar;
			if(seg[0] == '\n'){
				break;
			}else{
				for(int i = 1; i < 4; i++){
					nextOne = input.peek();
					if(nextOne == EOF){
						break;
					}

					if((nextOne >> 7) & 1){
						seg[i] = input.get();
						length++;
					}else{
						break;
					}
				}

				for(int j = 0; j < length; j++){
					num[j] = (seg[j] & 0x7F) << ((length - j - 1) * 7);
					totalNum |= num[j];
				}
				// *ptrFileOutput <<  "[" << to_string(totalNum) << "]";
				// totalNum = 0;
				// length = 1;
			}
			// cout << totalNum << endl;
			for(int k = 0; k < totalNum + 2; k++){
				// cout << totalNum << endl;
				*ptrFileOutput << charPrint;
			}

			totalNum = 0;
			length = 1;
			
		}else{
			// *ptrFileOutput << currentChar;
			charPrint = currentChar;
			// cout << charPrint;
			*ptrFileOutput << charPrint;
			nextOne = input.peek();

		}

		
	}
}

int main(int argc, char** argv){
	ifstream fileInput(argv[1], ios::in | ios::binary);
	ofstream fileOutput(argv[2], ios::out | ios::binary);
	ofstream* ptrFileOutput = &fileOutput;


	if(argc == 2){
		string result;
		rldecode(fileInput);
		// cout << result << endl;
	}else if(argc == 3){
		rldecode(fileInput, ptrFileOutput);
	}
	

	fileInput.close();
	fileOutput.close();

	return 0;
}
