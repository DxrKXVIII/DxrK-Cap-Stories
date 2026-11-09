#include "motor_graficos.h"

char caracterBrillo(float Brillo)
{
    const char escala[] = " .,-:;=+i1lrsceoxzaumnqpbkO0QCUXYLFGSEAPVDHKRBMWN8#@";

    int indice = (int)(Brillo / 255.0f * 51.0f);

    return escala[indice];
}

void dibujarTextoParpadeante(const char* texto, int posX, int posY, int fontSize, Color color, int framesContador, int velocidad = 30)
{
    if ((framesContador / velocidad) % 2 == 0)
    {
        DrawText(texto, posX, posY, fontSize, color);
    }
}

void dibujarPantallas(EstadoJuego& estado, const std::vector<std::string>& lore, float ancho, float alto)
{
    BeginDrawing();
    ClearBackground(BLACK);

		//Animacion ascii
if (estado.pantalla == MENU_INICIO || estado.pantalla == MENU_HISTORIAS)
        {
            if (estado.framesAscii.size() > 0) 
            {
                float tamanoFuenteAscii = alto * 0.0084f;
                Vector2 medida = MeasureTextEx(estado.fuenteTerminal, estado.framesAscii[estado.asciiFrameActual].c_str(), tamanoFuenteAscii, 1.0f);
                Vector2 posicionAscii = { (ancho / 4.0f) - (medida.x / 2.0f), (alto / 1.8f) - (medida.y / 2.0f) };
                DrawTextEx(estado.fuenteTerminal, estado.framesAscii[estado.asciiFrameActual].c_str(), posicionAscii, tamanoFuenteAscii, 1.0f, DARKGRAY);
            }
        }

            int posX = ancho * 0.65f; 
            int tTitulo = alto * 0.11f;
            int tOpcion = alto * 0.055f;
            
            int yTituloBase = alto * 0.14f;   
            int yOpcionBase = alto * 0.52f;   
            int espacioTitulos = tTitulo;
            int espacioOpciones = alto * 0.10f;
if (estado.pantalla == MENU_INICIO)
        {
            // 3. Dibujado de la cabecera 
            DrawText("DxrK Cap", posX, yTituloBase, tTitulo, WHITE);
            DrawText("Stories", posX, yTituloBase + espacioTitulos, tTitulo, WHITE);
            DrawText("V0.0", posX, yTituloBase + (espacioTitulos * 2), tTitulo, WHITE);
        
            // 4. Dibujado de opciones
            const char* opciones[5] = 
            { 
            	"  Mis historias",
            	"  Editor", 
            	"  Configuración", 
            	"  Información legal", 
            	"  Salir"
            };

            	for (int i = 0; i < 5; i++)
            	{
           				int posYActual = yOpcionBase + (espacioOpciones * i);
           
           				if (estado.opcionSeleccionada == i)
           				{
           					dibujarTextoParpadeante(opciones[i], posX, posYActual, tOpcion, WHITE, estado.framesContador, 20); // 20 hace un parpadeo un poco más rápido
							DrawText(">", posX, posYActual, tOpcion, WHITE);
           				}
            			else
            			{
            				DrawText(opciones[i], posX , posYActual, tOpcion, DARKGRAY);
            			}
            	}

        }
    
        else if(estado.pantalla == MENU_HISTORIAS)
        {
            int posX = ancho * 0.65f;
            int tTitulo = alto * 0.11f;
            int tOpcion = alto * 0.055f;
            
            int yTituloBase = alto * 0.14f;
            int yOpcionBase = alto * 0.52f;
            int espacioTitulos = tTitulo;
            int espacioOpciones = alto * 0.10f;

            DrawText("Mis", posX, yTituloBase, tTitulo, WHITE);
            DrawText("historias", posX, yTituloBase + espacioTitulos, tTitulo, WHITE);

            const char* opciones[5] = 
            { 
            	"  Voidless void",
            	"  Agregar historia", 
            	"  Menú principal" 
            };

            for (int i = 0; i < 3; i++)
            {
           			int posYActual = yOpcionBase + (espacioOpciones * i); 
           			if (estado.opcionSeleccionada == i)
       				{
      				dibujarTextoParpadeante(opciones[i], posX, posYActual, tOpcion, WHITE, estado.framesContador, 20); // 20 hace un parpadeo un poco más rápido
					DrawText(">", posX, posYActual, tOpcion, WHITE);
           			}
            		else
            		{
            			DrawText(opciones[i], posX , posYActual, tOpcion, DARKGRAY);
            		}
            }


        }

        else if (estado.pantalla == CONFIRMAR_SALIR)
		{
			const char* mensaje = "¿Seguro que quiere salir?";
			int posX = ancho / 2 - MeasureText(mensaje, 80) / 2;
			int posXOpcion = ancho / 2 - tOpcion;
			DrawText(mensaje, posX, alto / 2 - 40, 80, WHITE);
			
			const char* opciones[2] = 
            { 
            	"  No",
            	"  Sí"
            };

            	for (int i = 0; i < 2; i++)
            	{
           				int posYActual = yOpcionBase+ (alto / 20) + (espacioOpciones * i);
           
           				if (estado.opcionSeleccionada == i)
           				{
           					dibujarTextoParpadeante(opciones[i], posXOpcion, posYActual, tOpcion, WHITE, estado.framesContador, 20);
							DrawText(">", posXOpcion, posYActual, tOpcion, WHITE);
           				}
            			else
            			{
            				DrawText(opciones[i], posXOpcion , posYActual, tOpcion, DARKGRAY);
            			}
            	}

		}

		else if (estado.pantalla == CARGANDO_ASSETS)
		{
			if (!estado.cargaLista)
			{
				const char* msgCargando = "CARGANDO ASSETS EN VRAM...";
				int anchoTexto = MeasureText(msgCargando, 40);
				
				DrawText(msgCargando, (ancho - anchoTexto) / 2, (alto / 2) - 20, 40, WHITE);
			}
			else
			{
				const char* msgListo = "[ CARGA COMPLETA ]";
				int anchoListo = MeasureText(msgListo, 50);
				
				DrawText(msgListo, (ancho - anchoListo) / 2, (alto / 2) - 60, 50, WHITE);

			const char* msgEnter = "> PRESIONA ENTER PARA INICIAR <";
			int anchoEnter = MeasureText(msgEnter, 25);
		
			dibujarTextoParpadeante(msgEnter, (ancho - anchoEnter) / 2, (alto / 2) + 20, 25, WHITE, estado.framesContador);;
				
			}
		}

		else if (estado.pantalla == DESCARGANDO_ASSETS)
		{
			DrawText("Vaciando memoria...", ancho / 2 - 150, alto / 2, 40, WHITE);
		}
		
        else if (estado.pantalla == LEYENDO)
        {	

        	estado.sizeFuente = alto * 0.1f;
            std::string textoAnimado = lore[estado.lineaActual].substr(0, estado.letrasVisibles);
            int posX = ancho / 2 - (MeasureText(lore[estado.lineaActual].c_str(), estado.sizeFuente) / 2);

			// Fondos
			if (estado.fondoActual != "" && estado.texturas[estado.fondoActual].id != 0) 
			{
				float escalaFondo = ancho / (float)estado.texturas[estado.fondoActual].width;
				DrawTextureEx(estado.texturas[estado.fondoActual], estado.posFondo, 0.0f, escalaFondo, WHITE);
			}

			// Personajes          
			if (estado.personajeActual != "" && estado.texturas[estado.personajeActual].id != 0) 
			{
				float escalaPersonaje = alto / (float)estado.texturas[estado.personajeActual].height;
				DrawTextureEx(estado.texturas[estado.personajeActual], estado.posPersonaje, 0.0f, escalaPersonaje, WHITE);
			}
			//Caja dialogo
      		estado.posCajaDialogo = {0, (6.0f / 8.0f) * alto};
      		estado.sizeCajaDialogo = {ancho, (2.0f / 8.0f) * alto};
            DrawRectangleV(estado.posCajaDialogo, estado.sizeCajaDialogo, Fade(BLACK, 0.6f));



			//Dialogo
			estado.posYTexto = alto * (7.0f/8.0f) - estado.sizeFuente / 2;
            DrawText(textoAnimado.c_str(), posX, estado.posYTexto, estado.sizeFuente, WHITE);
        }

        else if (estado.pantalla == NO_DISPONIBLE)
        {
			const char* mensaje = "Función no disponible";
			int posX = ancho / 2 - MeasureText(mensaje, 80) / 2;
			DrawText(mensaje, posX, alto / 2 - 40, 80, WHITE);
			            
			const char* salir = "Presione ENTER para regresar";
			int salirPosX = ancho / 2 - MeasureText(salir, 30) / 2;
			DrawText(salir, salirPosX, alto / 2 + 60, 30, GRAY);	
        	
        }
    
    EndDrawing();
}

