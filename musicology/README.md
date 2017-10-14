
# Algorithm Description

In our implementation each **Musical Symbol** corresponds to a **number**. 

As you can see in **src/rules.txt** each number (Musical Note) has some other numbers (Musical Notes) below, which are the rules of this number (Musical Note). The current chosen rules are 2 for each note and have length 2. 
**Note**, each note could have one or more rules of different lengths. We will fix this issue as soon as we have the rules.


Flow:
1. In order to create an exercise the algorithm **reads the rules** and **creates** valid sequences of numbers, i.e. a Musical Sequence.

1. Then, it chooses which digits to hide, i.e. **hides** some Musical Notes from the created Musical Sequence.

1. Finally, the **user is asked** to fill the gaps of the Musical Sequence.




