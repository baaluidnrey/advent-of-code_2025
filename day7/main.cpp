#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

struct splitter_row {
    int row;
    vector<int> positions;
};

int main()
{
    // open puzzle input
    ifstream f("input_test.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    // extract data from puzzle input ----------
    string str;
    int source_position;
    vector<int> splitter_positions;
    vector<splitter_row> splitters;
    int row = 0;
    char c;
    while (getline(f, str)){
        splitter_positions.clear();
        for (int i = 0; i < str.length(); i++){
            c = str[i];
            if      (c == 'S')  source_position = i;
            else if (c == '^')  splitter_positions.push_back(i);
        }
        if (splitter_positions.size()>0){
            splitter_row splitters_tmp{row, splitter_positions};
            splitters.push_back(splitters_tmp);
        }
        row++;
    }
    f.close();

    // display input ----------
    cout << "source: " << source_position << endl;
    cout << "---\nsplitters\n";
    for (auto it : splitters){
        cout << "row " << it.row << ": ";
        for (auto p : it.positions) cout << p << ", ";
        cout << endl;
    }

    int res = 0;
    cout << "res : " << res << endl;
    return 0;
}
