#include <iostream>
#include <deque>
#include <vector>

int n, m;

using namespace std;

struct block {
    char type;
    int distance[3] = {100000, 100000, 100000}; // 0 -> A // 1 -> B // 2 -> C
    pair<int, int> road[3]; // 0 -> A // 1 -> B // 2 -> C
} map[505][505];


pair<int, pair<int, int>> calculateMin() {
    int min = 100000;
    int distances;
    pair<int, pair<int, int>> minBlock = make_pair(min, make_pair(0, 0));;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            distances = map[i][j].distance[0] + map[i][j].distance[1] + map[i][j].distance[2];
            if (map[i][j].type == '*') distances -= 2;
            if (min > distances) {
                min = distances;
                minBlock = make_pair(min, make_pair(i, j));
            }
        }
    }
    return minBlock;
}

void printMap() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << map[i][j].type;
        }
        cout << endl;
    }
}


vector<pair<int, int>> getNeighbor(pair<int, int> s) {
    vector<pair<int, int>> neighbor;
    if (s.first != 0) { neighbor.emplace_back(s.first - 1, s.second); }
    if (s.first != n - 1) { neighbor.emplace_back(s.first + 1, s.second); }
    if (s.second != m - 1) { neighbor.emplace_back(s.first, s.second + 1); }
    if (s.second != 0) { neighbor.emplace_back(s.first, s.second - 1); }
    return neighbor;
}


void bfs(pair<int, int> source, int root) { // find path
    int dist = 0;
    map[source.first][source.second].distance[root] = dist;
    deque<pair<int, int> > dq;
    dq.push_back(source);
    while (!dq.empty()) {
        pair<int, int> s = dq.front();
        dq.pop_front();
        vector<pair<int, int>> neighbor = getNeighbor(s);
        dist = map[s.first][s.second].distance[root];
        for (auto &itr: neighbor) {
            if ((map[itr.first][itr.second].type == '.' || map[itr.first][itr.second].type == 'A') &&
                map[itr.first][itr.second].distance[root] == 100000) {
                map[itr.first][itr.second].distance[root] = dist;
                map[itr.first][itr.second].road[root] = s;
                dq.push_front(itr);
            } else if (map[itr.first][itr.second].type == '*' && map[itr.first][itr.second].distance[root] == 100000) {
                map[itr.first][itr.second].distance[root] = dist + 1;
                map[itr.first][itr.second].road[root] = s;
                dq.push_back(itr);
            }
        }
    }
}

void rowing(int i, int j, int root, char look) { // cleaning road
    while (map[i][j].type != look) {
        if (map[i][j].type == '*')
            map[i][j].type = 'o';
        int I = i;
        i = map[i][j].road[root].first;
        j = map[I][j].road[root].second;
    }
}

void result(pair<int, pair<int, int>> minBlock) {
    if (minBlock.first < 100000) {
        cout << minBlock.first << endl;

        int i = minBlock.second.first;
        int j = minBlock.second.second;

        rowing(i, j, 0, 'A');

        rowing(i, j, 1, 'B');

        rowing(i, j, 2, 'C');

        printMap();
    } else cout << "CHRISTMAS RUINED!";
}

int main() {
    /////////// input ////////////
    cin >> n >> m;
    pair<int, int> A;
    pair<int, int> B;
    pair<int, int> C;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j].type;
            if (map[i][j].type != '.' && map[i][j].type != '*' && map[i][j].type != '#') {
                if (map[i][j].type == 'A') A = make_pair(i, j);
                else if (map[i][j].type == 'B') B = make_pair(i, j);
                else C = make_pair(i, j);
            }
        }
    }

    ////////////find roads////////

    bfs(A, 0);
    bfs(B, 1);
    bfs(C, 2);

    ////////find best path////////

    pair<int, pair<int, int>> minBlock = calculateMin();

    /////////output answer/////////

    result(minBlock);

    return 0;
}

/* sample input:
18 15
#**..*##*#**##*
*A##.**#.*.#**#
**.#*****#*.###
.**#*##*#.**###
.#.*#**.#.*#*#B
*.##*#**#***...
.***##*#**.*.**
###**#**#****.*
.**.**#**##.**.
**.*#*##**#***#
***.*#*.#**#...
##**.#****..**#
#**.***.#*##***
.*****#.***##**
*..#.*#.#***.#*
#****#.**..****
*#**#*#*...*.*#
*.**.C*.##*....
 */