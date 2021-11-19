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

void peliculas(Usuario aux)
{
    char archivoUsuarios[]= {"usuarios.dat"};
    char archivoPeliculas[]= {"peliculas.dat"};

    char buscarPeli[30];
    int buscarId=0;
    char buscarGenero[30];
    int currentId=aux.id;

    int dimension=50;
    Pelicula pelis[dimension];
    int validos=peliToArreglo(archivoPeliculas,pelis);

    int opcion;
    do
    {
        logo();
        printf("\n                         Panel de usuario ");
        printf("\n");
        printf("\n (1) - Listar películas ");
        printf("\n (2) - Buscar por nombre ");
        printf("\n (3) - Buscar por id ");
        printf("\n (4) - Buscar por género ");
        printf("\n (5) - Listar películas alfabeticamente ");
        printf("\n (6) - Listar películas por año ");
        printf("\n");
        printf("\n                         Mi lista ");
        printf("\n (7) - Ver Mi lista ");
        printf("\n (8) - Cargar Mi lista ");
        printf("\n (9) - Películas recomendadas ");
        printf("\n (10) - Eliminar de Mi lista ");
        printf("\n");
        printf("\n (11) - Cerrar sesión ");
        printf("\n");
        printf("\n Opcion: ");
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
            listarPeliculas(archivoPeliculas);
            system("pause");
            break;

        case 2:
            printf("\nIngrese nombre a buscar: \n");
            fflush(stdin);
            gets(&buscarPeli);
            if (buscarPeliculaNombre(archivoPeliculas, buscarPeli) == 0)
                printf("\nPelícula no encontrada!\n");
            system("pause");
            break;

        case 3:
            printf("\nIngrese id a buscar: \n");
            fflush(stdin);
            scanf("%d", &buscarId);
            if (buscarPeliculaId(archivoPeliculas, buscarId)==0)
                printf("\nPelícula no encontrada!\n");
            system("pause");
            break;

        case 4:
            printf("\nIngrese género a buscar: \n");
            fflush(stdin);
            gets(&buscarGenero);
            listarPeliculasGenero(archivoPeliculas, buscarGenero);
            system("pause");
            break;

        case 5:
            mostrarPelicOrdenadasNombre(archivoPeliculas);
            system("pause");
            break;

        case 6:

            PeliculasArregloOrdenarSeleccion(pelis,validos);
            arregloStrucMostrar(pelis,validos);
            system("pause");
            break;

        case 7:
            imprimirPeliculasMilista(archivoPeliculas, archivoUsuarios, currentId);

            system("pause");
            break;

        case 8:
            cargarMilista(archivoUsuarios, archivoPeliculas, currentId);
            system("pause");
            break;

        case 9:
            recomendarPelis(archivoUsuarios, archivoPeliculas, currentId);
            system("pause");
            break;

        case 10:
            eliminarPeliculaLista(archivoUsuarios, archivoPeliculas, currentId);
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

void recomendarPelis(char archivoUsuarios[], char archivoPeliculas[], int idUsuario)
{
    int arregloMiLista[50];
    int validosArreglo=archivoToArreglo(archivoUsuarios,arregloMiLista,idUsuario);
    char generoRecomendado[15];

    contarGenerosArreglo(arregloMiLista,validosArreglo,archivoPeliculas,idUsuario,&generoRecomendado);
    listarPeliculasGenero(archivoPeliculas,generoRecomendado);
}

void contarGenerosArreglo(int A[],int validos,char archivoPeliculas[], int idUsuario,char *generoRecomendado)
{
    char dato[15];
    int accion=0;
    int comedia=0;
    int drama=0;
    int romantica=0;
    int suspenso=0;
    int terror=0;

    for(int i=0; i<validos; i++)
    {
        if(A[i]>0)
        {
            mostrarGeneroPorId(archivoPeliculas,A[i],&dato);

            if(strcmpi(dato,"Accion")==0)
            {
                accion++;
            }
            else if(strcmpi(dato,"Comedia")==0)
            {
                comedia++;
            }
            else if(strcmpi(dato,"Drama")==0)
            {
                drama++;
            }
            else if(strcmpi(dato,"Romantica")==0)
            {
                romantica++;
            }
            else if(strcmpi(dato,"suspenso")==0)
            {
                suspenso++;
            }
            else
            {
                terror++;
            }
        }
    }

    if(accion>=comedia && accion>=drama && accion>=romantica && accion>=suspenso && accion>=terror)
    {
        strcpy(generoRecomendado,"Accion");
    }
    else if(comedia>=accion && comedia>=drama && comedia>=romantica && comedia>=suspenso && comedia>=terror)
    {
        strcpy(generoRecomendado,"Comedia");
    }
    else if(drama>=accion && drama>=comedia && drama>=romantica && drama>=suspenso && drama>=terror)
    {
        strcpy(generoRecomendado,"Drama");
    }
    else if(romantica>=accion && romantica>=comedia && romantica>=drama && romantica>=suspenso && romantica>=terror)
    {
        strcpy(generoRecomendado,"Romantica");
    }
    else if(suspenso>=accion && suspenso>=comedia && suspenso>=drama && suspenso>=romantica && suspenso>=terror)
    {
        strcpy(generoRecomendado,"Suspenso");
    }
    else
    {
        strcpy(generoRecomendado,"Terror");
    }
}

void mostrarGeneroPorId (char archivoPeliculas[], int id,char *dato)
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;
    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (aux.idPelicula==id)
            {
                strcpy(dato,aux.genero);
            }
        }
        fclose(arch);
    }
}

int archivoToArreglo(char archivoUsuarios[],int A[], int userid)
{
    FILE * arch;
    arch=fopen(archivoUsuarios, "rb");
    Usuario aux;
    int flag=0, i=0;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Usuario), 1, arch)>0 && !flag)
        {
            if (aux.id == userid)
            {
                if (aux.miLista[i]!=-1)
                    while(aux.miLista[i]!=-1)
                    {
                        A[i]=aux.miLista[i];
                        i++;
                    }
                else
                    printf("       No posee");
                flag=1;
            }
        }
        fclose(arch);
    }
    if (flag==0)
    {
        printf("\nError: Película no encontrada ");
    }
    return i;
}

void arregloMostrar(int A[],int validos)
{
    for(int i=0; i<validos; i++)
    {
        printf("%i ",A[i]);
    }
}

void cargarMilista(char archivoUsuarios[], char archivoPeliculas[], int idUsuario)
{

    listarPeliculas(archivoPeliculas); // abre listar peliculas asi se ven en el momento de cargar
    Usuario aux=buscarUsuarioPorId(archivoUsuarios, idUsuario);
    char nombrePeli[30];
    int i = 0;
    while (aux.miLista[i]!=-1)
        i++;
    do
    {
        printf("\nIngrese el nombre de la película para agregar a Mi Lista: ");
        fflush(stdin);
        gets(nombrePeli);
        int idPelicula=nombrexid(archivoPeliculas, nombrePeli);
        if(!existeIdArreglo(aux.miLista, idPelicula))
        {
            if(idPelicula!=-1)
            {
                aux.miLista[i]=idPelicula;
                i++;
            }
        }
        else
            printf("\nLa película ya esta en Mi Lista ");
        fflush(stdin);
        printf("\nDesea seguir ingresando: (s)(n) ");
    }
    while(getch()=='s' && i !=49);

    if (i==49)
        printf("\nAlncanzaste el maximo de peliculas admitidas ");
    aux.miLista[i]=-1;
    actualizarUsuario(archivoUsuarios, aux);
}

int existeIdArreglo(int peliculas[], int idBuscar)
{
    int flag=0, i=0;

    while(peliculas[i] != -1 && !flag)
    {
        if (peliculas[i]==idBuscar)
            flag++;
        i++;
    }
    return flag;
}

void imprimirPeliculasMilista(char archivoPeliculas[], char archivoUsuarios[], int userid)
{
    FILE * arch;
    arch=fopen(archivoUsuarios, "rb");
    Usuario aux;
    int flag=0, i=0;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Usuario), 1, arch)>0 && !flag)
        {
            if (aux.id == userid)
            {
                if (aux.miLista[i]!=-1)
                    while(aux.miLista[i]!=-1)
                    {
                        listarPeliculaid(archivoPeliculas, aux.miLista[i]);
                        i++;
                    }
                else
                    printf("\nNo posee canciones agregadas en la lista\n");
                flag=1;
            }
        }
        fclose(arch);
    }
    if (flag==0)
    {
        printf("\nError: Película no encontrada ");
    }

    printf("Total de peliculas en Mi Lista: %i\n",i);

}

int nombrexid(char archivoPelicula[], char nombrePelicula[])
{
    FILE * arch;
    arch=fopen(archivoPelicula, "rb");
    Pelicula aux;
    int id=-1, flag =0;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (strcmpi(aux.nombre, nombrePelicula)==0 && aux.estado==1 && flag==0)
            {
                id=aux.idPelicula;
                printf("\nPelicula encontrada, id = [%d] ", id);
                flag++;
            }
        }
        fclose(arch);
    }
    if (id==-1)
        printf("\nError: Película no encontrada ");
    return id;
}

int contarPeliculas (char archivoPeliculas[])
{
    int registros;
    FILE*arch;
    arch=fopen(archivoPeliculas, "rb");

    if (arch !=NULL)
    {
        fseek(arch,0,SEEK_END);
        registros= ftell(arch)/sizeof(Pelicula);

        fclose(arch);
    }
    return registros;
}

void cargarPelicula(char archivoPeliculas[])
{
    FILE *arch;
    arch=fopen(archivoPeliculas,"ab");
    if (arch==NULL)
        exit(1);
    Pelicula aux;

    aux.idPelicula=contarPeliculas(archivoPeliculas)+1;
    printf("\tCargando pelicula... ");
    printf("\nIngrese el nombre: ");
    fflush(stdin);
    if (buscarPeliculaNombre(archivoPeliculas, gets(aux.nombre)) ==0)
    {
        printf("\nAño: ");
        scanf("%d", &aux.anio);
        while (aux.anio > 2021 || aux.anio<1900)
        {

            printf("\nIngrese nuevamente: ");
            scanf("%d", &aux.anio);
        }

        printf("\nIngrese género:\n");
        printf("\n1 - Acción");
        printf("\n2 - Comedia");
        printf("\n3 - Drama");
        printf("\n4 - Romantica");
        printf("\n5 - Suspenso");
        printf("\n6 - Terror\n");
        int opcionGenero=0;
        scanf("%i", &opcionGenero);

        while (opcionGenero > 6)
        {
            printf("\nIngrese nuevamente: ");
            scanf("%i", &opcionGenero);
        }
        switch(opcionGenero)
        {
        case 1:
            strcpy(aux.genero, "Acción");
            break;
        case 2:
            strcpy(aux.genero, "Comedia");
            break;
        case 3:
            strcpy(aux.genero, "Drama");
            break;
        case 4:
            strcpy(aux.genero, "Romantica");
            break;
        case 5:
            strcpy(aux.genero, "Suspenso");
            break;
        case 6:
            strcpy(aux.genero, "Terror");
            break;
        }
        printf("\nIngrese actor 1: ");
        fflush(stdin);
        gets(aux.actores[0]);
        printf("\nIngrese actor 2: ");
        fflush(stdin);
        gets(aux.actores[1]);
        printf("\nIngrese actor 3: ");
        fflush(stdin);
        gets(aux.actores[2]);
        printf("\nIngrese calificación: (1 a 5)");
        scanf("%d", &aux.calificacion);

        while (aux.calificacion>5 || aux.calificacion<1)
        {
            printf("\nIngrese nuevamente: ");
            scanf("%d", &aux.calificacion);
        }
        aux.estado=1;
        fwrite(&aux, sizeof(Pelicula), 1, arch);
    }
    else
    {
        printf("\nPelícula ya ingresada!\n");
    }
    fclose(arch);
}

void listarPeliculas (char archivoPeliculas[])
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (aux.estado==1)
                mostrarPelicula(aux);
        }
        fclose(arch);
    }
    printf("\n\n");
}

void listarPeliculasGenero (char archivoPeliculas[], char genero[])
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (strcmpi(aux.genero, genero)==0 && aux.estado==1)
                mostrarPelicula(aux);
        }
        fclose(arch);
    }
    printf("\n\n");
}

void listarPeliculaid (char archivoPeliculas[], int id)
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (aux.idPelicula==id)
            {
                mostrarPelicula(aux);
            }

        }
        fclose(arch);
    }
    printf("\n\n");
}

void mostrarPelicula(Pelicula aux)
{
    printf("\n--------------------------------------");
    printf("\n         id: %d", aux.idPelicula);
    printf("\n     Nombre: %s", aux.nombre);
    printf("\n        Año: %d", aux.anio);
    printf("\n     Género: %s", aux.genero);
    printf("\n    Actor 1: %s", aux.actores[0]);
    printf("\n    Actor 2: %s", aux.actores[1]);
    printf("\n    Actor 3: %s", aux.actores[2]);
    printf("\n     Calif.: %d estrellas", aux.calificacion);
    printf("\n--------------------------------------");
    printf("\n");
}

void bajaPelicula(char archivoPeliculas[], int idPelicula)
{
    FILE *arch;
    arch=fopen(archivoPeliculas,"r+b");
    if (arch==NULL)
        exit(1);

    Pelicula aux;
    int flag=0;
    fread(&aux, sizeof(Pelicula), 1, arch);
    while(!feof(arch))
    {
        if (aux.idPelicula==idPelicula)
        {
            mostrarPelicula(aux);
            printf("\nEstado actual: < %d >\n", aux.estado);
            printf("\nIngrese nuevo estado: (0) inactiva (1) activa\n");
            scanf("%d",&aux.estado);
            int pos=ftell(arch)-sizeof(Pelicula);
            fseek(arch,pos,SEEK_SET);
            fwrite(&aux, sizeof(Pelicula), 1, arch);
            printf("\nEstado correctamente modificado!\n");
            flag=1;
            break;
        }
        fread(&aux, sizeof(Pelicula), 1, arch);
    }
    if (flag==0)
        printf("\nId no encontrado! \n");
    fclose(arch);
}

int buscarPeliculaNombre(char archivoPeliculas[], char nombrePelicula[])
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;
    int flag = 0;
    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (strcmpi(aux.nombre, nombrePelicula)==0 && aux.estado==1)
            {
                flag=1;
                mostrarPelicula(aux);
            }

        }
        fclose(arch);
    }
    return flag;
}

int buscarPeliculaId(char archivoPeliculas[], int id)
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;
    int flag = 0;
    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (aux.idPelicula==id && aux.estado==1)
            {
                flag=1;
                mostrarPelicula(aux);
            }

        }
        fclose(arch);
    }
    return flag;
}

int insertarPeliculaArreglo(Pelicula arreglo[], int validos, Pelicula nueva)
{
    int i = validos-1;
    while (i>=0 && strcmpi(arreglo[i].nombre,nueva.nombre)>0)
    {
        arreglo[i+1]=arreglo[i];
        i--;
    }
    arreglo[i+1]=nueva;
    return validos + 1;
}

void mostrarPelicOrdenadasNombre(char archivoPeliculas[])
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;
    Pelicula peliculas[50];
    int peliculasValidos=0;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (aux.estado==1)
            {
                peliculasValidos=insertarPeliculaArreglo(peliculas, peliculasValidos, aux);
            }
        }
        fclose(arch);
    }
    for (int i = 0 ; i < peliculasValidos ; i++)
        mostrarPelicula(peliculas[i]);
}

void listarPeliculasAdmin (char archivoPeliculas[])
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            mostrarPeliculaAdministrador(aux);
        }
        fclose(arch);
    }
}

void listarPeliculasBajaAdmin(char archivoPeliculas[])
{
    FILE * arch;
    arch=fopen(archivoPeliculas, "rb");
    Pelicula aux;

    if (arch!=NULL)
    {
        while (fread(&aux, sizeof(Pelicula), 1, arch)>0)
        {
            if (aux.estado==0)
                mostrarPeliculaAdministrador(aux);
        }
        fclose(arch);
    }
}

void mostrarPeliculaAdministrador(Pelicula aux)
{
    printf("\n--------------------------------------");
    printf("\n         id: %d", aux.idPelicula);
    printf("\n     Nombre: %s", aux.nombre);
    printf("\n        Año: %d", aux.anio);
    printf("\n     Género: %s", aux.genero);
    printf("\n    Actor 1: %s", aux.actores[0]);
    printf("\n    Actor 2: %s", aux.actores[1]);
    printf("\n    Actor 3: %s", aux.actores[2]);
    if(aux.estado == 1)
        printf("\n     Estado: [Activo]");
    else
        printf("\n     Estado: [Inactivo]");
    printf("\n     Calif.: %d estrellas", aux.calificacion);
    printf("\n--------------------------------------");
    printf("\n");
}

//mostrar ARREGLO de estructuras
void arregloStrucMostrar(Pelicula pelis[],int validos)
{
    for(int i=0; i<validos; i++)
    {
        mostrarPelicula(pelis[i]);
    }
}


//pos mayor
int arregloPosMenor(Pelicula pelis[],int validos,int pos)
{
    Pelicula menor=pelis[pos];
    int posMenor=pos;
    int i=pos;
    for(i; i<validos; i++)
    {
        if(pelis[i].anio > menor.anio)
        {
            menor=pelis[i];
            posMenor=i;
        }
    }
    return posMenor;
}

//ordenar por seleccion
void PeliculasArregloOrdenarSeleccion(Pelicula pelis[],int validos)
{
    Pelicula aux;
    int posMenor=0;
    int i=0;
    for(i; i<validos-1; i++)
    {
        posMenor=arregloPosMenor(pelis,validos,i);
        aux=pelis[i];
        pelis[i]=pelis[posMenor];
        pelis[posMenor]=aux;
    }
}

//pasar TODO archivo a ARREGLO
int peliToArreglo(char fileName[], Pelicula pelis[])
{

    FILE *arch=fopen(fileName,"rb");
    int i=-1;
    if(arch)
    {
        Pelicula estructura;
        i=0;
        while(fread(&estructura,sizeof(Pelicula),1,arch)>0)
        {

//         if(estructura.legajo>2){ //ejemplo de condicion para no pasar TODO
            pelis[i]=estructura;
            i++;
//         }
        }
        fclose(arch);
    }
    else
    {
        printf("ERROR!\n");
    }
    return i;
}
