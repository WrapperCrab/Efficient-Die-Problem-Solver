# Efficient Die Problem Solver
## A Solution to a Very Specific Problem
Given an n-sided die and a rational probability, this script finds the best way to simulate that probability with the die.

### How to Use
Just compile the code and run it. It runs in the terminal and will ask for the input it needs.\
Choice 1 finds and describes the optimal strategy using your given die and probability.\
Choice 2 analyzes a specific strategy given by the user.

### Any Die can Simulate Any Rational Probability
Imagine you are playing an rpg where you want a player to have a 1 in 5 chance of success and a 4 in 5 chance of failure.\
Easy enough if you have a 5-sided die lying around, but unfortunately, you only have a coin!\
Luckily, it's still possible.

What you do is flip the coin 3 times, keeping track of the results each time.\
Let's say that tails is 0 and heads is 1.\
From our flip, we can create a 3-digit binary number. Suppose we rolled 101 which is 5 in decimal.\
Then, we simply follow this algorithm:
```
if 1=result, then it's a success!
if 1<result<=5, then it's a failure.
if 5<result<=8, then we must retry the simulation.
```
And this will simulate a probability of 1/5 with a coin. The average/expected number of rolls this will take is 4.8.

This idea can be generalized to any die with at least 2 sides, and any rational probability.

### What is there to Solve?
Consider the example from the previous section.\
What if instead of thinking of the probability as 1/5, we thought of it as 3/15?

Then, we could flip our coin 4 times to get a number 1 to 16.
```
if 1<=result<=3, then it's a success!
if 3<result<=15, then it's a failure.
if result=16, then we must retry the simulation.
```
This also simulates a probability of 1/5 with a coin. 
However, the probability to retry is much lower, and as such, the average number of needed rolls is only 4.26667 which is smaller than the previous strategy.

So, this script finds the most efficient way to simulate a given probability with a given die.

It optimizes for: (ties are broken by following list item)
1. Lowest Expected Number of Rolls
2. Lowest Probability for Retry
3. Lowest Number of Rolls per Attempt
