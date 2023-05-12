//
//  Implicant.hpp
//  Quinn
//
//  Created by Mahmoud Mohamed on 3/18/23.
//

#ifndef Implicant_hpp
#define Implicant_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
using namespace std;
class implicant{
public:
    string binaryRepresentation;
    string decimalRepresentation;
    string literalRepresentation;
    bool coveredByEPI=false;
    implicant();
    bool prime=true;
    int getNumberOfOnes();
    
    //Functions for newly created implicant by combining two implicants
    void concatenateDec(string dec1, string dec2);
    int canBeCombined(string bin);//returns -1 if the two binary codes cannot be combined and returns the index of the element that will be eliminated if they can be combined
    void updateLit();//Creates the literal representation from the binary representation
    void combineBin(string bin1, string bin2,int index);//combines the two implicants
    
};
#endif /* Implicant_hpp */
