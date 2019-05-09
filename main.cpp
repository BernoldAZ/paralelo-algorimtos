#include <iostream>
#include <string>
#include <fstream>

#include "omp.h"
#include "uthash.h"



using namespace std;
//************************************************************************************************
// Struct que tiene la información de cada nodo
struct node {
    int id_nodo;
    int peso_nodo;
    int Cantidad_Anteriores;
    int Nodos_Anteriores[2862];
    int Cantidad_Siguientes;
    int Nodos_Siguientes[857];
};

//Array donde se van a guardar todos los nodos, El nodo con el id i va a estar en Array_Nodes[i]

node Array_Nodes[74782]; // 74782 es el maximo id de un nodo

node Array_Nodes_Iniciales[17312]; //17312 es la cantidad de nodos iniciales

int UltimoNodoInicial= 0; //Cuenta los nodos iniciales

int contador_Nodos = 0; // Cuenta todos los nodos

//***************************************************************************************************
//Funciones que hacen distintas cosas pequeñas

//Toma un numero que esta en un string y lo convierte a int
int StringToInt(string pString){

    int n = std::stoi(pString);

    return n;
}

node buscarNodo(int id){
    node j;

    j = Array_Nodes[id];
    /*
    int cont2=0;
    while(cont2<100000){
        if(Array_Nodes[cont2].id_nodo==id){
            j=Array_Nodes[cont2];
            break;
        }
        cont2++;
    }*/
    return j;
}

ofstream fi;
ofstream salida1;
ofstream salida2;

int ultimo=0;
int indice=0;
int indice1=0;
int indice2=0;

//*************************************************************************************************************************************************************************
//AQUI PARA ABAJO HACE LO DE LEER EL ARCHIVO Y CREAR NODOS

void Obtener_Datos_Nodos (string frase) {

    node Node_Actual;
    frase += ' ';

    int recorrer = 0;
    string id_nodo;
    string peso_nodo;
    string Cantidad_Anteriores;
    string Cantidad_Siguientes;
    bool IsFirst; //Bandera que indica si el nodo no tiene anteriores
    bool IsLast; //Bandera que indica si el nodo no tiene siguientes

    //*********************************************************
    while (frase[recorrer] != ' ') { //da el id del nodo
        id_nodo = id_nodo + frase[recorrer];
        recorrer++;
    }
    Node_Actual.id_nodo = StringToInt(id_nodo); //Guarda el id

    while(frase[recorrer] == ' '){
        recorrer++;
    }

    //*********************************************************
    while (frase[recorrer] != ' ') { //da el peso del nodo
        peso_nodo = peso_nodo + frase[recorrer];
        recorrer++;
    }
    Node_Actual.peso_nodo = StringToInt(peso_nodo);//Guarda el peso

    while(frase[recorrer] == ' '){
        recorrer++;
    }

    //*********************************************************
    while (frase[recorrer] != ' ') { //da la cantidad de nodos anteriores del nodo
        Cantidad_Siguientes = Cantidad_Siguientes + frase[recorrer];
        recorrer++;
    }
    Node_Actual.Cantidad_Siguientes = StringToInt(Cantidad_Siguientes);
    while(frase[recorrer] == ' '){
        recorrer++;
    }

    if (Cantidad_Siguientes != "0") { //Pregunta si tiene mas de 0 nodos anteriores
        IsFirst = false; //Altera la bandera

        int Cantidad_Nodos = StringToInt(Cantidad_Siguientes); //Nos da la cantidad de nodos que usaremos en el for

        for (int i = 0; i < Cantidad_Nodos; i++) { //Con cada iteracion nos da uno de los nodos siguientes

            string Node_Actual_En_Lista;
            while (frase[recorrer] != ' ') { //da los nodos anteriores del nodo
                Node_Actual_En_Lista = Node_Actual_En_Lista + frase[recorrer];

                recorrer++;

            }
            Node_Actual.Nodos_Siguientes[i] = StringToInt(Node_Actual_En_Lista);
            if (frase[recorrer] == ' ') { recorrer++; }

        }
    } else {
        IsFirst = true;
        if (frase[recorrer] == ' ') { recorrer++; }
    }

    //*********************************************************
    while (frase[recorrer] != ' ') { //da la cantidad de nodos siguientes del nodo
        Cantidad_Anteriores = Cantidad_Anteriores + frase[recorrer];
        recorrer++;
    }
    Node_Actual.Cantidad_Anteriores = StringToInt(Cantidad_Anteriores);
    while(frase[recorrer] == ' '){
        recorrer++;
    }

    if (Cantidad_Anteriores != "0") { //Pregunta si tiene mas de 0 nodos siguientes
        IsLast = false;

        int Cantidad_Nodos = StringToInt(Cantidad_Anteriores);

        for (int i = 0; i < Cantidad_Nodos; i++) {

            string Node_Actual_En_Lista;
            while (frase[recorrer] != ' ') { //da los nodos anteriores del nodo
                Node_Actual_En_Lista = Node_Actual_En_Lista + frase[recorrer];

                recorrer++;

            }
            Node_Actual.Nodos_Anteriores[i] = StringToInt(Node_Actual_En_Lista);
            if (frase[recorrer] == ' ') { recorrer++; }

        }
    } else {
        IsLast = true;
    }


    //AGREGA EL NODO AL ARRAY DE NODOS
    Array_Nodes[Node_Actual.id_nodo] = Node_Actual; //Se agrega en la posicion del id

    //Si el nodo leido no tiene arcos hacia el, es un nodo inicial y se coloca en el array de nodos iniciales
    if (IsFirst) {
        Array_Nodes_Iniciales[UltimoNodoInicial] = Node_Actual;
        UltimoNodoInicial++;
    }

    contador_Nodos++;
    //std::cout << Node_Actual.id_nodo << std::endl;

}

void readFile() {
    std::ifstream ficheroEntrada;
    ficheroEntrada.open("C:/Users/usuario/Desktop/TEC/algoritmos/Tarea/Pruebas/Paralelo/paralelo-algorimtos/graph_info.txt");
    string frase;

    //va lleyendo linea por linea
    while (!ficheroEntrada.eof()) {
        if(contador_Nodos == 50155){   //Hace que termine de leer el archivo. 50155 es la cantidad de nodos que hay
            break;
        }
        getline(ficheroEntrada, frase);
        //#pragma omp parallel
        //{
        Obtener_Datos_Nodos(frase);
        //};
    }
    ficheroEntrada.close();

    //Crea los respectivos archivos
    /*
    string arch="C:/Users/U1/Documents/Archivos/parejas.txt";
    fi.open(arch);
    crearParejas();
    fi.close();*/
}
//AQUI PARA ARRIBA HACE LO DE LEER EL ARCHIVO Y CREAR NODOS

//********************************************************************************************************************************
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
      node j=buscarNodo(b.Nodos_Siguientes[cont]);
      infoPareja(a,j,ayudaA,ayudaB,nivel,peso);
      cont++;
  }
}

string calcularFanIn(node a){
  //cout<<"Examina fan in nodo: "<<a.id_nodo<<"\n";
  string respuesta="";
  int cont=0;
  while(cont<a.Cantidad_Anteriores){
      node l=buscarNodo(a.Nodos_Anteriores[cont]);
      respuesta+=to_string(l.id_nodo);
      respuesta+=",";
      respuesta+=calcularFanIn(l);
      cont++;
  }
  return respuesta;
}

string calcularFanOut(node a){
  //cout<<"Examina fan out nodo: "<<a.id_nodo<<"\n";
  string respuesta="";
  int cont=0;
  while(cont<a.Cantidad_Siguientes){
      node l=buscarNodo(a.Nodos_Siguientes[cont]);
      respuesta+=to_string(l.id_nodo);
      respuesta+=",";
      respuesta+=calcularFanOut(l);
      cont++;
  }
  return respuesta;
}
string metricaFan(string f){
  if(f.length()==0){
      return "";
  }
  string metrica;
  int parser=0;
  int nodosAparecen[10000];
  int contNodo=0;
  string nodoActual;
  int limite=f.length();
  while(parser<limite){
      while(f[parser]!=',' && parser<limite){
          nodoActual+=f[parser];
          parser++;
      }
      nodosAparecen[contNodo]=StringToInt(nodoActual);
      parser++;
      contNodo++;
      nodoActual="";
  }
  contNodo++;
  metrica+="\nSumatoria neta: ";//Suma todo una vez
  int cont=0;
  int suma=0;
  int nodosSinRepetir[10000];
  int cont2=0;
  while(cont<contNodo){
      int revisor=0;
      while(nodosSinRepetir[revisor]!=0&&cont<contNodo){
          if(nodosAparecen[cont]==nodosSinRepetir[revisor]){
              cont++;
              revisor=-1;
          }
          revisor++;
      }
      if(cont<contNodo){
          nodosSinRepetir[cont2]=nodosAparecen[cont];
          cont++;
          cont2++;
      }
  }
  cont=0;
  while(cont<cont2){
      node l=buscarNodo(nodosSinRepetir[cont]);
      suma+=l.peso_nodo;
      cont++;
  }
  metrica+=to_string(suma);
  metrica+="\nSumatoria absoluta: ";//Suma todo
  cont=0;
  suma=0;
  while(cont<contNodo){
      node l=buscarNodo(nodosAparecen[cont]);
      suma+=l.peso_nodo;
      cont++;
  }
  metrica+=to_string(suma);
  metrica+="\nPromedio: ";//El anterior entre la cantidad de nodos
  suma=suma/(contNodo-1);
  metrica+=to_string(suma);
  return metrica;
}

void crearSalida1(node a){
  string respuesta;
  respuesta="Nodo: "+to_string(a.id_nodo);
  respuesta+=";\nFan In: ";
  string h=calcularFanIn(a);
  h=h.substr(0,h.length()-1);
  respuesta+=h;
  if(h==""){
      respuesta+="Vacio";
  }
  h=metricaFan(h);
  if(h!=""){
      respuesta+=";\nMetrica: "+h;
  }
  respuesta+=";\nFan Out: ";
  h=calcularFanOut(a);
  h=h.substr(0,h.length()-1);
  respuesta+=h;
  if(h==""){
      respuesta+="Vacio";
  }
  h=metricaFan(h);
  if(h!=""){
      respuesta+=";\nMetrica: "+h;
  }
  respuesta+=";\n\n";
  cout<<respuesta;
}

void crearParejas(){
  int ultimoEnLeer=0;
  while(ultimoEnLeer<ultimo){
      crearSalida1(Array_Nodes[ultimoEnLeer]);
      infoPareja(Array_Nodes[ultimoEnLeer],Array_Nodes[ultimoEnLeer],"","",0,0);
      ultimoEnLeer++;
  }
}

string cortarPareja(string pareja){
  string respuesta="";
  respuesta+="Pareja: ";
  int parser=0;
  while(pareja[parser]!=','){
      respuesta+=pareja[parser];
      parser++;
  }
  respuesta+=",";
  parser++;
  while(pareja[parser]!=','){
      respuesta+=pareja[parser];
      parser++;
  }
  parser++;
  parser++;
  int parserPesos=parser;
  while(pareja[parserPesos]!='['){
      parserPesos++;
  }
  parserPesos++;
  respuesta+="\nMetrica:\nSumatoria neta:\n";
  int nodos[10000];
  int peso=0;
  int tope=0;
  while(pareja[parser]!=']'&& pareja[parser]!=','){
      string nodo="";
      while(pareja[parser]!=','&& pareja[parser]!=']'){
          nodo+=pareja[parser];
          parser++;
      }
      if(pareja[parser]!=']'){
          parser++;
      }
      int numNodo=StringToInt(nodo);
      string pesoNodo="";
      while(pareja[parserPesos]!=','&& pareja[parserPesos]!=']'){
          pesoNodo+=pareja[parserPesos];
          parserPesos++;
      }
      parserPesos++;
      int pesNod=StringToInt(pesoNodo);
      int revisor=0;
      while(revisor<tope){
          if(nodos[revisor]==numNodo){
              numNodo=0;
              pesNod=0;
              break;
          }
          revisor++;
      }
      if(numNodo!=0){
          nodos[tope]=numNodo;
          tope++;
          peso+=pesNod;
      }
  }
  respuesta+=to_string(peso);
  respuesta+="\nSumatoria absoluta:\n";
  parserPesos++;
  string pesoNodo;
  while(pareja[parserPesos]!=','){
      pesoNodo+=pareja[parserPesos];
      parserPesos++;
  }
  parserPesos++;
  peso=StringToInt(pesoNodo);
  respuesta+=to_string(peso);
  respuesta+="\nPromedio:\n";
  pesoNodo="";
  while(parserPesos<=pareja.length()){
      pesoNodo+=pareja[parserPesos];
      parserPesos++;
  }
  int cantNodos=1;
  cantNodos+=StringToInt(pesoNodo);
  respuesta+=to_string(peso/cantNodos);
  respuesta+="\n";
  return respuesta;
}

int main() {

    readFile();
    //#pragma omp parallel
    //frase=frase.substr(0,4);

    std::cout << buscarNodo(74754).id_nodo << std::endl;


    string a="2,3,[2,3],[3,4],7,1";
    string b="2,5,[2,3,4,5],[3,4,5,8],20,3";
    string c="2,5,[2,7,3,4,5],[3,7,4,5,8],27,4";
    cout<<cortarPareja(a);
    cout<<cortarPareja(b);
    cout<<cortarPareja(c);

    return 0;
}
