#include <string>
#include <iostream>

void swap(int* x, int* y) {
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}

char* rc4Crypt(std::string input, std::string key) {
	char* result = new char[input.size()]; //used as a stringbuilder
	int j = 0;
	char z = '\0';
	int keystream[256];
	for (int i = 0; i < 256; i++) { //place 0 to 255 in keystream
		keystream[i] = i;
	}
    for (int i = 0; i < 256; i++) { //swap 0 to 255 based on key
		j = (key[i % key.size()] + keystream[i] + j) % 256;
		swap(&keystream[i], &keystream[j]);
	}
	j = 0;
    for (int i = 0; i < input.size(); i++) { //may have to deal with null term char
        int x = i % 256;
        j = (keystream[x] + j) % 256;
        swap(&keystream[x], &keystream[j]);
        z = keystream[(keystream[x] + keystream[j]) % 256];
        result[i] = (char)(input[i] ^ z); //apply keystream
	}
	return result;
}

int main() {
	char* cypheredText = rc4Crypt("Hello Encrypted World!", "T0uC(@#N");
	std::cout << cypheredText << std::endl;
	char* deCypheredText = rc4Crypt(cypheredText, "T0uC(@#N");
	std::cout << deCypheredText << std::endl;
	delete cypheredText;
	delete deCypheredText;
}