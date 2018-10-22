#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analizador.h"
#include "sintaxis.h"
#include <string.h>
#include "QMessageBox"

//Variables globales para comunicar lexico con sitactico
static int Ltoken;
static char* Llexema;

static const char* ARCHIVO = "/home/shikami/codigo.lex";

//Metodo para cargar el archivo al editor
void MainWindow::CargarArchivoAlEditor(){

   //Abrir el fichero (ruta estatica)
   archivo.open(ARCHIVO,std::ios::in);

   //si fallo la apertura del archivo
   //mostrar informacion y salir
   if(archivo.fail()){
       archivo.open(ARCHIVO,std::ios::out);
       archivo.close();
   }

   //lee el archivo y lo coloca en nuestro 'editor'
   QString string;
   QChar car;
   while(!archivo.eof()){
     car = archivo.get();
     if(car!=-1){
      string.append(car);
     }else{
       break;
     }
    }


   archivo.close();
   ui->textBrowser->setText(string);
}

//inicializacion
void MainWindow::Init(){

    //abre archivo
    archivo.open(ARCHIVO,ios::in);

    //prepara pila de ejecucion
    ExecucionStack.push('$'); //$ [fin de fichero]
    ExecucionStack.push(1);   //produccion program

    //mostrar informacion y salir
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    //cargar archivo al editor de textos
    MainWindow::CargarArchivoAlEditor();
    MainWindow::Init();

    //Preparar Tabla
    QStringList tablaToken;
    tablaToken<<"ESTADO"<<"LEXEMA"<<"GRANEMA";
    ui->tableWidget->setHorizontalHeaderLabels(tablaToken);
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->setColumnWidth(1,400);
    ui->tableWidget->setColumnWidth(2,400);
    ui->tableWidget->setColumnCount(3);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//metodo para seleccionar un archivo
//de manera dinamica, pendiente implementacoin
void MainWindow::openFile(){
    sfileWindow = new selectFileWindow(); // Be sure to destroy your window somewhere
    sfileWindow->show();
}

//METODO GUARDAR ARCHIVO del editor
void MainWindow::on_pushButton_clicked()
{
    //archivo.open ("codigo.lua");
    QString cadena = MainWindow::ui->textBrowser->toPlainText();

    std::string input;
    input = cadena.toStdString();
    std::ofstream out("codigo.lex");
    out << input;
    out.close();
}

//Metodo que trae el siguiente token
//Analizador Lexico, un token a la vez
void MainWindow::dameToken(){

    //inicializacion de estado
    edo = 0;

    //inicializacion de cadenas
    char *i;
    i = &lexema[0];
    while(i<=caux){
        *i=0x00;
        i++;
    }
    caux = &lexema[0];

    if(archivo.eof()){
        Ltoken = -1;
    }

    //mientras haya caracteres por leer
    while(!archivo.eof()&&edo<100){

        //se posiciona el puntero al inicio de lexema
        caux = &lexema[0];

        //mientras no se encuentra em estado terminal
        //analizar
        while(edo<=18){

            //obtenemos siguiente caracter
            c = archivo.get();

            //guardar el caracter actual en la cadena lexema
            if(c!=-1){
                if(c!=0x09&&c!=0x0A&&c!=0x20){
                    *caux  = c;
                    caux = caux + 1;
                }
                col = relaciona(c);
            }else{
                //fin de fichero, marcamos como diferente
                col = 32;
            }

            //debug
            //cout<<"sym:"<<c<<",edo:"<<edo<<",col:"<<col<<",goto:"<<TTABLE[edo][col]<<endl;

            //Avanza al siguiente estado
            edo = TTABLE[edo][col];
        }

        //ESTOS SON LOS ELEMENTOS QUE NO CONCLUYEN DIRECTAMENTE
        switch(edo){
            case PALABRA_RESERVADA:
                if(!esLetra(c))popcharacter(c);
                break;
            case IDENTIFICADOR:
                if(!(esNumero(c)||esLetra(c)||esGuionBajo(c)))popcharacter(c);
                break;
            case CONSTANTE_NUMERICA_ENTERA:
            case CONSTANTE_NUMERICA_REAL:
            case CONSTANTE_NUMERICA_NC:
                if(!esNumero(c)&&c!=-1)popcharacter(c);
                break;
            case ASIGNACION:
            case MAYOR_QUE:
            case MENOR_QUE:
            case NOT:
                popcharacter(c);
                break;
        }

        //Analizamos el resultado del analisis
        if(edo>=100&&edo<=132){
            elfounds++;

            Ltoken = edo;
            Llexema = lexema;

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(Ltoken)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(Llexema));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(Token(edo)));

        }else{
            caux = &lexema[0];
        }
        if(c==-1){
            Ltoken = -1;
            break;
        }
    }
}

//Relaciona tokens de lexico con columnas de sintactico
int MainWindow::relacionaAlex(int tkn){
    switch(tkn){
        case 101:
            return 1000;
        case 102:
            return 1001;
        case 103:
            return 1002;
        case 104:
            return 1003;
        case 105:
            return 1004;
        case 106:
            return 1005;
        case 107:
            return 1006;
        case 108:
            return 1007;
        case 109:
            return 1008;
        case 110:
            return 1009;
        case 111:
            return 1010;
        case 112:
            return 1011;
        case 113:
            return 1012;
        case 114:
            return 1013;
        case 115:
            return 1014;
        case 116:
            return 1015;
        case 117:
            return 1016;
        case 118:
            return 1017;
        case 119:
            return 1018;
        case 120:
            return 1019;
        case 121:
            return 1020;
        case 122:
            return 1021;
        case 123:
            return 1022;
        case 124:
            return 1023;
        case 125:
            return 1024;
        case 126:
            return 1025;
        case 127:
            return 1026;
        case 128:
            return 1027;
        case 129:
            return 1028;
        case 130:
            return 1029;
        case 131:
            return 1030;
        case 132:
            return 1031;
        case 100:
            if(QString::fromUtf8(Llexema)  == "constructor") return 1032;
            if(QString::fromUtf8(Llexema)  == "int") return 1033;
            if(QString::fromUtf8(Llexema)  == "float") return 1034;
            if(QString::fromUtf8(Llexema)  == "char") return 1035;
            if(QString::fromUtf8(Llexema)  == "string") return 1036;
            if(QString::fromUtf8(Llexema)  == "commit") return 1037;
            if(QString::fromUtf8(Llexema)  == "end") return 1038;
            if(QString::fromUtf8(Llexema)  == "if") return 1039;
            if(QString::fromUtf8(Llexema)  == "endif") return 1040;
            if(QString::fromUtf8(Llexema)  == "else") return 1041;
            if(QString::fromUtf8(Llexema)  == "while") return 1042;
            if(QString::fromUtf8(Llexema)  == "endwhile") return 1043;
            if(QString::fromUtf8(Llexema)  == "do") return 1044;
            if(QString::fromUtf8(Llexema)  == "dowhile") return 1045;
            if(QString::fromUtf8(Llexema)  == "enddo") return 1046;
            if(QString::fromUtf8(Llexema)  == "read") return 1047;
            if(QString::fromUtf8(Llexema)  == "write") return 1048;
            return 1000; //es identificador
    }
}

void MainWindow::AnalizaPaso(){

    //analizar nuevo token
    MainWindow::dameToken(); // Se Guarda en varaible global Ltoken y Llexema

    //Analizar estado de terminacion, si lo hay
    if(Ltoken==-1){
        if(ExecucionStack.top()=='$'){
            ExecucionStack.pop();
            QMessageBox msgBox;
            msgBox.setText("Analisis completado correctamente! la sintaxis es correcta");
            msgBox.exec();
        }else{
            QMessageBox msgBox;
            msgBox.setText("Analisis terminado incorrectamente, se llego al fin de fichero y no termino de analizar");
            msgBox.exec();
        }
        return;
    }

    //regresa elemento correspondiente a sintactico (>=1000)
    int Stoken = MainWindow::relacionaAlex(Ltoken);

    //obtiene columna
    int rcol = Stoken-1000;

    bool found = false;

    while(!found){

        //imprimirStack(ExecucionStack);

        if(ExecucionStack.top()>=1000){

            //es elemento terminal
            if(ExecucionStack.top()==Stoken){
                cout<<"Encontrado: "<<Stoken<<endl;
                ExecucionStack.pop();
                //cout<<"elemento encontrado, eliminado"<<endl;
                found = true;
            }else{
                //es accion (traduccion
                if(ExecucionStack.top()>=2000&&ExecucionStack.top()<=2500){

                    //TODO EjecutarAccion(ExecucionStack.pop())
                    cout<<"ACCION ENCONTRADA: "<<ExecucionStack.top()<<endl;
                    ExecucionStack.pop();
//                    break;

                }else{
                    cout<<"ERROR DE SINTAXIS, no coinciden los tokens"<<endl;
                    cout<<"En pila: "<<ExecucionStack.top()<<endl;
                    cout<<"Encontrado: "<<Stoken<<endl;
                    break;
                }
            }

        }else{

            //es elemento no terminal

            //cout<<"prouccion encontrada, analizando"<<endl;

            //cout<<ExecucionStack.top()-1<<","<<rcol<<endl;
            int elem = MATRIZ_PREDICTIVA[ExecucionStack.top()-1][rcol];

            //sustituye produccion por el contenido inverso de la produccion
            if(elem!=-1){

                //elimina la produccion
                ExecucionStack.pop();

                //insertar producciones a la pila
                for(int i=8; i>=0;i--){

                    int elem2 = MATRIZ_DE_PRODUCCIONES[(elem-1)][i];

                    //vacio
                    if(elem2==-1){
//                        cout<<"Encontrado:"<<"<vacio>";
                        break;
                    }else{
                        //ignorar el relleno
                        if(elem2!=0){
                            ExecucionStack.push(elem2);
//                            cout<<" -- "<<elem2<<" -- ";
                        }
                    }
                }
                cout<<endl;

            }else{
                //error de sintaxis
                cout<<elem<<endl;
                QMessageBox msgBox;
                msgBox.setText("Error de sintaxis");
                msgBox.exec();
                break;
            }

        }

        //imprimir pila
        imprimirStack();

    }
}

//Metodos de la GUI

void MainWindow::on_pushButton_3_clicked(){
    AnalizaPaso();
}

void MainWindow::on_pushButton_2_clicked()
{
    while(Ltoken!=-1){
        AnalizaPaso();
    }

}
