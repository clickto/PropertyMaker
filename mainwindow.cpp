#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
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


void MainWindow::on_pushButton_1_clicked()
{
	if (ui->lineEdit_ClassName->text().isEmpty()) {
		QMessageBox::information(this, "Warning", "Please input classname first!");
		return ;
	}
	creator.setClassName(ui->lineEdit_ClassName->text());
	QStringList list = ui->textEdit->toPlainText().split("\n");
	foreach (QString str, list) {
		creator.addNode(str.split(",").at(0), str.split(",").at(1));
	}
	creator.declaration();
	creator.define1();
}

void MainWindow::on_pushButton_2_clicked()
{
	if (ui->lineEdit_ClassName->text().isEmpty()) {
		QMessageBox::information(this, "Warning", "Please input classname first!");
		return ;
	}
	creator.setClassName(ui->lineEdit_ClassName->text());
	QStringList list = ui->textEdit->toPlainText().split("\n");
	foreach (QString str, list) {
		creator.addNode(str.split(",").at(0), str.split(",").at(1));
	}
	creator.declaration();
	creator.define2();
}
