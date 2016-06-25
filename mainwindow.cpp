#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(QString::fromUtf8("属性生成器"));
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
		QString str1, str2;
		str1 = str.split(",").at(0);
		str2 = str.split(",").at(1);
		str1 = str1.simplified();
		str2 = str2.simplified();
		creator.addNode(str1, str2);
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
		QString str1, str2;
		str1 = str.split(",").at(0);
		str2 = str.split(",").at(1);
		str1 = str1.simplified();
		str2 = str2.simplified();
		creator.addNode(str1, str2);
	}
	creator.declaration();
	creator.define2();
}
