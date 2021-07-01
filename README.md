## Binomial Tree Construction and Reduction

This code serves as a demonstration of my C++ knowledge. I decided to test myself by completing a EEE (Electronics and Electrical Engineering) computing assignment. 

The aim of the assignment was to first create a Binomial tree using a vector of strings containing the `true` branches. 

Following an input of: 


    std::vector<std::string> fv;
    std::string row;

    row = "11";
    fv.push_back(row);

    BoolTree ft1(fv);


The program should store the following tree in `ft1` <br> 

[Simple tree](media/simple_tree.PNG)

The second part of the assignment was to simplify the binomial tree. This meant that if a node's two branches were identical, the node should become either branch. 

[Example of simplification](media/simplification.PNG)

-------------------------

## My Solution

To complete this assignment I saw no other option than using ___recursive functions___. 

I decomposed the problem into several steps: 

1. Construct the tree
    1. Construct a `0`- filled tree
    2. Change the tree to include the `true` / `1` values
3. Simplify the tree
    1. Given a node, compare if both branches are identical
    2. If identical, change the current node to one of the branches
    3. If different, do the analysis on both branches

To verify whether the construction of the tree was correctly done, I wrote `get_string()`, a function that given a node it's branches' nodes from left to right. 

I was able to use this function in the simplification process by
1. Getting the string of a node
2. Removing the current node's value 
3. Separating the resultant string into 2 string (left branch and right branch)
4. Comparing both left and right strings

