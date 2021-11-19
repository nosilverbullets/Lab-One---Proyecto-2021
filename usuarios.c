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

void usuarios(Usuario aux)
{
    char archivoUsuarios[]= {"usuarios.dat"};
    char archivoPeliculas[]= {"peliculas.dat"};

    int idBuscar=0, idModificar=0;

    int opcion=0, idBaja=0;
    char opcionNombre[15];
    do
    {
        logo();
        printf("\n                        Panel de administracion:");
        printf("\n");
        printf("\n (1) - Cargar nuevo usuario ");
        printf("\n (2) - Listar usuarios");
        printf("\n (3) - Buscar usuario por nombre ");
        printf("\n (4) - Modificar usuario por id ");
        printf("\n (5) - Dar de baja / alta usuario ");
        printf("\n (6) - Cargar película ");
        printf("\n (7) - Dar de baja / alta película ");
        printf("\n (8) - Listar películas ");
        printf("\n (9) - Listar películas dadas de baja ");
        printf("\n (10) - Mostrar usuario por id ");

        printf("\n");
        printf("\n (11) - Cerrar sesión ");
        printf("\n");
        printf("\n Opción: ");

        fflush(stdin);
        scanf("%i", &opcion);

        while(opcion < 1 || opcion > 11)
        {
            printf("\nPor favor, ingrese una opción válida...\n");
            fflush(stdin);
            scanf("%i", &opcion);
        }

        switch(opcion)
        {
        case 1:
            cargarUsuario(archivoUsuarios, 1);
            system("pause");
            break;

        case 2:
            listarUsuarios(archivoUsuarios);
            system("pause");
            break;

        case 3:
            printf("\nIngrse nombre a buscar: ");
            fflush(stdin);
            gets(opcionNombre);
            buscarNombreUsuario(archivoUsuarios, opcionNombre);
            system("pause");
            break;

        case 4:
            printf("\nIngrese el id a modificar: ");
            scanf("%d", &idModificar);
            modificarUsuario(archivoUsuarios, idModificar);
            system("pause");
            break;

        case 5:
            printf("\nIngrese el id a modificar: ");
            scanf("%d", &idModificar);
            bajaUsuario(archivoUsuarios, idModificar);
            system("pause");
            break;

        case 6:
            cargarPelicula(archivoPeliculas);
            system("pause");
            break;

        case 7:
            printf("\nIngrese id a dar de baja: \n");
            scanf("%d", &idBaja);
            bajaPelicula(archivoPeliculas, idBaja);
            system("pause");
            break;

        case 8:
            listarPeliculasAdmin(archivoPeliculas);
            system("pause");
            break;

        case 9:
            listarPeliculasBajaAdmin(archivoPeliculas);
            system("pause");
            break;

        case 10:
            printf("\nIngrese id a buscar ");
            scanf("%d", &idBuscar);
            mostrarUsuarioId(archivoUsuarios, idBuscar);
            system("pause");
            break;

        case 11:
            system("cls");
            break;

        default:
            printf("\nOpción inválida!\n");
            system("pause");
            break;
        }
        system("cls");
    }
    while (opcion != 11);
}

int contarUsuarios (char archivoUsuarios[])
{
    int registros;
    FILE*arch;
    arch=fopen(archivoUsuarios, "rb");

    if (arch !=NULL)
    {
        fseek(arch,0,SEEK_END);
        registros= ftell(arch)/sizeof(Usuario);

        fclose(arch);
    }
    return registros;
}

void mostrarUsuarioId(char archivoUsuarios[], int id)
{
    FILE * arch;
    arch=fopen(archivoUsuarios, "rb");
    Usuario aux;
    int flag = 0;
    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Usuario), 1, arch)>0)
        {
            if (aux.id==id)
            {
                mostrarUsuario(aux);
            }
        }
        fclose(arch);
    }
}

int buscarNombreUsuario(char archivoUsuarios[], char nombreUsuario[])
{
    FILE * arch;
    arch=fopen(archivoUsuarios, "rb");
    Usuario aux;
    int flag = 0;
    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Usuario), 1, arch)>0)
        {
            if (strcmpi(aux.nombre, nombreUsuario)==0 && aux.estado==1)
            {
                flag=1;
                mostrarUsuario(aux);
            }

        }
        fclose(arch);
    }
    return flag;
}

int cargarUsuario(char archivoUsuarios[], int isadmin)
{
    FILE *arch;
    arch=fopen(archivoUsuarios,"ab");
    if (arch==NULL)
        exit(1);
    Usuario aux;
    char opcion;
    int i=0;

    aux.id=contarUsuarios(archivoUsuarios)+1;
    printf("\n\nCargando usuario... ");
    printf("\nIngrese el nombre: ");
    fflush(stdin);
    if (buscarNombreUsuario(archivoUsuarios, gets(aux.nombre)) ==0)
    {
        printf("\nIngrese contraseña: ");
        fflush(stdin);
        gets(aux.contrasenia);

        if (isadmin)
        {
            printf("\nIngrese tipo de usuario: (1) admin (0) normal ");
            scanf("%d", &aux.tipodeusuario);
        }else
            aux.tipodeusuario=0;
        printf("\nIngrese teléfono: ");
        fflush(stdin);
        gets(aux.celular);
        printf("\nIngrese mail: ");
        fflush(stdin);
        gets(aux.mail);
        printf("\nDesea agregar peliculas favoritas? (s)(n) ");
        fflush(stdin);
        while(getch()=='s' && i !=49)
        {

            printf("\nIngrese id: ");
            scanf("%d", &aux.miLista[i]);
            i++;
            printf("\nDesea seguir ingresando: (s)(n) ");
            fflush(stdin);
        }
        if (i==49)
            printf("\nAlncanzaste el maximo de peliculas admitidas ");
        aux.miLista[i]=-1;
        aux.estado=1;
        fwrite(&aux, sizeof(Usuario), 1, arch);
        printf("\nUsuario creado con exito! \n");

    }
    else
    {
        printf("\nError: Usuario existente\n");
    }
    fclose(arch);
    return i;
}

void imprimirMilista(Usuario aux)
{
    int i=0;
    if (aux.miLista[i]!=-1)
        while(aux.miLista[i]!=-1)
        {
            printf("[%d] ", aux.miLista[i]);
            i++;
        }
    else

        printf("       No posee");
}

void listarUsuarios(char archivoUsuarios[])
{
    FILE *arch = fopen(archivoUsuarios,"rb");

    if(arch)
    {
        Usuario aux;
        while(fread(&aux,sizeof(Usuario),1,arch) >0)
        {
            mostrarUsuario(aux);
        }
        fclose(arch);
    }
    else
    {
        printf("\nError en archivo\n");
    }
}

void mostrarUsuario(Usuario aux)
{

    printf("\n--------------------------------------");
    printf("\n         id: %d", aux.id);
    printf("\n     Nombre: %s", aux.nombre);
    printf("\n       Mail: %s", aux.mail);
    printf("\n    Celular: %s", aux.celular);
    printf("\n Contraseña: %s", aux.contrasenia);

    if (aux.tipodeusuario==1)
    {
        printf("\nTipo de usuario: [admin]");
    }
    if (aux.tipodeusuario==0)
    {
        printf("\nTipo de usuario: [normal]");
    }
    printf("\nLista id's favoritas: \n");
    imprimirMilista(aux);
    if(aux.estado == 1)
        printf("\n     Estado: Activo");
    else
        printf("\n     Estado: Inactivo");
    printf("\n--------------------------------------");
    printf("\n");
}

void listarMilista(char archivoUsuarios[], Usuario aux, char archivoPeliculas[])
{
    int i=0;
    if (aux.miLista[i]!=-1)
        while(aux.miLista[i]!=-1)
        {
            listarPeliculaid(archivoPeliculas, aux.miLista[i]);
            i++;
        }
    else
        printf("\nNo posee películas favoritas ");
}

void modificarUsuario(char archivoUsuarios[], int idUsuario)
{
    FILE *arch;
    arch=fopen(archivoUsuarios,"r+b");
    if (arch==NULL)
        exit(1);

    Usuario aux;
    int flag=0;
    fread(&aux, sizeof(Usuario), 1, arch);
    while(!feof(arch))
    {
        if (aux.id==idUsuario)
        {
            mostrarUsuario(aux);

            printf("\nDesea editar el nombre: (s)i (n)o ");
            if (tolower(getch())=='s')
            {
                printf("\nIngrese el nombre: ");
                fflush(stdin);
                while (buscarNombreUsuario(archivoUsuarios, gets(aux.nombre)) ==1)
                {
                    printf("\nError: Ingrese el nombre nuevamente: ");
                    fflush(stdin);
                }
            }
            printf("\nDesea editar la contraseña: (s)i (n)o ");
            if (tolower(getch())=='s')
            {
                printf("\nIngrese contraseña: ");
                fflush(stdin);
                gets(aux.contrasenia);
            }
            printf("\nDesea editar el teléfono: (s)i (n)o ");
            if (tolower(getch())=='s')
            {


                printf("\nIngrese teléfono: ");
                fflush(stdin);
                gets(aux.celular);
            }
            printf("\nDesea editar el mail: (s)i (n)o ");
            if (tolower(getch())=='s')
            {


                printf("\nIngrese mail: ");
                fflush(stdin);
                gets(aux.mail);
            }

            int pos=ftell(arch)-sizeof(Usuario);
            fseek(arch,pos,SEEK_SET);
            fwrite(&aux, sizeof(Usuario), 1, arch);
            printf("\n> Usuario editado correctamente\n");
            flag=1;
            break;
        }
        fread(&aux, sizeof(Usuario), 1, arch);
    }
    if (flag==0)
        printf("\nError: Id no encontrado! \n");
    fclose(arch);
}

void bajaUsuario(char archivoUsuarios[], int idUsuario)
{
    FILE *arch;
    arch=fopen(archivoUsuarios,"r+b");
    if (arch==NULL)
        exit(1);

    Usuario aux;
    int flag=0;
    fread(&aux, sizeof(Usuario), 1, arch);
    while(!feof(arch))
    {
        if (aux.id==idUsuario)
        {
            mostrarUsuario(aux);
            printf("\nEstado anterior: < %d >\n", aux.estado);

            if (aux.estado == 1)
                aux.estado=0;
            else
                aux.estado=1;
            printf("Estado actual: < %d >\n", aux.estado);
            int pos=ftell(arch)-sizeof(Usuario);
            fseek(arch,pos,SEEK_SET);
            fwrite(&aux, sizeof(Usuario), 1, arch);
            printf("\nUsuario correctamente modificado! \n");
            flag=1;

            break;
        }
        fread(&aux, sizeof(Usuario), 1, arch);
    }
    if (flag==0)
        printf("\nId no encontrado! \n");
    fclose(arch);
}

Usuario buscarUsuarioPorId(char archivoUsuarios[], int userId)
{
    FILE *file = fopen(archivoUsuarios, "rb");
    Usuario aux;
    if(file)
    {
        while(fread(&aux, sizeof(Usuario), 1, file)>0)
        {
            if(aux.id == userId)
                break;
        }
        if(fclose(file) != 0)
            printf("\n Error al cerrar el archivo");
    }
    return aux;
}

void eliminarDatoArreglo(int arreglo[], int dato)
{
    int i=0;
    int flag = 0;
    while(arreglo[i] != -1)
    {
        if(arreglo[i] == dato || flag)
        {
            flag = 1;
            arreglo[i] = arreglo[i+1];
        }
        i++;
    }
    arreglo[i-1] = -1;
}

void actualizarUsuario(char archivoUsuarios[], Usuario usuario)
{
    FILE *file = fopen(archivoUsuarios, "r+b");
    if(file)
    {
        Usuario aux;
        while(fread(&aux, sizeof(Usuario), 1, file)>0)
        {
            if(aux.id == usuario.id)
            {
                fseek(file, -sizeof(Usuario), SEEK_CUR);
                fwrite(&usuario, sizeof(Usuario), 1, file);
                break;
            }
        }
        if(fclose(file) != 0)
            printf("\nError al cerrar el archivo");
    }
    else
        printf("\nError al abrir el archivo");
}

void eliminarPeliculaLista(char archivoUsuarios[], char archivoPelicula[], int userId)
{
    Usuario usuario = buscarUsuarioPorId(archivoUsuarios, userId);

    imprimirPeliculasMilista(archivoPelicula, archivoUsuarios, usuario.id);

    char nombrePeliculaEliminar[30];
    printf("\nIngrese el nombre de la película a eliminar de Mi Lista: ");
    fflush(stdin);
    gets(nombrePeliculaEliminar);
    int idEliminar = nombrexid(archivoPelicula, nombrePeliculaEliminar);
    if(idEliminar!=-1)
    {
        eliminarDatoArreglo(usuario.miLista, idEliminar);
        actualizarUsuario(archivoUsuarios, usuario);
    }
    else
    {
        printf("\nLa pelicula que ingreso es incorrecta!");
        system("pause");
    }
}
