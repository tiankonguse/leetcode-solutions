# Read from the file file.txt and output all valid phone numbers to stdout.

#   -E, --extended-regexp     PATTERN is an extended regular expression (ERE)
# -G 不能使用 \d 语法糖，可以使用正则字符
cat file.txt  | grep -E  "^(([0-9]{3}-)|(\([0-9]{3}\) ))[0-9]{3}-[0-9]{4}$"

#   -G, --basic-regexp        PATTERN is a basic regular expression (BRE)
# -G 需要给正则字符加斜杠，不能使用 \d 语法糖
cat file.txt  | grep -G "^\(\(([0-9]\{3\}) \)\|\([0-9]\{3\}-\)\)[0-9]\{3\}-[0-9]\{4\}$"

#   -P, --perl-regexp         PATTERN is a Perl regular expression
cat file.txt  | grep -P "^((\d{3}-)|(\(\d{3}\) ))\d{3}-\d{4}$"

