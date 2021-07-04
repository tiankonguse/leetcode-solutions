# Read from the file file.txt and print its transposed content to stdout.

colNum=$(head -1 file.txt | wc -w)

# wc 直接获取单词个数，即列数
colNum=$(cat file.txt | head -n 1 | wc -w)

# 先使用 sed 分隔为行，在使用 wc 统计行数
colNum=$(cat file.txt | head -n 1 | sed 's/ /\n/g' | wc -l)

for (( i = 1; i <= $colNum; i++ )); do
    awk -v col=$i '{print $col}' file.txt | xargs
    cut -d' ' -f$i file.txt | xargs
    cut -d' ' -f$i file.txt | tr '\n' ' '
    cut -d' ' -f$i file.txt | tr '\n' ' ' | sed 's/ $/\n/'
    str=$(awk -v col=$i '{print $col}' file.txt)
    echo $str
done


for i in `seq 1 $column`; do
    awk -v col=$i '{print $col}' file.txt | xargs
done

