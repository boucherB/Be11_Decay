//
// Created by brandon on 8/29/19.
//

#include "dataExtraction.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void dataExtraction(string file, vector<xy>& dataVec){

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
            j = 1;
        }else{
            dataVec.at(line).y = temp;
            j = 0;
            ++line;
        }

    }


}