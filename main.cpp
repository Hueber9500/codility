#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> &T);
bool isVisited[100002];

bool is_neighbour(pair<int, int> c1, pair<int,int> c2)
{
    return (abs(c1.first - c2.first) + abs(c1.second - c2.second) ) <= 1;
}

#define MAX_ROW 3
#define MAX_COL 3

vector<pair<int, int>> find_neighbours(pair<int, int> cell, int max_row, int max_col)
{
    vector<pair<int, int>> neighbours;
    int row_start = std::max(0, cell.first - 1);
    int row_end = std::min(max_row, cell.first + 1);
    int col_start = std::max(0, cell.second - 1);
    int col_end = std::min(max_col, cell.second + 1);

    for(int row = row_start; row <= row_end; row++)
    {
        for( int col = col_start; col <= col_end; col++)
        {
            if(!(row == cell.first && col == cell.second))
            {
                if (is_neighbour(cell, pair(row, col)))
                {
                    neighbours.push_back(pair(row,col));
                }
            }
        }
    }

    return neighbours;
}

int matrix(vector<vector<int>>& matrix)
{
    vector<pair<int, int>> empty_cells;

    for (int i = 0 ; i<matrix.size(); i++)
    {
        for (int j=0; j<matrix[i].size(); j++)
        {
            if(matrix[i][j] > 1)
            {
                empty_cells.push_back(pair<int,int>(i,j));
            }
        }
    }
}




int main()
{
    vector<vector<int>> m = 
        {
            {1, 2, 1},
            {2, 1, 1},
            {0, 0, 1}
        };

    find_neighbours({0,1}, MAX_ROW, MAX_COL);

    vector<int> arr = {0,9,0,2,6,8,0,8,3,0};

    solution(arr);

    return 0;
}

void DFS(int node, const vector<vector<int>>& adjacents, vector<bool>& visited, int tickets_left)
{
	visited[node] = true;
	for(int n: adjacents[node])
	{
        if (visited[n]) continue;

        if (n % 2 == 1 && tickets_left == 0) {cout<<"No more tickets"<<endl; continue;}

        if ( n % 2 == 1) tickets_left--;

        std::cout<<node << " " << n <<endl;
        DFS(n, adjacents, visited, tickets_left);
	}
}



int solution(vector<int> &T) 
{   
    vector<vector<int>> verticesAdjacents(T.size());

    for(size_t i = 0; i < T.size(); i++ ){
        if( i != T[i] ){
            verticesAdjacents[i].push_back(T[i]);
            verticesAdjacents[T[i]].push_back(i);
        }
    }

    int starting_city = T[0];
    int max = 0;
    int available_tickets = 1;
    for (int neighbour: verticesAdjacents[starting_city]){
        vector<bool> visits(T.size());
        visits[starting_city] = true;
        if(starting_city % 2 == 1){
            available_tickets--;
        }
        DFS(neighbour, verticesAdjacents, visits, available_tickets);
        int visited_cities = std::count_if(visits.begin(), visits.end(), [](bool el){ return el; });
        if ( max < visited_cities){
            max = visited_cities;
        }

        cout<<"Starting again"<<endl;
    }

    cout<<"Max visited cities "<< max << endl;

    return max;
}