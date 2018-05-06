#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analizador.h"
#include <string.h>

void analiza();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

   QStringList tablaToken;
   tablaToken<<"ESTADO"<<"LEXEMA"<<"GRANEMA";
   ui->tableWidget->setHorizontalHeaderLabels(tablaToken);
   ui->tableWidget->setColumnWidth(0,80);
   ui->tableWidget->setColumnWidth(1,400);
   ui->tableWidget->setColumnWidth(2,400);
   ui->tableWidget->setColumnCount(3);

      //Aqui el codigo
      //Abrir el fichero (ruta estatica)
      archivo.open("codigo.lua",std::ios::in);

      //si fallo la apertura del archivo
      //mostrar informacion y salir
      if(archivo.fail()){
          archivo.open("codigo.lua",std::ios::out);
          archivo.close();
      }

      //mientras haya caracteres por leer

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(){
    sfileWindow = new selectFileWindow(); // Be sure to destroy your window somewhere
    sfileWindow->show();
}

void MainWindow::on_pushButton_clicked()
{
//    archivo.open ("codigo.lua");
    QString cadena = MainWindow::ui->textBrowser->toPlainText();

    std::string input;
    input = cadena.toStdString();
    std::ofstream out("codigo.lua");
    out << input;
    out.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    //ifstream archivo;   //control de flujo del archivo

    //inicializacion de estado
    edo = 0;

    //Abrir el fichero (ruta estatica)
    archivo.open("codigo.lua",ios::in);

    //si fallo la apertura del archivo
    //mostrar informacion y salir
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    //mientras haya caracteres por leer
    while(!archivo.eof()){

        //reinicializa estado y numero de simbolos
        edo=0;

        //se posiciona el puntero al inicio de lexema
        caux = &lexema[0];

        //mientras no se encuentra em estado terminal
        //analizar
        while(edo<=18){

            //si por alguna razon el automata no concluyo
            //pero esta en el fin de fichero rompe
            //if(c==-1)
              //  break;

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
                //si no esta en la lista de palabras reservadas
                //then edo = 101
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

        //Analizamos el resultado del analicis
        if(edo>=100&&edo<=132){

            elfounds++;

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(edo)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(lexema));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(Token(edo)));

            cout<<lexema<<endl;
            cout<<Token(edo)<<endl;


            //reinicializa la cadena lexema
            char *i;
            i = &lexema[0];
            while(i<=caux){
                *i=0x00;
                i++;
            }
            caux = &lexema[0];

        }else{
            caux = &lexema[0];
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(edo)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(""));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(Error(edo)));
        }

        if(c==-1)
            break;

    }

    //Cantidad de elementos encontrados
    cout<<"#=====================#"<<endl;
    cout<<"Elementos encontrados: "<<elfounds<<endl;
    cout<<"#=====================#"<<endl;

    //Cerramos el archivo
    archivo.close();
}
