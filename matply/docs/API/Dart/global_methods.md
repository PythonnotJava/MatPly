# 对矩阵的全局设置

## set_visible_round
设置打印矩阵数据的格式

## get_visible_round
获取打印矩阵数据的格式

## set_round
设置矩阵操作中的误差精度

## get_round
获取矩阵操作中的误差精度

## set_seed
设置随机种子

## initMp
在打算创建矩阵实例之前，可以通过无参数传入声明这是一个开端，此处毫无作用，仅仅为了规范；如果创建了第一个矩阵实例，则可以选择性传入这个矩阵的self值，此值将作为链表的头结点
> 关于Mp的实现，它的底层是一个简单的链表结构，同时记录存储了多少个`Pointer<Pointer<Matrix>>?`（因为创建失败返回空指针的也算）。凡涉及到__new__方法的创建，都会触发Signal信号，添加节点到Mp

## Signal
手动添加新节点，不建议在开发中使用

## getInstances
获取存储矩阵的self个数，也就是创建了多少个矩阵实例

## freeMp
统一释放内存，防止内存泄漏
> * 添加了地址进制指定，hex为true打印十六进制地址否则打印十进制地址。另外从

## set_mult_rand[new from V1.0.9;deleted from V1.1.0]
当开启多线程的时候，为了保护线程安全，C底层采用rand_s/rand_r来获取伪随机数，默认开启
> 注：自1.0.9版本开始，如果一个随机模拟方法多次调用，一定要使用多线程安全；如果一个随机模拟方法只调用了一次，可以选择使用单线程模式

## get_mult_rand[new from V1.0.9;deleted from V1.1.0]
获取是否设置了使用多线程随机数

## set_max_thread_support[new from V1.1.0]
设置当前最大线程数

## get_max_thread_support[new from V1.1.0]
获取当前最大线程数

## get_max_thread_sys[new from V1.1.0]
获取系统最大线程数

## set_simple_dvcst_value[new from V1.1.0]
安全的设置被视为简单程序的多线程启动量
> 所谓安全的，即一次设置，永久上锁，即使在线程竞争的条件下，也只按照第一个被设置的量启动

## get_simple_dvcst_value[new from V1.1.0]
获取被视为简单程序的多线程启动量

## set_complex_dvcst_value[new from V1.1.0]
安全的设置被视为复杂程序的多线程启动量

## get_complex_dvcst_value[new from V1.1.0]
获取被视为复杂程序的多线程启动量

## get_time[new from V1.1.0]
获取当前运行时间帧，类似Python的time.time方法，可以使用Stopwatch类代替

## set_multp_shown[new from V1.1.0]
设置底层线程信息可视化启动

## get_multp_shown[new from V1.1.0]
获取底层线程信息可视化是否启动

## set_simple_dvcst_value_force[new from V1.1.0]
[_**Danger**_]强制修改被视为简单程序的多线程启动量，没有任何数值要求

## set_complex_dvcst_value_force[new from V1.1.0]
[_**Danger**_]强制修改被复杂简单程序的多线程启动量，没有任何数值要求

[下一篇：构造函数](constructor.md)