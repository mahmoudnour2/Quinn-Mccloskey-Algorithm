//
//  main.cpp
//  Quinn
//
//  Created by Mahmoud Mohamed on 3/18/23.
//
//
//  main.cpp
//  QuinProject
//
//  Created by Mahmoud Mohamed on 3/15/23.
//
#include <iostream>
#include "Implicant.hpp"
#include "QmAlgo.hpp"
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include "BooleanFunc.hpp"
#include "TestCases.hpp"
using namespace std;
vector<implicant> constructMinterms(vector<string> binRepr,vector<string>decRepr);
vector<Boolean_Function> get_test_cases();
void get_ans(string& input, int& num);
int main() {
    cout<<"Test cases(1) OR Input SoP(2): ";
    int ans;
    cin>>ans;
    while(ans!=1 && ans!=2){
        cout<<"Try again "<<endl<<"Test cases(1) OR Input Sop(2): ";cin>>ans;
    }

    if(ans==2){//if the user wants to input a boolean expression
    int num;
    string input;
    get_ans(input,num);

    Boolean_Function function1(input, num);
    vector<string> binRepr=function1.getBinMinterms();
    vector<string> decRepr=function1.getdecMinterms();
    vector<implicant> minterms=constructMinterms(binRepr, decRepr);
    QmAlgorithm algo1;
    function1.Print_Truth_Trable();
    function1.Print_Canonical_SoP();
    function1.Print_Canonical_PoS();
    algo1.generateAlgo(minterms);
    algo1.print_algo();
    }


    else{//if the user wants to view the test cases
        vector<Boolean_Function> test_cases=get_test_cases();
        vector<QmAlgorithm> Algos;
        for(int i=0;i<test_cases.size();i++){//generates an adjacent vector of QmAlgorithms for every test case
            vector<string> binRepr=test_cases[i].getBinMinterms();
            vector<string> decRepr=test_cases[i].getdecMinterms();
            vector<implicant> minterms=constructMinterms(binRepr, decRepr);
            QmAlgorithm algo;
            algo.generateAlgo(minterms);
            Algos.push_back(algo);

        }
        for(int testnum=0;testnum<test_cases.size();testnum++){//Loops over the test cases and prints them
            cout<<"Test Case Number "<<testnum+1<<endl<<"Input: "<<test_cases[testnum].Get_Input()<<endl;
            test_cases[testnum].Print_Truth_Trable();
            test_cases[testnum].Print_Canonical_SoP();
            test_cases[testnum].Print_Canonical_PoS();
            Algos[testnum].print_algo();
            cout<<"--------------------------------------------------------------------"<<endl;
            cout<<endl<<endl;
        }

    }


}

//HELPER FUNCTIONS
vector<implicant> constructMinterms(vector<string> binRepr,vector<string>decRepr){
    vector<implicant> m;
    for(int i=0;i<binRepr.size();i++){
        implicant imp;
        imp.binaryRepresentation=binRepr[i];
        imp.decimalRepresentation=decRepr[i];
        m.push_back(imp);
    }
    return m;
}
void get_ans(string& Input, int& Num){

    int num = 0;
        cout << "Please enter the number of variables in your Boolean Function: ";
        cin >> num;

        string input;
        cout << "Please enter your Sum of Product Expression for a Boolean Function: ";
        cin >> input;
        cout << endl;

         while (Validate(input) == 0) {
             cout << "Wrong Input! Please try again!" << endl << endl;
             cout << "Please enter your Sum of Product Expression for a Boolean Function: ";
             cin >> input;
         }
        Input=input;
        Num=num;
}

