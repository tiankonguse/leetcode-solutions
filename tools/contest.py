"""
背景介绍：
1) 周赛都记录在 ../contest/ 中比赛ID是递增数字
2) 第一级目录名是百位数字, 第二级目录名是比赛ID
3) 比赛有四道题, 命名为A,B,C,D前缀
4) 有些周赛是比赛期间做的，有些是比赛之后做的。比赛期间做的成绩记录在 remote-contest.json 中，这个文件的比赛分为周赛和双周赛，周赛标题是 ”第 xxx 场周赛“，双周赛标题是 ”第 xxx 场双周赛“，这里只需要提取双周赛信息。  
5）json 的 data.userContestRankingHistory 是比赛列表(每次比赛信息是 item)， item.contest.title 为 ”第 xxx 场周赛“， xxx 为比赛ID，item.attended 代表是否参赛，这里需要提取出参数的所有周赛。  

需求:
编写一个 python 脚本，在 ../ 目录下生成 contest.md 文件，内容是表格。  
表格共 10 列，分别为比赛ID的个位从 0 到 9的连续10场比赛
比赛目录存在，代表做了了这次比赛，内容显示比赛ID，超链接为比赛目录地址，例如 [83](./contest/0/083/)。
如果 remote-contest.json 里面参赛某场周赛，内容前面显示一个 对号，例如 ✅[83](./contest/0/083/) 。
如果某次比赛没有参加，内容为空。  
如果如果一行的10场比赛都没参加，则该行不显示。


"""

# 在文件顶部添加json导入
import os
import json

# 添加load_attended_contests函数
def load_attended_contests():
    json_path = "./remote-contest.json"
    if not os.path.exists(json_path):
        print(f"文件 {json_path} 不存在")
        return set()
    
    with open(json_path, 'r', encoding='utf-8') as f:
        remoteContest = json.load(f)
    
    attended_contests = set()
    if "data" not in remoteContest:
        print("remote-contest.json 文件没有 data 字段")
        return set()
    
    
    data = remoteContest.get('data', {})
    for item in data.get('userContestRankingHistory', []):
        title = item.get('contest', {}).get('title', '')
        if '场周赛' in title and item.get('attended', False):
            contest_id = int(title.replace('第', '').replace('场周赛', ''))
            attended_contests.add(contest_id)
    
    
    print("加载参赛信息完成, 共", len(attended_contests), "场比赛")
    return attended_contests

def generate_contest_table():
    # 获取所有比赛目录
    contest_dir = "../contest"
    if not os.path.exists(contest_dir):
        print(f"比赛目录 {contest_dir} 不存在")
        return
    
    # 加载参赛信息
    attended_contests = load_attended_contests()
    print("加载参赛信息完成, 共", len(attended_contests), "场比赛")
    # print(" 最后一个比赛是", max(attended_contests), " 比赛ID")
    
    print("开始收集比赛ID")
    contest_ids = []
    for hundred in os.listdir(contest_dir):
        hundred_path = os.path.join(contest_dir, hundred)
        if not os.path.isdir(hundred_path) or not hundred.isdigit():
            continue
        for contest_id in os.listdir(hundred_path):
            contest_path = os.path.join(hundred_path, contest_id)
            if os.path.isdir(contest_path) and contest_id.isdigit():
                contest_ids.append(int(contest_id))
    
    if not contest_ids:
        print("未找到任何比赛记录")
        return
    
    print("开始排序比赛ID")
    contest_ids.sort()
    
    print("开始生成表格数据")
    min_id = min(contest_ids) if contest_ids else 0
    max_id = max(contest_ids) if contest_ids else 0
    
    print("开始写入markdown文件")
    with open("../contest.md", "w") as f:
        print("写入表头")
        f.write("| " + " | ".join(str(i) for i in range(10)) + " |\n")
        f.write("|" + " :---: |" * 10 + "\n")
        
        print("生成表格内容")
        for start_id in range(min_id, max_id + 1, 10):
            row_data = []
            row_empty = True
            for col in range(10):
                contest_id = start_id + col
                hundred = contest_id // 100
                contest_path = f"../contest/{hundred}/{contest_id:03d}"
                # 修改链接生成部分
                if os.path.exists(contest_path):
                    prefix = "✅" if contest_id in attended_contests else ""
                    link = f"{prefix}[{contest_id}](./contest/{hundred}/{contest_id:03d}/)"
                    row_data.append(link)
                    row_empty = False
                else:
                    row_data.append("")
                
            if row_empty:
                continue
                
            f.write("| " + " | ".join(row_data) + " |\n")
    
    print("表格生成完成")

if __name__ == "__main__":
    generate_contest_table()
