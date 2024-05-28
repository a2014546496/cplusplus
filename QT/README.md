# QT
## һ���źźͲ�
1. ʲô���źźͲۣ���QT��ʹ���źźͲۺ���������Ϣ֮��Ĵ��ݡ�QT��ÿ�����ÿؼ������������źźͲۡ��û��ڴ������ĳ���ؼ���Ӧ�Ĳ���ʱ������������һ���źţ����źŹ����Ĳۺ����ͻ�ִ��(��Խ������ݵĸ�����ʾ)
* �źźͲ۶�������һ��һ�Ĺ�ϵ��һ�Ӷ�Ĺ�ϵ����Զ�Ĺ�ϵ�����źŷ����󣬸��źŹ�����һ�����߶���ۺ����ͻ���ݽ�����ϵʱ��˳�����ν��е��á�

* �Զ����źźͲ۵ķ������ź���ۺ����Ĳ�������һ�¡�

    ```c++
    // 1 method �����ھ��л���û�в����������
    connect(ptr_sender, SIGNAL(function_sender(args)), ptr_receiver, SLOT(function_receiver(args)));

    //2 method �÷����������źź�����ۺ����Ĳ���������Ĭ��ֵ
    connect(ptr_sender, &ptr_sender::function_sender, ptr_receiver, &ptr_receiver::function_receiver);

    //3 method use lamba

    connect(ptr_sender,&ptr_sender::function_sender, [&|=| ](){});

    ```

* ���߳��µ��ź���ۺ�����connect�����һ������Ĭ�ϣ�ȱʡ��ΪQT::AutoConnection��

    ��Ҫ�еĹ�ϵ�У�  
    QT::DirectConnection �źű�����ʱ���ۺ�������ִ�У���ͬһ���߳��С�

    QT::QueuedConnection ���¼�ѭ���ص��������̺߳�ִ�вۺ������ۺ������źŲ���ͬһ���߳��С�

    QT::BlockingQueuedConnection �� QT::QueuedConnection���ƣ�ֻ���ź��̻߳��������ۺ����߳�ִ����ϡ�������ͬһ���߳���ʹ�ã������������ 

    QT::AutoConnection �źŽ������뷢������ͬһ���߳��У�ʹ��QT::DirectConnection,��֮ʹ��QT::QueuedConnection��


* ʹ��sender()������ȡ�����ߡ���sender()�᷵�ط����ߵĶ���ָ�룬���֪�������ߵ����Ϳ���ʹ��qobject_cast<type *>(sender()) ����ת����


## ���� Ԫ����
* Ԫ�����������̳�QObject���ࡢ��private���� Q_OBJECT�꣨����ʹ�����ԡ��źźͲۻ��ƣ���MOC��Ԫ�����������Ϊÿ��QObject�����ṩ��Ҫ�Ĵ���ʵ��Ԫ����ϵͳ�����ԣ�����Q_OBJECT���Ϊ�������������һ������Ԫ����֧�ִ����c++Դ�ļ����������Դ�ļ���ͬ���ʵ���ļ�һ�𱻱��������ӡ�

    �ṩ QObject::metaObject()����Ԫ����

    ����className��������������

    newInstance()������ʵ����

    inherits��const char* className)�ж��Ƿ�ΪclassName������ࡣ

    tr()��trutf8()�ɷ����ַ�����

    setProperty()�� prperty() ���úͻ�ȡ�������ƶ�Ӧ��ֵ��


* ����ϵͳ���壺
![Alt text](image.png)

    ```c++
    //defined
    Q_PROPERTY(bool focus READ hasFocus)
    
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)

    Q_PERPERTY(QCursor cursor READ cuursor WRITEsetCursor RESET unsetCursor)

    //use
    Qobject object.....
    object->setProerty("flat", truue);
    bool isFlat = object->property("flat");

    //����ʹ�����ֻ���ʵ��QSS�÷�
    editLine->setProperty("required", "true");

    //*.qss��
    *[required="true"] 
    {
       background-color:lime 
    }
    ```

    ## ����MVCģʽ��Model��View

    ![Alt text](image-1.png)

 1. ʲô��MVC��Model��View��Controller�� ������ʵ�����ݣ���SQL��������ݱ����ı��ļ��ȣ���ģ�ͣ�����ģ�ͣ���ʵ������ͨ�ţ�Ϊ��ͼ����ṩ���ݽӿڣ�������ͼ��ʾ���ݡ�View������ͼ����չʾ��Ϣ��
 2. QT���ṩ������ģ�͡�

    ![Alt text](image-2.png)
    ![Alt text](image-3.png)

    ���г����࣬�����Զ�����̳в�ʵ�����еķ�����

3. ��ͼ���
    ![Alt text](image-4.png)
    ![Alt text](image-5.png)

4. ������Controller��

    �����ฺ���ṩ������ģ�͵ı༭��CURD����Ȼ����ʾ�ڶ�Ӧ�Ľ����С�

    ![Alt text](image-6.png)


## �ġ� ���ÿؼ�

1. QPushButton��QToolButton��QCheckButton�ȳ��ð�ť��

2. LineEdit��SpinBox�ȳ��ñ༭��ͻ�������

3. QListView��QTreeView��QTableView����View��β������ ģ��/��ͼ��Model/View���ṹ�����ݴ����Model�С�

4. QListWidget��QTreeWidget����Widget��β���࣬��ֱ�ӽ����ݴ洢��ÿһ�����С�

5. ��ǩ��ͼƬ��QLabel��QPixmap��


## �塢 ���ò���


## �����ര�����

## �ߡ���ͼ

## �ˡ��Զ���ؼ�

## �š���Ƶ����

## ʮ��������Ƶ


## ʮһ��QtӦ�÷���
