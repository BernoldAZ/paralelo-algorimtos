#include <stdio.h>
#include <string.h>

#include "omp.h"
#include "uthash.h"


//************************************************************************************************
//elementos de la hash table
struct node {
    char id[6];            /* we'll use this field as the key */
    char siguientes[10];
    char peso[20];
    UT_hash_handle hh; /* makes this structure hashable */
};

//Declaracion del puntero a la hash table
struct node *users = NULL;


//funcion que permite agregar nodos a la hash table
void add_user(struct node *s) {
    HASH_ADD_INT( users, id, s );
}

//funcion que permite buscar nodos en la hash table
struct node *find_user(int user_id) {
    struct node *s;

    HASH_FIND_INT( users, &user_id, s );
    return s;
}

//funcion que permite eliminar nodos en la hash table
void delete_user(struct node *user) {
    HASH_DEL( users, user);
}

//************************************************************************************************
//elementos que leen archivos


void readFile(){
    FILE *archivo;

    char caracteres[100];

    archivo = fopen("C:/Users/usuario/Desktop/TEC/algoritmos/Tarea/Pruebas/Paralelo/graph_info.txt","r"); //Aqui ponen donde ustedes lo tienen guardado

    if (archivo == NULL)
        exit(1);
    else
    {
        while (feof(archivo) == 0)
        {
            fgets(caracteres,100,archivo);

            printf("%s",&caracteres);

        }
    }
    fclose(archivo);
}



int main() {


    readFile();
    #pragma omp parallel
    {
        printf("\nHello, World!\n");
    }
    printf("Exit!\n");
    return 0;
}