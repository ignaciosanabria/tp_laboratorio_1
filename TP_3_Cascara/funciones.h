#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct{
    char titulo[30];
    char genero[30];
    int duracion;
    char descripcion[500];
    int puntaje;
    int flag; //VARIABLE USADA COMO BANDERA PARA LAS FUNCIONES.C
    char linkImagen[150];
}EMovie;

/**
 *  Agrega una pelicula al archivo binario
 *  @param *movie puntero de la estructura a ser agregada al archivo
 *  @return el retorno 0 al finalizar la funcion
 */
int agregarPelicula(EMovie *movie);

/**
 *  Borra una pelicula del archivo binario
 *  @param *movie puntero de la estructura a ser eliminada al archivo
 *  @return el retorno es 0 al finalizar la funcion.
 */
int borrarPelicula(EMovie *movie);

/**
 *  Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 *  @param *movie puntero que apunta hacia la estructura movie para crear html
 *  @return el retorno es 0 al finalizar la funcion
 */
int generarPagina(EMovie *movie);
void Val_tan(char x[], int tan); // FUNCION DE VALIDACION DE CADENA DE CARACTERES
int val_int(int dato, int min, int max); //FUNCION DE VALIDACION DE ENTEROS
int Menu();
#endif // FUNCIONES_H_INCLUDED
