#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QDir>
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
	QString name = ui->lineEdit_ClassName->text();
	if (name.isEmpty()) {
		QMessageBox::information(this, "Warning", "Please input classname first!");
		return ;
	}
	QString classname = name.at(0).toUpper() + name.right(name.size() - 1);

	creator.setClassName(classname);
	QStringList list = ui->textEdit->toPlainText().split("\n");
	if (list.isEmpty()) {
		QMessageBox::information(this, "Warning", "Please input at last one property!");
		return;
	}
	creator.clearNode();
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
	QString name = ui->lineEdit_ClassName->text();
	if (name.isEmpty()) {
		QMessageBox::information(this, "Warning", "Please input classname first!");
		return ;
	}
	QString classname = name.at(0).toUpper() + name.right(name.size() - 1);

	creator.setClassName(classname);
	QStringList list = ui->textEdit->toPlainText().split("\n");
	if (list.isEmpty()) {
		QMessageBox::information(this, "Warning", "Please input at last one property!");
		return;
	}
	creator.clearNode();
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

void MainWindow::on_pushButton_explorer_clicked()
{
	QString dir = QDir::currentPath();

	QProcess process;
	process.setEnvironment(QProcess::systemEnvironment());
	QStringList args;
	args <<dir.replace('/', '\\');
	qDebug() <<args;
	process.execute("explorer.exe", args);
}
