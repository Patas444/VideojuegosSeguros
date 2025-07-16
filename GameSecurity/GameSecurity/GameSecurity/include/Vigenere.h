#pragma once
#include "Prerequisites.h"

class
	Vigenere {
public:
	Vigenere() = default;

   /**
    * @brief Construye un cifrador Vigenère con la clave dada.
    * @param key Clave de cifrado (se normaliza automáticamente a letras mayúsculas).
    * @throws std::invalid_argument Si la clave está vacía o no contiene letras.
    */
	Vigenere(const std::string& key) :key(normalizeKey(key)) {
		if (key.empty()) {
			throw std::invalid_argument("La clave no puede estar vac�a o sin letras.");
		}
	}

   /**
	* @brief Normaliza una clave eliminando caracteres no alfabéticos y convirtiendo todo a mayúsculas.
	* @param rawKey Clave cruda introducida por el usuario.
	* @return std::string Clave limpia, solo letras en mayúsculas.
	*/
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

   /**
	* @brief Cifra un texto con el cifrado Vigenère.
	*
	* @param text Texto a cifrar (se mantienen caracteres no alfabéticos sin cambios).
	* @return std::string Texto cifrado.
	*/
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

	/**
	 * @brief Descifra un texto cifrado con el cifrado Vigenère.
	 * @param text Texto cifrado.
	 * @return std::string Texto descifrado (legible si la clave es correcta).
	 */
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

   /**
	* @brief Calcula un "puntaje de legibilidad" basado en palabras comunes en español.
	* @param text Texto a evaluar.
	* @return double Puntaje (mayor puntaje implica mayor probabilidad de ser texto legible).
	*/
	static double fitness(const std::string& text) {
		static const std::vector<std::string> comunes = {
		" DE ", " LA ", " EL ", " QUE ", " Y ",
		" A ", " EN ", " UN ", " PARA ", " CON ",
		" POR ", " COMO ", " SU ", " AL ", " DEL ",
		" LOS ", " SE ", " NO ", " MAS ", " O ",
		" SI ", " YA ", " TODO ", " ESTA ", " HAY ",
		" ESTO ", " SON ", " TIENE ", " HACE ", " SUS ",
		" VIDA ", " NOS ", " TE ", " LO ", " ME ",
		" ESTE ", " ESA ", " ESE ", " BIEN ", " MUY ",
		" PUEDE ", " TAMBIEN ", " AUN ", " MI ", " DOS ",
		" UNO ", " OTRO ", " NUEVO ", " SIN ", " ENTRE ",
		" SOBRE "
		};

		double score = 0;
		for (auto& w : comunes) {
			size_t pos = 0;
			while ((pos = text.find(w, pos)) != std::string::npos) {
				score += w.length();
				pos += w.length();
			}
		}
		return score;

	}

	/**
	* @brief Intenta romper el cifrado Vigenère por fuerza bruta probando todas las claves posibles.
	* @param maxKeyLenght Longitud máxima de la clave a probar.
	* @return std::string Clave más probable encontrada.
	* @details Evalúa cada descifrado con la función @ref fitness para seleccionar la mejor coincidencia.
	* Imprime en consola la clave y el texto descifrado con mejor puntaje.
	*/
	static std::string breakEncode(const std::string& text, int maxKeyLenght) {
		std::string bestKey;
		std::string bestText;
		std::string trailKey;

		double bestScore = -std::numeric_limits<double>::infinity(); // Initialize best score

		// Funcion revursiva para generar todas las posibles claves de longitud
		std::function<void(int, int)> dfs = [&](int pos, int maxLen) {
			if (pos == maxLen) {
				Vigenere v(trailKey);
				std::string decodedText = v.decode(text);
				double score = fitness(decodedText); // Score the decoded text
				if (score > bestScore) {
					bestScore = score;
					bestKey = trailKey;
					bestText = decodedText;
				}
				return;
			}
			for (char c = 'A'; c <= 'Z'; ++c) {
				trailKey[pos] = c;
				dfs(pos + 1, maxLen);
			}
		};

		for (int L = 1; L <= maxKeyLenght; ++L) {
			trailKey.assign(L, 'A');
			dfs(0, L);
		}

		std::cout << "*** Fuerza Bruta Vigen�re ***\n";
		std::cout << "Clave encontrada:  " << bestKey << "\n";
		std::cout << "Texto descifrado:  " << bestText << "\n\n";
		return bestKey;
	}

private:
	std::string key; // The key for the Vigenere cipher
};

/*
#include "Prerequisites.h"
#include "Vigenere.h"

int main() {
	std::string text = "Hola este mensaje otorga una decima";
	std::string key = "RobertoCharreton00";

	std::cout << "Texto original: " << text << std::endl;
	std::cout << "Clave: " << key << std::endl;

	Vigenere vigenere(key);
	std::string encrypted = vigenere.encode(text);
	std::cout << "Texto cifrado: " << encrypted << std::endl;

	std::string decrypted = vigenere.decode(encrypted);
	std::cout << "Texto descifrado: " << decrypted << std::endl;


	return 0;
}

*/