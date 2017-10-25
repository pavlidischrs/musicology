# Getting Started

### Algorithm Description

Each Musical Symbol in our implementation has an **ID**. Currently we have 10 Musical Notes so IDs are from 0 to 9. 

#### Back End

To show the lower pentagram we create a vector of numbers, where each number is a Musical Note ID (**givenExercise**). Then, the Front End reads this sequence and displays the Musical Symbols, which have ID equal to the numbers of the sequence.

When the User puts a new Musical Symbol in the upper pentagram (clicks a Musical Note from Choices Box), we read the ID of the chosen Symbol and store it in a vector (**givenAnswer**). This vector will be the user's answer. 

The evaluation process reads the **Rules**, the **givenAnswer** and the **givenExercise** to infer if the given answer is correct.

(check for rules on [src/](/src)).


#### Front End (Qt Graphics)
We have implemented the **MusicalNoteItem Class**, which inherits from the **QGraphicsPixmapItem Class**. To show the Musical Notes we add the items in QGraphicsScene and visualise it with QGraphicsView. 

The **MusicalNoteItem** overrides the **mouserPressEvent** to handle the event when user clicks on a Musical Note from the Choices Box. We overrode this event so as to place the clicked Musical Note to the **upper pentagram**.




## Installing
Clone or download and compile the code.

## Prerequisites

* Qt SDK (Check **Built With** section to see my work environment)

# Usage

1. Press **Create New Exercise**
1. Choose the right symbols from the **Choices Box**
1. Press **Check Answer** to check you answer
1. Create a new exercise and keep solving


# Built With 
* QtCreator IDE 5.9.2 with the MSVC 2015 Kit (on Windows 10)





