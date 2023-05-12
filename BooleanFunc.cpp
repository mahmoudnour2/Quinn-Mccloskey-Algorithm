//
//  BooleanFunc.cpp
//  Quinn
//
//  Created by Mahmoud Mohamed on 3/19/23.
//

#include "BooleanFunc.hpp"
bool Validate(string input) {

    int length = input.length();

    for (int i = 0; i < input.length(); i++) {

        for (int j = i+1; j < input.length(); j++) {

            if (input[j] == '+') {

                
                break;
            }

           
            if (input[i] == input[j] && input[j] != '\'') {
                
                return 0;

            }

           


        }


    }


    if (isalpha(input[0]) == 0) {

        return 0;
    }

    if (input[input.length() - 1] != '\'' && isalpha(input[input.length() - 1]) == 0) {

        
        return 0;


    }

    for (int i = 0; i < input.length(); i++) {

        if (isalpha(input[i])==0) {

            if (input[i] != '\'' && input[i] != '+') {
                
                return 0;

            }
        }

        if (input[i] == '+' && (input[i + 1] == '+' || input[i + 1] == '\'')) {

           
            return 0;


        }

    }

    bool check;

    if (isupper(input[0]) == 1) {

        check = 1;

    }

    else {

        check = 0;
    }

    for (int i = 0; i < input.length(); i++) {

        if (isupper(input[i]) == 1 && check == 0 && input[i]!= '+' && input[i]!= '\'') {

            return 0;

        }

        if (isupper(input[i]) == 0 && check == 1 && input[i] != '+' && input[i] != '\'') {

            return 0;
        }


    }


    return 1;
}
//Function definitions of class

int BinarytoDecimal(string binary,int len, int i=0){
   if (i == len-1)
   return (binary[i] - '0');
   int temp=binary[i]-'0';
   temp=temp<<len-i-1;
   temp=temp+BinarytoDecimal(binary,len,i+1);
   return (temp);
}
vector<string> Boolean_Function::getBinMinterms(){
    return Binary_Rep1;
}
vector<string> Boolean_Function::getdecMinterms(){
    vector<string> decMinterms;
    for(int i=0;i<Binary_Rep1.size();i++){
        int dec=BinarytoDecimal(Binary_Rep1[i], Binary_Rep1[i].size());
        string decS=to_string(dec);
        decMinterms.push_back(decS);
        //convert from binary to decimal and push to decMinterms vector
    }
    return decMinterms;
}
Boolean_Function::Boolean_Function(string input, int num) {

    number_of_variables = num;
    myInput = input;
    variables.resize(num);
    Identify_Variables();
    Generate_Truth_Table();
    Identify_Minterms();
    Generate_Binary_Rep();
    Generate_Final_Truth_Table();
    Generate_Canonical_SoP();
    Generate_Canonical_PoS();
};



string Boolean_Function::Get_Input() {


    return myInput;

}

string Boolean_Function::Binary_Sum(string num1, string num2) {

    string addRes;

    int len, carry, re, i;

    len = num1.size();
    addRes = "";
    carry = 0;

    for (i = (len - 1); i > -1; i--)
    {
        re = carry;
        if (num1[i] == '1')
            re = re + 1;
        else
            re = re + 0;
        if (num2[i] == '1')
            re = re + 1;
        else
            re = re + 0;
        if (re % 2 == 1)
            addRes = '1' + addRes;
        else
            addRes = '0' + addRes;
        if (re < 2)
            carry = 0;
        else
            carry = 1;
    }
    if (carry != 0)
        addRes = '1' + addRes;

    //cout << "\nAddition Result = " << addRes;

    return addRes;
}



void Boolean_Function::Generate_Truth_Table() {

    Truth_Table.resize(pow(2, number_of_variables));

    for (int i = 0; i < Truth_Table.size(); i++) {

        Truth_Table[i].resize(number_of_variables);
    }


  /*  cout << "number of rows is " << Truth_Table.size() << endl;
    
    for (int i = 0; i < Truth_Table[i].size(); i++) {

        cout << "Number of columns in row " << i << " is " << Truth_Table[i].size() << endl;

    }*/


    string num1 = "0";

    for (int i = 1; i < number_of_variables; i++) {

        num1 = num1 + '0';

    }

   // cout << "num1 is " << num1 << endl;


    string num2 = "0";

    for (int i = 1; i < number_of_variables; i++) {

        if (i == number_of_variables - 1) {

            num2 = num2 + '1';
        }

        else {

            num2 = num2 + '0';
        }
       
    }

   // cout << "num2 is " << num2 << endl;

    int one = 0;
    int two = 0;

    for (int i = 0; i < Truth_Table.size(); i++) {

        for (int j = 0; j < Truth_Table[i].size(); j++) {

            if (num1[j] == '0') {

                one = 0;
            }

            else if (num1[j] == '1') {

                one = 1;
            }

            Truth_Table[i][j] = one;
           
        }

        num1 = Binary_Sum(num1, num2);
        
    }

}


void Boolean_Function::Print_Truth_Trable() {

    cout << "The Truth Table for the given function is " << endl << endl;

    for (int i = 0; i < Truth_Table.size(); i++) {

        for (int j = 0; j < Truth_Table[i].size(); j++) {

           
            cout << Truth_Table[i][j] << " ";

        }

        cout << endl;

    }

    cout << endl;
}


void Boolean_Function::Identify_Minterms() {

    string temp;
    int counter1 = 0;
    int counter2 = 0;


    for (int i = 0; i < myInput.length(); i++) {

        if (i == myInput.length() - 1) {

            temp = myInput.substr(counter1, counter2+1);
            counter1 = counter1 + counter2 + 1;
            counter2 = 0;

            minterms.push_back(temp);


        }

        if (myInput[i] == '+') {

            temp = myInput.substr(counter1, counter2);
            counter1 = counter1+counter2+1;
            counter2 = 0;
           
            minterms.push_back(temp);


        }

        else {

            counter2++;

        }

    }

}


void Boolean_Function::Print_Minterms() {

    for (int i = 0; i < minterms.size(); i++) {

        cout << "minterm " << i+1 << " is " << minterms[i] << endl;
    }



}


void  Boolean_Function::Identify_Variables() {

    int count = 0;
    int k = 0;
    int tracker = 0;

    for (int i = 0; i < myInput.size(); i++) {


        if (isalpha(myInput[i]) != 0) {

           
            for (int j = 0; j < variables.size(); j++) {

                if (myInput[i] == variables[j]) {

                    break;
                }

                count++;
               

            }

            if (count == variables.size()) {

                variables[k]=(myInput[i]);
                k++;
                tracker++;
            }

            

        }

        count = 0;

    }

 

    sort(variables.begin(), variables.end());

   int extra = variables.size() - tracker;

  

    int m = 0;

    int counter = 0;

    while (extra!=0) {

        if (counter == 0) {

            variables[m] = variables[variables.size() - 1];
            variables[m]++;
            m++;
            extra--;
            counter++;

        }

        else {

            variables[m] = variables[m-1];
            variables[m]++;
            m++;
            extra--;


        }

        

    }

    sort(variables.begin(), variables.end());


}


void Boolean_Function::Print_Variables() {
    

    for (int i = 0; i < variables.size(); i++) {

        cout << "Variable " << i + 1 << " is " << variables[i] << endl;

    }

}

 void Boolean_Function::Generate_Binary_Rep() {
    
    vector<vector<int>> Binary_Representation_Minterms;

    int now = 0;

    for (int i = 0; i < minterms.size(); i++) {

        now++;

        for (int j = 0; j <variables.size() ; j++) {

            
            Binary_Representation_Minterms.resize(now);

            for (int k = 0; k < minterms[i].length(); k++) {

                if (minterms[i][k] == variables[j]) {


                    if (k + 1 < minterms[i].length()) {

                      

                        if (minterms[i][k + 1] == '\'') {

                           
                            Binary_Representation_Minterms[now-1].resize(number_of_variables);
                            Binary_Representation_Minterms[now-1][j] = 0;

                        }

                        else {

                            Binary_Representation_Minterms[now-1].resize(number_of_variables);
                            Binary_Representation_Minterms[now-1][j] = 1;

                        }

                        break;

                    }

                    else {

                       // cout << "I am here for Variable " << variables[j] << endl;
                        Binary_Representation_Minterms[now-1].resize(number_of_variables);
                        Binary_Representation_Minterms[now-1][j] = 1;

       
                    }

                    break;

                   
                }

                else {

                    if (k == minterms[i].length()-1) {

                        Binary_Representation_Minterms[now-1].resize(number_of_variables);
                        Binary_Representation_Minterms[now-1][j] = -5;

                    }


                }


            }
           

        }

    }
    

   // vector<int> Binary_Representation_Final;
   // int row = 0;


    for (int i = 0; i < Binary_Representation_Minterms.size(); i++) {

        for (int j = 0; j < Binary_Representation_Minterms[i].size(); j++) {

            if (Binary_Representation_Minterms[i][j] == -5) {

                Binary_Representation_Minterms.resize(Binary_Representation_Minterms.size() + 2);

                Binary_Representation_Minterms[Binary_Representation_Minterms.size() - 1] = Binary_Representation_Minterms[i];

                Binary_Representation_Minterms[Binary_Representation_Minterms.size() - 2] = Binary_Representation_Minterms[i];

                Binary_Representation_Minterms[Binary_Representation_Minterms.size() - 1][j] = 0;
                Binary_Representation_Minterms[Binary_Representation_Minterms.size() - 2][j] = 1;

                break;
            }

        }


    }


   // int counter1 = 0;

    vector<vector<int>> Final_Vector;
    for (int i = 0; i < Binary_Representation_Minterms.size(); i++) {

        for (int j = 0; j < Binary_Representation_Minterms[i].size(); j++) {


            if (Binary_Representation_Minterms[i][j] == -5) {

              //  counter1++;
                break;

            }

            else if (j == Binary_Representation_Minterms[i].size() - 1) {

                Final_Vector.push_back(Binary_Representation_Minterms[i]);
            }

        }

    }



    for (int i = 0; i < Final_Vector.size(); i++) {

        if (i + 1 < Final_Vector.size()) {

            for (int j = i + 1; j < Final_Vector.size(); j++) {

                if (Final_Vector[i] == Final_Vector[j]) {

                    

                    Final_Vector.erase(Final_Vector.begin() + j);

                }

            }

        }
        

    }


    Binary_Rep = Final_Vector;



    // Storing the Binary Representation in a String Format

    Binary_Rep1.resize(Binary_Rep.size());

    for (int i = 0; i < Binary_Rep.size(); i++) {

        Binary_Rep1[i] = "";

        for (int j = 0; j < Binary_Rep[i].size(); j++) {

            Binary_Rep1[i] = Binary_Rep1[i] + to_string(Binary_Rep[i][j]);
        }


    }


    // Print the Binary Rep in String

   /* for (int i = 0; i < Binary_Rep1.size(); i++) {

        cout << Binary_Rep1[i] << endl;

    }*/
    

}


void Boolean_Function::Generate_Final_Truth_Table() {


    for (int i = 0; i < Truth_Table.size(); i++) {

        for (int j = 0; j < Binary_Rep.size(); j++) {

           

            if (Truth_Table[i] == Binary_Rep[j]) {

                Truth_Table[i].push_back(1);
                break;

            }

            else if (j == Binary_Rep.size()-1) {

                Truth_Table[i].push_back(0);
            }

           
        }

    }

}




void Boolean_Function::Generate_Canonical_SoP() {

    string output = "";

    for (int i = 0; i < Truth_Table.size(); i++) {

        if (Truth_Table[i][Truth_Table[i].size() - 1] == 1) {

            for (int j = 0; j < Truth_Table[i].size()-1; j++) {


                if (Truth_Table[i][j] == 1) {

                    output = output + variables[j];
                    

                }

                else if (Truth_Table[i][j] == 0) {

                    output = output + variables[j] + "\'";
                  

                }

            }
           

            output = output + "+";
           


        }
       

    }
   
    output = output.substr(0, output.length() - 1);
    canonical_SoP = output;
        
}

void Boolean_Function::Print_Canonical_SoP() {

    cout << "The Canonical SoP for the given function is " << canonical_SoP << endl << endl;

}


void Boolean_Function::Generate_Canonical_PoS() {


    string pos = "(";

    for (int i = 0; i < canonical_SoP.length(); i++) {

      
        if (isalpha(canonical_SoP[i]) != 0) {

            if (canonical_SoP[i + 1] == '\'') {

                pos = pos + canonical_SoP[i];

                if ( i+2 < canonical_SoP.size() && isalpha(canonical_SoP[i + 2]) != 0) {

                    pos = pos + '+';
                }

            }

            else {

                pos = pos + canonical_SoP[i] + '\'';

                if (i + 1 < canonical_SoP.size() && isalpha(canonical_SoP[i + 1]) != 0) {

                    pos = pos + '+';
                }
            }




        }
        
        
        if (canonical_SoP[i] == '+') {

            pos = pos + ')' +  '*' + '(';
        }


    }

    pos = pos + ')';

    canonical_PoS = pos;

}


void Boolean_Function::Print_Canonical_PoS() {

    cout << "The Canonical PoS for the given function is " << canonical_PoS << endl << endl;

}


vector<char> Boolean_Function::Get_Variables() {


    return variables;



}
