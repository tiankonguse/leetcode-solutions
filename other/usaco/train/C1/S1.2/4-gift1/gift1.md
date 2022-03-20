# Task 'gift1': Greedy Gift Givers

A group of NP (2 ≤ NP ≤ 10) uniquely named friends has decided to exchange gifts of money. Each of these friends might or might not give some money to some or all of the other friends (although some might be cheap and give to no one). Likewise, each friend might or might not receive money from any or all of the other friends. Your goal is to deduce how much more money each person receives than they give.

The rules for gift-giving are potentially different than you might expect. Each person goes to the bank (or any other source of money) to get a certain amount of money to give and divides this money evenly among all those to whom he or she is giving a gift. No fractional money is available, so dividing 7 among 2 friends would be 3 each for the friends with 1 left over – that 1 left over goes into the giver's "account". All the participants' gift accounts start at 0 and are decreased by money given and increased by money received.

In any group of friends, some people are more giving than others (or at least may have more acquaintances) and some people have more money than others.

Given:

* a group of friends, no one of whom has a name longer than 14 characters,
* the money each person in the group spends on gifts, and
* a (sub)list of friends to whom each person gives gifts,


determine how much money each person ends up with.

## IMPORTANT NOTE


The grader machine is a Linux machine that uses standard Unix conventions: end of line is a single character often known as '\n'. This differs from Windows, which ends lines with two characters, '\r\ and '\n'. Do not let your program get trapped by this!