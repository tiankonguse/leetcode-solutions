#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 
echo  "" > ../link.md;

num=0
for i in ../problemset/* ; do
    #i=`echo $i | sed 's/^.*\/\([^/]\+\)$/\1/'`;
    name=`echo $i | sed 's/..\/problemset\///'`;
    newpath=`find ../problemset-new -iname "*[0-9]-$name"`
    if [ "X"$newpath == "X" ];
    then
        echo "$name no find"
        continue
    fi
    for j in $i/*; do
        if [ $j == "$i/*" ]; then 
            continue;
        fi 
        # echo "move $i $j"
        mv $j $newpath/
    done
    rmdir $i
    num=$(($num+1))
    echo "num = $num"
    # echo "* $i [problem](./problemset/$i) [test](https://leetcode.com/problems/$i/) " >> ../link.md;  
done
echo "end"


# find . -iname "*-4sum" 