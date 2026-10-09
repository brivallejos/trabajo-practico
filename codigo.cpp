#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct
{
    char nombreEvento[50];
    char sector;
    int numAsiento;
    float precio;
    bool estaPagada;
}t_entrada;

//funcion para carga de datos
t_entrada cargarEntrada()
{
    t_entrada entrada; // porq es lo q devuelve la funcion dsp
    int estaPagada;

    printf("nombre del evento: ");
    fflush(stdin); // limpio buffer antes d recibir
    gets(entrada.nombreEvento);

    printf("sector V= vip, G=general");
fflush(stdin);
    scanf("%c", &entrada.sector);

printf("num assiento: ");
    scanf("%d", &entrada.numAsiento);

printf("precio: ");
scanf("%f", &entrada.precio);

printf("esta pagada? (1= si, 0=no)");
scanf("%d", &estaPagada);

if (estaPagada==1)
{
    entrada.estaPagada=true;
}else
{
    entrada.estaPagada=false;
}
return entrada;
}
int main(){
    t_entrada entrada;
    entrada = cargarEntrada();
   return 0;
}