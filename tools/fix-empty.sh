#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash

echo "begin" 

function Fix(){
    d=$1
    for i in $d/* ; do
        if [ ! -d "$i" ]; then
            echo "$i is file"
            continue
        fi
        echo "$i is folder"
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

}

Fix "../problemset-new/"
Fix "../other/lcof"
Fix "../other/lcci"



echo "end"
