#########################################################################
# File Name: transpose-file-awk.sh
# Author: tiankonguse
# mail: i@tiankonguse.com
# Created Time: 2015年04月01日 星期三 00时04分46秒
#########################################################################
#!/bin/bash

awk '{for(i=0;++i<=NF;)a[i]=a[i]?a[i] FS $i:$i}END{for(i=0;i++<NF;)print a[i]}' file.txt

awk '{for(i=1;i<=NF;i++)a[NR,i]=$i}END{for(j=1;j<=NF;j++)for(k=1;k<=NR;k++)printf k==NR?a[k,j] RS:a[k,j] FS}' file.txt


 awk '{a=a$1" ";b=b$2" "}END{print a"\n"b}' file.txt


