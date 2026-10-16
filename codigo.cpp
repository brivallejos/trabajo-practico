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
}t_entrada;

//declaramos funciones para usar segun lo que elija el usuario(menu)
t_entrada cargarEntrada();
void ejecutarMenu();
void agregarRegistro();
void listarTodo();
void listarPorCondicion();
void buscarPorNombre();
void dividrArchivoBool();
void salir();

//funcion para carga de datos
t_entrada cargarEntrada()
{
    t_entrada entrada; // porq es lo q devuelve la funcion dsp
    int estaPagada;

    printf("nombre del evento: ");
    fflush(stdin); // limpio buffer antes d recibir
    gets(entrada.nombreEvento);

    do{
        printf("sector V= vip, G=general");
        fflush(stdin);
        scanf("%c", &entrada.sector);
        entrada.sector = toupper(entrada.sector); // para q no distinga entre mayusculas y minus
        if (entrada.sector!='V' && entrada.sector!='G'){ // if para q avise
            printf("solo escriba G o V, ninguna otra es aceptada");
        }
    }while (entrada.sector!='V' && entrada.sector!='G'); //bucle para validacion

printf("num assiento: ");
    scanf("%d", &entrada.numAsiento);

printf("precio: ");
scanf("%f", &entrada.precio);

printf("esta pagada? (1= si, 0=no)");
scanf("%d", &estaPagada);

if (estaPagada==1)
{
    entrada.estaPagada=true;
}else if (estaPagada==0)
{
    entrada.estaPagada=false;
}else{
    entrada.estaPagada=false; // para que no acepte cualquier numero como true
}
return entrada;
}

void ejecutarMenu()
{
    int opcion;
    do
    {
        printf("menu de opciones:\n");
        printf("1. agregar un registro al archivo\n");
        printf("2. por pantalla todo el archivo\n");
        printf("3. listar solo entradas VIP\n"); //listamos condicion: VIP
        printf("4. busqueda especifica segun nombre de evento\n");
        printf("5. dividir informacion en dos archivos de texto (pagadas y no pagadas\n");
        printf("6. salir del sistema\n");
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
        }// del switch
    }while (opcion!=6);
}// de la funcion

//aca ptrimero va la funcion de agregarRegistro
void agregarRegistro()
{
    FILE* archivo; //declaro el puntero para manejar elarchivo
    archivo=fopen("entrada.txt","a"); //para q abra el archivo y la  a es para agregar/append, o es .dat(?
    if (archivo==NULL)
    {
        printf("error, se abrio mal el archivo");
    }else
    {
        // si no hay error !=NULL, piod los datos
        t_entrada leoRegistro = cargarEntrada(); // es la estructura y la variable q cree para leer registro por registro y la funcionpara carfgar
        fprintf(archivo, "%s %c %d %.2f %d\n",
            nuevoRegistro.nombreEvento,// aca guardamos uno por uno separados por un espacio, es para guardar la info para q no se pierda ciuando se cierra elprograma sino q se escriba en el archivo
            nuevoRegistro.sector,
            nuevoRegistro.numAsiento,
            nuevoRegistro.precio,
            nuevoRegistro.estaPagada);

        fclose(archivo);
    }
}

void listarTodo()
{
    FILE* archivo;
    t_entrada leoRegistro; // creo una nueva variable para leer cada registro
    archivo=fopen("entrada.txt","r"); //abrimos el archivo d txt y r porq es para lectura
    if (archivo==NULL) //compruebo asi siempre si hubo algun errror
    {
        printf("error, se abrio mal el archivo");
    }else if (archivo!=NULL)
    {
        while (fread(&leoRegistro, sizeof(t_entrada), 1, archivo)==1){// mientras fread pueda leer 1 registro lo imprime
        printf("Evento: %s, Sector: %c, Asiento: %d, Precio: %f,Pagada? %d\n",
                           leoRegistro.nombreEvento, leoRegistro.sector, leoRegistro.numAsiento, leoRegistro.precio, leoRegistro.estaPagada);
    }
fclose(archivo); //siempre cerrar el archivo si esq lo abrimos
}
}

void listarPorCondicion() // void porq no devuelve nada dsp
{
    FILE* archivo; //puntero FILE para manejar el archivo
    t_entrada leoRegistro;
    int contador=0;
    archivo=fopen("entrada.txt","r");
    if (archivo==NULL)
    {
        printf("error, se abrio mal el archivo");
    }
    else
    {
while (fread(&LeoRegistro, sizeof(t_entrada), 1, archivo)==1)
{
    if (LeoRegistro.sector == V)
    {
        printf("Evento: %s, Asiento: %d, Precio: %.2f\n", leoRegistro.nombreEvento, leoRegistro.numAsiento, leoRegistro.precio);
        contador++;
    }else if (contador==0){
        printf("No se encontraron entradas VIP");
    }
}
        fclose(archivo);
    }
}//funcion
void buscarPorNombre()
{
    FILE* archivo;
    t_entrada leoRegistro;
    int encontrado=0; //inicio el contador en c
    char buscar[50]; //arreglo para guarda rel nombre del evento

    printf("Ingrese el nombre del evento a buscar:");
    fflush(stdin);
    gets(buscar);//no m convence esto

    archivo=fopen("entrada.txt","r");//eswto tampoco, chat mdice q esto tendria q ser dat
    if (archivo==NULL)
    {
        printf("error, se abrio mal el archivo");
    }
    else
    {
        while (fread(&leoRegistro, sizeof(t_entrada), 1, archivo) == 1)
        {
            if (strcasecmp(leoRegistro.nombreEvento, buscar) == 0)
            {
                printf("Evento: %s, Sector: %c, Asiento: %d, Pagada: %d\n", leoRegistro.nombreEvento, leoRegistro.sector, leoRegistro.numAsiento, leoRegistro.estaPagada);
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



//aca falta una funcin antes
void salir()
{
    printf("elegiste la opcion para salri del sietma");
}
int main(){
    ejecutarMenu();
   return 0;
}
