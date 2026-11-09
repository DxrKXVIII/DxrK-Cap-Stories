#include "motor_lore.h" 
#include <cstdio>       
#include <cstring>
#include <string>

//Carga de lore
std::vector<std::string> cargarLore(std::string loreTexto)
{
    std::vector<std::string> loreLineas;
    char loreLineaX1[1024];
        
    FILE* lore = fopen(loreTexto.c_str(), "r");
        
    if (lore == NULL)
    {
        return loreLineas;
    }
    else
    {
        while(fgets(loreLineaX1, 1024, lore) != NULL) 
        {
            loreLineaX1[strcspn(loreLineaX1, "\n")] = '\0';
            loreLineas.push_back(loreLineaX1);
        }
    }

    fclose(lore);
    return loreLineas;
}

//Analisis de comando personalizado para acciones
bool analizarComando(std::string linea, std::string& tipo, std::string& valor)
{
	if (linea.length() > 2 && linea.front() == '[' && linea.back() == ']')
	{
		size_t posicionDosPuntos = linea.find(':');

			if (posicionDosPuntos != std::string::npos)
			{
				tipo = linea.substr(1, posicionDosPuntos - 1);
				valor = linea.substr(posicionDosPuntos + 1, linea.length() - posicionDosPuntos - 2);
				return true;
			}
	}
	return false;
}

//Animacion ascii
std::vector<std::string> cargarAnimacionAscii(int totalFrames)
{
    std::vector<std::string> animacion;
    
    for (int i = 1; i <= totalFrames; i++)
    {
        char ruta[100];
        sprintf(ruta, "assets/AsciiAnim/AsciiFrames/frame_%04d.txt", i);
        
        FILE* archivo = fopen(ruta, "r");
        if (!archivo) {
            printf("No se encontro %s\n", ruta);
            continue;
        }

        std::string frameCompleto = "";
        char linea[2048];
        
        while (fgets(linea, sizeof(linea), archivo)) 
        {
            frameCompleto += linea;
        }
        
        fclose(archivo);
        animacion.push_back(frameCompleto);
    }
    
    return animacion;
}
