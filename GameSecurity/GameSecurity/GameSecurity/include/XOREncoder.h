#pragma once
#include "Prerequisites.h"


/**
 * @file XOREncoder.h
 * Clase para cifrar/descifrar datos con XOR y realizar ataques de fuerza bruta.
 */
class 
XOREncoder {
public:
	XOREncoder() = default;
	~XOREncoder() = default;
	
	/**
     * @brief Cifra o descifra una cadena usando XOR con la clave proporcionada.
     * @param input Cadena a procesar (texto plano o cifrado).
     * @param key Clave para el XOR (se repite en bucle si es más corta que el texto).
     * @return std::string Cadena resultante (texto cifrado o descifrado).
     */
	std::string 
	encode(const std::string& input, const std::string& key) {
		std::string output = input;
		for (int i = 0; i < input.size(); i++) {
			output[i] = input[i] ^ key[i % key.size()];			
		}
		return output;
	}

	/**
	 * @brief Convierte un texto hexadecimal en un vector de bytes.
	 * @param input Cadena con valores hexadecimales separados por espacios.
	 * @return std::vector<unsigned char> Vector de bytes correspondiente.
	 */
	std::vector<unsigned char> 
		HexToBytes(const std::string &input) {
		std::vector<unsigned char> bytes;
		std::istringstream iss(input);
		std::string hexValue;

		while (iss >> hexValue)	{
			if (hexValue.size() == 1) {
				hexValue = "0" + hexValue;
			}
			unsigned int byte;
			std::stringstream ss;
			ss << std::hex << hexValue;
			ss >> byte;
			bytes.push_back(static_cast<unsigned char>(byte));
		}
		return bytes;
	}

   /**
    * @brief Imprime una cadena en formato hexadecimal (útil para depuración).
    * @param input Texto a mostrar en hex.
    */
	void
	printHex(const std::string& input) {
		for (unsigned char c : input)	{
			std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
		}
	}

   /**
    * @brief Verifica si un texto contiene solo caracteres imprimibles y espacios.

    * @param data Texto a validar.
    * @return true Si el texto es legible (imprimible).
    * @return false Si contiene caracteres no imprimibles.
    */
	bool isValidText(const std::string& data) {
		return std::all_of(data.begin(), data.end(), [](unsigned char c) {
			return std::isprint(c) || std::isspace(c) || c == '\n' || c == ' ';
			});
	}

   /**
    * @brief Fuerza bruta probando todas las posibles claves de 1 byte.
    *
    * @param cifrado Datos cifrados en bytes.
    *
    * @details Imprime las posibles claves y el texto legible encontrado.
    */
	void
	bruteForce_1Byte(const std::vector<unsigned char>& cifrado) {
		for (int clave = 0; clave < 256; ++clave) {
			std::string result;

			for (unsigned char c : cifrado) {
				result += static_cast<unsigned char>( c ^ clave);
			}

			if (isValidText(result)) {
				std::cout << "=============================\n";
				std::cout << "Clave 1 byte  : '" << static_cast<char>(clave)
					<< "' (0x" << std::hex << std::setw(2) << std::setfill('0') << clave << ")\n";
				std::cout << "Texto posible : " << result << "\n";
			}
		}
	}

	/**
	* @brief Fuerza bruta probando todas las combinaciones posibles de 2 bytes.
	* @param cifrado Datos cifrados en bytes.
	* @details Imprime las claves candidatas y el texto resultante si es legible.
	*/
	void
	bruteForce_2Byte(const std::vector<unsigned char>& cifrado) {
		for (int b1 = 0; b1 < 256; ++b1) {
			for (int b2 = 0; b2 < 256; ++b2){
				std::string result;
				unsigned char key[2] = {static_cast<unsigned char>(b1), static_cast<unsigned char>(b2)};

				for (int i = 0; i < cifrado.size(); i++) {
					result += cifrado[i] ^ key[i % 2];
				}

				if (isValidText(result)) {
					std::cout << "=============================\n";
					std::cout << "Clave 2 bytes : '" << static_cast<char>(b1) << static_cast<char>(b2)
						<< "' (0x" << std::hex << std::setw(2) << std::setfill('0') << b1
						<< " 0x" << std::setw(2) << std::setfill('0') << b2 << ")\n";
					std::cout << "Texto posible : " << result << "\n";
				}

			}
		}
		
	}

	/**
	* @brief Prueba claves comunes (diccionario) para intentar descifrar.
	* @param cifrado Datos cifrados en bytes.
	* @details Usa claves frecuentes como "clave", "admin", "1234" y otras.
	*/
	void bruteForceByDictionary(const std::vector<unsigned char>& cifrado) {
		std::vector<std::string> clavesComunes = {
			"clave", "admin", "1234", "root", "test", "abc", "hola", "user",
			"pass", "12345", "0000", "password", "default"
		};

		for (const auto& clave : clavesComunes) {
			std::string result;
			for (int i = 0; i < cifrado.size(); i++) {
				result += static_cast<unsigned char>( cifrado[i] ^ clave[i % clave.size()]);
			}
			if (isValidText(result)) {
				std::cout << "=============================\n";
				std::cout << "Clave de diccionario: '" << clave << "'\n";
				std::cout << "Texto posible : " << result << "\n";
			}
		}
	}

	// Lee el contenido completo de un archivo en una string
	std::string readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::binary);
		if (!file) {
			throw std::runtime_error("No se pudo abrir el archivo: " + filename);
		}
		return std::string((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
	}

	// Escribe contenido en un archivo
	void writeFile(const std::string& filename, const std::string& content) {
		std::ofstream file(filename, std::ios::binary);
		if (!file) {
			throw std::runtime_error("No se pudo escribir el archivo: " + filename);
		}
		file.write(content.c_str(), content.size());
	}

private:

};