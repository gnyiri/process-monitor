#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_process_tree_model = new ProcessTreeModel(this);
    ui->m_process_tree->setModel(m_process_tree_model);
    ui->m_process_tree->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
