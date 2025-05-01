"""
背景介绍：
1)  参加的周赛都记录在../contest/中比赛ID是递增数字
2) 第一级目录名是百位数字, 第二级目录名是比赛ID
3) 比赛有四道题, 命名为A,B,C,D前缀

需求:
编写一个 python 脚本，在 ../ 目录下生成 contest.md 文件，内容是表格。  
表格共 10 列，分别为比赛ID的个位从 0 到 9的连续10场比赛
比赛目录存在，代表参加了这次比赛，内容显示比赛ID，超链接为比赛目录地址，例如 [83](./contest/0/083/)。
如果某次比赛没有参加，内容为空。  
如果如果一行的10场比赛都没参加，则该行不显示。
"""

import os

def generate_contest_table():
    # 获取所有比赛目录
    contest_dir = "../contest"
    if not os.path.exists(contest_dir):
        print(f"比赛目录 {contest_dir} 不存在")
        return
    
    # 收集所有比赛ID
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
    
    # 按比赛ID排序
    contest_ids.sort()
    
    # 生成表格数据
    min_id = min(contest_ids) if contest_ids else 0
    max_id = max(contest_ids) if contest_ids else 0
    
    # 写入markdown文件
    with open("../contest.md", "w") as f:
        # 写表头
        f.write("| " + " | ".join(str(i) for i in range(10)) + " |\n")
        f.write("|" + " :---: |" * 10 + "\n")
        
        # 按每10场比赛为一行生成表格
        for start_id in range(min_id, max_id + 1, 10):
            row_data = []
            row_empty = True
            for col in range(10):
                contest_id = start_id + col
                hundred = contest_id // 100
                contest_path = f"../contest/{hundred}/{contest_id:03d}"
                if os.path.exists(contest_path):
                    link = f"[{contest_id}](./contest/{hundred}/{contest_id:03d}/)"
                    row_data.append(link)
                    row_empty = False
                else:
                    row_data.append("")
            
            # 如果整行都为空则跳过
            if row_empty:
                continue
                
            f.write("| " + " | ".join(row_data) + " |\n")

if __name__ == "__main__":
    generate_contest_table()
