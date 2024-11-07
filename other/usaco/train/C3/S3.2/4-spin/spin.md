Spinning Wheels
1998 ACM NE Regionals
Each of five opaque spinning wheels has one or more wedges cut out of its edges. These wedges must be aligned quickly and correctly. Each wheel also has an alignment mark (at 0 degrees) so that the wheels can all be started in a known position.
Wheels rotate in the `plus degrees' direction, so that shortly after they start, they pass through 1 degree, 2 degrees, etc. (though probably not at the same time).

This is an integer problem. Wheels are never actually at 1.5 degrees or 23.51234123 degrees. For example, the wheels are considered to move instantaneously from 20 to 25 degrees during a single second or even from 30 to 40 degrees if the wheel is spinning quickly.

All angles in this problem are presumed to be integers in the range 0 <= angle <= 359. The angle of 0 degrees follows the angle of 359 degrees. Each wheel rotates at a certain integer number of degrees per second, 1 <= speed <= 180.

Wedges for each wheel are specified by an integer start angle and integer angle size (or `extent'), both specified in degrees. Wedges in the test data will be separated by at least one degree.
The 'extent' also includes the original "degree" of the wedge, so '0 180' means degrees 0..180 inclusive -- one more than most would imagine.

At the start, which is time 0, all the wheels' alignment marks line up.
Your program must determine the earliest time (integer seconds) at or after the start that some wedge on each wheel will align with the wedges on the other wheel so that a light beam can pass through openings on all five wedges.
The wedges can align at any part of the rotation.

PROGRAM NAME: spin
INPUT FORMAT
Each of five input lines describes a wheel.

The first integer on an input line is the wheel's rotation speed. The next integer is the number of wedges, 1 <= W <= 5. The next W pairs of integers tell each wedge's start angle and extent.

SAMPLE INPUT (file spin.in)
30 1 0 120
50 1 150 90
60 1 60 90
70 1 180 180
90 1 180 60
OUTPUT FORMAT
A single line with a single integer that is the first time the wedges align so a light beam can pass through them. Print `none' (lower case, no quotes) if the wedges will never align properly.

SAMPLE OUTPUT (file spin.out)
9