#ifndef SELECTFOLDER_H
#define SELECTFOLDER_H

#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui {
class SelectFolder;
}

class SelectFolder : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectFolder(QWidget *parent = 0);
    ~SelectFolder();

signals:
    void getPath(QString);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::SelectFolder *ui;
    QFileSystemModel* dirModel;
    QString path;

    void constructLineEdit();
    void constructDirModel();
    void constructTreeView();
};

#endif // SELECTFOLDER_H
