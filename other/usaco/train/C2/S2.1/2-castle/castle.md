## The Castle

IOI'94 - Day 1

In a stroke of luck almost beyond imagination, Farmer John was sent a ticket to the Irish Sweepstakes (really a lottery) for his birthday. 
This ticket turned out to have only the winning number for the lottery! 
Farmer John won a fabulous castle in the Irish countryside.


Bragging rights being what they are in Wisconsin, Farmer John wished to tell his cows all about the castle. 
He wanted to know how many rooms it has and how big the largest room was. 
In fact, he wants to take out a single wall to make an even bigger room.


Your task is to help Farmer John know the exact room count and sizes.

The castle floorplan is divided into M (wide) by N (1 <=M,N<=50) square modules. 
Each such module can have between zero and four walls. 
Castles always have walls on their "outer edges" to keep out the wind and rain.


Consider this annotated floorplan of a castle:

```
     1   2   3   4   5   6   7
   #############################
 1 #   |   #   |   #   |   |   #
   #####---#####---#---#####---#   
 2 #   #   |   #   #   #   #   #
   #---#####---#####---#####---#
 3 #   |   |   #   #   #   #   #   
   #---#########---#####---#---#
 4 # ->#   |   |   |   |   #   #   
   ############################# 

#  = Wall     -,|  = No wall
-> = Points to the wall to remove to
     make the largest possible new room
```


By way of example, this castle sits on a 7 x 4 base. 
A "room" includes any set of connected "squares" in the floor plan. 
This floorplan contains five rooms (whose sizes are 9, 7, 3, 1, and 8 in no particular order).


Removing the wall marked by the arrow merges a pair of rooms to make the largest possible room that can be made by removing a single wall.

The castle always has at least two rooms and always has a wall that can be removed.

PROGRAM NAME: castle
INPUT FORMAT
The map is stored in the form of numbers, one number for each module ("room"), M numbers on each of N lines to describe the floorplan. The input order corresponds to the numbering in the example diagram above.

Each module descriptive-number tells which of the four walls exist and is the sum of up to four integers:

1: wall to the west
2: wall to the north
4: wall to the east
8: wall to the south
Inner walls are defined twice; a wall to the south in module 1,1 is also indicated as a wall to the north in module 2,1.
Line 1:	Two space-separated integers: M and N
Line 2..:	M x N integers, several per line.

SAMPLE INPUT (file castle.in)
7 4
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13
OUTPUT FORMAT
The output contains several lines:
Line 1:	The number of rooms the castle has.
Line 2:	The size of the largest room
Line 3:	The size of the largest room creatable by removing one wall
Line 4:	The single wall to remove to make the largest room possible

Choose the optimal wall to remove from the set of optimal walls by choosing the module farthest to the west (and then, if still tied, farthest to the south). If still tied, choose 'N' before 'E'.
Name that wall by naming the module that borders it on either the west or south, along with a direction of N or E giving the location of the wall with respect to the module.

SAMPLE OUTPUT (file castle.out)
5
9
16
4 1 E
INPUT DETAILS
First, the map is partitioned like below. Note that walls not on the outside borders are doubled:

     1    2    3    4    5    6    7
   ####|####|####|####|####|####|#####
 1 #   |   #|#   |   #|#   |    |    #
   ####|   #|####|   #|#   |####|    #
  -----|----|----|----|----|----|-----
   ####|#   |####|#  #|#  #|####|#   #
 2 #  #|#   |   #|#  #|#  #|#  #|#   #
   #  #|####|   #|####|#  #|####|#   #
  -----|----|----|----|----|----|-----
   #   |####|   #|####|#  #|####|#   #
 3 #   |    |   #|#  #|#  #|#  #|#   #
   #   |####|####|#  #|####|#  #|#   #
  -----|----|----|----|----|----|-----
   #  #|####|####|    |####|   #|#   #
 4 #  #|#   |    |    |    |   #|#   #
   ####|####|####|####|####|####|#####
Let's talk about the squares with a (row, column) notation such that the lower right corner is denoted (4, 7).

The input will have four lines, each with 7 numbers. Each number describes one 'room'. >Walls further toward the top are 'north', towards the bottom are 'south', towards the left are 'west', and towards the right are 'east'.

Consider square (1,1) which has three walls: north, south, and west. To encode those three walls, we consult the chart:

1: wall to the west
2: wall to the north
4: wall to the east
8: wall to the south
and sum the numbers for north (2), south (8), and west (1). 2 + 8 + 1 = 11, so this room is encoded as 11.
The next room to the right (1,2) has walls on the north (2) and east (4) and thus is encoded as 2 +4 = 6.

The next room to the right (1,3) is the same as (1,1) and thus encodes as 11.

Room (1,4) is the same as (1,2) and thus encodes as 6.

Room (1,5) has rooms on the west (1) and north (2) and thus encodes as 1 + 2 = 3.

Room (1,6) has rooms on the north (2) and south (8) and thus encodes as 2 + 8 = 10.

Room (1,7) is the same as room (1,2) and thus encodes as 6.

This same method continues for rooms (2,1) through (4,7).