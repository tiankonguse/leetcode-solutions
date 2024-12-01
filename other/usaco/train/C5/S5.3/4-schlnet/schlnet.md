Network of Schools
IOI '96 Day 1 Problem 3
A number of schools are connected to a computer network. Agreements have been developed among those schools: each school maintains a list of schools to which it distributes software (the "receiving schools").
Note that if B is in the distribution list of school A, then A does not necessarily appear in the list of school B.

You are to write a program that computes the minimal number of schools that must receive a copy of the new software in order for the software to reach all schools in the network according to the agreement (Subtask A).
As a further task, we want to ensure that by sending the copy of new software to an arbitrary school, this software will reach all schools in the network. To achieve this goal we may have to extend the lists of receivers by new members.
Compute the minimal number of extensions that have to be made so that whatever school we send the new software to, it will reach all other schools (Subtask B). One extension means introducing one new member into the list of receivers of one school.

PROGRAM NAME: schlnet
INPUT FORMAT
The first line of the input file contains an integer N: the number of schools in the network (2<=N<=100). The schools are identified by the first N positive integers. Each of the next N lines describes a list of receivers.
The line i+1 contains the identifiers of the receivers of school i. Each list ends with a 0. An empty list contains a 0 alone in the line.

SAMPLE INPUT (file schlnet.in)
5
2 4 3 0
4 5 0
0
0
1 0
OUTPUT FORMAT
Your program should write two lines to the output file. The first line should contain one positive integer: the solution of subtask A. The second line should contain the solution of subtask B.


SAMPLE OUTPUT (file schlnet.out)
1
2