#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <cmath>

using namespace std;

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

        int GetValue(int pos){
            return v[pos];
        }

        void UpdateValue(int pos, int value){
            v[pos] = value;
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
    vector<int> v;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open()){
        cerr << "Error opening the file!";
        return 1;
    }

    // get data from file and put it in a map
    while (getline(f, str)){
        for (char c : str){
            if      (c=='.')    v.push_back(0);
            else if (c=='@')    v.push_back(1);     // roll of paper
        }
        nb_lines++;
    }
    Map2D map2D = Map2D(v, nb_lines);
    // map2D.PrintMap();

    // compute neighbours
    vector<int> v_rolls_to_remove;
    int nb_rolls_to_remove = 0;

    // part 1 ----------
    // res = 0;
    // for (int pos=0; pos<=v.size(); pos++){
    //     if (v[pos]==1 && map2D.SumNeighbours(pos)<4) res++;
    // }

    // part 2 ----------
    res = 0;
    do {
        // cout << "---\n";
        // map2D.PrintMap();
        nb_rolls_to_remove = 0;
        for (int pos=0; pos<=v.size(); pos++){
            if (map2D.GetValue(pos)==1 && map2D.SumNeighbours(pos)<4){
                nb_rolls_to_remove++;
                v_rolls_to_remove.push_back(pos);
                for (auto it : v_rolls_to_remove) map2D.UpdateValue(it, 0);
            }
        }
        res += nb_rolls_to_remove;
    } while (nb_rolls_to_remove > 0);

    // for (int pos=0; pos<=v.size(); pos++) v_neighbours.push_back(map2D.SumNeighbours(pos));
    // Map2D neighbours_map = Map2D(v_neighbours, nb_lines);
    // cout << "neighbours:\n";
    // neighbours_map.PrintMap();

    f.close();
    cout << "res: " << res << endl;
    return 0;
}
