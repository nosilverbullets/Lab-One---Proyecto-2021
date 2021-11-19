#ifndef PELICULAS_H_INCLUDED
#define PELICULAS_H_INCLUDED
#include "peliculas.h"
#include "usuarios.h"
#include "login.h"

typedef struct
{
    int idPelicula;
    char nombre[50];
    int anio;
    char genero[30];
    char actores[3][50];
    int calificacion;
    int estado;
} Pelicula;

void peliculas(Usuario aux);
void recomendarPelis(char archivoUsuarios[], char archivoPeliculas[], int idUsuario);
void contarGenerosArreglo(int A[],int validos,char archivoPeliculas[], int idUsuario,char *generoRecomendado);
void mostrarGeneroPorId (char archivoPeliculas[], int id,char *dato);
int archivoToArreglo(char archivoUsuarios[],int A[], int userid);
void arregloMostrar(int A[],int validos);
void cargarMilista(char archivoUsuarios[], char archivoPeliculas[], int idUsuario);
int existeIdArreglo(int peliculas[], int idBuscar);
void imprimirPeliculasMilista(char archivoPeliculas[], char archivoUsuarios[], int userid);
int nombrexid(char archivoPelicula[], char nombrePelicula[]);
int contarPeliculas (char archivoPeliculas[]);
void cargarPelicula(char archivoPeliculas[]);
void listarPeliculas (char archivoPeliculas[]);
void listarPeliculasGenero (char archivoPeliculas[], char genero[]);
void listarPeliculaid (char archivoPeliculas[], int id);
void mostrarPelicula(Pelicula aux);
void bajaPelicula(char archivoPeliculas[], int idPelicula);
int buscarPeliculaNombre(char archivoPeliculas[], char nombrePelicula[]);
int buscarPeliculaId(char archivoPeliculas[], int id);
int insertarPeliculaArreglo(Pelicula arreglo[], int validos, Pelicula nueva);
void mostrarPelicOrdenadasNombre(char archivoPeliculas[]);
void listarPeliculasAdmin (char archivoPeliculas[]);
void listarPeliculasBajaAdmin(char archivoPeliculas[]);
void mostrarPeliculaAdministrador(Pelicula aux);
void arregloStrucMostrar(Pelicula pelis[],int validos);
int arregloPosMenor(Pelicula pelis[],int validos,int pos);
void PeliculasArregloOrdenarSeleccion(Pelicula pelis[],int validos);
int peliToArreglo(char fileName[], Pelicula pelis[]);

#endif // PELICULAS_H_INCLUDED
