#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <ctype.h>
#include "peliculas.h"
#include "usuarios.h"
#include "login.h"

// TP Programacion 2021
// Prof Archuby, Carolina
//
//  Alumnos
// Di meglio, jose luis
// Mantobani, Matias
// D'Aleo, Braian

// Credenciales
// admin 1234 (admin)
// mati 1234 (normal)

int main()
{
    setlocale(LC_ALL, "spanish");
    char archivoUsuarios[]= {"usuarios.dat"};
    char archivoPeliculas[]= {"peliculas.dat"};

    home();

    return 0;
}
