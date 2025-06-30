#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
int n, m;
char maze[MAXN][MAXN];
bool visited[MAXN][MAXN];
pair<int, int> parent[MAXN][MAXN];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
pair<int, int> start, end_pos;

bool isValid(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= m) return false;
    if (maze[x][y] == '0' || visited[x][y]) return false;
    return true;
}

void bfs() {
    queue<pair<int, int>> q;
    visited[start.first][start.second] = true;
    q.push(start);

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();
        if (cur == end_pos) break;

        for (int i = 0; i < 4; ++i) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                parent[nx][ny] = cur;
                q.push({nx, ny});
            }
        }
    }
}

bool dfs(int x, int y) {
    if (!isValid(x, y)) return false;
    visited[x][y] = true;
    if (make_pair(x, y) == end_pos) return true;

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (!visited[nx][ny]) {
            parent[nx][ny] = {x, y};
            if (dfs(nx, ny)) return true;
        }
    }
    return false;
}

void reconstructPath(pair<int, int> end_point) {
    pair<int, int> cur = end_point;
    while (cur != start) {
        if (maze[cur.first][cur.second] != 'E')
            maze[cur.first][cur.second] = '*';
        cur = parent[cur.first][cur.second];
    }
    maze[start.first][start.second] = 'S';
}

void printMaze() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << maze[i][j];
        }
        cout << '\n';
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> maze[i][j];
            if (maze[i][j] == 'S') start = {i, j};
            if (maze[i][j] == 'E') end_pos = {i, j};
        }
    }

    bfs();
    dfs(start.first, start.second);

    reconstructPath(end_pos);
    printMaze();

    return 0;
}
