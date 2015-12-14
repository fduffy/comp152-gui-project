#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setTargetFile();
    void setDestFile();
    void setKey();
    int keyCheck(QString key);
    int fileCheck(QString file);

private slots:
    void on_encryptButton_clicked();

    void on_decryptButton_clicked();

    void on_targetBrowse_clicked();

    void on_destinationBrowse_clicked();

private:
    Ui::MainWindow *ui;
    QString targetFile = "";
    QString destFile = "";
    QString key = "0";

    int encrypt(QString key, QString targetFile, QString destFile);
    int decrypt(QString key, QString targetFile, QString destFile);

};

#endif // MAINWINDOW_H
