#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

bool is_palindrome(const string &str, size_t lo, size_t hi){
    while (lo < hi + 1){
        if (str[lo] != str[hi]) return false;
        lo++;
        hi--;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string word;
    while (cin >> word){
        unordered_map<char, vector<size_t>> char_occurrences;
        unordered_set<string> palindromes;
        priority_queue<string, vector<string>, greater<string>> ordered_palindromes;
        for (size_t i = 0; i < word.length(); i++) char_occurrences[word[i]].push_back(i);

        for (size_t i = 0; i < word.length(); i++){
            vector<size_t> vec = char_occurrences[word[i]];
            for (vector<size_t>::iterator it = vec.begin(); it != vec.end(); ++it){
                if (*it <= i) continue;
                if (is_palindrome(word, i, *it)){
                    string sub_string = word.substr(i, *it - i + 1);
                    if (palindromes.find(sub_string) == palindromes.end()){
                        palindromes.insert(sub_string);
                        ordered_palindromes.push(sub_string);
                    }
                    printf("\n");
                }
            }
        }

        while (!ordered_palindromes.empty()){
            cout << ordered_palindromes.top() << endl;
            ordered_palindromes.pop();
        }
    }
    return 0;
}