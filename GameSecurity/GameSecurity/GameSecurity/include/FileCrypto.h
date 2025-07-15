#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"

// Funciones de utilidad para manejo de archivos y cifrado
namespace fs = std::filesystem;
std::string readFile(const std::string& filename);
void writeFile(const std::string& filename, const std::string& content);
void cifrarArchivo(XOREncoder& encoder, const std::string& key);
void descifrarArchivo(XOREncoder& encoder, const std::string& key);
