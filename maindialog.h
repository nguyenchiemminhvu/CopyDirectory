#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#pragma once

#include "selectfolder.h"
#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QDirIterator>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

public slots:
    void receiptSourcePath(const QString& path);
    void receiptDestinationPath(const QString& path);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_commandLinkButton_clicked();
    void on_copyButton_clicked();
    void on_button1_clicked();
    void on_button2_clicked();

private:
    Ui::mainDialog *ui;
    QString source;
    QString destination;

    void constructLineEdit1();
    void constructLineEdit2();
    void constructCopyButton();
    void copyFolder();
    QString cutPath(QString path);
    QString makeDestPath(QString& path);
};

#endif // MAINDIALOG_H
