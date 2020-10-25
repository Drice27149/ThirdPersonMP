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

#### 遇到的问题和解决方法

​	一开始尝试使用蓝图, 用得不顺手, 而且网络同步不好实现, 于是抛弃了蓝图的使用。参照[官方文档的多人游戏入门教程](https://docs.unrealengine.com/en-US/Gameplay/Networking/QuickStart/index.html)搭起了游戏的基本框架。 [C++ example game project ShooterGame](https://docs.unrealengine.com/en-US/Resources/SampleGames/ShooterGame/index.html)的代码帮助十分大, 阅读了online部分后, 模仿完成了游戏网络部分的实现。





