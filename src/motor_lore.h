#ifndef MOTOR_LORE_H
#define MOTOR_LORE_H

#include <vector>
#include <string>

std::vector<std::string> cargarLore(std::string loreTexto);
bool analizarComando(std::string linea, std::string& tipo, std::string& valor);
std::vector<std::string> cargarAnimacionAscii(int totalFrames);

#endif
