#ifndef MOTOR_GRAFICOS_H
#define MOTOR_GRAFICOS_H

#include <raylib.h>
#include <vector>
#include <string>
#include "motor_core.h"

void dibujarPantallas (EstadoJuego& estado, const std::vector<std::string>& lore, float ancho, float alto);

#endif
