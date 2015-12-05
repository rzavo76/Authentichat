#include <string>
#include <iostream>

void swap(int& x, int& y) {
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
}

std::string rc4Crypt(std::string input, std::string key) {
	char* result = new char[input.size()]; //used as a stringbuilder
	int x, j = 0;
	int keystream[256];
	for (int i = 0; i < 256; i++) { //place 0 to 255 in keystream
		keystream[i] = i;
	}
    for (int i = 0; i < 256; i++) { //swap 0 to 255 based on key
		j = (key[i % key.size()] + keystream[i] + j) % 256;
		swap(keystream[i], keystream[j]);
	}
    for (int i = 0; i < input.size(); i++) { //may have to deal with null term char
        x = i % 256;
        j = (keystream[x] + j) % 256;
        swap(keystream[x], keystream[j]);
        result[i] = (char)(input[i] ^ keystream[(keystream[x] + keystream[j]) % 256]); //apply keystream
	}
	return result;
}

int main() {
	std::string cypheredText = rc4Crypt("AuthentichatKey", "T0uC(@#N");
	std::cout << cypheredText << std::endl;
	std::string deCypheredText = rc4Crypt(cypheredText, "T0uC(@#N");
	std::cout << deCypheredText << std::endl;
}