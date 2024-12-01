Canada Tour
You have won a contest sponsored by an airline. The prize is a ticket to travel around Canada, beginning in the most western point served by this airline, then traveling only from west to east until you reach the most eastern point served, and then coming back only from east to west until you reach the starting city. No city may be visited more than once, except for the starting city, which must be visited exactly twice (at the beginning and the end of the trip). You are not allowed to use any other airline or any other means of transportation.

Given a list of cities served by the airline and a list of direct flights between pairs of cities, find an itinerary which visits as many cities as possible and satisfies the above conditions beginning with the first city and visiting the last city on the list and returning to the first city.

PROGRAM NAME: tour
INPUT FORMAT
Line 1:	The number N of cities served by the airline and the number V of direct flights that will be listed. N will be a positive integer not larger than 100. V is any positive integer.
Lines 2..N+1:	Each line contains a name of a city served by the airline. The names are ordered from west to east in the input file. There are no two cities in the same meridian. The name of each city is a string of, at most, 15 digits and/or characters of the Latin alphabet; there are no spaces in the name of a city.
Lines N+2..N+2+V-1:	Each line contains two names of cities (taken from the supplied list), separated by a single blank space. This pair is connected by a direct, two-way airline flight.
SAMPLE INPUT (file tour.in)
8 9	
Vancouver		
Yellowknife	
Edmonton
Calgary
Winnipeg
Toronto	
Montreal
Halifax	
Vancouver Edmonton
Vancouver Calgary	
Calgary Winnipeg
Winnipeg Toronto
Toronto Halifax
Montreal Halifax
Edmonton Montreal
Edmonton Yellowknife
Edmonton Calgary
OUTPUT FORMAT
Line 1:	The number M of different cities visited in the optimal itinerary. Output 1 if no itinerary is possible.
SAMPLE OUTPUT (file tour.out)
7
Namely: Vancouver, Edmonton, Montreal, Halifax, Toronto, Winnipeg, Calgary, and Vancouver (but that's not a different city).