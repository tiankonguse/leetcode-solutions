## 文档目录


1. [项目结构](#一项目结构)  
2. [加入互动编程基本步骤](#二加入互动编程基本步骤)
3. [如何用自己的分支代码 Pull Request 互动](#三如何用自己的分支代码-pull-request-互动)
4. [如何保持自己 Fork 的仓库与 原仓库同步](#四如何保持自己-fork-的仓库与-原仓库同步)
5. [分支操作说明](#五分支操作说明)


# 零、几个原则  


1. 题的格式分两种，一种是素有题目放在[problemset](./problemset)目录下，一种是按5位的题号，每100个一组放在[problemset-new](./problemset-new)下。 例如 123 题，5位就是 00123，放在 001 目录下。  
2. 每个目录或文件后面会有一段话，那是最后一题提交时的描述，大家可以忽略那个。  
3. [link.md](link.md) 和 [link-new.md](link-new.md) 两个索引目前是自动生成，大家有什么好的建议可以提交 issue。  
4. 请不要删除不是自己的文件！


# 一、项目结构


* readme.md ： 项目说明文档
* [link.md](link.md) : 旧版Leetcode  题目列表。  
* [link-new.md](link-new.md) : 大家做过的新版 Leetcode  题目列表。  
* include : 管理员维护的 Leetcode 模板 以及 使用样例。  
* problemset : Leetcode 题目集，大家重点关注这个目录。   
* problemset-new : Leetcode 题目集，大家重点关注这个目录。   
* contest : 未来互动比赛时使用，保留。  
* images ： 此项目的图片资源，保留。  
* jisuanke ： 计蒜客相关算法题，保留。  
* other ： 其他相关算法题，保留。  
* tools : 项目相关的工具集，保留。  
* .gitignore : 项目配置文件，保留。    




# 二、加入互动编程基本步骤


1. 注册 github.com 账号。  
2. 使用浏览器打开 https://github.com/tiankonguse/leetcode-solutions  
3. 在页面右上角找到 fork 按钮，将该仓库 Fork 到你自己的账户中, 并创建自己的分支，格式: `base-{昵称}`。  
4. 把代码拉取到本地(你也可以到时候上传文件，或者页面上创建文件)。  
   命令行：`git clone https://github.com/tiankonguse/leetcode-solutions.git`  
   IDE工具：使用 [Desktop for Github](https://desktop.github.com/) 将 [leetcode-solutions](https://github.com/tiankonguse/leetcode-solutions.git) 这个你 Fork 过来的仓库克隆到本地。  
5. 找到 tiankonguse-code 这个公众号，看最新一篇算法相关的文章，里面会提供几道题，尽量独立去做出来，一道题超过半小时没做出来，可以尝试看题解。如果都做完了，可以向前继续找其他文章。  
6. 做的题按照 `/problemset-new/题号-题目/leetcode昵称.代码语言后缀` 的格式放入到你自己的 base 分支里。  
7. 同步这个项目最新代码到 master，并合并到你的 base 分支。  
8. 基于 master 分支创建 from 分支，然后将 base 分支合并到 from 分支。  
9. 将你的 master 分支、base 分支、from 分支提交到自己的 github 仓库里。  
10. 将你的 from 分支代码进行 Pull Request，来互动并记录你曾做过这道题。  



## 三、如何用自己的分支代码 Pull Request 互动  


建议进行 pull request 之前，先参考文章《[如何保持自己 Fork 的仓库与原仓库同步](https://mp.weixin.qq.com/s/cPHUqFz78hDIVH4kqHZJPw)》来将代码保持同步。  


这里假设你已经在你的仓库里按照规范提交了你的代码。  



1. 切换到 from 分支，点击 pull request 。  


![](/images/pull-request-click-pull-button.png)  


2. 输入一个简洁的标题，内容罗列自己做的题目列表，并点击 Create pull request。  

注意输入标题之上的两行文字，第一行是 tiankonguse/leetcode-solutions ，base  是 master, 第二行是自己的仓库，compare 是 自己创建的分支。    


![](/images/pull-request-create-again.png)  


3. 随后，Github 用户 @tiankonguse 即 leetcode-solutions 仓库的管理员，会收到一个 pull request 请求通知。  
如果管理员确认这个 Pull request 没问题，就会点击 Merge pull request 来通过这次合并。  


注意实现：


> 提交 Pull request 之前，必须先将你的 Fork 的 master 与原仓库同步  
> Pull request 之前，请基于 master 分支创建一个新的 from 分支  
> 提交时标题尽量简短且清楚地说明你在做什么，并在内容里罗列这一次做的题目列表  
> 耐心等待回复。  


## 四、分支操作说明  


主要流程如下图，下面使用文字来解释一下。  


![](/images/git-branch-manger2.jpg)  


1. 所有人都需要创建自己的开发分支，格式是`base-{昵称}`。  
2. 对于你的 `master`分支，只能从 原项目 `tiankonguse/leetcode-solutions` 同步过来，不能自己提交。  
3. 自己的代码，只能在自己的分支`base-{昵称}`里按照规则添加对应的代码文件，可以随时提交到自己的远程仓库里。  
4. 想要将自己的代码`pull request`到原项目时，需要先将自己的`master`和原项目对齐（A节点的ff合并），然后将自己的`master`和自己的分支合并（A+B->C），最后创建 from 分支再`pull request`到原项目（D -> E）。  
5. 上一步骤有三个操作，所有操作都是`pull request`，本质是`merge`操作，只是`from`和`to`的不同，都可以通过同步教程来完成。  



