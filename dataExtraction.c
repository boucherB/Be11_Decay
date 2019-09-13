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

    fstream data(file);

    if(data.fail()){
        cout << "Chief we have a problem" << endl;
    }

    bool j = 0; //even, odd
    int line = 0; //iterator

    while(!data.eof()){

        double temp; //temp is temporary value
        data >> temp; //extract the data

        if(!j){
            dataVec.at(line).x = temp;
            cout << temp << " ";
            j = 1;
        }else{
            dataVec.at(line).y = temp;
            cout << temp << endl;
            j = 0;
            ++line;
        }

    }

    int maxIndex = 0;
    for(int i = 0; i < dataVec.size(); ++i){
      if(dataVec.at(maxIndex).x < dataVec.at(i).x){
        maxIndex = i;
      }
    }

    maxX = maxIndex;

    maxIndex = 0;
    for(int i = 0; i < dataVec.size(); ++i){
      if(dataVec.at(maxIndex).y < dataVec.at(i).y){
        maxIndex = i;
      }
    }
    maxY = maxIndex;

    int minIndex = 0;
    for(int i = 0; i < dataVec.size(); ++i){
        if(dataVec.at(minIndex).x > dataVec.at(i).x){
          maxIndex = i;
        }
    }
    minX = minIndex;
    minIndex = 0;
    for(int i = 0; i < dataVec.size(); ++i){
        if(dataVec.at(minIndex).y > dataVec.at(i).y){
          maxIndex = i;
        }
    }
    minY = minIndex;

}
