#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

//int       4000
//string    4001
//float     4002
//bool      4003

//* -> apuntador

// =============== TABLA DE SIMBOLOS VARIABLES
struct tsv{
    int dir_var;        //direccion
    string  desc;       //descripcion
    int tipo;
    int apram;
    struct tsv *siguiente;
};

//primer elemento de la tabla
tsv *lista_tsv;
tsv *fin_tsv;

//contador de la tabla de simbolos
int simbolos_contador = 0;

tsv* buscarEnTsv(string id){
    if(lista_tsv==nullptr){
        return nullptr;
    }else{
        tsv* tmp = lista_tsv;
        do{
            if(tmp->desc==id){
                return tmp;
            }else{
                tmp = tmp->siguiente;
            }
        }while(tmp!=nullptr);
    }
    return nullptr;
    cout<<"ERROR, variable no declarada";
}

tsv* darAltaDeId(string id){

    //buscar si no se ha declarado
    if(buscarEnTsv(id)==nullptr){

        //si no se ha declarado: dar de alta
        tsv *nuevo_elemento = new tsv();

        nuevo_elemento->desc=id;
        nuevo_elemento->dir_var=simbolos_contador;
        simbolos_contador++;

        if(lista_tsv==nullptr){
            //la lista esta vacia
            lista_tsv = nuevo_elemento;
            fin_tsv = nuevo_elemento;
        }else{
            //la lista tiene algun elemento
            fin_tsv->siguiente = nuevo_elemento;
            fin_tsv = nuevo_elemento;
        }

        return nuevo_elemento;


    }else{
        cout<<"ERROR, variable ya declarada";
    }

    return nullptr;

}

// =============== TABLA DE SIMBOLOS VARIABLES
struct tsc{
    int dir_con;        //direccion
    string  desc;       //descripcion
    int tipo;
    int apram;
    struct tsc *siguiente;
};

//primer elemento de la tabla
tsc *lista_tsc;
tsc *fin_tsc;

//contador de la tabla de simbolos
int simbolos_contador_const = 0;

tsc* darDeAltaConstante(string id, int tipo){
    tsc *nuevo_elemento = new tsc();

    nuevo_elemento->desc=id;
    nuevo_elemento->dir_con=simbolos_contador_const;
    nuevo_elemento->tipo=tipo;

    simbolos_contador_const++;

    if(lista_tsc==nullptr){
        //la lista esta vacia
        lista_tsc = nuevo_elemento;
        fin_tsc = nuevo_elemento;
    }else{
        //la lista tiene algun elemento
        fin_tsc->siguiente = nuevo_elemento;
        fin_tsc = nuevo_elemento;
    }

    return nuevo_elemento;
}


tsc* buscarEnTsc(string id,int tipo){

    if(lista_tsc==nullptr){
        darDeAltaConstante(id,tipo);
    }else{
        tsc* tmp = lista_tsc;
        do{
            if(tmp->desc==id){
                //si la encontro, retorna el elemento
                return tmp;
            }else{
                tmp = tmp->siguiente;
            }
        }while(tmp!=nullptr);
    }

    //si llega aqui, no encontro la constante
    return darDeAltaConstante(id,tipo);
}

//tabla de constantes
//NOTAS
//int dir = buscarEnTsv("res")->dir_var;
