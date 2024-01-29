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


void bfs(pair<int, int> source, int root) {
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
                if (itr.first == 2 && itr.second == 8 && root == 1)
                    cout << s.first << " " << s.second;
                dq.push_back(itr);
            }
        }
    }
}

void rowing(int i, int j, int root, char look) {
    while (map[i][j].type != look) {
        if (map[i][j].type == '*')
            map[i][j].type = 'o';
        if (root == 1)
            cout << i << " " << j << endl;
        if (map[i][j].distance[root] == 0) {
            break;
        }
            cout << i << " " << j << endl;
        i = map[i][j].road[root].first;
        j = map[i][j].road[root].second;
    }
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
            if (map[i][j].type != '.' && map[i][j].type != '*') {
                if (map[i][j].type == 'A') A = make_pair(i, j);
                else if (map[i][j].type == 'B') B = make_pair(i, j);
                else C = make_pair(i, j);
            }
        }
    }

    //////////////////////////////

    bfs(A, 0);
    bfs(B, 1);
    bfs(C, 2);

    //////////////////////////////

    int min = 100000;
    pair<int, int> minBlock;
    int distances;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            distances = map[i][j].distance[0] + map[i][j].distance[1] + map[i][j].distance[2];
            if (map[i][j].type == '*') distances -= 2;
            if (min > distances) {
                min = distances;
                minBlock = make_pair(i, j);
            }
        }
    }

    //////////////////////////////

    if (min < 100000) {
        cout << min << endl;
        int i = minBlock.first;
        int j = minBlock.second;
        rowing(i, j, 0, 'A');
        cout << 'A';
        rowing(i, j, 1, 'B');
        cout << 'A';
        rowing(i, j, 2, 'C');
        cout << 'A';
        printMap();
    } else cout << "CHRISTMAS RUINED!";

    return 0;
}
