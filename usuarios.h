#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#include "peliculas.h"
#include "usuarios.h"
#include "login.h"

typedef struct
{
    int id;
    char nombre[50];
    char mail[50];
    char celular[15];
    char nombreDeUsuario[20];
    char contrasenia[8];
    int miLista[50];
    int tipodeusuario;            // <- 0: normal // 1: admin
    int estado;
} Usuario;

void usuarios(Usuario aux);
int contarUsuarios (char archivoUsuarios[]);
void mostrarUsuarioId(char archivoUsuarios[], int id);
int buscarNombreUsuario(char archivoUsuarios[], char nombreUsuario[]);
int cargarUsuario(char archivoUsuarios[], int isadmin);
void imprimirMilista(Usuario aux);
void listarUsuarios(char archivoUsuarios[]);
void mostrarUsuario(Usuario aux);
void listarMilista(char archivoUsuarios[], Usuario aux, char archivoPeliculas[]);
void modificarUsuario(char archivoUsuarios[], int idUsuario);
void bajaUsuario(char archivoUsuarios[], int idUsuario);
Usuario buscarUsuarioPorId(char archivoUsuarios[], int userId);
void eliminarDatoArreglo(int arreglo[], int dato);
void actualizarUsuario(char archivoUsuarios[], Usuario usuario);
void eliminarPeliculaLista(char archivoUsuarios[], char archivoPelicula[], int userId);

#endif // USUARIOS_H_INCLUDED
