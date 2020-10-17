#开发记录2 python.cv2 相关问题  
##1.python plt.imshow与cv2.imshow的色差问题  
opencv 的接口使用BGR模式，matplotlib.pyplot 接口使用的是RGB模式，所以相同的三维数组，显示不同。   
解决办法：
<block>

	b, g, r = cv2.split(frame)
    frame = cv2.merge([r, g, b])
    cv2.imshow('',frame)
    cv2.waitKey(10)
<block>