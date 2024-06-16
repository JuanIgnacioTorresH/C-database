#include <stdio.h>
#include <string.h>

// DECLARACION DE VARIABLES GLOBALES

// Variable numero de estanterias (input)
int num_estant;

//Inicialización de base de datos
char base_de_datos [num_estant][6][4][15];
int opcion;

// Variables declaradas para la funcion de agregar estanterias
int categ_estant;
char letra_estant[1];
int indice_estant_agreg;
indice_estant_agreg = 0;

// Variables declaradas para la funcion de agregar paquetes
int indice_paquete;
int paquete_full;
int paquete_fecha;
int paquete_nombre;
int paquete_categ;

// Variables declaradas para la funcion de eliminar estanterias
int indice_estant_elim;

// Variables declaradas para la funcion de eliminar paquetes
int indice_paquete_elim;
int indice_paquete_estant_elim;

// Variables declaradas para porcentaje
int porcent;

// Contadores
int a, b, c;

// FUNCIONES (modos del menu)
int agregar_estanteria() {
    // Pido dos valores de indentificacion el estanteria que van en el indice 0 y le asigno un valor a los restantes
    // Notar que el máximo de caracteres posibles a escribir por string es 15
    printf("Ingrese letra asignada de la estantería");
    gets(letra_estant);
    printf("Ingrese categoría de la estanteria");
    gets(categ_estant);

    strcpy(base_de_datos[indice_estant_agreg][0][0], letra_estant );
    strcpy(base_de_datos[indice_estant_agreg][0][1], categ_estant );
    strcpy(base_de_datos[indice_estant_agreg][0][2], "-" );
    strcpy(base_de_datos[indice_estant_agreg][0][3], "-" );
}

int agregar_paquete(int full){
    // Notar que el máximo de caracteres posibles a escribir por string es 15
    // Main pasa el valor de base_full de la estanteria que me pide el usuario y se fija si esta llena
    if (full >= 5) {
        printf("Ya no hay espacio para almacenar mas paquetes en esta estanteria");
    }
    else {
        //Si no esta lleno, pide cada categoria y rellena cada seccion del paquete
        printf("Ingrese categoría");
        gets(paquete_categ);
        strcopy(base_de_datos[indice_paquete][full][0], paquete_categ);
        printf("Ingrese nombre");
        gets(paquete_nombre);
        strcopy(base_de_datos[indice_paquete][full][1], paquete_nombre);
        printf("Ingrese fecha de caducidad");
        gets(paquete_fecha);
        strcopy(base_de_datos[indice_paquete][full][2], paquete_fecha);
    }
}

int eliminar_estanteria() {
    // Para eliminar, le pide el indice de estanteria y copia todas las estanterias un indice para atras
    printf("Ingrese el indice de la estanteria a eliminar (Puede comprobar indices en listado)");
    scanf("%d", &indice_estant_elim);
    for (a=indice_estant_elim; a < num_estant-1; a++){
        for (b=0; b<6; b++){
            for (c=0; c<4; c++){
                strcpy(base_de_datos[indice_estant_elim][b][c], base_de_datos[indice_estant_elim+1][b][c]);
            }
        }
    }
}

int eliminar_paquete() {
    // Para eliminar un paquete, se pide la estanteria y paquete a eliminar, y se copia tanto paquetes como
    // estanterias un indice para atras
    printf("Ingrese el indice de la estanteria del paquete a eliminar (Puede comprobar indices en listado)");
    scanf("%d", &indice_paquete_estant_elim);
    printf("Ingrese el indice del paquete a eliminar (Puede comprobar indices en listado)");
    scanf("%d", &indice_paquete_elim);
    for (a=indice_paquete_elim; a<6; a++){
        for (b=0; b<4; b++){
            strcpy(base_de_datos[indice_paquete_estant_elim][indice_paquete_elim][b], base_de_datos[indice_paquete_estant_elim][indice_paquete_elim+1][b]);
        }
    }
}

int listado() {
    // Itera por toda la matriz y printea
    for (a = 0; a < indice_estant_agreg; a++) {
        printf ("---Estantería %d\n---", indice_estant_agreg);
        for (b = 0; b < 6; b++) {
            for (c = 0; c<4; c++){
                printf("%s ", base_de_datos[a][b][c]);
            }
            printf("\n");
        }
    }
}

int porcentaje(){
    // Regla de tres simples entre las estanterias que hice y las que hay en total
    porcent = (indice_estant_agreg * 100) / num_estant;
}

int main(){
    // Pide la cantidad de estanterias que usara la base de datos
    // Como hay un bucle abajo, solo es una vez
    printf ("Ingrese la cantidad de estanterias del almacen");
    scanf("%d", &num_estant);


    //Defino a cero los valores del array para el contador de si esta lleno alguna estanteria
    // Base_full cuenta la cantidad de paquetes en cada estanteria
    int base_full [num_estant];
    for (a=0; a< num_estant-1; a++){
        base_full[a] = 0;
    }
    

    //Bucle
    while (1){
        // Pide la accion que debe ejecutar y ejecuta la funcion correspondiente (ver cada funcion arriba)
        printf ("Elija 1 para agregar estanteria");
        printf ("Elija 2 para agregar paquete");
        printf ("Elija 3 para eliminar estanteria");
        printf ("Elija 4 para eliminar paquete");
        printf ("Elija 5 para listado");
        printf ("Elija 6 para porcentaje de espacio ocupado");
        scanf("%d", &opcion);
        if (opcion == 1){
            agregar_estanteria();
            // El indice de agregar estanterias cuenta cuantas estanterias se hicieron hasta el momento
            indice_estant_agreg++;
        }
        else if(opcion == 2){
            printf("Ingrese la estanteria a la que quiere agregar el paquete");
            gets(indice_paquete);
            agregar_paquete(base_full[indice_paquete]);
            // Paquete_full cuenta para saber cuando se llena un paquete
            base_full[indice_paquete]++;
        } 
        else if(opcion == 3){
            eliminar_estanteria();
            // Copie un valor hacia atras todo el array para sacar la estanteria que borre del array que trackea
            // que tan lleno esta cada estanteria
            for (a=indice_estant_elim; a> num_estant-1; a++){
                base_full[indice_estant_elim] = base_full[indice_estant_elim+1];
            }
            // Resto 1 al contador de estanterias hechas
            indice_estant_agreg--;
        }
        else if(opcion == 4){
            eliminar_paquete();
            // Resto 1 al numero de paquetes en la estanteria correspondiente
            base_full[indice_paquete_estant_elim]--;
        }
        else if(opcion == 5){
            listado();
        }
        else if(opcion == 6){
            porcentaje();
        }
        else{
            printf("Error");
        }
    }
    return 0;
}