# Transformations

A square pattern of size N x N (1 <= N <= 10) black and white square tiles is transformed into another square pattern. Write a program that will recognize the minimum transformation that has been applied to the original pattern given the following list of possible transformations:

* #1: 90 Degree Rotation: The pattern was rotated clockwise 90 degrees.
* #2: 180 Degree Rotation: The pattern was rotated clockwise 180 degrees.
* #3: 270 Degree Rotation: The pattern was rotated clockwise 270 degrees.
* #4: Reflection: The pattern was reflected horizontally (turned into a mirror image of * itself by reflecting around a vertical line in the middle of the image).
* #5: Combination: The pattern was reflected horizontally and then subjected to one of the * rotations (#1-#3).
* #6: No Change: The original pattern was not changed.
* #7: Invalid Transformation: The new pattern was not obtained by any of the above methods.


In the case that more than one transform could have been used, choose the one with the minimum number above.
