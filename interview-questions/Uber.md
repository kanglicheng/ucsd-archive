#UCSDCSEIQ_Uber
1st Round: On-Campus Interview with a dude (45 Minutes)
1. Given an integer n, print out all valid sets of parentheses using 2n parentheses
If n = 2, then Answer = ()(), (())
2nd Round: Phone Interview (45 Minutes)
2. Assume you’re drawing cards one by one from a deck and you want to stop when you have a straight in your hand (Interviewer defined a straight as a set of 5 cards of sequential rank, so 2,3,4,5,6). Write an algorithm to do this in O(n) time and return the earliest straight that you find.
Ex. Assume you’re drawing these cards one by one: A, 4, 3, 2, 9, 5, 8, 7, 6
You would stop when you draw the 5 because in your hand you have the cards A 2 3 4 and if you add on the 5, you can form a straight.
The straight you would return is A 2 3 4 5. Although 5 6 7 8 9 is also a straight, it comes up later in the deck (you would draw it later), so it wouldn’t be the earliest one.