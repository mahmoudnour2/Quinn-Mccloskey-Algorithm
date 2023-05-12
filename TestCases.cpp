//
//  TestCases.cpp
//  Quinn
//
//  Created by Mahmoud Mohamed on 3/19/23.
//

#include "TestCases.hpp"
vector<Boolean_Function> get_test_cases(){
    vector<Boolean_Function> test_cases;

        // Testing Case 1

        int num1 = 2;
        string one = "AB'+AB";
        Boolean_Function test1(one, num1);

        // Testing Case 2

        int num2 = 3;
        string two = "BC'+A'B'";
        Boolean_Function test2(two, num2);

        // Testing Case 3

        int num3 = 4;
        string three = "A'C'+AD'";
       Boolean_Function test3(three, num3);

        // Testing Case 4

        int num4 = 4;
        string four = "A'B'C+AB'D'+BCD+B'C'D'+ABC'";
        Boolean_Function test4(four, num4);



        // Testing Case 5

        int num5 = 5;
        string five = "B'C'+C'D'E+CDE'+D'E'";
       Boolean_Function test5(five, num5);



        // Testing Case 6
        
        int num6 = 6;
        string six = "AB'C'DE'F+ACD'E'F'+CD'F'+BEF+A'C'F'+ACF+B'CEF";
        Boolean_Function test6(six, num6);


        // Testing Case 7

        int num7 = 7;
        string seven = "MNO'P+M'N'P'";
        Boolean_Function test7(seven, num7);


        // Testing Case 8

        int num8 = 10;
        string eight = "ABCD'E'F'GJ+ABE'FHI'+A'B'DG'HI+ABCDEFG";
        Boolean_Function test8(eight, num8);


        // Testing Case 9

        int num9 = 3;
        string nine = "A'C'";
        Boolean_Function test9(nine, num9);


        // Testing Case 10

        int num10 = 3;
        string ten = "BC'+B'C";
        Boolean_Function test10(ten, num10);

      
        test_cases.push_back(test1);
        test_cases.push_back(test2);
        test_cases.push_back(test3);
        test_cases.push_back(test4);
        test_cases.push_back(test5);
        test_cases.push_back(test6);
        test_cases.push_back(test7);
        test_cases.push_back(test8);
        test_cases.push_back(test9);
        test_cases.push_back(test10);
    return test_cases;
}
