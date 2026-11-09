#include <raylib.h>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <map>

// Librerias propias
#include "motor_lore.h"
#include "motor_core.h"
#include "motor_graficos.h"

float alto = 720;
float ancho = 1280;
int ultimoEstado = 0;

// Inicio del main
int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(ancho, alto, "DxrK Cap Stories V0.1");
	SetTargetFPS(60);

	EstadoJuego estado(ancho, alto);

	// Carga de lore/texto
	std::string loreTexto = "assets/lore.txt";
	std::vector<std::string> lore = cargarLore(loreTexto);
	estado.framesAscii = cargarAnimacionAscii(50);

	//Bandera de cerrar
	bool cerrarMotor = false;
	
	// Inicio del ciclo principal
	while(!WindowShouldClose() && !cerrarMotor)
	{
		ancho = GetScreenWidth();
		alto = GetScreenHeight();
		        
		if (IsKeyPressed(KEY_F11)) 
		{
			ToggleFullscreen();
		}

		if (estado.framesAscii.size() > 0) 
		{
		            estado.asciiContador++;
		            if (estado.asciiContador >= estado.asciiVelocidad) 
		            {
		                estado.asciiContador = 0;
		                estado.asciiFrameActual++;
		                
		                if (estado.asciiFrameActual >= (int)estado.framesAscii.size()) 
		                {
		                    estado.asciiFrameActual = 0; 
		                }
		            }
		 }
	
		if (estado.pantalla == MENU_INICIO)
		{	
			ultimoEstado = 0;
			estado.framesContador++;
			//Control menu
			if(IsKeyPressed(KEY_DOWN)) estado.opcionSeleccionada++;
			if(IsKeyPressed(KEY_UP)) estado.opcionSeleccionada--;

			//Limite de opciones
			if(estado.opcionSeleccionada > 4) estado.opcionSeleccionada = 0;
			if(estado.opcionSeleccionada < 0) estado.opcionSeleccionada = 4;

			if (IsKeyPressed(KEY_ENTER))
			{
					switch (estado.opcionSeleccionada)
					{
						case 0:
						{
							estado.pantalla = MENU_HISTORIAS;
							estado.opcionSeleccionada = 0;
							break;
						}

						case 1:
						{	
								estado.pantalla = NO_DISPONIBLE;	
								break;
						}
						case 2:
						{	
								estado.pantalla = NO_DISPONIBLE;	
								break;
						}
						case 3:
						{	
								estado.pantalla = NO_DISPONIBLE;	
								break;
						}
						case 4:
						{
							estado.pantalla = CONFIRMAR_SALIR;
							estado.opcionSeleccionada = 0;
							break;
						}
					}
			}


		}
	

		else if (estado.pantalla == MENU_HISTORIAS)
		{
			ultimoEstado = 1;
			estado.framesContador++;
			//Control menu
			if(IsKeyPressed(KEY_DOWN)) estado.opcionSeleccionada++;
			if(IsKeyPressed(KEY_UP)) estado.opcionSeleccionada--;

			//Limite de opciones
			if(estado.opcionSeleccionada > 2) estado.opcionSeleccionada = 0;
			if(estado.opcionSeleccionada < 0) estado.opcionSeleccionada = 2;

			if (IsKeyPressed(KEY_ENTER))
			{
				switch(estado.opcionSeleccionada)
				{
					case 0:
					{
						estado.pantalla = CARGANDO_ASSETS;
						break;
					}
					case 1:
					{
						estado.pantalla = NO_DISPONIBLE;
						break;
					}
					case 2:
					{
						estado.pantalla = MENU_INICIO;
						estado.opcionSeleccionada = 0;
						break;
					}
				}

				
			}


		}

		else if (estado.pantalla == CARGANDO_ASSETS)
		{
			estado.framesContador++;

			if (estado.framesContador > 10 && !estado.cargaLista)
			{
				std::string tipoComando = "";
				std::string valorComando = "";
				size_t lector = 0;
				FILE *archivo = fopen("directorio_assets.txt", "w");
						

			// Lector de comandos y carga en VRAM
				while (lector < lore.size())
				{
					if (analizarComando(lore[lector], tipoComando, valorComando))
					{

						if (tipoComando == "FONDO" || tipoComando == "PERSONAJE")
						{
							estado.texturas[valorComando] = LoadTexture(valorComando.c_str());   

							if(archivo != NULL)
							{
								fprintf(archivo, "%s\n", valorComando.c_str());
							}
						}
										
					}
				lector++;
				}
			if(archivo != NULL) fclose(archivo);
			estado.cargaLista = true;	
			}
			if (estado.cargaLista)
			{
				if (IsKeyPressed(KEY_ENTER))
				{
					estado.pantalla = LEYENDO;
					estado.cargaLista = false;
					estado.lineaActual = 0;
					estado.letrasVisibles = 0;
					estado.framesContador = 0;
				}
			}
		}
		
		else if (estado.pantalla == LEYENDO)
		{
			ultimoEstado = 2;
			std::string tipoComando = "";
			std::string valorComando = "";

			// Interceptor de comandos en tiempo real
			while (estado.lineaActual < lore.size() && analizarComando(lore[estado.lineaActual], tipoComando, valorComando))
			{
				if (tipoComando == "FONDO")
				{
					estado.fondoActual = valorComando;
				}
				else if (tipoComando == "PERSONAJE")
				{
					estado.personajeActual = valorComando;
				}
				else if (tipoComando == "FINHISTORIA")
				{
					estado.fondoActual = "";
					estado.personajeActual = "";
					estado.letrasVisibles = 0;
					estado.framesContador = 0;
					estado.pantalla = DESCARGANDO_ASSETS;
					break;
				}
				
				estado.lineaActual++;
				estado.letrasVisibles = 0;
				estado.framesContador = 0;
			}
	
			estado.framesContador++;
	
			// Animación de texto
			if(estado.framesContador >= estado.velocidadTexto)
			{
				estado.framesContador = 0;
	
				if(estado.letrasVisibles < lore[estado.lineaActual].length())
				{
					estado.letrasVisibles++;
				}
			}

			//Controles
			if(IsKeyPressed(KEY_ENTER))
			{
				if (estado.letrasVisibles < lore[estado.lineaActual].length())
				{
					estado.letrasVisibles = lore[estado.lineaActual].length();
				}
				else if(estado.lineaActual < lore.size() - 1)
				{
					estado.lineaActual++;
					estado.letrasVisibles = 0;
					estado.framesContador = 0;
				}
				else
				{
					estado.letrasVisibles = 0;
					estado.framesContador = 0;
					estado.pantalla = DESCARGANDO_ASSETS;
				}
			}
		}


		else if (estado.pantalla == DESCARGANDO_ASSETS)
		{	
			estado.framesContador++;
			
			if (estado.framesContador > 10)
			{
				for (auto& par : estado.texturas)
				{
					UnloadTexture(par.second);
				}				

				estado.texturas.clear();
				estado.pantalla = MENU_HISTORIAS;
				estado.opcionSeleccionada = 0;
				estado.framesContador = 0;
				
			}
		}




		else if (estado.pantalla == NO_DISPONIBLE)
		{
			if (IsKeyPressed(KEY_ENTER))
		    {
				switch(ultimoEstado)
				{
					case 0:
					{
						estado.pantalla = MENU_INICIO;
						break;
					}
					case 1:
					{
						estado.pantalla = MENU_HISTORIAS;
						break;
					}
					case 2:
					{
						estado.pantalla = LEYENDO;
						break;
					}
				}
			}
		}

		else if (estado.pantalla == CONFIRMAR_SALIR)
		{	
			estado.framesContador++;
			if(IsKeyPressed(KEY_DOWN)) estado.opcionSeleccionada++;
			if(IsKeyPressed(KEY_UP)) estado.opcionSeleccionada--;

			if(estado.opcionSeleccionada > 1) estado.opcionSeleccionada = 0;
			if(estado.opcionSeleccionada < 0) estado.opcionSeleccionada = 1;

			if(IsKeyPressed(KEY_ENTER))
			{
				if(estado.opcionSeleccionada == 0)
				{
					estado.pantalla = MENU_INICIO;
				}
				else if(estado.opcionSeleccionada == 1)
				{
					cerrarMotor = true;
				}
				
			}	
		}
		// Dibujo
		dibujarPantallas(estado, lore, ancho, alto);
			
	}
	

// Limpieza de RAM al salir
	for (auto& par : estado.texturas)
	{
		UnloadTexture(par.second);
	}
	estado.texturas.clear();
	UnloadFont(estado.fuenteTerminal);
	CloseWindow();
	return 0;
}
