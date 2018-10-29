#ifndef TRADUCTOR_H
#define TRADUCTOR_H
#endif // TRADUCTOR_H

#include <stack>
#include <stdlib.h>     /* malloc, free, rand */
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

//Valores para los tipos de datos
enum tipos{
    ENTERO=2501,
    FLOTANTE,
    CARACTER,
    CADENA
};

//Valores para los codigos de operacion
enum cops{
    FONDO_FALSO = -1,
    INPUT = 3000,
    OUTPUT,
    ASIG,
    OR,
    AND,
    DIF,
    PLUS,
    MINUS,
    MULT,
    DIV,
    MODULUS,
    EQUALS,
    NOTEQUALS,
    LESSTHAN,
    LESSOREQUALSTHAN,
    GREATERTHAN,
    GREATEROREQUALSTHAN
};

//nodo de Estructura de cuadruplos
struct cuadruplo {
    int key;
    cops cop;
    int op1;
    int op2;
    int resl;
    struct cuadruplo *next2;
};

//nodo de Estructura de renglon de tabla de simbolos
struct simbolosRow{
    tipos type;
    int count;
    string desc;
    int *apram;
    int *apnext;
    struct simbolosRow *next2;
};

//Definiciones de tipos
typedef struct simbolosRow SimbolosRow;
typedef SimbolosRow *SimbolosRowPtr;

typedef struct cuadruplo Cuadruplo;
typedef Cuadruplo *CuadruploPtr;

//PILAS

//pila de operadores
static std::stack<cops> POperadores;

//pila de operandos
static std::stack<int> POperandos;

//pila de tipos
static std::stack<tipos> PTipos;

//pila de tmp avail
static std::stack<int> PAvail;

//pila de saltos
static std::stack<int> PSaltos;

//contador de la estructura de declaracion
static tipos DecAux;

//contador de la estructura de la tabla de simbolos
static int SimbolosCount = 3500;

//contador de cuadruplos
static int CuadruplosCount = 0;

//raiz de la estructura
static CuadruploPtr cuadruplos;

//Ultimo elemento de la lista de cuadruplos
static CuadruploPtr FinalCuadruplo;

//elemento final de la tabla de simbolos
static SimbolosRowPtr FinalElemTS;

//raiz de la tabla de simbolos
static SimbolosRowPtr TDS;

//declaracion de funciones

void generarCuadruplo(cops,int,int,int);
CuadruploPtr buscarCuadruplo(int );

void pushPO(int, char*);
SimbolosRowPtr buscarOp(int);

int buscarIdEnTDS(char*);
int buscarODeclararEnTDS(int,char*);
//TODO buscar AddrEnTDS

void ejecutarAccion(int);
bool esAvail(int);
int obtenerAvail();
void liberarAvail(int);
SimbolosRowPtr buscarAddrEnTDS(int);
void imprimirCuadruplos();
void imprimirTDS();

//Implementacion de funciones

SimbolosRowPtr buscarAddrEnTDS(int a){
    SimbolosRowPtr nodo;
    nodo = TDS;
    do{
        if(nodo->count==a){
            break;
        }else{
            nodo = nodo->next2;
        }
    }while(nodo!=nullptr);
    return nodo;
}

int obtenerAvail(){
    int tmp = PAvail.top();
    PAvail.pop();
    return tmp;
}

void liberarAvail(int addr){
    PAvail.push(addr);
}

//genera cuadruplo
void generarCuadruplo(cops cop, int op1, int op2, int res)
{
    CuadruploPtr nodo = new Cuadruplo();

    nodo->key=CuadruplosCount;
    nodo->cop = cop;
    nodo->op1 = op1;
    nodo->op2 = op2;
    nodo->resl = res;
    nodo->next2 = nullptr;

    CuadruplosCount++;

    if (cuadruplos==nullptr)
    {
        cuadruplos = nodo;
        FinalCuadruplo= nodo;
    }
    else
    {
        FinalCuadruplo->next2=nodo;
        FinalCuadruplo = nodo;
    }


}

//buscar cuadruplo (pendiente de revisar)
CuadruploPtr BuscarCuadruplo(int count)
{
    CuadruploPtr nodo;
    nodo=cuadruplos;
    do
    {
        if(nodo->key== count)
            break;
        else
            nodo= nodo->next2;
    }
    while(nodo!=nullptr);
    return nodo;
}

//imprme la tabla de cuadruplos
void imprimirCuadruplos(){

    cout<<"      CUADRUPLOS     "<<endl;
    cout<<"---------------------"<<endl;
    cout<<" c "<<" OP1 "<<" OP2 "<<" RES "<<endl;

    if(cuadruplos!=nullptr){
        CuadruploPtr node = cuadruplos;
        do{
            cout<<node->key<<" "<<node->cop<<" "<<node->op1<<" "<<node->op2<<" "<<node->resl<<endl;
            node = node->next2;
        }while(node!=nullptr);
    }else{
        cout<<" !!!! La tabla de cuadruplos esta vacia"<<endl;
    }
}

//imprme la tabla de simbolos
void imprimirTDS(){

    cout<<"  TABLA DE SIMBOLOS "<<endl;
    cout<<"---------------------"<<endl;
    cout<<" addr "<<" type "<<" desc "<<"  "<<endl;

    if(TDS!=nullptr){
        SimbolosRowPtr node = TDS;
        do{
            cout<<" "<<node->count<<"  "<<node->type<<"  "<<node->desc<<" "<<endl;
            node = node->next2;
        }while(node!=nullptr);
    }else{
        cout<<" !!!! La tabla de simbolos esta vacia"<<endl;
    }
}

//identifica si la direccion pertenece al avail
bool esAvail(int n){
    return n>=5550&&n<=6000;
}

//devuelve la direccion del id
//o devuelve -1 si no lo encontro
int buscarIdEnTDS(char *lexema){

    SimbolosRowPtr node;
    node = TDS;

    string cpy;

    char *i;
    i = &lexema[0];

    while(*i!=0x00){
        cpy.append(i);
        i++;
    }

    if(node!=nullptr){
      //recorrer la lista en busca del elemento
      do{
        if(node->desc==cpy){
            return node->count;
        }
        node = node->next2;
      }while(node!=nullptr);
    }

    return -1;
}

//devuelve la direccion de la constante existente
//o de una nueva declarada
int buscarODeclararEnTDS(int codeid,char *lexema){

    //busca si se encuentra alguna entrada
    int baddr = buscarIdEnTDS(lexema);

    //si no se encontro
    if(baddr==-1){

        //declarar
        //SimbolosRow *newPtr; //nuevo nodo
        //reservar espacio para nuevo nodo
        //newPtr = (SimbolosRowPtr) malloc(sizeof(SimbolosRow));

        SimbolosRowPtr newPtr = new SimbolosRow();

        if(newPtr!=nullptr){
            //si hay espacio en memoria

            newPtr->next2 = nullptr;
            newPtr->count = SimbolosCount;

            string cpy;

            char *i;
            i = &lexema[0];

            while(*i!=0x00){
                cpy.append(i);
                i++;
            }

            newPtr->desc = cpy;

            switch(codeid){
                case 1001:
                    newPtr->type = ENTERO;
                    break;
                case 1002:
                    newPtr->type = FLOTANTE;
                    break;
                case 1003:
                    newPtr->type = FLOTANTE;
                    break;
                case 1030:
                    newPtr->type = CARACTER;
                    break;
                case 1031:
                    newPtr->type = CADENA;
                    break;
            }

            if(TDS==nullptr){
              //lista vacia, crear primer elemento
              TDS = newPtr;
              FinalElemTS = newPtr;
            }else{
                FinalElemTS->next2 = newPtr;
                FinalElemTS = newPtr;
            }

            //incrementar contador de la tabla de simbolos
            SimbolosCount++;

            //retornar la direccion declarada
            return newPtr->count;
        }else{
            throw "no hay espacio disponible en memoria";
        }
    }else{
        //si encontro, retornar la direccion
        return baddr;
    }
}

//Push pila de operandos
//obtiene la direccion del id o constante y le hace
//push a la pila de operandos
void pushPO(int codeid, char *lexema){

    if(codeid==1000){

        //es id
        int addr = buscarIdEnTDS(lexema);

        if(addr>=0){

            //direccion valida push
            POperandos.push(addr);

            //push tambien a la pila de tipos
            SimbolosRowPtr nodo = buscarAddrEnTDS(addr);
            PTipos.push(nodo->type);


        }else{
            //el elemento no existe
            throw "variable no declarada";
        }

    }else{
        if(codeid==1001||codeid==1002||codeid==1003||codeid==1030||codeid==1031){
            //es constante numerica

            int addr = buscarODeclararEnTDS(codeid,lexema);
            POperandos.push(addr);

            //push tambien a la pila de tipos
            SimbolosRowPtr nodo = buscarAddrEnTDS(addr);
            PTipos.push(nodo->type);

        }else{
            //simbolo no reconocido
            throw "Simbolo no apto para la pila de operandos";
        }
    }

}

void ACTION_2012(int codeid){
    switch (codeid) {
        //==
        case 1020:
            POperadores.push(EQUALS);
        break;
        //!=
        case 1018:
            POperadores.push(NOTEQUALS);
        break;
        //<
        case 1023:
            POperadores.push(LESSTHAN);
        break;
        //<=
        case 1024:
            POperadores.push(LESSOREQUALSTHAN);
        break;
        //>
        case 1021:
            POperadores.push(GREATERTHAN);
        break;
        //>=
        case 1022:
            POperadores.push(GREATEROREQUALSTHAN);
        break;
    }
}

void ACTION_2013(){

    tipos t1,t2;

    t1 = PTipos.top();
    PTipos.pop();

    t2 = PTipos.top();
    PTipos.pop();

    //si top y top-1 son compatibles entonces
    if(t1==t2){

        //obtener operando 2
        int operando2 = POperandos.top();
        POperandos.pop();

        //obtener operando 1
        int operando1 = POperandos.top();
        POperandos.pop();

        //obtiene una direccion correspondiente al avail
        int resultado = obtenerAvail();

        //se obtiene el operador
        cops operador = POperadores.top();

        //genera cuadruplo
        generarCuadruplo(operador,operando1,operando2,resultado);

        if(esAvail(operando1))
            liberarAvail(operando1);

        if(esAvail(operando2))
            liberarAvail(operando2);

        POperandos.push(resultado);
        PTipos.push(t1);

        POperadores.pop();
    }else{
        throw "Error semantico, tipos no compatibles";
    }
}

void ACTION_2014(){
    //TODO si top de la pila es booleano

//    int resultado = POperandos.top();
//    POperandos.pop();

    //se espera que este un operador not en el tope
//    cops operador = POperadores.top();
//    POperadores.pop();

    //generar cuadruplo del not
//    generarCuadruplo(operador,0,0,resultado);

}

void ACTION_2015(){

//    tipos t1,t2;

//    t1 = PTipos.top();
//    PTipos.pop();

//    t2 = PTipos.top();
//    PTipos.pop();

//    //si top y top-1 son compatibles entonces
//    if(t1==t2){

//        //obtener operando 2
//        int operando2 = POperandos.top();
//        POperandos.pop();

//        //obtener operando 1
//        int operando1 = POperandos.top();
//        POperandos.pop();

//        //obtiene una direccion correspondiente al avail
//        int resultado = obtenerAvail();

//        //se obtiene el operador
//        cops operador = POperadores.top();

//        //genera cuadruplo
//        generarCuadruplo(operador,operando1,operando2,resultado);

//        if(esAvail(operando1))
//            liberarAvail(operando1);

//        if(esAvail(operando2))
//            liberarAvail(operando2);

//        POperandos.push(resultado);
//        PTipos.push(t1);

//        POperadores.pop();
//    }else{
//        throw "Error semantico, tipos no compatibles";
//    }
}


void ACTION_2016(){

//    tipos t1,t2;

//    t1 = PTipos.top();
//    PTipos.pop();

//    t2 = PTipos.top();
//    PTipos.pop();

//    //si top y top-1 son compatibles entonces
//    if(t1==t2){

//        //obtener operando 2
//        int operando2 = POperandos.top();
//        POperandos.pop();

//        //obtener operando 1
//        int operando1 = POperandos.top();
//        POperandos.pop();

//        //obtiene una direccion correspondiente al avail
//        int resultado = obtenerAvail();

//        //se obtiene el operador
//        cops operador = POperadores.top();

//        //genera cuadruplo
//        generarCuadruplo(operador,operando1,operando2,resultado);

//        if(esAvail(operando1))
//            liberarAvail(operando1);

//        if(esAvail(operando2))
//            liberarAvail(operando2);

//        POperandos.push(resultado);
//        PTipos.push(t1);

//        POperadores.pop();
//    }else{
//        throw "Error semantico, tipos no compatibles";
//    }
}

//=====> EXPRESIONES

void ACTION_2002() {
    POperadores.push(OR);
}

void ACTION_2003 () {
    POperadores.push(AND);
}

void ACTION_2004 () {
    POperadores.push(DIF);
}

void ACTION_2005 (int type) {

    if(type == 1004) {
         //1004 +
        POperadores.push(PLUS);
    } else {
        //1005 -
        POperadores.push(MINUS);
    }
}

void ACTION_2006 (int type) {
    //*
    if(type == 1006) {
        POperadores.push(MULT);
    } else {
        // /
        if(type == 1007) {
            POperadores.push(DIV);
        } else {
            // %
            if(type == 1008){
                POperadores.push(MODULUS);
            }
        }
    }
}

void ACTION_2007 (int type, char* lex){

    //declara o busca la constante con su tipo
    //en este metodo se comprueba y se dan de alta con su tipo
    int addr = buscarODeclararEnTDS(type,lex);
    tipos tip = buscarAddrEnTDS(addr)->type;


    POperandos.push(addr);
    PTipos.push(tip);

}

//mete marca de fondo falso
void ACTION_2008 (int codeid) {
    if(codeid == 1009) {
        POperadores.push(FONDO_FALSO);
    } else {
        throw 'Error semantico.';
    }
}

//saca marca de fondo falso
void ACTION_2009 () {
    POperadores.pop();
}

void ACTION_2010 () {
    if(POperadores.top() == MULT || POperadores.top() == DIV || POperadores.top() == MODULUS) {

        tipos t1 = PTipos.top();PTipos.pop();
        tipos t2 = PTipos.top();PTipos.pop();

        if(t1==t2) {

            int operando2 = POperandos.top();
            POperandos.pop();

            int operando1 = POperandos.top();
            POperandos.pop();

            int resultado = obtenerAvail();

            generarCuadruplo(POperadores.top(),operando1,operando2,resultado);


            if(esAvail(operando2)) {
               liberarAvail(operando2);
            }
            if(esAvail(operando1)) {
               liberarAvail(operando1);
            }

            PTipos.push(t1);
            POperandos.push(resultado);
            POperadores.pop();

        } else {
            throw "Error semántico";
        }
    }
}

void ACTION_2011 () {
    if(POperadores.top() == PLUS || POperadores.top() == MINUS) {

        tipos t1 = PTipos.top();PTipos.pop();
        tipos t2 = PTipos.top();PTipos.pop();

        if(t1==t2) {

            int operando2 = POperandos.top();
            POperandos.pop();

            int operando1 = POperandos.top();
            POperandos.pop();

            int resultado = obtenerAvail();

            generarCuadruplo(POperadores.top(),operando1,operando2,resultado);


            if(esAvail(operando2)) {
               liberarAvail(operando2);
            }
            if(esAvail(operando1)) {
               liberarAvail(operando1);
            }

            PTipos.push(t1);
            POperandos.push(resultado);
            POperadores.pop();

        } else {
            throw "Error semántico";
        }
    }
}

//=====> ASIGNACION

void ACTION_2001(int code_id, char *lexema){
    pushPO(code_id,lexema);
}

void ACTION_2022(){
    tipos t1 = PTipos.top();
    PTipos.pop();
    tipos t2 = PTipos.top();
    PTipos.pop();

    if(t1==t2){
        int exp = POperandos.top();
        POperandos.pop();
        int res = POperandos.top();
        POperandos.pop();
        generarCuadruplo(ASIG,exp,0,res);

        if(esAvail(exp))
            liberarAvail(exp);
        if(esAvail(res))
            liberarAvail(res);
    }else{
        throw "ERROR SEMANTICO";
    }
}

//=====> DECLARACION DE VARIABLES

//pendiente booleano, pero lista e.e
void ACTION_2017(int code_id){

    if(code_id == 1033){
        DecAux = ENTERO;
    }

    if(code_id == 1034)
    {
        DecAux = FLOTANTE;
    }

    /*TODO if(code_id == bool (103?){
     * DecAux = Bool;
     * }*/

    if(code_id == 1035)
    {
        DecAux = CARACTER;
    }

    if(code_id == 1036)
    {
        DecAux = CADENA;
    }


}

//lista
void ACTION_2018(int code_id, char* lexema){
    int a = buscarODeclararEnTDS(code_id,lexema);
    POperandos.push(a);
}

//lista
void ACTION_2019(){

    while(!POperandos.empty()){
        int a = POperandos.top();
        POperandos.pop();

        SimbolosRowPtr n = buscarAddrEnTDS(a);
        n->type = DecAux;
    }

}

//FIN DECLARACION DE CONSTANTES


//READ
void ACTION_2020(char *lexema){
    int addr = buscarIdEnTDS(lexema);
    generarCuadruplo(INPUT,0,0,addr);
}

//WRITE
void ACTION_2021(){
    PTipos.pop();
    int op = POperandos.top();
    POperandos.pop();
    generarCuadruplo(OUTPUT,0,0,op);
}
