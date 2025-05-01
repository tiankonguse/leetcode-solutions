#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash


ParseLine(){
    local line="$1"
    # echo "try parse $line"
    local params=$(echo $line | sed 's/___/ /g' | sed 's/^.*"question__title": *"\([^"]*\)".*"question__title_slug": *"\([^"]*\)".*"frontend_question_id": *\([^,]*\),.*$/\3___\2___\1/')

    local frontend_question_id=$(echo $params | awk -F'___' '{ printf $1 }')
    local question__title_slug=$(echo $params | awk -F'___' '{ printf $2 }')
    local question__title=$(echo $params | awk -F'___' '{ printf $3 }')

    if [[ $frontend_question_id =~ ^[0-9]+$ ]]; then
        echo "${frontend_question_id}___${question__title_slug}___${question__title}"
    elif [[ $frontend_question_id =~ ^\"[0-9]+\"$ ]]; then
        frontend_question_id=$(echo $frontend_question_id | sed 's/"//g' )
        echo "${frontend_question_id}___${question__title_slug}___${question__title}"
    else
        echo ""
    fi
}

TestLine(){
    local name="$1"
    local line="$2"
    echo "test $name"
    local params=$(ParseLine "$line")

    if [ ${#params} -eq 0 ]; then
        echo "skip $line"
    else
        local frontend_question_id=$(echo $params | awk -F'___' '{ printf $1 }')
        local question__title_slug=$(echo $params | awk -F'___' '{ printf $2 }')
        local question__title=$(echo $params | awk -F'___' '{ printf $3 }')
        echo "add [$frontend_question_id]  <--->   [$question__title_slug]  <--->  [$question__title]"
    fi
}

# TestLine 'badCase' '{"stat":{"question_id":1000564,"question__title":"\u9b54\u6cd5\u68cb\u76d8","question__title_slug":"1ybDKD","question__hide":false,"total_acs":853,"total_submitted":2191,"total_column_articles":12,"frontend_question_id":"LCP 76","is_new_question":false},"status":null,"difficulty":{"level":3},"paid_only":false,"is_favor":false,"frequency":0,"progress":0},{'
# TestLine 'normalNum' '"stat":{"question_id":3423,"question__title":"Maximum Sum of Subsequence With Non-adjacent Elements","question__title_slug":"maximum-sum-of-subsequence-with-non-adjacent-elements","question__hide":false,"total_acs":9239,"total_submitted":21352,"total_column_articles":58,"frontend_question_id": 3165,"is_new_question":false},"status":"ac","difficulty":{"level":3},"paid_only":false,"is_favor":false,"frequency":0,"progress":0},{'
# TestLine 'stringNum' '"stat":{"question_id":3423,"question__title":"Maximum Sum of Subsequence With Non-adjacent Elements","question__title_slug":"maximum-sum-of-subsequence-with-non-adjacent-elements","question__hide":false,"total_acs":9239,"total_submitted":21352,"total_column_articles":58,"frontend_question_id": "3165","is_new_question":false},"status":"ac","difficulty":{"level":3},"paid_only":false,"is_favor":false,"frequency":0,"progress":0},{'
# exit

echo "begin" 

fineName="../link-new-mac.md"

echo  "" > $fineName

import requests

def get_problems():
    url = "https://leetcode.com/api/problems/all/"
    response = requests.get(url, timeout=3)
    return response.json()

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
    # skip :  "question__title": "Check if DFS Strings Are Palindromes", "question__title_slug": "check-if-dfs-strings-are-palindromes", "question__hide": false, "total_acs": 4288, "total_submitted": 21963, "frontend_question_id": 3327, "is_new_question": false}, "status": null, "difficulty": {"level": 3}, "paid_only": false, "is_favor": false, "frequency": 0, "progress": 0}, { 
    #params=$(echo $line | sed 's/___/ /g' | sed 's/^.*"question__title": *"\([^"]*\)".*"question__title_slug": *"\([^"]*\)".*"frontend_question_id": *\([0-9]*\).*$/\3___\2___\1/')
    
    params=$(ParseLine "$line")
    if [ ${#params} -eq 0 ]; then
        continue
    fi

    frontend_question_id=$(echo $params | awk -F'___' '{ printf $1 }')
    question__title_slug=$(echo $params | awk -F'___' '{ printf $2 }')
    question__title=$(echo $params | awk -F'___' '{ printf $3 }')
    echo "add [$frontend_question_id]  <--->   [$question__title_slug]  <--->  [$question__title]"

    problem=$(echo $params | awk -F'___' '{ printf "%03d/%05d-%s",$1/100, $1,$2 }')
    if [ ! -d ../problemset-new/$problem/ ]; then
        mkdir -p "../problemset-new/$problem/"
        echo "create $problem"
    fi
    

    acnum=$(ls -l ../problemset-new/$problem/ | grep -v "readme.md" | grep -v total |  wc -l)
    echo "${params}___${acnum}" | awk -F'___'  '{ printf "| %d | [%s](https://leetcode-cn.com/problems/%s/) | [题解数量（%d）](/problemset-new/%03d/%05d-%s/) |\n",$1,$3,$2,$4,$1/100,$1,$2 }' >> $fineName
done

echo "end"
