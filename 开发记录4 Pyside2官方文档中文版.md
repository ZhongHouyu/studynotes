#开发记录4 Pyside2官方文档中文版  （一）  

（pyside2简介与入门教程部分）

该文档主要基于qt公司的官方pyside2官方文档做出翻译和整理  

##PySide2开发文档  


###开始第一个Qt应用  

####环境需求
在Python环境下开始开发Qt应用之前，我们应该先安装配置好相应的python环境：

	>Python 2.7 或者3.5+  
	>推荐使用一个虚拟环境，如venv 或 virtuallenv  

####安装  

安装好python之后，通过pip安装PySide2，在终端中输入以下命令：  

	pip install PySide2   #下载最新的版本  

注意：windows平台上使用pip前请检查自己的环境变量是否添加相关内容，否则需要进入pip所在文件下才能运行  

####检查安装  
通过运行以下命令检查你的安装是否成功，并得知自己的PySide2版本等相关信息  

```
import PySide2.QtCore

#打印PySide2版本
# e.g. 5.11.1a1
print(PySide2.__version__)

# 得到版本信息的一个序列
# e.g. (5, 11, 1, 'a', 1)
print(PySide2.__version_info__)

# 打印当前PySide2对应的qt版本
# e.g. "5.11.2"
print(PySide2.QtCore.__version__)

# 得到相应qt版本信息的一个序列
# e.g. (5, 11, 2)
print(PySide2.QtCore.__version_info__)  

```   
至此，pyside2相关的配置工作就完成了  


####创建一个简单的应用  

在配置好环境后，用几行代码就可以开发出能输出”hello world“的简单程序，下面将会介绍完成这个简单程序的几个步骤：  

1.创建一个新py文件 hello world.py，并添加以下几个import项：  
```
import sys
import random
from PySide2 import QtCore, QtWidgets, QtGui
```  
pyside2提供了许多Qt开发相关的API，QtCore, QtWidgets, QtGui是非常常用的包，后面会有更详细的介绍  

2.创建一个类MyWidget，继承于QWidget，并包含QPushButton 和 QLabel两个实例  

···
class MyWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.hello = ["Hallo Welt", "Hei maailma", "Hola Mundo", "Привет мир"]

        self.button = QtWidgets.QPushButton("Click me!")
        self.text = QtWidgets.QLabel("Hello World")
        self.text.setAlignment(QtCore.Qt.AlignCenter)

        self.layout = QtWidgets.QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)
        self.setLayout(self.layout)

        self.button.clicked.connect(self.magic)


    def magic(self):
        self.text.setText(random.choice(self.hello))
···
在MyWidget类中有一个magic函数，通过产生随机数来选择不同语言的“你好”  

3.现在，在主函数中示例一个`MyWidget`，并展示它  

```
if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())
```   

运行程序，点击下方的按钮就可以看到不同的“你好”了  
<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-pyside2/hello.png" />
</div>  


###PySide2模块介绍  

####基础模块  

这些是创建一个 Widget-based界面的主要模块  

||
|  :----:|  :----| 
| Qt.Core | 提供了非图形界面功能的核心功能，如槽、属性、基类、序列等 | 
| Qt.GUI| 在QtCroe的基础上扩展了GUI功能，如事件、窗口、屏幕、OpenGl、基于栅格的2D绘图板，图像等 | 
| Qt.Widgets| 提供应用中常用的控件，如组成你图像界面的按钮、表格等 |   

####QML与Qt Quick  
通过以下模块实现 QML文件与python的交互  

||
|  :----:|  :----| 
| Qt.QML | 提供与PythonAPI交互的基础功能 | 
| Qt.Quick| 提供能在Qt应用中使用QtQucik的类 | 
| Qt.QuickWidgets| 提供能在Qt应用中使用的QQuickWidget类 |   

####数据可视化  

统计图（charts）、流程图（diagrams）、动画（animations）：这些模块能让你在的界面中使用这些功能


||
|  :----:|  :----| 
| Qt.Charts | 提供一般统计图的绘制方法 | 
| Qt.DataVisualization| 提供能在3D维度展现你的数据的方法 | 


####多媒体  

实现声音、视频、硬件的交互

||
|  :----:|  :----| 
| Qt.Multimedia | 提供基础的多媒体功能 | 
| Qt.MultimediaWidgets| 提供基于widget的多媒体API | 

####网络引擎  

如果尼电应用是基于一个浏览器或者要与网络应用交互，那么这些模块可以实现那些功能  


||
|  :----:|  :----| 
| Qt.WebEngineWidgets | 提供widgets来处理网络相关内容 | 
| Qt.WebChannel| 实现服务器-客户端的端到端的交互功能 | 

###Pyside2 入门教程  ###  
这是一个针对于python环境下Qt开发新手的一个引导教程。文档本身是把C++项目重构成了python 项目，介绍了一些基础控件以及的他们的使用方法  

### 第一个QtWidgets应用程序 ###   

与其他所有编程框架一样，我们从第一个“hello world”程序出发。  

下面是一个Hello World 应用的简单例子：  


```
import sys
from PySide2.QtWidgets import QApplication, QLabel
app = QApplication(sys.argv)
label = QLabel("Hello World!")
label.show()
app.exec_()
```  
对于一个基于Pyside2的widget应用来说，必须先从`Pyside2.QtWidgets`模块引入相关的类  
之后，创建一个QApplication 示例。在Qt收到来自命令行的任何指令参数的时候，你可以通过把这些参数传给QApplication对象来实现。但通常来说，你不需要输入任何参数让它自己运行，或者像以下方式传参：
```
app = QApplication([])  
```
其中[]就是参数内容  

在创建了一个application对象后，我们可以再创建一个QLabel对象。QLabel是一个可以展示文本、图像的控件（并可以增加html样式）：
```
# 通过html标签语言修改控件样式
label = QLabel("<font color=red size=40>Hello World!</font>")   
```  
在Qt中也引入了QML这种声明式（declarative language ）的语言来创建UI，如下面view.qml就是一个简单的QML文件：  
```
import QtQuick 2.0
Rectangle {
    width: 200
    height: 200
    color: "green"
    Text {
        text: "Hello World"
        anchors.centerIn: parent
    }
}
	
```  
在QML文件中引入的`QtQuick 2.0`就是一个QML模块  
而后面的QML代码与HTML或XML语言十分相似。在这个文件中，我们创立了一个绿色的200*200大小的矩形，并在其中加上了一个写着“hello world”的文本对象。代码`anchors.centerIn: parent`让该文本出现在它的直接父组件矩形的中央  

接下来，我们再在main.py中调用这样的界面样式：   
```
from PySide2.QtWidgets import QApplication
from PySide2.QtQuick import QQuickView
from PySide2.QtCore import QUrl
app = QApplication([])
view = QQuickView()
url = QUrl("view.qml")
view.setSource(url)
view.show()
app.exec_()
```

效果如下：  
<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-pyside2/viewQML.png" />
</div>  



### 一个简单的按钮教程 ###  

在这篇教程中，我们将会展示如何在Pyside2中使用信号和槽。   
信号和槽是一个Qt的一个特色设计，该设计能让不同的图形控件之间实现通信。  
在下面的应用程序中，我们创建了一个按钮控件，并为其增加了一个`Button clicked`响应，每次按下这个按钮，控制台都会输出“hello！”  

首先导入必须的Pyside2类和python sys模块：  
```
import sys
from PySide2.QtWidgets import QApplication, QPushButton
from PySide2.QtCore import Slot
```
然后建立一个函数：在控制台发送消息：  
```
@Slot()
def say_hello():
    print("Button clicked, Hello!")
```
注意：`@Slot()`是一个修饰器，是对`say_hello()`函数的一个注解，可以理解为该过程使`say_hello()`函数成为为一个槽  

创建一个可以点击的按钮，也就是一个`QPushButton`实例，并在按钮上写上label文本  
```
button = QPushButton("Click me")
```   
在我们显示这个按钮之前，我们必须把`say_hello()`函数与按钮的点击信号相连接：   

```
button.clicked.connect(say_hello)
```  

最后，在Qt主循环中显示按钮：  

```
button.show()

app.exec_()   
```

下面是这个例子的完整代码：   
```
import sys
from PySide2.QtWidgets import QApplication, QPushButton
from PySide2.QtCore import Slot


@Slot()
def say_hello():
 print("Button clicked, Hello!")


# Create the Qt Application
app = QApplication(sys.argv)
# Create a button, connect it and show it
button = QPushButton("Click me")
button.clicked.connect(say_hello)
button.show()
# Run the main Qt loop
app.exec_()
		
```   

### 创建一个简单的对话框应用 ###  

这篇教程中展现了如何使用基础的控件实现一个对话框。该程序的主要功能是用户在`QLineEdit`中填写自己的名字，按下按钮，对话框就会跟用户打招呼（在控制台输出hello user_name）   

首先创建一个简单的对话框窗体：  
```
import sys
from PySide2.QtWidgets import QApplication, QDialog, QLineEdit, QPushButton


class Form(QDialog):
    def __init__(self, parent=None):
        super(Form, self).__init__(parent)
        self.setWindowTitle("My Form")


if __name__ == '__main__':
    # Create the Qt Application
    app = QApplication(sys.argv)
    # Create and show the form
    form = Form()
    form.show()
    # Run the main Qt loop
    sys.exit(app.exec_())
```  

注意，在

在`QDlalog`类中可以定义任何`Pyside2 widgets`的子类。在这个例子中，我们定义了一个名为`Form`的`QDlalog`子类。并且`Form`中的`init()`方法也调用了父类的初始函数`init()`，并置窗口标题为“my Form”   

加入控件  

使用`QLineEdit`输入使用者姓名，用`QPushButton`打印`QLineEdit`得到的内容，并把这一过程加入`Form`的`init()`方法中：

```
self.edit = QLineEdit("Write my name here..")
self.button = QPushButton("Show Greetings")
```
显然如何排列这两个控件是一个问题，为了准确放置我们的控件，需要再使用一个`layout`容器来组织我们的控件们  
Qt中有许多layout样式，在这里我们使用了`QVBoxLayout`来使控件垂直方向排列，并把这一过程加入`init()`方法  

```
# Create layout and add widgets
layout = QVBoxLayout()
layout.addWidget(self.edit)
layout.addWidget(self.button)
# Set dialog layout
self.setLayout(layout)
```

控件的布局完成之后，还需要把控件连接起来，即用信号与槽的方式建立联系：

```
# Add button signal to greetings slot
self.button.clicked.connect(self.greetings)
``` 

完整代码如下：  
```
import sys

from PySide2.QtCore import Slot
from PySide2.QtWidgets import (QLineEdit, QPushButton, QApplication,
                               QVBoxLayout, QDialog)


class Form(QDialog):
    def __init__(self, parent=None):
        super(Form, self).__init__(parent)
        # Create widgets
        self.edit = QLineEdit("Write my name here")
        self.button = QPushButton("Show Greetings")
        # Create layout and add widgets
        layout = QVBoxLayout()
        layout.addWidget(self.edit)
        layout.addWidget(self.button)
        # Set dialog layout
        self.setLayout(layout)
        # Add button signal to greetings slot
        self.button.clicked.connect(self.greetings)

    # Greets the user
    @Slot()
    def greetings(self):
        print("Hello %s" % self.edit.text())


if __name__ == '__main__':
    # Create the Qt Application
    app = QApplication(sys.argv)
    # Create and show the form
    form = Form()
    form.show()
    # Run the main Qt loop
    sys.exit(app.exec_())

```
运行结果如下所示：  

<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-pyside2/dialog-1.png" /><img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-pyside2/dialog-2.png" />
</div>  


至此Pyside2简介和基础教程部分就告一段落，接下来将会对常用控件进行进一步讲解