//
//  Centroid.cpp
//  K Means
//
//  Created by O Bashaw on 6/10/19.
//  Copyright © 2019 O Bashaw. All rights reserved.
//

#include "Centroid.h"

// Function: Centroid
// Purpose: default constructor
// Returns: new centroid
Centroid::Centroid()
{
    mLoc.push_back(0);
    mLoc.push_back(0);
}

// Function: Centroid
// Purpose: parameterized constructor
// Returns: new centroid with mLoc set to random location in dimension (take average location of 3 random vectors)
Centroid::Centroid(const unsigned DIM, std::vector<DataVector*> vSet)
{
    // for randomization
    //std::srand(std::time(nullptr));
    
    // repeat this process for each dimension
    for (unsigned i = 0; i < DIM; i++)
    {
        // double to store average
        double x = 0.0;
        
        // repeat 3 times...
        for (unsigned j = 0; j < RAND_LOC_INDEX; j++)
        {
            // add the ith location element of a random vector in vSet to x
            x += vSet[std::rand() % (vSet.size() - 1)] -> mData[i];
        }
        
        // divide by 3
        x = x/RAND_LOC_INDEX;
        
        // add x to mLoc
        mLoc.push_back(x);
    }
}

// Function: Centroid
// Purpose: parameterized constructor
// Returns: new centroid with mLoc set to desired location in 2-D
Centroid::Centroid(const double xLoc, const double yLoc)
{
    mLoc.push_back(xLoc);
    mLoc.push_back(yLoc);
}

// Function: ~Centroid
// Purpose: destructor
// Returns: none
Centroid::~Centroid()
{
    // go through mMembers and delete all DataVector*
    for (DataVector* v : mMembers)
    {
        v -> mData.clear();
        v -> cParent = nullptr;
        delete v;
        v = nullptr;
    }
}

// Function: addMember
// Purpose: adds DataVector* to mMembers
// Returns: none
void Centroid::addMember(DataVector* toAdd)
{
    // add DataVector* to mMembers
    mMembers.push_back(toAdd);
    
    toAdd -> cParent = this;
}

// Function: switchMembership
// Purpose: move a DataVector from one centroid to another
// Returns: none
void Centroid::switchMembership(DataVector* vect, Centroid* newParent)
{
    // get iterator to the vector we want to swap
    auto i = std::find(mMembers.begin(), mMembers.end(), vect);
    
    // remove it from the current parent Centroid
    mMembers.erase(i);
    
    // add it to the new parent Centroid
    newParent -> addMember(vect);
}


// Function: recalcLoc
// Purpose: recalculate mLoc based on mMembers
// Returns: bool that tells whether mLoc changed after call to function
bool Centroid::recalcLoc()
{
    bool changed = false;
   // std::vector<double> newLoc;
    
    // compute
    for (unsigned i = 0; i < 2; i++)
    {
        double total = 0.0;
        
        // find average for ith dimension, to be used as new i coordinate in mLoc
        for (unsigned j = 0; j < mMembers.size(); j++)
        {
            // gather ith piece of mData from each DataVector in mMembers
            total += mMembers[j] -> mData[i];
        }
        // divide total by the number of DataVectors in mMembers
        total /= mMembers.size();
        
        // if mLoc has changed, update bool and ith dimensional coordinate
        if (total != mLoc[i])
        {
            changed = true;
            mLoc[i] = total;
        }
        // otherwise, ensure that changed is set to false
        else
        {
            changed = false;
        }
    }
    // We can just use one bool for this because of the iterative nature of the above computations
    // That is, a change in the double for ANY element in mLoc will set changed to true
    return changed;
}

// Function: displayMembers
// Purpose: display DataVector in mMembers
// Returns: none
void Centroid::displayMembers()
{
    //std::cout << "mLoc: " << getLoc() << std::endl;
    for (auto i : mMembers)
    {
        std::cout << "\t" << i << std::endl;
    }
}

// Function: getLoc
// Purpose: get mLoc in a string
// Returns: string with coordinates of Centroid
std::string Centroid::getLoc()
{
    std::string loc = "( ";
    for (unsigned i = 0; i < mLoc.size(); i++)
    {
        if (i == mLoc.size() - 1)
        {
            loc += std::to_string(mLoc[i]);
            loc += " ";
        }
        else
        {
            loc += std::to_string(mLoc[i]);
            loc += ", ";
        }
    }
    loc += ")";
    return loc;
}


