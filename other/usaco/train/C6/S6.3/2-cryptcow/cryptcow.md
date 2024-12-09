Cryptcowgraphy
Brian Dean
The cows of Farmer Brown and Farmer John are planning a coordinated escape from their respective farms and have devised a method of encryption to protect their written communications.

Specifically, if one cow has a message, say, "International Olympiad in Informatics", it is altered by inserting the letters C, O, and W, in random location in the message, such that C appears before O, which appears before W. Then the cows take the part of the message between C and O, and the part between O and W, and swap them. Here are two examples:

            International Olympiad in Informatics
                              -> 
            CnOIWternational Olympiad in Informatics
            
            International Olympiad in Informatics
                              -> 
            International Cin InformaticsOOlympiad W
To make matters more difficult, the cows can apply their encryption scheme several times, by again encrypting the string that results from the previous encryption. One night, Farmer John's cows receive such a multiply-encrypted message. Write a program to compute whether or not the non-encrypted original message could have been the string:

            Begin the Escape execution at the Break of Dawn
PROGRAM NAME: cryptcow
INPUT FORMAT
A single line (with both upper and lower case) with no more than 75 characters that represents the encrypted message.
SAMPLE INPUT (file cryptcow.in)
Begin the EscCution at the BreOape execWak of Dawn
OUTPUT FORMAT
Two integers on a single line. The first integer is 1 if the message decodes as an escape message; 0 otherwise. The second integer specifies the number of encryptions that were applied (or 0 if the first integer was 0).
SAMPLE OUTPUT (file cryptcow.out)
1 1