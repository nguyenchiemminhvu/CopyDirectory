#include "selectfolder.h"
#include "ui_selectfolder.h"

SelectFolder::SelectFolder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectFolder)
{
    ui->setupUi(this);
    constructLineEdit();
    constructDirModel();
    constructTreeView();
}

SelectFolder::~SelectFolder()
{
    delete ui;
}

void SelectFolder::constructLineEdit()
{
    ui->lineEdit->setEnabled(false);
}

void SelectFolder::constructDirModel()
{
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath("");
    dirModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
}

void SelectFolder::constructTreeView()
{
    ui->treeView->setModel(dirModel);
}

void SelectFolder::on_pushButton_clicked()
{
    //Accept the path
    emit getPath(path);
    close();
}

void SelectFolder::on_pushButton_2_clicked()
{
    //exit select folder form
    close();
}

void SelectFolder::on_treeView_clicked(const QModelIndex &index)
{
    ui->treeView->resizeColumnToContents(index.column());
    QFileInfo info = dirModel->fileInfo(index);
    path = info.absoluteFilePath();
    ui->lineEdit->setText(path);
}
