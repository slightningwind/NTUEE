#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int mode=-1;
    std::string rotors,positions,secret,usertext,esecret,output;
    bool validinput();

signals:
    void runE();
    void runD();
    void finish();

public slots:
    void setE();
    void setD();
    void modedef();
    void Encrypt();
    void Decrypt();
    void outputdisplay();
    void cleartext();
    void clearall();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
