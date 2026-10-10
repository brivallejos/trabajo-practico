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
t_entrada entrada;
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
            agregarRegistro;
            break;
        case 2:
            listarTodo;
            break;
        case 3:
            listarPorCondicion;
            break;
        case 4:
            buscarPorNombre;
            break;
        case 5:
            dividrArchivoBool;
            break;
        case 6:
            salir;
            break;
        default:
            printf("opcion no valida, solo numeros del 1 al 6\n");
            break;
        }// del switch
    }while (opcion!=6);
}// de la funcion
int main(){
    t_entrada entrada;
    entrada = cargarEntrada();
    ejecutarMenu();
   return 0;
}