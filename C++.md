### 一、堆与栈的区别 ###   

堆（Heap）与栈（Stack）是开发人员必须面对的两个概念，在理解这两个概念时，需要放到具体的场景下，因为不同场景下，堆与栈代表不同的含义。一般情况下，有两层含义：
（1）程序内存布局场景下，堆与栈表示两种内存管理方式；
（2）数据结构场景下，堆与栈表示两种常用的数据结构。  
#### 1. 程序内存分区中的堆与栈 ####  
1.1 栈简介
栈由操作系统自动分配释放 ，用于存放函数的参数值、局部变量等，其操作方式类似于数据结构中的栈。参考如下代码：  
```
int main() {
	int b;				//栈
	char s[] = "abc"; 	//栈
	char *p2;			//栈
}
```
其中函数中定义的局部变量按照先后定义的顺序依次压入栈中，也就是说相邻变量的地址之间不会存在其它变量。栈的内存地址生长方向与堆相反，由高到底，所以后定义的变量地址低于先定义的变量，比如上面代码中变量 s 的地址小于变量 b 的地址，p2 地址小于 s 的地址。栈中存储的数据的生命周期随着函数的执行完成而结束。  

1.2 堆简介  

堆由开发人员分配和释放， 若开发人员不释放，程序结束时由 OS 回收，分配方式类似于链表。参考如下代码：
```
int main() {
	// C 中用 malloc() 函数申请
	char* p1 = (char *)malloc(10);
	cout<<(int*)p1<<endl;		//输出：00000000003BA0C0
	
	// 用 free() 函数释放
	free(p1);
   
	// C++ 中用 new 运算符申请
	char* p2 = new char[10];
	cout << (int*)p2 << endl;		//输出：00000000003BA0C0
	
	// 用 delete 运算符释放
	delete[] p2;
}
```

其中 p1 所指的 10 字节的内存空间与 p2 所指的 10 字节内存空间都是存在于堆。堆的内存地址生长方向与栈相反，由低到高，但需要注意的是，后申请的内存空间并不一定在先申请的内存空间的后面，即 p2 指向的地址并不一定大于 p1 所指向的内存地址，原因是先申请的内存空间一旦被释放，后申请的内存空间则会利用先前被释放的内存，从而导致先后分配的内存空间在地址上不存在先后关系。堆中存储的数据若未释放，则其生命周期等同于程序的生命周期。

关于堆上内存空间的分配过程，首先应该知道操作系统有一个记录空闲内存地址的链表，当系统收到程序的申请时，会遍历该链表，寻找第一个空间大于所申请空间的堆节点，然后将该节点从空闲节点链表中删除，并将该节点的空间分配给程序。另外，对于大多数系统，会在这块内存空间中的首地址处记录本次分配的大小，这样，代码中的delete语句才能正确地释放本内存空间。由于找到的堆节点的大小不一定正好等于申请的大小，系统会自动地将多余的那部分重新放入空闲链表。  

1.3 堆与栈区别  

堆与栈实际上是操作系统对进程占用的内存空间的两种管理方式，主要有如下几种区别：
（1）管理方式不同。栈由操作系统自动分配释放，无需我们手动控制；堆的申请和释放工作由程序员控制，容易产生内存泄漏；  

（2）空间大小不同。每个进程拥有的栈的大小要远远小于堆的大小。理论上，程序员可申请的堆大小为虚拟内存的大小，进程栈的大小 64bits 的 Windows 默认 1MB，64bits 的 Linux 默认 10MB；  

（3）生长方向不同。堆的生长方向向上，内存地址由低到高；栈的生长方向向下，内存地址由高到低。  

（4）分配方式不同。堆都是动态分配的，没有静态分配的堆。栈有2种分配方式：静态分配和动态分配。静态分配是由操作系统完成的，比如局部变量的分配。动态分配由alloca函数进行分配，但是栈的动态分配和堆是不同的，他的动态分配是由操作系统进行释放，无需我们手工实现。  

（5）分配效率不同。栈由操作系统自动分配，会在硬件层级对栈提供支持：分配专门的寄存器存放栈的地址，压栈出栈都有专门的指令执行，这就决定了栈的效率比较高。堆则是由C/C++提供的库函数或运算符来完成申请与管理，实现机制较为复杂，频繁的内存申请容易产生内存碎片。显然，堆的效率比栈要低得多。  

（6）存放内容不同。栈存放的内容，函数返回地址、相关参数、局部变量和寄存器内容等。当主函数调用另外一个函数的时候，要对当前函数执行断点进行保存，需要使用栈来实现，首先入栈的是主函数下一条语句的地址，即扩展指针寄存器的内容（EIP），然后是当前栈帧的底部地址，即扩展基址指针寄存器内容（EBP），再然后是被调函数的实参等，一般情况下是按照从右向左的顺序入栈，之后是被调函数的局部变量，注意静态变量是存放在数据段或者BSS段，是不入栈的。出栈的顺序正好相反，最终栈顶指向主函数下一条语句的地址，主程序又从该地址开始执行。堆，一般情况堆顶使用一个字节的空间来存放堆的大小，而堆中具体存放内容是由程序员来填充的。  

从以上可以看到，堆和栈相比，由于大量malloc()/free()或new/delete的使用，容易造成大量的内存碎片，并且可能引发用户态和核心态的切换，效率较低。栈相比于堆，在程序中应用较为广泛，最常见的是函数的调用过程由栈来实现，函数返回地址、EBP、实参和局部变量都采用栈的方式存放。虽然栈有众多的好处，但是由于和堆相比不是那么灵活，有时候分配大量的内存空间，主要还是用堆。  

无论是堆还是栈，在内存使用时都要防止非法越界，越界导致的非法内存访问可能会摧毁程序的堆、栈数据，轻则导致程序运行处于不确定状态，获取不到预期结果，重则导致程序异常崩溃，这些都是我们编程时与内存打交道时应该注意的问题。  

####2. 数据结构中的堆与栈 ####

数据结构中，堆与栈是两个常见的数据结构，理解二者的定义、用法与区别，能够利用堆与栈解决很多实际问题。  

2.1 栈简介  

栈是一种运算受限的线性表，其限制是指只仅允许在表的一端进行插入和删除操作，这一端被称为栈顶（Top），相对地，把另一端称为栈底（Bottom）。把新元素放到栈顶元素的上面，使之成为新的栈顶元素称作进栈、入栈或压栈（Push）；把栈顶元素删除，使其相邻的元素成为新的栈顶元素称作出栈或退栈（Pop）。这种受限的运算使栈拥有“先进后出”的特性（First In Last Out），简称FILO。  

栈分顺序栈和链式栈两种。栈是一种线性结构，所以可以使用数组或链表（单向链表、双向链表或循环链表）作为底层数据结构。使用数组实现的栈叫做顺序栈，使用链表实现的栈叫做链式栈，二者的区别是顺序栈中的元素地址连续，链式栈中的元素地址不连续。   

栈的结构如下图所示：  
<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-c++/stack.jpg" />
</div>

栈的基本操作包括初始化、判断栈是否为空、入栈、出栈以及获取栈顶元素等。下面以顺序栈为例，使用 C++ 给出一个简单的实现。  
```
#include<stdio.h>
#include<malloc.h>

#define DataType int
#define MAXSIZE 1024
struct SeqStack {
	DataType data[MAXSIZE];
	int top;
};

//栈初始化,成功返回栈对象指针，失败返回空指针NULL
SeqStack* initSeqStack() {
	SeqStack* s=(SeqStack*)malloc(sizeof(SeqStack));
	if(!s) {
		printf("空间不足\n");
		return NULL;
	} else {
		s->top = -1;
		return s;
	}
}

//判断栈是否为空
bool isEmptySeqStack(SeqStack* s) {
	if (s->top == -1)
		return true;
	else
		return false;
}

//入栈，返回-1失败，0成功
int pushSeqStack(SeqStack* s, DataType x) {
	if(s->top == MAXSIZE-1)
	{
		return -1;//栈满不能入栈
	} else {
		s->top++;
		s->data[s->top] = x;
		return 0;
	}
}

//出栈，返回-1失败，0成功
int popSeqStack(SeqStack* s, DataType* x) {
	if(isEmptySeqStack(s)) {
		return -1;//栈空不能出栈
	} else {
		*x = s->data[s->top];
		s->top--;
		return 0;
	}
}

//取栈顶元素，返回-1失败，0成功
int topSeqStack(SeqStack* s,DataType* x) {
	if (isEmptySeqStack(s))
		return -1;	//栈空
	else {
		*x=s->data[s->top];
		return 0;
	}
}

//打印栈中元素
int printSeqStack(SeqStack* s) {
	int i;
	printf("当前栈中的元素:\n");
	for (i = s->top; i >= 0; i--)
		printf("%4d",s->data[i]);
	printf("\n");
	return 0;
}

//test
int main() {
	SeqStack* seqStack=initSeqStack();
	if(seqStack) {
		//将4、5、7分别入栈
		pushSeqStack(seqStack,4);
		pushSeqStack(seqStack,5);
		pushSeqStack(seqStack,7);
		
		//打印栈内所有元素
		printSeqStack(seqStack);
		
		//获取栈顶元素
		DataType x=0;
		int ret=topSeqStack(seqStack,&x);
		if(0==ret) {
			printf("top element is %d\n",x);
		}
		
		//将栈顶元素出栈
		ret=popSeqStack(seqStack,&x);
		if(0==ret) {
			printf("pop top element is %d\n",x);
		}
	}
	return 0;
}

```
运行上面的程序，输出结果：  
```
当前栈中的元素:
   7   5   4
top element is 7
pop top element is 7
```  
2.2 堆简介  

2.2.1 堆的性质  

堆是一种常用的树形结构，是一种特殊的完全二叉树，当且仅当满足所有节点的值总是不大于或不小于其父节点的值的完全二叉树被称之为堆。堆的这一特性称之为堆序性。因此，在一个堆中，根节点是最大（或最小）节点。如果根节点最小，称之为小顶堆（或小根堆），如果根节点最大，称之为大顶堆（或大根堆）。堆的左右孩子没有大小的顺序。下面是一个小顶堆示例：  

<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-c++/heap.png" />
</div>  

堆的存储一般都用数组来存储堆，i节点的父节点下标就为( i – 1 ) / 2 
它的左右子节点下标分别为 2 ∗ i + 1和 2 * i + 1 
如第0个节点左右子节点下标分别为1和2。  

<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-c++/heap-2.png" />
</div> 

2.2.2 堆的基本操作

（1）建立
以最小堆为例，如果以数组存储元素时，一个数组具有对应的树表示形式，但树并不满足堆的条件，需要重新排列元素，可以建立“堆化”的树。  
<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-c++/heap-3.png" />
</div>   
（2）插入
将一个新元素插入到表尾，即数组末尾时，如果新构成的二叉树不满足堆的性质，需要重新排列元素，下图演示了插入15时，堆的调整。  
<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-c++/heap-4.png" />
</div>    

（3）删除
堆排序中，删除一个元素总是发生在堆顶，因为堆顶的元素是最小的（小顶堆中）。表中最后一个元素用来填补空缺位置，结果树被更新以满足堆条件。
<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-c++/heap-5.png" />
</div>  

2.2.3 堆操作实现

（1）插入代码实现
每次插入都是将新数据放在数组最后。可以发现从这个新数据的父节点到根节点必然为一个有序的数列，现在的任务是将这个新数据插入到这个有序数据中，这就类似于直接插入排序中将一个数据并入到有序区间中，这是节点“上浮”调整。不难写出插入一个新数据时堆的调整代码：  

```
//新加入i节点,其父节点为(i-1)/2
//参数：a：数组，i：新插入元素在数组中的下标  
void minHeapFixUp(int a[], int i) {  
    int j, temp;  
    temp = a[i];  
    j = (i-1)/2;      //父节点  
    while (j >= 0 && i != 0) {  
        if (a[j] <= temp)//如果父节点不大于新插入的元素，停止寻找  
            break;  
        a[i]=a[j];    		//把较大的子节点往下移动,替换它的子节点  
        i = j;  
        j = (i-1)/2;  
    }  
    a[i] = temp;  
}  
```

因此，插入数据到最小堆时：

```
//在最小堆中加入新的数据data  
//a：数组，index：插入的下标，
void minHeapAddNumber(int a[], int index, int data) {  
    a[index] = data;  
    minHeapFixUp(a, index);  
} 
```
（2）删除代码实现
按照堆删除的说明，堆中每次都只能删除第0个数据。为了便于重建堆，实际的操作是将数组最后一个数据与根节点交换，然后再从根节点开始进行一次从上向下的调整。
调整时先在左右儿子节点中找最小的，如果父节点不大于这个最小的子节点说明不需要调整了，反之将最小的子节点换到父节点的位置。此时父节点实际上并不需要换到最小子节点的位置，因为这不是父节点的最终位置。但逻辑上父节点替换了最小的子节点，然后再考虑父节点对后面的节点的影响。堆元素的删除导致的堆调整，其整个过程就是将根节点进行“下沉”处理。下面给出代码：

```
//a为数组，len为节点总数；从index节点开始调整，index从0开始计算index其子节点为 2*index+1, 2*index+2；len/2-1为最后一个非叶子节点 
void minHeapFixDown(int a[],int len,int index) {
	if(index>(len/2-1))//index为叶子节点不用调整
		return;
	int tmp=a[index];
	lastIndex=index;
	while(index<=len/2-1)        //当下沉到叶子节点时，就不用调整了
	{ 
		// 如果左子节点小于待调整节点
		if(a[2*index+1]<tmp) {
			lastIndex = 2*index+1;
		}
		//如果存在右子节点且小于左子节点和待调整节点
		if(2*index+2<len && a[2*index+2]<a[2*index+1]&& a[2*index+2]<tmp) {
			lastIndex=2*index+2;
		}
		//如果左右子节点有一个小于待调整节点，选择最小子节点进行上浮
		if(lastIndex!=index) {
			a[index]=a[lastIndex];
			index=lastIndex;
		} else break;             //否则待调整节点不用下沉调整
	}
	a[lastIndex]=tmp;           //将待调整节点放到最后的位置
}
```  

（3）建堆
有了堆的插入和删除后，再考虑下如何对一个数据进行堆化操作。要一个一个的从数组中取出数据来建立堆吧，不用！先看一个数组，如下图：  

<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-c++/heap-6.png" />
</div>    

很明显，对叶子节点来说，可以认为它已经是一个合法的堆了即20，60， 65， 4， 49都分别是一个合法的堆。只要从A[4]=50开始向下调整就可以了。然后再取A[3]=30，A[2] = 17，A[1] = 12，A[0] = 9分别作一次向下调整操作就可以了。下图展示了这些步骤：  

<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-c++/heap-7.png" />
</div>  
2.2.4 堆的具体应用——堆排序  

堆排序（Heapsort）是堆的一个经典应用，有了上面对堆的了解，不难实现堆排序。由于堆也是用数组来存储的，故对数组进行堆化后，第一次将A[0]与A[n - 1]交换，再对A[0…n-2]重新恢复堆。第二次将A[0]与A[n – 2]交换，再对A[0…n - 3]重新恢复堆，重复这样的操作直到A[0]与A[1]交换。由于每次都是将最小的数据并入到后面的有序区间，故操作完成后整个数组就有序了。有点类似于直接选择排序。
因此，完成堆排序并没有用到前面说明的插入操作，只用到了建堆和节点向下调整的操作，堆排序的操作如下：  
```
//array:待排序数组，len：数组长度
void heapSort(int array[],int len) {
	//建堆
	makeMinHeap(array,len); 
	
	//最后一个叶子节点和根节点交换，并进行堆调整，交换次数为len-1次
	for(int i=len-1;i>0;--i) {
		//最后一个叶子节点交换
		array[i]=array[i]+array[0];
		array[0]=array[i]-array[0];
		array[i]=array[i]-array[0];
        
        //堆调整
		minHeapFixDown(array, 0, len-i-1);  
	}
}  
```
（1）稳定性。堆排序是不稳定排序。
（2）堆排序性能分析。由于每次重新恢复堆的时间复杂度为O(logN)，共N-1次堆调整操作，再加上前面建立堆时N/2次向下调整，每次调整时间复杂度也为O(logN)。两次操作时间复杂度相加还是O(NlogN)，故堆排序的时间复杂度为O(NlogN)。
最坏情况：如果待排序数组是有序的，仍然需要O(NlogN)复杂度的比较操作，只是少了移动的操作；
最好情况：如果待排序数组是逆序的，不仅需要O(NlogN)复杂度的比较操作，而且需要O(NlogN)复杂度的交换操作，总的时间复杂度还是O(NlogN)。
因此，堆排序和快速排序在效率上是差不多的，但是堆排序一般优于快速排序的重要一点是数据的初始分布情况对堆排序的效率没有大的影响。

### 二、智能指针 ###   
如1.1中所说，在C++中使用new关键字来完成新对象的构建，使用new关键字会调用类的构造函数，不加参数会使用默认的构造函数，而使用delete关键字删除类时，会调用析构函数。  
但是，析构函数的调用不等于delete 释放类中内存的内容，如果在构造函数中有动态申请内存，那么在析构函数中需要手动释放掉，否则会内存泄漏。
对于这样的问题，C++11的智能指针则是一个很好的解决方案。  

C++里面的四个智能指针: auto_ptr, unique_ptr,shared_ptr, weak_ptr 其中后三个是C++11支持，并且第一个已经被C++11弃用。     

**C++11智能指针介绍**

智能指针主要用于管理在堆上分配的内存，它将普通的指针封装为一个栈对象。当栈对象的生存周期结束后，会在析构函数中释放掉申请的内存，从而防止内存泄漏。C++ 11中最常用的智能指针类型为shared_ptr,它采用引用计数的方法，记录当前内存资源被多少个智能指针引用。该引用计数的内存在堆上分配。当新增一个时引用计数加1，当过期时引用计数减一。只有引用计数为0时，智能指针才会自动释放引用的内存资源。对shared_ptr进行初始化时不能将一个普通指针直接赋值给智能指针，因为一个是指针，一个是类。可以通过make_shared函数或者通过构造函数传入普通指针。并可以通过get函数获得普通指针。

**为什么要使用智能指针**

智能指针的作用是管理一个指针，因为存在以下这种情况：申请的空间在函数结束时忘记释放，造成内存泄漏。使用智能指针可以很大程度上的避免这个问题，因为智能指针是一个类，当超出了类的实例对象的作用域时，会自动调用对象的析构函数，析构函数会自动释放资源。所以智能指针的作用原理就是在函数结束时自动释放内存空间，不需要手动释放内存空间。  

**auto_ptr**
（C++98的方案，C++11已经抛弃）采用所有权模式。
```
auto_ptr<string> p1 (new string ("I reigned lonely as a cloud.")); 
auto_ptr<string> p2; 
p2 = p1; //auto_ptr不会报错.
```
此时不会报错，p2剥夺了p1的所有权，但是当程序运行时访问p1将会报错。所以auto_ptr的缺点是：存在潜在的内存崩溃问题  

**unique_ptr**
（替换auto_ptr）unique_ptr实现独占式拥有或严格拥有概念，保证同一时间内只有一个智能指针可以指向该对象。它对于避免资源泄露(例如“以new创建对象后因为发生异常而忘记调用delete”)特别有用。
采用所有权模式，还是上面那个例子  

```
unique_ptr<string> p3 (new string ("auto"));   //#4
unique_ptr<string> p4；                       //#5
p4 = p3;//此时会报错！！
```
编译器认为p4=p3非法，避免了p3不再指向有效数据的问题。尝试复制p3时会编译期出错，而auto_ptr能通过编译期从而在运行期埋下出错的隐患。因此，unique_ptr比auto_ptr更安全。
另外unique_ptr还有更聪明的地方：当程序试图将一个 unique_ptr 赋值给另一个时，如果源 unique_ptr 是个临时右值，编译器允许这么做；如果源 unique_ptr 将存在一段时间，编译器将禁止这么做，比如：  
```
unique_ptr<string> pu1(new string ("hello world")); 
unique_ptr<string> pu2; 
pu2 = pu1;                                      // #1 不允许
unique_ptr<string> pu3; 
pu3 = unique_ptr<string>(new string ("You"));   // #2 允许
```
其中#1留下悬挂的unique_ptr(pu1)，这可能导致危害。而#2不会留下悬挂的unique_ptr，因为它调用 unique_ptr 的构造函数，该构造函数创建的临时对象在其所有权让给 pu3 后就会被销毁。这种随情况而已的行为表明，unique_ptr 优于允许两种赋值的auto_ptr 。  

注：如果确实想执行类似与#1的操作，要安全的重用这种指针，可给它赋新值。C++有一个标准库函数std::move()，让你能够将一个unique_ptr赋给另一个。尽管转移所有权后 还是有可能出现原有指针调用（调用就崩溃）的情况。但是这个语法能强调你是在转移所有权，让你清晰的知道自己在做什么，从而不乱调用原有指针。
（额外：boost库的boost::scoped_ptr也是一个独占性智能指针，但是它不允许转移所有权，从始而终都只对一个资源负责，它更安全谨慎，但是应用的范围也更狭窄。）

例如：
```
unique_ptr<string> ps1, ps2;
ps1 = demo("hello");
ps2 = move(ps1);
ps1 = demo("alexia");
cout << *ps2 << *ps1 << endl;
```
**shared_ptr**
shared_ptr实现共享式拥有概念。多个智能指针可以指向相同对象，该对象和其相关资源会在“最后一个引用被销毁”时候释放。从名字share就可以看出了资源可以被多个指针共享，它使用计数机制来表明资源被几个指针共享。可以通过成员函数use_count()来查看资源的所有者个数。除了可以通过new来构造，还可以通过传入auto_ptr, unique_ptr,weak_ptr来构造。当我们调用release()时，当前指针会释放资源所有权，计数减一。当计数等于0时，资源会被释放。
shared_ptr 是为了解决 auto_ptr 在对象所有权上的局限性(auto_ptr 是独占的), 在使用引用计数的机制上提供了可以共享所有权的智能指针。
成员函数：
use_count 返回引用计数的个数
unique 返回是否是独占所有权( use_count 为 1)
swap 交换两个 shared_ptr 对象(即交换所拥有的对象)
reset 放弃内部对象的所有权或拥有对象的变更, 会引起原有对象的引用计数的减少
get 返回内部对象(指针), 由于已经重载了()方法, 因此和直接使用对象是一样的.如
```
shared_ptr<int> sp(new int(1)); 
```
sp 与 sp.get()是等价的。
share_ptr的简单例子：
```
int main()
{
	string *s1 = new string("s1");

	shared_ptr<string> ps1(s1);
	shared_ptr<string> ps2;
	ps2 = ps1;

	cout << ps1.use_count()<<endl;	//2
	cout<<ps2.use_count()<<endl;	//2
	cout << ps1.unique()<<endl;	//0

	string *s3 = new string("s3");
	shared_ptr<string> ps3(s3);

	cout << (ps1.get()) << endl;	//033AEB48
	cout << ps3.get() << endl;	//033B2C50
	swap(ps1, ps3);	//交换所拥有的对象
	cout << (ps1.get())<<endl;	//033B2C50
	cout << ps3.get() << endl;	//033AEB48

	cout << ps1.use_count()<<endl;	//1
	cout << ps2.use_count() << endl;	//2
	ps2 = ps1;
	cout << ps1.use_count()<<endl;	//2
	cout << ps2.use_count() << endl;	//2
	ps1.reset();	//放弃ps1的拥有权，引用计数的减少
	cout << ps1.use_count()<<endl;	//0
	cout << ps2.use_count()<<endl;	//1
}
```
**weak_ptr**
share_ptr虽然已经很好用了，但是有一点share_ptr智能指针还是有内存泄露的情况，当两个对象相互使用一个shared_ptr成员变量指向对方，会造成循环引用，使引用计数失效，从而导致内存泄漏。
weak_ptr 是一种不控制对象生命周期的智能指针, 它指向一个 shared_ptr 管理的对象. 进行该对象的内存管理的是那个强引用的shared_ptr， weak_ptr只是提供了对管理对象的一个访问手段。weak_ptr 设计的目的是为配合 shared_ptr 而引入的一种智能指针来协助 shared_ptr 工作, 它只可以从一个 shared_ptr 或另一个 weak_ptr 对象构造, 它的构造和析构不会引起引用记数的增加或减少。weak_ptr是用来解决shared_ptr相互引用时的死锁问题,如果说两个shared_ptr相互引用,那么这两个指针的引用计数永远不可能下降为0,资源永远不会释放。它是对对象的一种弱引用，不会增加对象的引用计数，和shared_ptr之间可以相互转化，shared_ptr可以直接赋值给它，它可以通过调用lock函数来获得shared_ptr。  

```
class B;	//声明
class A
{
public:
	shared_ptr<B> pb_;
	~A()
	{
		cout << "A delete\n";
	}
};

class B
{
public:
	shared_ptr<A> pa_;
	~B()
	{
		cout << "B delete\n";
	}
};

void fun()
{
	shared_ptr<B> pb(new B());
	shared_ptr<A> pa(new A());
	cout << pb.use_count() << endl;	//1
	cout << pa.use_count() << endl;	//1
	pb->pa_ = pa;
	pa->pb_ = pb;
	cout << pb.use_count() << endl;	//2
	cout << pa.use_count() << endl;	//2
}

int main()
{
	fun();
	return 0;
}

```
可以看到fun函数中pa ，pb之间互相引用，两个资源的引用计数为2，当要跳出函数时，智能指针pa，pb析构时两个资源引用计数会减1，但是两者引用计数还是为1，导致跳出函数时资源没有被释放（A、B的析构函数没有被调用）运行结果没有输出析构函数的内容，造成内存泄露。如果把其中一个改为weak_ptr就可以了，我们把类A里面的shared_ptr pb_，改为weak_ptr pb_ ，运行结果如下：
```
1
1
1
2
B delete
A delete
```
这样的话，资源B的引用开始就只有1，当pb析构时，B的计数变为0，B得到释放，B释放的同时也会使A的计数减1，同时pa析构时使A的计数减1，那么A的计数为0，A得到释放。
注意：我们不能通过weak_ptr直接访问对象的方法，比如B对象中有一个方法print()，我们不能这样访问，pa->pb_->print()，因为pb_是一个weak_ptr，应该先把它转化为shared_ptr，如：  
```
shared_ptr<B> p = pa->pb_.lock();
p->print();
```
weak_ptr 没有重载*和->但可以使用 lock 获得一个可用的 shared_ptr 对象. 注意, weak_ptr 在使用前需要检查合法性.
expired 用于检测所管理的对象是否已经释放, 如果已经释放, 返回 true; 否则返回 false.
lock 用于获取所管理的对象的强引用(shared_ptr). 如果 expired 为 true, 返回一个空的 shared_ptr; 否则返回一个 shared_ptr, 其内部对象指向与 weak_ptr 相同.
use_count 返回与 shared_ptr 共享的对象的引用计数.
reset 将 weak_ptr 置空.
weak_ptr 支持拷贝或赋值, 但不会影响对应的 shared_ptr 内部对象的计数.  

**share_ptr和weak_ptr的核心实现**

weakptr的作为弱引用指针，其实现依赖于counter的计数器类和share_ptr的赋值，构造，所以先把counter和share_ptr简单实现
**Counter简单实现:  **

```
template <class T>
class WeakPtr; //为了用weak_ptr的lock()，来生成share_ptr用，需要拷贝构造用

template <class T>
class SharePtr
{
public:
    SharePtr(T *p = 0) : _ptr(p)
    {
        cnt = new Counter();
        if (p)
            cnt->s = 1;
        cout << "in construct " << cnt->s << endl;
    }
    ~SharePtr()
    {
        release();
    }

    SharePtr(SharePtr<T> const &s)
    {
        cout << "in copy con" << endl;
        _ptr = s._ptr;
        (s.cnt)->s++;
        cout << "copy construct" << (s.cnt)->s << endl;
        cnt = s.cnt;
    }
    SharePtr(WeakPtr<T> const &w) //为了用weak_ptr的lock()，
							//来生成share_ptr用，需要拷贝构造用
    {
        cout << "in w copy con " << endl;
        _ptr = w._ptr;
        (w.cnt)->s++;
        cout << "copy w  construct" << (w.cnt)->s << endl;
        cnt = w.cnt;
    }
    SharePtr<T> &operator=(SharePtr<T> &s)
    {
        if (this != &s)
        {
            release();
            (s.cnt)->s++;
            cout << "assign construct " << (s.cnt)->s << endl;
            cnt = s.cnt;
            _ptr = s._ptr;
        }
        return *this;
    }
    T &operator*()
    {
        return *_ptr;
    }
    T *operator->()
    {
        return _ptr;
    }
    friend class WeakPtr<T>; //方便weak_ptr与share_ptr设置引用计数和赋值

protected:
    void release()
    {
        cnt->s--;
        cout << "release " << cnt->s << endl;
        if (cnt->s < 1)
        {
            delete _ptr;
            if (cnt->w < 1)
            {
                delete cnt;
                cnt = NULL;
            }
        }
    }

private:
    T *_ptr;
    Counter *cnt;
};

```

share_ptr的给出的函数接口为：构造，拷贝构造，赋值，解引用，通过release来在引用计数为0的时候删除_ptr和cnt的内存。  

**weak_ptr简单实现** 

```
template <class T>
class WeakPtr
{
public: //给出默认构造和拷贝构造，其中拷贝构造不能有从原始指针进行构造
    WeakPtr()
    {
        _ptr = 0;
        cnt = 0;
    }
    WeakPtr(SharePtr<T> &s) : _ptr(s._ptr), cnt(s.cnt)
    {
        cout << "w con s" << endl;
        cnt->w++;
    }
    WeakPtr(WeakPtr<T> &w) : _ptr(w._ptr), cnt(w.cnt)
    {
        cnt->w++;
    }
    ~WeakPtr()
    {
        release();
    }
    WeakPtr<T> &operator=(WeakPtr<T> &w)
    {
        if (this != &w)
        {
            release();
            cnt = w.cnt;
            cnt->w++;
            _ptr = w._ptr;
        }
        return *this;
    }
    WeakPtr<T> &operator=(SharePtr<T> &s)
    {
        cout << "w = s" << endl;
        release();
        cnt = s.cnt;
        cnt->w++;
        _ptr = s._ptr;
        return *this;
    }
    SharePtr<T> lock()
    {
        return SharePtr<T>(*this);
    }
    bool expired()
    {
        if (cnt)
        {
            if (cnt->s > 0)
            {
                cout << "empty" << cnt->s << endl;
                return false;
            }
        }
        return true;
    }
    friend class SharePtr<T>; //方便weak_ptr与share_ptr设置引用计数和赋值
    
protected:
    void release()
    {
        if (cnt)
        {
            cnt->w--;
            cout << "weakptr release" << cnt->w << endl;
            if (cnt->w < 1 && cnt->s < 1)
            {
                //delete cnt;
                cnt = NULL;
            }
        }
    }

private:
    T *_ptr;
    Counter *cnt;
};

```  
weak_ptr一般通过share_ptr来构造，通过expired函数检查原始指针是否为空，lock来转化为share_ptr。

