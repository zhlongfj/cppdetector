# CPPDetector

cppdetector是一款C++的静态代码检测工具，后续会逐步将effective C++，谷歌编程规范，诺瓦编程规范中的条款引入到检测规则中。

cppdetector参数如下：

参数1：标识应用采用何种方式运行：

* 多线程："multithread"

* 多进程："multiprocess"

* 单线程："singlethread"

参数2：被检测的代码路径

参数3(可选)：例外代码路径，存放例外文件数组的JSON文件，参见：exceptionconfig.json

参数4：检测的规则项，存放规则的JSON文件，参见：detectorRuleNames.json

示例：run.bat，检测代码，只要修改第2个参数，即被检测代码路径后即可双击运行检测

示例：checklastpush.bat，检测最后一次提交记录的代码，只需要将codePath设置成git库的更目录即可：set codepath=F:\work\git\viplexcore\

