//
//  main.cpp
//  Tower of Hanoi Solver
//
//  Created by Zachary Hetrick on 8/31/15.
//  Copyright (c) 2015 Zetrick. All rights reserved.
//

#include <iostream>
#include <string>

const int numTowers = 3;//DO NOT CHANGE THIS
const char towerMaterial = '|';
const char ringMaterial = '#';
const char blankSpace = '.';


const int numRings = 3; //This can change

const int towerHeight = numRings + 2;
const int padding = 2;
const int biggestRing = numRings*2-1;

int funcCalls = 0;

std::string * ringLook;
std::string * towerLook;

enum whichTower
{
    TOWER_ONE = 0,
    TOWER_TWO = 1,
    TOWER_THREE = 2,
};

struct ring
{
    int size = 0;
};

struct tower
{
    int height = 0;
    ring * whichRing = NULL;
};

//Tower will look like this with 3 rings:
//.......................
//....|......|......|....
//....#......|......|....
//...###.....|......|....
//..#####....|......|....

//This function prints the towers
void printTowers(tower * theTowers)
{
    int modifier = 0;
    
    for(int i = 0; i < towerHeight; ++i)
    {
        //first print the blank top row and a new line
        if(i == 0)
        {
            for(int j = 0; j < (biggestRing * 3 + padding * 4); ++j)
                std::cout << blankSpace;
            
            std::cout << std::endl;
        }
        //Then print the top of the towers and a new line
        if(i == 1)
        {
            //padding - tower - padding - tower - padding - tower - padding
            std::cout << blankSpace << blankSpace;
            std::cout << *towerLook;
            std::cout << blankSpace << blankSpace;
            std::cout << *towerLook;
            std::cout << blankSpace << blankSpace;
            std::cout << *towerLook;
            std::cout << blankSpace << blankSpace;
            std::cout << std::endl;
        }
        //Then start printing the towers...
        
        if(i > 1)
        {
            //Start with padding, then start checking the tower heights.
            std::cout << blankSpace << blankSpace;
            
            //If the towerHeight is 3, print the 3rd element of whichRing
            //if the tower height is 2, print the 2nd element of whichRing
            //if tower height is 1, print the 1st element of whichRing
            if(theTowers[TOWER_ONE].height >= numRings - modifier)
            {
                std::cout << ringLook[(theTowers[TOWER_ONE].whichRing[numRings - modifier - 1].size) - 1];
            }
            else std::cout << *towerLook;
            std::cout << blankSpace << blankSpace;
            
            if(theTowers[TOWER_TWO].height >= numRings - modifier)
            {
                std::cout << ringLook[(theTowers[TOWER_TWO].whichRing[numRings - modifier - 1].size) - 1];
            }
            else std::cout << *towerLook;
            std::cout << blankSpace << blankSpace;
            
            if(theTowers[TOWER_THREE].height >= numRings - modifier)
            {
                std::cout << ringLook[(theTowers[TOWER_THREE].whichRing[numRings - modifier - 1].size) - 1];
            }
            else std::cout << *towerLook;
            std::cout << blankSpace << blankSpace;
            
            ++modifier;
            std::cout << std::endl;
        }
    }
    
}

//Put all rings into the first tower. In a normal game it will initialize as 3, 2, 1
//Whenever a ring changes towers, it must be added to the new towers' whichRing array in order
//Then the height of the tower must increase by one, while the height of the previous tower decreases by one and the
//Ring deleted (zeroed out) from the top of the previous tower.
tower * initializeTower(tower* theTowers)
{
    //Initialize ring size on each ring in the first tower
    for(int i = 0; i < numRings; ++i)
    {
        theTowers[TOWER_ONE].whichRing[i].size = numRings - i;
    }
    
    //Set tower one as having all of the rings
    theTowers[TOWER_ONE].height = numRings;
    return theTowers;
}

//This function creates the three towers
tower * makeTowers(int rings)
{
    //Create the array of towers. This will always make 3 towers.
    //The tower default height = 0
    tower * theTowers = new tower[numTowers];
    
    //Fill the towers whichRing variable with an array of the number of rings
    //In a normal game, this is giving each tower 3 rings in their whichRing array.
    //the rings are default size of 0, aka, there is no ring there at all
    //ring size 1 in a normal game: ..#..
    //ring size 2 in a normal game: .###.
    //ring size 3 in a normal game: #####
    theTowers[TOWER_ONE].whichRing = new ring[numRings];
    theTowers[TOWER_TWO].whichRing = new ring[numRings];
    theTowers[TOWER_THREE].whichRing = new ring[numRings];
    
    //Put the rings on the first tower
    theTowers = initializeTower(theTowers);
    
    return theTowers;
}

//This function sets up the way n number rings look
std::string * makeRingDisplays(std::string * ringLooks)
{
    int originalAmount = 1;
    int amountOfRingMaterial = originalAmount;
    
    //Make the rings
    for(int i = 0; i < numRings; ++i)
    {
        ringLooks = new std::string[numRings];
    }
    
    for(int i = 0; i < numRings; ++i)
    {
        for(int j = 0; j < ((biggestRing - amountOfRingMaterial)/2); ++j)
        {
            ringLooks[i] += blankSpace;
        }
        
        for(int j = 0; j < amountOfRingMaterial; ++j)
        {
            ringLooks[i] += ringMaterial;
        }
        
        for(int j = 0; j < ((biggestRing - amountOfRingMaterial)/2); ++j)
        {
            ringLooks[i] += blankSpace;
        }
        
        amountOfRingMaterial = originalAmount + 2;
        originalAmount += 2;
    }
    return ringLooks;
}

//This function sets up the way an empty tower looks
std::string * makeTowerDisplay(std::string * towerLook)
{
    //Make the tower string
    for(int i = 0; i < numRings; ++i)
    {
        towerLook = new std::string;
    }
    
        for(int j = 0; j < ((biggestRing - 1)/2); ++j)
        {
            towerLook[0] += blankSpace;
        }
    
            towerLook[0] += towerMaterial;
        
        for(int j = 0; j < ((biggestRing - 1)/2); ++j)
        {
            towerLook[0] += blankSpace;
        }
    
    return towerLook;
}

//Move a ring from source tower to destination tower. This function also prevents illegal moves
tower * moveRing(tower * theTowers, whichTower currentTower, whichTower destinationTower)
{
    ring foundRing;
    int indexOfRingBeforeMove = 0; //This variable will help us reset things if an illegal move is tried.
    
    //This search starts at the top ring (the back of the array) and works its way backward to the bottom (front of the array)
    //as soon as it finds a ring, it moves it to the first open spot (closest to front of array) of the destination tower.
    for(int i = numRings-1; i >= 0; --i)
    {
        if(theTowers[currentTower].whichRing[i].size > 0) // if this is true, we've found a ring.
                                                          //Copy which ring it is and delete from this tower
        {
            indexOfRingBeforeMove = i;
            foundRing = theTowers[currentTower].whichRing[i];
            theTowers[currentTower].whichRing[i].size = 0; // zero out the size of this ring
            --theTowers[currentTower].height; // reduce the height of the tower by one
            break; // This will break out of the loop could also use "break;" I think...
        }
    }
    
    //If a ring was found
    if(foundRing.size > 0)
    {
        //Find the location in the destination tower to copy the ring
        for(int i = 0; i < numRings; ++i)
        {
            //If there is a ring, move to the next array element (moving up the tower) to check for another
            if(theTowers[destinationTower].whichRing[i].size > 0)
            {
                //if we come across a ring SMALLER than the foundRing.size, then undo the delete and do not change the tower since this is an illegal move.
                if(theTowers[destinationTower].whichRing[i].size < foundRing.size)
                {
                    ++theTowers[currentTower].height; // Increase the previous towers' height
                    theTowers[currentTower].whichRing[indexOfRingBeforeMove].size = foundRing.size; // Reset the previous towers ring
                    break; //leave the loop and return
                }
                
                continue; //Otherwise, continue searching
            }
            //If we hit the else, we have found a legal place the ring can go. Place it and increase the tower height by 1.
            else
            {
                theTowers[destinationTower].whichRing[i].size = foundRing.size;
                ++theTowers[destinationTower].height; // Increase the height of the destination tower by one
                break;
            }
        }
    }
    return theTowers;
}

//This is the part I'm having trouble with...
//This is the recursive function to solve the tower
//I've tried implementing it multiple times, but can't seem to get
//it right so i've just deleted it all for now.
void solveHanoi()
{
    //?????????
    return;
}

void wait()
{
    std::cin.sync();
    std::cin.get();
}
int main()
{
    //Make the three towers
    tower * theTowers = makeTowers(numRings);
    
    //Make the ring and tower displays
    ringLook = makeRingDisplays(ringLook);
    towerLook = makeTowerDisplay(towerLook);
    
    printTowers(theTowers);
    wait();
    
    //THIS IS THE HARD CODED WAY OF HOW TO SOLVE THIS PROBLEM WITH 3 RINGS
    //I'm supposed to make a recursive function to solve the problem with n number of rings
    //But I can't seem to understand how to implement it...
    
    moveRing(theTowers, TOWER_ONE, TOWER_THREE);
    printTowers(theTowers);
    wait();
    moveRing(theTowers, TOWER_ONE, TOWER_TWO);
    printTowers(theTowers);
    wait();
    moveRing(theTowers, TOWER_THREE, TOWER_TWO);
    printTowers(theTowers);
    wait();
    moveRing(theTowers, TOWER_ONE, TOWER_THREE);
    printTowers(theTowers);
    wait();
    moveRing(theTowers, TOWER_TWO, TOWER_ONE);
    printTowers(theTowers);
    wait();
    moveRing(theTowers, TOWER_TWO, TOWER_THREE);
    printTowers(theTowers);
    wait();
    moveRing(theTowers, TOWER_ONE, TOWER_THREE);
    printTowers(theTowers);

    //Now for the recursion part...  This is confusing me!
    solveHanoi();
    
    return 0;
}