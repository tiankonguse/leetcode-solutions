#########################################################################
# File Name: valid-phone-numbers.sh
# Author: tiankonguse
# mail: i@tiankonguse.com
# Created Time: 2015年04月01日 星期三 00时19分25秒
#########################################################################
#!/bin/bash
cat file.txt | grep "^([0-9]\{3\}) [0-9]\{3\}-[0-9]\{4\}$\|^[0-9]\{3\}-[0-9]\{3\}-[0-9]\{4\}$"

