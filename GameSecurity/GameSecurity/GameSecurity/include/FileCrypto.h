#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"

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

		std::cout << "" << std::endl;

		std::cout << "Archivo descifrado exitosamente." << std::endl;
		std::cout << "Archivo cifrado: " << inputFile << std::endl;
		std::cout << "Archivo descifrado: " << outputFile << std::endl;

		std::cout << "" << std::endl;

		std::cout << "Contenido descifrado:" << std::endl;
		std::cout << "==========================" << std::endl;
		std::cout << decrypted << std::endl;
		std::cout << "==========================" << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "Error al descifrar: " << ex.what() << std::endl;
	}
}
