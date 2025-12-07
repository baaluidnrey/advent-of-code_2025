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

vector<int> splitLaserBeam(vector<int> beams, vector<int> splitters, int &nb_splits){
    
    vector<int> res;
    for (auto b : beams){
        for (auto s : splitters){
            if (b==s){
                nb_splits++;
                int p1 = b-1;
                int p2 = b+1;
                // it would be more optimized to use a set
                if (count(res.begin(), res.end(), p1) == 0) res.push_back(p1);
                if (count(res.begin(), res.end(), p2) == 0) res.push_back(p2);
            }
        }
    }
    return res;
}

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
    vector<int> beams;
    vector<int> splitter_positions;
    vector<splitter_row> splitters;
    int row = 0;
    char c;
    while (getline(f, str)){
        splitter_positions.clear();
        for (int i = 0; i < str.length(); i++){
            c = str[i];
            if      (c == 'S')  beams.push_back(i);
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
    /*
    cout << "---\nbeams\n";
    for (auto p : beams) cout << p << ", ";
    cout << endl;
    cout << "---\nsplitters\n";
    for (auto it : splitters){
        cout << "row " << it.row << ": ";
        for (auto p : it.positions) cout << p << ", ";
        cout << endl;
    }
    */

    // part. 1 ----------
    int res = 0;
    vector<int> beams_tmp = beams;
    do {
        beams_tmp = splitLaserBeam(beams_tmp, splitters.front().positions, res);

        // cout << "---\nbeams: ";
        // for (auto p : beams_tmp) cout << p << ", ";
        // cout << endl;
        // cout << "splitters: ";
        // for (auto p : splitters.front().positions) cout << p << ", ";
        // cout << endl;
        // cout << "nb of splits: " << res << endl;

        splitters.erase(splitters.begin());
    } while (splitters.size()>0);


    cout << "res : " << res << endl;
    return 0;
}
