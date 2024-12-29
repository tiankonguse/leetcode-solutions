# Leetcode 所有题目题解


## 几个原则  


1. 所有题目的格式，按5位的题号，每100个一组放在[problemset-new](./problemset-new)下。 例如 123 题，5位就是 00123，放在 001 目录下。  
2. 每个目录或文件后面会有一段话，那是最后一题提交时的描述，大家可以忽略那个。  
3. [link-new.md](link-new.md) 索引目前是自动生成，所有题都可以通过这个索引快速到达。  
4. 请不要删除不是自己的文件！
5. [category.md](category.md)是对题目的分类，大家可以按分类来学习算法和数据结构。




## 项目结构


* readme.md ： 项目说明文档
* [link-new.md](link-new.md) : 大家做过的新版 Leetcode  题目列表。  
* include : 管理员维护的 Leetcode 模板 以及 使用样例。  
* problemset-new : Leetcode 题目集，大家重点关注这个目录。   
* contest : 未来互动比赛时使用，保留。  
* [category.md](category.md)：题目的分类  
* images ： 此项目的图片资源，保留。  
* other ： 其他相关算法题，保留。  
    * [lcci](other/lcci/) 程序员面试金典
    * [lcof](other/lcof/) 剑指 OFFER
* tools : 项目相关的工具集，保留。  
* .gitignore : 项目配置文件，保留。    
* [join.md](join.md) 加入项目手册  

## vscode


```
gcc -v
clang -v
brew install gcc

gcc-13 -v


macOS 的 debugger 是 lldb,，得自己安装gdb
brew install gdb
whereis gdb
WARNING: Debugger executable '/usr/local/bin/gdb' is not signed. As a result, debugging may not work properly.
ERROR: Unable to start debugging. Unexpected GDB output from command "-exec-run". Unable to find Mach task port for process-id 91593: (os/kern) failure (0x5).
 (please check gdb is codesigned - see taskgated(8))

1. 打开 Keychain Access
2. 菜单项Keychain Access --> Certificate Assistant --> Create a Certificate... ，点击Create a Certificate... 
3. 给证书选个名字，此处是 gdb_codesign，可以用其他名字; 设置 Identity Type 为 Self Signed Root ; 设置 Certificate Type 为 Code Signing ; 勾选 Let me override defaults，然后Continue
4. 接下来默认即可（中间截图省略），点击几次Continue，直到为证书指定位置（Specify a Location For The Certificate），设置 Keychain 为 System ，然后 Create，输入密码

确保 keychain 是 System keychain
security find-certificate -c gdb_codesign |grep System.keychain
确保证书没有过期
security find-certificate -p -c gdb_codesign | openssl x509 -checkend 0


```

## 代码格式化

```bash
# 格式名可选：LLVM, Google, Chromium, Mozilla, WebKit。
clang-format -style=Google -dump-config > .clang-format
```

