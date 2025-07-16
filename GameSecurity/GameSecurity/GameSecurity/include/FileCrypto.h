#pragma once
#include "Prerequisites.h"
#include "CesarEncryption.h"
#include "XOREncoder.h"
#include "DES.h"
#include "Vigenere.h"
#include "AsciiBinary.h"

namespace fs = std::filesystem;

/**
 * @brief Lee el contenido completo de un archivo en modo binario.
 * @param Ruta y nombre del archivo a leer archivos txt.
 * (Es el que me ayuda a poder leer los archivos txt que quiero cifrar).
 */
std::string readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		throw std::runtime_error("No se pudo abrir el archivo: " + filename);
	}
	return std::string((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
}

/**
 * @brief Escribe el contenido en un archivo en modo binario.
 * @param filename Ruta y nombre del archivo donde se escribirá el contenido.
 * (Aqui se sobrescribe ya sea para cifrado o descifrado).
 */
void writeFile(const std::string& filename, const std::string& content) {
	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		throw std::runtime_error("No se pudo escribir el archivo: " + filename);
	}
	file.write(content.c_str(), content.size());
}

// ===XOREncode===
/**
 * @brief Cifra un archivo de la carpeta `Archivos_Org` y lo guarda en `Archivos_Cif`.
 * @param encoder Instancia de @ref XOREncoder utilizada para el cifrado.
 * @param key Clave ingresada por el usuario para cifrar el archivo.
 * (Aqui solicito al usuario el nombre del archivo original (`.txt`) y el nombre del archivo de salida (`.enc`)).
 */
void cifrarArchivo(XOREncoder& encoder, const std::string& key) {
	try {
		std::string inputFile, outputFile;

		std::cout << "Ingresa el nombre del archivo a cifrar [Nombre.txt]: ";
		std::cin >> inputFile;

		std::cout << "Ingresa el nombre del archivo de salida [Nombre_Cifr.enc]: ";
		std::cin >> outputFile;

		std::string originalText = readFile("Archivos_Org/" + inputFile);
		std::string encrypted = encoder.encode(originalText, key);
		writeFile("Archivos_Cif/" + outputFile, encrypted);

		std::cout << "" << std::endl;

		std::cout << "Archivo cifrado exitosamente." << std::endl;
		std::cout << "Archivo original: " << inputFile << std::endl;
		std::cout << "Archivo cifrado: " << outputFile << std::endl;

		std::cout << "" << std::endl;

		std::cout << "Resultado:" << std::endl;
		std::cout << "==========================" << std::endl;
		std::cout << encrypted << std::endl;
		std::cout << "==========================" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "Error al cifrar: " << ex.what() << std::endl;
	}
}

/**
 * @brief Descifra un archivo de la carpeta `Archivos_Cif` y lo guarda en `Archivos_Org`.
 * @param encoder Instancia de @ref XOREncoder utilizada para el descifrado.
 * @param key Clave ingresada por el usuario para descifrar el archivo.
 * (Igual que el otro solicita al usuario pero ahora el nombre del archivo cifrado (`.enc`) y el nombre del archivo de salida (`.txt`).)
 */
void descifrarArchivo(XOREncoder& encoder, const std::string& key) {
	try {
		std::string inputFile, outputFile;

		std::cout << "Ingresa el nombre del archivo cifrado [Nombre_Cifr.enc]: ";
		std::cin >> inputFile;

		std::cout << "Ingresa el nombre del archivo descifrado [Nombre_Decrypt.txt]: ";
		std::cin >> outputFile;

		std::string encryptedRead = readFile("Archivos_Cif/" + inputFile);
		std::string decrypted = encoder.encode(encryptedRead, key);
		writeFile("Archivos_Org/" + outputFile, decrypted);

        std::cout << std::endl;

		std::cout << "Archivo descifrado exitosamente." << std::endl;
		std::cout << "Archivo cifrado: " << inputFile << std::endl;
		std::cout << "Archivo descifrado: " << outputFile << std::endl;

        std::cout << std::endl;

		std::cout << "Contenido descifrado:" << std::endl;
		std::cout << "==========================" << std::endl;
		std::cout << decrypted << std::endl;
		std::cout << "==========================" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "Error al descifrar: " << ex.what() << std::endl;
	}
}


// ===CesarEncryption===

/**
 * @brief Cifra un archivo con el cifrado César.
 * @param cesar Instancia de @ref CesarEncryption.
 * @param desplazamiento Valor del desplazamiento (1-25).
 */
void cifrarArchivoCesar(CesarEncryption& cesar, int desplazamiento) {
    try {
        std::string inputFile, outputFile;
        std::cout << "Ingresa el nombre del archivo a cifrar [Nombre.txt]: ";
        std::cin >> inputFile;
        std::cout << "Ingresa el nombre del archivo de salida [Nombre_CesarCifr.ces]: ";
        std::cin >> outputFile;

        std::cout << std::endl;

        std::string originalText = readFile("Archivos_Org/" + inputFile);
        std::string encrypted = cesar.encode(originalText, desplazamiento);
        writeFile("Archivos_Cif/" + outputFile, encrypted);

        std::cout << std::endl;

        std::cout << "Archivo cifrado exitosamente." << std::endl;
        std::cout << "Archivo original: " << inputFile << std::endl;
        std::cout << "Archivo cifrado: " << outputFile << std::endl;

        std::cout << std::endl;

        std::cout << "Resultado:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << encrypted << std::endl;
        std::cout << "==========================" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error en cifrado César: " << ex.what() << std::endl;
    }
}

/**
 * @brief Descifra un archivo con el cifrado César.
 * @param cesar Instancia de @ref CesarEncryption.
 * @param desplazamiento Valor del desplazamiento (1-25).
 */
void descifrarArchivoCesar(CesarEncryption& cesar, int desplazamiento) {
    try {
        std::string inputFile, outputFile;
        std::cout << "Ingresa el nombre del archivo cifrado [Nombre_CesarCifr.ces]: ";
        std::cin >> inputFile;
        std::cout << "Ingresa el nombre del archivo descifrado [Nombre_CesarDecrypt.txt]: ";
        std::cin >> outputFile;

        std::cout << std::endl;

        std::string encryptedRead = readFile("Archivos_Cif/" + inputFile);
        std::string decrypted = cesar.decode(encryptedRead, desplazamiento);
        writeFile("Archivos_Org/" + outputFile, decrypted);

        std::cout << std::endl;

        std::cout << "Archivo descifrado exitosamente." << std::endl;
        std::cout << "Archivo cifrado: " << inputFile << std::endl;
        std::cout << "Archivo descifrado: " << outputFile << std::endl;

        std::cout << std::endl;

        std::cout << "Contenido descifrado:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << decrypted << std::endl;
        std::cout << "==========================" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error en descifrado César: " << ex.what() << std::endl;
    }
}

// ===DES===

/**
 * @brief Cifra un archivo de texto en bloques de 64 bits usando DES.
 * @param des Instancia de @ref DES con la clave ya configurada.
 * @details Aplica padding con espacios si el tamaño no es múltiplo de 8 bytes.
 */
void cifrarArchivoDES(DES& des) {
    try {
        std::string inputFile, outputFile;
        std::cout << "Ingresa el nombre del archivo a cifrar [Nombre.txt]: ";
        std::cin >> inputFile;
        std::cout << "Ingresa el nombre del archivo de salida [Nombre_DESCifr.des]: ";
        std::cin >> outputFile;

        std::cout << std::endl;

        std::string originalText = readFile("Archivos_Org/" + inputFile);
        std::string encrypted;

        for (size_t i = 0; i < originalText.size(); i += 8) {
            std::string block = originalText.substr(i, 8);
            while (block.size() < 8) block.push_back(' '); // Padding con espacios

            std::bitset<64> encodedBlock = des.encode(des.stringToBitset64(block));
            encrypted += des.bitset64ToString(encodedBlock);
        }

        writeFile("Archivos_Cif/" + outputFile, encrypted);

        std::cout << std::endl;

        std::cout << "Archivo cifrado exitosamente." << std::endl;
        std::cout << "Archivo original: " << inputFile << std::endl;
        std::cout << "Archivo cifrado: " << outputFile << std::endl;

        std::cout << std::endl;

        std::cout << "Resultado:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << encrypted << std::endl;
        std::cout << "==========================" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error en cifrado DES: " << ex.what() << std::endl;
    }
}

/**
 * @brief Descifra un archivo previamente cifrado con DES.
 * @param des Instancia de @ref DES con la misma clave usada en el cifrado.
 */
void descifrarArchivoDES(DES& des) {
    try {
        std::string inputFile, outputFile;
        std::cout << "Ingresa el nombre del archivo cifrado [Nombre_DESCifr.des]: ";
        std::cin >> inputFile;
        std::cout << "Ingresa el nombre del archivo descifrado [Nombre_DESDecrypt.txt]: ";
        std::cin >> outputFile;

        std::string encryptedRead = readFile("Archivos_Cif/" + inputFile);
        std::string decrypted;

        for (size_t i = 0; i < encryptedRead.size(); i += 8) {
            std::string block = encryptedRead.substr(i, 8);
            std::bitset<64> decodedBlock = des.decode(des.stringToBitset64(block));
            decrypted += des.bitset64ToString(decodedBlock);
        }

        writeFile("Archivos_Org/" + outputFile, decrypted);

        std::cout << std::endl;

        std::cout << "Archivo descifrado exitosamente." << std::endl;
        std::cout << "Archivo cifrado: " << inputFile << std::endl;
        std::cout << "Archivo descifrado: " << outputFile << std::endl;

        std::cout << std::endl;

        std::cout << "Contenido descifrado:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << decrypted << std::endl;
        std::cout << "==========================" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error en descifrado DES: " << ex.what() << std::endl;
    }
}

// ===Vigenere===

/**
 * @brief Cifra un archivo con el cifrado Vigenère.
 * @param vigenere Instancia de @ref Vigenere (ya inicializada con la clave).
 */
void cifrarArchivoVigenere(Vigenere& vigenere) {
    try {
        std::string inputFile, outputFile;
        std::cout << "Ingresa el nombre del archivo a cifrar [Nombre.txt]: ";
        std::cin >> inputFile;
        std::cout << "Ingresa el nombre del archivo de salida [Nombre_VigCifr.vig]: ";
        std::cin >> outputFile;

        std::string originalText = readFile("Archivos_Org/" + inputFile);
        std::string encrypted = vigenere.encode(originalText);
        writeFile("Archivos_Cif/" + outputFile, encrypted);

        std::cout << std::endl;

        std::cout << "Archivo cifrado exitosamente." << std::endl;
        std::cout << "Archivo original: " << inputFile << std::endl;
        std::cout << "Archivo cifrado: " << outputFile << std::endl;

        std::cout << std::endl;

        std::cout << "Resultado:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << encrypted << std::endl;
        std::cout << "==========================" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error en cifrado Vigenère: " << ex.what() << std::endl;
    }
}

/**
 * @brief Descifra un archivo cifrado con Vigenère.
 * @param vigenere Instancia de @ref Vigenere (con la clave correcta).
 */
void descifrarArchivoVigenere(Vigenere& vigenere) {
    try {
        std::string inputFile, outputFile;
        std::cout << "Ingresa el nombre del archivo cifrado [Nombre_VigCifr.vig]: ";
        std::cin >> inputFile;
        std::cout << "Ingresa el nombre del archivo descifrado [Nombre_VigDecrypt.txt]: ";
        std::cin >> outputFile;

        std::string encryptedRead = readFile("Archivos_Cif/" + inputFile);
        std::string decrypted = vigenere.decode(encryptedRead);
        writeFile("Archivos_Org/" + outputFile, decrypted);

        std::cout << std::endl;

        std::cout << "Archivo descifrado exitosamente." << std::endl;
        std::cout << "Archivo cifrado: " << inputFile << std::endl;
        std::cout << "Archivo descifrado: " << outputFile << std::endl;

        std::cout << std::endl;

        std::cout << "Contenido descifrado:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << decrypted << std::endl;
        std::cout << "==========================" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error en descifrado Vigenère: " << ex.what() << std::endl;
    }
}


//===AsciiBinary===

/**
 * @brief Convierte el contenido de un archivo de texto a su representación binaria (ASCII en bits).
 * @param asciiBin Instancia de @ref AsciiBinary.
 */
void cifrarArchivoAsciiBinary(AsciiBinary& asciiBin) {
    try {
        std::string inputFile, outputFile;
        std::cout << "Ingresa el nombre del archivo a convertir a binario [Nombre.txt]: ";
        std::cin >> inputFile;
        std::cout << "Ingresa el nombre del archivo de salida [Nombre_Bin.bin]: ";
        std::cin >> outputFile;

        std::string originalText = readFile("Archivos_Org/" + inputFile);
        std::string binary = asciiBin.stringToBinary(originalText);
        writeFile("Archivos_Cif/" + outputFile, binary);

        std::cout << std::endl;

        std::cout << "Archivo convertido a Binario exitosamente." << std::endl;
        std::cout << "Archivo original: " << inputFile << std::endl;
        std::cout << "Archivo binario: " << outputFile << std::endl;

        std::cout << std::endl;

        std::cout << "Resultado:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << binary << std::endl;
        std::cout << "==========================" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error en conversión a Binario: " << ex.what() << std::endl;
    }
}

/**
 * @brief Convierte un archivo binario a texto ASCII.
 * @param asciiBin Instancia de @ref AsciiBinary.
 */
void descifrarArchivoAsciiBinary(AsciiBinary& asciiBin) {
    try {
        std::string inputFile, outputFile;
        std::cout << "Ingresa el nombre del archivo binario [Nombre_Bin.bin]: ";
        std::cin >> inputFile;
        std::cout << "Ingresa el nombre del archivo de salida [Nombre_AscDecrypt.txt]: ";
        std::cin >> outputFile;

        std::string binaryRead = readFile("Archivos_Cif/" + inputFile);
        std::string asciiText = asciiBin.binaryToString(binaryRead);
        writeFile("Archivos_Org/" + outputFile, asciiText);

        std::cout << std::endl;

        std::cout << "Archivo convertido a ASCII exitosamente." << std::endl;
        std::cout << "Archivo binario: " << inputFile << std::endl;
        std::cout << "Archivo ASCII: " << outputFile << std::endl;

        std::cout << std::endl;

        std::cout << "Contenido descifrado:" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << asciiText << std::endl;
        std::cout << "==========================" << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error en conversión de Binario a ASCII: " << ex.what() << std::endl;
    }
}
