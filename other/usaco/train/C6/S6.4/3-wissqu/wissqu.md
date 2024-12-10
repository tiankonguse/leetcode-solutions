Wisconsin Squares
It's spring in Wisconsin and time to move the yearling calves to the yearling pasture and last year's yearlings to the greener pastures of the north 40.

Farmer John has five kinds of cows on his farm (abbreviations are shown in parentheses): Guernseys (A), Jerseys (B), Herefords (C), Black Angus (D), and Longhorns (E).
These herds are arranged on the 16 acre pasture, one acre for each small herd, on a 4 x 4 grid (labeled with rows and columns) like this:

              1 2 3 4
             +-------
            1|A B A C
            2|D C D E
            3|B E B C
            4|C A D E
In the initial pasture layout, the herds total 3 A's, 3 B's, 4 C's, 3 D's, and 3 E's. This year's calves have one more D herd and one fewer C herd, for a total of 3 A's, 3 B's, 3 C's, 4 D's, and 3 E's.

FJ is extremely careful in his placement of herds onto his pasture grid. This is because when herds of the same types of cows are too close together, they misbehave: they gather near the fence and smoke cigarettes and drink milk.
Herds are too close together when they are on the same square or in any of the eight adjacent squares.

Farmer John must move his old herd out of the field and his new herd into the field using his old brown Ford pickup truck, which holds one small herd at a time.
He picks up a new herd, drives to a square in the yearling pasture, unloads the new herd, loads up the old herd, and drives the old herd to the north 40 where he unloads it.
He repeats this operation 16 times and then drives to Zack's for low-fat yogurt treats and familiar wall decor.

Help Farmer John. He must choose just exactly the correct order to replace the herds so that he never puts a new herd in a square currently occupied by the same type of herd or adjacent to a square occupied by the same type of herd.
Of course, once the old cows are gone and the new cows are in place, he must be careful in the future to separate herds based on the new arrangement.

Very important hint: Farmer John knows from past experience that he must move a herd of D cows first.

Find a way for Farmer John to move the yearlings to their new pasture. Print the 16 sequential herd-type/row/column movements that lead to a safe moving experience for the cows.

Calculate the total number of possible final arrangements for the 4x4 pasture and calculate the total number of ways those arrangements can be created.

PROGRAM NAME: wissqu
TIME LIMIT: 5 seconds
INPUT FORMAT
Four lines, each with four letters that denote herds.

SAMPLE INPUT (file wissqu.in)
ABAC
DCDE
BEBC
CADE
OUTPUT FORMAT
16 lines, each with a herd-type, row and column. If there are multiple solutions (and there are), you should output the solution for which the concatenated string ("D41C42A31 ... D34") of the answers is first in lexicographic order.

One more line with the total number of ways these arrangements can be created.

SAMPLE OUTPUT (file wissqu.out)
D 4 1
C 4 2
A 3 1
A 3 3
B 2 4
B 3 2
B 4 4
E 2 1
E 2 3
D 1 4
D 2 2
C 1 1
C 1 3
A 1 2
E 4 3
D 3 4
14925