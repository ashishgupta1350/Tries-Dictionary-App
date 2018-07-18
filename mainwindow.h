#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
//#include<QPrinter>
//#include<QPrintDialog>
//#include"trie.cpp"
#include"trie.h"

namespace Ui {
class MainWindow; // how all the classes are arranged into a file
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_dictionaryButton_clicked();

    void on_checkButton_clicked();

    void on_correctButton_clicked();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile=""; // has the file name only and not the string of text within the file
    QString fileString="";
    Trie myTrie;
};

#endif // MAINWINDOW_H
