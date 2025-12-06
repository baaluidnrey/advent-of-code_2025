#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Map2D {

    public:
        Map2D(vector<int> v, int height) : v(v), height(height)
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

    /* compute neighbours
    vector<int> v_neighbours;
    for (int pos=0; pos<=v.size(); pos++) v_neighbours.push_back(map2D.SumNeighbours(pos));
    Map2D neighbours_map = Map2D(v_neighbours, nb_lines);
    cout << "neighbours:\n";
    neighbours_map.PrintMap();
    */

    // compute res
    res = 0;
    for (int pos=0; pos<=v.size(); pos++){
        if (v[pos]==1 && map2D.SumNeighbours(pos)<4) res++;
    }

    f.close();
    cout << "res: " << res << endl;
    return 0;
}
