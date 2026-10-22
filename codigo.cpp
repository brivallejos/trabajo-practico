#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    char nombreEvento[50]; // arreglo para cadena
    char sector;
    int numAsiento;
    float precio;
    bool estaPagada;
} t_entrada;

// declaramos funciones para usar segun lo que elija el usuario(menu)
t_entrada cargarEntrada();
void ejecutarMenu();
void agregarRegistro();
void listarTodo();
void listarPorCondicion();
void buscarPorNombre();
void dividrArchivoBool();
void salir();

// funcion para carga de datos
t_entrada cargarEntrada()
{
    t_entrada entrada; // porq es lo q devuelve la funcion dsp
    int estaPagada;

    printf("nombre del evento (sin espacios): ");
    scanf("%s", entrada.nombreEvento);

    do {
        printf("sector V= vip, G=general: ");
        scanf(" %c", &entrada.sector);
        entrada.sector = toupper(entrada.sector); // para q no distinga entre mayusculas y minus
        if (entrada.sector != 'V' && entrada.sector != 'G') { // if para q avise
            printf("solo escriba G o V, ninguna otra es aceptada\n");
        }
    } while (entrada.sector != 'V' && entrada.sector != 'G'); // bucle para validacion

    printf("num asiento: ");
    scanf("%d", &entrada.numAsiento);

    printf("precio: ");
    scanf("%f", &entrada.precio);

    printf("esta pagada? (1= si, 0=no): ");
    scanf("%d", &estaPagada);

    if (estaPagada == 1)
    {
        entrada.estaPagada = true;
    }
    else if (estaPagada == 0)
    {
        entrada.estaPagada = false;
    }
    else
    {
        entrada.estaPagada = false; // para que no acepte cualquier numero como true
    }
    return entrada;
}

void ejecutarMenu()
{
    int opcion;
    do
    {
        printf("\nmenu de opciones:\n");
        printf("1. agregar un registro al archivo\n");
        printf("2. por pantalla todo el archivo\n");
        printf("3. listar solo entradas VIP\n"); // listamos condicion: VIP
        printf("4. busqueda especifica segun nombre de evento\n");
        printf("5. dividir informacion en dos archivos de texto (pagadas y no pagadas)\n");
        printf("6. salir del sistema\n");
        printf("opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarRegistro();
            break;
        case 2:
            listarTodo();
            break;
        case 3:
            listarPorCondicion();
            break;
        case 4:
            buscarPorNombre();
            break;
        case 5:
            dividrArchivoBool();
            break;
        case 6:
            salir();
            break;
        default:
            printf("opcion no valida, solo numeros del 1 al 6\n");
            break;
        } // del switch
    } while (opcion != 6);
} // de la funcion


void agregarRegistro()
{
    FILE* archivo; // declaro el puntero para manejar el archivo
    archivo = fopen("entrada.txt", "a"); // para q abra el archivo y la a es para agregar/append en archivo de texto
    if (archivo == NULL)
    {
        printf("error, se abrio mal el archivo\n");
    }
    else
    {
        // si no hay error !=NULL, pido los datos
        t_entrada leoRegistro = cargarEntrada(); // es la estructura y la variable q cree para leer el registro y la funcion para cargar

        // aca guardamos uno por uno separados por un espacio para que se escriba en el archivo de texto
        fprintf(archivo, "%s %c %d %.2f %d\n",
                leoRegistro.nombreEvento,
                leoRegistro.sector,
                leoRegistro.numAsiento,
                leoRegistro.precio,
                leoRegistro.estaPagada ? 1 : 0);

        fclose(archivo); // siempre cerrar el archivo
    }
}

void listarTodo()
{
    FILE* archivo;
    t_entrada leoRegistro; // creo una nueva variable para leer cada registro
    int pagadaAux;
    archivo = fopen("entrada.txt", "r"); // abrimos el archivo d txt y r porq es para lectura

    if (archivo == NULL) // compruebo asi siempre si hubo algun error
    {
        printf("error, se abrio mal el archivo\n");
    }
    else
    {
        // mientras fscanf pueda leer los 5 campos formateados los imprime por pantalla
        while (fscanf(archivo, "%s %c %d %f %d",
                      leoRegistro.nombreEvento,
                      &leoRegistro.sector,
                      &leoRegistro.numAsiento,
                      &leoRegistro.precio,
                      &pagadaAux) == 5)
        {
            leoRegistro.estaPagada = (pagadaAux == 1);
            printf("Evento: %s, Sector: %c, Asiento: %d, Precio: %.2f, Pagada? %d\n",
                   leoRegistro.nombreEvento,
                   leoRegistro.sector,
                   leoRegistro.numAsiento,
                   leoRegistro.precio,
                   leoRegistro.estaPagada);
        }
        fclose(archivo); // siempre cerrar el archivo si esq lo abrimos
    }
}

void listarPorCondicion() // void porq no devuelve nada dsp
{
    FILE* archivo; // puntero FILE para manejar el archivo
    t_entrada leoRegistro;
    int pagadaAux;
    int contador = 0; // inicio el contador en 0

    archivo = fopen("entrada.txt", "r");
    if (archivo == NULL)
    {
        printf("error, se abrio mal el archivo\n");
    }
    else
    {
        while (fscanf(archivo, "%s %c %d %f %d",
                      leoRegistro.nombreEvento,
                      &leoRegistro.sector,
                      &leoRegistro.numAsiento,
                      &leoRegistro.precio,
                      &pagadaAux) == 5)
        {
            leoRegistro.estaPagada = (pagadaAux == 1);

            if (leoRegistro.sector == 'V') // verifico la condicion del sector VIP
            {
                printf("Evento: %s, Asiento: %d, Precio: %.2f\n",
                       leoRegistro.nombreEvento,
                       leoRegistro.numAsiento,
                       leoRegistro.precio);
                contador++;
            }
        }

        if (contador == 0) // al terminar de leer todo me fijo si no habia ninguno
        {
            printf("No se encontraron entradas VIP\n");
        }

        fclose(archivo);
    }
} // funcion

void buscarPorNombre()
{
    FILE* archivo;
    t_entrada leoRegistro;
    int pagadaAux;
    int encontrado = 0; // inicio la bandera/contador en 0
    char buscar[50]; // arreglo para guardar el nombre del evento

    printf("Ingrese el nombre del evento a buscar: ");
    scanf("%s", buscar);

    archivo = fopen("entrada.txt", "r"); // apertura para lectura de texto
    if (archivo == NULL)
    {
        printf("error, se abrio mal el archivo\n");
    }
    else
    {
        while (fscanf(archivo, "%s %c %d %f %d",
                      leoRegistro.nombreEvento,
                      &leoRegistro.sector,
                      &leoRegistro.numAsiento,
                      &leoRegistro.precio,
                      &pagadaAux) == 5)
        {
            leoRegistro.estaPagada = (pagadaAux == 1);

            if (strcasecmp(leoRegistro.nombreEvento, buscar) == 0) // compara ignorando mayusculas y minusculas
            {
                printf("Evento: %s, Sector: %c, Asiento: %d, Pagada: %d\n",
                       leoRegistro.nombreEvento,
                       leoRegistro.sector,
                       leoRegistro.numAsiento,
                       leoRegistro.estaPagada);
                encontrado = 1;
            }
        }

        if (encontrado == 0)
        {
            printf("No se encontro ningun evento.\n");
        }

        fclose(archivo);
    }
}

// funcion para dividir el archivo segun el campo booleano (estaPagada)
void dividrArchivoBool()
{
    FILE* archivoOrigen = fopen("entrada.txt", "r");
    FILE* archivoPagadas = fopen("pagadas.txt", "w"); // crea/sobrescribe archivo de pagadas
    FILE* archivoNoPagadas = fopen("no_pagadas.txt", "w"); // crea/sobrescribe archivo de no pagadas

    t_entrada leoRegistro;
    int pagadaAux;

    if (archivoOrigen == NULL || archivoPagadas == NULL || archivoNoPagadas == NULL)
    {
        printf("error, fallo la apertura de archivos al dividir\n");
    }
    else
    {
        while (fscanf(archivoOrigen, "%s %c %d %f %d",
                      leoRegistro.nombreEvento,
                      &leoRegistro.sector,
                      &leoRegistro.numAsiento,
                      &leoRegistro.precio,
                      &pagadaAux) == 5)
        {
            leoRegistro.estaPagada = (pagadaAux == 1);

            // segun el booleano escribe en un archivo o en el otro
            if (leoRegistro.estaPagada)
            {
                fprintf(archivoPagadas, "%s %c %d %.2f %d\n",
                        leoRegistro.nombreEvento, leoRegistro.sector,
                        leoRegistro.numAsiento, leoRegistro.precio, 1);
            }
            else
            {
                fprintf(archivoNoPagadas, "%s %c %d %.2f %d\n",
                        leoRegistro.nombreEvento, leoRegistro.sector,
                        leoRegistro.numAsiento, leoRegistro.precio, 0);
            }
        }

        printf("archivos divididos correctamente en pagadas.txt y no_pagadas.txt\n");

        fclose(archivoOrigen);
        fclose(archivoPagadas);
        fclose(archivoNoPagadas);
    }
}

void salir()
{
    printf("elegiste la opcion para salir del sistema\n");
}

int main()
{
    ejecutarMenu();
    return 0;
}
