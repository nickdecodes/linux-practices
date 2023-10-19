# linux_note

[鸟哥私房菜](https://linux.vbird.org) ｜ [菜鸟linux](https://www.runoob.com/linux/linux-tutorial.html)

- [文件管理](#文件管理)
    - [文件类型](#文件类型)
    - [文件权限](#文件权限)
        - [更改权限-chmod](#更改权限-chmod)
        - [更改用户-chown](#更改用户-chown)
        - [更改组别-chgrp](#更改组别-chgrp)
    - [用户管理](#用户管理)
        - [切换用户-su](#切换用户-su)
        - [临时切换-sudo](#临时切换-sudo)
        - [用户密码-passwd](#用户密码-passwd)
        - [群组密码-gpasswd](#群组密码-gpasswd)
        - [更改脚本-chsh](#更改用户-chsh)
        - [修改用户-usermod](#修改用户-usermod)
        - [新建用户-useradd](#新建用户-useradd)
        - [删除用户-userdel](#删除用户-userdel)
        - [显示用户-id](#显示用户-id)
    - [文件目录](#文件目录)
        - [目录切换-cd](#目录切换-cd)
        - [目录显示-pwd](#目录显示-pwd)
        - [目录建立-mkdir](#目录建立-mkdir)
        - [目录删除-rmdir](#目录删除-rmdir)
        - [目录查看-ls](#目录查看-ls)
    - [文件管理](#文件管理)
        - [文件复制-cp](#文件复制-cp)
        - [文件删除-rm](#文件删除-rm)
        - [文件移动-mv](#文件移动-mv)
        - [反向列示-tac](#反向列示-tac)
        - [行号打印-nl](#行号打印-nl)
        - [翻页查看-more](#翻页查看-more)
        - [翻页查看-less](#翻页查看-less)
        - [数据截取-head](#数据截取-head)
        - [数据截取-tail](#数据截取-tail)
        - [创建文件-touch](#创建文件-touch)
        - [隐藏属性-chattr](#隐藏属性-chattr)
        - [隐藏属性-lsattr](#隐藏属性-lsattr)
        - [特殊权限-SUID|SGID|SBIT](#特殊权限-SUID|SGID|SBIT)
        - [文件查找-find](#文件查找-find)
        - [打包解包-tar](#打包解包-tar)
- [文本处理](#文本处理)
    - [文本查找-grep](#文本查找-grep)
    - [进程查找-pgrep](进程查找-pgrep)
    - [树状显示-pstree](#树状显示-pstree)
    - [文本排序-sort](#文本排序-sort)
    - [文本转换-tr](#文本转换-tr)
    - [文本切分-cut](#文本切分-cut)
    - [文本拼接-paste](#文本拼接-paste)
    - [文本统计-wc](#文本统计-wc)
    - [数据处理-sed](#数据处理-sed)
    - [数据处理-awk](#数据处理-awk)
    - [数据提取-xargs](#数据提取-xargs)
    - [文本分割-split](#文本分割-split)
- [性能分析](#性能分析)
    - [进程查询-ps](#进程查询-ps)
    - [进程监控-top](#进程监控-top)
    - [文件查询-lsof](#文件查询-lsof)
    - [内存用量-free](#内存用量-free)
    - [资源限制-ulimit](#资源限制-ulimit)
- [网络工具](#网络工具)
    - [网卡配置-ifconfig](#网卡配置-ifconfig)
    - [网络连接-netstat](#网络连接-netstat)
    - [查看路由-route](#查看路由-route)
    - [检查网络-ping](#检查网络-ping)
    - [转发路径-traceroute](#转发路径-traceroute)
    - [网络分析-nc](#网络分析-nc)
    - [命令行抓包-tcpdump](#命令行抓包-tcpdump)
    - [域名解析-dig](#解析工具-dig)
    - [网络请求-curl](#网络请求-curl)
- [开发及调试](#开发及调试)
    - [编辑器-vim](#编辑器-vim)
    - [编译器-gcc和g++](#编译器-gcc和g++)
    - [调试工具-gdb](#调试工具-gdb)
    - [查看依赖库-ldd](#查看依赖库-ldd)
    - [二进制文件分析-objdump](#二进制文件分析-objdump)
    - [ELF文件格式分析-readelf](#elf文件格式分析-readelf)
    - [跟踪进程中系统调用-strace](#跟踪进程中系统调用-strace)
    - [跟踪进程栈-pstack](#跟踪进程栈-pstack)
    - [进程内存映射-pmap](#进程内存映射-pmap)
- [其他](#其他)
    - [终止进程-kill](#终止进程-kill)
    - [终止进程-pkill](#终止进程-pkill)
    - [修改文件权限-chmod](#修改文件权限-chmod)
    - [创建链接-ln](#创建链接-ln)
    - [显示文件尾-tail](#显示文件尾-tail)
    - [版本控制-git](#版本控制-git)
    - [设置别名-alias](#设置别名-alias)
- [认识与学习BASH](#认识与学习BASH)
    - [命令查询-type](#命令查询-type)

------

## 文件管理

### 文件类型

使用 ls -al 命令可以查看当前路径下所有文件的详细信息

```bash
$ ls -al
➜  notes git:(main) ls -al
total 64
drwxr-xr-x  12 zhengdongqi  staff    384  8 21 19:26 .
drwxr-xr-x@  7 zhengdongqi  staff    224  8 20 15:50 ..
-rw-r--r--@  1 zhengdongqi  staff  10244  8 21 20:08 .DS_Store
drwxr-xr-x  14 zhengdongqi  staff    448  8 21 20:20 .git
-rw-r--r--   1 zhengdongqi  staff    447  8 21 19:26 .gitmodules
-rw-r--r--   1 zhengdongqi  staff  11357  8 20 15:30 LICENSE
-rw-r--r--@  1 zhengdongqi  staff     14  8 20 15:47 README.md
```

该命令主要输出了七列内容，分别为：权限，文件数，所属用户，所属群组，文件大小，常见日期，文件名。

第一列权限，主要可以分为以下四个部分：文件类型，所属用户权限，所属组权限，其它用户权限。

以刚才执行的结果为例

| 文件类型 | 所属用户权限 | 所属群组权限 | 其它用户权限 |
| -------- | ------------ | ------------ | ------------ |
| d        | rwx          | r-x          | r-x          |

第一部分文件类型 d，代表这个文件是一个目录（directory），目录是一种特殊文件；

第二部分所属用户权限为 rwx, 代表该文件拥有者拥有可读(read), 可写(write)，可执行(execute)的权限；

第三部分所属组权限为r-x,代表该文件拥有者在一个群组的用户具有可读，可执行的权限，在这里-顶替了w的位置，代表没有写权限；

第四部分其它用户权限同样为可读，可执行。

> Linux中的文件类型出来目录d之外，总共有7种文件类型，在这里我们做一个简要的了解；

```bash
r	# (regular file)  常规文件
d 	# (directory) 目录
i 	# (link) 链接文件
b 	# (block) 块设备 存储数据以供系统存取的接口设备，也就是硬盘
c 	# (character) 字符设备 串口设备， 键盘， 鼠标等
s 	# (socket) 套接字
p 	# (pipe) 管道
```

对于普通文件又可以分为以下三种：

纯文本文件

> 纯文本文件使用ASCII编码，这是Linux系统中最常见的一种文件类型，之所以成为纯文本文件，是因为这种类型的文件是我们可以直接读取的的内容，在Linux，几乎所有的配置文件都属于这种类型的。

二进制文件

> 二进制文件是系统中的可执行文件(不包括脚本)，计算机只能认识并执行二进制文件，二进制文件不能使用 cat 等命令直接读出。

数据格式的文件

> 在一些程序运行过程中，需要读取待定格式的文件，这种文件被称为数据文件(data.file)，这种文件通常也不能使用cat命令读出。但是可以使用last读取其中命令。
>

### 文件权限

对于文件权限，我们也可以用以下的方式来表示：

|   r    |   w    |   x    |   r    |   w    |   x    |   r    |   w    |   x    |
| :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: |
| (2^2)4 | (2^1)2 | (2^0)1 | (2^2)4 | (2^1)2 | (2^0)1 | (2^2)4 | (2^1)2 | (2^0)1 |

#### 更改权限-chmod 

```bash
			u # (user)			+ (加入)			r (read)
chmod		g # (group)			- (移除)			w (write)           文件或目录
			o # (other)			= (设置)			x (execute)
			a # (all)	

chmod a+x file # 给file文件都赋予执行的权限
chmod o-x file # 将file文件o减去执行权限
chmod 755 file # 设置file文件的权限为 rwxr-xr-x
chmod u=rwx, go=rx file # 设置file文件的权限为 rwxr-xr-x
```

#### 更改用户-chown 

```bash
chown zhengdongqi:haizei file # 修改file的所属用户是zhengdongqi，所属组为haizei
chown -R zhengdongqi:haizei directory # 修改目录directory及目录下的所有文件的所属用户是zhengdongqi，所属组为haizei
chown zhengdongqi file # 修改file的所属用户为zhengdongqi
```

#### 更改组别-chgrp

```bash
chgrp root file # 修改file所属的组为root
```

| 组件 |     内容      |  替代对象  |      r       |      w       |              x               |
| :--: | :-----------: | :--------: | :----------: | :----------: | :--------------------------: |
| 文件 | 详细数据 data |   文件夹   | 读到文件内容 | 修改文件内容 |         执行文件内容         |
| 目录 |    文件名     | 可分类抽屉 |  读到文件名  |  修改文件名  | 进入该目录的权限 key文件目录 |

### 用户管理

| 配置文件     | 内容                                               |
| ------------ | -------------------------------------------------- |
| /etc/passwd  | 用户名 密码位 用户编号 归属组编号 姓名 $HOME Shell |
| /etc/shadow  | 用户名 已加密密码 密码改动信息 密码策略            |
| /etc/group   | 群组名 密码位 群组编号 组内用户                    |
| /etc/gshadow | 群组密码相关文件                                   |
| /etc/sudoers | 用户名 权限定义 权限                               |

#### 切换用户-su

```bash
su [-lmpfc] <username>
-       # 重新登录 当前用户不仅切换为指定用户的身份，同时所用的工作环境也切换为此用户的环境（包括 PATH 变量、MAIL 变量等），使用 - 选项可省略用户名，默认会切换为 root 用户。
-l      # 重新登录 同 - 的使用类似，也就是在切换用户身份的同时，完整切换工作环境，但后面需要添加欲切换的使用者账号。
-p      # 不更改环境变量 表示切换为指定用户的身份，但不改变当前的工作环境（不使用切换用户的配置文件）。
-m      # 不更改环境变量 和 -p 一样；
-c command # 切换后执行命令， 并退出 仅切换用户执行一次命令，执行后自动切换回来，该选项后通常会带有要执行的命令。
```

#### 临时切换-sudo

```bash
sudo [-siul] <command>
-s	# 切换为root shell
-i	# 切换为root shell,并初始化
-u usernae|uid # 执行命令的身份
-l	# 显示自己的权限
```

#### 用户密码-passwd

```bash
passwd [-dleSxnsf] <command>
-d		# 清除密码
-l		# 暂时锁定用户，该选项会在 /etc/shadow 文件中指定用户的加密密码串前添加 "!"，使密码失效。仅 root 用户可用；
-u      # 解锁用户，和 -l 选项相对应，也是只能 root 用户使用；
-e		# 使密码过期
-S		# 显示密码认证信息
-x days	# 设置该用户的密码有效期，对应 /etc/shadow 文件中各行密码的第 5 个字段；
-n days # 设置该用户修改密码后，多长时间不能再次修改密码，也就是修改 /etc/shadow 文件中各行密码的第 4 个字段；
-w      # 设置用户密码过期前的警告天数，对于 /etc/shadow 文件中各行密码的第 6 个字段；
-i      # 设置用户密码失效日期，对应 /etc/shadow 文件中各行密码的第 7 个字段。
-s   	# 更改登录用户
-f		# 更改用户信息
--stdin # 可以将通过管道符输出的数据作为用户的密码。主要在批量添加用户时使用；
```

#### 强制修改-chage

```bash
chage [选项] 用户名
-l              # 列出用户的详细密码状态;
-d 日期          # 修改 /etc/shadow 文件中指定用户密码信息的第 3 个字段，也就是最后一次修改密码的日期，格式为 YYYY-MM-DD；
-m 天数          # 修改密码最短保留的天数，也就是 /etc/shadow 文件中的第 4 个字段；
-M 天数          # 修改密码的有效期，也就是 /etc/shadow 文件中的第 5 个字段；
-W 天数          # 修改密码到期前的警告天数，也就是 /etc/shadow 文件中的第 6 个字段；
-i 天数          # 修改密码过期后的宽限天数，也就是 /etc/shadow 文件中的第 7 个字段；
-E 日期          # 修改账号失效日期，格式为 YYYY-MM-DD，也就是 /etc/shadow 文件中的第 8 个字段。
```

#### 更改脚本-chsh

```bash 
chsh -s shell <username>
```

#### 修改用户-usermod

```bash
usermod [-cdefgGlLsuU] <username>
-c string		# 修改用户的说明信息，即修改 /etc/passwd 文件目标用户信息的第 5 个字段；
-d dir			# 修改用户的主目录，即修改 /etc/passwd 文件中目标用户信息的第 6 个字段，需要注意的是，主目录必须写绝对路径；
-e days			# 修改用户的失效曰期，格式为 "YYYY-MM-DD"，即修改 /etc/shadow 文件目标用户密码信息的第 8 个字段；
-f dats			# 密码过期后宽限的日期
-g groupname 	# 修改用户的初始组，即修改 /etc/passwd 文件目标用户信息的第 4 个字段（GID）；
-G groupname	# 修改用户的附加组，其实就是把用户加入其他用户组，即修改 /etc/group 文件；
-l username		# 修改用户名称；
-L 				# 修改用户密码， 使密码无效, 临时锁定用户（Lock）；
-U 				# 解锁用户（Unlock），和 -L 对应；
-s shell		# 修改用户的登录 Shell，默认是 /bin/bash。
-u uid			# 修改用户的UID，即修改 /etc/passwd 文件目标用户信息的第 3 个字段（UID）；
```

#### 新建用户-useradd

```bash
usreadd [-dmMsugGnefcD] <username>
-d dir 			# 手工指定用户的主目录。主目录必须写绝对路径，而且如果需要手工指定主目录，则一定要注意权限；
-m				# 建立用户时强制建立用户的家目录。在建立系统用户时，该选项是默认的；
-M				# 不自动建立$HOME
-s shell		# 手工指定用户的登录 Shell，默认是 /bin/bash；
-u uid			# 手工指定用户的 UID，注意 UID 的范围（不要小于 500）
-g groupname	# 手工指定用户的初始组。一般以和用户名相同的组作为用户的初始组，在创建用户时会默认建立初始组。一旦手动指定，则系统将不会在创建此默认的初始组目录。
-G				# 指定用户的附加组。我们把用户加入其他组，一般都使用附加组；
-n				# 不建立以用户名为群组名称的群组
-e days			# 指定用户的失效曰期，格式为 "YYYY-MM-DD"。也就是 /etc/shadow 文件的第八个字段；
-f adys			# 缓冲时间，days后关闭账号
-c string   	# 手工指定/etc/passwd文件中各用户信息中第 5 个字段的描述性内容，可随意配置；
-D [表达式]  	  # 更改设定值
-o 				# 允许创建的用户的 UID 相同。例如，执行 "useradd -u 0 -o usertest" 命令建立用户 usertest，它的 UID 和 root 用户的 UID 相同，都是 0；
-r 				# 创建系统用户，也就是 UID 在 1~499 之间，供系统程序使用的用户。由于系统用户主要用于运行系统所需服务的权限配置，因此系统用户的创建默认不会创建主目录。
/etc/login.defs新建用户规则
/etc/skel/新建用户默认文件
```

#### 删除用户-userdel

```bash
userdel -r <username>
-r	# 删除用户相关的文件和目录
# 注意，在删除用户的同时如果不删除用户的家目录，那么家目录就会变成没有属主和属组的目录，也就是垃圾文件。
```

#### 显示用户-id

```bash
id [-gGnru] <username>
-g	# 下属所属组ID
-G	# 显示附加组ID
-n 	# 显示用户，所属组， 或附加群组的名称
-u	# 显示用户ID
-r	# 显示实际ID
```

#### 群组密码-gpasswd

```bash
gpasswd [-adrAM] <群组名>
	            # 选项为空时，表示给群组设置密码，仅 root 用户可用。
-A user1,...	# 将群组的控制权交给 user1,... 等用户管理，也就是说，设置 user1,... 等用户为群组的管理员，仅 root 用户可用。
-M user1,...	# 将 user1,... 加入到此群组中，仅 root 用户可用。
-r				# 移除群组的密码，仅 root 用户可用。
-R				# 让群组的密码失效，仅 root 用户可用。
-a user			# 将 user 用户加入到群组中。
-d user	        # 将 user 用户从群组中移除。
-A				# 删除密码
```

#### 群组添加-groupadd

```bash
groupadd [选项] 组名
-g GID # 指定组 ID；
-r     # 创建系统群组。
```

#### 群组修改-groupmod

```bash
groupmod [选现] 组名
-g GID   # 修改组 ID；
-n 新组名 # 修改组名；
```

#### 群组删除-groupdel

```bash
groupdel 组名
```

#### 切换群组-newgrp

```bash
newgrp 组名
```

### 文件目录

```bash
.		 	# 代表此层目录
..		 	# 代表上一层目录
-		 	# 代表前一个工作目录
~	     	# 代表目前使用者身份所在的家目录
~account 	# 代表 account 最高使用者的家目录 (account是这个账号名称)
```

#### 目录切换-cd

```bash
cd  	 	# 切换目录
cd ~dmtsai	# 代表进入 dmtsai 这个使用者的家目录，亦即/home/dmtsai
cd ~		# 表示回到自己的家目录
cd 			# 回到自己的家目录
cd ..		# 表示回到上层目录
cd -		# 表示回到刚刚的那个目录
cd ../postfix # 回到相对路径的地方
```

#### 目录显示-pwd

```bash
pwd		 	# 显示当前目录
pwd -p	 	# 显示出真正的路径，而非用链接(link)路径
```

#### 目录建立-mkdir

```bash
mkdir   	# 建立一个新目录
mkdir -m	# 设置文件的权限。直接设置，不使用默认权限(umask)
mkdir -p	# 帮助你直接将所需要的目录(包含上层目录)递归创建
```

#### 目录删除-rmdir

```bash
rmdir		# 删除一个空目录
rmdir -p	# 连同上层的空目录一起删除
```

#### 目录查看-ls

```bash
-a 			# 全部的文件，连同隐藏文件(开头为 .的文件) 一起列出来(常用)
-A			# 全部的文件，连同隐藏文件，但不包括. 与 ..这两个目录
-d			# 仅列出目录本身，而不是列出目录内的文件数据(常用)
-f			# 直接列出结果，而不是列出目录内的文件数据
-F			# 根据文件，目录等信息，给予附加数据结构
-h  		# 将文件一人类较易读的方式列出来
-i			# 列出inode号码，
-l			# 详细信息显示(常用)
-n 			# 列出 UID 与 GID 而使用者与用户组的名称
-r			# 将排序结果反向输出
-R			# 连同子目录内容一起列出来，等于该目录下的所有文件都会显示出来
-S			# 以文件容量大小排序，而不是用文件名排序
-t			# 依时间排序，而不是用文件名
--collor=never	# 不要依据文件特性给予颜色显示
--collor=always # 显示颜色
--collor=auto	# 让系统自行依据设置来判断是否给予颜色
--full-time		# 以完整时间模式(包括年，月，日，时，分) 输出：
--time={atime,ctime} # 输出access时间或改变权限属性时间(ctime),而非内容修改时间(modification time)
```

### 文件管理

#### 文件复制-cp

```bash
cp [-adfilprsu] 源文件 (source) 目标文件 (destination)
cp [options] source1 source2 source3 ... directory

-a		# 相当于-dr --preserve=all 的意思， 至于dr请参考下列说明(常用)
-d		# 若文件为链接文件的属性(link file), 直接复制链接文件属性而非文件本身
-f		# 为强制(force)的意思，若目标文件已经存在切无法开启，则删除后再尝试一下
-i		# 若目标文件(dextination)已经存在时，在覆盖时会先询问操作的运行(常用)
-l		# 进行硬链接(hard link) 的链接建立，而非复制文件本身
-p		# 连同文件的属性一起复制过去，而非使用默认属性
-r		# 递归复制
-s		# 复制成符号链接文件
-u 		# 更新拷贝
--preserve=all # 除了-p的权限相关参数外，还加入SELinux的属性，links，xattr等也复制
```

#### 文件删除-rm

```bash
rm [-fir] 文件或目录
-f 		# 即使 force 的意思， 忽略不存在的文件，不会出现警告信息
-I		# 交互模式，在删除前会询问使用者是否操作
-r		# 递归删除，最常用于目录的删除，这就是非常危险的选项
```

#### 文件移动-mv

``` bash
mv [-fiu] source destination
mv [options] soruce1 source2,source3...directory
-f		# force强制的意思，如果目标已经存在，不会询问而直接覆盖
-i		# 若目标文件(destination)已经存在，就会询问是否覆盖
-u		# 若目标文件已经存在，且source比较新，才会更新
```

#### 文件内容-cat

由第一行开始显示文件内容

```bash
cat [-AbEnTv]
-A		# 相当于-vET的整合选项，可列出一些特殊字符而不是空白字符而已
-b		# 列出行号，仅针对非空白行做行号显示，空白行不标行号
-E		# 将结尾的换行符$显示出来
-n		# 打印出行号，连同空行也会有行号，与-b的选项不同
-T		# 将[tab]按键^I显示出来
-v		# 列出一些看不出来的特殊字符
```

#### 反向列示-tac

从最后一行开始显示文件内容

#### 行号打印-nl

显示的时候，同时输出行号

```bash
nl [-bnw] 文件
-b		# 指定行号指定的方式，主要有两种
		# -b a: 表示不论是为空行，也同样列出行号(类似 cat -n)
		# -b t: 如果有空行，空的哪一行不要列出行号(默认值)
-n		# 列出行号表示的方法
		# -n ln: 行号在屏幕的最左方显示
		# -n rn：行号在自己栏位的最右方显示，且不加0
		# -n rz：行号在自己栏位的最右方显示，且加0
-w		# 行号栏位的占用的字符数
```

#### 翻页查看-more

```bash
空格键(space)		# 代表向下翻一页
Enter 	 		  # 代表向下翻一行
/字符串   		    # 代表在这个显示的内容当中，向下查找字符串这个关键词
:f 				  # 立刻显示出文件名以及目前显示的行数
q				  # 代表立刻离开more，不再显示文件内容
b    			  # 或 [ctrl]-b: 代表往回翻页，不过这个操作只对文件管用，对于管道没有用less 上下均可翻页
```

#### 翻页查看-less

```bash
空格键			    # 向下翻动一页
[pagedown]		  # 向下翻动一页
[pageup]		  # 向上翻动一页
/字符串			# 向下查找字符串的的功能
？字符串		   # 向上查找字符串的功能
n				  # 重复前一个查找(与/或？有关)
N				  # 反向的重复前一个查找( 与/或？有关)
g				  # 前进到这个数据的第一行
G 				  # 前进到这个数据的最后一行去(注意大小写)
q  				  # 离开less程序
```

#### 数据截取-head

取出前面几行

```bash
head [-n number] 文件
-n 		# 后面接数字，代表显示几行的意思
```

#### 数据截取-tail

取出后面几行

```bash
tail [-n number] 文件
-n 		# 后面接数字，代表显示几行的意思
-f		# 代表持续刷新显示后面所接文件的内容，要等到按下[ctrl]-c才会停止
```

#### 创建文件-touch

修改时间(modification time, mtime):

当该文件的【内容数据】变更时，就会更新这个时间，内容数据指的是文件内容。而不是文件的是属性或权限

状态时间(status time, ctime):

当该文件的状态改变时，就会更新这个时间，举例来说，像是权限与属性被更改了，就都会更新这个时间

读取时间(access time, atime)

当该文件的内容被读取时，就会更新这个读取时间，

```bash
touch [-acdmt] 文件
-a		# 仅自定义access time
-c		# 仅修改文件的时间，若该文件不存在则不建立新文件
-d		# 后面可以接欲自定义的日期而不用目前的日期，也可以使用--data=“日期或时间”
-m		# 仅修改mtime
-t		# 后面可以接欲定义的时间而不用目前的时间
```

#### 隐藏属性-chattr

chattr : 配置文件隐藏属性

```bash
chattr [+-=] [ASacdistu] 文件或目录名称
+		# 增加一个特殊参数，其它原本存在参数则不动
-		# 删除某一个特殊参数，其它原本存在参数则不动
=		# 直接设置参数，且仅有后面接的参数
A		# 但设置了A这个属性时，若你在存取文件或目录时，它的存取时间 atime，将不会被修改，可避免I/O较慢的的机器过度读写磁盘
S		# 一般文件是非同步写入磁盘的，如果加上S这个属性时，当你进行任何文件的修改，修改会同步写入磁盘中
a		# 当设置a后，这个文件将只能增加数据，而不能删除也不能修改数据，只有root才能设置这属性
c		# 这个属性设置之后，将会自动的将此文件压缩，在读取文件的时候将会自动压缩，但是在存储的时候，将会先进行压缩后在存储
d		# 当dump程序被执行的时候，，设置d属性将可使该文件不会被dump备份
i		# 这个i就很厉害了，它可以让一个文件不能被删除，改名，设置链接也无法写入或增添数据，对于系统的安全大有助益。
s		# 当文件设置了s属性时，如该文件被删除，它将会完全的从硬盘删除，所有如果误删，完全无法恢复
u		# 与s相反的，当使用u来配置文件时，如果该文案被删除了，则数据还在磁盘中，可以使用来恢复文件
```

#### 隐藏属性-lsattr

lsattr : 显示文件隐藏属性

```bash
lsattr [-adR] 文件或目录
-a		# 将隐藏文件的属性也显示出来
-d		# 如果接的是目录，仅列出目录本身的属性而非目录内的文件名
-R		# 连同子目录的数据也一并列出来
```

#### 特殊权限-SUID|SGID|SBIT

#### 文件查找-find

```bash
find [查找目录] [查找条件]

查找目录：
 .：在当前目录及子目录下查找（默认）
 A：在目录A及A的子目录下查找
查找条件：
-name	# 根据文件名查找
-regex	# 使用正则表达式匹配
-type	# 按类型查找（f:文件，d:目录，l:链接...）
-atime	# 按访问时间查找（n:n天前的一天内，+n:n天前(不含n天本身)，-n:n天内(不含n天)）
-mtime	# 按修改时间查找（n:n天前的一天内，+n:n天前(不含n天本身)，-n:n天内(不含n天)）
-size	# 按大小查找（单位k，+nk:"比nk更大"，-nk:"比nk更小"）
-perm	# 按权限查找（644：权限等于644的文件）
-user/-nouser	# 用户名等于/用户名不等于
-group/-nogroup	# 组名等于/组名不等于
```

示例

```bash
# 1.在当前目录及子目录下查找后缀为cpp的文件
find . -name *.cpp

# 2.使用正则表达式查找
find -regex ".*.cpp$"
```

#### 打包解包-tar

```bash
tar [-j|-z] [cv] [-f 压缩包名] [-A	追加 tar 文件到归档文件] 目录
tar [-j|-z] [xv] [-f 解压包名] [-C 解压路径]

选项：
-c/-x：打包/解包
-j/-z：bzip2格式/gzip格式
-v：显示过程
```

## 文本处理

### 文本查找-grep

使用方法

```bash
grep [选项] 模式串 文件
输出 | grep [选项] 模式串

选项
-e：使用多个模式串
-i：忽略大小写
-n：打印行号
-c：统计次数（一行算一次）
-v: 反向输出
-w: word
```

示例

```bash
# 1.在test.c中搜索包含字符串”printf“或”count“的行
grep -e "printf" -e "count" test.c
```

### 进程查找-pgrep

```bash
pgrep [-onlpgtu] <进程名>
-o 		# 起始进程号
-n		# 结束进程号
-l 		# 显示进程名称
-p		# 指定父进程
-g		# 指定进程组
-t		# 指定开启的终端进程
-u		# 指定uid
```

### 树状显示-pstree

### 文本排序-sort

使用方法

```bash
sort [选项] 文件
输出 | sort [选项]

选项
 -d：按字典序排序（默认）
 -n：按数字排序
 -k："-k n"表示按k行第n列进行排序
 -r：反序
 -f: 忽略大小写
 -b: 忽略最前面的空格符
 -M: 以月份名称排序
 -t: 分隔符，默认[TAB]
```

### 文本转换-tr

使用方法

```bash
# set1、set2为字符集，可以是单个字符，也可以是字符串
输出 | tr [选项] set1 set2

选项：
 -d：删除所有属于第一字符集的字符
 -s：字符压缩，重复写一个
 -c: 取代所有不属于第一字符集的字符
```

示例

```bash
# 1.删除字符':'
cat /etc/passwd | tr -d ':'

# 2.将小写字母替换成大写字母
last | tr '[a-z]' 'A-Z'

# 3.将'a'、'b'、'c'替换成'z'
cat test | tr “abc” 'z'

# 4.将连续的'a'压缩成'b'（单个或连续出现的多个‘a’会压缩成一个‘b’）
cat test | tr -s 'a' 'b'
```

### 文本切分-cut

使用方法

```bash
cut [选项] 文件
输出 | cut [选项]

选项：
 -d：分隔符（-d ':' 以’:‘为分隔符）
 -f：选择域（-f 1,2 输出分隔后第1列和第2列）
 -c：字符范围（-c n-m 输出第n到m个字符。如果没有m，输出到末尾）
```

示例

```bash
# 1.按’:‘分隔$PATH，输出第3个和第5个
echo $PATH | cut -d ':' -f 3,5

# 2.输出export运行结果每行的第12-20个字符
export | cut -c 12-20
```

### 文本拼接-paste

使用方法

```bash
paste [选项] file1 file2

选项：
 -d：指定拼接时使用的分隔符（默认使用tab作为分隔符）
```

### 文本统计-wc

使用方法

```bash
wc [选项] 文件
输出 | wc [选项]

选项：
 -c：统计字符数
 -w：统计单词数
 -l：统计行数
```

### 数据处理-sed

sed常用于一整行的处理。如果有一个100万行的文件，要在第100行加某些文字，此时由于文件太大，不适合用vim处理。因此使用sed是个很好的选择

使用方法

```bash
sed [选项] '[动作]' 文件
输入 | sed [选项] '[动作]'

选项：
 -n：安静模式，只输出sed处理过的行（否则未处理行也会输出）
 -i：结果直接作用到文件（没指定时不会修改文件）
 -e：在命令行模式上输入动作
 -f：从文件中读取动作

动作：[n1[,n2]] function
function:
 a/i：在后插入/在前插入
 d：删除
 p：打印
 s：替换
```

示例

```bash
# 1.插入
nl /etc/passwd | sed '2a drink tea' #在第2行后插入一行："drink tea"
nl /etc/passwd | sed '2a aaa \
> bbb' #在第2行后插入两行："aaa"和"bbb"

# 2.删除
nl /etc/passwd | sed '2,5d' #删除2~5行
sed '/^$/d' ip #将ip文件中的空行删除

# 3.打印2~5行（安静模式，不使用安静模式2~5行会打印2次）
nl /etc/passwd | sed -n '2,5p'

# 4.替换
nl /etc/passwd | sed '2s/daemon/root/g' #将第二行的daemon替换成root
ifconfig | grep 'inet addr' | sed 's/^.*addr://g' #将所有开头的“inet addr:”删除
```

### 数据处理-awk

相比于sed常用于一整行的处理，awk则比较倾向于将一行分成数个“字段”来处理。因此，相当适合小型的数据处理

**awk处理步骤**：

1. 读入第一行，并将第一行的数据填入$0,$1,$2等变量当中
2. 依据条件类型的限制，判断是否需要进行后面的动作
3. 做完所有的动作与条件类型
4. 若还有后续的“行”的数据，则重复1~3步，直到所有的数据都读完为止

使用方法

```bash
awk '条件类型1{动作1} 条件类型2{动作2} ...' filename
输出 | awk '条件类型1{动作1} 条件类型2{动作2} ...'

变量：
 $0		# 整行
 $1		# 按分隔符分隔后的第1列
 $2		# 按分隔符分隔后的第2列
 $k		# 按分隔符分隔后的第k列
 NF		# 每一行拥有的字段数
 NR		# 目前所处理的行数
 FS		# 目前的分隔字符（默认是空格或tab）
# 条件判断：>、<、>=、<=、==、!=
# 命令分隔：使用';'或Enter
```

示例

```bash
# 1.打印last -n 5结果中每行经过分隔符(默认情况下为空格或tab)分隔后的第1列和第3列
last -n 5 | awk '{print $1 "\t" $3}'

# 2.以':'作为分隔符，打印第3列小于10的所有行的第1列和第3列
cat /etc/passwd | awk '{FS=":"} $3<10{print $1 "\t" $3}'      #（第一行不会处理）
cat /etc/passwd | awk 'BEGIN{FS=":"} $3<10{print $1 "\t" $3}' #（第一行会处理）
cat /etc/passwd | awk -F : 'BEGIN{print "start"} $3<10{print $1 "\t" $3}' # (第一行会处理)
# 3.假设test文件由3列数字组成，以空格分隔。该命令会计算每行的和然后打印
awk '{total=$1+$2+$3;printf "%10d %10d %10d %10.2f\n",$1,$2,$3,total}' test
```

> 注意上面的示例2，awk首先是读取一行，分隔后的数据填入$0,$1,$2等变量中才开始进行条件判断和执行动作。因此第一条命令在按空格或tab分隔后才将分隔符换成':'，所以第一行显示结果不对

### 数据提取-xargs

```bash
xargs [option] [cmmmand]
-0		# 将特殊字符还原为普通字符
-eEOF	# 当xargs读到EOF时停止
-p		# 执行指令前询问
-n num 	# 每次执行command时需要的参数个数
```

### 文本分割-split

```bash
split [bl] <file> 
-b size # 切分为size大小的文件
-l num 	# 以num行为大小切分
```

## 性能分析

### 进程查询-ps

man ps手册非常庞大，不是很好查阅，因此主要记住几个命令

- a：显示一个终端的所有进程，除会话引线外；
- u：显示进程的归属用户及内存的使用情况；
- x：显示没有控制终端的进程；
- -l：长格式显示更加详细的信息；
- -e：显示所有进程；

示例

```bash
# 1.列出仅与自身环境有关的进程，最上层的父进程是允许该ps命令的bash而没有扩展到init进程中去
ps -l

# 2.列出系统所有进程的信息
ps aux    # 可以查看系统中所有的进程；
ps -le    # 可以查看系统中所有的进程，而且还能看到进程的父进程的 PID 和进程优先级；
ps -ef    # aux会截断COMMAND列，-ef不会。aux是BSD风格，-ef是System V风格
ps axjf   # 以"进程树"的方式显示所有进程
ps -lA    # 输出格式同ps -l
```

```bash
$ ps -l
UID   PID  PPID        F CPU PRI NI       SZ    RSS WCHAN     S             ADDR TTY           TIME CMD
501 35992 35991     4006   0  31  0 35049696   6384 -      S                   0 ttys000    1:01.95 -zsh

F：		# 进程标志，说明进程的权限
-4		 # root权限
-1		 # 仅能fork而不能exec
-0		 # 既非4也非1

S				# 进程的状态
-R(running)		# 正在运行
-S(Sleep)		# 可被唤醒的睡眠
-D				# 不可被唤醒的睡眠（通常可能在等待I/O）
-T				# 停止，可能是在后台暂停
-Z(Zombie)		# 僵尸进程

C				# CPU使用率

PRI/NI			# Priority/Nice的缩写，CPU优先级(越小越高)

ADDR/SZ/WCHAN	# 内存相关，ADDR指出进程在内存的哪个部分，running进程一般显示'-'。SZ为进程使用的内存。WCHAN表示进程当前是否运行中'-'，当进程睡眠时，指出进程等待的事件

TTY				# 进程运行的终端机
TIME			# 进程用掉的CPU时间
```

```bash
$ ps aux
USER               PID  %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
zhengdongqi      35992   0.2  0.0 35311840   7732 s000  S    14 822    1:02.55 -zsh

USER			# 进程所属用户
%CPU/%MEM		# 进程消耗的CPU百分比和内存百分比
VSZ				# 进程用掉的虚拟内存(KB)
RSS				# 进程占用的固定内存(KB)
TTY				# 进程运行的终端机，与终端机无关则显示'?'。tty1~tty6是本机的登陆者程序，pts/0等表示由网络连接进主机的进程
STAT			# 进程目前的状态，与```ps -l```结果中的**S**等同
START			# 进程启动的时间
TIME			# 进程实际使用的CPU运行时间
```

### 进程监控-top

使用方法

```bash
top [选项]

选项：
-b			# 使用批处理模式输出。一般和"-n"选项合用，用于把 top 命令重定向到文件中；
-c			# 显示完整的命令
-d			# 秒数：指定 top 命令每隔几秒更新。默认是 3 秒；
-s			# 使 top 命令在安全模式中运行，避免在交互模式中出现错误；
-S			# 累积模式
-u	unname	# 用户名：只监听某个用户的进程；
-n			# 次数：指定 top 命令执行的次数。一般和"-"选项合用；
-p			# 进程PID：仅查看指定 ID 的进程；
-q			# 给尽可能高的优先级
```

**top模式下的命令**：

| 命令   | 描述                                                         |
| ------ | ------------------------------------------------------------ |
| ? 或 h | 显示交互模式的帮助                                           |
| P      | 按照 CPU 的使用率排序，默认就是此选项；                      |
| M      | 按照内存的使用率排序；                                       |
| N      | 按照 PID 排序；                                              |
| q      | 退出 top 命令；                                              |
| 1      | 多核情况下切换CPU                                            |
| c      | 显示完整信息                                                 |
| T      | 按照 CPU 的累积运算时间排序，也就是按照 TIME+ 项排序；       |
| k      | 按照 PID 给予某个进程一个信号。一般用于中止某个进程，信号 9 是强制中止的信号； |
| r      | 按照 PID 给某个进程重设优先级（Nice）值；                    |

> **%Cpu(s)后面的“wa”表示I/O wait，过高说明长时间等待I/O，I/O存在瓶颈**

### 文件查询-lsof

使用方法

```bash
lsof [选项]

选项：
 -i			# -i:端口号查看端口被占用的情况
 -u			# 后跟用户名查看具体用户打开的文件
 -p			# 后跟PID查看指定进程打开的文件
 +d			# 后跟目录查看指定目录下被进程打开的文件，"+D"递归
```

### 内存用量-free

使用方法

```bash
free [选项]

选项：
-b|-k|-m|-g # 以字节，KB，M，G显示
-o			# 忽略缓冲区调节列
-t			# 列出物理内存与swap的汇总情况    
-h 		  	# 以可读形式显示
```

```bash
$ free
             total       used       free     shared    buffers     cached
Mem:      32305048   31504312     800736       7568    2191884   16048656
-/+ buffers/cache:   13263772   19041276
Swap:            0          0          0

buffers # 主要缓存dentry和inode等元数据
cached # 主要缓存文件内容，即page cache
buffers/cache # 实际使用的内存。used-buffers-cached
buffers/cache # 可用内存。free+buffers+cached（在内存紧张时，buffers和cached可以回收）
```

[详细结果说明](https://fixatom.com/linux-free-cmd-buffers-and-cached/)

### 磁盘用量-dh

```bash
df [选项] [目录或文件名]
-a	# 显示所有文件系统信息，包括系统特有的 /proc、/sysfs 等文件系统；
-m	# 以 MB 为单位显示容量；
-k	# 以 KB 为单位显示容量，默认以 KB 为单位；
-h	# 使用人们习惯的 KB、MB 或 GB 等单位自行显示容量；
-T	# 显示该分区的文件系统名称；
-i	# 不用硬盘容量显示，而是以含有 inode 的数量来显示。
```

### 磁盘统计-du

```bash
du [选项] [目录或文件名]
-a # 显示每个子文件的磁盘占用量。默认只统计子目录的磁盘占用量
-h # 使用习惯单位显示磁盘占用量，如 KB、MB 或 GB 等；
-s # 统计总磁盘占用量，而不列出子目录和子文件的磁盘占用量
du -ah --max-depth=1
```

### 资源限制-ulimit

使用方法

```bash
ulimit [选项]      # 查看
ulimit [选项] 新值  # 修改

选项：
 -a：列出shell进程的所有资源限制情况（-a命令会列出查看某一资源限制的选项参数）
 ...
```

> 使用`ulimit`修改资源限制只会对当前终端环境有效，如果想永久生效，可以修改文件`/etc/security/limits.conf`，该文件的内容如下；

```bash
# /etc/security/limits.conf
#
#Each line describes a limit for a user in the form:
#
#<domain>        <type>  <item>  <value>
#
#Where:
#<domain> can be:
#        - a user name
#        - a group name, with @group syntax
#        - the wildcard *, for default entry
#        - the wildcard %, can be also used with %group syntax,
#                 for maxlogin limit
#        - NOTE: group and wildcard limits are not applied to root.
#          To apply a limit to the root user, <domain> must be
#          the literal username root.
#
#<type> can have the two values:
#        - "soft" for enforcing the soft limits
#        - "hard" for enforcing hard limits
#
#<item> can be one of the following:
#        - core - limits the core file size (KB)
#        - data - max data size (KB)
#        - fsize - maximum filesize (KB)
#        - memlock - max locked-in-memory address space (KB)
#        - nofile - max number of open files
#        - rss - max resident set size (KB)
#        - stack - max stack size (KB)
#        - cpu - max CPU time (MIN)
#        - nproc - max number of processes
#        - as - address space limit (KB)
#        - maxlogins - max number of logins for this user
#        - maxsyslogins - max number of logins on the system
#        - priority - the priority to run user process with
#        - locks - max number of file locks the user can hold
#        - sigpending - max number of pending signals
#        - msgqueue - max memory used by POSIX message queues (bytes)
#        - nice - max nice priority allowed to raise to values: [-20, 19]
#        - rtprio - max realtime priority
#        - chroot - change root to directory (Debian-specific)
#
#<domain>      <type>  <item>         <value>
#

#*               soft    core            0
#root            hard    core            100000
#*               hard    rss             10000
#@student        hard    nproc           20
#@faculty        soft    nproc           20
#@faculty        hard    nproc           50
#ftp             hard    nproc           0
#ftp             -       chroot          /ftp
#@student        -       maxlogins       4

# End of file
```

示例

```bash
root@068ca8da6d06:/# ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 7863
max locked memory       (kbytes, -l) 82000
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1048576
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) unlimited
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
```

## 网络工具

### 网卡配置-ifconfig

### 网络连接-netstat

```bash
netstat [选项]

选项：
-a			# 将所有的连接、监听、Socket数据都列出来（如，默认情况下，不会列出监听状态的连接）
-t			# 列出tcp连接
-u			# 列出udp连接
-n			# 将连接的进程服务名称以端口号显示（如下图中Local Address会换成10.0.2.15:22）
-l			# 列出处于监听状态的连接
-p			# 添加一列，显示网络服务进程的PID（需要root权限）
-i			# 显示网络接口列表，可以配合ifconfig一起分析
-s			# 打印网络统计数据，包括某个协议下的收发包数量
-alnt 
```

```bash
$ netstat
Active Internet connections (w/o servers)
Proto Recv-Q Send-Q Local Address               Foreign Address             State
tcp        0      0 localhost:41173             localhost:epmd              TIME_WAIT
tcp        0      0 localhost:53385             localhost:epmd              ESTABLISHED
tcp        0      0 ip-172-31-6-51.ap-sou:43640 ip-172-31-15-143.ap-so:6379 ESTABLISHED
tcp        0      0 ip-172-31-6-51.ap-sou:36732 ip-172-31-20-237.:ddi-tcp-1 TIME_WAIT

Active Internet connections（w/o servers）# 网络相关的连接
Recv-Q # 接收队列(已接收还未递交给应用)
Send-Q # 发送队列(接收方未确认的数据)
Local Address # 本地IP(主机):端口(服务名)
Foreign Address # 远端IP:端口
Recv-Q和Send-Q通常应该为0，如果长时间不为0可能存在问题
Active UNIX domain sockets（w/o servers）# 本地相关的套接字
RefCnt # 连接到此socket的进程数
Flags # 连接标识
Type # socket访问的类型
Path # 连接到此socket的相关程序的路径
```

[netstat的10个基本用法](https://linux.cn/article-2434-1.html)

### 查看路由-route

### 检查网络-ping

### 转发路径-traceroute

### 网络分析-nc

### 命令行抓包-tcpdump

使用方法

```bash
sudo tcpdump [选项] ...

选项：
 -D/-i：查看/指定网卡
```

示例

```bash
# 抓取本地9877号端口的TCP数据包
sudo tcpdump -i lo tcp port 9877
```

### 域名解析-dig

### 网络请求-curl

## 开发及调试

### 编辑器-vim

### 编译器-gcc和g++

[C程序的编译过程](https://www.cnblogs.com/CarpenterLee/p/5994681.html)

使用方法

```bash
gcc/g++ [选项] 源文件

选项：
 -E			# 让编译器在预处理之后停止，不进行后续编译过程，得到.i文件
 -S			# 让编译器在编译之后停止 ，不进行后续过程，得到.s文件
 -c			# 生成机器码即二进制.o文件
 -o			# 指定目标文件名
 -g			# 在编译的时候生成调试信息
 -Wall		# 生成所有警告信息
 -I 目录	   # 指定头文件的查找目录
 生成动态链接库：
        1. gcc/g++ -c -fPIC 源文件 -o 目标文件名
        2. gcc -shared 目标文件名 -o 动态链接库名.so
    生成静态链接库：
        1. gcc/g++ -c 源文件 -o 目标文件名
        2. ar -crv 静态链接库名.a 目标文件名
    -l库名 -L 目录：引入链接库，-L指定查找该库的目录。如-lm表示引入libm.so
```

### 调试工具-gdb

使用方法

```bash
# 第一步：得到可执行文件
gcc/g++ -o 可执行文件 -g 源文件

# 第二步：启动gdb
gdb # 启动gdb

# 第三步：执行gdb命令进行调试
(gdb) gdb命令

gdb命令：
 file 	# 可执行文件：导入需要调试的文件
 r		# 运行程序
 q		# 退出gdb
 b		# 设置断点
     b	# 行号
     b 	# 函数名称
     b 	# *函数名
     b 	# *代码地址
     b 	# 编号
 c		# 继续执行，直到下一断点或程序结束
 s		# 执行一行代码，如果此行代码有函数调用则进入函数
 n		# 执行一行代码，如果此行代码有函数调用，不进入函数，直接执行函数
 i(info) 子命令	# 查看某些信息（只输入info或i可以查看有哪些子命令）
     info thread  # 查看进程的所有线程，会显示每个线程的序号（1~n）
 thread 线程序号   # 切换到相应的线程（线程序号可以由info thread得到）
 f(frame) 函数栈帧号	# 切换到相应的函数栈帧（函数栈帧号可以由where等命令得到）
 list：查看源码
     list 行号	# 查看指定行号附近的源码
     list 函数	# 查看指定函数附近的源码
     list 文件:行号	# 查看指定文件中指定行附近的代码
 where	# 查看当前位置
 p(print) /格式 表达式
     格式：
         x	# 按十六进制格式显示变量
         d	# 按十进制格式显示变量
         u	# 按十六进制格式显示无符号整形
         o	# 按八进制格式显示变量
         t	# 按二进制格式显示变量
         a	# 按十六进制格式显示变量
         c	# 按字符格式显示变量
         f	# 按浮点数格式显示变量
     表达式中可用的操作符：
         @	# 一个和数组有关的操作符，左边是起始地址，右边是长度（p *arr@3）
         ::	# 指定一个在文件或是函数中的变量（p 'f2.c'::x）
         {<type>}<addr>	# 一个指向内存<addr>的类型为type的一个对象
 x(examine) <n/f/u> <addr>	# 查看内存
     n	# 正整数，表示需要显示的内存单元个数
     f	# 显示的格式（格式字母同上面的print）
     u	# 每个单元的字节数
         b	# 1字节
         h	# 2字节
         w	# 4字节（默认）
         g	# 8字节
```

### 查看依赖库-ldd

### 二进制文件分析-objdump

### ELF文件格式分析-readelf

### 跟踪进程中系统调用-strace

### 跟踪进程栈-pstack

### 进程内存映射-pmap

## 其他

### 终止进程-kill

```bash
kill [-alpsu] <PID>
-a		# 处理信号进程时，不限制命令名和进程号的对应关系
-l信号PID # 不加信号ID，则列出全部信号
-p pid	 # 给PID的进程只打印相关进程号，而不是发送任何信号
-s		# 指定要发送的信号
-u		# 指定用户
kill -9 pid
kill pid
```

### 终止进程-pkill

```bash
pkill [-onpgt] <进程名称>
-o		# 起始pid
-n		# 结束pid
-p pid	# 指定父进程号发送信号
-g 		# 指定进程组
-t		# 指定中端
```

### 创建链接-ln

```c
ln [选项] [file] [tofile]
-b 删除，覆盖以前建立的链接
-d 允许超级用户制作目录的硬链接
-f 强制执行
-i 交互模式，文件存在则提示用户是否覆盖
-n 把符号链接视为一般目录
-s 软链接(符号链接)
-v 显示详细的处理过程
```

### 版本控制-git

### 设置别名-alias

### 进程树表示-pstree

```bash
pstree [选项] [PID或用户名]
-a	# 显示启动每个进程对应的完整指令，包括启动进程的路径、参数等。
-c	# 不使用精简法显示进程信息，即显示的进程中包含子进程和父进程。
-n	# 根据进程 PID 号来排序输出，默认是以程序名排序输出的。
-p	# 显示进程的 PID。
-u	# 显示进程对应的用户名称。
```

### 登陆用户-w-who

```bash
w [选项] [用户名]
-h	# 不显示输出信息的标题
-l	# 用长格式输出
-s	# 用短格式输出，不显示登陆时间，JCPU 和 PCPU 时间
-V	# 显示版本信息
```

```bash
who [选项] [file]
-a	# 列出所有信息，相当于所有选项。
-b	# 列出系统最近启动的时间日期。
-l	# 列出所有可登陆的终端信息。
-m	# 仅列出关于当前终端的信息，who -m 命令等同于 who am i。
-q	# 列出在本地系统上的用户和用户数的清单。
-r	# 显示当前系统的运行级别。
-s	# 仅显示名称、线路和时间字段信息，这是 who 命令的默认选项。
-u	# 显示当前每个用户的用户名、登陆终端、登陆时间、线路活动和进程标识。
-T 或 -w	# 显示 tty 终端的状态，“+”表示对任何人可写，“-”表示仅对 root 用户或所有者可写，“？”表示遇到线路故障。
```

### 过去登陆-last-lastlog

```bash
last [选项]
-a	# 把从何处登陆系统的主机名或 IP 地址显示在最后一行。
-R	# 不显示登陆系统的主机名或 IP 地址。
-x	# 显示系统关机、重新开机以及执行等级的改变等信息。
-n  # 显示列数	设置列出信息的显示列数。
-d	# 将显示的 IP 地址转换成主机名称。
```

## 认识与学习BASH

### 命令查询-type

```bash
type [-tpq] name
			# 不加任何选项与参数时，type会显示出name是外部命令还是bash内置命令
-t			# 当加入-t参数时，type将name以下这些字眼显示出它的意义
	file	# 表示位外部命令
	alias	# 表示该命令位命令别名所设置的名称
	builtion# 表示该命令位bash内置的命令功能
-p			# 如果后面接的name为外部命令时，才会显示完整的文件名
-a			# 会由PATH变量定义的路径中，将所有含name的命令都列出来，包含alias
```
