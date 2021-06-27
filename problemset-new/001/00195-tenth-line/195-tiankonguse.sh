# Read from the file words.txt and output the word frequency list to stdout.


# head -n K 输出 TOP K 行
# head -n -K 除了最后 K 行，输出其他所有行
# tail -n K 输出最后 10 行
# tail -n +K 从第 K 行开始输出之后所有的行
cat file.txt| head -n 10 | tail -n +10



# sed 
sed -n "10p" file.txt


# grep -n 搜索时输出行数
# grep -E 正则搜索
# sed 正则替换
grep -n '' file.txt  | grep -E "^10:" | sed 's/^10:\(.*\)$/\1/'

# NR， Number of Record, 默认一行一条记录，读取的次数
awk '{ if(NR == 10) { print $0;} }' file.txt
awk 'NR == 10' file.txt

row_num=$(cat file.txt | wc -l)
if [ $row_num -ge 10 ];then
    cat file.txt| head -n 10 | tail -n 1
fi
