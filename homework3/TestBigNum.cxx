#include <iostream>
#include <cstdlib>
#include "BigNum.h"
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <fstream>
#include <cstring>

using namespace std;
using namespace HW3;
ofstream grade;

#define TOTALTESTS 20

int testNo = 0;
int i = 0;
void tester(){
    cerr << "*** Running test " << (testNo + 1) << " *** "<< endl;
    grade.open ("grade.txt", ios::out | ios::app);
    if (testNo >= TOTALTESTS)
    {
        grade.close();
        cerr << "returning";
        return;
    }
    if (testNo == 0){
        //cout << "DEFAULT CONSTRUCTOR TEST" << endl;
        BigNum test1;
        if (strcmp(test1.printBigNum(), "0") == 0){
            cerr << "test 1 passed.\n";
            grade << "test 1 passed.\n";
        }else{
            grade << "test 1 failed.\n";
        }
    }
    if (testNo == 1){
        //cout << "INT CONSTRUCTOR TESTS" << endl;
        BigNum test2 = 243;
        if (strcmp(test2.printBigNum(), "243") == 0){
            cerr << "test 2 passed.\n";
            grade << "test 2 passed.\n";
        }else{
            grade << "test 2 failed.\n";
        }
    }
    if (testNo == 2){
        BigNum test3 = -243;
        if (strcmp(test3.printBigNum(), "-243") == 0){
            cerr << "test 3 passed.\n";
            grade << "test 3 passed.\n";
        }else{
            grade << "test 3 failed.\n";
        }
    }
    if (testNo == 3){
        BigNum test4 = 0;
        if (strcmp(test4.printBigNum(), "0") == 0){
            cerr << "test 4 passed.\n";
            grade << "test 4 passed.\n";
        }else{
            grade << "test 4 failed.\n";
        }
    }
    if (testNo == 4){
        BigNum test5 = 3458919;
        if (strcmp(test5.printBigNum(), "3458919") == 0){
            cerr << "test 5 passed.\n";
            grade << "test 5 passed.\n";
        }else{
            grade << "test 5 failed.\n";
        }
    }
    if (testNo == 5){ 
        //cout << "STRING CONSTRUCTOR TESTS" << endl;  
        BigNum test6 = (string) "0";
        if (strcmp(test6.printBigNum(), "0") == 0){
            cerr << "test 6 passed.\n";
            grade << "test 6 passed.\n";
        }else{
            grade << "test 6 failed.\n";
        }
    }
    if (testNo == 6){
        BigNum test7 = (string) "9997632187383270741827";
        if (strcmp(test7.printBigNum(), "9997632187383270741827") == 0){
            cerr << "test 7 passed.\n";
            grade << "test 7 passed.\n";
        }else{
            grade << "test 7 failed.\n";
        }
    }
    if (testNo == 7){
        BigNum test8 = (string) "-9997632187383270741827";
        if (strcmp(test8.printBigNum(), "-9997632187383270741827") == 0){
            cerr << "test 8 passed.\n";
            grade << "test 8 passed.\n";
        }else{
            grade << "test 8 failed.\n";
        }
    }
    if (testNo == 8){
        BigNum test9 = (string) "-0008"; 
        if (strcmp(test9.printBigNum(), "-8") == 0){
            cerr << "test 9 passed.\n";
            grade << "test 9 passed.\n";
        }else{
            grade << "test 9 failed.\n";
        }
    }
    if (testNo == 9){
        BigNum test10 = (string) "-3458919728786732132";
        if (strcmp(test10.printBigNum(), "-3458919728786732132") == 0){
            cerr << "test 10 passed.\n";
            grade << "test 10 passed.\n";
        }else{
            grade << "test 10 failed.\n";
        }
    }
    if (testNo == 10){
        //cout << "COPY CONSTRUCTOR TESTS" << endl;
        BigNum test11a = 243;
        BigNum test11 = test11a;
        if (strcmp(test11.printBigNum(), "243") == 0){
            cerr << "test 11 passed.\n";
            grade << "test 11 passed.\n";
        }else{
            grade << "test 11 failed.\n";
        }
    }
    if (testNo == 11){
        BigNum test12a = (string) "-3458919728786732132";
        BigNum test12 = test12a;
        if (strcmp(test12.printBigNum(), "-3458919728786732132") == 0){
            cerr << "test 12 passed.\n";
            grade << "test 12 passed.\n";
        }else{
            grade << "test 12 failed.\n";
        }
    }
    if (testNo == 12){
        BigNum test13a = -243;
        BigNum test13 = test13a;
        if (strcmp(test13.printBigNum(), "-243") == 0){
            cerr << "test 13 passed.\n";
            grade << "test 13 passed.\n";
        }else{
            grade << "test 13 failed.\n";
        }
    }
    if (testNo == 13){
        BigNum test14a = 3458919;
        BigNum test14 = test14a;
        if (strcmp(test14.printBigNum(), "3458919") == 0){
            cerr << "test 14 passed.\n";
            grade << "test 14 passed.\n";
        }else{
            grade << "test 14 failed.\n";
        }
    }
    //cout << "ASSIGNMENT OPERATOR TESTS" << endl;
    if (testNo == 14){
        BigNum test15;
        BigNum test15a = 3458919;
        
        test15 = test15a;
        if (strcmp(test15.printBigNum(), "3458919") == 0){
            cerr << "test 15 passed.\n";
            grade << "test 15 passed.\n";
        }else{
            grade << "test 15 failed.\n";
        }
    }
    if (testNo == 15){
        BigNum test16;
        BigNum test16a = (string) "-3458919728786732132";
        BigNum test16b = 243;
        
        test16 = test16a = test16b;
        if (strcmp(test16.printBigNum(), "243") == 0){
            cerr << "test 16 passed.\n";
            grade << "test 16 passed.\n";
        }else{
            grade << "test 16 failed.\n";
        }
    }
    if (testNo == 16){
        BigNum test17;
        BigNum test17a;
        
        test17 = test17a;
        if (strcmp(test17.printBigNum(), "0") == 0){
            cerr << "test 17 passed.\n";
            grade << "test 17 passed.\n";
        }else{
            grade << "test 17 failed.\n";
        }
    }
    if (testNo == 17){
        BigNum test18;
        BigNum test18a = (string) "-9997632187383270741827";
        test18 = test18a;
        if (strcmp(test18.printBigNum(), "-9997632187383270741827") == 0){
            cerr << "test 18 passed.\n";
            grade << "test 18 passed.\n";
        }else{
            grade << "test 18 failed.\n";
        }
    }
    if (testNo == 18){
        BigNum test18b = 76878;
        test18b = test18b;
        if (strcmp(test18b.printBigNum(), "76878") == 0){
            cerr << "test 19 passed.\n";
            grade << "test 19 passed.\n";
        }else{
            grade << "test 19 failed.\n";
        }
    }
    if (testNo == 19){
        
// bad Eliz; can't test resize() directly but can force it
//       test18b.resize(200);
	BigNum test19 = (string) "99999999999999999999999999999999";
	BigNum test19b = 1;
	test19b = test19;
        if (strcmp(test19b.printBigNum(), "99999999999999999999999999999999") == 0){
            cerr << "test 20 passed.\n";
            grade << "test 20 passed.\n";
        }else{
            grade << "test 20 failed.\n";
        }
    }
    grade.close();
    return;
}

void termination_handler (int param)
{
    grade.close();
    if (++testNo <= TOTALTESTS){
        grade.open ("grade.txt", ios::out | ios::app);
        grade << "test " << testNo << " failed.\n";
        cerr << "\n************** test " << testNo << " failed. ***************\n"; 
        if (testNo == TOTALTESTS){
            cerr << "exiting";
            exit(1);
        }
        return tester();
    }
}
int main()
{
    grade.open ("grade.txt");
    grade.close();
    signal (SIGSEGV, termination_handler);
    signal (SIGABRT, termination_handler);
    signal (SIGFPE, termination_handler);
    signal (SIGILL, termination_handler);
    signal (SIGSEGV, termination_handler);
    signal (SIGTERM, termination_handler);
    for (testNo = 0; testNo < TOTALTESTS; testNo++){
        tester();
    }
	int a1 = 0001;
	int b1 = 21;
    BigNum a = a1;
    BigNum b = b1; 
    
    cout << "\nOperator > (1 = true, 0 = false)" << endl;
    cout << a << " > " << b << ": " << (a > b) << endl;
    cout << b1 << " > " << a1 << ": " << (b > a) << endl;
    
    cout << "\nOperator < (1 = true, 0 = false)" << endl;
    cout << a1 << " < " << b1 << ": " << (a < b) << endl;
    cout << b1 << " < " << a1 << ": " << (b < a) << endl;

    int c1 = 10;
    int d1 = 11;
    BigNum c = c1;
    BigNum d = d1;
    BigNum e = 11;
 
    cout << "\nOperator == (1 = true, 0 = false)" << endl;
    cout << c1 << " = " << b1 << ": " << (c == b) << endl;
    cout << d1 << " = " << d1 << ": " << (d == e) << endl;

    cout << "\nOperator != (1 = true, 0 = false)" << endl;
    cout << c1 << " != " << b1 << ": " << (c != b) << endl;
    cout << d1 << " != " << d1 << ": " << (d != e) << endl;
	
    cout << "\nOperator >= (1 = true, 0 = false)" << endl;
    cout << c1 << " >= " << d1 << ": " << (c >= d) << endl;
    cout << b1 << " >= " << d1 << ": " << (b >= d) << endl;
    cout << c1 << " >= " << c1 << ": " << (e >= c) << endl;	
    
    cout << "\nOperator <= (1 = true, 0 = false)" << endl;
    cout << c1 << " <= " << d1 << ": " << (c <= d) << endl;
    cout << b1 << " <= " << d1 << ": " << (b <= d) << endl;
    cout << c1 << " <= " << c1 << ": " << (e <= c) << endl;
    
	BigNum x; 
	cout << "\nInput/Output test" << endl;
	cout << "Enter a big num: ";
    cin >> x; 
    cout << "Output: " << x;
    
    grade.close();
    return 0;
}
