#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 
echo  "" > ../link-new.md

data=$(curl -s "https://leetcode.com/api/problems/all/" -m 3)

echo "| ID | Title | Solutions |" >> ../link-new.md
echo "| :------: | :------: | :------: |" >> ../link-new.md

for line in $(echo $data | sed 's/ /___/g' | sed 's/"stat"/\n/g' | grep -E "question__title_slug"); do
    params=$(echo $line | sed 's/___/ /g' | sed 's/^.*"question__title":\s*"\([^"]\+\)".*"question__title_slug":\s*"\([^"]\+\)".*"frontend_question_id":\s*\([0-9]\+\).*$/\3___\2___\1/')
    problem=$(echo $params | awk -F'___' '{ printf "%05d-%s",$1,$2 }')
    mkdir -p "../problemset-new/$problem/"
    echo "run $problem"
    echo $params | awk -F'___'  '{ printf "| %d | [%s](https://leetcode.com/problems/%s/) | [%05d-%s](/problemset-new/%03d/%05d-%s/) |\n",$1,$3,$2,$1,$2,$1,$1,$2 }' >> ../link-new.md
done

echo "end"
