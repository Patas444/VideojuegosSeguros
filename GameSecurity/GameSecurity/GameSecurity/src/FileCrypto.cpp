#include "FileCrypto.h"

namespace fs = std::filesystem;

std::string readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		throw std::runtime_error("No se pudo abrir el archivo: " + filename);
	}
	return std::string((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
}

void writeFile(const std::string& filename, const std::string& content) {
	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		throw std::runtime_error("No se pudo escribir el archivo: " + filename);
	}
	file.write(content.c_str(), content.size());
}

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
