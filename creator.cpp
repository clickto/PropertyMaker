#include "creator.h"
#include <QDebug>

void Creator::setClassName(QString name)
{
	classname = name;
}
void Creator::addNode(QString type, QString name)
{
	QStringList str;
	str<<type<<name;
	list.append(str);
}
void Creator::clearNode()
{
	list.clear();
}
void Creator::declaration()
{
	QString name = QString("%1.h").arg(classname);
	QFile file(name);
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() <<__FILE__<<__LINE__<<"open file failed.";
		return ;
	}
	QTextStream out(&file);

	out << QString ("#ifndef %1_H").arg(classname.toUpper())<<"\r\n";
	out << QString ("#define %1_H").arg(classname.toUpper()) <<"\r\n";
	out << QString ("#include<QObject>\r\n");
	out << QString ("class %1Private;").arg(classname)<<"\r\n";
	out << QString ("class %1 : public QObject {").arg(classname) << "\r\n";
	out << "	Q_OBJECT" <<"\r\n";

	//声明属性
	//Q_PROPERTY(int name READ name WRITE setName NOTIFY nameChanged)
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("	Q_PROPERTY(%1 %2 READ %3 WRITE set%4 NOTIFY %5Changed)").arg(type).arg(name).arg(name).arg(QString("%1%2").arg(name.at(0).toUpper()).arg(name.mid(1, name.size()))).arg(name) << "\r\n";
	}

	//声明属性的读写函数
	out << "public:"<<"\r\n";
	out << QString("	%1(QObject *parent=0);").arg(classname)<<"\r\n";
	out << QString("	~%1();").arg(classname)<<"\r\n";
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("	%1 %2() const;").arg(type).arg(name) <<"\r\n";
	}
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out << QString ("	void set%1%2(%3 value);").arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type) << "\r\n";
	}

	out << "	Q_INVOKABLE void upParams()\n	{\n		emit paramsChanged();\n	}"<<"\r\n";

	//声明属性的改变信号
	out << "signals:"<<"\r\n";
	foreach(QStringList node, list) {
		QString name = node.at(1);
		out <<QString ("	void %1Changed();").arg(name) << "\r\n";
	}
	out <<QString ("	void paramsChanged();") <<"\r\n";
	out <<QString ("private:\r\n	%1Private *m_dptr;\r\n").arg(classname);

	out <<"};"<<"\r\n";
	out <<QString ("#endif //%1_H").arg(classname.toUpper()) <<"\r\n";
	file.close();
}


void Creator::define1()
{
	QString name = QString("%1.cpp").arg(classname);
	QFile file(name);
	if (!file.open(QIODevice::WriteOnly)) {
		qDebug() <<__FILE__<<__LINE__<<"open file failed.";
		return ;
	}
	QTextStream out(&file);

	out << QString("#include \"%1.h\"").arg(classname)<<"\r\n";

	//成员变量
	out << QString("class %1Private {\r\npublic:\r\n").arg(classname);
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out << QString("	%1 %2;").arg(type).arg(name)<<"\r\n";
	}

	//实现部分
	out << QString("};") << "\r\n";
	out << QString("%1::%1(QObject *parent) : QObject(parent), m_dptr(new %1Private)").arg(classname)<<"\r\n";
	out << QString("{\r\n}\r\n");
	out << QString("%1::~%1()\r\n{\r\n	delete m_dptr;\r\n}\r\n").arg(classname);

	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("%1 %2::%3 () const\r\n{\r\n	return m_dptr->%4;\r\n}").arg(type).arg(classname).arg(name).arg(name) <<"\r\n";
		out << QString ("void %1::set%2%3 (%4 value)\r\n{\r\n	if ( m_dptr->%5 == value) return;\r\n	m_dptr->%5 = value;\r\n	emit %5Changed();\r\n	emit paramsChanged();\r\n}").arg(classname).arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type).arg(name)<< "\r\n";
	}

	file.close();
}


void Creator::define2()
{
	QString name = QString("%1.cpp").arg(classname);
	QFile file(name);
	if (!file.open(QIODevice::ReadWrite)) {
		qDebug() <<__FILE__<<__LINE__<<"open file failed.";
		return ;
	}
	QTextStream out(&file);

	out << QString("#include \"%1.h\"").arg(classname)<<"\r\n";
	out << QString("#include <QDomElement>\r\n");
	out << QString("#define MODULE_INFO \"%1%2\"\r\n").arg(classname.at(0).toUpper()).arg(classname.right(classname.length() - 1));
	//成员变量
	out << QString("class %1Private {\r\npublic:\r\n").arg(classname)<<"\r\n";
	out << QString("	QDomNode	root;\r\n");
	foreach(QStringList node, list) {
		QString name = node.at(1);
		out << QString("	QDomElement %1;").arg(name)<<"\r\n";
	}

	//构造函数
	out << QString("	%1Private(QDomNode node): root(QDomNode())\r\n").arg(classname);
	out << QString("	{\r\n		root = node.firstChildElement (MODULE_INFO);\r\n");
	out << QString("		if (root.isNull()) {\r\n");
	out << QString("			QDomDocument doc = node.toDocument();\r\n");
	out << QString("			root = doc.createElement(MODULE_INFO);\r\n");
	foreach(QStringList node, list) {
		QString name = node.at(1);
		out << QString ("			%1 = doc.createElement(\"%1\");\r\n").arg(name);	
	}
	foreach(QStringList node, list) {
		QString name = node.at(1);
		out << QString ("			root.appendChild(%1);\r\n").arg(name);
	}

	out << QString("			node.appendChild (root);\r\n");

	foreach(QStringList node, list) {
		QString name = node.at(1);
		out << QString ("			%1.setAttribute(\"value\", QVariant());\r\n").arg(name);
	}
	out << QString ("		} else {\r\n");
	foreach(QStringList node, list) {
		QString name = node.at(1);
		out << QString ("			%1 = root.firstChildElement(\"%1\");\r\n").arg(name);
	}

	//实现部分
	out <<QString("		}\r\n	}\r\n};")<<"\r\n";

	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		QString rType = "";
		if (type == "int") {
			rType = ".toInt()";
		} else if (type == "float") {
			rType = ".toFloat()";
		} else if (type == "double") {
			rType = ".toDouble()";
		} else if (type == "long") {
			rType = ".toLong()";
		}

		out <<QString("%1 %2::%3() const\r\n{\r\n	return m_dptr->%4.attribute(\"value\")%5;\r\n}").arg(type).arg(classname).arg(name).arg(name).arg(rType) <<"\r\n";
		out << QString ("void %1::set%2%3(%4 value)\r\n{\r\n	if ( %5() == value) return;\r\n	m_dptr->%5.setAttribute(\"value\", value);\r\n	emit %5Changed();\r\n	emit paramsChanged();\r\n}").arg(classname).arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type).arg(name)<< "\r\n";
	}

	file.close();
}
