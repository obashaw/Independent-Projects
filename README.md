# K-Means
This code is a K-Means clustering program I built from scratch in C++.  I have 2 semesters of experience in C++ and used the
extent of my formal training to complete this project.  

The Centroid class is for the Centroid object itself and it stores information about a given cluster, namely its location
in n-Dimensional space and its member points (defined in the DataVector Struct).  Aside from constructors/destructor, this
class contains member functions to assign and reassign DataVectors to different Centroids, recompute the location of the 
Centroid and display member variables.

The main.cpp is the bulk of the sorting algorithm. This is where the desired data file is selected from a predetermined 
list and loaded.  There are functions broken down into small pieces like finding the nearest Centroid to a DataVector and 
to check if a Centroid has 0 DataVectors, and more complex ones like running the entire program using the smaller 
functions and loops.


