#include <iostream>
#include <string>
#include <fstream>

#include "omp.h"
#include "uthash.h"

using namespace std;
//************************************************************************************************
//elementos de la hash table
struct node {
    int id_nodo;
    int peso_nodo;
    int Cantidad_Anteriores;
    int Nodos_Anteriores[10000];
    int Cantidad_Siguientes;
    int Nodos_Siguientes[10000];
};


node Array_Nodes[500];

//***************************************************************************************************
//Funciones que hacen distintas cosas pequeñas

//Toma un numero que esta en un string y lo convierte a int
int StringToInt(string pString){

    int n = std::stoi(pString);

    return n;
}




//************************************************************************************************
//elementos que leen archivos
void Obtener_Datos_Nodos (string frase){

    node Node_Actual;

    int recorrer = 0;
    string id_nodo;
    string peso_nodo;
    string Cantidad_Anteriores;
    string Cantidad_Siguientes;
    bool IsFirst; //Bandera que indica si el nodo no tiene anteriores
    bool IsLast; //Bandera que indica si el nodo no tiene siguientes

    //*********************************************************
    while(frase[recorrer] != ' '){ //da el id del nodo
        id_nodo = id_nodo + frase[recorrer];
        recorrer++;
    }
    Node_Actual.id_nodo = StringToInt(id_nodo); //Guarda el id
    if(frase[recorrer] == ' '){recorrer++;}

    //*********************************************************
    while(frase[recorrer] != ' '){ //da el peso del nodo
        peso_nodo = peso_nodo + frase[recorrer];
        recorrer++;
    }
    Node_Actual.peso_nodo = StringToInt(peso_nodo);//Guarda el peso
    if(frase[recorrer] == ' '){recorrer++;}

    //*********************************************************
    while(frase[recorrer] != ' ') { //da la cantidad de nodos anteriores del nodo
        Cantidad_Anteriores = Cantidad_Anteriores + frase[recorrer];
        recorrer++;
    }
    Node_Actual.Cantidad_Anteriores = StringToInt(Cantidad_Anteriores);
    if(frase[recorrer] == ' '){recorrer++;}

    if (Cantidad_Anteriores != "0"){ //Pregunta si tiene mas de 0 nodos anteriores
        IsFirst = false; //Altera la bandera

        int Cantidad_Nodos = StringToInt(Cantidad_Anteriores); //Nos da la cantidad de nodos que usaremos en el for

        for (int i=0; i<Cantidad_Nodos;i++ ){ //Con cada iteracion nos da uno de los nodos siguientes

            string Node_Actual_En_Lista;
            while(frase[recorrer] != ' '){ //da los nodos anteriores del nodo
                Node_Actual_En_Lista = Node_Actual_En_Lista + frase[recorrer];

                recorrer++;

            }
            Node_Actual.Nodos_Anteriores[i] = StringToInt(Node_Actual_En_Lista);
            if(frase[recorrer] == ' '){recorrer++;}

        }
    }
    else{
        IsFirst = true;
        if(frase[recorrer] == ' '){recorrer++;}
    }

    //*********************************************************
    while(frase[recorrer] != ' '){ //da la cantidad de nodos siguientes del nodo
        Cantidad_Siguientes = Cantidad_Siguientes + frase[recorrer];
        recorrer++;
    }
    Node_Actual.Cantidad_Siguientes = StringToInt(Cantidad_Siguientes);
    if(frase[recorrer] == ' '){recorrer++;}

    if (Cantidad_Siguientes != "0"){ //Pregunta si tiene mas de 0 nodos siguientes
        IsLast = false;

        int Cantidad_Nodos = StringToInt(Cantidad_Siguientes);

        for (int i=0; i<Cantidad_Nodos;i++ ){

            string Node_Actual_En_Lista;
            while(frase[recorrer] != ' '){ //da los nodos anteriores del nodo
                Node_Actual_En_Lista = Node_Actual_En_Lista + frase[recorrer];

                recorrer++;

            }
            Node_Actual.Nodos_Siguientes[i] = StringToInt(Node_Actual_En_Lista);
            if(frase[recorrer] == ' '){recorrer++;}

        }
    }
    else{
        IsLast = true;
    }


    //AGREGA EL NODO A LA HASHTABLE
    Array_Nodes[Node_Actual.id_nodo] = Node_Actual;


/*
    std::cout << find_node(StringToInt(id_nodo))->id_nodo << std::endl;
    std::cout << find_node(StringToInt(id_nodo))->peso_nodo << std::endl;
    std::cout << find_node(StringToInt(id_nodo))->Cantidad_Anteriores << std::endl;
    std::cout << find_node(StringToInt(id_nodo))->Nodos_Anteriores[0] << std::endl;
    std::cout << find_node(StringToInt(id_nodo))->Cantidad_Siguientes << std::endl;
    std::cout << find_node(StringToInt(id_nodo))->Nodos_Siguientes[0] << std::endl;

    std::cout << frase << std::endl;*/

}

void readFile(){
    std::ifstream ficheroEntrada;
    string frase;

    ficheroEntrada.open ("C:/Users/usuario/Desktop/TEC/algoritmos/Tarea/Pruebas/Paralelo/paralelo-algorimtos/test.txt");


    //va lleyendo linea por linea
    while (!ficheroEntrada.eof()){
        getline(ficheroEntrada, frase);

        #pragma omp parallel
        {
            Obtener_Datos_Nodos(frase);
        };
        //Break
    }
    std::cout << Array_Nodes[32].id_nodo << std::endl;

    
    ficheroEntrada.close();

}


int main() {

    readFile();
    #pragma omp parallel
    {

    };
    return 0;
}