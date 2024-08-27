# MatPly 

```text
    __  ___      __  ____  __     
   /  |/  /___ _/ /_/ __ \/ /_  __
  / /|_/ / __ `/ __/ /_/ / / / / /
 / /  / / /_/ / /_/ ____/ / /_/ / 
/_/  /_/\__,_/\__/_/   /_/\__, /  
                         /____/   
```

## 💡什么是MatPly？
> MatPly是使用C语言实现并被转换为多个语言版本的矩阵操作库  
> 目前提供的语言以及支持平台的版本有：
> - Windows/Linux/Android平台下Dart语言版本
> ![procsee](doc/API/Dart/src/process.png)

## 🔗网页文档版本
> [https://www.robot-shadow.cn/src/pkg/MatPly_Dart/site/](https://www.robot-shadow.cn/src/pkg/MatPly_Dart/site/)

## 🔗Github地址
> [https://github.com/PythonnotJava/MatPly](https://github.com/PythonnotJava/MatPly)

## 🔗pub仓库
> [https://pub.dev/packages/matply](https://pub.dev/packages/matply)

## ⚠️Warning
<p style="text-indent: 20pt;font-weight: lighter">
Matply在调用C API时采用的dll文件，
由源代码使用Path从pub下载源寻找dll的绝对路径，
然而，在实际开发的时候，如Flutter编译生成可执行文件到别的客户端环境，
是会发生dll查找失败的问题，这时您需要从MatPly的源代码（默认是C:\Users\USERNAME\AppData\Local\Pub\Cache\hosted）中将依赖的dll复制到您的资源文件夹中。重新赋值路径到pubCacheDir即可。
</p>