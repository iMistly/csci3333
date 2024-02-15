# CSCI 3333 Project One
## Binary Arithmetic Expression Trees

### Basic Part (100 points)
#### Problem Description

This project is about design and implement expression trees, which are special cases of parse trees or grammar trees. you need to implement a program to do the following:

1. Takes a binary arithmetic expression as input, builds a binary expression tree for the input expression
2. Check whether there are any syntactic or semantic errors in the expression. If yes, then report the errors. 
3. If there are no errors in the input expression, then:
    - Calculate and display the value of the input expression.
    - Print the infix (in-order traversal), prefix (pre-order traversal) and postfix (post-order traversal) expressions of the input expression.

For ease of your implementation and testing, your program shall input arithmetic expressions from a text file. To help build the binary expression tree, you shall use two stack type data structures, one helps manage operators from the arithmetic expression, and the other help manage the tree nodes for building the trees.
The table below lists operation precedence and association orders.

|Operator|Precedence (or Priority)|Association Order|
|--------|------------------------|-----------------|
|(  )	 |0 (highest precedence)  |left to right    |
|*, /	 |1	                      |left to right    |
|+, -	 |2	                      |left to right    |

Use the following input arithmetic expressions to test your program:
1. (10.24 + 5.4 * 2.5) / 6.7 + (12.5 * 20.67 + 10) * 25
2. (10.24 + 5.4 * 2.5) / 6.7 + (12.5 * 20.67 + 10) * 25)
3. (10.24 + 5.4 * 2.5) / 6.7 + (12.5 * 20.67 + ) * 25
Note: 
    - Expression 1 has no syntactic errors. 
    - Expressions 2 and 3 have one error each. 

#### Optional Part - for possible extra credits

In addition to binary arithmetic expressions, I would like you to consider binary relation operators of <, <=, ==, !=, >, >=, and logical operators of ||, &&, and !. I ask you to expand the functionality of your program for binary arithmetic expressions to deal with expressions that is composed of parentheses, binary arithmetic operator, binary relational operators, and logical operators. 
This optional part is not required. If you can finish it, I'll give 5 to 10 extra points for you. 
Use the following input arithmetic expressions to test your program:
1. (10.24 + 5.4 * 2.5) / 6.7 >= (12.5 * 20.67 + 10) * 25
2. (10.24 + 5.4 * 2.5 <= 100)  &&  (12.5 * 20.67 < 10 * 25)
3. (10.24 <= 5.4 * 2.5) || (!  ((26 / 12 <= 5 + 9)  &&  (12.5 * 20.67 < 10 * 25)))


