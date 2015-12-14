#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QChar>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encryptButton_clicked()
{
    setKey();
    setTargetFile();
    setDestFile();
    encrypt(key, targetFile, destFile);
}

void MainWindow::on_decryptButton_clicked()
{
    setKey();
    setTargetFile();
    setDestFile();
    decrypt(key, targetFile, destFile);
}


int MainWindow::encrypt(QString key, QString targetFile, QString destFile)
{
//key check
    int keyint = keyCheck(key);
//input file check
    fileCheck(targetFile);
    QFile inputFile(targetFile);

    qDebug() << targetFile;

//output file check
    fileCheck(destFile);
    QFile outputFile;
    outputFile.setFileName(destFile);

    inputFile.open(QIODevice::ReadWrite);
    outputFile.open(QIODevice::ReadWrite);

    QTextStream in(&inputFile);
    QString text = in.readAll();
    QTextStream out(&outputFile);

    int i=0;
    while(i < text.size())
    {
        char val = text.at(i).toLatin1();

        if (val >= 65 && val <= 122)
            {
                val = ((val + keyint) - 65) % 58 + 65;
            }
            out << val;
            i++;
    }
    inputFile.close();
    outputFile.close();
    return 0;
}
int MainWindow::decrypt(QString key, QString targetFile, QString destFile)
{
//key check
    int keyint = keyCheck(key);
//input file check
    fileCheck(targetFile);
    QFile inputFile(targetFile);
//output file check
    fileCheck(destFile);
    QFile outputFile;
    outputFile.setFileName(destFile);

    qDebug() << destFile;

    inputFile.open(QIODevice::ReadWrite);
    outputFile.open(QIODevice::ReadWrite);

    QTextStream in(&inputFile);
    QString text = in.readAll();

    QTextStream out(&outputFile);


    for(int i=0; i < text.size(); i++)
    {
        char val = text.at(i).toLatin1();

        if (val >= 65 && val <= 122)
            {
                val = (val - keyint - 65 + 58) % 58 + 65;
            }
            out << val;
    }
    inputFile.close();
    outputFile.close();
    return 0;
}
int MainWindow::keyCheck(QString key)
{
    int keyint = key.toInt();
    if(keyint == 0)
    {
        QMessageBox *errorBox = new QMessageBox();
        errorBox->critical(0,"Error","Not valid key!\nMust be integer greater than 0!");
        errorBox->setFixedSize(500,200);
        delete errorBox;
        return 1;
    }
    else
    {
        return keyint;
    }
}

int MainWindow::fileCheck(QString file)
{
    QFileInfo fileCheck(file);
    qDebug() <<file;
    if(!fileCheck.isFile() && !fileCheck.exists())
    {
        QMessageBox *errorBox = new QMessageBox();
        errorBox->critical(0,"Error","File does not exist!");
        errorBox->setFixedSize(500,200);
        delete errorBox;
        return 1;
    }
    else
        return 0;
}


void MainWindow::setTargetFile()
{
   targetFile = ui->targetFileLine->text();
}

void MainWindow::setDestFile()
{
    destFile = ui->destFileLine->text();
}

void MainWindow::setKey()
{
    key = ui->keyLine->text();
}

void MainWindow::on_targetBrowse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "*.txt");
    ui->targetFileLine->setText(fileName);
}

void MainWindow::on_destinationBrowse_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open File", QDir::homePath(), "*.txt");
    ui->destFileLine->setText(fileName);
}
