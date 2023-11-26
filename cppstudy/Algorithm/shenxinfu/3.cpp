#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<int> ti, vector<int> si, int i, int sum, int time, int &temp, int &res){
    if (sum + ti[i] > time) {
        res = max(res, temp);
    }

    for (int j = i; j < ti.size()-1; ++j){
        sum = sum + ti[j];
        temp = temp + si[j];
        dfs(ti, si, j+1, sum, time, temp, res);
        sum = sum - ti[j];
        temp = temp - si[j];
    }
}

int main() {
    vector<int> ti, si;
    int time;
    string s1, s2, s3;
    cin >> s1; cin >> s2; cin >> s3;
    string s;
    for (int i = 0; i < s1.size(); ++i){
        if (s1[i] == ','){
            ti.push_back(atoi(s.c_str()));
            s = "";
        }else s = s + s1[i];
    }
    ti.push_back(atoi(s.c_str()));
    s = "";
    for (int i = 0; i < s2.size(); ++i){
        if (s2[i] == ','){
            si.push_back(atoi(s.c_str()));
            s = "";
        }else s = s + s2[i];
    }
    si.push_back(atoi(s.c_str()));
    time = atoi(s3.c_str());
    int res = 0, temp = 0;
    for (int i = 0; i < ti.size(); ++i){
        dfs(ti, si, i, 0, time, temp, res);
    }

    cout << res << endl;
}