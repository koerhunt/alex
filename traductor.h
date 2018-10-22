#ifndef TRADUCTOR_H
#define TRADUCTOR_H
#endif // TRADUCTOR_H

#include <stack>
#include <stdlib.h>     /* malloc, free, rand */
#include <stdio.h>

//Valores para los tipos de datos
enum tipos{
    ENTERO=2501,
    FLOTANTE,
    CARACTER,
    CADENA
};

//Valores para los codigos de operacion
enum cops{
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
    int addr;
    char *desc;
    tipos type;
    int *apram;
    int *apnext;
    struct simbolosRow *next2;
};

//Definiciones de tipos
typedef struct cuadruplo Cuadruplo;
typedef struct simbolosRow SimbolosRow;

typedef Cuadruplo *CuadruploPtr;
typedef SimbolosRow *SimbolosRowPtr;

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
static int DecAux = 0;

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

void generarCuadruplo(cops, int , int , int );
CuadruploPtr buscarCuadruplo(int );

void pushPO(int, char*);
SimbolosRowPtr buscarOp(int);

int buscarIdEnTDS(char*);
int buscarODeclararEnTDS(int,char*);
void ejecutarAccion(int);
int obtenerAvail();
bool esAvail(int);
void liberarAvail(int);

//Implementacion de funciones

//TODO obtenerAvail
//TODO liberarAvail()

//identifica si la direccion pertenece al avail
bool esAvail(int n){
    return n>=5550&&n<=6000;
}

//devuelve la direccion del id
//o devuelve -1 si no lo encontro
int buscarIdEnTDS(char *lexema){

    SimbolosRowPtr node;
    node = TDS;

    if(node!=nullptr){
      //recorrer la lista en busca del elemento
      do{
        if(node->desc==lexema){
            return node->addr;
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

        SimbolosRowPtr newPtr; //nuevo nodo

        //reservar espacio para nuevo nodo
        newPtr = (SimbolosRowPtr) malloc(sizeof(SimbolosRow));

        if(newPtr!=nullptr){
            //si hay espacio en memoria

            newPtr->addr = SimbolosCount;
            newPtr->desc = lexema;

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
            return newPtr->addr;
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
            //direccion valida
            POperandos.push(addr);

        }else{
            //el elemento no existe
            throw "variable no declarada";
        }

    }else{
        if(codeid==1001||codeid==1002||codeid==1003||codeid==1030||codeid==1031){
            //es constante numerica

            int addr = buscarODeclararEnTDS(codeid,lexema);
            POperandos.push(addr);

        }else{
            //simbolo no reconocido
            throw "Simbolo no apto para la pila de operandos";
        }
    }

}

//TODO buscarCuadruplo()
//TODO GenerarCuadruplo()


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

    int resultado = POperandos.top();
    POperandos.pop();

    //se espera que este un operador not en el tope
    cops operador = POperadores.top();
    POperadores.pop();

    //generar cuadruplo del not
    generarCuadruplo(operador,0,0,resultado);

}

void ACTION_2015(){

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
