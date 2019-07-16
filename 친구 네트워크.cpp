#include <iostream>
using namespace std;
#define MOD 200003

int T, tc, N;

typedef struct _gr { // 그룹
    int cnt, par;
}; _gr gr[MOD];
int gri; 

typedef struct _fri { // 해쉬 테이블
    char name[21];
    int g_num;
    _fri *next;
    _fri() : g_num(0), next(nullptr) {}
    ~_fri() { delete next; }
}; _fri fri[MOD];

void strcpy(char *dst, char *src) {// str 복사
    for (; *src != '\0'; src++, dst++) {
        *dst = *src;
    }
    *dst = '\0';
}
int strcmp(char *dst, char *src) {// str 비교 다르면 0 같으면 1
    for (; *src != '\0'; src++, dst++) {
        if (*dst != *src) return 0;
    }
    return 1;
}

int hf(char *S) { // 해쉬 함수
    int ret = 0, exp = 1;
    for (; *S != '\0'; S++, exp = (exp *2) % MOD) {
        ret = (ret + exp * (*S)) % MOD;
    }
    return ret;
}

int fik(char* S){// 찾아서 없으면 넣어주고 group num return
    _fri *head = &fri[hf(S)]; // head는 _fri 포인트 객체 : 포인트 객체는 소멸자 실행X(동적 할당 포함)
    while (1) {
        if (head->next == nullptr){
            head->next = new _fri();
            head->next->g_num = gri++;
            strcpy(head->next->name, S); 
            return head->next->g_num;
        }
        else if (strcmp(head->next->name, S)){
            return head->next->g_num;
        }
        else{
            head = head->next;
        }
    }
}

int p_find(int gn){ // parent 찾기
    if (gr[gn].par == gn) return gn;
    return gr[gn].par = p_find(gr[gn].par);
}
int uni(int gn1, int gn2){ // union find
    int pgn1 = p_find(gn1);
    int pgn2 = p_find(gn2);

    if (pgn1 != pgn2){
        gr[pgn2].par = pgn1;
        return gr[pgn1].cnt += gr[pgn2].cnt;
    }
    else return gr[pgn1].cnt;
}

void solve(){
    cin >> T;
    for (tc = 1; tc <= T; tc++) {
        cin >> N;
        gri = 1;
        for (int a = 0; a <= N; a++) gr[a].par = a, gr[a].cnt = 1;
        for (int a = 0; a < MOD; a++){
            delete fri[a].next;
            fri[a].next = nullptr;
        }
        char name1[21], name2[21];
        for (int a = 0; a < N; a++) {
            cin >> name1 >> name2;
            cout << uni(fik(name1), fik(name2)) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
