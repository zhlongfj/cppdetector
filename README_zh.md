# cppdetector

<center>
    <a href="https://github.com/zhlongfj/cppdetector" target="_blank" rel="noopener noreferrer">
        <img src="https://img.shields.io/github/issues/zhlongfj/cppdetector?style=flat-square" alt="version"/>
    </a>
    <a href="https://github.com/zhlongfj/cppdetector" target="_blank" rel="noopener noreferrer">
        <img src="https://img.shields.io/github/repo-size/zhlongfj/cppdetector?style=flat-square" alt="version"/>
    </a>
    <a href="https://github.com/zhlongfj/cppdetector" target="_blank" rel="noopener noreferrer">
        <img src="https://img.shields.io/github/stars/zhlongfj/cppdetector" alt="version"/>
    </a>
    <a href="https://github.com/zhlongfj/cppdetector" target="_blank" rel="noopener noreferrer">
        <img src="https://img.shields.io/github/languages/count/zhlongfj/cppdetector?style=flat-square" alt="version"/>
    </a>
    <a href="https://github.com/zhlongfj/cppdetector" target="_blank" rel="noopener noreferrer">
        <img src="https://img.shields.io/github/forks/zhlongfj/cppdetector" alt="version"/>
    </a>
    <a href="https://github.com/zhlongfj/cppdetector" target="_blank" rel="noopener noreferrer">
        <img src="https://img.shields.io/github/license/zhlongfj/cppdetector" alt="version"/>
    </a>
</center>


## :large_blue_circle: Internationalization

[English](README.md) | 中文文档

## :information_source: 介绍
cppdector受到[TscanCode](https://github.com/Tencent/TscanCode)的启发。在使用[TscanCode](https://github.com/Tencent/TscanCode)的过程中，发现[TscanCode](https://github.com/Tencent/TscanCode)缺少部分团队需要的检测项，如：

* 声明public的成员变量
* lambda以引用捕获所有变量
* [谷歌c++风格](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide)，如：定义非POD类型的[静态和全局变量](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/scoping/?highlight=POD#static-and-global-variables)

cppdetector吸收了[TscanCode](https://github.com/Tencent/TscanCode)中的一些规则，并增加了实际开发中得到验证的原则([非线程安全的单例模式检测](todo))， [谷歌c++风格](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide)，[effectvie C++](todo)等编程规范，帮助程序员从一开始就发现代码缺陷，提高代码质量。

cppdetector通过正则和字符串匹配检测代码。在检测时，不需要编译被检测代码。

## :eight_spoked_asterisk: 编译环境
任何 支持C++17(filesystem)的 编译器都可以工作。

可选择的编译器：

* Visual Studio 2017 version 15.7(or above)
* Linux：GCC 8.0(or later)
* Mac：clang 7.0(or later)

## :gem: 编译
cppdetector采用cmake进行工程配置
### Windows
#### cmake command

```
//cd到cppdetector目录
mkdir build 
cd build
cmake ..
cmake --build . --config RelWithDebInfo
//you can Open the cppdetector.sln to compile in the Build directory  
```
#### IDE打开cmake项目

* clion打开cppdetector根目录
* Visual Studio->“打开本地文件夹”，选中cppdetector根目录

### Mac
#### cmake command

```
//cd到cppdetector目录
mkdir build
cd build
cmake ..
cmake --build . --config RelWithDebInfo
#you can build with multi-core, eg: 6 core
#cmake --build . --config RelWithDebInfo -j6
#you can compile with `make` on Linux and Mac
#make
```
####I DE打开cmake项目

* clion打开cppdetector根目录

## :gem: 运行
### Windows
`cppdetector multithread "codepath"`
### Mac
`./cppdetector multithread /Users/hualongzhang/work/cppdetector/detector_core`

## 参数

Parameter  | Description
------------- | -------------
Param1  | singlethread, multithread or multiprocess 
Param2  | 代码路径
Param3 | 例外配置文件路径
Param4 | 规则名配置文件路径
Param5 | 结果存放路径

### 例外配置文件格式

```
[
    "/Users/hualongzhang/work/cppdetector/detector_core/3rdparty",
    "/Users/hualongzhang/work/cppdetector/detector_core/common/codeconversion.h"
]
```
### 规则名配置文件格式
可由代码生成：`DetectorCommon().setDetectorRuleNames((resultDir / "detectorRuleNames.json").string()`

数组规则名如下：

```
{
	"ArrayDetector": [
		"ArrayRuleIndexOutOfBounds",
		"ArrayRuleIndexUsedBeforeCheck",
		"ArrayRuleIndexCheckDefectively",
		"ArrayRuleBufferOverflow",
		"ArrayRuleIndexOutOfBoundsFromFunc",
		"ArrayRuleIndexOutOfBoundsInLoop",
		"ArrayRuleMemsetZeroByte"
	]
}
```

### 可能的方式

```
./cppdetector multithread "/Users/hualongzhang/work/cppdetector/detector_core"
./cppdetector multithread "/Users/hualongzhang/work/cppdetector/detector_core" "/Users/hualongzhang/work/cppdetector" 
./cppdetector multithread "/Users/hualongzhang/work/cppdetector/detector_core" "/Users/hualongzhang/work/cppdetector" "/Users/hualongzhang/work/cppdetector/supporting/exceptionconfig.json"
./cppdetector multithread "/Users/hualongzhang/work/cppdetector/detector_core" "/Users/hualongzhang/work/cppdetector" "/Users/hualongzhang/work/cppdetector/supporting/exceptionconfig.json" 
./cppdetector multithread "/Users/hualongzhang/work/cppdetector/detector_core" "/Users/hualongzhang/work/cppdetector" "/Users/hualongzhang/work/cppdetector/supporting/exceptionconfig.json" 
"/Users/hualongzhang/work/cppdetector/supporting/detectorRuleNames.json"
./cppdetector multithread "/Users/hualongzhang/work/cppdetector/detector_core" "/Users/hualongzhang/work/cppdetector" "/Users/hualongzhang/work/cppdetector/supporting/exceptionconfig.json" 
"/Users/hualongzhang/work/cppdetector/supporting/detectorRuleNames.json" /Users/hualongzhang/work/cppdetector/bin/detectorResult
```

## :gift:测试
### windows

运行脚本进行测试，你也可以更改run.bat中的代码路径来检测其他代码

```
cd cppdetector\release\windows_x64
run.bat
```


## :stuck_out_tongue_winking_eye: 作者

github: [zhlongfj](https://github.com/zhlongfj)

email: zhlongfj@sina.com

## :copyright: 许可

[License MIT](LICENSE)

[badags](https://shields.io/category/social)
[谷歌C++编程规范]
(https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/)
