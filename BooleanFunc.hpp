//
//  BooleanFunc.hpp
//  Quinn
//
//  Created by Mahmoud Mohamed on 3/19/23.
//

#ifndef BooleanFunc_hpp
#define BooleanFunc_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool Validate(string input);
int BinarytoDecimal(char binary[],int len, int i=0);
class Boolean_Function
{
    
private:
    
    int number_of_variables;
    string myInput;
    vector<char> variables;
    vector<vector<int>> Binary_Rep;
    vector<string> Binary_Rep1;
    vector<vector<int>> Truth_Table;
    vector<string> minterms;
    string canonical_SoP;
    string canonical_PoS;
    

public:
    vector<string> getBinMinterms();
    vector<string> getdecMinterms();
    Boolean_Function(string input, int num);

    string Binary_Sum(string num1, string num2);
    void Generate_Truth_Table();
    void Print_Truth_Trable();
    
    void Identify_Minterms();
    void Print_Minterms();

    void Identify_Variables();
    void Print_Variables();

    void Generate_Binary_Rep();

    void Generate_Final_Truth_Table();


    void Generate_Canonical_SoP();
    void Print_Canonical_SoP();
    
    string Get_Input();


    void Generate_Canonical_PoS();
    void Print_Canonical_PoS();

    vector<char> Get_Variables();

};
#endif /* BooleanFunc_hpp */
