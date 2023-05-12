//
//  QmAlgo.cpp
//  Quinn
//
//  Created by Mahmoud Mohamed on 3/18/23.
//

#include "QmAlgo.hpp"

bool singular(string s);

void QmAlgorithm::generateAlgo(vector<implicant> mintermsVect){
    this->minterms=mintermsVect;
    generateMap();
    storeLitForMinterms();
    generateImplicantTable();
    storePrimeImplicants();
    storeEPIs();
    updateMintermsCoveredState();
    fixCoverageChart();
    minimalExpression();
}
//PRINTING FUNCTIONS
void QmAlgorithm::printPrimeImplicants(){
    cout<<endl<<"Prime Implicants: "<<endl;
    for(int i=0;i<primeImplicants.size();i++){
        cout<<primeImplicants[i].binaryRepresentation<<endl;
    }
}
void QmAlgorithm::storeLitForMinterms(){
    for(int i=0;i<minterms.size();i++){
        minterms[i].updateLit();
    }
}
void QmAlgorithm::printEPIs(){
    cout<<endl<<"Essential Prime Implicants: "<<endl;
    for(int i=0;i<EPIs.size();i++){
//        EPIs[i].updateLit();
        cout<<EPIs[i].literalRepresentation<<endl;
    }
}
void QmAlgorithm::printMintermsNotCoveredbyEPIs(){
        cout<<endl<<"Minterms not covered by EPIs: "<<endl;
        for(int i=0;i<minterms.size();i++){
            if(minterms[i].coveredByEPI==false){
                cout<<minterms[i].decimalRepresentation<<endl;
            }
        }
}
void QmAlgorithm::print_minimized(){
    cout<<"Minimized Logic Expression is: "<<endl;
    int idx1=indicesOfMinimalPIs[0];
    cout<<primeImplicants[idx1].literalRepresentation;
    for(int i=1;i<indicesOfMinimalPIs.size();i++){
        cout<<"+";
        int idx=indicesOfMinimalPIs[i];
        cout<<primeImplicants[idx].literalRepresentation;
    }
    cout<<endl;
}
void QmAlgorithm::printCoverage(){
    cout<<"Coverage Chart:"<<endl;
    cout<<endl;
    for(int i=0;i<coverageChart.size();i++){
        int k=i-1;
        if(i>0){
            cout<<minterms[k].decimalRepresentation<<"-    ";
        }
        else{
            cout<<0<<"-    ";
        }
        for(int j=0;j<coverageChart[i].size();j++){
            
            cout<<coverageChart[i][j]<<"      ";
        }
        cout<<endl;
    }
}
void QmAlgorithm::print_algo(){
    printPrimeImplicants();
    printEPIs();
    printMintermsNotCoveredbyEPIs();
    cout<<endl;
    print_minimized();
//    printCoverage();
    
}
//END OF PRINTING FUNCTIONS
void QmAlgorithm::fixCoverageChart(){
    //add a row of a value other than -1 in the beginning of the 2D vector, as well as a column
    vector<int> ColsConditions(coverageChart[0].size(),5);
    coverageChart.insert(coverageChart.begin(), ColsConditions);
    for(int i=0;i<coverageChart.size();i++){
        coverageChart[i].insert(coverageChart[i].begin(), 5);
    }
}
void QmAlgorithm::storePrimeImplicants(){
    for(int i=0;i<implicantTable.size();i++){//loop over every column
        for(int j=0;j<implicantTable[i].size();j++){//loop over every implicant in every column
            if(implicantTable[i][j].prime==true){
                primeImplicants.push_back(implicantTable[i][j]);
            }
        }
    }
}

void QmAlgorithm::storeEPIs(){//uses the decimal representation of the prime implicants and minterms to pick the essential prime implicants (by checking if the minterm decimal value is a substring of the prime implicant decimal representation, i.e., if the prime implicant covers the minterm)
    for(int i=0;i<minterms.size();i++){
        //loop over each minterm
        vector<int> col;
        int P=0;//Number of prime implicants that cover the minterm i
        int s=0;//index of Essential prime implicant if present
        for(int j=0;j<primeImplicants.size();j++){ //then loop over the prime implicants to check how many prime implicants cover this minterm, if one, then push it to the vector EPIs
                string s1=primeImplicants[j].decimalRepresentation;
                string s2=minterms[i].decimalRepresentation;
            if(singular(s2)){
                istringstream ss(s1);
                string token;
                bool present=false;
                while(getline(ss, token, ',')){
                    if (s2==token){
                        present=true;
                        P++;
                        s=j;
                        col.push_back(1);
                    }
                    
                }
                if(present==false){
                        col.push_back(0);
                }
            }
            else{
            if (s1.find(s2) != string::npos) {//if the minterm decimal value is a substring of the prime implicant decimal representation, i.e., if the prime implicant covers the minterm
                    P++;
                    s=j;//save the index of the prime implicant in case we find that it's essential
                col.push_back(1);
                }
            else{
                col.push_back(0);
            }
            }
        }
        if (P==1){//if only one prime implicant covers the minterm
            //check uniqueness(compare with already added EPIs, and that is because an EPI can be essential to more than one minterm)
            bool unique=true;
            for(int i=0;i<EPIs.size();i++){
                if(EPIs[i].literalRepresentation==primeImplicants[s].literalRepresentation){
                    unique=false;
                }
            }
            if(unique==true){
            EPIs.push_back(primeImplicants[s]);
            }
        }
        coverageChart.push_back(col);
    }
    
}

void QmAlgorithm::updateMintermsCoveredState(){
    for(int i=0;i<EPIs.size();i++){
        string decReprEPI=EPIs[i].decimalRepresentation;
        istringstream ss(decReprEPI);
        string decValue;
        while(getline(ss, decValue, ',')){
            int index=mapp[decValue];
            minterms[index].coveredByEPI=true;
        }
    }
}//This function uses the decimal representation of the EPI to mark the covered minterms

void QmAlgorithm::generateImplicantTable(){
    implicantTable.push_back(minterms);
    int k=0;
    int times=0;
    while(!implicantTable[k].empty()){//Loop until we face a column with no elements
        //k represents column number
        times++;
        vector<implicant> newImplicants;//the vector of the next column
        int numberOfDigits=minterms[0].binaryRepresentation.size();
    vector<vector<int>> NoOfOnes(numberOfDigits+1);//NoOfOnes vector-->row 0 has the indexes of implicants with 0 1's, row  1 has the indexes of implicants with 1 1's, etc...
    for(int i=0;i<implicantTable[k].size();i++){//Loop over the column to fill the NoOfOnes vector
        int num=implicantTable[k][i].getNumberOfOnes();
        NoOfOnes[num].push_back(i);
    }
        int row=0;
        while(row<minterms[0].binaryRepresentation.size()){//loop over all the ROWS of the NoOfOnes vector, i.e. so as to compare each group of implicants(grouped according to number of ones) and compare each element in it with the elements of the next group to find a possible combination
            for(int i=0;i<NoOfOnes[row].size();i++){//loop over the first row
                int impIndex=NoOfOnes[row][i];
                implicant imp=implicantTable[k][impIndex];
                for(int j=0;j<NoOfOnes[row+1].size();j++){//loop over the row after to see a possible combination
                    int imp2Index=NoOfOnes[row+1][j];
                    string binRepr1=imp.binaryRepresentation;
                    string binRepr2=implicantTable[k][imp2Index].binaryRepresentation;
                    int answer=imp.canBeCombined(binRepr2);
                    if(answer!=-1){//if the two implicants can be combined, then combine and create the new implicant
                        implicant newImp;
                        newImp.combineBin(binRepr1, binRepr2, answer);//answer is the index of the element that will be eliminated
                        string newBinRepr=newImp.binaryRepresentation;
                        bool unique=true;//Testing the uniqueness of the binary representation of the implicant
                        for(int m=0;m<newImplicants.size();m++){//comparing it with the binary representations of the already added implicants in the vector of the next column
                            if(newBinRepr==newImplicants[m].binaryRepresentation){
                                unique=false;
                            }
                        }
                        if(unique==true){
                        string decRepr1=implicantTable[k][impIndex].decimalRepresentation;
                        string decRepr2=implicantTable[k][imp2Index].decimalRepresentation;
                        newImp.concatenateDec(decRepr1, decRepr2);
                        newImp.updateLit();
                        newImplicants.push_back(newImp);
                        }
                        implicantTable[k][impIndex].prime=false;
                        implicantTable[k][imp2Index].prime=false;
                        //this is set out of the condition because starting from the second column you can reach the same binary representation using different implicants
                        //as an example in the slides, slide 28, 01-- can be reached from the second column using (4,5)+(6,7) or (4,6)+(5,7), they both lead to 4,5,6,7
                    }
                }
            }
            row++;
        }
        implicantTable.push_back(newImplicants);
        k++;
        
    }
}
int QmAlgorithm::getDominatingRows(int r1, int r2){
    bool r1dominating=true;
    bool r2dominating=true;
    for(int i=1;i<coverageChart[r1].size();i++){
        if(coverageChart[r1][i]==1 ||coverageChart[r2][i]==1){
            if(coverageChart[r1][i]==1 && coverageChart[r2][i]!=1){
                r2dominating=false;
            }
            else if(coverageChart[r1][i]!=1 && coverageChart[r2][i]==1){
                r1dominating=false;
            }
        }
    }
    if(r1dominating==true){
        return 1;
    }
    else if(r2dominating==true){
        return 2;
    }
    else if(r1dominating==true && r2dominating==true){
        return 3;
    }
    else{
        return -1;
    }
}
int QmAlgorithm::getDominatedCols( int c1, int c2){
    bool c1dominating=true;
    bool c2dominating=true;
    for(int i=1;i<coverageChart.size();i++){
        if(coverageChart[i][c1]==1 ||coverageChart[i][c2]==1){
            if(coverageChart[i][c1]==1 && coverageChart[i][c2]!=1){
                c2dominating=false;
            }
            else if(coverageChart[i][c1]!=1 && coverageChart[i][c2]==1){
                c1dominating=false;
            }
        }
    }
    if(c1dominating==true){
        return 2;
    }
    else if (c2dominating==true){
        return 1;
    }
    else{
        return -1;
    }
}
void QmAlgorithm::minimalExpression(){
    int changeOccured=1;
    while(changeOccured==1){
        changeOccured=0;
    for(int i=1;i<coverageChart.size();i++){//looping over the rows (minterms)
        int primeThatCoverIt=0;
        int indexOfPrime=-1;
        for(int j=1;j<coverageChart[0].size();j++){//loop over the columns(prime implicants)
            if(coverageChart[i][0]!=-1 && coverageChart[0][j]!=-1){//if neither are excluded
                if(coverageChart[i][j]==1){
                    primeThatCoverIt++;
                    indexOfPrime=j;
                }
            }
        }
        if(primeThatCoverIt==1){//if it's covered by an EPI in col j
            //remove col j
            
            coverageChart[0][indexOfPrime]=-1;
            indicesOfMinimalPIs.push_back(indexOfPrime-1);
            changeOccured=1;
            
            //remove the minterms covered by EPI in col j
            for(int k=1;k<coverageChart.size();k++){
                if(coverageChart[k][indexOfPrime]==1){
                    coverageChart[k][0]=-1;
                }
            }
            
        }
    }
        
       //Remove dominating rows
       
        for(int i=1;i<coverageChart.size();i++){
            for(int j=1;j<coverageChart.size();j++){
                if(i==j){
                    continue;
                }
                if(coverageChart[i][0]==-1 || coverageChart[j][0]==-1){
                    continue;
                }
                int r1=i;
                int r2=j;
                bool r1dominating=true;
                bool r2dominating=true;
                for(int i=1;i<coverageChart[r1].size();i++){
                    if(coverageChart[0][i]==-1){
                        continue;
                    }
                    if(coverageChart[r1][i]==1 ||coverageChart[r2][i]==1){
                        if(coverageChart[r1][i]==1 && coverageChart[r2][i]!=1){
                            r2dominating=false;
                        }
                        else if(coverageChart[r1][i]!=1 && coverageChart[r2][i]==1){
                            r1dominating=false;
                        }
                    }
                }
                if(r1dominating==true){
                    coverageChart[i][0]=-1;
                    changeOccured=1;
                    //remove row i
                }
                else if(r2dominating==true){
                    coverageChart[j][0]=-1;
                    changeOccured=1;
                    //remove row j
                }
            }
        }
        
        //Remove dominated columns
        for(int i=1;i<coverageChart[0].size();i++){
            for(int j=1;j<coverageChart[0].size();j++){
                if(i==j){
                    continue;
                }
                if(coverageChart[0][i]==-1 || coverageChart[0][j]==-1){
                    continue;
                }
                int c1=i;
                int c2=j;
                bool c1dominating=true;
                bool c2dominating=true;
                for(int i=1;i<coverageChart.size();i++){
                    if(coverageChart[i][0]==-1){
                        continue;
                    }
                    if(coverageChart[i][c1]==1 ||coverageChart[i][c2]==1){
                        if(coverageChart[i][c1]==1 && coverageChart[i][c2]!=1){
                            c2dominating=false;
                        }
                        else if(coverageChart[i][c1]!=1 && coverageChart[i][c2]==1){
                            c1dominating=false;
                        }
                    }
                }
                if(c2dominating==true){//c1 dominated, thus we remove i
                    coverageChart[0][i]=-1;
                    changeOccured=1;
                    //remove col i
                }
                else if(c1dominating==true){//c2 dominated, thus we remove j
                    coverageChart[0][j]=-1;
                    changeOccured=1;
                    //remove col j
                }
            }
        }
        
    }
}

//HELPER FUNCTIONS
void QmAlgorithm::generateMap(){
    for(int i=0;i<minterms.size();i++){
        mapp[minterms[i].decimalRepresentation]=i;
    }
    //map and use as a key the decimal value to get the index of the minterm
    //That is because we will use the decimal representation of the EPI, and specifically use the decimal values of each implicant combined in this EPI, to update the property "coveredByEPI"
}
bool singular(string s){
    bool singular=true;
    for(int i=0;i<s.size();i++){
        if(s[i]==','){
            singular=false;
        }
    }
    return singular;
}
