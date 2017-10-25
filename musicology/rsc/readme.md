
#### Currently the rules are organised as following.


We are on the Level 1 of Counterpoint i.e we put a Musical Symbol in a postion according to the Musical Symbol in the below position. So, we only care about the below symbol.

We have a [**rules**](rules) file where we store the rules. In this file you can see a column of numbers separated with empty lines.
**Note**, each number represents a Musical Note and it is the Musical Note's ID. So what we see in the document is the IDs.

The last two numbers of each batch are the Musical Symbols (we see IDs in our case) that are valid to be entered if in the lower pentagram we have a Musical Symbol, which has an ID equal to the first number of the batch.

**So, imagine that the first number is the symbol in the lower pentagram and the next numbers are the symbols that could be entered in the upper pentagram.**