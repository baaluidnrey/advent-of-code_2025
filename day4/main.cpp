#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#define PAPER_ROLL  1
#define EMPTY       0

class Map2D {

    public:
        Map2D(vector<int> v, int height) : 
        v(v),
        height(height)
        {
            width = v.size() / height;
        }

        void PrintMap(){
            for (int i=0; i<height; i++){
                for (int j=0; j<width; j++) cout << v[i*width+j] << " ";
                cout << endl;
            }
        }

        int SumNeighbours(int pos){
            int sum = 0;
            for (int i=-1; i<=1; i++){
                for (int j=-1; j<=1; j++){
                    int row = (pos / width) + i;
                    int col = (pos % width) + j;
                    if ( ( row>=0 && row<width) 
                      && (col>=0 && col<height) ){
                        sum += v[row*width+col];
                    }
                }
            }
            return sum - v[pos];
        }

        int GetSize(){
            return v.size();
        }

        int GetValue(int pos){
            return v[pos];
        }

        void UpdateValue(int pos, int value){
            v.erase(v.begin()+pos);
            v.insert(v.begin()+pos, value);
            // v[pos] = value;
        }

    private:
        vector<int> v;
        int height;
        int width;
};


int main()
{
    int nb_lines=0;
    int res;
    string str;
    vector<int> v, v_neighbours, v_rolls_to_remove;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    // get data from file and put it in a map
    while (getline(f, str)){
        for (char c : str){
            if      (c=='.')    v.push_back(EMPTY);
            else if (c=='@')    v.push_back(PAPER_ROLL);
        }
        nb_lines++;
    }
    Map2D map2D = Map2D(v, nb_lines);
    // map2D.PrintMap();

    // compute number of rolls of paper to remove
    res = 0;
    int nb_rolls_to_remove = 0;
    bool part_1 = true;
    do {
        nb_rolls_to_remove = 0;
        v_rolls_to_remove.clear();
        for (int pos=0; pos<=map2D.GetSize(); pos++){
            if ( map2D.GetValue(pos)==PAPER_ROLL && map2D.SumNeighbours(pos)<4 ) {
                nb_rolls_to_remove++;
                v_rolls_to_remove.push_back(pos);
                if (!part_1)    // the update creates a really wird behavior and does not work with part. 1
                    for (auto p : v_rolls_to_remove) map2D.UpdateValue(p, EMPTY);
            }
        }
        res += nb_rolls_to_remove;
        cout << "---\n";
        cout << "nb_rolls_to_remove: " << nb_rolls_to_remove << endl;
        // map2D.PrintMap();
    }
    while (!part_1 && nb_rolls_to_remove > 0);

    f.close();
    cout << "res: " << res << endl;
    return 0;
}
