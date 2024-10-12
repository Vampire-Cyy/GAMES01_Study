# $Lecture11$：光场与颜色空间

## 1. 光场

基本思想，用平面来模拟人眼实际看到三维空间

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011155600236.png" alt="image-20241011155600236" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011155610845.png" alt="image-20241011155610845" style="zoom:33%;" />

### 1.1 全光函数

通过函数的形式来描述所有光线信息

- $P(\theta,\phi)$引入两个参数来描述光线的位置信息，得到一张灰度图
<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011160230695.png" alt="image-20241011160230695" style="zoom:50%;" />
- $P(\theta,\phi,\lambda)$，加入光的波长，得到色彩信息
<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011160419048.png" alt="image-20241011160419048" style="zoom:50%;" />
- $P(\theta,\phi,\lambda,t)$引入时间
- $P(\theta,\phi,\lambda,t,V_x.V_y.V_z)$最后引入自己的位置，代表整个世界中的光线分布
<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011204928125.png" alt="image-20241011204928125" style="zoom:50%;" />

对于这个七维的函数，可以表示任何地方，任何方向，任何时间看到的东西的颜色，这就是全光函数

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011205037709.png" alt="image-20241011205037709" style="zoom:50%;" />

### 1.2 光线

光线具有起点和方向，定义为$P(\theta,\phi,V_x,V_y,V_z)$

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011213059446.png" alt="image-20241011213059446" style="zoom:50%;" />

也可以用两个点来定义

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011213127256.png" alt="image-20241011213127256" style="zoom:50%;" />

### 1.3 光场

 由全光函数可以知道世界中任意光线的分布，由一块幕布来模拟三维空间的思想给出了这样一种解决方式，想要描述一个物体的视觉信息，只要找出它的包围盒，并记录包围盒表面任意一点向任意方向的发光情况即可，光场就是在任意位置向任意方向的光照强度

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011213411031.png" alt="image-20241011213411031" style="zoom:50%;" />

知道光场后，从任意位置都可以看向这个物体，有了视点以及方向查询$4D$的函数就可以查询到记录的值

而有了包围盒后，不需要知道物体的细节，只要记录包围盒表面的任何位置任何方向的光照信息即可

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011213511690.png" alt="image-20241011213511690" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011213522180.png" alt="image-20241011213522180" style="zoom:50%;" />

光场可以用$S$和$\theta$得到任意一条光线

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011213802355.png" alt="image-20241011213802355" style="zoom:50%;" />

也可以定义两个相互平行的平面，只要连接两个点就可以确定唯一的一条光线，找到所有的uv和st的对应关系，便可以定义任意一条光线

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011213913711.png" alt="image-20241011213913711" style="zoom:50%;" />

假设整个世界在st平面右边

从uv上一固定点向st平面上任意一点看，得到的就相当于在这个点放一个摄像机所得到的图集

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011214047105.png" alt="image-20241011214047105" style="zoom:50%;" />

从uv上任意一点向st平面上一固定点看，得到的就是同一个物体在不同方向上所得到的结果

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011214211551.png" alt="image-20241011214211551" style="zoom:50%;" />

### 1.4 光场摄像机

基本原理：将像素替换成透镜，让透镜将来自不同方向的光分开然后记录下来

这种底片支持后期的重新聚焦

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011214357992.png" alt="image-20241011214357992" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011214437270.png" alt="image-20241011214437270" style="zoom:50%;" />

还原普通照片的方法：对于每个透镜都选择每一“块”的最底部的像素。

有了光场之后，可以虚拟移动相机的位置 ，而光场摄像机记录了所有的光场信息。

但是光场摄像机存在分辨率不足，高成本等问题

## 2. 颜色

颜色本质上是人的一种感知，而不是光的某种物理属性，不同波长的光不是不同的颜色

### 2.1 颜色的物理学基础

不同的颜色对应着不同的吸收光谱

#### 2.1.1 可见光的光谱

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011214741720.png" alt="image-20241011214741720" style="zoom:50%;" />

#### 2.1.2 谱功率密度

谱功率密度（SPD）是光线不同波长的光强分布是多少，也即不同颜色的光对应的光强分布

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011214851082.png" alt="image-20241011214851082" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011214903331.png" alt="image-20241011214903331" style="zoom:50%;" />

谱功率密度是度量光的重要属性，具有线性运算的性质

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011215008454.png" alt="image-20241011215008454" style="zoom:50%;" />

### 2.2 颜色的生物学基础

人的眼睛的构造与相机类似，而颜色这一感知就是在视网膜这一结构上形成的

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011215102906.png" alt="image-20241011215102906" style="zoom: 50%;" />

#### 2.2.1 感光细胞

视网膜上有两种感光细胞：

- 视杆细胞：感知光的强度，得到一张灰度图
- 视锥细胞：感知光的颜色，有三种类型：S-Cone，M-Cone，L-Cone，对于不同波长的光反应不一样

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011215346916.png" alt="image-20241011215346916" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011215358863.png" alt="image-20241011215358863" style="zoom:50%;" />

并且感光细胞存在极强的个体差异性，在不同人中分布不同

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011215442187.png" alt="image-20241011215442187" style="zoom:50%;" />

#### 2.2.2 三色理论

三色理论提出人所看到的颜色，其实是由三个数所构成的，而不是具体的物体

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011215617704.png" alt="image-20241011215617704" style="zoom:67%;" />

每一个光的波长信息不能被人眼测量，也不能被大脑接受

而人眼在得到了SML这三个数后向大脑传输信号，使大脑获取这一信息，最终形成了颜色这一感知

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011215734544.png" alt="image-20241011215734544" style="zoom:67%;" />

#### 2.2.3 同色异谱

由于人所感知到的颜色实际上只是由3个数构成的，所以很有可能出现最后看到的色彩相同，但是光谱分布不同这样的情况，因此有时并不需要知道具体的光谱分布，而只需要通过不同波长的实验进行模拟即可

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011220005921.png" alt="image-20241011220005921" style="zoom:50%;" />

这四张光谱截然不同，但积分出来所得到的颜色却是相同的

### 2.3 颜色匹配

颜色匹配主要有两种系统：加色系统和减色系统

加色系统

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011220300401.png" alt="image-20241011220300401" style="zoom:50%;" />

减色系统

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011221841228.png" alt="image-20241011221841228" style="zoom:50%;" />

给定一组主要的光，调整这些光的亮度并将其混合在一起，最终用一组3个数RGB来描述

![image-20241011220337876](C:\Users\Vampire\AppData\Roaming\Typora\typora-user-images\image-20241011220337876.png)

但是有的颜色加不出来，此时可以在原色上加色，相当于给调色减色，由此得到相同的颜色

![image-20241011220446248](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011220446248.png)

CIE RGB Color Matching

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011220520798.png" alt="image-20241011220520798" style="zoom:50%;" />

CIE RGB Color Matching Functions

即每个CIE RGB主要光匹配x轴上给定波长的单色光需要混合的量

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011220538312.png" alt="image-20241011220538312" style="zoom:50%;" />

Color Reproduction with Matching Functions

对于任何一个光谱s，感知到的光被下面的公式匹配（缩放CIE RGB原色）

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011220559734.png" alt="image-20241011220559734" style="zoom:50%;" />

### 2.4 颜色空间

由不同的方法所生成的一系列颜色称为颜色空间

#### 2.4.1 sRGB

sRGB：标准RGB空间，是最常见，最广泛的色彩空间，但是色域有限

#### 2.4.2 CIE XYZ

CIE XYZ是一个人造的的颜色匹配系统，首先设定标准颜色原色组X，Y，Z

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011221021378.png" alt="image-20241011221021378" style="zoom: 67%;" />

可以看出y的分布函数大致均匀且对称，因此可以将y视为一个特殊的表示亮度的常量

对X，Y，Z进行归一化，得到x，y，z

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011221117438.png" alt="image-20241011221117438" style="zoom:67%;" />

固定y，得到一张关于x，z的关系的函数图，在对应的位置填上对应的颜色，就得到一张色域图，表示所能表示出来的颜色

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011221237489.png" alt="image-20241011221237489" style="zoom:67%;" />

不同颜色空间所对应的色域

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011221252109.png" alt="image-20241011221252109" style="zoom:50%;" />

#### 2.4.3 HSV颜色空间

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011221335394.png" alt="image-20241011221335394" style="zoom:50%;" />

HSV颜色空间常见于拾色器中，方便调出需要的颜色：

- Hue：色调，不同类型的颜色
- Saturation：饱和度，更接近白色还是纯色
- Brightness：亮度，色彩的明暗程度

#### 2.4.4 CIELAB Space（L\*a\*b）

利用了互补色和视觉暂留原理的一种颜色空间，以一对互补色为轴的两端进行表示

互补色：无法混合的两种颜色

![image-20241011221702752](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011221702752.png)

