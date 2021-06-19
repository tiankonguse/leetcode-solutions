#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 

for i in $(grep -r suanfa_xiaomiquan.jpg  ../problemset | grep suanfa_xiaomiquan.jpg | awk -F':' '{print $1}'); do
    echo $i
    cat $i | tr '\n' '\r' |   sed  's/## hello.*//' | tr '\r' '\n' > $i.tmp
    cat $i.tmp > $i
    rm $i.tmp
done
echo "end"
