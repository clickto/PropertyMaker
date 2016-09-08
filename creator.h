#ifndef CREATOR_H
#define CREATOR_H
#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QList>
#include <QStringList>

class Creator
{
public:
	void setClassName(QString name);
	void addNode(QString type, QString name);
	void declaration();
	void define1();
	void define2();

private:
	QString classname;
	QList<QStringList> list;
};

#endif // CREATOR_H
