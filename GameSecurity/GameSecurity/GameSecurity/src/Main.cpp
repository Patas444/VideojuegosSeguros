#include "Prerequisites.h"
#include "CesarEncryption.h"
#include "XOREncoder.h"
#include "AsciiBinary.h"
#include "DES.h"
#include <random>

int main() {
	// Clave DES de 64 bits
	std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");
	std::string phrase = "$Hola DES!";

	// Asegurar que la frase tenga longitud múltiplo de 8
	while (phrase.size() % 8 != 0) {
		phrase += '\0'; // null space
	}

	std::vector<std::bitset<64>> cipherBlocks;
	std::cout << "Texto original: " << phrase << std::endl;
	std::cout << "Cifrado en hexadecimal:\n";

	// Cifrado con DES
	DES des(key);
	for (size_t i = 0; i < phrase.size(); i += 8) {
		std::string block = phrase.substr(i, 8);
		auto blockBits = des.stringToBitset64(block);
		auto encrypted = des.encode(blockBits);
		cipherBlocks.push_back(encrypted);
		std::cout << std::hex << std::uppercase << std::setw(16) << std::setfill('0') << encrypted.to_ullong() << " ";
	}

	std::cout << std::endl;

	// Descifrado con DES
	std::string output;
	for (const auto& block : cipherBlocks) {
		auto decrypted = des.decode(block);
		output += des.bitset64ToString(decrypted);
	}

	std::cout << "Texto descifrado: " << phrase << std::endl;
	return 0;
}

/*// Genera una clave aleatoria de 8 bytes (64 bits)
std::string generateRandomKey() {
	std::string key;
	std::random_device rd; // fuente de entropía
	std::mt19937 gen(rd()); // generador
	std::uniform_int_distribution<> dis(0, 255); // valores byte (0 - 255)

	for (int i = 0; i < 8; ++i) {
		char randomChar = static_cast<char>(dis(gen));
		key += randomChar;
	}
	return key;
}

// Convierte un string de 8 bytes a bitset<64>
std::bitset<64> stringToBitset64(const std::string& str) {
	std::bitset<64> bits;
	for (size_t i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			bool bit = (str[i] >> (7 - j)) & 1;
			bits[(7 - i) * 8 + j] = bit;
		}
	}
	return bits;
}

int main() {
	std::string randomKeyString = generateRandomKey();
	std::bitset<64> key = stringToBitset64(randomKeyString);

	// Mostrar clave como texto (puede tener caracteres no imprimibles)
	std::cout << "Clave generada (texto): ";
	for (unsigned char c : randomKeyString) {
		std::cout << c;
	}
	std::cout << std::endl;

	// Mostrar clave como hexadecimal
	std::cout << "Clave generada (hex): ";
	for (unsigned char c : randomKeyString) {
		std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)(unsigned char)c << " ";
	}
	std::cout << std::dec << std::endl; // Vuelve a decimal

	std::string phrase = "$Hola DES!";

	// Asegurar múltiplo de 8
	while (phrase.size() % 8 != 0) {
		phrase += '\0';
	}

	std::vector<std::bitset<64>> cipherBlocks;
	std::cout << "Texto original: " << phrase << std::endl;
	std::cout << "Cifrado en hexadecimal:\n";

	DES des(key);
	for (size_t i = 0; i < phrase.size(); i += 8) {
		std::string block = phrase.substr(i, 8);
		auto blockBits = des.stringToBitset64(block);
		auto encrypted = des.encode(blockBits);
		cipherBlocks.push_back(encrypted);
		std::cout << std::hex << std::uppercase << std::setw(16) << std::setfill('0') << encrypted.to_ullong() << " ";
	}

	std::cout << std::endl;

	// Descifrado con DES
	std::string output;
	for (const auto& block : cipherBlocks) {
		auto decrypted = des.decode(block);
		output += des.bitset64ToString(decrypted);
	}

	std::cout << "Texto descifrado: " << output << std::endl;
	return 0;
}
*/



/*
int main() {
	XOREncoder XORencoder;

	// Cifrar mensaje con XOR
	std::string mensaje = "Hola Mundo e e e e";
	std::string clave = "clave";

	std::cout << "Mensaje original: " << mensaje << std::endl;
	std::string cifrado = XORencoder.encode(mensaje, clave);

	std::cout << "Mensaje cifrado(original): " << cifrado << std::endl;
	std::string descifrado = XORencoder.encode(cifrado, clave);

	// Descifrar usando la misma clave
	std::cout << "Mensaje desifrado: " << descifrado << std::endl;

	// Pasar el cifrado a vector<unsigned char> para probar bruteForceByDictionary
	std::vector<unsigned char> cifradoBytes(cifrado.begin(), cifrado.end());

	// Realiza la fuerza bruta por diccionario con archivos
	XORencoder.bruteForceByDictionary(cifradoBytes);

	return 0;
}
*/

/*int main() {
	AsciiBinary AB;

	std::string input = "Hello, World!";

	// Convertir a binario
	std::string binary = AB.stringToBinary(input);
	std::cout << "Texto a binario: " << binary << std::endl;

	// Convertir de binario a texto
	std::string message = AB.binaryToString(binary);
	std::cout << "Binario a texto: " << message << std::endl;

	return 0;
}*/
