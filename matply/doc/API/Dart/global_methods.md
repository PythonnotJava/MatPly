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

## initMp[new from V1.0.2]
在打算创建矩阵实例之前，可以通过无参数传入声明这是一个开端，此处毫无作用，仅仅为了规范；如果创建了第一个矩阵实例，则可以选择性传入这个矩阵的self值，此值将作为链表的头结点
> 关于Mp的实现，它的底层是一个简单的链表结构，同时记录存储了多少个`Pointer<Pointer<Matrix>>?`（因为创建失败返回空指针的也算）。凡涉及到__new__方法的创建，都会触发Signal信号，添加节点到Mp

## Signal[new from V1.0.2]
手动添加新节点，不建议在开发中使用

## getInstances[new from V1.0.2]
获取存储矩阵的self个数，也就是创建了多少个矩阵实例

## freeMp[new from V1.0.2]
统一释放内存，防止内存泄漏
> [new from V1.0.8]
> * 添加了地址进制指定，hex为true打印十六进制地址否则打印十进制地址。另外从
