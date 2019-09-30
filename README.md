# Parallelization using OpenMP on C and Python for Plotting the Execution Time Comparison Between Linear and Parallel Programming


C Programs which implement the Breadth First Search on graphs, linear search on arrays, inorder traversal on binary search tree, merge sort and selection sort. And then their proper parallelization using OpenMP to turn them into multiprocessing programs. It also includes an execution time comparison using plotting on Python


### Execution

Each Folder contains modules with the implementation of the algorithm on both linear and parallel programming. 

They also contain a program in C which generates statistics comparing both linear and parallel execution times on the data structure the algorithm is based on while the elements increase. These statistics ca then be plotted by using the program graphStatistics on python.

For instance, to compare the Merge Sort Algorithm the execution would go something like this.

```
cd MergeSort/
gcc -o TimeToFile.o TimeToFile.c
TimeToFile.o
python grahStatistics.py
```


## Built With

* [OpenMP](https://www.openmp.org/) - The OpenMP API specification for parallel programming
* [Python](https://www.python.org) - Programming Language to Analyze statistics on file
* [Matplotlib](https://matplotlib.org) - Python 2D Plotting library
* C - Programming Language


## Authors

* **Zuriel Rodriguez** (https://github.com/nowhereknight)
