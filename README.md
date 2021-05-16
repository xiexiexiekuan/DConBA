# DConBN
## 算法介绍
我们提出了一种基于IDA星优化（DConBN）的贝叶斯网络学习方法
1.在逆序图中，我们使用深度优先搜索方法遍历节点。二进制位向量和位操作用于快速方便地查询节点的最佳父集。此外，我们优化了双向链接列表中节点的存储顺序，这有助于避免对列表中的节点进行排序。这样可以更好地扩展更好的节点，从而提高学习效率。
2.根据贝叶斯网络的特点，采用动态阈值修正方法，进一步提高了效率和准确性。边缘搜索中的阈值根据BN得分和遍历节点的层数动态更新。这可以帮助选择适当数量的优秀节点来进行扩展。此外，我们根据节点受阈值限制的最大次数来修剪节点。这样可以减少内存消耗并提高效率，从而在一定程度上增加可以处理的最大变量数。
3.我们使用Child and Asia数据集进行实验并验证DConBN的有效性。实验结果表明，FringeBN不仅提高了精度和效率，而且占用的存储空间更少。此外，与A *，动态编程（DP），分支定界（B＆B）和DFBnB的现有算法相比，FringeBN可以处理具有更多变量的数据，并且具有更好的学习效率和准确性。
## 操作环境配置
该项目需要在Ubuntu系统上运行。以下配置假定使用纯Ubuntu 18.04 x64
### 安装操作环境
```c
▼ gcc-4.8.5 和 g++-4.8.5
● 首先，确保你使用的是 gcc-4.8.5 和 g++-4.8.5，你可以使用命令 "gcc --version" 和 "g++ --version" 来检查版本
● 安装命令为：
    	sudo apt-get install -y gcc-4.8 g++-4.8
● 如果您的电脑系统只有 gcc4.8 和 g++ 4.8 一种版本，请忽略此步骤。如果有多个版本，请执行下述步骤：
	ls /usr/bin
	update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50 #(50 means high priority)
	update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
	update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 20 #(20 means low priority,gcc-7 means another version of gcc)
	update-alternatives --config gcc
● 不管您是否有多个版本的gcc，请执行以下步骤：
	vim ~/.bashrc # (Add the following 5 lines at the end of the file)
	export C_INCLUDE_PATH=$HOME/local/include:$C_INCLUDE_PATH
	export CPLUS_INCLUDE_PATH=$HOME/local/include:$C_INCLUDE_PATH
	export LD_LIBRARY_PATH=$HOME/local/lib:$HOME/local/lib64:$LD_LIBRARY_PATH
	export LIBRARY_PATH=$LD_LIBRARY_PATH
	export PATH=$HOME/local/bin:$PATH
	source $HOME/.bashrc
	
▼ boost1.63.0
● 如果您的系统已经具有不兼容的Boost版本，请执行以下步骤以删除现有的Boost，如果没有，请跳过这些步骤，然后直接下载boost1.63.0
    进入目录 "/usr/lib" 使用命令 "rm `ls | grep" boost "`"
    进入目录 "/usr/include" 使用命令 "rm -rf boost"
● 安装 boost1.63.0 库:
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
▼ bazel-0.4.5
● 要安装该模块，可参阅 (https://docs.bazel.build/versions/master/install-ubuntu.html#install-with-installer-ubuntu)，您需要下载 bazel-0.4.5-installer-linux-x86_.sh。
	apt-get install pkg-config zip g++ zlib1g-dev unzip python
	add-apt-repository ppa:openjdk-r/ppa
	apt-get update
	apt-get install openjdk-8-jdk
	chmod +x bazel-0.4.5-installer-linux-x86_64.sh
	./bazel-0.4.5-installer-linux-x86_64.sh --user
## 对样本评分以获得PSS文件
本模块将介绍如何基于示例文件获取分数文件。首先，您需要下载项目包：urlearning-cpp-dev.zip，然后还需要下载示例中使用的示例文件：asia_s500_v1.csv。请转到所有下载的“下载”文件夹
### 编译项目
▼ 当配置了gcc-4.8.5，g ++-4.8.5和boost 1.63.0环境并下载了项目文件时，您可以编译代码。 成功编译后，您可以使用"score"
	cd urlearning-cpp-dev/
	./configure --prefix=$HOME/local
	make
	make install
### 获取PSS成绩文件
▼ 使用 "score" 来转换 asia_s500_v1.csv 为 asia_s500_v1.pss
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

	结果：我们得到了asia_s500_v1.pss，您可以下载页面进行下载
```
### 附言
-请注意，运行路径不包括中文
-您可以在下载文件夹中获得完整的Asia（样本大小为500、1000）和Child数据集（样本大小分别为500、1000和5000）。亚洲有8个变量，儿童有20个变量。数据包中提供的原始CSV数据需要通过“得分”方法转换为可运行的PSS文件
-如果要添加约束，则可以使用命令“ score --help”查找命令的格式
## 根据分数文件获取贝叶斯网络
本模块将介绍如何在FringeBN算法中生成贝叶斯网络。首先，您需要下载代码包：FringeBN.zip，另请参见下载文件夹。
### 建立贝叶斯网络
```
▼ 使用 "make" 命令构建项目
	cd FringeBN
	make
▼ 将pss文件放到以下目录:FringeBN/dist/Debug_astar/GNU-Linux-x86，当然你也可以在运行时指定文件目录
▼ 使用 astar-debug.exe 来获取网络
	./astar-debug asia_s500_v1.pss
	xxx@xxx:~/FringeBN/dist/Debug_astar/GNU-Linux-x86$ ./astar-debug asia_s500_v1.pss
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
2.附言
-该程序的主要功能在文件中：a_star_internal_main.cpp
-如果要修改参数值设置，请特别注意对文件score_cache.h的修改
-如果要添加约束，则可以使用命令“ ./astar-debug --help”来查找命令的格式

## 混淆矩阵
本模块将指导您获取基于贝叶斯网络的混淆矩阵，以了解诸如网络准确性之类的指标。首先，您需要下载文件：Cmatrix.zip。请参阅下载文件夹。

### 编译代码
```
▼ 使用以下命令编译文件，可以参考readme.txt
	cd Cmatrix
	gcc Cmatrix.cpp -lstdc++ -o Cmatrix
	
	结果：我们得到可执行文件：Cmatrix.exe
### 生成混淆矩阵
▼ 首先将在“网络文件”页面中生成的贝叶斯网络结构复制到“ txt”文本中
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
▼ 然后将标准网络“ asiagraph.txt”和以上文件放在“ Cmatrix /”目录中
▼ 最后，运行以下命令以获取结果
	./Cmatrix Parameter1.txt Parameter1.txt
			Standard network    Current network
	xxx@xxx:~/Cmatrix$ ./Cmatrix asiagraph.txt asia_s500_v1_network.txt
	5  3  

  2  54  

  acc = 0.921875	pre = 0.714286	rec = 0.625	f1 = 0.666667
```