# 加入互动编程基本步骤


1. 注册 [github.com](https://github.com/) 账号。  
2. 使用浏览器打开 https://github.com/tiankonguse/leetcode-solutions[](https://github.com/tiankonguse/leetcode-solutions)。  
3. 在页面右上角找到“fork”按钮，将该仓库 Fork 到你自己的账户中。  
4. 把代码拉取到本地。  
   命令行：`git clone https://github.com/tiankonguse/leetcode-solutions.git`  
   IDE工具：使用 [Desktop for Github](https://desktop.github.com/) 将 [leetcode-solutions](https://github.com/tiankonguse/leetcode-solutions.git) 这个你 Fork 过来的仓库克隆到本地。  
5. 找到 tiankonguse-code 这个公众号，看最新一篇算法相关的文章，里面会提供几道题，尽量独立去做出来，一道题超过半小时没做出来，可以尝试看题解。如果都做完了，可以向前继续找其他文章。  
6. 自己做的题按照 `/problemset/题目/leetcode昵称-题目.代码语言后缀` 的格式放入到你 Fork 的项目里。  
  具体参考 [计划发起一个练习算法项目](https://mp.weixin.qq.com/s/ThqNvzMQAmOI69j7t4mG8Q) 这篇文章的截图。  
7. 将这些代码提交到自己的 github 仓库里。  
8. 将你的代码进行 Pull Request，来记录你曾做过这道题。  


## 如何使用 Pull Request 进行互动  

1. 创建新分支（如果存在则不需要创建），命名为 from-<昵称>, 然后点击 Create Branch 建立新分支。  


![](/images/pull-request-create-branch.png)  


2. 在 pull request 页卡点击 create  pull request。  


![](/images/pull-request-click-pull-button.png)  


3. compare 选项，选择自己的分支，并点击创建按钮。  


![](/images/pull-request-create-again.png)  


4. 随后，Github 用户 @tiankonguse 即 leetcode-solutions 仓库的管理员，会收到一个 pull request 请求通知。  
如果我确认这个 Pull request 没问题，就会点击 Merge pull request 来通过这次合并。  


注意实现：


> 提交 Pull request 之前，必须先将你的 Fork 的 master 与原仓库同步到最新  
> 从 master 创建 新的 branch 进行增补、修改等操作  
> 提交时尽量简短且清楚地说明修改原因  
> 耐心等待回复。  


## 如何保持自己 Fork 的仓库与 原仓库同步  


1. 在你的 Fork 页面中如下图所示，点击 Compare 链接：  


![](/images/sync_fork_compare.png)  


2. 将 base repository 更改成当前自己的 Fork，在图示中即为 tiankongever/leetcode-solutions  


![](/images/sync_fork_choose_base_repository.png)  


3. 这时候，页面会显示 There isn't anything to compare.  
  因为你在比较 “自己” 和 “自己”。点击 compare across forks 链接：  


![](/images/sync-fork-compare-across-forks.png)  


4. 将 head repository 更改成 Upstream Repository（即，上游仓库），在图示中即为 ：  


![](/images/sync-fork-choose-head-repository.png)  


5. 稍等片刻，你会看到比较结果；而后你可以创建一个 Pull request —— 这是一个由你自己向你自己的 Fork 仓库提交的 Pull request：  


![](/images/sync-fork-create-pull-request.png)  


6. 你在 Pull requests 标签页里会看到你刚刚提交的 Pull request：  
点击 Merge pull request 按钮


![](/images/sync-fork-merge-pull-request.png)  


7. 同意并合并之后的结果是，你的 Fork 与上游仓库同步完成了：  


![](/images/sync-fork-finish.png)



当然，有时会出现一些你无法解决的问题，那么，还有一个最后的方法：

将你的 Fork 删除，而后重新到 https://github.com/tiankonguse/leetcode-solutions 页面按一次 Fork 按钮……








