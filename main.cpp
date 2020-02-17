#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std; 

#include "prototypes.h" //FIXME
#include "functions.cpp"

/*
-Purpose: 
		Things have different heights. We need to take this into account.
		Thus, at the end of the point placing process but before the writing process,
		There must be a function that scrubs through the list of waypoints, recognizes
		which are mandatory and which are points in between, and attempts to make the
		waypoint heights be evenly distributed.
-Process:
		Mandatory waypoint found
		Keep track of which are the points in between it and the next mandatory waypoint
		Find the heigh difference between the two key points
		Divide it by the number of points
		Assign incrementally increasing height to the points in the middle, then repeat
	
-Requirements
		Takes in a vector(?), determines what points are critical/mandatory, determines
		How many points are in the middle, subtracts height to get height difference, 
		Divides height difference to get even increases.
*/
//MAKE A GOOGLE DOC ABOUT YOUR TEST HARNESS
//MAKE A LOG
//IF ERROR, SET TO 200 ft, IF NEGATIVE HEIGHT, no, set to 200
void calculate(vector<point>& points);
void readData(const string &inp, vector<point>& points);
int findCP(const vector<point>& points, unsigned index);
bool isAscending(const vector<point>& points, unsigned startIndex, unsigned endIndex);

int main()
{
    cout << "Testing Function: " << endl; 
    cout << endl; 

    //three points, ascending order, CP is last point
    //don't declare a size yet, you're going to be ending up filling it with garbage values
    vector<point> test1; 
    cout << "Testing a set of 3 points, in ascending order: "<<endl; 
    point temp = point();  
    temp.height = 200; 
    temp.crit = true; 
    point temp1 = point();  
    temp1.height = 200; 
    point temp2 = point();  
    temp2.height = 400; 
    temp2.crit = true; 
    test1.push_back(temp); //ask about height
    test1.push_back(temp1);
    test1.push_back(temp2);
    for(int i = 0; i < test1.size(); i++)
    {
        cout<<test1.at(i).height << " ";
    }
    calculate(test1); 
    cout << endl; 
    for(int i = 0; i < test1.size(); i++)
    {
        cout<<test1.at(i).height << " ";
    }
    cout << endl;  
    //cout << "Supposed to be: 266.666, " << endl; 
    //cout << endl; 
    //cout.flush(); 

    //three points, descending  order, CP is last point
    vector<point> test2; 
    cout << "\nTesting a set of 3 points, in descending order: "<<endl; 
    point Temp = point();  
    Temp.height = 400; 
    Temp.crit = true; 
    point Temp1 = point();  
    Temp1.height = 200; 
    point Temp2 = point();  
    Temp2.height = 200; 
    Temp2.crit = true; 
    test2.push_back(Temp); //ask about height
    test2.push_back(Temp1);
    test2.push_back(Temp2);
    for(int i = 0; i < test2.size(); i++)
    {
        cout<<test2.at(i).height << " ";
    }
    cout << endl; 
    calculate(test2); 
    for(int i = 0; i < test2.size(); i++)
    {
        cout<<test2.at(i).height << " ";
    }
    cout << endl; 
    //cout << endl;

    //three points, all negative
    /*vector<point> test3; 
    cout << "\nTesting a set of 3 points, all negative"<<endl; 
    point TTemp = point();  
    TTemp.height = -400; 
    point TTemp1 = point();  
    TTemp1.height = -200; 
    point TTemp2 = point();  
    TTemp2.height = -200; 
    test3.push_back(TTemp); //ask about height
    test3.push_back(TTemp1);
    test3.push_back(TTemp2);
    for(int i = 0; i < test3.size(); i++)
    {
        cout<<test3.at(i).height << " ";
    }
    cout << endl; 
    calculate(test3); 
    for(int i = 0; i < test3.size(); i++)
    {
        cout<<test3.at(i).height << " ";
    }
    cout << endl; */
    //cout << endl;

    vector<point> test4; 
    cout << "\nTesting a set of 4 points, in ascending order: "<<endl; 
    point TTTemp = point();
    TTTemp.height = 200; 
    TTTemp.crit = true; 
    point TTTemp1 = point();  
    TTTemp1.height = 200; 
    point TTTemp2 = point();  
    TTTemp2.height = 200; 
    point TTTemp3 = point();  
    TTTemp3.height = 400; 
    TTTemp3.crit = true; 
    test4.push_back(TTTemp); //ask about height
    test4.push_back(TTTemp1);
    test4.push_back(TTTemp2);
    test4.push_back(TTTemp3);
    for(int i = 0; i < test4.size(); i++)
    {
        cout<<test4.at(i).height << " ";
    }
    cout << endl; 
    calculate(test4); 
    for(int i = 0; i < test4.size(); i++)
    {
        cout<<test4.at(i).height << " ";
    }
    cout << endl; 
    
    vector<point> test5; 
    cout << "\nTesting a set of 5 points, in ascending order: "<<endl; 
    point TTTTemp = point();  
    TTTTemp.height = 2000; 
    TTTTemp.crit = true; 
    point TTTTemp1 = point();  
    TTTTemp1.height = -2000; 
    point TTTTemp2 = point();  
    TTTTemp2.height = -2000; 
    point tTTTTemp2 = point();  
    tTTTTemp2.height = -2000; 
    point TTTTemp3 = point();  
    TTTTemp3.height = 4000; 
    TTTTemp3.crit = true; 
    test5.push_back(TTTTemp); //ask about height
    test5.push_back(TTTTemp1);
    test5.push_back(TTTTemp2);
    test5.push_back(tTTTTemp2);
    test5.push_back(TTTTemp3);
    for(int i = 0; i < test5.size(); i++)
    {
        cout<<test5.at(i).height << " ";
    }
    cout << endl; 
    calculate(test5); 
    for(int i = 0; i < test5.size(); i++)
    {
        cout<<test5.at(i).height << " ";
    }
    cout << endl; 


}

/*CALCULATES deltaH AND ADDS TO EACH POINT
* Works with findCP function
*/
//list use when you have items, 
//front, back middle end for lists, list doesnt have everything stored in order 
// linked with pointers 
// IF NOT A CRITICAL, HEIGHT = 200
void calculate(vector<point>& points)
{
        //(abs(deltaH)/n+1), n being number of points, h being change in height;
        int index1 =  findCP(points, 0);
        int index2 = findCP(points, 1);
        int incrementScalarP = 1; 
        int incrementScalarN = points.size() - 2; 

        for(int i = index1 + 1; i < index2; i++)
        {
            if(points.at(i).height < 0)
            {   
                cout << "Error, passing in negative height."<< endl; 
                cout << "Changing height to positive..."<< endl; 
                points.at(i).height = points.at(i).height * -1; 
                cout << points.at(i).height<<endl; 
            }
            double deltaH = abs(points.at(index1).height - points.at(index2).height); 
            double increment = (deltaH)/(points.size());
            if(points.at(index1).height < points.at(index2).height)
            {
                points.at(i).height += incrementScalarP * increment;
                incrementScalarP++;  
            }
            else 
            {
                points.at(i).height += incrementScalarN * increment; 
                incrementScalarN--; 
            }
        }
        
    
}

/* FINDS CRITICAL POINT
* Returns index of first found CP, starting from index given 
*/
//FIX ME: if it doesnt find a CP, return -1
int findCP(const vector<point>& points, unsigned index)
{
    for(int i = index; i < points.size(); i++){
        if(points.at(i).crit)
        {
            return i; 
        }
    }
    return -1;
}

/*
* CHECKS IF POINTS ARE POSITIVE OR NEGATIVE
* ..how do I check orientation of points?? you will have to check the height
*/
/*bool isAscending(const vector<point>& points, unsigned startIndex, unsigned endIndex)
{
    for(unsigned int i = startIndex; i < endIndex; i++)
    {
        double temp = points.at(startIndex).height; 
        if(temp > points.at(i).height){
            return false; 
        }
    }
    return true; 
}*/
