### 10.18~10.25

#### 本周内容

* 实现一个射击打靶的游戏, 子弹击中位置离靶心越近得分越高
* 实现多人游戏机制。多个玩家在限定时间内击打多个靶子, 游戏时间结束后按分数排名, 分数高者胜。 

#### app和演示视频

* [演示视频链接](https://pan.baidu.com/s/12VeMLM39Tw6oQpuZqhX0Mw), 提取码: swnx
* [apk链接](https://pan.baidu.com/s/1xchUwp2Zx55AifL1jhJb7Q), 提取码: rgap

#### 游戏流程

* 初始化

  游戏服务器启动之后, 等待玩家加入游戏。在游戏开始之间玩家可以进行射击, 但不会获得分数。当加入游戏的玩家大于等于两个时, 游戏开始。

* 游戏开始

  显示"Game Started"字样并开始倒计时, 游戏时间为20秒。在游戏时间内玩家对靶子进行多次射击, 击中位置离靶心越近获得的分数越高。当游戏倒计时为0时, 游戏结束。

* 游戏结束

  显示"Game Ended"字样, 然后公示每位玩家的最终得分, 格式为"Player Name  final Score:  Score"。最后根据得分最多者输出胜者, 格式为"Winner is Player name"。游戏结束后玩家可以进行射击, 但不会获得分数。 

#### 游戏设计

* 基于发射体和碰撞检测的子弹系统

  参考自[官方文档的多人游戏入门教程](https://docs.unrealengine.com/en-US/Gameplay/Networking/QuickStart/index.html), 定义```ThirdPersonMPProjectile```作为子弹类。在构造函数中创建一个```Sphere Component```并设置作为```RootComponent```，再往```RootComponent```上绑定一个``Projectile Movement Component``, 子弹就拥有了碰撞检测和移动的基础。通过```SphereComponent->OnComponentHit.AddDynamic```注册在```OnComponentHit```事件发生时被调用的函数```OnProjectileImpact```, 在该函数中实现生成碰撞效果, 产生伤害的逻辑。

* 根据碰撞位置计算得分

  定义```AThirdPersonMPTarget```作为靶子类, 通过重载每次被击中后调用的```TakeDamage```函数实现分数计算和增加到特定Player。

  ```c++
  TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
  ```

  * 通过```DamageCauser->GetActorLocation()```和```AThirdPersonMPTarget::GetActorLocation()```分别获取碰撞位置和靶心位置, 计算两者间距离并根据距离越小分数越多的原则赋分。
  * 通过```DamageCauser->GetOwner()```获得发出子弹的玩家, 调用其```AddScore()```方法实现分数的增加。

* 计时系统

  在```AThirdPersonMPGameMode```中实现了计时功能, 定义```MatchRemainTime```为当前游戏剩下的时间, 每局游戏初始化并维护该变量。如果```MatchRemainTime```大于等于零, 则```MatchRemainTime -= 1```并通过```SetTimer```递归调用计时函数, 否则游戏结束。

* 分数同步以及决定胜者

  ```APlayerState```中恰好有```Score```变量, 可以方便地在server端通过```GetScore()```和```SetScore()```方法进行维护。由于```APlayerState```本身就是replicated的, 也省去了同步的工作。游戏结束后, 在服务端根据```APlayerState```中的```Score```取最大者就是胜者。

#### 遇到的问题和解决方法

​	一开始尝试使用蓝图, 用得不顺手, 而且网络同步不好实现, 于是抛弃了蓝图的使用。参照[官方文档的多人游戏入门教程](https://docs.unrealengine.com/en-US/Gameplay/Networking/QuickStart/index.html)搭起了游戏的基本框架。 [C++ example game project ShooterGame](https://docs.unrealengine.com/en-US/Resources/SampleGames/ShooterGame/index.html)的代码帮助十分大, 阅读了online部分后, 模仿完成了游戏网络部分的实现。





