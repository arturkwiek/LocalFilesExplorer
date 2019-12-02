#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileInfoList>
#include <QDirIterator>

/******************************
 *
 * author: A. Kwiek
 * date: 2 12 2019r.
 * title Local File Explorer
 *
 * Search and show
 * -> catalogs
 *  -> files
 *      -> target filenames hit by template string
 *
 * ******************************/


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

void MainWindow::on_btnSearch_clicked()
{
    QString targetStr = ".o"; // What we search for
    QFileInfoList hitList; // Container for matches
    QString directory = "."; // Where to search
    QDirIterator it(directory, QDirIterator::Subdirectories);


    qDebug() << "Search files...";

    // Iterate through the directory using the QDirIterator
    while (it.hasNext()) {
        QString filename = it.next();
        QFileInfo file(filename);


        if (file.isDir()) { // Check if it's a dir
            qDebug() << filename;
            continue;
        }
        qDebug() << "\t" << filename;

        // If the filename contains target string - put it in the hitlist
        if (file.fileName().contains(targetStr, Qt::CaseInsensitive)) {
            hitList.append(file);
            qDebug() << "\t\thit target:" << file.baseName();
        }
    }

    foreach (QFileInfo hit, hitList) {
        qDebug() << hit.absoluteFilePath();
    }
}
