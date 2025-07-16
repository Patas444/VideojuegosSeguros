#include "Prerequisites.h"
#include "CesarEncryption.h"
#include "XOREncoder.h"
#include "AsciiBinary.h"
#include "DES.h"
#include "Vigenere.h"
#include "CryptoGenerator.h"
#include "FileCrypto.h"

/**
 * @brief Función principal del programa.
 * Muestra un menú interactivo que permite al usuario.
 * Cifrar y descifrar llamando a "FileCrypto.h y cpp"
 * dependiendo de la opción
 */


int main() {
	XOREncoder xorEncoder;
	CesarEncryption cesar;
	std::bitset<64> desKey; // El usuario la ingresará como string
	DES des;
	Vigenere vigenere;
	AsciiBinary asciiBin;

	std::string xorKey;
	int cesarShift;
	std::string vigenereKey;
	std::string desKeyInput;
	int opcion;

	do {
		std::cout << "== MENU DE CIFRADO XOR ==" << std::endl;

		std::cout << "" << std::endl;

		std::cout << "< AVISO! >" << std::endl;
		std::cout << "============================================================================" << std::endl;
		std::cout << "[Atento usuario para que este programa funcione correctamente debes ubicar  ]" << std::endl;
		std::cout << "[tus archivos en las carpetas correspondientes (Archivos_Org y Archivos_Cif)]" << std::endl;
		std::cout << "============================================================================" << std::endl;
		std::cout << "[Su ubicacion esta en:                                                      ]" << std::endl;
		std::cout << "[ [Location] \VideojuegosSeguros\GameSecurity\GameSecurity\GameSecurity...      ]" << std::endl;
		std::cout << "[\Archivos_Org o Archivos_Cif                                                ]" << std::endl;
		std::cout << "============================================================================" << std::endl;
		std::cout << "[Por ultimo todo los .txt o lo que quieras cifrar debe ir en Archivos_Org   ]" << std::endl;
		std::cout << "[y lo que esta cifrado y quieras decifrar debe ir en Archivos_Cif.          ]" << std::endl;
		std::cout << "============================================================================" << std::endl;

		std::cout << "" << std::endl;

		std::cout << "=== MENU DE CIFRADOS ===" << std::endl;
		std::cout << "1) Cifrar XOR" << std::endl;
		std::cout << "2) Descifrar XOR" << std::endl;
		std::cout << "3) Cifrar Cesar" << std::endl;
		std::cout << "4) Descifrar Cesar" << std::endl;
		std::cout << "5) Cifrar DES" << std::endl;
		std::cout << "6) Descifrar DES" << std::endl;
		std::cout << "7) Cifrar Vigenere" << std::endl;
		std::cout << "8) Descifrar Vigenere" << std::endl;
		std::cout << "9) Convertir ASCII" << std::endl;
		std::cout << "10) Convertir Binario" << std::endl;
		std::cout << "11) Salir" << std::endl;
		std::cout << "Selecciona una opcion: ";
		std::cin >> opcion;

		switch (opcion) {
		case 1:
			std::cout << "Ingresa la clave para XOR: ";
			std::cin >> xorKey;
			cifrarArchivo(xorEncoder, xorKey);
			break;

		case 2:
			std::cout << "Ingresa la clave para XOR: ";
			std::cin >> xorKey;
			descifrarArchivo(xorEncoder, xorKey);
			break;

		case 3:
			std::cout << "Ingresa el desplazamiento (Cesar): ";
			std::cin >> cesarShift;
			cifrarArchivoCesar(cesar, cesarShift);
			break;

		case 4:
			std::cout << "Ingresa el desplazamiento (Cesar): ";
			std::cin >> cesarShift;
			descifrarArchivoCesar(cesar, cesarShift);
			break;

		case 5:
			std::cout << "Ingresa la clave DES (8 caracteres): ";
			std::cin >> desKeyInput;

			if (desKeyInput.size() != 8) {
				std::cerr << "La clave DES debe tener exactamente 8 caracteres.";
				break;
			}

			{
				DES des(DES().stringToBitset64(desKeyInput));
				cifrarArchivoDES(des);
			}
			break;

		case 6:
			std::cout << "Ingresa la clave DES [8 caracteres]: ";
			std::cin >> desKeyInput;

			if (desKeyInput.size() != 8) {
				std::cerr << "La clave DES debe tener exactamente 8 caracteres.";
				break;
			}

			{
				DES des(DES().stringToBitset64(desKeyInput));
				descifrarArchivoDES(des);
			}
			break;

		case 7:
		{
			std::cout << "Ingresa la clave Vigenere (Solo letras): " << std::endl;
			std::cin >> vigenereKey;

			// Validación: solo letras
			while (!std::all_of(vigenereKey.begin(), vigenereKey.end(), [](unsigned char c) {
				return std::isalpha(c);
				})) {
				std::cerr << "La clave solo puede contener letras... Intenta de nuevo: " << std::endl;
				std::cin >> vigenereKey;
			}

			Vigenere vigenere(vigenereKey);
			cifrarArchivoVigenere(vigenere);
			break;
		}

		case 8:
		{
			std::cout << "Ingresa la clave Vigenere (Solo letras): " << std::endl;
			std::cin >> vigenereKey;

			while (!std::all_of(vigenereKey.begin(), vigenereKey.end(), [](unsigned char c) {
				return std::isalpha(c);
				})) {
				std::cerr << "La clave solo puede contener letras... Intenta de nuevo: " << std::endl;
				std::cin >> vigenereKey;
			}

			Vigenere vigenere(vigenereKey);
			descifrarArchivoVigenere(vigenere);
			break;
		}

		case 9:
			cifrarArchivoAsciiBinary(asciiBin);
			break;

		case 10:
			descifrarArchivoAsciiBinary(asciiBin);
			break;
		case 11:
			std::cout << "\nSaliendo del programa... ¡Adiós!\n";
			break;
		default:
			std::cout << "Solo hay 3 opciones ... no mas... ¡Intenta de nuevo!" << std::endl;
			break;
		}

		if (opcion != 11) {
			std::cout << "\nPresiona [Enter] para continuar...";
			std::cin.ignore();
			std::cin.get();
			system("cls");
		}

	} while (opcion != 11);

	return 0;
}

// #include "CryptoGenerator.h"
/*int main() {
	// 1) Generar una contraseña de 16 caracteres (mayúsculas, minúsculas, dígitos)
	CryptoGenerator cryptoGen;
	cryptoGen.generatePassword(16); // Generate a password of length 16

	// 2) Generar 16 bytes aleatorios genéricos
	auto randomBytes = cryptoGen.generateBytes(16);
	std::cout << "Random Bytes (hex): " << cryptoGen.toHex(randomBytes) << std::endl;

	// 3) Clave AES de 128 bits
	auto key128 = cryptoGen.generateKey(128);
	std::cout << "Key 128-bit (hex): " << cryptoGen.toHex(key128) << std::endl;

	// 4) IV de 128 bits (16 bytes)
	auto iv = cryptoGen.generateIV(16);
	std::cout << "IV 128-bit (hex): " << cryptoGen.toHex(iv) << "\n";

	// 5) Salt de 16 bytes
	auto salt = cryptoGen.generateSalt(16);
	std::cout << "Salt (Base64): " << cryptoGen.toBase64(salt) << "\n";

	// 6) Safe Release
	//cryptoGen.secureWipe(iv);
	//cryptoGen.secureWipe(salt);

	// 7) from Base64
	std::string base64String = cryptoGen.toBase64(salt);
	std::cout << "Base64: " << base64String << "\n";

	auto fromBase64 = cryptoGen.fromBase64(cryptoGen.toBase64(salt));
	std::cout << "From Base64: " << cryptoGen.toHex(fromBase64) << "\n";

	// 8) Estimated Entropy
	std::string pwd = base64String;
	auto entropy = cryptoGen.estimateEntropy(pwd);
	std::cout << "Password 1: " << cryptoGen.generatePassword(16) << "\n";
	std::cout << "Estimated Entropy 1: " << entropy << " | " << cryptoGen.passwordStrength(pwd) << "\n";
	auto entropy2 = cryptoGen.estimateEntropy("LRobles_32444");
	std::cout << "Password 2: " << "LRobles_32444" << "\n";
	std::cout << "Estimated Entropy 2: " << entropy2 << " | " << cryptoGen.passwordStrength("LRobles_32444") << "\n";

	// 9) Generar las 3 contraseñas con mayor entropía
	std::cout << "  " << "\n";
	auto topPasswords = cryptoGen.passwordsGenerator(20, 15);
	for (size_t i = 0; i < topPasswords.size(); ++i) {
	std::cout << "Password " << i + 1 << ": " << topPasswords[i] << " | " << cryptoGen.passwordStrength(topPasswords[i]) << "\n";
	std::cout << "Entropy : " << cryptoGen.estimateEntropy(topPasswords[i]) << "\n";
	std::cout << "  " << "\n";
	}

	return 0;
}*/


/*int main() {
	std::string text = "Hola este mensaje otorga una decima y patrocinado por PataSoft";
	std::string key = "PTS";

	std::cout << "Texto original: " << text << std::endl;
	std::cout << "Clave: " << key << std::endl;

	Vigenere vigenere(key);
	std::string encrypted = vigenere.encode(text);
	std::cout << "Texto cifrado: " << encrypted << std::endl;

	std::string decrypted = vigenere.decode(encrypted);
	std::cout << "Texto descifrado: " << decrypted << std::endl;

	std::cout << "\n--- Cifrado por fuerza bruta ---" << std::endl;
	std::string fuerzaBruta = Vigenere::breakBruteForce(encrypted, 3); // longitud máxima de clave = 3
	std::cout << "Texto descifrado por fuerza bruta: " << fuerzaBruta << std::endl;

	return 0;
}*/


/*int main() {
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
}*/


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
