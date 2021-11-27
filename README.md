# FAstar
## 算法介绍
本项目提出了一种基于优化IDA星的贝叶斯网络学习研究方法 FAstar

(1) 使用逆序图构建搜索树，并采用位向量和位操作让变量修改更为高效。在拓展过程中进行深度优先搜索，忽略搜索过程中不符合估计函数的节点，实现对搜索深度的限制，减少了无效搜索的花销

(2) 采用线性表作为搜索节点的存储结构，保存节点的唯一标志信息，在方便检索的同时大大减少内存空间占用。对节点的插入进行局部优化，提高搜索的最优性，避免高额的排序开销

(3) 根据BN特点对搜索图进行分枝剪除，减少浪费在低效路径上的搜索。实验结果表明，FAstar算法不仅可以处理变量数量更多的数据，而且还明显提高了精确度和运行效率

## 操作环境配置
该项目需要在Ubuntu系统上运行，以下配置假定使用纯Ubuntu 18.04 x64
### gcc-4.8.5 和 g++-4.8.5
```
1. 首先确保你使用的是 gcc-4.8.5 和 g++-4.8.5，你可以使用命令 "gcc --version" 和 "g++ --version" 来检查版本

2. 安装命令为： sudo apt-get install -y gcc-4.8 g++-4.8

3. 如果您的电脑系统只有 gcc-4.8 和 g++-4.8 一种版本，请忽略此步骤。如果有多个版本，请执行下述步骤：
	ls /usr/bin
	update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50 #(50 means high priority)
	update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
	update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 20 #(20 means low priority,gcc-7 means another version of gcc)
	update-alternatives --config gcc
4. 不管您是否有多个版本的gcc，请执行以下步骤：
	vim ~/.bashrc # (Add the following 5 lines at the end of the file)
	export C_INCLUDE_PATH=$HOME/local/include:$C_INCLUDE_PATH
	export CPLUS_INCLUDE_PATH=$HOME/local/include:$C_INCLUDE_PATH
	export LD_LIBRARY_PATH=$HOME/local/lib:$HOME/local/lib64:$LD_LIBRARY_PATH
	export LIBRARY_PATH=$LD_LIBRARY_PATH
	export PATH=$HOME/local/bin:$PATH
	source $HOME/.bashrc	
```
### boost1.63.0
```
1. 如果您的系统已经具有不兼容的Boost版本，请执行以下步骤以删除现有的Boost，如果没有，请跳过这些步骤，然后直接下载boost1.63.0
    进入目录 "/usr/lib" 使用命令 "rm `ls | grep" boost "`"
    进入目录 "/usr/include" 使用命令 "rm -rf boost"
2. 安装 boost1.63.0 库:
	cd /home
	wget https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.bz2/download
	mv download boost_1_63_0.tar.bz2
	tar --bzip2 -xvf boost_1_63_0.tar.bz2
	cd boost_1_63_0
	./bootstrap.sh --prefix=$HOME/local
	./b2 install
	mkdir $HOME/local/bin
```
### 安装bazel以运行URLearning评分模块
```
1. 要安装该模块，可参阅 (https://docs.bazel.build/versions/master/install-ubuntu.html#install-with-installer-ubuntu)，您需要下载 bazel-0.4.5-installer-linux-x86_.sh
	apt-get install pkg-config zip g++ zlib1g-dev unzip python
	add-apt-repository ppa:openjdk-r/ppa
	apt-get update
	apt-get install openjdk-8-jdk
	chmod +x bazel-0.4.5-installer-linux-x86_64.sh
	./bazel-0.4.5-installer-linux-x86_64.sh --user
```
## 对样本评分以获得PSS文件
本模块将介绍如何基于示例文件获取分数文件。您需要下载项目包：urlearning-cpp-dev.zip和样本文件：asia_s500_v1.csv，可下载于文件夹中
### 编译项目
```
1. 当配置了gcc-4.8.5、g ++-4.8.5 和 boost 1.63.0 环境并下载了项目文件时，您可以编译代码。成功编译后，您可以使用"score"
	cd urlearning-cpp-dev/
	./configure --prefix=$HOME/local
	make
	make install
```
### 获取PSS成绩文件
```
1. 使用 "score" 来转换 asia_s500_v1.csv 为 asia_s500_v1.pss
  xxx@xxx:~$ score asia_s500_v1.csv asia_s500_v1.pss
  URLearning, Score Calculator
  Input file: 'asia_s500_v1.csv'
  Output file: 'asia_s500_v1.pss'
  Delimiter: ','
  Constraints file: ''
  r_min: '5'
  Scoring function: 'BIC'
  ESS: '1.000000'
  Maximum parents: '0'
  Threads: '1'
  Running time (per variable): '-1'
  Has header: 'false'
  Enable end-of-scoring pruning: 'true'
  Enable deCampos-style pruning (experimental for BDeu): 'False'
  Parsing input file.
  Initializing data specifications.
  recordFile.getRecords()[0].size(): 8
  Creating AD-tree.
  Thread: 0, Variable: 0, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 0, Size before pruning: 120, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 0, Size after pruning: 1, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 1, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 1, Size before pruning: 120, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 1, Size after pruning: 7, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 2, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 2, Size before pruning: 120, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 2, Size after pruning: 1, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 3, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 3, Size before pruning: 120, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 3, Size after pruning: 7, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 4, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 4, Size before pruning: 120, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 4, Size after pruning: 7, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 5, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 5, Size before pruning: 120, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 5, Size after pruning: 8, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 6, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 6, Size before pruning: 120, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 6, Size after pruning: 5, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 7, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 7, Size before pruning: 120, Time: Mon Aug 17 04:48:19 2020
  Thread: 0, Variable: 7, Size after pruning: 10, Time: Mon Aug 17 04:48:19 2020
   0.050580s wall, 0.030000s user + 0.010000s system = 0.040000s CPU (40.1%)

	结果：我们得到了asia_s500_v1.pss，您可以在下载页面进行下载
```
### 附言
1. 请注意，运行路径不包括中文
2. 您可以在下载文件夹中获得完整的Asia（样本大小为500、1000）和Child数据集（样本大小分别为500、1000和5000）。亚洲有8个变量，儿童有20个变量。数据包中提供的原始CSV数据需要通过“得分”方法转换为可运行的PSS文件
3. 如果要添加约束，则可以使用命令“score --help”查找命令的格式
## 根据分数文件获取贝叶斯网络
本模块将介绍如何在FAstar算法中生成贝叶斯网络。首先，您需要下载代码包：FAstar.zip，另请参见下载文件夹。
### 建立贝叶斯网络
```
1. 使用 "make" 命令构建项目
	cd FAstar
	make
2. 将pss文件放到以下目录:FAstar/dist/Debug_astar/GNU-Linux-x86，当然你也可以在运行时指定文件目录
3. 使用 astar-debug.exe 来获取网络
	./astar-debug asia_s500_v1.pss
	xxx@xxx:~/FAstar/dist/Debug_astar/GNU-Linux-x86$ ./astar-debug asia_s500_v1.pss
	URLearning, DFBnB
  Dataset: 'asia_s500_v1.pss'
  Net file: ''
  Reading score cache: 'asia_s500_v1.pss'
  threshold = 0.500000	Cutset = 100
  Creating sparse parent graphs
  Creating bitset data structures
  Initializing search variables
  shortest path, nodes.size = 256
  3, 0, 2, 5, 1, 4, 6, 7, 
  best parents :
   optimalParents[0] = {}
   optimalParents[1] = {5, }
   optimalParents[2] = {}
   optimalParents[3] = {}
   optimalParents[4] = {1, }
   optimalParents[5] = {2, 3, }
   optimalParents[6] = {5, }
   optimalParents[7] = {3, 4, }
  score: 1133.481079
  END
  Nodes expanded: 257
  shortpath, nodes.size = 256

  running time: 0.013875 s!
  Memory footprint(KB)=29968
```
### 附言
1. 该程序的主要功能在文件中：a_star_internal_main.cpp
2. 如果要修改参数值设置，请特别注意对文件score_cache.h的修改
3. 如果要添加约束，则可以使用命令“ ./astar-debug --help”来查找命令的格式
## 混淆矩阵
本模块将指导您获取基于贝叶斯网络的混淆矩阵，以了解诸如网络准确性之类的指标。首先，您需要下载文件：Cmatrix.zip。请参阅下载文件夹
### 编译代码
```
1. 使用以下命令编译文件，可以参考readme.txt
	cd Cmatrix
	gcc Cmatrix.cpp -lstdc++ -o Cmatrix
	
	结果：我们得到可执行文件：Cmatrix.exe
```
### 生成混淆矩阵
```
1. 首先将生成的贝叶斯网络结构复制到“txt”文本中
	asia_s500_v1_network.txt A file opens as follows:
		8
		<varset> optimalParents[0] = {}
		<varset> optimalParents[1] = {5, }
		<varset> optimalParents[2] = {}
		<varset> optimalParents[3] = {}
		<varset> optimalParents[4] = {1, }
		<varset> optimalParents[5] = {2, 3, }
		<varset> optimalParents[6] = {5, }
		<varset> optimalParents[7] = {3, 4, }
2. 然后将标准网络“ asiagraph.txt”和以上文件放在“ Cmatrix /”目录中
3. 最后，运行以下命令以获取结果
	./Cmatrix Parameter1.txt Parameter1.txt
			Standard network    Current network
	xxx@xxx:~/Cmatrix$ ./Cmatrix asiagraph.txt asia_s500_v1_network.txt
	5  3  

	2  54  

	acc = 0.921875	pre = 0.714286	rec = 0.625	f1 = 0.666667
```
