Calf Flac
It is said that if you give an infinite number of cows an infinite number of heavy-duty laptops (with very large keys), that they will ultimately produce all the world's great palindromes. Your job will be to detect these bovine beauties.

Ignore punctuation, whitespace, numbers, and case when testing for palindromes, but keep these extra characters around so that you can print them out as the answer; just consider the letters `A-Z' and `a-z'.

Find the largest palindrome in a string no more than 20,000 characters long. The largest palindrome is guaranteed to be at most 2,000 characters long before whitespace and punctuation are removed.

PROGRAM NAME: calfflac
INPUT FORMAT
A file with no more than 20,000 characters. The file has one or more lines which, when taken together, represent one long string. No line is longer than 80 characters (not counting the newline at the end).
SAMPLE INPUT (file calfflac.in)
Confucius say: Madam, I'm Adam.
OUTPUT FORMAT
The first line of the output should be the length of the longest palindrome found. The next line or lines should be the actual text of the palindrome (without any surrounding white space or punctuation but with all other characters) printed on a line (or more than one line if newlines are included in the palindromic text). If there are multiple palindromes of longest length, output the one that appears first.

SAMPLE OUTPUT (file calfflac.out)
11
Madam, I'm Adam