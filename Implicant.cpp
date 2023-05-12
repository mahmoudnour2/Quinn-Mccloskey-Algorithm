//
//  Implicant.cpp
//  Quinn
//
//  Created by Mahmoud Mohamed on 3/18/23.
//

#include "Implicant.hpp"

implicant::implicant(){
    binaryRepresentation="";
    decimalRepresentation="";
    literalRepresentation="";
}
void implicant :: concatenateDec(string dec1, string dec2){
    this->decimalRepresentation=dec1+","+dec2;
}
int implicant :: canBeCombined(string bin){
    int counter=0;
    int index=-1;
    int n=0;
    while(counter<bin.size()){
        if(bin[counter]!=this->binaryRepresentation[counter]){
            index=counter;
            n++;
            if(n>1){
                return -1;
            }
        }
        counter++;
    }
    return index;
   
}
void implicant :: updateLit(){
    string bin=this->binaryRepresentation;
    string lit="";
    int asci=97;
    
    for(int i=0;i<bin.size();i++){
        if(bin[i]=='1'){
            lit=lit+char(asci);
            
        }
        else if(bin[i]=='0'){
            lit=lit+char(asci)+"'";
        }
        asci++;
    }
    
    this->literalRepresentation=lit;
}
void implicant :: combineBin(string bin1, string bin2,int index){
    string combinedBin="";
    for(int i=0;i<bin1.size();i++){
        if(i!=index){
            combinedBin=combinedBin+bin1[i];
        }
        else{
            combinedBin=combinedBin+'-';
        }
    }
    this->binaryRepresentation=combinedBin;
}
int implicant :: getNumberOfOnes(){
    string b=this->binaryRepresentation;
    int n=0;
    for(int i=0;i<b.size();i++){
        if(b[i]=='1'){
            n++;
        }
    }
    return n;
}
