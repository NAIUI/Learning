# [Visual Studio介绍](https://www.bilibili.com/video/BV1S541137P2/?spm_id_from=333.999.0.0)

### 一、工具介绍篇

* Visual Studio  V.S.  Codeblocks  V.S.  Visual Studio Code

* 工具安装修改简介

* Visual Studio C++简单工程演示

### 二、工具配置篇

* 界面配置
  * 配色
  * 启动
* VA配置
  * VA简介
  * 高亮
* 杂项配置：
  * 字体
  * Tab配置
  * 代码边界Limit

### 三、工具使用篇[tank-1990]

* 应用程序工程
  * 简单应用建立
  * 多种模板区别
  * 解决方案-工程
  * 解决方案配置Debug/Release(区别)，x86/x64(兼容性)
  * 工程操作：新建、添加、删除等
  * 重要工程属性修改
* lib静态库工程
  * 简单lib应用建立
  * 通用依赖建立
  * vs简化依赖建立
* dll动态库工程
  * import导入dll工程建立
    ``` 
    _declspec(dllexport)修饰函数 返回值与函数名之间加：__stdcall 链接时改为dllimport
    例：
      _declspec(dllexport) int __stdcall Init(const char* which);
      
    // C导出
    #ifdef __cplusplus
    extern "C"{
    #endif
    ...
    
    #ifdef __cplusplus 
    }
    #endif
    ```
  * 动态加载dll工程建立
    1. 库的加载：`LoadLibrary, dlopen`
    2. 获取函数地址：`GetProcAddress, dlsym`
    3. 调用某个函数完成某个功能
    4. 卸载：`FreeLibrary, dlclose`
    ```
    typedef int(__stdcall* Init)(const char* which);  
    // using Init = int(__stdcall*)(const char* which);
    ```
  * 简单插件工程
* Linux跨平台工程

### 四、工程组织篇(Tank-1990)

* 手动多工程组织
  * 编译排错篇（穿插）
  * 工程选项修改（穿插）
* cmake工程组织
- 版本管理（穿插）

### 五、代码调试篇

* 常用调试手段
* 断点篇
* 多线程调试
* 性能内存监视
* 远程调试

### 六、附录

* Tanks-1992

  版权声明：源代码来源为：https://github.com/krystiankaluzny/Tanks，欢迎大家自行下载并支持原作者。附件中仅供学习练习使用！！！


* SDL 官网

  [Simple DirectMedia Layer - SDL version 2.0.14 (stable)] http://www.libsdl.org/download-2.0.php

  下载：[SDL2-devel-2.0.14-VC.zip]

* SDL TTF 2.0

  http://www.libsdl.org/projects/SDL_ttf/

   [SDL2_ttf-devel-2.0.15-VC.zip](http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip) (Visual C++ 32/64-bit)

* SDL Image

  http://www.libsdl.org/projects//SDL_image/

   [SDL2_image-devel-2.0.5-VC.zip](http://www.libsdl.org/projects//SDL_image/release/SDL2_image-devel-2.0.5-VC.zip) (Visual C++ 32/64-bit)
