#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 

fineName="../other/lcof/README.md"

echo  "" > $fineName

data=$(curl -s "https://leetcode-cn.com/api/problems/lcof/" -m 3)

echo "# 剑指 OFFER" >> $fineName
echo "" >> $fineName
echo "地址：https://leetcode-cn.com/problemset/lcof/ " >> $fineName
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
    pre=$(echo $frontend_question_id | sed 's/^.* Offer \(.*\)$/\1/' | sed 's/ //g' )
    
    problem="$pre-$question__title_slug"
    mkdir -p "../other/lcof/list/$problem/"
    echo "run ${params}___${problem}"
    echo "${params}___${problem}" | awk -F'___'  '{ printf "| %s | [%s](https://leetcode.com/problems/%s/) | [题解](/other/lcof/list/%s/) |\n",$3,$1,$2,$4 }' >> $fineName
    # break
done

echo "end"
