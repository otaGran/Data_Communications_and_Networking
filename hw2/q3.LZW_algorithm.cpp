//
// Created by beans on 10/1/2017.
//
/*
STRING = get input symbol
    WHILE there are still input symbols DO
        SYMBOL = get input symbol
        IF STRING + SYMBOL is in the TABLE THEN
            STRING = STRING + SYMBOL
        ELSE
            output the code for STRING
            add STRING + SYMBOL to TABLE
            STRING = SYMBOL
        END
    END
output the code for STRING
 */

/*
 * test Input 1: abbbabbbab
 * Output: 97,98,257,256,258,98
 *
 * test input 2: abcabcabcabcabcabcabc
 * Output: 97,98,99,256,258,257,259,262,261,257
 *
 */

#include <iostream>
#include <cstring>
#include <map>

using namespace std;
map<string,int> table;
int main(){
    string input,input_symbol;
    cin >> input;
    int cnt = 1,code_cnt = 256;
    //init the table with a,b,c
    table["a"] = 97;
    table["b"] = 98;
    table["c"] = 99;
    input_symbol = input.substr(0,1);
    while(cnt<input.size()){
        string symbol = input.substr(cnt++,1);
        string tmp = input_symbol+symbol;
        if(table.count(tmp)) {
            input_symbol += symbol;
        }
        else {
            cout << table[input_symbol] << "," ;
            table[tmp] = code_cnt++;
            input_symbol = symbol;
        }
    }
    cout << table[input_symbol] << endl;
}


