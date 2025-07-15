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

		std::cout << "Ingresa el nombre del archivo a cifrar (Ej: TextInfo.txt): ";
		std::cin >> inputFile;

		std::cout << "Ingresa el nombre del archivo de salida (Ej: Nombre_XD.enc): ";
		std::cin >> outputFile;

		std::string originalText = readFile("Archivos_Org/" + inputFile);
		std::string encrypted = encoder.encode(originalText, key);
		writeFile("Archivos_Cif/" + outputFile, encrypted);

		std::cout << "\nArchivo cifrado exitosamente.\n";
		std::cout << "Archivo original: " << inputFile << "\n";
		std::cout << "Archivo cifrado: " << outputFile << std::endl;

		std::cout << "\nResultado:\n";
		std::cout << "--------------------------\n";
		std::cout << encrypted << "\n";
		std::cout << "--------------------------\n\n";
	}
	catch (const std::exception& ex) {
		std::cerr << "Error al cifrar: " << ex.what() << "\n";
	}
}

void descifrarArchivo(XOREncoder& encoder, const std::string& key) {
	try {
		std::string inputFile, outputFile;

		std::cout << "Ingresa el nombre del archivo cifrado (Ej: Nombre_XD.enc): ";
		std::cin >> inputFile;

		std::cout << "Ingresa el nombre del archivo descifrado (Ej: Decrypt_Nombre_Xd.txt): ";
		std::cin >> outputFile;

		std::string encryptedRead = readFile("Archivos_Cif/" + inputFile);
		std::string decrypted = encoder.encode(encryptedRead, key);
		writeFile("Archivos_Org/" + outputFile, decrypted);

		std::cout << "\nArchivo descifrado exitosamente.\n";
		std::cout << "Archivo cifrado: " << inputFile << "\n";
		std::cout << "Archivo descifrado: " << outputFile << std::endl;

		std::cout << "\nContenido descifrado:\n";
		std::cout << "--------------------------\n";
		std::cout << decrypted << "\n";
		std::cout << "--------------------------\n\n";
	}
	catch (const std::exception& ex) {
		std::cerr << "Error al descifrar: " << ex.what() << "\n";
	}
}
