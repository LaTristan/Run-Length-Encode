#include <iostream>
#include <fstream>

using namespace std;



string rldecode(ifstream& input){
	string result;
	unsigned int currentChar, nextChar;
	// unsigned int count = 0;
	unsigned int num[4];
	unsigned int seg[4];
	unsigned int finalNum = 0;
	nextChar = input.get();
	int length = 1;

	while(!input.eof()){
		// if(input.eof()){
		// 	break;
		// }
		currentChar = nextChar;
		// input >> currentChar;
		
		if((currentChar >> 7) & 1){
			seg[0] = currentChar;
			// cout << "seg[0]: " << seg[0] << endl;
			for(int i = 1; i < 4; i++){
				seg[i] = input.get();
				if(seg[i] == -1){
					break;
				}
				if(!((seg[i] >> 7) & 1)){
					break;
				}
				length++;

			}
			// cout << length << endl;
			for(int j = 0; j < length; j++){
				num[j] = (seg[j] & 0x7F) << ((length - j - 1) * 7);
				finalNum |= num[j];
			}

			result += "[" + to_string(finalNum) + "]";
			nextChar = seg[length];
			finalNum = 0;
			length = 1;
		}else{
			result += (unsigned char)currentChar;
			nextChar = input.get();
		}
	}


	return result;
}



int main(int argc, char** argv){
	ifstream fileInput(argv[1], ios::in | ios::binary);

	if(argc == 2){
		string result;
		result = rldecode(fileInput);
		cout << result << endl;
	}

	fileInput.close();

	return 0;
}
