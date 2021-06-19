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

for line in $(echo $data | sed 's/ /___/g' | sed -e 's/\"stat\"/\'$'\n/g' | grep -E "question__title_slug"); do
#    echo $line
    echo "---"
    params=$(echo $line | sed 's/___/ /g' | sed 's/^.*"question__title": "\([^"]*\)".*"question__title_slug": "\([^"]*\)".*"frontend_question_id": \([0-9]*\).*$/\3___\2___\1/')
    problem=$(echo $params | awk -F'___' '{ printf "%03d/%05d-%s",$1/100, $1,$2 }')
    mkdir -p "../problemset-new/$problem/"
    echo "run $problem"
    echo $params | awk -F'___'  '{ printf "| %d | [%s](https://leetcode.com/problems/%s/) | [%05d-%s](/problemset-new/%03d/%05d-%s/) |\n",$1,$3,$2,$1,$2,$1/100,$1,$2 }' >> $fineName
done

echo "end"
