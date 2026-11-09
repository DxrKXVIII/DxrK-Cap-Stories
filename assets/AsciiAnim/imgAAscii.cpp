#include "raylib.h"
#include <iostream>

float obtenerBrillo(Color *pixeles, size_t pixelActual);
char caracterBrillo(float Brillo);

int main(int argc, char *argv[])
{
    SetTraceLogLevel(LOG_WARNING);
    Image imagen = LoadImage(argv[1]);
    Color *pixeles = LoadImageColors(imagen);

    size_t bloqueTamano = 8;
    size_t bloquesPorFila = imagen.width / bloqueTamano;
    float brilloPixelActual = 0;
    float promedioTotal = 0;
    float suma = 0;

    size_t elementos = 0;
    size_t pixelActual = 0;
    size_t inicioBloque = 0;

    int bloquesContador = 0;

    int X = 0;
    int Y = 0;

    if (pixeles == nullptr)
    {
        std::cout << "ERROR: pixeles es nullptr\n";
        return 1;
    }

    size_t bloquesTotales =
        (imagen.width / bloqueTamano) *
        (imagen.height / bloqueTamano);

    while (bloquesContador < (int)bloquesTotales)
    {
        inicioBloque =
        (bloquesContador / bloquesPorFila) *
        bloqueTamano *
        imagen.width
            +
            (bloquesContador % bloquesPorFila) *
            bloqueTamano;

        while (elementos < bloqueTamano * bloqueTamano)
        {
            pixelActual = inicioBloque + Y * imagen.width + X;

            brilloPixelActual =
                obtenerBrillo(pixeles, pixelActual);

            suma += brilloPixelActual;

            elementos++;
            X++;

            if (X == (int)bloqueTamano)
            {
                X = 0;
                Y++;
            }
        }

        promedioTotal = suma / elementos;

        char caracter = caracterBrillo(promedioTotal);

        std::cout << caracter;

        if ((bloquesContador + 1) % bloquesPorFila == 0)
        {
            std::cout << "\n";
        }

        bloquesContador++;
        elementos = 0;
        suma = 0;
        X = 0;
        Y = 0;
    }

    UnloadImageColors(pixeles);
    UnloadImage(imagen);

    return 0;
}

float obtenerBrillo(Color *pixeles, size_t pixelActual)
{
    Color pixel = pixeles[pixelActual];

    float brillo =
        (float)pixel.r * 0.2126 +
        (float)pixel.g * 0.7152 +
        (float)pixel.b * 0.0722;

    return brillo;
}

char caracterBrillo(float Brillo)
{
    const char escala[] = "    .,-:;=+i1lrsceoxzaumnqpbkO0QCUXYLFGSEAP#@";

    int indice = (int)(Brillo / 255.0f * 44.0f);

    return escala[indice];
}
