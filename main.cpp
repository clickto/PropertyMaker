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

void make()
{
	QFile file("out.txt");
	if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
		return ;
	}
	QTextStream out(&file);

	//定义部分
	out <<QString("//%1.h").arg(classname)<<endl;

	//属性的读取函数
	out << "public:"<<endl;
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("	%1 %2 () const;").arg(type).arg(name) <<endl;
		out << QString ("	void set%1%2 (%3 _value);").arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type) << endl;
	}
	//属性的改变信号
	out << "signals:"<<endl;
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString ("	void %1Changed();").arg(name) << endl;
	}
		//	out <<QString("%1 %2 () const;").arg(type).arg(name) <<endl;
		//	out << QString ("void set%1%2 (%3 _value);").arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type) << endl;
		//	out <<QString ("void %1Changed();").arg(name) << endl;

	//成员变量
	out << "private:"<<endl;
	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out << QString("	%1 m_%2;").arg(type).arg(name)<<endl;
	}

	//实现部分
	out <<QString("//%1.cpp").arg(classname)<<endl;

	foreach(QStringList node, list) {
		QString type = node.at(0);
		QString name = node.at(1);
		out <<QString("%1 %2::%3 () const\n{\n	return m_%4;\n}").arg(type).arg(classname).arg(name).arg(name) <<endl;
		out << QString ("void %1::set%2%3 (%4 _value)\n{\n if ( m_%5 == _value)\n	return;\n m_%5 = _value;\n emit %5Changed();\n}").arg(classname).arg(name.at(0).toUpper()).arg(name.mid(1, name.size())).arg(type).arg(name)<< endl;
	}


	file.close();
}

int main(int argc, char * argv[])
{
	setClassName("PWParams");

	addNode("int", "audio");
	addNode("int", "width");
	addNode("int", "height");
	addNode("int", "linepersec");
	addNode("int", "prf");
	addNode("int", "ver");
	addNode("int", "baseline");
	addNode("int", "autotrace");
	addNode("int", "invert");
	addNode("int", "optid");
	addNode("int", "resolution");
	addNode("int", "triplex");

	make();

	return 0;
}
