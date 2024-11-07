#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;
    int numTrees, tree, person=1;
    cin >> numTrees;

    vector<vector<int>> people_to_trees(n);
        
    while (person > 0) {
        person=0;
        cin >> person >> tree;
        if(person > 0)
            people_to_trees[person-1].push_back(tree);
    }
    
    vector<string> people_to_tree_string(n);

    for (int i = 0; i < people_to_tree_string.size(); i++) {
        sort(people_to_trees[i].begin(), people_to_trees[i].end());
        for (int j = 0; j < people_to_trees[i].size(); j++) {
            string tree_str = to_string(people_to_trees[i][j]) + "-";
            people_to_tree_string[i] += tree_str;
        }
    }

    sort(people_to_tree_string.begin(), people_to_tree_string.end());
    people_to_tree_string.erase(unique(people_to_tree_string.begin(), people_to_tree_string.end()), people_to_tree_string.end());
    cout << people_to_tree_string.size();

    return 0;
}
