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
    MODULUS
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
    int desc;
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
static std::stack<int> POperadores;

//pila de operandos
static std::stack<int> POperandos;

//pila de tipos
static std::stack<int> PTipos;

//pila de tmp avail
static std::stack<int> PAvail;

//pila de saltos
static std::stack<int> PSaltos;

//contador de la estructura de declaracion
static int DecAux = 0;

//contador de la estructura de la tabla de simbolos
static int SimbolosCount =0;

//contador de cuadruplos
static int CuadruplosCount = 0;

//raiz de la estructura
CuadruploPtr cuadruplos;

//Ultimo elemento de la lista de cuadruplos
CuadruploPtr FinalCuadruplo;

//elemento final de la tabla de simbolos
SimbolosRow FinalElemTS;

//raiz de la tabla de simbolos
SimbolosRow TDS;

//declaracion de funciones

void generarCuadruplo(cops cop, int op1, int op2, int res);
CuadruploPtr buscarCuadruplo(int addr);

void pushPO(int codeid, char* lexema);
SimbolosRowPtr buscarOp(int address);

//void a(){
//    SimbolosRowPtr tmpNode;

//    //alojar un espacio para un nodo
//    tmpNode = (SimbolosRowPtr) malloc(sizeof(SimbolosRow));

//    if(tmpNode!=nullptr){
//        //espacio alojado

//    }else{
//        //memoria insuficiente
//    }
//    //liberar espacio de memoria
//    free(tmpNode);
//}

//TODO ACCIONES

//TODO GenerarCuadruplo()
//TODO buscarCuadruplo()

