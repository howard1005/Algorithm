#include <iostream>
using namespace std;
int T, tc, H, W, bd[10][25], dp[10][25][59049], STEP;
int enc(int x){
    int ret = 0, e = 1;
    for (int y = 0; y < H; y++, e *= 3)  ret += bd[y][x] * e;
    return ret;
}
inline int dfs(int y, int x){
    if (y >= H - 1){
        x++, y = 0;
        if (x >= W - 1) return STEP;
    }
    int& ret = dp[y][x][enc(x)];
    if (ret >= STEP) return ret;
    int ret1 = STEP, ret2 = STEP;
    ret1 = dfs(y + 1, x);
    int flag = 1;
    for (int a = y; a < y + 2; a++) for (int b = x; b < x + 2; b++){
        if (a >= H || b >= W || bd[a][b]){
            flag = 0;
            break;
        }
    }   
    if (flag){
        bd[y][x] = bd[y + 1][x] = 1, bd[y][x + 1] = bd[y + 1][x + 1] = 2;
        ret2 = dfs(y + 1, x) + 1;
        bd[y][x] = bd[y + 1][x] = bd[y][x + 1] = bd[y + 1][x + 1] = 0;
    }
    return ret = ret1 < ret2 ? ret2 : ret1;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    for (tc = 1; tc <= T; tc++){
        cin >> H >> W;
        for (int a = 0; a < H; a++) for (int b = 0; b < W; b++) cin >> bd[a][b];
        STEP = tc * 1000;
        cout << "#" << tc << " " << dfs(0, 0) - STEP << "\n";
    }return 0;}
