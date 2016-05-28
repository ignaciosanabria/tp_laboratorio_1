#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <windows.h>

int main()
{
    char seguir='s';
    EMovie movie;

    while(seguir=='s')
    {


        switch(Menu())
        {
            case 1:
                system("cls");
                agregarPelicula(&movie);
                system("pause");
                break;
            case 2:
                system("cls");
                borrarPelicula(&movie);
                system("pause");
                break;
            case 3:
                system("cls");
                generarPagina(&movie);
                system("pause");
               break;
            case 4:
                seguir = 'n';
                printf("USTED HA SALIDO DEL MENU DE PELICULAS!!\n");
                break;
            default:
                printf("ERROR. DEBE UTILIZAR UN NUMERO ENTRE 1 y 4 PARA UTILIZAR EL MENU!!\n");
        }
    }

    return 0;
}
