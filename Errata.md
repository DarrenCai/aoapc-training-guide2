# aoapc-training-guide2

#### 介绍
《算法竞赛入门经典-训练指南-升级版》勘误

## 第2章

- 例题25  侏罗纪（Jurassic Remains, NEERC 2003, Codeforces Gym 101388J）
    
 总时间复杂度为 **O(2<sup>n/2</sup>log n)，即O(1.44<sup>n</sup>log n)** 
     应为：

    总时间为 O(n/2*2<sup>n/2</sup>log2)，即 O(n*1.44<sup>n</sup>)。


## 第3章

### 3.5.1 表 3-5

![输入图片说明](https://images.gitee.com/uploads/images/2021/0416/175008_b2cacfc9_5344186.png "屏幕截图.png")

后面一段的这句话： 对于等价类v={" **abca** ", "abc", "ab"}，len(v)=3, minlen(v)=2。
修改为v={"abc", "bc", "c"}。

## 第4章 

- 例题18  行星（Asteroids, NEERC 2009,  **UVa1710** ） 题号应为 UVa1438