#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creator.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:

	void on_pushButton_1_clicked();

	void on_pushButton_2_clicked();

	void on_pushButton_explorer_clicked();

private:
	Ui::MainWindow *ui;
	Creator creator;
};

#endif // MAINWINDOW_H
