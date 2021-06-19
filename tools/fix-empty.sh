#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 

for i in ../problemset-new/* ; do
    if [ ! -d "$i" ]; then
        continue
    fi
    for j in $i/* ; do
        if [ ! -d "$j" ]; then
            # rm $j  # remove readme
            continue
        fi
        if [ ! -f $j/readme.md  ];then
            echo "这道题还没有人做，你可以来抢占一血" >> $j/readme.md
            echo "not exit $j/readme.md"
            # echo
        else
            echo "exit $j/readme.md"
        fi
    done
done
echo "end"
