#pragma once
#include "Prerequisites.h"

/**
 * @class CesarEncryption
 * @brief Implementación del cifrado César para texto alfabético y numérico.
 * Este cifrado desplaza las letras y números un número fijo de posiciones en el alfabeto o dígitos.
 * También incluye métodos para realizar ataques por fuerza bruta y un análisis básico de frecuencia
 * para intentar deducir la clave.
 */
class
	CesarEncryption {
public:
	CesarEncryption() = default;
	~CesarEncryption() = default;

	/**
	* @brief Cifra un texto utilizando el algoritmo César.
	* @param texto Texto a cifrar (puede incluir letras, números y símbolos).
	* @param desplazamiento Número de posiciones a desplazar (1-25 recomendado).
	* @return std::string Texto cifrado.
	*/
	std::string
		encode(const std::string& texto, int desplazamiento) {
		std::string result = "";

		for (char c : texto) {
			if (c >= 'A' && c <= 'Z') {
				result += (char)(((c - 'A' + desplazamiento) % 26) + 'A');
			}
			else if (c >= 'a' && c <= 'z') {
				result += (char)(((c - 'a' + desplazamiento) % 26) + 'a');
			}
			else if (c >= '0' && c <= '9') {
				result += (char)(((c - '0' + desplazamiento) % 10) + '0');
			}
			else {
				result += c;
			}
		}

		return result;
	}


   /**
	* @brief Descifra un texto previamente cifrado con César.
	* @param texto Texto cifrado.
	* @param desplazamiento Número de posiciones usadas originalmente para cifrar.
	* @return std::string Texto descifrado.
	*/
	std::string
		decode(const std::string& texto, int desplazamiento) {
		return encode(texto, 26 - (desplazamiento % 26));
	}

   /**
	* @brief Intenta descifrar un texto probando todas las claves posibles (fuerza bruta).
	* @param texto Texto cifrado.
	* @post Imprime en consola los 26 posibles resultados con su respectiva clave.
	*/
	void bruteForceAttack(const std::string& texto) {
		std::cout << "\nIntentos de descifrado por fuerza bruta:\n";
		for (int clave = 0; clave < 26; clave++) {
			std::string intento = encode(texto, 26 - clave);
			std::cout << "Clave " << clave << ": " << intento << std::endl;
		}
	}

   /**
	* @brief Evalúa una clave probable mediante análisis de frecuencia.
	* Utiliza la letra más común del texto cifrado y la compara con las letras
	* más frecuentes en español (`e, a, o, s, r...`), además de buscar palabras comunes.
	* @param texto Texto cifrado.
	* @return int Clave más probable para descifrar.
	*/
	int evaluatePossibleKey(const std::string& texto) {
	int frecuencias[26] = { 0 };

		// Contar frecuencias de letras
		for (char c : texto) {
			if (c >= 'a' && c <= 'z') {
				frecuencias[c - 'a']++;
			}
			else if (c >= 'A' && c <= 'Z') {
				frecuencias[c - 'A']++;
			}
		}

		// Letras comunes en espa?ol (orden de frecuencia)
		const char letrasEsp[] = { 'e', 'a', 'o', 's', 'r', 'n', 'i', 'd', 'l', 'c' };

		// Buscar la letra m?s frecuente en el mensaje cifrado
		int indiceMax = 0;
		for (int i = 1; i < 26; ++i) {
			if (frecuencias[i] > frecuencias[indiceMax]) {
				indiceMax = i;
			}
		}

		// Probar varias suposiciones de mapeo
		int mejorClave = 0;
		int mejorPuntaje = -1;

		for (char letraRef : letrasEsp) {
			int clave = (indiceMax - (letraRef - 'a') + 26) % 26;
			int puntaje = 0;

			// Descifrar con esa clave
			std::string descifrado = encode(texto, 26 - clave);

			// Palabras comunes simples
			std::string comunes[] = { "el", "de", "la", "que", "en", "y", "los", "se" };

			for (std::string palabra : comunes) {
				if (descifrado.find(palabra) != std::string::npos) {
					puntaje++;
				}
			}

			if (puntaje > mejorPuntaje) {
				mejorPuntaje = puntaje;
				mejorClave = clave;
			}
		}

		return mejorClave;
	}

private:

};