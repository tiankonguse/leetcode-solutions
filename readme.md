## 文档目录


[TOC]


1. [项目结构](#一项目结构)  
2. [加入互动编程基本步骤](#二加入互动编程基本步骤)
3. [如何用自己的分支代码 Pull Request 互动](#三如何用自己的分支代码-pull-request-互动)
4. [如何保持自己 Fork 的仓库与 原仓库同步](#四如何保持自己-fork-的仓库与-原仓库同步)
5. [分支操作说明](#五分支操作说明)


# 一、项目结构

* readme.md ： 项目说明文档
* [link.md](link.md) : 大家做过的 Leetcode  题目列表。  
* include : 管理员维护的 Leetcode 模板 以及 使用样例。  
* problemset : Leetcode 题目集，大家重点关注这个目录。   
* contest : 未来互动比赛时使用，保留。  
* images ： 此项目的图片资源，保留。  
* jisuanke ： 计蒜客相关算法题，保留。  
* other ： 其他相关算法题，保留。  
* .gitignore : 项目配置文件，保留。    
* run.sh : 自动生成 link.md 脚本，保留。  




# 二、加入互动编程基本步骤


1. 注册 github.com 账号。  
2. 使用浏览器打开 https://github.com/tiankonguse/leetcode-solutions  
3. 在页面右上角找到 fork 按钮，将该仓库 Fork 到你自己的账户中, 并创建自己的分支，格式: `from-{昵称}`。  
4. 把代码拉取到本地(你也可以到时候上传文件，或者页面上创建文件)。  
   命令行：`git clone https://github.com/tiankonguse/leetcode-solutions.git`  
   IDE工具：使用 [Desktop for Github](https://desktop.github.com/) 将 [leetcode-solutions](https://github.com/tiankonguse/leetcode-solutions.git) 这个你 Fork 过来的仓库克隆到本地。  
5. 找到 tiankonguse-code 这个公众号，看最新一篇算法相关的文章，里面会提供几道题，尽量独立去做出来，一道题超过半小时没做出来，可以尝试看题解。如果都做完了，可以向前继续找其他文章。  
6. 做的题按照 `/problemset/题目/leetcode昵称-题目.代码语言后缀` 的格式放入到你自己的分支里。  
7. 将你的分支代码提交到自己的 github 仓库里。  
8. 将你的分支代码进行 Pull Request，来互动并记录你曾做过这道题。  



## 三、如何用自己的分支代码 Pull Request 互动  


建议进行 pull request 之前，先参考下一小节《如何保持自己 Fork 的仓库与原仓库同步》来将代码保持同步。  


这里假设你已经在你的仓库里按照规范提交了你的代码。  


1. 创建新分支（如果存在先删除），命名为 from-<昵称>, 然后点击 Create Branch 建立新分支。  

注2：这个文档说明是比较简单粗暴，如果你自己已经会 github 相关操作，就不需要删除分支。  


![](/images/pull-request-create-branch.png)  


2. 切换到新分支，点击 pull request 。  


![](/images/pull-request-click-pull-button.png)  


3. 输入一个简洁的标题，内容罗列自己做的题目列表，并点击 Create pull request。  

注意输入标题之上的两行文字，第一行是 tiankonguse/leetcode-solutions ，base  是 master, 第二行是自己的仓库，compare 是 自己创建的分支。    


![](/images/pull-request-create-again.png)  


4. 随后，Github 用户 @tiankonguse 即 leetcode-solutions 仓库的管理员，会收到一个 pull request 请求通知。  
如果管理员确认这个 Pull request 没问题，就会点击 Merge pull request 来通过这次合并。  


注意实现：


> 提交 Pull request 之前，必须先将你的 Fork 的 master 与原仓库同步  
> Pull request 之前，请创建一个新的分支  
> 提交时标题尽量简短且清楚地说明你在做什么，并在内容里罗列这一次做的题目列表  
> 耐心等待回复。  


## 四、如何保持自己 Fork 的仓库与 原仓库同步  


1. 在你 Fork 页面中如下图所示，点击 Compare 链接：  


点击 Compare 之前，请确保当前分支是 master。  


![](/images/sync_fork_compare.png)  


2. 将左边的 base repository 更改成当前自己的 Fork，在图示中即为 {你的昵称}/leetcode-solutions  


如果上一步骤忘记切换为 master 分支，这一步骤还来得及补救，在左边的 base 里面选择 master。  


![](/images/sync_fork_choose_base_repository.png)  


3. 这时候，页面会显示 Comparing changes， 点击 compare across forks 链接。  


![](/images/sync-fork-compare-across-forks.png)  


4. 将右边的 head repository 更改成 tiankonguse/leetcode-solutions ，在图示中即为  


![](/images/sync-fork-choose-head-repository.png)  


5. 此时你会看到比较结果。 然后点击 Create pull request（含义为将最新的 leetcode-solutions 合并到自己的项目中）  


![](/images/sync-fork-create-pull-request.png)  


6. 你在 Pull requests 标签页里会看到你刚刚提交的 Pull request，点击 Merge pull request 按钮。  


![](/images/sync-fork-merge-pull-request.png)  


7. 同意并合并之后，你的 Fork 与 远程最新的 leetcode-solutions 保持一致了。    


![](/images/sync-fork-finish.png)



当然，有时会出现一些你无法解决的问题，那么，还有一个最后的方法：


将你的 Fork 删除，而后重新到 https://github.com/tiankonguse/leetcode-solutions 页面拉取最新的代码。  



## 五、分支操作说明  


主要流程如下图，下面使用文字来解释一下。  


![](/images/git-branch-manger.jpg)  


1. 所有人都需要创建自己的分支，格式是`form-{昵称}`。  
2. 对于你的 `master`分支，只能从 原项目 `tiankonguse/leetcode-solutions` 同步过来，不能自己提交。  
3. 自己的代码，只能在自己的分支`form-{昵称}`里按照规则添加对应的代码文件，可以随时提交到自己的远程仓库里。  
4. 想要将自己的代码`pull request`到原项目时，需要先将自己的`master`和原项目的`master`对齐（同步1），然后将自己的`master`和自己的分支合并（同步2），最后再`pull request`到原项目（同步3）。  
5. 上一步骤有三个操作，做的操作都是`pull request`，本质是`merge`操作，只是`from`和`to`的不同，都可以通过同步教程来完成。  






