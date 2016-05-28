#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
/*FUNCION DE MENU*/
int Menu()
{
       int opcion=0;

        printf("BIENVENIDO AL MENU DE PELICULAS:\n");
        printf("1- Agregar pelicula\n");
        printf("2- Borrar pelicula\n");
        printf("3- Generar pagina web\n");
        printf("4- Salir\n");
        scanf("%d",&opcion);

        return opcion;

}
/*FUNCION QUE AGREGA PELICULAS AL ARCHIVO BINARIO bin */
int agregarPelicula(EMovie *movie)
{
    FILE *bin;
    movie->flag=0;


        printf("Ingrese titulo de pelicula:\n");
        fflush(stdin);
        gets(movie->titulo);
        Val_tan(movie->titulo,31);
        printf("Ingrese genero de pelicula:\n");
        fflush(stdin);
        gets(movie->genero);
        Val_tan(movie->genero,31);
        printf("Ingrese la duracion de pelicula *En minutos :\n");
        scanf("%d",&movie->duracion);
        movie->duracion=val_int(movie->duracion, 1, 300);
        printf("Ingrese la descripcion de pelicula:\n");
        fflush(stdin);
        gets(movie->descripcion);
        Val_tan(movie->descripcion, 501);
        printf("Ingrese el puntaje de pelicula *1-100 :\n");
        scanf("%d",&movie->puntaje);
        movie->puntaje=val_int(movie->puntaje,1,100);
        printf("Ingrese link de imagen:\n");
        fflush(stdin);
        gets(movie->linkImagen);
        Val_tan(movie->linkImagen, 151);
        movie->flag=1;

        if((bin=fopen("datosmovie.bin","ab+"))==NULL)
        {
            printf("ERROR AL CARGAR LOS DATOS EN EL ARCHIVO!!\n");
        }
        else
        {
             fwrite(movie,sizeof(EMovie),1,bin);
        }
        printf("SE GUARDARON LOS DATOS DE LA PELICULA!!\n");
        fclose(bin);
        return 0;
}
/*FUNCION PARA BORRAR PELICULAS DEL ARCHIVO BINARIO bin*/
int borrarPelicula(EMovie *movie)
{
    FILE *punteroDato;
    char auxTitulo[20];
    int encontro=0;

    printf("Ingrese nombre de la pelicula que desea borrar:");
    fflush(stdin);
    strlwr(gets(auxTitulo));

    if((punteroDato=fopen("datosmovie.bin","r+"))==NULL)
    {
      printf("NO SE PUEDE ABRIR EL ARCHIVO!!");
      return 0;

    }
    else
    {
        while((fread(movie,sizeof(EMovie),1,punteroDato))!=0)
        {
           if(movie->flag==1)
            {
                strlwr(movie->titulo);
                if(strcmp(movie->titulo,auxTitulo)==0)
               {
                   fseek(punteroDato,-sizeof(EMovie),SEEK_CUR);
                   movie->flag=0;
                   fwrite(movie,sizeof(EMovie),1,punteroDato);


                   encontro=1;
                   printf("LA PELICULA HA SIDO BORRADA CORRECTAMENTE!!");

                   break;
               }
            }
        }

        if(encontro==0)
        {
            printf("NO SE ENCONTRO LA PELICULA SOLICITADA!!");
            return 0;
        }

    }

    if(fclose(punteroDato)==-1)
    {
        printf("ERROR AL CERRAR EL ARCHIVO, INTENTELO DE NUEVO!!");
        return 0;
    }
    else
    {
        system("pause");
    }
    return 0;
}
/*FUNCION DE GENERAR UNA PAGINA HTML */
int generarPagina(EMovie *movie)
{
    FILE *punteroDato,*punteroHtml;

    if((punteroDato=fopen("datosmovie.bin","rb"))!=NULL)
    {
        if((punteroHtml=fopen("listadoMovies.html","wb"))!=NULL)
        {
            fprintf(punteroHtml,"<!DOCTYPE html>\n"
            "<!-- Template by Quackit.com -->\n"
            "<html lang='en'>\n"
            "<head>\n"
            "    <meta charset='utf-8'>\n"
            "    <meta http-equiv='X-UA-Compatible' content='IE=edge'>\n"
            "    <meta name='viewport' content='width=device-width, initial-scale=1'>\n"
            "    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->\n"
            "    <title>Lista peliculas</title>\n"
            "    <!-- Bootstrap Core CSS -->\n"
            "    <link href='css/bootstrap.min.css' rel='stylesheet'>\n"
            "    <!-- Custom CSS: You can use this stylesheet to override any Bootstrap styles and/or apply your own styles -->\n"
            "    <link href='css/custom.css' rel='stylesheet'>\n"
            "    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->\n"
            "    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->\n"
            "    <!--[if lt IE 9]>\n"
            "        <script src='https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js'></script>\n"
            "        <script src='https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js'></script>\n"
            "    <![endif]-->\n"
            "</head>\n"
            "<body>\n"
            "    <div class='container'>\n"
            "        <div class='row'>\n");
            while((fread(movie,sizeof(EMovie),1,punteroDato))!=0)
            {

               if(movie->flag==1)
               {
                    fprintf(punteroHtml,"<!-- Repetir esto para cada pelicula -->\n"
                    "<article class='col-md-4 article-intro'>\n"
                    "<a href='#'>\n"
                    "<img class='img-responsive img-rounded' src='%s' alt=''>\n"
                    "</a>\n"
                    "<h3>\n"
                    "<a href='#'>%s</a>\n"
                    "</h3>\n"
                    "<ul>\n"
                    "<li>Genero:%s</li>\n"
                    "<li>Puntaje:%d</li>\n"
                    "<li>Duracion:%d</li>\n"
                    "</ul>\n"
                    "<p>%s</p>\n"
                    " </article>\n"
                    "<!-- Repetir esto para cada pelicula -->\n",movie->linkImagen,movie->titulo,movie->genero,movie->puntaje,movie->duracion,movie->descripcion);
               }

            }

            fprintf(punteroHtml,"        </div>\n"
            "<!-- /.row -->\n"
            "</div>\n"
            "<!-- /.container -->\n"
            "<!-- jQuery -->\n"
            "<script src='js/jquery-1.11.3.min.js'></script>\n"
            "<!-- Bootstrap Core JavaScript -->\n"
            "<script src='js/bootstrap.min.js'></script>\n"
            "<!-- IE10 viewport bug workaround -->\n"
            "<script src='js/ie10-viewport-bug-workaround.js'></script>\n"
            "<!-- Placeholder Images -->\n"
            "<script src='js/holder.min.js'></script>\n"
            "</body>\n"
            "</html>\n");
        }
        else
        {
            printf("EL HTML NO FUE CREADO!!\n");
            return 0;
        }

    }
    else
    {
        printf("NO SE PUDO CARGAR LA ESTRUCTURA DE PELICULAS!!\n");
        return 0;
    }

    printf("SE CREO CORRECTAMENTE EL LISTADO DE PELICULAS\n");
    fclose(punteroDato);
    fclose(punteroHtml);

    return 0;

}

/*FUNCION VALIDACION DE CADENA DE CARACTERES */
void Val_tan(char x[], int tan)
{
    while(strlen(x)>tan-1)
    {
     printf("ERROR. Reingrese una cadena que no exceda los %d caracteres: \n",tan-1);
     fflush(stdin);
     gets(x);
    }
}

/*FUNCION DE VALIDACION DE ENTEROS */

int val_int(int dato, int min, int max)
{
    while(dato<min || dato>max)
        {
            printf("Error. Reingrese el dato entre %d y %d: \n", min, max);
            scanf("%d",&dato);
        }
        return dato;
}
