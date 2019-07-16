#define ll long long
#define HASH 98617
#define MAX 1e9
#define MIN -1e9
 
typedef struct _bb{
    ll t, len, base, ori, live, con[4];
}bb; bb bbarr[30001], srtbbarr[30001], hsm[HASH];
int tc = 0;
 
void init(int module[][4][4], bb A[30001]){
    for (int a = 0; a < 30000; a++){
        A[a].len = MIN, A[a].base = MAX, A[a].ori = 0, A[a].live = 1, A[a].t = tc;
        for (int b = 0; b < 4; b++) A[a].con[b] = 0;
        for (int b = 0; b < 4; b++) for (int c = 0; c < 4; c++){
            A[a].len = A[a].len > module[a][b][c] ? A[a].len : module[a][b][c];
            A[a].base = A[a].base < module[a][b][c] ? A[a].base : module[a][b][c];
        }
        ll tmp = 1;
        for (int b = 0; b < 4; b++) for (int c = 0; c < 4; c++){
            A[a].ori += (module[a][b][c] - A[a].base) * tmp;
            tmp *= 10;
        }
        tmp = 1;
        for (int b = 0; b < 4; b++) for (int c = 3; c >= 0; c--){
            A[a].con[0] += (A[a].len - module[a][b][c]) * tmp;
            tmp *= 10;
        }
        tmp = 1;
        for (int b = 0; b < 4; b++) for (int c = 0; c < 4; c++){
            A[a].con[1] += (A[a].len - module[a][c][b]) * tmp;
            tmp *= 10;
        }
        tmp = 1;
        for (int b = 3; b >= 0; b--) for (int c = 0; c < 4; c++){
            A[a].con[2] += (A[a].len - module[a][b][c]) * tmp;
            tmp *= 10;
        }
        tmp = 1;
        for (int b = 3; b >= 0; b--) for (int c = 3; c >= 0; c--){
            A[a].con[3] += (A[a].len - module[a][c][b]) * tmp;
            tmp *= 10;
        }
    }
}
 
void linsrt(bb A[], bb B[]){
    int idx = 0;
    for (int a = 1; a <= 8; a++){
        for (int b = 0; b < 30000; b++){
            if (A[b].len == a) B[idx++] = A[b];
        }
    }
}
 
int makeBlock(int module[][4][4]){
    tc++;
    init(module, bbarr);
    linsrt(bbarr, srtbbarr);
    int ans = 0;
    for (int a = 29999; a >= 0; a--){
        for (int b = 0; b < 4; b++){
            if (srtbbarr[a].live == 0) continue;
            ll mv = srtbbarr[a].con[b];
            for (int k = mv % HASH;; k = (k + 1) % HASH){
                if (hsm[k].t == tc && hsm[k].len > 0 && hsm[k].ori == mv && hsm[k].live == 1){
                    hsm[k].live = 0;
                    srtbbarr[a].live = 0;
                    ans += srtbbarr[a].len + hsm[k].base;
                    break;
                }
                else if (hsm[k].t != tc || hsm[k].len == 0) break;
            }   
        }
        if (srtbbarr[a].live == 1){
            for (int k = srtbbarr[a].ori % HASH;; k = (k + 1) % HASH){
                if (hsm[k].t != tc || hsm[k].len == 0){
                    hsm[k] = srtbbarr[a];
                    break;
                }
            }
        }
    }
    return ans;
}
