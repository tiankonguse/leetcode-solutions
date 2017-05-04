#########################################################################
# File Name: run.sh
# Author: tiankonguse(skyyuan)
# mail: i@tiankonguse.com
# Created Time: 2016年06月04日 星期六 17时02分20秒
#########################################################################
#!/bin/bash



for f in `find ./problemset/ -name readme.md` ; do
    res=`cat $f | grep suanfa_xiaomiquan.jpg`
	if [ $res"X" == "X" ];
	then
		echo $f;
		cat xiaomiquan.md >> $f
	fi
done
echo "end"
 
