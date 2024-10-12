# $Lecture7$：光线追踪

## 1. 阴影贴图

在之前学习到光栅化时，提到了一个问题，如何处理阴影，在光栅化时我们忽略了这个问题，接下来考虑一种利用贴图的方式来实现阴影的方式——Shadow Mapping

### 1.1 实现原理

阴影映射的思想是：

- 在阴影里，说明能被相机看到但不能被光源看到
- 不在阴影里，说明能同时被相机和光源看到

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20164100.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20164123.png" style="zoom:50%;" />

### 1.2 实现步骤

因此得到阴影映射的步骤：

- 在光源处做一次光栅化，得到光栅图像和每个像素的深度图（只存储光源能看到的最近深度）
- 从摄像机做光栅化，得到光栅图像和像素的深度图
- 对于每一个看到的点，将其映射回光源渲染的深度图上， 比较从光源到这个看到的点的深度和其在深度图上对应的深度，若其深度小于该点在光源的深度，说明这个点可以同时被光源和摄像机看到

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20170341.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20170405.png" style="zoom:50%;" />

### 1.3 阴影映射的问题

至此得到了一个获得阴影的方式，但是这个方式并不完美

- Shadow Mapping仅能生成硬阴影（边缘锐利的阴影）
- 生成的阴影的效果与阴影贴图的分辨率有关系
- 涉及浮点数比较的精度问题

### 1.4 硬阴影与软阴影

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20170712.png" style="zoom:50%;" />

- 硬阴影：边缘锐利明显的阴影
- 软阴影：边缘模糊有过渡色的阴影

而产生软阴影的原理是因为物理意义上本应的存在

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20170835.png" style="zoom: 67%;" />

## 2. 光线追踪

阴影贴图无法完全满足我们对阴影渲染的要求，通过光栅化实现硬阴影的方法，有很多制约，通过一些改进方式同样可以实现软阴影，但是无法实现全局光照，光的多次反射，还有一些复杂的毛发渲染同样难以实现

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20195844.png" style="zoom:50%;" />

软阴影的产生是由于光源的大小和距离。一个面积较大的光源照射一个物体，可以从多个角度投射光线到物体上。当光线从不同角度照射时，阴影边缘的重叠区域会因光线部分遮挡而出现阴影的渐变效果。

光泽反射是一种既不完全镜面反射也不完全漫反射的光反射现象。光泽度高、粗糙度低的表面产生的反射相对清晰，接近镜面反射；而光泽度低、粗糙度高的表面，反射图像就会更加模糊，趋向漫反射。

间接光照是一个场景中光线经过一次或多次反射后照射到物体表面的光照效果。在真实世界中，一个房间只通过一扇窗投过光照，但是房间里没有一个地方是完全黑色的，这就是光的多次反射造成的。

### 2.1 基本依据

- 光线沿直线传播：在微观角度光沿着波形转播，在宏观角度光沿直线传播
- 光线相互不碰撞：当光线的传播路径发生交叠时，我们认为光线的传播互不干扰
- 光线具有可逆性：真实世界中，视觉成像是因为物体反射或反射光线，进入视网膜；在图形学中，屏幕成像是因为从相机向像素建立了反向的光线传播路径，采集路径上的着色信息

### 2.2 基本原理

光线追踪采用了针孔相机模型，分为视线生成和像素着色两个阶段

对于视线生成，以相机为起点，以像素为锚点，利用光的可逆性，建立一条视觉射线，找到视线与空间中的物体所产生的最近的交点

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20200658.png" style="zoom:50%;" />

对于像素着色，当找到视线与物体之间的最近交点时，随即建立交点与光源的连线，判断交点是否在阴影之中，并根据结果来计算着色，考虑反射与折射的能量损失，写回像素结果

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20200804.png" style="zoom:50%;" />



### 2.3 惠特式光线追踪（Whitted-Style Ray Tracing）

上述过程中只考虑了直接光照，并未考虑反射与折射，Whitted-Style Ray Tracing则引入了间接光照的处理

在视线生成后，找到最近的交点，根据光线的可逆性，找到反射光线与折射光线产生的交点，递归寻找下一个交点

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20201258.png" style="zoom:50%;" />

之后将所有交点与光源连线，判断是否在阴影中，并根据结果计算着色，考虑在反射和折射时发生的能量损失

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20201237.png" style="zoom:50%;" />

## 3. 交点判定

在上文中频繁提到了判断视线与光线和物体的交点，接下来学习如何进行这一过程

### 3.1 交点判定原理

对于任意一条光线，可以用这样的一个函数表达式来表示：
$$
\vec r(t)=\vec o + t\vec d
$$
**隐式几何交点**：通过数学关系式，采用牛顿迭代法解方程的方式来计算得到$t$和交点，$f(\vec o+t\vec d)=0$

**显示几何交点**：将点与线转换成多边形网格，判断光线与平面和三角形的交点

**平面交点判定**：

对于任意一个平面，可以使用一个向量和一个点来定义，其中向量是法向量，点为平面内任意一个点
$$
（\vec p-\vec p^{\prime}）\cdot N=0\\
结合光线的表示\\
(\vec o + t\vec d-\vec p^{\prime})\cdot N=0
$$
<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20205457.png" style="zoom:67%;" />

**三角形焦点判定**：

对于三角形交点，可以通过 Moller Trumbore Algorithm 快速求解。算法利用重心坐标定义三角形内的一个点，以此得到如下关系式：
$$
\vec o+t\vec d=(1-b_1-b_2)\vec P_0+b_1\vec P_1+b_2\vec P_2
$$
根据重心坐标的特性，当$1-b_1-b_2=0$时，点在三角形内，因此关系是中存在三个变量，可以得到三个线性方程组求解变量

### 3.2 交点判定加速

在实际应用中，三维空间内可能包含非常多的物体和三角形，判断一条光线和每个三角形是否相交是一个非常耗时，消耗性的的操作，因此产生了一些针对交点判定加速的优化方法

#### 3.2.1 包围盒

使用一个简单的几何体包围一个复杂的物体，如果光线与包围盒没有交点，那么必然与内部物体没有交点，从而达到交点判定加速的目的

对于一个长方形包围盒，可以理解为三对不同的平行面形成的交集，在实际应用中会使用一种特殊的长方体，即三对面各自与坐标系的轴对齐，因此称为轴对齐包围盒（Axis-Aligned Bounding Box, AABB）

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20205542.png" style="zoom:50%;" />

**交点判定**： 

接下来考虑如何判断光线是否与轴对齐包围盒相交，先考虑二维的情况

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20211729.png" style="zoom:50%;" />

- 对于一束光线，和每一组平行面相交，计算得出两组$t_{min},t_{max}$
- 保证$t_{min}>0$的情况下，$t_{enter}=max(t_{minx},t_{miny}),t_{exit}=min(t_{maxx}.t_{maxy})$

扩展到三维，仅需增加一维$z$轴上的值即可

对于最终求出的$t_{min},t_{max}$有以下集中情况：

- $t_{exit}<0$时表示包围盒在光源背后，没有交点
- $t_{enter}<0且t_{exit}>0$时表示光线在包围盒内部
- 当且仅当$t_{enter}<t_{exit},t_{exit}\ge0$时光线和包围盒存在交点

#### 3.2.2 统一网格

对包围和内部的空间进行预处理，将包围盒拆分成统一的立体网格，将与物体发生重叠的网格进行标识

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20214709.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20214727.png" style="zoom:50%;" />

在判断光线与包围盒内部物体的交点时，会先遍历所有网格，当网格与光线有交点时，会继续判断网格内的物体是否与光线有交点

网格的划分与加速效果存在差异：

- 当只有一个网格时，没有加速效果
- 当网格划分非常密集时，计算交点时遍历网格的开销会增大，出现性能降低的情况
- 根据经验，加速效果较好时网格的数量等于物体的数量乘上一个常数（一般为27）

统一网格在一些物体分布均匀的场景加速效果较好，而在一些物体很密集一些物体很空旷时加速效果并不好

#### 3.2.3 空间划分

空间划分主要是为了解决空间中物体分布不均匀的问题，其主要有Oct-Tree,KT-Tree,BSP-Tree等几种技术

**Oct-Tree**：八叉树，基本原理时把立方体分割成八等份，递归进行分割，直到格子为空或者物体足够少

**KD-Tree**：与八叉树类似，区别在于每次将格子一分为二，沿着某个轴进行分割，相比于八叉树其节点数量的复杂度不会随着维度而指数增长

**BSP-Tree**：对空间一分为二，每次选择一个方向进行分割，相比于KD-Tree，其切割的方向并不一定与轴平行

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20215851.png" style="zoom:50%;" />

一般来说，在实际应用中最常用的是KD-Tree

KD-Tree会对包围盒空间进行预处理，对包围盒空间进行二分，构建出一颗二叉树，根节点存储二分前的整体空间，叶子节点存储物体的真实空间

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20220200.png" style="zoom:50%;" />

在进行交点判定时，本质上是对二叉树进行先序遍历，判断光线是否与整体空间有交点

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20220331.png" style="zoom:50%;" />

如果有则对其叶子节点也进行交点判定，否则对下一个节点进行判断，以此类推，当空间仍与光线存在交点时，则继续遍历二叉树，直至判定光线与物体之间存在交点或不存在交点

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20220625.png" style="zoom:50%;" />

KD-Tree在统一网格的基础上又加速了不少，但依然存在一些无法解决的问题：

- 存在无法判定的例子，比如包围盒在三角形中
- 同一物体被划分在多个包围盒中时，会有重复判断的问题

#### 3.2.4 物体划分

针对空间划分无法解决的问题，采用物体划分来解决，一种典型的技术就是BVH

BVH的整体原理与KD-Tree详细，但是KD-Tree是基于空间进行划分的，而BVH是基于物体进行划分的

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20220944.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20221000.png" style="zoom:50%;" />

对物体进行划分后，重新计算包围盒，形成根节点的子节点，最终所有叶子节点存储物体列表

在划分BVH时，有一些经验上的原则：

- 每次选择某一个坐标最长的方向进行分割
- 从位于中间位置的物体进行分割

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20221347.png" style="zoom:50%;" />

```
//伪代码实现
Intersect(Ray ray, BVH node) {
 if (ray misses node.bbox) return;
 if (node is a leaf node)
 test intersection with all objs;
 return closest intersection;
 hit1 = Intersect(ray, node.child1);
 hit2 = Intersect(ray, node.child2);
 return the closer of hit1, hit2;
}
```

## 4. 辐射度量学

为了采取更为真实的渲染方式，正确地定义光在反射与折射时的能量损失，需要更加科学的光照定义方法，因此引入辐射度量学的定义

### 4.1 几何

先定义几个几何相关概念：

- **角**：采取弧度制，通过弧长与半径的比值来定义：$\theta=\frac{l}{r}$
- **立体角**：弧面积与半径平方的比值：$\Omega=\frac{A}{r^2}$
- **微分立体角**：与$z$轴形成的夹角$\theta$，绕$z$轴形成的夹角$\phi$

计算微分立体角：
$$
dA=(rd\theta)(r\sin\theta d\phi)=r^2\sin\theta d\theta d\phi\\
d\omega=\frac{dA}{r^2}=\sin\theta d\theta d\phi\\
$$
<img src="C:\Users\Vampire\AppData\Roaming\Typora\typora-user-images\image-20240928235513219.png" alt="image-20240928235513219" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20235546.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-28%20235603.png" style="zoom:50%;" />

### 4.2 光学物理

在辐射度量学中，主要设计以下几个光学物理相关术语：

- 辐射能量（Radiant Energy）
- 辐射通量（Radiant Flux）
- 辐射强度（Radiant Intensity）
- 辐射照度（Irradiance）
- 辐射亮度（Radiance）

#### 4.2.1 辐射能量

辐射能量表示电磁辐射的能量，用符号$Q$表示，以焦耳为单位

#### 4.2.2 辐射通量

辐射通量表示单位时间内流通的能量用符号$\Phi$表示，以瓦特或流明为单位，$\Phi=\frac{dQ}{dt}$

在光学物理中，通常也用辐射通量代表单位时间辐射处光子的数量

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20001554.png" style="zoom:50%;" />

#### 4.2.3 辐射强度

辐射强度表示单位立体角的辐射通量，其中$\Phi$表示辐射通量，$\omega$表示立体角，我们可以用辐射强度描述一束光线：$I(\omega)=\frac{d\Phi}{d\omega}$

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20001758.png" style="zoom:50%;" />

#### 4.2.4 辐射照度

辐射照度表示单位正交面积的辐射通量，计算的辐射通量应该是在光照方向的垂直分量上：$E(p)=\frac{d\Phi(p)}{dA}$

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20001945.png" style="zoom:50%;" />

此时可以利用兰伯特余弦定理可以计算辐射照度

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20002125.png" style="zoom:50%;" />

同样，可以计算空间中一个点光源在空间中辐射的衰减程度，可以发现辐射照度随着半径增加而指数级衰减，辐射强度没有变化

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20002341.png)

#### 4.2.5 辐射亮度

辐射亮度表示单位立体角，单位正交面积的辐射通量，可以用辐射亮度来描述某个面光源在某个锥形方向的辐射通量
$$
L(p,\omega)=\frac{d^2\Phi(p,\omega)}{d\omega dA\cos\theta}
$$
根据辐射强度和辐射照度的定义，将辐射亮度的定义进行转化，单位立体角的辐射照度，或单位面积的辐射强度

根据这两个定义可以引入另外两个物理量：入射辐射亮度和出射辐射亮度

- 入射辐射亮度：单位立体角的辐射照度，理解为从某个方向向一个面进行辐射，该面所接收到的辐射照度：$L(p,\omega)=\frac{dEp}{d\omega\cos\theta}$
- 出射辐射亮度：单位面积的辐射强度，理解为一个面向某个方向进行辐射，该方向所发射的辐射强度：$L(p,\omega)=\frac{dI(p,\omega)}{dA\cos\theta}$

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20003237.png" style="zoom:67%;" />

在下图这样的一个场景中，辐射照度表示$dA$接收的所有能量，辐射亮度表示$dA$从某个方向接受的能量
$$
\begin{align*}
dE(p,\omega)&=L_i(p,\omega)\cos\theta d\omega\\
E(p)&=\int_{H^2}L_i(p,\omega)\cos\theta d\omega\\
\end{align*}
$$
<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20003824.png" style="zoom:50%;" />

### 4.3 双反射分布函数

已知入射光线的能量和角度，当辐射到物体表面后，光线会向各个角度反射，且各个角度反射的能量是不同的，双反射分布函数（Bidirectional Reflectance Distribution Function，BRDF）就是用于计算这种场景下的各个角度的反射能量

- 入射阶段：当入射光线从$\omega_i$角度辐射到物体表面的一个位置时，可以认为该位置吸收了所有的光线能量，用辐射强度来表示$dE(\omega_i)$
- 反射阶段：可以认为该位置将光线能量向各个方向进行辐射，对于方向$\omega_i$的光线能量，用辐射亮度来表示即$dL(x,\omega_r)$

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20004938.png" style="zoom: 50%;" />

本质上，BRDF就是表示一个由入射方向$\omega_i$ 向反射方向$\omega_r$辐射能量的比例函数$f_r(\omega_i\rightarrow\omega_r)$
$$
BRDF:f_r(\omega_i\rightarrow\omega_r)=\frac{dL_r(\omega_r)}{dE_i(\omega_i)}=\frac{dL_r(\omega_r)}{L_i(\omega_i)\cos\theta_id\omega_i}
$$
<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20004959.png" style="zoom:50%;" />

在实际应用中，对于镜面反射，BRDF定义反射方向包含所有能量，其他方向均为 0；对于漫反射，BRDF定义所有方向的能量分布相同。事实上，BRDF就是描述了光线和物体表面的作用，也就是决定了物体的材质

## 5. 全局光照

通过上述的BRDF我们可以得出了不同次数光线反射的能量的具体值为多少，由此建立反射方程与渲染方程

### 5.1 反射方程

由于BRDF定义了一个入射方向$\omega_i$向一个反射方向$\omega_r$反射时的能量比例，由此可以通过积分计算所有方向对一个反射方向$\omega_r$的能量聚合，得到反射方程：
$$
L_r(p,\omega_r)=\int_{H^2}f_r(p,\omega_i\rightarrow\omega_r)L_i(p,\omega_i)\cos\theta_id\omega_i
$$

### 5.2 渲染方程

基于反射方程可以进一步得到渲染方程，考虑反射方程，忽略了物体本身会发光的情况，于是增加一个发光项即可得到渲染方程，将$\cos\theta_i=n\cdot\omega_i$代入，得到渲染方程：
$$
L_r(p,\omega_r)=L_e(p,\omega_r)+\int_{H^2}L_i(p,\omega_i)f_r(p,\omega_i,\omega_r)(n\cdot\omega_i)d\omega_i
$$
<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20010131.png" style="zoom:50%;" />

上述渲染方程中只考虑了光源的情况，但还有一种情况是由物体反射的光线，这时仅需进行一步简单的变换将光源的这一项替换为物体发出的光线

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20010255.png" style="zoom:50%;" />

对渲染方程进行下列的数学变换：
$$
\begin{align*}
l(u)&=e(u)+\int l(v)K(u,v)dv\\
将&K作为反射操作符，L是一个递归项\\
L&=E+KL\\
接下来求解L，K是一个反射操作符，&因此可以理解为反射次数越多展开项越多，K^2就表示光在空间中弹射两次\\
L&=E+KL\\
IL-KL&=E\\
(I-K)L&=E\\
L&=(I-k)^{-1}E\\
L&=(I+K+K^2+K^3+\cdots)E\\
L&=E+KE+K^2E+K^3E+\cdots
\end{align*}
$$
![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20010949.png)

而考虑弹射的次数不同，对于渲染的效果也是大相径庭

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/ray-tracing-32.png"  />

### 5.3 蒙特卡洛积分

关于经典的光线追踪，Whitted-Style Ray Tracing存在一些问题：

- 光线只进行镜面反射和折射
- 光线在漫反射面停止弹射

对于第一种情况经典光线追踪只能渲染镜面反射，无法渲染磨砂反射

对于第二种情况对于漫反射物体光线传播至表面时会停止弹射

因此就要通过渲染方程来对交点进行渲染

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20011350.png" style="zoom: 50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20011412.png" style="zoom:50%;" />

接下来的问题就是如何求解渲染方程，这是我们采用一种积分方式——蒙特卡洛积分

#### 5.3.1 概率论基础

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20011637.png)

对于一个连续性随机变量，可以定义它的一个概率分布函数（Probability Distribution Function，PDF），满足以下两个性质：

- 所有取值的概率之和为$1$：$\int p(x)dx=1;(p(x)\ge0)$
- 期望为概率与随机变量乘积的积分：$E(x)=\int xp(x)dx$

#### 5.3.2 蒙特卡洛积分公式

下一步是求解这个定积分

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20012002.png" style="zoom:50%;" />

蒙特卡洛积分：通过在积分域内不断采样$f(x)$，构成在$[a,b]$间的一个个长方形，然后对所有长方形面积之和求平均值，由此得到离散形式的蒙特卡洛方程：
$$
F_N=\frac{1}{N}\sum_{i=1}^{1}\frac{f(x_i)}{p(x_i)}\\
\int_a^bf(x)dx=\frac{1}{N}\sum_{i=1}^{N}\frac{f(x_i)}{p(x_i)}\\
$$
既然是采样，根据前面学到的一些采样理论，$N$越大时求解的结果更精确

### 5.4 路径追踪

接下来考虑真正的渲染过程

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20012528.png" style="zoom:67%;" />

考虑一个像素点的着色过程，$\omega_0$为观测方向，$\omega_i$为光线入射方向，先忽略着色点本身的发光项，得到一个简化的渲染方程：
$$
L_o(p,\omega_o)=\int_{H^2}L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(n\cdot\omega_i)d\omega_i
$$
将渲染等价为在半球面上进行采样，那么任意一点的采样概率取均匀分布的$p(\omega_i)=\frac{1}{2\pi}$，利用蒙特卡洛积分来求解渲染方程：
$$
\begin{align*}
L_o(p,\omega_o)&=\int_{H^2}L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(n\cdot\omega_i)d\omega_i\\
&\approx\frac{1}{N}\sum_{i=1}^{N}\frac{f(\omega_i)}{p(\omega_i)}\\
&\approx\frac{1}{N}\sum_{i=1}^{N}\frac{L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(n\cdot\omega_i)}{p(\omega_i)}
\end{align*}
$$

```
//伪代码实现
shade(p, wo)
	Randomly choose N directions wi~pdf
	Lo = 0.0
	For each wi
		Trace a ray r(p, wi)
		If ray r hit the light
			Lo += (1 / N) * L_i * f_r * cosine / pdf(wi)
	Return Lo
```

在上述的方法中，只考虑了一次光线的弹射，而全局光照还包括二次弹射，三次弹射，考虑二次弹射和三次弹射，即为从物体$Q$反射到物体$P$的光线，即为从$P$观测$Q$，$Q$点的着色，于是全局光照就转换成了一个递归的算法

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20013636.png" style="zoom:50%;" />

```
shade(p, wo)
	Randomly choose N directions wi~pdf
	Lo = 0.0
	For each wi
		Trace a ray r(p, wi)
		If ray r hit the light
			Lo += (1 / N) * L_i * f_r * cosine / pdf(wi)
		Else If ray r hit an object at q
			Lo += (1 / N) * shade(q, -wi) * f_r * cosine / pdf(wi)
	Return Lo
```

但留个问题，这样就结束了吗？

#### 5.4.1 光线数量问题

在上述的算法中，对于每一个点的着色需要采样各个方向的光线，而每一个方向所经过的反射点又会采样各个方向，这样的复杂度时指数型增长的

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20013913.png" style="zoom:50%;" />

而只有当采样数为$1$时，递归时才不会出现内存爆炸的问题，因此对于每个着色点，只通过一条射线进行光线追踪的方式即为路径追踪（Path Tracing）

```
shade(p, wo)
	Randomly choose ONE direction wi~pdf(w)
	Trace a ray r(p, wi)
	If ray r hit the light
		Return L_i * f_r * cosine / pdf(wi)
	Else If ray r hit an object at q
		Return shade(q, -wi) * f_r * cosine / pdf(wi)

```

不再采样每个方向仅随机从一个方向进行路径追踪，计算着色，而在蒙特卡洛积分中，采样数越小，准确性越低，效果会变差，然而发现，其实一个像素中不止有一条光线，可以通过一个像素生成多条光线，将路径追踪后的着色值求解平均值

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20014320.png" style="zoom:50%;" />

```
//伪代码实现
ray_generation(camPos, pixel)
	Uniformly choose N sample positions within the pixel
	pixel_radiance = 0.0
	For each sample in the pixel
		Shoot a ray r(camPos, cam_to_sample)
		If ray r hit the scene at p
			pixel_radiance += 1 / N * shade(p, sample_to_cam)
	Return pixel_radiance
```

#### 5.4.2 结束条件问题

还剩一个问题，既然这是一个递归算法，那么什么时候终止呢？在之前并未设置终止条件

因此这个终止条件该怎么设置呢？

借助概率论的知识，引入俄罗斯轮盘赌的方式

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20014625.png" style="zoom:50%;" />

基本原理为，设定一个概率值：$0<P<1$：

- 射出光线的概率为$P$，由此返回的着色结果为$\frac{L_0}{P}$
- 不射出光线的概率为$1-P$,由此返回的着色结果为$0$

使用这种方式发现，最后得出的期望没有变化：$E=P\times(\frac{L_0}{P})+(1-P)\times0=L_0$

```
shade(p, wo)
	Manually specify a probability P_RR
	Randomly select ksi in a uniform dist. in [0, 1]
	If (ksi > P_RR) return 0.0;
	
	Randomly choose ONE direction wi~pdf(w)
	Trace a ray r(p, wi)
	If ray r hit the light
		Return L_i * f_r * cosine / pdf(wi) / P_RR
	Else If ray r hit an object at q
		Return shade(q, -wi) * f_r * cosine / pdf(wi) / P_RR
```

#### 5.4.3 光源采样问题

最后一个问题，这个算法并不高效，然而只有当像素采样达到一定阈值才能得到相对高质量的结果

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20015041.png" style="zoom:50%;" />

考虑出现这个问题的原因：因为均匀采样，只有极少数方向才能打到光源，大多数方向的光线被浪费掉了

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/ray-tracing-47.png" style="zoom:67%;" />

对此，考虑直接对光源采样，发现此时每一条光线都是有贡献的，又因为蒙特卡洛积分必须在同一积分域上采样，所以需要将空间中的面光源投影到球面上

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20015346.png)

由图可知，关系如下：
$$
d\omega=\frac{dA\cos\theta^{\prime}}{|x^{\prime}-x|^2}
$$
将这个式子重新带入渲染方程：
$$
 \begin{align*}
 L_o(p,\omega_o)&=\int_{H^2}L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)\cos\theta d\omega_i\\
 &=\int_{H^2}L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)\frac{\cos\theta\cos\theta^{\prime}}{|x^{\prime}-x|^2}dA
 \end{align*}
$$
那么现在就该考虑物体本身发光带来的影响了：

- 光的直接照射：直接采样光源，无需俄罗斯轮盘赌
- 光的间接反射：反射，漫反射，需要俄罗斯轮盘赌

```
shade(p, wo)
	# Contribution from the light source.
	Uniformly sample the light at x’ (pdf_light = 1 / A)
	L_dir = L_i * f_r * cos θ * cos θ’ / |x’ - p|^2 / pdf_light
	
	# Contribution from other reflectors.
	L_indir = 0.0
	Test Russian Roulette with probability P_RR
	Uniformly sample the hemisphere toward wi (pdf_hemi = 1 / 2pi)
	Trace a ray r(p, wi)
	If ray r hit a non-emitting object at q
		L_indir = shade(q, -wi) * f_r * cos θ / pdf_hemi / P_RR
	Return L_dir + L_indir
```

最后我们来说以下路径追踪的效果

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-29%20020021.png" style="zoom:50%;" />

#### 5.4.4 前方的区域以后再来探索吧~

- 半球采样——一定是均匀的吗？怎么采样效果最好，如果是一般的图形呢？

- 蒙特卡洛积分中概率分布函数的选取——怎样才是最佳的选择？（重要采样方法）

- 这里任意的一个方向和生成随机数对结果有影响吗？——采取低差异序列是一种不错的选择

- 可以从半球面和光源处采样，那可以组合起来吗？——可以，一种优化方式即为多阶段抽样（multiple imp. sampling）

- 像素的着色是这个像素出发的所有光线着色的平均值，但是这种加权只能是平均吗？——不一定，一种加权方式为像素重构滤波（pixel reconstruction filter）

- 像素所接受到的光照和它实际的各种属性（颜色等）是一样的吗？——不是，需要通过一种伽马空间的变换才能得到这些属性

  