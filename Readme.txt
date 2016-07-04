目的：
	属性自动生成器
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

在软件界面输入类名，属性，然后按生成按钮1 或者生成按钮2 就可以生成相应的 .h 和 .cpp文件

生成按钮1 是简单的数据封装
生成按钮2 是把封装数据用xml的方式存储获取初始值，并且注册到engine中去。

输入的类名 首字母会自动被大写
输入的属性用逗号隔开
属性首位的空格等非法字符会自动被剔除