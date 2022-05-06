#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 

fineName="../other/lcof-ii/README.md"

echo  "# 剑指 OFFER II" > $fineName


echo  "" >> $fineName
echo  "本书精选国内外名企高频面试题并深度拓展，系统地总结了程序员面试中必备的数据结构与算法知识，并以面试者及面试官的双向视角剖析考点与解题思路，适合所有正在准备面试的程序员阅读。" >> $fineName
echo  "" >> $fineName
echo  "地址：[https://leetcode-cn.com/problemset/e8X3pBZi/ ](https://leetcode-cn.com/problem-list/e8X3pBZi/)" >> $fineName
echo  "" >> $fineName


data=$(curl -s "https://leetcode-cn.com/api/problems/all/" -m 3)

echo "| ID | Title | Solutions |" >> $fineName
echo "| :------: | :------: | :------: |" >> $fineName


# linux: sed 's/"stat"/\n/g'
# mac: sed -e 's/\"stat\"/\'$'\n/g'adv

for line in $(echo $data | sed 's/ /___/g' | sed -e 's/\"stat\"/\'$'\n/g' | grep -E "question__title_slug" | grep "___Offer___II___"); do
#    echo $line
    echo "---"
    # {"question_id":1000228,"question__title":"\u6574\u6570\u9664\u6cd5","question__title_slug":"xoh6Oh","question__hide":false,"total_acs":33692,"total_submitted":160482,"total_column_articles":304,"frontend_question_id":"\u5251\u6307 Offer II 001"

    params=$(echo $line | sed 's/___/ /g' | sed 's/^.*"question__title":\s*"\([^"]*\)".*"question__title_slug":\s*"\([^"]*\)".*"frontend_question_id":\s*"\([^"]*\)".*$/\1___\2___\3/')
    question__title=$(echo $params | awk -F'___' '{ printf "%s",$1 }')
    frontend_question_id=$(echo $params | awk -F'___' '{ printf "%s",$4 }')
    question__title_slug=$(echo $params | awk -F'___' '{ printf "%s",$2 }')
    pre=$(echo $frontend_question_id | sed 's/^.* Offer \(.*\)$/\1/' | sed 's/ //g' )
    
    problem="$pre-$question__title_slug"
    mkdir -p "../other/lcof-ii/list/$problem/"

    
    num=$(ls -l ../other/lcof-ii/list/$problem/ | grep -v "readme.md" | grep -v total |  wc -l)

    echo "run ${params}___${problem}"
    echo "${params}___${problem}___${pre}___${num}" | awk -F'___'  '{ printf "| 剑指 OFFER II %s | [题目](https://leetcode-cn.com/problems/%s/) | [题解数量（%d）](/other/lcof-ii/list/%s/) |\n",$5,$2,$6,$4 }' >> $fineName
    # break
done


echo "end"
