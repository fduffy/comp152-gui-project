#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFileDialog>

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


void MainWindow::encrypt(int key, QString targetFile, QString destFile)
{
    QFile inputFile(targetFile);
    QFile outputFile(destFile);
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
                val = ((val + key) - 65) % 58 + 65;
            }
            out << val;
            i++;
    }
    inputFile.close();
    outputFile.close();
}
void MainWindow::decrypt(int key, QString targetFile, QString destFile)
{
    QFile inputFile(targetFile), outputFile(destFile);
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
                val = (val - key - 65 + 58) % 58 + 65;
            }
            out << val;
    }
    inputFile.close();
    outputFile.close();
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
    key = ui->keyLine->text().toInt();
}

void MainWindow::on_targetBrowse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "*.txt");
    ui->targetFileLine->setText(fileName);
}

void MainWindow::on_destinationBrowse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "*.txt");
    ui->destFileLine->setText(fileName);
}
