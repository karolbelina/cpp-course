# zmpo
This repository contains the code written for the Advanced object-oriented programming methods lab course (also known as "The C++ course") taught by dr inż. Michał Przewoźniczek.

## Assignments
The assignments given on the course were not self-contained.
To address that, the code shared by multiple assignments has been separated out into its own static library.
This library is then linked to the actual assignments through references, by setting the proper `AdditionalIncludeDirectories` in Visual Studio Community 2017, which is the software used throughout the course.

The instructions for the assignments are available in Polish in the [instructions](instructions) directory.

### assg1
This assignment acted as an introduction to the C++ language and its many intricacies.
The task was to define a custom list class based on an array of numbers.

As the code related to the tables is used later in the assignment 3, it's contained in the [table](src/table) catalog.

### assg2
In this assignment, the student had to write a set of classes, which would act as building blocks for creating a basic command line interface.
Such interface would be made out of items, and an item could be either a command or a menu containing a set of items. The resulting tree could be then traversed by the user by inputing the IDs of the items in a prompt.

This code is used throughout the whole course, so it was reasonable to put it in a separate catalog called [menu](src/menu).

### assg3
The main point of this assignment was to create a basic recursive descent parser for the grammar
```ebnf
item    = menu | command;
menu    = "(", name, ",", id, ";" [ item ], { ",", item }, ")";
command = "[", name, ",", id, ",", help string, "]";
```
which would transform an input string into the menu item tree defined in assignment 2.
The program would notify the user of any syntax errors encountered during the parsing.

The student also had to define a set of custom commands for manipulating and managing the tables defined in assignment 1.

### assg4
The aim of this assignment was to solve the [0/1 knapsack problem](https://en.wikipedia.org/wiki/Knapsack_problem) with a use of a genetic algorithm.

The `GeneticAlgorithm` class is a template for any _problem_, as long as that _problem_ defines a gene, a mutation function of that gene, and a fitness function for a genotype.
The algorithm itself uses a simple two-point crossover for the creation of new individuals. The user can also define the population size, the probabilities of a mutation and a crossover, as well as the size of the elitist selection.

The code related to the genetic algorithm and the knapsack problem was put in a [genalg](src/genalg) catalog, as it's used in assignment 5, too.

### liveassg
As the code for each of the previous assignments was written over any of the last two weeks outside of the actual classes, this time the student had about an hour to finish the whole assignment.
This tested whether the student was capable of solving a problem in a short period of time.

Every task assigned to each lab group was a little different to prevent cheating. What I got was to create a set of functions for three-dimensional arrays, which involved a bunch of pointers.

### assg5
This time the student had to make an extension to the knapsack problem defined in assignment 4.
Apart from the 0/1, the genetic algorithm should also solve the unbounded and the continuous knapsack problem variation.
Everything had to be wrapped in a menu from assignments 2 and 3.

## Notes
- Throughout the code I throw exceptions against the will of the professor.
  Should you take any inspiration from this code while attending this course, make sure to define a bunch of enums that act as error codes.
- I'm not planning on refactoring this in any way in the future.
  Some things could have been done better for sure, but I don't care anymore.