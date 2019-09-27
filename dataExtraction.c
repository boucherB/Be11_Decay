//
// Created by brandon on 8/29/19.
//

#include "dataExtraction.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void dataExtraction(string file, vector<xy>& dataVec, int& maxX, int& maxY, int& minX, int& minY){

    fstream data(file); //input stream

    if(data.fail()){ //checks if it fails
        cout << "Chief we have a problem" << endl;
    }

    bool j = 0; //even, odd
    int line = 0; //iterator

    while(!data.eof()){ //while not at the end of the file

        double temp; //temp is temporary value
        data >> temp; //extract the data

        if(!j){
            dataVec.at(line).x = temp;
            j = 1;
        }else{
            dataVec.at(line).y = temp;
            j = 0;
            ++line;
        }

    }

    //checking for the maximum and minimum values for x and y
    int maxIndex = 0;
    for(int i = 0; i < dataVec.size(); ++i){
      if(dataVec.at(maxIndex).x < dataVec.at(i).x){ //determining the max of x
        maxIndex = i;
      }
    }

    maxX = maxIndex; //setting the max index

    maxIndex = 0;
    for(int i = 0; i < dataVec.size(); ++i){
      if(dataVec.at(maxIndex).y < dataVec.at(i).y){ //max of y
        maxIndex = i;
      }
    }
    maxY = maxIndex;

    int minIndex = 0;
    for(int i = 0; i < dataVec.size(); ++i){
        if(dataVec.at(minIndex).x > dataVec.at(i).x){ //determining the minimum of x
          maxIndex = i;
        }
    }
    minX = minIndex; //setting the minimum of x

    minIndex = 0;
    for(int i = 0; i < dataVec.size(); ++i){
        if(dataVec.at(minIndex).y > dataVec.at(i).y){ //min of y
          maxIndex = i;
        }
    }
    minY = minIndex;

}
