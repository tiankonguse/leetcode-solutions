# coding: utf-8
# get https://leetcode.com/api/problems/all/

import requests
import os
import sys
import json

def get_problems():
    """Fetch problems from LeetCode API."""
    url = "https://leetcode.com/api/problems/all/"
    try:
        response = requests.get(url, timeout=3)
        return response.json()
    except Exception as e:
        print(f"Error fetching data: {e}")
        return None

def generate_markdown(output_file="link-new.md"):
    """Generate markdown file with problem links."""
    print("begin")
    
    # Get data from LeetCode
    data = get_problems()
    if not data or 'stat_status_pairs' not in data:
        print("Failed to get valid data from LeetCode")
        return
    
    # Create output file
    with open(output_file, 'w') as f:
        f.write("| ID | Title | Solutions |\n")
        f.write("| :------: | :------: | :------: |\n")
    
    
    num = 0
    for problem in data['stat_status_pairs']:
        num += 1
        if num % 100 == 0:
            print(f"run {num}")
        
        stat = problem.get('stat', {})
        frontend_question_id = stat.get('frontend_question_id')
        question_title_slug = stat.get('question__title_slug')
        question_title = stat.get('question__title')
        
        # Skip if any required field is missing
        if not all([frontend_question_id, question_title_slug, question_title]):
            continue
            
        # Convert frontend_question_id to string if it's not already
        if not isinstance(frontend_question_id, str):
            frontend_question_id = str(frontend_question_id)
            
        print(f"add [{frontend_question_id}]  <--->   [{question_title_slug}]  <--->  [{question_title}]")
        
        # Create problem directory
        problem_dir = f"../problemset-new/{int(frontend_question_id)//100:03d}/{int(frontend_question_id):05d}-{question_title_slug}/"
        if not os.path.exists(problem_dir):
            os.makedirs(problem_dir)
            print(f"create {problem_dir}")
        
        # Count solution files
        ac_num = len([f for f in os.listdir(problem_dir) if f != "readme.md"])
        
        # Append to markdown file
        with open(output_file, 'a') as f:
            f.write(f"| {frontend_question_id} | [{question_title}](https://leetcode-cn.com/problems/{question_title_slug}/) | [题解数量（{ac_num}）](/problemset-new/{int(frontend_question_id)//100:03d}/{int(frontend_question_id):05d}-{question_title_slug}/) |\n")
    
    print("end")

if __name__ == "__main__":
    output_file = "../link-new.md"
    if len(sys.argv) > 1:
        output_file = sys.argv[1]
    
    generate_markdown(output_file)