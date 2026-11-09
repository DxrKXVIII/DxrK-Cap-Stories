#ifndef MOTOR_CORE_H
#define MOTOR_CORE_H

#include <raylib.h>
#include <vector>
#include <string>
#include <map>

enum PantallaActual
{
	MENU_INICIO,
	LEYENDO,
	MENU_HISTORIAS,
	NO_DISPONIBLE,
	CONFIRMAR_SALIR,
	CARGANDO_ASSETS,
	DESCARGANDO_ASSETS
};



struct EstadoJuego
{
	// Animación ASCII
    std::vector<std::string> framesAscii;
    int asciiFrameActual;
    int asciiContador;
    int asciiVelocidad;
	Font fuenteTerminal;
	
    //Texturas
    std::map <std::string, Texture2D> texturas;
	std::string fondoActual;
	std::string personajeActual;
	bool cargaLista;


    // Escritura y control
    size_t lineaActual;
    int framesContador;
    size_t letrasVisibles;
    int velocidadTexto;

    // Posiciones para UI
    int sizeFuente;
    int posYTexto;
    Vector2 posFondo;
    Vector2 posPersonaje;
    Vector2 sizeCajaDialogo;
    Vector2 posCajaDialogo;

	//Control de estados
	PantallaActual pantalla;
	int opcionSeleccionada;

    // Constructor
EstadoJuego (float anchoPantalla, float altoPantalla) 
    {
    	fondoActual = "";
    	personajeActual = "";
    	cargaLista = false;
    	
        // Animacion
        asciiFrameActual = 0;
        asciiContador = 0;
        asciiVelocidad = 10;
        fuenteTerminal = LoadFont("assets/Teletactile-3zavL.ttf");
       
        lineaActual = 0;
        framesContador = 0;
        letrasVisibles = 0;
        velocidadTexto = 2;
		
        pantalla = MENU_INICIO;
        opcionSeleccionada = 0;
    }
};

#endif
