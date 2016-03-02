目的：
	本工程用来自动生成代码
来源：
	QObject中的Q_PROPERTY属性的定义和实现,代码量较大的问题，手动写起来太累了，于是就有了本工程 
简介：
	例如，在一个QOBject类中，写好了如下的属性，接下来的实现，工作量较大，可以用本工程代替生成代码。
/*
	Q_PROPERTY(int audio READ audio WRITE setAudio NOTIFY audioChanged)
	Q_PROPERTY(int width READ width  WRITE setWidth  NOTIFY widthChanged)
	Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
	Q_PROPERTY(int linepersec READ linepersec WRITE setLinepersec NOTIFY linepersecChanged)
	Q_PROPERTY(int prf READ prf WRITE setPrf NOTIFY prfChanged)
	Q_PROPERTY(int ver READ ver WRITE setVer NOTIFY verChanged)
	Q_PROPERTY(int baseline READ baseline WRITE setBaseline NOTIFY baselineChanged)
	Q_PROPERTY(int autotrace READ autotrace WRITE setAutotrace NOTIFY autotraceChanged)
	Q_PROPERTY(int invert READ invert WRITE setInvert NOTIFY invertChanged)
	Q_PROPERTY(int optid READ optid WRITE setOptid NOTIFY optidChanged)
	Q_PROPERTY(int resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)
	Q_PROPERTY(int triplex READ triplex WRITE setTriplex NOTIFY triplexChanged)
*/
	
	本工程中有三个接口
	//设置类的名称
	setClassName(QString classname)
	//增加一个属性, type 为属性的数据类型，name 为属性的命名
	addNode(QString type, QString name)
	//生成代码 将生成代码，保存在运行目录下的out.txt文本文件中。注：如果记事本不能识别\n换行符，请使用notepad++等替代工具打开
	make()