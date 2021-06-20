#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 

fineName="../other/lcci/README.md"

echo  "" > $fineName

data=$(curl -s "https://leetcode-cn.com/api/problems/lcci/" -m 3)

echo "#  程序员面试金典（第 6 版）" >> $fineName
echo "" >> $fineName
echo "地址：https://leetcode-cn.com/problemset/lcci/ " >> $fineName
echo "" >> $fineName

echo "# 目录 " >> $fineName
echo "" >> $fineName
echo "| ID | Title | Solutions |" >> $fineName
echo "| :------: | :------: | :------: |" >> $fineName


# linux: sed 's/"stat"/\n/g'
# mac: sed -e 's/\"stat\"/\'$'\n/g'adv

for line in $(echo $data | sed 's/ /___/g' | sed -e 's/\"stat\"/\'$'\n/g' | grep -E "question__title_slug"); do
#    echo $line
    echo "---"
    params=$(echo $line | sed 's/___/ /g' | sed 's/^.*"question__title":\s*"\([^"]*\)".*"question__title_slug":\s*"\([^"]*\)".*"frontend_question_id":\s*"\([^"]*\)".*$/\1___\2___\3/')
    question__title=$(echo $params | awk -F'___' '{ printf "%s",$1 }')
    question__title_slug=$(echo $params | awk -F'___' '{ printf "%s",$2 }')
    frontend_question_id=$(echo $params | awk -F'___' '{ printf "%s",$3 }')
    pre=$(echo $frontend_question_id | sed 's/^.* \([0-9]*\)\.\([0-9]*\).*$/\1-\2/')
    
    problem="$pre-$question__title_slug"
    mkdir -p "../other/lcci/list/$problem/"
    echo "run ${params}___${problem}"
    echo "${params}___${problem}___${pre}" | awk -F'___'  '{ printf "| 程序员面试金典 %s | [%s](https://leetcode-cn.com/problems/%s/) | [题解](/other/lcci/list/%s/) |\n",$5,$1,$2,$4 }' >> $fineName
    # break
done

echo "end"
