//
//  QmAlgo.hpp
//  Quinn
//
//  Created by Mahmoud Mohamed on 3/18/23.
//

#ifndef QmAlgo_hpp
#define QmAlgo_hpp

#include <stdio.h>
#include "Implicant.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
using namespace std;
class QmAlgorithm{
public:
    void generateAlgo(vector<implicant> mintermsVect);
    void print_algo();
private:
    vector<vector<implicant>> implicantTable;
    vector<implicant> primeImplicants;
    vector<implicant> EPIs;
    vector<implicant> minterms;
    vector<vector<int>> coverageChart;
    map<string,int> mapp;
    vector<int> indicesOfMinimalPIs;
    void generateImplicantTable();
    void storePrimeImplicants();
    void storeEPIs();
    void generateMap();
    void updateMintermsCoveredState();
    void storeLitForMinterms();
    void printPrimeImplicants();
    void printEPIs();
    void printMintermsNotCoveredbyEPIs();
    void printCoverage();
    void print_minimized();
    void minimalExpression();
    int getDominatingRows(int r1, int r2);
    int getDominatedCols(int c1, int c2);
    void fixCoverageChart();
    bool mintermsExhausted();
    
};

#endif /* QmAlgo_hpp */
