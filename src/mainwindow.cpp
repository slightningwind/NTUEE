#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rotorsystem.h"
#include "functions.h"
#include <QMessageBox>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->Encrypt_button, &QRadioButton::clicked, this, &MainWindow::setE);
    QObject::connect(ui->Decrypt_button, &QRadioButton::clicked, this, &MainWindow::setD);
    QObject::connect(ui->Run_button, &QPushButton::clicked,this, &MainWindow::modedef);
    QObject::connect(this, &MainWindow::runE, this, &MainWindow::Encrypt);
    QObject::connect(this, &MainWindow::runD, this, &MainWindow::Decrypt);
    QObject::connect(this, &MainWindow::finish, this, &MainWindow::outputdisplay);
    QObject::connect(ui->ClearAll_button, &QPushButton::clicked,this, &MainWindow::clearall);
    QObject::connect(ui->ClearText_button, &QPushButton::clicked,this, &MainWindow::cleartext);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setE(){
    mode=1;
}

void MainWindow::setD(){
    mode=0;
}

bool MainWindow::validinput(){
    int k=rotors.length();
    for(int i=0;i<k;i++){
        if(ltn(rotors[i])>25||ltn(rotors[i])<0){
            return 0;
        }
    }
    k=positions.length();
    for(int i=0;i<k;i++){
        if(ltn(positions[i])>25||ltn(positions[i])<0){
            return 0;
        }
    }
    k=secret.length();
    for(int i=0;i<k;i++){
        if(ltn(secret[i])>25||ltn(secret[i])<0){
            return 0;
        }
    }
    k=usertext.length();
    for(int i=0;i<k;i++){
        if(ltn(usertext[i])>25||ltn(usertext[i])<0){
            return 0;
        }
    }
    return 1;
}

void MainWindow::modedef(){
    rotors=ui->Rotors_line->text().toStdString();
    positions=ui->Positions_line->text().toStdString();
    secret=ui->Secret_line->text().toStdString();
    usertext=ui->Text_input->toPlainText().toStdString();
    int rl=rotors.length(),pl=positions.length(),sl=secret.length();
    if(mode==-1||rotors==""||positions==""||secret==""||usertext==""){
        QMessageBox err;
        err.setText("Oops, you might have missed something......");
        err.setWindowTitle("Error");
        err.exec();
    }
    else if(MainWindow::validinput()==0){
        QMessageBox err;
        err.setText("Invalid input. \n (Inputs should be lowercase letters without any space.)");
        err.setWindowTitle("Error");
        err.exec();
    }
    else if(rl!=pl||rl!=sl||sl!=pl){
        QMessageBox err;
        err.setText("The length of \"Rotors\", \"Positions\" and \"Secret Code\" should be equal.");
        err.setWindowTitle("Error");
        err.exec();
    }
    else if(mode==1){
        emit runE();
    }
    else if(mode==0){
        emit runD();
    }
}

void MainWindow::Encrypt(){
    rotorsystem sys(rotors);
    sys.build_rotors();
    sys.setpos(positions);
    esecret=sys.encryption(secret);
    sys.setpos(secret);
    output=sys.encryption(usertext);
    emit finish();
}
void MainWindow::Decrypt(){
    rotorsystem sys(rotors);
    sys.build_rotors();
    sys.setpos(positions);
    esecret=sys.encryption(secret);
    sys.setpos(esecret);
    output=sys.encryption(usertext);
    emit finish();
}
void MainWindow::outputdisplay(){
    switch(mode){
        case 1:
        ui->Output_display->setPlainText("Encrypted secret code:");
        break;
        case 0:
        ui->Output_display->setPlainText("Decrypted secret code:");
        break;
    }
    ui->Output_display->appendPlainText(QString::fromStdString(esecret));
    ui->Output_display->appendPlainText("");
    switch(mode){
        case 1:
        ui->Output_display->appendPlainText("Encrypted text:");
        break;
        case 0:
        ui->Output_display->appendPlainText("Decrypted text:");
        break;
    }
    ui->Output_display->appendPlainText(QString::fromStdString(output));
}

void MainWindow::clearall(){
    ui->Positions_line->clear();
    ui->Rotors_line->clear();
    ui->Secret_line->clear();
    ui->Text_input->clear();
    ui->Output_display->clear();
}
void MainWindow::cleartext(){
    ui->Secret_line->clear();
    ui->Text_input->clear();
    ui->Output_display->clear();
}



