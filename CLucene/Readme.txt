一、安装需要软件

1.g++

2.cmake

3.zlib（安装方法apt-get insatll zlib1g-dev，使用数据源是网易的镜像，注意zlib后是“一”不是“l”）

二、安装步骤

1.cd到clucene目录下，输入“cmake -G KDevelop3”

2.执行命令：make

3.安装：sudo make install

三、测试

1.cd到src/test目录下，执行：make cl_test，则会在bin/目录下产生一个cl_test执行文件，在bin目录下输入./cl_test

2.cd到src/demo目录下，执行：make cl_demo，也会在bin/目录下产生一个cl_demo执行文件，同上

 

说明：其他版本的clucene，也可以按这个步骤安装，不过需要改一下配置文件，因为make时提示，uint32_t没有定义，所以在配置文件中加入这些定义即可.
