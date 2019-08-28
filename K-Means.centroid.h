//
//  Centroid.h
//  K Means
//
//  Created by O Bashaw on 6/10/19.
//  Copyright © 2019 O Bashaw. All rights reserved.
//

#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
class Centroid;
const int RAND_LOC_INDEX = 3;

// Struct DataVector that holds one data point
struct DataVector
{
    // use vector so that we can operate in 2D, 3D, 4D ...
    std::vector<double> mData;
    // Pointer to Centroid that this DataVector is closest to aka "Parent"
    Centroid* cParent;
};


class Centroid
{
public:
    // Function: Centroid
    // Purpose: default constructor
    // Returns: new centroid
    Centroid();
    
    // Function: Centroid
    // Purpose: parameterized constructor
    // Returns: new centroid with mLoc set to average location of 3 data vectors from set
    Centroid(const unsigned DIM, std::vector<DataVector*> vSet);
    
    // Function: Centroid
    // Purpose: parameterized constructor
    // Returns: new centroid with mLoc set to desired location in 2-D
    Centroid(const double xLoc, const double yLoc);
    
    // Function: ~Centroid
    // Purpose: destructor
    // Returns: none
    ~Centroid();
    
    // Function: addMember
    // Purpose: adds DataVector* to mMembers
    // Returns: none
    void addMember(DataVector* toAdd);

    // Function: switchMembership
    // Purpose: move a DataVector from one centroid to another
    // Returns: none
    void switchMembership(DataVector* vect, Centroid* newParent);
    
    // Function: recalcLoc
    // Purpose: recalculate mLoc based on mMembers
    // Returns: bool that tells whether mLoc changed after call to function
    bool recalcLoc();
    
    // Function: getLocElement
    // Purpose: get desired element of mLoc
    // Returns: double with mLoc[i]
    double getLocElement(unsigned i)
    {
        return mLoc[i];
    }
    
    // Function: getLocElement
    // Purpose: get desired element of mLoc
    // Returns: double with mLoc[i]
    unsigned getMemberSize()
    {
        return mMembers.size(); 
    }
    
    // Function: displayMembers
    // Purpose: display DataVectors in mMembers
    // Returns: none
    void displayMembers();
    
    // Function: getLoc
    // Purpose: display mLoc
    // Returns: string with coordinates of Centroid
    std::string getLoc();
private:
    std::vector<double> mLoc;
    std::vector<DataVector*> mMembers;
};
