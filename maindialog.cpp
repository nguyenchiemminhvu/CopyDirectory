#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
    constructLineEdit1();
    constructLineEdit2();
    constructCopyButton();
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::constructLineEdit1()
{
    ui->lineEdit->setDisabled(true);

    QFile file("file.txt");
    if(!file.open(QIODevice::Text | QIODevice::ReadWrite))
    {
        return;
    }

    QTextStream stream(&file);

    QString line = stream.readLine();
    ui->lineEdit->setText(line);
    file.close();
}

void mainDialog::constructLineEdit2()
{
    ui->lineEdit_2->setDisabled(true);

    QFile file("file.txt");
    if(!file.open(QIODevice::Text | QIODevice::ReadWrite))
    {
        return;
    }

    QTextStream stream(&file);
    stream.readLine();
    QString line = stream.readLine();
    ui->lineEdit_2->setText(line);
    file.close();
}

void mainDialog::constructCopyButton()
{
    if(ui->lineEdit->text() != "" && ui->lineEdit_2->text() != "")
    {
        ui->copyButton->setDisabled(false);
    }
    else
    {
        ui->copyButton->setDisabled(true);
    }
}

void mainDialog::on_lineEdit_textChanged(const QString &arg1)
{
    //Line edit 1 get changed
    if(ui->lineEdit->text().isEmpty())
    {
        ui->button1->setText("Add path");
        ui->copyButton->setEnabled(false);
    }
    else
    {
        ui->button1->setText("Edit path");
        if(!ui->lineEdit_2->text().isEmpty())
            ui->copyButton->setEnabled(true);
    }
}

void mainDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    //Line edit 2 get changed
    if(ui->lineEdit_2->text().isEmpty())
    {
        ui->button2->setText("Add path");
        ui->copyButton->setEnabled(false);
    }
    else
    {
        ui->button2->setText("Edit path");
        if(!ui->lineEdit->text().isEmpty())
            ui->copyButton->setEnabled(true);
    }
}

void mainDialog::on_commandLinkButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.facebook.com/nguyenchiemminhvu"));
}

void mainDialog::on_copyButton_clicked()
{
    //copy folder
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty())
        return;

    copyFolder();
    QMessageBox::information(this,"Copy","Done",QMessageBox::Ok);
}

void mainDialog::on_button1_clicked()
{
    //Select the source path
    SelectFolder* sl = new SelectFolder;
    connect(sl,SIGNAL(getPath(QString)),this,SLOT(receiptSourcePath(QString)));
    sl->show();
}

void mainDialog::on_button2_clicked()
{
    //Select the destination path
    SelectFolder* sl = new SelectFolder;
    connect(sl,SIGNAL(getPath(QString)),this,SLOT(receiptDestinationPath(QString)));
    sl->show();
}

void mainDialog::receiptSourcePath(const QString &path)
{
    ui->lineEdit->setText(path);
    source = ui->lineEdit->text();

    QFile file("file.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << source << endl << destination;
        file.close();
    }
}

void mainDialog::receiptDestinationPath(const QString &path)
{
    ui->lineEdit_2->setText(path);
    destination = ui->lineEdit_2->text();

    QFile file("file.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << source << endl << destination;
        file.close();
    }
}

void mainDialog::copyFolder()
{
    QDirIterator dirIterator(source,QDir::AllDirs | QDir::NoDotAndDotDot ,QDirIterator::Subdirectories);
    //get all sub directory in source directory
    while(dirIterator.hasNext())
    {
        QString temp = dirIterator.next();

        temp = makeDestPath(temp);
        QDir dir(temp);
    }

    QDirIterator fileIterator(source,QDir::Files, QDirIterator::Subdirectories);
    //get all file path in source directory
    while(fileIterator.hasNext())
    {
        QString temp = fileIterator.next();
        QFile file(temp);
        temp = makeDestPath(temp);

        if(QFile::exists(temp))
        {
            QFile::remove(temp);
        }

        file.copy(temp);
    }
}

QString mainDialog::cutPath(QString path)
{
    int nChar = source.length();
    QString temp = path.remove(0,nChar);
    return temp;
}

QString mainDialog::makeDestPath(QString &path)
{
    QString destPath = destination + cutPath(path);
    return destPath;
}
