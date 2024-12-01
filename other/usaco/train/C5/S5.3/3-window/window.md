Window Area
IV Balkan Olympiad
You've just be assigned the project of implemented a windowing interface. This windowing interface is fairly simple, and fortunately, you don't have to display the actual windows. There are 5 basic operations:

Create a window
Bring a window to the top
Put a window to the bottom
Destroy a window
Output what percentage of a window is visible (i.e., isn't covered by windows above it).
In the input, the operations appear in the following format:

Create window: w(I,x,y,X,Y)
Bring window to top: t(I)
Put window on bottom: b(I)
Destroy window: d(I)
Output percentage visible: s(I)
The I is a unique identifier for each window, which is one character. The character can be any of 'a'..'z', 'A'..'Z', and '0'..'9'. No extra spaces will appear in the input.
(x,y) and (X,Y) are opposite corners of the window. When a window is created, it is put `on top'. You can't create a window with an identifier that is already in use, but you can destroy a window and then create a new one with the identifier of the destroyed window.
Coordinates will be positive integers, and all windows will be of non-zero area (x != X and y != Y). The x and y coordinates are between 1 and 32767 inclusive.

PROGRAM NAME: window
INPUT FORMAT
The input file consists of a sequence of commands to your interpreter. They will be listed one per line. Terminate the program when no more input is available

SAMPLE INPUT (file window.in)
w(a,10,132,20,12)
w(b,8,76,124,15)
s(a)
OUTPUT FORMAT
Output lines only for the s() commands. Of course, there might be several s() commands (but no more than 500) so the output should be a sequence of percentages, one per line, stating the percentage of the windows that are visible.
The percentages should be rounded to 3 decimal places.

SAMPLE OUTPUT (file window.out)
49.167