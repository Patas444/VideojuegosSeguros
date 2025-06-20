#pragma once
#include "Prerequisites.h"

class
	Vigenere {
public:
	Vigenere() = default;

	Vigenere(const std::string& key) :key(normalizeKey(key)) {
		if (key.empty()) {
			throw std::invalid_argument("La clave no puede estar vac�a o sin letras.");
		}
	}

	static std::string
		normalizeKey(const std::string& rawKey) {
		std::string k;
		for (char c : rawKey) {
			if (std::isalpha(static_cast<unsigned char>(c))) {
				k += std::toupper(static_cast<unsigned char>(c)); // Convert to uppercase and append
			}
		}
		return k;
	}

	std::string encode(const std::string& text) {
		std::string result;
		result.reserve(text.size()); // Reserve space for efficiency
		unsigned int i = 0; // Index for the key

		for (char c : text) {
			if (std::isalpha(static_cast<unsigned char>(c))) {
				bool isLower = std::islower(static_cast<unsigned char>(c));
				char base = isLower ? 'a' : 'A'; // Determine base based on case

				// Desplazamiento de la key
				int shift = key[i % key.size()] - 'A'; // Calculate shift based on key character mod26
				// Encode
				char encodedChar = static_cast<char>((c - base + shift) % 26 + base);
				result += encodedChar; // Append encoded character to result
				i++; // Increment key index
			}
			else {
				result += c; // Non-alphabetic characters are added unchanged
			}
		}

		return result; // Return the encoded string
	}

	std::string decode(const std::string& text) {
		std::string result;
		result.reserve(text.size()); // Reserve space for efficiency
		unsigned int i = 0; // Index for the key

		for (char c : text) {
			if (std::isalpha(static_cast<unsigned char>(c))) {
				bool isLower = std::islower(static_cast<unsigned char>(c));
				char base = isLower ? 'a' : 'A'; // Determine base based on case

				// Desplazamiento de la key
				int shift = key[i % key.size()] - 'A'; // Calculate shift based on key character mod26
				// decode
				char encodedChar = static_cast<char>(((c - base) - shift + 26) % 26 + base);
				result += encodedChar; // Append encoded character to result
				i++; // Increment key index
			}
			else {
				result += c; // Non-alphabetic characters are added unchanged
			}
		}

		return result; // Return the encoded string
	}

	static std::string toUpper(const std::string& str) {
		std::string upperStr = str;
		std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return upperStr;
	}

	static std::string breakBruteForce(const std::string& ciphertext, int maxKeyLength = 3) {
	static const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static const std::vector<std::string> commonWords = { "EL", "LA", "QUE", "DE", "Y", "A", "EN", "ES", "UN", "HOLA", "ESTE", "MENSAJE", "UNA", "DECIMA", "PATAS", "DOG" };

	std::string bestDecryption;
	std::string bestKey = "(no encontrada)";
	int bestScore = -1;

	std::function<void(std::string)> tryKeys;

	tryKeys = [&](std::string currentKey) {
		if (currentKey.length() > static_cast<size_t>(maxKeyLength)) return;

		std::string cleanKey = normalizeKey(currentKey);
		if (cleanKey.empty()) return;

		Vigenere v(cleanKey);
		std::string decrypted = v.decode(ciphertext);


		int score = 0;
		for (const std::string& word : commonWords) {
			if (decrypted.find(word) != std::string::npos) {
				score++;
			}
		}

		std::string decryptedUpper = toUpper(decrypted);
		if (score > bestScore) {
			bestScore = score;
			bestDecryption = decrypted;
			bestKey = cleanKey; // << guardar la mejor clave
		}

		for (char c : alphabet) {
			tryKeys(currentKey + c);
		}
	};

	for (char c : alphabet) {
		tryKeys(std::string(1, c));
	}

	std::cout << "Clave encontrada por fuerza bruta: " << bestKey << std::endl;
	return bestDecryption;
}


private:
	std::string key; // The key for the Vigenere cipher
};