#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include "peliculas.h"
#include "usuarios.h"
#include "login.h"

void home();
void logo();
void signin(char archivoUsuarios[]);
void login();
int validarUsuario(char archivoUsuarios[], char currentUser[], char currentPassword[]);

#endif // LOGIN_H_INCLUDED
