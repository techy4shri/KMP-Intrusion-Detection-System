#include "kmp.h"
#include <iostream>

using namespace std;

KMP::KMP(const string& pattern) : pattern(pattern) {
    buildLPS();
}

void KMP::buildLPS() {
    int m = pattern.length();
    lps.resize(m,0);

    int len = 0;
    int i=1;

    while(i<m){
        if(pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else{
            if(len != 0){
                len = lps[len-1];
            } else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

vector<int> KMP::search(const string& text) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();

    int i = 0; //for text[]
    int j = 0; //for pattern[]

    while(i<n){
        if(pattern[j] == text[i]){
            j++; i++;
        }
        if(j==m){
            result.push_back(i-j); //match
            j = lps[j-1];
        } else if(i < n && pattern[j] != text[i]) {
            if(j!= 0){
                j = lps[j-1]; //no match, go back
            } else{
                i++; //thak haar kar ise hi badha diya :)
            }
        }
    }

    return result;
}