#ifndef TRADUCTOR_H
#define TRADUCTOR_H
#endif // TRADUCTOR_H

#include <stack>

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

struct a;
//TODO {Estructura de cuadruplos}

//TODO func generarCuadruplo()
//TODO func rellenar()

//TODO obtenerVariable
//TODO obtenerConstante
//TODO declararVariable
//TODO declararConstante
//TODO COP
//TODO ACCIONES
