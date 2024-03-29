#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "fstream"
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pixmap.fill(Qt::white);
    n_link=0;
    ifstream fs("jordy2.0.txt",ios::binary);
        string dir,name,labels;
        int _y=0,nl=0;
        while( fs.read( (char *) & _y, sizeof( int )) ){ //a terminar el bloc de notas
            string *_labels=new string[30];
            char* f0=new char[_y+2]; //el +2 es por el tamaño del string q ocupa y su \0
            fs.read( f0, _y );
            f0[_y]=0;
            dir=f0;
            delete []f0;

            fs.read( (char *) & _y, sizeof( int ));
            char* f1=new char[_y+2];
            fs.read( f1, _y );
            f1[_y]=0;
            name=f1;
            delete []f1;

            fs.read( (char *) & nl, sizeof( int ));
            for(int i=0;i<nl;i++){
                fs.read( (char *) & _y, sizeof( int ));
                char* f2=new char[_y+2];
                fs.read( f2, _y );
                f2[_y]=0;
                labels=f2;
                _labels[i]=labels;
                delete []f2;
            }

            Image im(name,dir,_labels);
            qDebug()<<QString::fromStdString(name);
            qDebug()<<QString::fromStdString(dir);
            int mm=0;
            while(_labels[mm]!="\0"){
                qDebug()<<QString::fromStdString(_labels[mm]);
                mm++;
            }
            li.push_back(im);

        }

    if(li.begin()!=NULL){

        it_p=li.begin();
        Image imag=*it_p;
        QPixmap a( QString::fromStdString(imag.date_path()+imag.date_name()) );
        pixmap=a;
        ui->text_labels_2->setText(" ");
        ui->text_labels_2->append("Nombre:");
        ui->text_labels_2->append( QString::fromStdString(imag.date_name()) );
        ui->text_labels_2->append("Path:");
        ui->text_labels_2->append( QString::fromStdString(imag.date_path()) );
        ui->text_labels_2->append("Labels:");
        int i=0;
        while( imag.date_label()[i] != "\0" ){
            ui->text_labels_2->append(QString::fromStdString(imag.date_label()[i]));
            i++;
        }
    }
    else {
        it_p=NULL;
        QPixmap a;
        pixmap=a;
    }
    ui->label_image->setPixmap(pixmap);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_prev_clicked()
{
    pixmap.fill(Qt::white);
    --it_p;
    Image imag=*it_p;
    QPixmap z(QString::fromStdString(imag.date_path()+imag.date_name()));
    pixmap=z;
    ui->text_labels_2->setText(" ");
    ui->text_labels_2->append("Nombre:");
    ui->text_labels_2->append( QString::fromStdString(imag.date_name()) );
    ui->text_labels_2->append("Path:");
    ui->text_labels_2->append( QString::fromStdString(imag.date_path()) );
    ui->text_labels_2->append("Labels:");
    int i=0;
    while( imag.date_label()[i] != "\0" ){
        ui->text_labels_2->append(QString::fromStdString(imag.date_label()[i]));
        i++;
    }

    ui->label_image->setPixmap(pixmap);

}

void MainWindow::on_button_next_clicked()
{
    pixmap.fill(Qt::white);
    ++it_p;
    Image imag=*it_p;
    QPixmap z(QString::fromStdString(imag.date_path()+imag.date_name()));
    pixmap=z;
    ui->text_labels_2->setText(" ");
    ui->text_labels_2->append("Nombre:");
    ui->text_labels_2->append( QString::fromStdString(imag.date_name()) );
    ui->text_labels_2->append("Path:");
    ui->text_labels_2->append( QString::fromStdString(imag.date_path()) );
    ui->text_labels_2->append("Labels:");
    int i=0;
    while( imag.date_label()[i] != "\0" ){
        ui->text_labels_2->append(QString::fromStdString(imag.date_label()[i]));
        i++;
    }

    ui->label_image->setPixmap(pixmap);
}

void MainWindow::on_pushback_clicked()
{
    string *_labels=new string[30];
    QString qstrname=ui->line_name->text();
    QString qstrpath=ui->line_path->text();
    QString qstrlabels=ui->text_labels->toPlainText();
    int j=0;
    int m=0;
    for(int i=0;i<qstrlabels.size();i++){
        if(qstrlabels[i]=="\n"){
            if(j==0){
                string qstrlabel=qstrlabels.toStdString();
                QString aux=QString::fromStdString(qstrlabel.substr(j,i-j));
                j=i;
                _labels[m]=aux.toStdString();
                m++;
                ui->text_labels_2->append(aux);
            }
            else{
                string qstrlabel=qstrlabels.toStdString();
                QString aux=QString::fromStdString(qstrlabel.substr(j+1,i-j-1));
                j=i;
                _labels[m]=aux.toStdString();
                m++;
                ui->text_labels_2->append(aux);
            }
        }
    }
    Image a(qstrname.toStdString(),qstrpath.toStdString(),_labels);
    li.push_back(a);
    n_link++;
    if(it_p==NULL)it_p=li.begin();
    Image* aux_imag=&*it_p;
    bst_li.insert(aux_imag);
    qDebug()<<"DEBE HABER INSERTADO";

    qDebug()<<QString::fromStdString(a.date_name());
    qDebug()<<QString::fromStdString(a.date_path());
    int mm=0;
    while(_labels[mm]!="\0"){
        qDebug()<<QString::fromStdString(a.date_label()[mm]);
        mm++;
    }
    qDebug()<<QString::fromStdString(a.date_path()+a.date_name());
}

void MainWindow::on_pushfront_clicked()
{
/*
    string *_labels=new string[30];
    QString qstrname=ui->line_name->text();
    QString qstrpath=ui->line_path->text();
    QString qstrlabels=ui->text_labels->toPlainText();
    int j=0;
    int m=0;
    for(int i=0;i<qstrlabels.size();i++){
        if(qstrlabels[i]=="\n"){
            if(j==0){
                string qstrlabel=qstrlabels.toStdString();
                QString aux=QString::fromStdString(qstrlabel.substr(j,i-j));
                j=i;
                _labels[m]=aux.toStdString();
                m++;
            }
            else{
                string qstrlabel=qstrlabels.toStdString();
                QString aux=QString::fromStdString(qstrlabel.substr(j+1,i-j-1));
                j=i;
                _labels[m]=aux.toStdString();
                m++;
            }
        }
    }
    Image a(qstrname.toStdString(),qstrpath.toStdString(),_labels);
    li.push_front(a);
*/
}

void MainWindow::on_save_clicked()
{

    ofstream fs ("jordy2.0.txt");
    linked_list<Image>::iterator it;
    it=li.begin();
    int as=0;
    Image im;
    string str;
    int _y=0;
    while( as!=n_link){
        im=*it;
        str=im.date_path();
        _y=str.size();
        fs.write( (char *) &_y, sizeof( int ) ); //tamaño del string
        fs.write(str.c_str(),_y);

        str=im.date_name();
        _y=str.size();
        fs.write( (char *) &_y, sizeof( int ) );
        fs.write(str.c_str(),_y);

        int i=0;
        while(im.date_label()[i] != "\0"){
            i++;
        }
        fs.write( (char *) &i, sizeof( int ) ); //total de labels a leer
        i=0;
        while( im.date_label()[i] != "\0" ){
            str=im.date_label()[i];
            _y=str.size();
            fs.write( (char *) &_y, sizeof( int ) ); //tamaño del string
            fs.write(str.c_str(),_y);
            i++;
        }
        as++;
        ++it;
    }
    fs.close();


}

void MainWindow::on_Delete_clicked()
{
    li.remove(it_p.nod());
    qDebug()<<"salio";
    ofstream fs ("aiudaa.txt");
    linked_list<Image>::iterator it2;

    it2=li.begin();
    int as=0;
    Image im;
    string str;
    int _y=0;
    while(as!=n_link){
        im=*it2;
        str=im.date_path();
        _y=str.size();
        fs.write( (char *) &_y, sizeof( int ) ); //tamaño del string
        fs.write(str.c_str(),_y);

        str=im.date_name();
        _y=str.size();
        fs.write( (char *) &_y, sizeof( int ) );
        fs.write(str.c_str(),_y);

        int i=0;
        while(im.date_label()[i] != "\0"){
            i++;
        }
        fs.write( (char *) &i, sizeof( int ) ); //total de labels a leer
        i=0;
        while( im.date_label()[i] != "\0" ){
            str=im.date_label()[i];
            _y=str.size();
            fs.write( (char *) &_y, sizeof( int ) ); //tamaño del string
            fs.write(str.c_str(),_y);
            i++;
        }
        as++;
        ++it2;
    }
    fs.close();
    remove("jordy2.0.txt");
    rename("aiudaa.txt","jordy2.0.txt");

}



void MainWindow::on_Reserva_clicked()
{
    DIR * direct;
    string dir="Reserva";
    if(direct=opendir(dir.c_str())){
        closedir(direct); //encontro
    }
    else{
        string direccion_total="Reserva";
        if( mkdir(direccion_total.c_str())==0 )qDebug()<<"\nCreada con exito";
        else qDebug()<<"\nHa ocurrido un error";

    }                      //no encontro
    FILE * archivo;
    string cadena,direccion_total,destino="Reserva";

    ifstream fs("jordy2.0.txt",ios::binary);

        string name,labels;
        int _y=0,nl=0;
        while( fs.read( (char *) & _y, sizeof( int )) ){ //a terminar el bloc de notas
            char* f0=new char[_y+2]; //el +2 es por el tamaño del string q ocupa y su \0
            fs.read( f0, _y );
            f0[_y]=0;
            direccion_total=f0;
            qDebug()<<QString::fromStdString(direccion_total);
            delete []f0;

            fs.read( (char *) & _y, sizeof( int ));
            char* f1=new char[_y+2];
            fs.read( f1, _y );
            delete []f1;

            fs.read( (char *) & nl, sizeof( int ));
            for(int i=0;i<nl;i++){
                fs.read( (char *) & _y, sizeof( int ));
                char* f2=new char[_y+2];
                fs.read( f2, _y );
                delete []f2;
            }

            if(archivo=fopen(direccion_total.c_str(), "r")){
                cadena="copy "+ direccion_total + " " + destino;
                system(cadena.c_str());
            }

        }
}


void MainWindow::on_Search_name_clicked()
{
    string *_labels=new string[30];
    QString qstrname=ui->line_name->text();
    QString qstrpath=ui->line_path->text();
    QString qstrlabels=ui->text_labels->toPlainText();
    int j=0;
    int m=0;
    for(int i=0;i<qstrlabels.size();i++){
        if(qstrlabels[i]=="\n"){
            if(j==0){
                qDebug()<<"entro";
                qDebug()<<i;
                string qstrlabel=qstrlabels.toStdString();
                QString aux=QString::fromStdString(qstrlabel.substr(j,i-j));
                j=i;
                _labels[m]=aux.toStdString();
                m++;
            }
            else{
                string qstrlabel=qstrlabels.toStdString();
                QString aux=QString::fromStdString(qstrlabel.substr(j+1,i-j-1));
                j=i;
                _labels[m]=aux.toStdString();
                m++;

            }
        }
    }
    Image a(qstrname.toStdString(),qstrpath.toStdString(),_labels);
    Image* aux_imag=&a;
    if(bst_li.find(aux_imag)==true) qDebug()<<"Lo encontro";
    else {
        qDebug()<<"No lo encontro";
    }

}
