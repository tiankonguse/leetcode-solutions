#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 

fineName="../link-new.md"

echo  "" > $fineName

data=$(curl -s "https://leetcode.com/api/problems/all/" -m 3)

echo "| ID | Title | Solutions |" >> $fineName
echo "| :------: | :------: | :------: |" >> $fineName


# linux: sed 's/"stat"/\n/g'
# mac: sed -e 's/\"stat\"/\'$'\n/g'adv

num=0
for line in $(echo $data | sed 's/ /___/g' | sed -e 's/\"stat\"/\'$'\n/g' | grep -E "question__title_slug"); do
#    echo $line
    # echo "---"
    num=$((num+1))
    num1=$num
    num1=$((num1%100))
    if [[ $num1 == 0 ]]; then
        echo "run $num"
    fi
    params=$(echo $line | sed 's/___/ /g' | sed 's/^.*"question__title": "\([^"]*\)".*"question__title_slug": "\([^"]*\)".*"frontend_question_id": \([0-9]*\).*$/\3___\2___\1/')
    problem=$(echo $params | awk -F'___' '{ printf "%03d/%05d-%s",$1/100, $1,$2 }')
    if [ -d ../problemset-new/$problem/ ]; then
        continue
    fi
    
    mkdir -p "../problemset-new/$problem/"
    echo "run $problem"

    num=$(ls -l ../problemset-new/$problem/ | grep -v "readme.md" | grep -v total |  wc -l)

    echo "${params}}___${num}" | awk -F'___'  '{ printf "| %d | [%s](https://leetcode-cn.com/problems/%s/) | [题解数量（%d）](/problemset-new/%03d/%05d-%s/) |\n",$1,$3,$2,$4,$1/100,$1,$2 }' >> $fineName
done

echo "end"
