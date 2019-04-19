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


node Array_Nodes[1000];

//***************************************************************************************************
//Funciones que hacen distintas cosas pequeñas

//Toma un numero que esta en un string y lo convierte a int
int StringToInt(string pString){

    int n = std::stoi(pString);

    return n;
}

ofstream fi;
int ultimoEnLeer=0;
int ultimo=0;
int indice=0;
//************************************************************************************************
//elementos que leen archivos
void Obtener_Datos_Nodos (string frase){

    node Node_Actual;
    frase+=' ';

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
        Cantidad_Siguientes = Cantidad_Siguientes + frase[recorrer];
        recorrer++;
    }
    Node_Actual.Cantidad_Siguientes = StringToInt(Cantidad_Siguientes);
    if(frase[recorrer] == ' '){recorrer++;}

    if (Cantidad_Siguientes != "0"){ //Pregunta si tiene mas de 0 nodos anteriores
        IsFirst = false; //Altera la bandera

        int Cantidad_Nodos = StringToInt(Cantidad_Siguientes); //Nos da la cantidad de nodos que usaremos en el for

        for (int i=0; i<Cantidad_Nodos;i++ ){ //Con cada iteracion nos da uno de los nodos siguientes

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
        IsFirst = true;
        if(frase[recorrer] == ' '){recorrer++;}
    }

    //*********************************************************
    while(frase[recorrer] != ' '){ //da la cantidad de nodos siguientes del nodo
        Cantidad_Anteriores = Cantidad_Anteriores + frase[recorrer];
        recorrer++;
    }
    Node_Actual.Cantidad_Anteriores = StringToInt(Cantidad_Anteriores);
    if(frase[recorrer] == ' '){recorrer++;}

    if (Cantidad_Anteriores != "0"){ //Pregunta si tiene mas de 0 nodos siguientes
        IsLast = false;

        int Cantidad_Nodos = StringToInt(Cantidad_Anteriores);

        for (int i=0; i<Cantidad_Nodos;i++ ){

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
        IsLast = true;
    }


    //AGREGA EL NODO A LA HASHTABLE
    Array_Nodes[ultimoEnLeer] = Node_Actual;


/*
    int cont=0;
    std::cout << "ID: " << Array_Nodes[ultimoEnLeer].id_nodo << std::endl;
    std::cout << "Peso: " << Array_Nodes[ultimoEnLeer].peso_nodo << std::endl;
    std::cout << "Cant Anteriores: " << Array_Nodes[ultimoEnLeer].Cantidad_Anteriores << std::endl;
    std::cout << "Anteriores: ";
    while(cont<Array_Nodes[ultimoEnLeer].Cantidad_Anteriores){
        std::cout << Array_Nodes[ultimoEnLeer].Nodos_Anteriores[cont];
        cont++;
    }
    cont=0;
    std::cout << "\nCant Siguientes: " << Array_Nodes[ultimoEnLeer].Cantidad_Siguientes<< std::endl;
    std::cout << "Siguientes: ";
    while(cont<Array_Nodes[ultimoEnLeer].Cantidad_Siguientes){
        cout<< Array_Nodes[ultimoEnLeer].Nodos_Siguientes[cont];
        cont++;
    }


    std::cout << "\n"<<frase << "\n\n\n"<<std::endl;
    */
    ultimoEnLeer++;


}
void escribir(string entrada){
  fi.seekp(indice);//Se ubica en el indice
  fi << entrada;
}
void infoPareja(node a, node b,string c,string d,int nivel,int peso){//Cuando se llama en profundidad n>1
  string info;
  info=to_string(a.id_nodo);//Primer nodo
  info+=",";
  info+=to_string(b.id_nodo);//Ultimo nodo
  info+=",[";//Nodos por los que pasa
  string ayudaA;
  ayudaA=c;
  ayudaA+=to_string(b.id_nodo);
  info+=ayudaA;
  ayudaA+=",";
  info+="],[";//Peso de los nodos por los que pasa
  string ayudaB=d;
  ayudaB+=to_string(b.peso_nodo);
  info+=ayudaB;
  ayudaB+=",";
  info+="],";
  peso+=b.peso_nodo;
  info+=to_string(peso);//Sumatoria de todos los nodos
  info+=",";
  info+=to_string(nivel);//Cantidad de nodos por los que pasa/Nivel de profundidad de la llamada
  int cont=0;
  info+="\n";
  escribir(info);
  indice+=info.length()+1;
  //Escribe el archivo
  nivel+=1;
  while(cont<b.Cantidad_Siguientes){
      node j;
      int cont2=0;
      while(cont2<100000){
          //cout<<"CONT2: "<<cont2<<"\n";
          if(Array_Nodes[cont2].id_nodo==b.Nodos_Siguientes[cont]){
              j=Array_Nodes[cont2];
              break;
          }
          cont2++;
      }
      infoPareja(a,j,ayudaA,ayudaB,nivel,peso);
      cont++;
  }
}

void crearParejas(){
  ultimoEnLeer=0;
  while(ultimoEnLeer<ultimo){
      //cout<<"YA\n";
      infoPareja(Array_Nodes[ultimoEnLeer],Array_Nodes[ultimoEnLeer],"","",0,0);
      ultimoEnLeer++;
  }
}

void readFile(){
    std::ifstream ficheroEntrada;

    ficheroEntrada.open ("C:/Users/U1/Documents/Archivos/grafoPequeno.txt");


    string frase;


    //va lleyendo linea por linea
    while (!ficheroEntrada.eof()){
        getline(ficheroEntrada, frase);

        //#pragma omp parallel
        //{
            Obtener_Datos_Nodos(frase);
        //};
        //Break
    }
    ultimo=ultimoEnLeer;
    ultimoEnLeer=0;


    
    ficheroEntrada.close();
    //Crea los respectivos archivos
    string arch="C:/Users/U1/Documents/Archivos/parejas.txt";
    fi.open(arch);
    crearParejas();
    fi.close();


}


int main() {

    readFile();
    //#pragma omp parallel
    {

    };
    return 0;
}
