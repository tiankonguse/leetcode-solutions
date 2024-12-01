Telecowmunication
Farmer John's cows like to keep in touch via email so they have created a network of cowputers so that they can intercowmunicate.
These machines route email so that if there exists a sequence of c cowputers a1, a2, ..., a(c) such that a1 is connected to a2, a2 is connected to a3, and so on then a1 and a(c) can send email to one another.

Unfortunately, a cow will occasionally step on a cowputer or Farmer John will drive over it, and the machine will stop working. This means that the cowputer can no longer route email, so connections to and from that cowputer are no longer usable.

Two cows are pondering the minimum number of these accidents that can occur before they can no longer use their two favorite cowputers to send email to each other.
Write a program to calculate this minimal value for them, and to calculate a set of machines that corresponds to this minimum.

For example the network:

               1
              /  
             3 - 2
shows 3 cowputers connected with 2 lines. We want to send messages between cowputers 1 and 2. Direct lines connect 1-3 and 2-3. If cowputer 3 is down, them there is no way to get a message from 1 to 2.
PROGRAM NAME: telecow
INPUT FORMAT
Line 1	Four space-separated integers: N, M, c1, and c2. N is the number of computers (1 <= N <= 100), which are numbered 1..N. M is the number of connections between pairs of cowputers (1 <= M <= 600).
The last two numbers, c1 and c2, are the id numbers of the cowputers that the communicating cows are using. Each connection is unique and bidirectional (if c1 is connected to c2, then c2 is connected to c1). There can be at most one wire between any two given cowputers.
Computers c1 and c2 will not have a direct connection.
Lines 2..M+1	The subsequent M lines contain pairs of cowputers id numbers that have connections between them.
SAMPLE INPUT (file telecow.in)
3 2 1 2
1 3
2 3
OUTPUT FORMAT
Generate two lines of output. The first line is the minimum number of (well-chosen) cowputers that can be down before terminals c1 & c2 are no longer connected. The second line is a minimal-length sorted list of cowputers that will cause c1 & c2 to no longer be connected.
Note that neither c1 nor c2 can go down. In case of ties, the program should output the set of computers that, if interpreted as a base N number, is the smallest one.

SAMPLE OUTPUT (file telecow.out)
1
3