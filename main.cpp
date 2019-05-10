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
    string fanIn="";
    string fanOut="";
};

//Variables que se usan a lo largo del codigo
//Array donde se van a guardar todos los nodos, El nodo con el id i va a estar en Array_Nodes[i]
node Array_Nodes[74782]; // 74782 es el maximo id de un nodo
//node Array_Nodes_Iniciales[17312]; //17312 es la cantidad de nodos iniciales //Cuenta los nodos iniciales
int contador_Nodos = 0; // Cuenta todos los nodos
ofstream fi;//Variables para archivos
ofstream salida1;
ofstream salida2;//Cantidad de nodos que hay leidos

//***************************************************************************************************
//Funciones que hacen distintas cosas pequeñas

//Toma un numero que esta en un string y lo convierte a int
int StringToInt(string pString){
    int n = std::stoi(pString);
    return n;
}

node buscarNodo(int id){//Busca un nodo(Cuando el indice es igual al id)
    node j;
    j = Array_Nodes[id];
    return j;
}

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
    //bool IsFirst; //Bandera que indica si el nodo no tiene anteriores
    //bool IsLast; //Bandera que indica si el nodo no tiene siguiente
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
        //IsFirst = false; //Altera la bandera
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
        //IsFirst = true;
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
        //IsLast = false;
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
    }// else {
        //IsLast = true;
    //}
    //AGREGA EL NODO AL ARRAY DE NODOS
    Array_Nodes[Node_Actual.id_nodo] = Node_Actual; //Se agrega en la posicion del id
    //Si el nodo leido no tiene arcos hacia el, es un nodo inicial y se coloca en el array de nodos iniciales
    /*
    if (IsFirst) {
        Array_Nodes_Iniciales[UltimoNodoInicial] = Node_Actual;
        UltimoNodoInicial++;
    }
    */
    contador_Nodos++;
    //std::cout << Node_Actual.id_nodo << std::endl;
}


//AQUI PARA ARRIBA HACE LO DE LEER EL ARCHIVO Y CREAR NODOS

//********************************************************************************************************************************
void escribir(string entrada){//Escribe en el archivo de parejas de nodos (apyo)
  fi << entrada;
}

void escribir1(string entrada){//Escribe en el archivo con metricas de cada nodo
  salida1 << entrada;
}

void escribir2(string entrada){//Escribe en el archivo con metricas de cada par de nodo
  salida2<< entrada;
}

/*
node buscarNodo(int id){//Buscar nodo(viejo)

  node j;
  int cont2=0;
  while(cont2<ultimo+1){
      if(Array_Nodes[cont2].id_nodo==id){
          j=Array_Nodes[cont2];
          break;
      }
      cont2++;
  }
  return j;

}
*/

void infoPareja(node a, node b,string c,string d,int nivel,int peso){//Metodo que crea un string que se usa de apoyo para las parejas de nodos
  string info;
  info=to_string(a.id_nodo);//Primer nodo
  info+=",";
  info+=to_string(b.id_nodo);//Ultimo nodo
  info+=",[";//De aqui en adelante son los nodos por los que pasa
  string ayudaA;
  ayudaA=c;
  ayudaA+=to_string(b.id_nodo);
  info+=ayudaA;
  ayudaA+=",";
  info+="],[";//De aqui en adelante es el peso de los nodos por los que pasa
  string ayudaB=d;
  ayudaB+=to_string(b.peso_nodo);
  info+=ayudaB;
  ayudaB+=",";
  info+="],";
  peso+=b.peso_nodo;
  info+=to_string(peso);//Sumatoria de todos los pesos de los nodos
  info+=",";
  info+=to_string(nivel);//Cantidad de nodos por los que pasa
  int cont=0;
  info+="\n";
  escribir(info);
  //Escribe el archivo
  nivel+=1;
  while(cont<b.Cantidad_Siguientes){
      node j=buscarNodo(b.Nodos_Siguientes[cont]);
      infoPareja(a,j,ayudaA,ayudaB,nivel,peso);
      cont++;
  }
}

string calcularFanIn(node a){//Calcula fan in de un nodo
  if(a.fanIn!=""){
      return a.fanIn;
  }
  string respuesta="";
  int cont=0;
  while(cont<a.Cantidad_Anteriores){//examina todos los nodos anteriores al nodo
      node l=buscarNodo(a.Nodos_Anteriores[cont]);
      respuesta+=to_string(l.id_nodo);//Agrega el Id del nodo
      respuesta+=",";
      respuesta+=calcularFanIn(l);//Añade el fan in de ese nodo
      cont++;
  }
  a.fanIn=respuesta;
  return respuesta;
}

string calcularFanOut(node a){//Calcula el fan out de un nodo
  if(a.fanOut!=""){
      return a.fanOut;
  }
  string respuesta="";
  int cont=0;
  while(cont<a.Cantidad_Siguientes){//Examina todos los nodos siguientes al nodo
      node l=buscarNodo(a.Nodos_Siguientes[cont]);
      respuesta+=to_string(l.id_nodo);//Agrega el Id del nodo
      respuesta+=",";
      respuesta+=calcularFanOut(l);//Añade el fan out de ese nodo
      cont++;
  }
  a.fanOut=respuesta;
  return respuesta;
}

string metricaFan(string f){
  if(f.length()==0){//Si el fan esta vacio, no existe metrica
      return "";
  }
  string metrica;
  int parser=0;
  int nodosAparecen[10000];//Nodos que aparesen
  int contNodo=0;
  string nodoActual;
  int limite=f.length();
  while(parser<limite){
      while(f[parser]!=',' && parser<limite){//Añade los nodos que aparecen en el string a un arreglo de enteros
          nodoActual+=f[parser];
          parser++;
      }
      nodosAparecen[contNodo]=StringToInt(nodoActual);
      parser++;
      contNodo++;
      nodoActual="";
  }
  contNodo++;
  metrica+="\nSumatoria neta: ";//Suma todo solo una vez
  int cont=0;
  int suma=0;
  int nodosSinRepetir[10000];
  int cont2=0;
  while(cont<contNodo){
      int revisor=0;
      while(nodosSinRepetir[revisor]!=0&&cont<contNodo){//Busca los nodos que no se repiten en el arreglo
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
  cont2--;
  while(cont<cont2){//Calcula la sumatoria neta
      node l=buscarNodo(nodosSinRepetir[cont]);
      suma+=l.peso_nodo;
      cont++;
  }
  metrica+=to_string(suma);
  metrica+="\nSumatoria absoluta: ";//Suma todo
  cont=0;
  suma=0;
  contNodo--;
  while(cont<contNodo){//Calcula sumatoria absoluta
      node l=buscarNodo(nodosAparecen[cont]);
      suma+=l.peso_nodo;
      cont++;
  }
  metrica+=to_string(suma);
  metrica+="\nPromedio: ";//El anterior entre la cantidad de nodos
  suma=suma/(contNodo);//Calcula promedio
  metrica+=to_string(suma);
  return metrica;
}

string calcularFanOutConMetrica(node a){//Metodo que saca el fan out de un nodo y de una vez adjunta la metrica
  string h="";
  h=calcularFanOut(a);
  h=h.substr(0,h.length()-1);
  if(h==""){
      h+="Vacio";
      return h;
  }else{
      string ayuda=h;
      h+=";\nMetrica: ";
      h+=metricaFan(ayuda);
      return h;
  }
}

string calcularFanInConMetrica(node a){//Metodo que saca el fan in de un nodo y de una vez adjunta la metrica
  string h="";
  h=calcularFanIn(a);
  h=h.substr(0,h.length()-1);
  if(h==""){
      h+="Vacio";
      return h;
  }else{
      string ayuda=h;
      h+=";\nMetrica: ";
      h+=metricaFan(ayuda);
      return h;
  }
}

void crearSalida1(node a){//Metodo que calcula las metricas de un nodo
  string respuesta;
  respuesta="Nodo: "+to_string(a.id_nodo);
  respuesta+=";\nFan In: ";
  string h=calcularFanInConMetrica(a);
  respuesta+=h;
  respuesta+=";\nFan Out: ";
  h=calcularFanOutConMetrica(a);
  respuesta+=h;
  respuesta+=";\n\n";
  escribir1(respuesta);
}

void crearParejas(){//Metodo que crea todas las parejas existentes de nodos
  int ultimoEnLeer=0;
  //PARALELIZAR
  int nodos=0;
  while(nodos<contador_Nodos){
      //cout<<"Creando parejas del nodo: "<<ultimoEnLeer<<"\n";
      if(Array_Nodes[ultimoEnLeer].id_nodo!=0){
          infoPareja(Array_Nodes[ultimoEnLeer],Array_Nodes[ultimoEnLeer],"","",1,0);
          nodos++;
      }
      ultimoEnLeer++;
  }
}
void crearMetricaNodos(){
  int nodos=0;
  //PARALELIZAAAAAAAAR
  int leyendo=0;
  while(nodos<contador_Nodos){
      if(Array_Nodes[leyendo].id_nodo!=0){
        crearSalida1(Array_Nodes[leyendo]);
        nodos++;
      }
      leyendo++;
  }
}

string cortarPareja(string pareja){//Este es un metodo largo para obtener la metrica de un par de nodos en caso de que se arregle la suma de rutas
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

string cortarPareja2(string pareja){//Este es un metodo para obtener la metrica de un par de nodos en caso de que no se arregle
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
  while(pareja[parser]!=']'){
      parser++;
  }
  parser++;
  while(pareja[parser]!=']'){
      parser++;
  }
  respuesta+="\nMetrica:\nSumatoria neta:\n";
  int peso=0;
  parser++;
  parser++;
  string ayuda="";
  while(pareja[parser]!=','){
    ayuda+=pareja[parser];
    parser++;
  }
  peso=StringToInt(ayuda);
  parser++;
  respuesta+=to_string(peso);
  respuesta+="\nSumatoria absoluta:\n";
  respuesta+=to_string(peso);
  respuesta+="\nPromedio:\n";
  ayuda="";
  while(parser<=pareja.length()){
      ayuda+=pareja[parser];
      parser++;
  }
  int cantNodos=0;
  cantNodos+=StringToInt(ayuda);
  respuesta+=to_string(peso/cantNodos);
  respuesta+="\n";
  return respuesta;
}

void readFile2() {
  std::ifstream ficheroEntrada;
  ficheroEntrada.open("C:/Users/usuario/Desktop/TEC/algoritmos/Tarea/Pruebas/Paralelo/paralelo-algorimtos/graph_info.txt");
  string frase;
  //Array_Nodes[ultimoEnLeer] = Node_Actual;
  //va lleyendo linea por linea
  while (!ficheroEntrada.eof()) {
      getline(ficheroEntrada, frase);
      Obtener_Datos_Nodos(frase);
  }
  ficheroEntrada.close();
  //std::cout << buscarNodo(74754).id_nodo << std::endl;
}


void readFile(){//Practicamente todo lo principal
    std::ifstream ficheroEntrada;
    ficheroEntrada.open ("C:/Users/U1/Documents/Archivos/grafoPequeno.txt");
    string frase;
    //va lleyendo linea por linea del grafo
    while (!ficheroEntrada.eof()){
        getline(ficheroEntrada, frase);
        Obtener_Datos_Nodos(frase);
    }
    ficheroEntrada.close();
    //Crea los respectivos archivos
    string arch="C:/Users/U1/Documents/Archivos/parejas.txt";
    string arch2="C:/Users/U1/Documents/Archivos/nodos.txt";
    string arch3="C:/Users/U1/Documents/Archivos/infoParejas.txt";
    fi.open(arch);
    salida1.open(arch2);
    crearParejas();//Crea parejas de nodos
    //cout<<"Hizo parejas de nodos\n";
    crearMetricaNodos();//Crea la metrica de cada nodo
    //cout<<"Hizo los nodos\n";
    fi.close();
    salida1.close();
    ficheroEntrada.open ("C:/Users/U1/Documents/Archivos/parejas.txt");
    salida2.open(arch3);//De aqui para bajo se crea la metrica de cada par de nodos
    while (!ficheroEntrada.eof()){
        getline(ficheroEntrada, frase);
        if(frase==""){
            break;
        }
        frase=cortarPareja2(frase);
        escribir2(frase);
    }
    ficheroEntrada.close();
    salida2.close();
}

void simulacion(){//simulacion de como partir los nodos en mpi
  int cont=0;
  int max=1;
  int nodos=3458;
  while((nodos%max)!=0){
      nodos++;
  }
  float nodosCU=(nodos+0.0)/max;
  while(cont<max){
      cout<<"Nodo: "<<cont<<" se encarga desde: "<<int(nodosCU*cont)<<" hasta: "<<int(nodosCU*(cont+1))<<"\n";
      cont++;
  }
  return;
}

int main() {
    readFile();
    cout<<"listo";
    //#pragma omp parallel
  //simulacion();
    {
    };
    return 0;
}
