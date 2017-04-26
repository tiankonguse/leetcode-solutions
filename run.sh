#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 
echo  "" > link.md;

for i in ./problemset/* ; do
    i=`echo $i | sed 's/^.*\/\([^/]\+\)$/\1/'`;
    echo "run $i"
    echo "* $i [problem](./problemset/$i/readme.md) [test](https://leetcode.com/problems/$i/) " >> link.md;  
done
echo "end"
