//
//  main.cpp
//  K Means
//
//  Created by O Bashaw on 6/10/19.
//  Copyright © 2019 O Bashaw. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Centroid.h"
#include <cstddef>

// Headers:
void group (std::vector<DataVector*> &vectors, std::vector<Centroid*> &centroids, const unsigned DIM, unsigned round);
void findNearest (DataVector* vect, std::vector<Centroid*> &centroids, const unsigned DIM, unsigned round);
double calcEuclidian (DataVector* vect, Centroid* cent, const unsigned DIM);
void display(std::vector<Centroid*> &cSet);
void checkEmpty(std::vector<Centroid*> &cSet, std::vector<DataVector*> &vSet, const unsigned DIM);
DataVector* findFarthest(std::vector<DataVector*> &vSet, const unsigned DIM);
void load2D(std::string file, std::vector<DataVector*> &vSet);
void load3D(std::string file, std::vector<DataVector*> &vSet);
void run(std::vector<DataVector*> &vSet, std::vector<Centroid*> &cSet);

const unsigned DIM = 3;

int main()
{
    std::srand(std::time(NULL));
    
    std::cout << "K-means algorithm" << std::endl;
    // Prompt user for file choice
    unsigned i = 0;
    std::cout << "Which dataset would you like to cluster?" << std::endl;
    std::cout << "0) Quit" << std::endl;
    std::cout << "1) 'g2-2-30.txt' : 2D set with N = 2048 vectors and k = 2 clusters" << std::endl;
    std::cout << "2) 's1.txt' : 2D set with N = 5000 vectors and k = 15 clusters" << std::endl;
    std::cout << "3) 'a1.txt' : 2D set with N = 3000 vectors and k = 20 clusters" << std::endl;
    std::cout << "4) 'dim.txt' : 3D set with N = 2026 vectors and k = 9 clusters" << std::endl;
    std::cin >> i;
    
    // create vector vSet of DataVector*
    std::vector<DataVector*> vSet;
    // create vector cSet of Centroid*
    std::vector<Centroid*> cSet;
    
    // based on user selection
    if (i == 1)
    {
        // load vectors from g2-2-100.txt
        load2D("g2-2-30.txt", vSet);
        std::cout << "DataVectors loaded: " << vSet.size() << std::endl;
        
        // create 2 centroids for K-means
        for (unsigned j = 0; j < 2; j++)
        {
            Centroid* c1 = new Centroid(2, vSet);
            cSet.push_back(c1);
        }
        std::cout << "Centroids created: " << cSet.size() << std::endl;
        run(vSet, cSet);
    }
    else if (i == 2)
    {
        // load vectors from s1.txt
        load2D("s1.txt", vSet);
        std::cout << "DataVectors loaded: " << vSet.size() << std::endl;
        
        // create 15 centroids for K-means
        for (unsigned j = 0; j < 15; j++)
        {
            Centroid* c1 = new Centroid(2, vSet);
            cSet.push_back(c1);
        }
        std::cout << "Centroids created: " << cSet.size() << std::endl;
        run(vSet, cSet);
    }
    else if (i == 3)
    {
        // load vectors from a1.txt
        load2D("a1.txt", vSet);
        std::cout << "DataVectors loaded: " << vSet.size() << std::endl;
        // create 15 centroids for K-means
        for (unsigned j = 0; j < 20; j++)
        {
            Centroid* c1 = new Centroid(2, vSet);
            cSet.push_back(c1);
        }
        std::cout << "Centroids created: " << cSet.size() << std::endl;
        run(vSet, cSet);
    }
    else if (i == 4)
    {
        // load vectors from dim3.txt
        load3D("dim3.txt", vSet);
        std::cout << "DataVectors loaded: " << vSet.size() << std::endl;

        // create 9 centroids for K-means
        for (unsigned j = 0; j < 9; j++)
        {
            Centroid* c1 = new Centroid(3, vSet);
            cSet.push_back(c1);
        }
        std::cout << "Centroids created: " << cSet.size() << std::endl;
        run(vSet, cSet);
    }
    
    // destroy c1 and c2, set both to nullptr
    for (auto i : cSet)
    {
        delete i;
        i = nullptr;
    }
    
    return 0;
}

// Function: run
// Purpose: cluster the data
// Returns: none
void run(std::vector<DataVector*> &vSet, std::vector<Centroid*> &cSet)
{
    // round counter
    unsigned round = 0;
    
    // create N for dimension
    const unsigned DIM = 3;
    
    // create bool to track centroid updates
    bool changed = true;
    
    
    // operate while the centroids are changing location
    while (changed == true)
    {
        std::cout << "Round: " << round << std::endl;
        // print locations of each centroid
        for (auto i : cSet)
        {
            std::cout << "Centroid : " << i -> getLoc() << "\tVectors: " << i -> getMemberSize() << std::endl;
        }
        std::cout << std::endl;
        
        // call to group()
        group(vSet, cSet, DIM, round);
        
        // call to checkEmpty()
        checkEmpty(cSet, vSet, DIM);
        
        
        // for each centroid
        for (auto i : cSet)
        {
            // set changed to the value of recalcLoc()
            changed = i -> recalcLoc();
        } // end range based for
        
        // increment round and print
        round++;
        std::cout << "\n" << std::endl;
    } // end while
}


// Function: group
// Purpose: for all DataVectors, find the nearest centroid
// Returns: none
void group (std::vector<DataVector*> &vectors, std::vector<Centroid*> &centroids, const unsigned DIM, unsigned round)
{
    for (auto i : vectors)
    {
        // call to findNearest for each DataVector* in vSet
        findNearest(i, centroids, DIM, round);
    }
}


// Function: findNearest
// Purpose: given DataVector*, dimension and all available Centroids, find nearest centroid and assign cParent to it
// Returns: none
void findNearest (DataVector* vect, std::vector<Centroid*> &centroids, const unsigned DIM, unsigned round)
{
    // in the first round...
    if (round == 0)
    {
        // set dist to distance from vect to c[0]
        double dist = calcEuclidian(vect, centroids[0], DIM);
        
        // create link between vect and c[0]
        vect -> cParent = centroids[0];
        centroids[0] -> addMember(vect);
        
        for (unsigned i = 1; i < centroids.size(); i++)
        {
            // if there is a closer centroid than centroids[0]...
            if (calcEuclidian(vect, centroids[i], DIM) < dist)
            {
                // set dist to the distance to new centroid
                dist = calcEuclidian(vect, centroids[i], DIM);
                // switch membership from old cParent
                vect -> cParent -> switchMembership(vect, centroids[i]);
                // set cParent to new centroid
                vect -> cParent = centroids[i];
            } // end if for distance check
        } // end for
        
    } // end if for round check
    else
    {
        // for the remaining centroids
        for (unsigned i = 0; i < centroids.size(); i++)
        {
            // if the Euclidian from vector to centroid is less than current dist AND
            // the "newParent" centroids[i] is not equal to cParent (prevents unwanted duplication)
            double newDist = calcEuclidian(vect, centroids[i], DIM);
            double oldDist = calcEuclidian(vect, vect -> cParent, DIM);
            if ( newDist < oldDist && (centroids[i] != vect -> cParent) )
            {
                // remove Datavector from old cParent and add to new one
                vect -> cParent -> switchMembership(vect, centroids[i]);
                
                // set cParent to that centroid
                vect -> cParent = centroids[i];
            } // end if for distance and ownership check
            
        } // end for for iteration through centroid vector
    } // end else for round check
}

// Function: calcEuclidian
// Purpose: given a vector, centroid and dimension, compute the distance between the points
// Returns: double w/ distance
double calcEuclidian (DataVector* vect, Centroid* cent, const unsigned DIM)
{
    double dist = 0.0;
    // add square of each vector component to dist
    for (unsigned i = 0; i < DIM; i++)
    {
        // access ith element of mLoc
        double temp = vect -> mData[i] - cent -> getLocElement(i);
        // square it
        temp *= temp;
        // add to dist
        dist += temp;
    }
    // take nth root of the distance
    dist = std::pow(dist, (double) 1/DIM);
    
    return dist;
};


// Function: display
// Purpose: for every Centroid in the parameter vector, display the member DataVectors
// Returns: none
void display(std::vector<Centroid*> &cSet)
{
    for (auto i : cSet)
    {
        // print centroid and its address
        std::cout << "Centroid: " << i -> getLoc() << std::endl;
    }
}


// Function: checkEmpty
// Purpose: check if any Centroids have no members, and if they do, add the vector farthest to its cParent
// Returns: none
void checkEmpty(std::vector<Centroid*> &cSet, std::vector<DataVector*> &vSet, const unsigned DIM)
{
    // for every Centroid
    for (auto i : cSet)
    {
        // if there are no DataVectors in the mMember vector
        if (i -> getMemberSize() == 0)
         {
             // find the DataVector farthest from its centroid and switch membership to Centroid i
             DataVector* toSwitch = findFarthest(vSet, DIM);
             toSwitch -> cParent -> switchMembership(toSwitch, i);
         }
    }
}

// Function: findFarthest
// Purpose: find the vector that is farthest from its parent centroid and return it
// Returns: DataVector*
DataVector* findFarthest(std::vector<DataVector*> &vSet, const unsigned DIM)
{
    // create double for distance and DataVector* for return
    double dist = 0;
    DataVector* toRet = nullptr;
    
    // for every DataVector* ...
    for (auto i : vSet)
    {
        // if the distance from that vector to its parent is greater than the current farthest (dist)
        // and the current parent has more than 1 DataVector
        if (calcEuclidian(i, i -> cParent, DIM) > dist && i -> cParent -> getMemberSize() > 1)
        {
            // set dist to the distance from this vector to its parent
            dist = calcEuclidian(i, i -> cParent, DIM);
            
            // set the pointer to this vector
            toRet = i;
        }
    }
    return toRet;
}





// Function: load2D
// Purpose: create DataVector and add them to vSet by reading desired text file for 2D data
// Returns: none
void load2D(std::string file, std::vector<DataVector*> &vSet)
{
    std::ifstream read(file);
    // check that file opens
    if (read.is_open())
    {
        std::cout << "File open.\nReading..." << std::endl;
        while(!read.eof())
        {
            std::string line;
            std::getline(read, line);
            // size_t to hold beginning index of first number
            std::size_t start1 = line.find_first_of("0123456789");
            if (start1 != std::string::npos)
            {
                // make temp string that is line from beginning index of first num to end of string
                std::string t1 = line.substr(start1);
                // find the first ' ' after the string
                std::size_t end1 = t1.find_first_of(' ');
                // cast to double
                double x = std::stod(t1.substr(0, end1));
                // trim the first number from t1
                t1 = t1.substr(end1);
                
                // find beginning of second number
                std::size_t start2 = t1.find_first_of("0123456789");
                // trim it down into temp
                std::string t2 = t1.substr(start2);
                // find end of second number
                std::size_t end2 = t2.find_first_of(' ');
                // cast to double
                double y = std::stod(t2.substr(0, end2));
                DataVector* vect = new DataVector();
                vect -> mData.push_back(x);
                vect -> mData.push_back(y);
                vSet.push_back(vect);
            } // end inner if
        } // end while !eof()
    } // end is_open if
    
    else
    {
        std::cout << "File: " << file << " not open." << std::endl;
    }
}


// Function: load3D
// Purpose: create DataVector and add them to vSet by reading desired text file for 2D data
// Returns: none
void load3D(std::string file, std::vector<DataVector*> &vSet)
{
    std::ifstream read(file);
    // check that file opens
    if (read.is_open())
    {
        std::cout << "File open.\nReading..." << std::endl;
        while(!read.eof())
        {
            std::string line;
            std::getline(read, line);
            // size_t to hold beginning index of first number
            std::size_t start1 = line.find_first_of("0123456789");
            if (start1 != std::string::npos)
            {
                // make temp string that is line from beginning index of first num to end of string
                std::string t1 = line.substr(start1);
                // find the first ' ' after the string
                std::size_t end1 = t1.find_first_of(' ');
                // cast to double
                double x = std::stod(t1.substr(0, end1));
                // trim the first number from t1
                t1 = t1.substr(end1);
                
                // find beginning of second number
                std::size_t start2 = t1.find_first_of("0123456789");
                // trim it down into temp
                std::string t2 = t1.substr(start2);
                // find end of second number
                std::size_t end2 = t2.find_first_of(' ');
                // cast to double
                double y = std::stod(t2.substr(0, end2));
                t2 = t2.substr(end2);
                
                // find beginning of second number
                std::size_t start3 = t2.find_first_of("0123456789");
                // trim it down into temp
                std::string t3 = t2.substr(start3);
                // find end of second number
                std::size_t end3 = t3.find_first_of(' ');
                // cast to double
                double z = std::stod(t3.substr(0, end3));
                DataVector* vect = new DataVector();
                vect -> mData.push_back(x);
                vect -> mData.push_back(y);
                vect -> mData.push_back(z);
                vSet.push_back(vect);
            } // end inner if
        } // end while !eof()
    } // end is_open if
    
    else
    {
        std::cout << "File: " << file << " not open." << std::endl;
    }
}
