Ŀ�ģ�
	�����������Զ����ɴ���
��Դ��
	QObject�е�Q_PROPERTY���ԵĶ����ʵ��,�������ϴ�����⣬�ֶ�д����̫���ˣ����Ǿ����˱����� 
��飺
	���磬��һ��QOBject���У�д�������µ����ԣ���������ʵ�֣��������ϴ󣬿����ñ����̴������ɴ��롣
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
	
	���������������ӿ�
	//�����������
	setClassName(QString classname)
	//����һ������, type Ϊ���Ե��������ͣ�name Ϊ���Ե�����
	addNode(QString type, QString name)
	//���ɴ��� �����ɴ��룬����������Ŀ¼�µ�out.txt�ı��ļ��С�ע��������±�����ʶ��\n���з�����ʹ��notepad++��������ߴ�
	make()