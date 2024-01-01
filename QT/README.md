# 一、 Qt核心特点

1. Qt是一个跨平台的c++开发类库，使用标准C++编写,提供跨平台GUI服务。
2. 特点: 
 * 元对象系统：提供对象之间通信的信号与槽机制、运行时类型信息和动态属性系统。，由三个基础组成(QObject所有使用元对象系统的类的基类；在类的private下部分声明Q_OBJECT宏，使得类可以使用元对象的特性，如动态属性、信号与槽；MOC(元对象编译器)为每个QObject的子类提供必要的代码来实现元对象系统的特性)

    QObject::metaObject:返回类关联的元对象，包含一些接口如className函数可以在运行时返回类的名称字符串。
    
    QObject::inherits:判断一个对象实例是否名称为className的。
    
    QObject::tr与trUtf8可以翻译字符串，用于多语言界面设计。

    QObject::setProperty和 Property可以通过属性名称动态设置和获取属性值。
```c++
QObject *obj = new QPushButton;
obj->metaObject()->className(); //"返回QpushButton"

obj->inherits("QObject");//true
obj->inherits("QPushButton"); // true
obj->inherits("Qsda") ; //false
```

* 属性系统：Q_PROPERTY(type name 
  
  (READ getFunction [WRITE setFunction] | MEMBER meberName [READ getfunction | WRITE setFunction])  
  
  [RESET resetFunction]
  
  [NOTIFY notifySignal]

  [REVISION int]

  [DESIGNABLE bool]

  [SCRIPTABLE bool]

  [STORED bool]

  [USER bool]

  [CONSTANT]

  [FINAL]

  )

    READ WRITE 指定读和设定一个属性值的函数 
    
    MEMBER 指定一个成员变量与属性关联，成为可读可写的属性

    RESET 用于指定一个设置属性缺省值的函数

    NOTIFY 可选，用于设置一个信号，当属性值发生变化时发射该信号

    DESIGNABLE 表示该属性是否可在Qt Designer 中可见，默认 true

    CONSTANT 表示属性值是一个常数 即为const类型

    FINAL 表示定义的属性不能被子类重载

    动态属性：QObject::setProperty函数可以在运行时为类定义一个新的属性，称为动态属性。动态属性三针对类的实例定义。

    ```c++
     editName->setProperty("required", "true");
     comboSex->setProperty("required", "true");
     checkAgree->setProperty("required", "true");
    ```

    类的附加信息
    Q_CLASSINFO宏,可以为类的元对象定义 "名称 - 值"。如

    ```c++
    class QMyclass: public QObject
    {
        Q_OBJECT
        Q_CLASSINFO("author", "Wang")
        Q_CLASSINFO("company","UPC")
        public:
        ...
    };
    ```

 * 信号与槽：是对象间进行通信的机制，需要由Qt的元对象系统支持才能实现。发射信号时不需要知道Qt是如何找到槽函数。与回调函数相比，信号与槽执行速度要慢一点，因为需要查找连接的对象和槽函数，但是灵活性高比回调强。

```c++
    connect(lineEdit, &QLineEdit::textChanged, this, &widget::on_textChanged);
    connect(sender, SIGAL(signal(参数类型)), this, SLOT(slotFun(参数类型)));
    /*
        connect的最后一个参数
        Qt::AutoConnection（缺省值）：如果信号的接受者与发射者在同一个线程中，使用Qt
        ::DirectConnection，反之使用Qt::QueuedConnection,在信号发射时自动确定关联方式。

        Qt::DirectConnection 信号发射后槽函数立即执行，槽函数与信号在同一个线程。
        Qt::QueuedConnection 在事件循环回到接收线程后执行槽函数，槽函数与信号在不同的线程。
        Qt::BlockingQueuedConnection 与 QueuedConnection相似，只是信号线程会阻塞直到槽函数执行完毕，禁止在同一个线程使用，会造成死锁。
    */
```

使用 sender 获取信号发射者,在槽函数中使用Qobject::sender可以获取信号发射者的指针，如果知道发射者的类型，可以将指针投射为确定的类型，然后使用确定类的接口函数。
```c++
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
```
信号函数必须是无返回值的函数，但可以由参数列表，信号函数无需实现，只需在某些条件下发射信号。

```c++
class QPerson : public QObject
{
    Q_OBJECT
private:
    int m_age = 10;
public:
    void incAge()
    {
        m_age++;
        emit ageChanged(m_age); //发射关键字 emit 
    }
signals:
    void ageChanged(int value);
};

```