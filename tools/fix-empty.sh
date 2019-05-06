#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 

for i in ../problemset-new/* ; do
    if [ ! -f $i/readme.md  ];then
        echo "这道题还没有人做，你可以来抢占一血" >> $i/readme.md
        echo "not exit $i"
    else
        echo "exit $i"
    fi
done
echo "end"
