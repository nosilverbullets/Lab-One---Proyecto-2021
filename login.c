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

void home()
{
    char archivoUsuarios[]= {"usuarios.dat"};
    char archivoPeliculas[]= {"peliculas.dat"};

    int opcion;
    do
    {
        logo();


        printf("\n                        (1) Iniciar sesión ");
        printf("\n                        (2) Registrarse ");
        printf("\n                        (3) Salir ");
        printf("\n");
        printf("\n Opción: ");
        scanf("%i", &opcion);
        switch(opcion)
        {
        case 1:
            system("cls");
            login();
            break;

        case 2:
            system("cls");
            signin(archivoUsuarios);
            break;

        case 3:
            system("cls");
            exit(1);
            break;

        default:
            printf("\nOpción inválida, ingrese nuevamente ");
            break;
        }
        system("cls");
    }
    while(opcion !=3);
}

void logo()
{
    printf("\n     #########                        #######             ######");
    printf("\n     #########                         #####          #########");
    printf("\n      #####            ####### ######  ############*   ########");
    printf("\n      #####          ################  ##############     #####");
    printf("\n      #####         #####     #####    ######   ######    #####");
    printf("\n      #####    #### *####     #####    ######   #####*    #####");
    printf("\n    ###############  ################  ##############  ##########");
    printf("\n    ###############    *#####* ######  ###########*   ############");
    printf("\n");
    printf("\n              Sistema de gestión de películas y usuario ");
    printf("\n ");
}


void signin(char archivoUsuarios[])
{
    logo();

    cargarUsuario(archivoUsuarios, 0);
    system("cls");
}

void login()
{
    char archivoUsuarios[]= {"usuarios.dat"};
    char archivoPeliculas[]= {"peliculas.dat"};

    char currentUser[50];
    char curretPassword[8];

    logo();

    printf("\n              Sistema de gestión de películas y usuarios");
    printf("\n");
    printf("\n                        > Ingrese usuario: ");
    fflush(stdin);
    gets(currentUser);
    printf("\n                       > Ingrese contraseña: ");
    fflush(stdin);
    gets(curretPassword);

    validarUsuario(archivoUsuarios, currentUser, curretPassword);
}

int validarUsuario(char archivoUsuarios[], char currentUser[], char currentPassword[])
{
    FILE * arch;
    arch=fopen(archivoUsuarios, "rb");
    Usuario aux;
    int flag = 0;
    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Usuario), 1, arch)>0)
        {
            if (strcmp(aux.nombre, currentUser)==0 && strcmp(aux.contrasenia, currentPassword)==0 && aux.estado==1)
            {
                if (aux.tipodeusuario == 1)
                {
                     system("cls");
                     usuarios(aux);
                }
                else
                {
                     system("cls");
                     peliculas(aux);
                }
            }
        }
        printf("\nUsuario o contraseña inválidos");
        printf("\nIngrese los datos nuevamente...");
        system("pause");
        fclose(arch);
    }
    return flag;
}
