#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
using namespace std;
#include <algorithm>

string Lower(string s)
{
    string ret="";
    for(unsigned int i=0;i<s.length();i++)
    {
        if(s[i]>='A' and s[i]<='Z')
        {
            s[i]=s[i]-'A'+'a';

        }
        if( s[i]>='a' && s[i]<='z' )
            ret+=s[i];
    }
    ret+='\0';
    return ret;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setCentralWidget(ui->textEdit); // not sure if this is necessary
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    fileString.clear();
    ui->textEdit->setText(QString());  // simply clearing the strings and file into the application
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,"Open File");
    QFile file(fileName);// this will open the file
    currentFile=fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot Open File : "+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text=in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Save As");
    QFile file(fileName);
    currentFile=fileName;
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot Save File : "+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.close();
}

void MainWindow::on_dictionaryButton_clicked()
{
// Code brought from above, open file function and rest is refered from the documentation of QT. _ 18th July
    QString fileName=QFileDialog::getOpenFileName(this,"Open File");
    QFile file(fileName);// this will open the file
    currentFile=fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot Open File : "+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString allWords=in.readAll(); // all words has \n seperated words
    QStringList listOfWords=allWords.split('\n');

    // we have a list of words in our listOfWwords Q string, so now insert it into our trie data structure and start finding errors
    for(int i=0;i<listOfWords.size()-100;i++)
    {
       QString temp=listOfWords.at(i);
       string word = temp.toLocal8Bit().constData(); // it is working on the computer
//       cout<<word<<endl;
       word=Lower(word);
       myTrie.Insert(word);
    }
    file.close();
    ui->corrTextEdit->setPlainText(QString("The Dictionary is correctly set up!"));

    return;
}



void MainWindow::on_checkButton_clicked()
{
    // stack exchange rocks

    string wrongWords="";
    QRegExp sep("(\\s+|\n|,|" ")");
    QString textEditWords=ui->textEdit->toPlainText();
    ui->corrTextEdit->setText(textEditWords);
    QStringList listOfWords=textEditWords.split(" ");
    for(int i=0;i<listOfWords.size();i++)
    {
       QString temp=listOfWords.at(i);
       string word = temp.toLocal8Bit().constData(); // Stack Exchange
       word=Lower(word);
       bool isPresent=myTrie.Search(word);
       if(!isPresent)
       {
           wrongWords+=word+"\n";

       }
    }
    wrongWords+='\0';
//    QString myWrongWordsForDisplay=QString(wrongWords);
    QString myWrongWordsForDisplay = QString::fromStdString(wrongWords);
    ui->corrTextEdit->setText(myWrongWordsForDisplay);

}

void MainWindow::on_correctButton_clicked()
{
    // stack exchange rocks

    string wrongWords="";
    QRegExp sep("(\\s+|\n|,|" ")");
    QString textEditWords=ui->textEdit->toPlainText();
    ui->corrTextEdit->setText(textEditWords);
    QStringList listOfWords=textEditWords.split(" ");
    for(int i=0;i<listOfWords.size();i++)
    {
       QString temp=listOfWords.at(i);
       string word = temp.toLocal8Bit().constData(); // Stack Exchange
       word=Lower(word);
       bool isPresent=myTrie.Search(word);
       vector<string> suggestions;
       if(!isPresent)
       {

           if(word.length()>=4)
           {
               suggestions=myTrie.AdvanceSearch(word.substr(0,3)); // this takes the first 3 characters
               // ie takes a 3 character substring and does an advanced Search, it returns a vector full of words that
               // start with those 3 characters and then helps us choose the word
           }
           wrongWords+=word+"\n";
           wrongWords+="Suggestions: ";
           for(unsigned int i=0;i<(suggestions.size())%8;i++)
           {
               wrongWords+=suggestions[i];
               wrongWords+=" , ";
           }
//           wrongWords+=suggestions[suggestions.size()-1];
           wrongWords+="\n \n";
       }
    }
    wrongWords+='\0';
//    QString myWrongWordsForDisplay=QString(wrongWords);
    QString myWrongWordsForDisplay = QString::fromStdString(wrongWords);
    ui->corrTextEdit->setText(myWrongWordsForDisplay);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
