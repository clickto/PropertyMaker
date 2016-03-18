#include <QObject>
#include <QTextStream>
#include <QFile>
QString classname;
QList<QStringList> list;

void setClassName(QString name)
{
	classname = name;
}
void addNode(QString type, QString name)
{
	QStringList str;
	str<<type<<name;
	list.append(str);
}

void declaration()
{
	QFile file("out.txt");
	if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
		return ;
	}
	QTextStream out(&file);

	//声明部分
	out <<QString("//%1.h").arg(classname)<<endl;


	//声明属性
	//Q_PROPERTY(int name READ name WRITE setName NOTIFY nameChanged)
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("	Q_PROPERTY(%1 %2 READ %3 WRITE set%4 NOTIFY %5Changed)").arg(type).arg(name).arg(name).arg(QString("%1%2").arg(name.at(0).toUpper()).arg(name.mid(1, name.size()))).arg(name) << endl;

	}

	//声明属性的读写函数
	out << "public:"<<endl;
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("	%1 %2() const;").arg(type).arg(name) <<endl;
		out << QString ("	void set%1%2(%3 _value);").arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type) << endl;
	}
	//声明属性的改变信号
	out << "signals:"<<endl;
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString ("	void %1Changed();").arg(name) << endl;
	}

	file.close();
}

void define1()
{
	QFile file("out.txt");
	if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
		return ;
	}
	QTextStream out(&file);

	//实现部分
	out <<QString("//%1.cpp").arg(classname)<<endl;

	//成员变量
	out << QString("class %1Private {\npublic:\n").arg(classname)<<"private:"<<endl;
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out << QString("	%1 %2;").arg(type).arg(name)<<endl;
	}

	//实现部分
	out <<QString("}")<<endl;

	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("%1 %2::%3 () const\n{\n	return m_dptr->%4;\n}").arg(type).arg(classname).arg(name).arg(name) <<endl;
		out << QString ("void %1::set%2%3 (%4 _value)\n{\n	if ( m_dptr->%5 != _value) {\n		m_dptr->%5 = _value;\n		emit %5Changed();\n	}\n}").arg(classname).arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type).arg(name)<< endl;
	}

	file.close();
}


void define2()
{
	QFile file("out.txt");
	if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
		return ;
	}
	QTextStream out(&file);

	//实现部分
	out <<QString("//%1.cpp").arg(classname)<<endl;

	//成员变量
	out << QString("class %1Private {\npublic:\n").arg(classname)<<"private:"<<endl;
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out << QString("	QDomElement %1;").arg(name)<<endl;
	}

	//实现部分
	out <<QString("}")<<endl;

	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("%1 %2::%3() const\n{\n	return m_dptr->%4.attribute(\"value\").toDouble();\n}").arg(type).arg(classname).arg(name).arg(name) <<endl;
		out << QString ("void %1::set%2%3(%4 _value)\n{\n	if ( %5() != _value) {\n		QString sValue = QString(\"%1\").arg(_value);\n		m_dptr->%5.setAttribute(\"value\", sValue);\n		emit %5Changed();\n	}\n}").arg(classname).arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type).arg(name)<< endl;
	}

	file.close();
}

int main(int argc, char * argv[])
{
//	setClassName("PWParams");

//	addNode("int", "audio");
//	addNode("int", "width");
//	addNode("int", "height");
//	addNode("int", "linepersec");
//	addNode("int", "prf");
//	addNode("int", "ver");
//	addNode("int", "baseline");
//	addNode("int", "autotrace");
//	addNode("int", "invert");
//	addNode("int", "optid");
//	addNode("int", "resolution");
//	addNode("int", "triplex");

//	makeprivate();

//	setClassName("PwSampling");
//	addNode("int", "simple");
//	addNode("int", "angle");
//	addNode("int", "gategap");
//	addNode("int", "pwangle");
////	makeprivate();
//	makecommon();

//	setClassName("Echo");

//	addNode("int", "viewx");
//	addNode("int", "viewy");
//	addNode("int", "viewwidth");
//	addNode("int", "viewheight");
//	makecommon();
//	makeprivate();

	setClassName("TgcParams");

	addNode("qreal", "tgc1");
	addNode("qreal", "tgc2");
	addNode("qreal", "tgc3");
	addNode("qreal", "tgc4");
	addNode("qreal", "tgc5");
	addNode("qreal", "tgc6");
	addNode("qreal", "tgc7");
	addNode("qreal", "tgc8");
	declaration();
	define2();
	return 0;
}
