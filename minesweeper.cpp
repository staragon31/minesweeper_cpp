#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <locale>
#include <windows.h>

using namespace std;


// для зручності

istream& operator>>(istream& o, vector<vector<int>> &a){
    for(int i = 0; i<a.size();i++)
        for(int j = 0; j<a[i].size(); j++)
            o>>a[i][j];
    return o;
}
ostream& operator<<(ostream& o, vector<vector<int>> &a){
    for(int i = 0; i<a.size();i++){
        for(int j = 0; j<a[i].size(); j++)
            o<<a[i][j]<<' ';
        o<<"\n";
    }
    return o;
}
ostream& operator<<(ostream& o, vector<vector<string>> &a){
    for(int i = 0; i<a.size();i++){
        for(int j = 0; j<a[i].size(); j++)
            o<<a[i][j]<<' ';
        o<<"\n";
    }
    return o;
}

ostream& operator<<(ostream& o, vector<int> &a){
    for(int i = 0; i<a.size();i++)
        o<<a[i]<<' ';
        o<<"\n";
    
    return o;
}


vector<vector<int>> Create_field(int n, int m, float diff)
{
    vector<vector<int>> a(n, vector<int>(m));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, n*m);

    int i = 0;
    while ( i < round(n*m*diff))
    {
        int ran = dist(gen);
        int nn = (ran-1)/m;
        int mm = (ran-1)%m;
        if (a[nn][mm] != -1){
            i++;
            a[nn][mm] = -1;
        }
    }
    for (int i = 0; i < n; i++)
        {
        for (int j = 0; j < m; j++)
            {
                int count = 0;
                if  (a[i][j] != -1)
                {
                if (i!=0)
                    if(a[i-1][j] == -1)
                        count++;
                if (j!=0)
                    if(a[i][j-1] == -1)
                        count++;
                if (i!=n-1)
                    if(a[i+1][j] == -1)
                        count++;
                if (j!=m-1)
                    if(a[i][j+1] == -1)
                    count++;
                if(i!=0 && j!=0)
                    if(a[i-1][j-1] == -1)
                        count++;
                if(i!=n-1 && j!=0)
                    if(a[i+1][j-1] == -1)
                        count++;
                if(i!=0 && j!=m-1)
                    if(a[i-1][j+1] == -1)
                        count++;
                if(i!=n-1 && j!=m-1)
                    if(a[i+1][j+1] == -1)
                        count++;
                a[i][j] = count;
                }
            }
        }
    return a;
}

void Click(vector<vector<int>>& M1, vector<vector<string>>& D1, int n, int m)
{
    if (to_string(M1[n][m]) != D1[n][m]){
        string res;
        if (M1[n][m] == -1) 
            res = "X";
        else
            res = to_string(M1[n][m]);
        D1[n][m] = res;
        if (M1[n][m] == 0){
            for (int i = n-1; i < n+2; i++)
            {
                for (int j = m-1; j < m+2; j++)
                {
                    if(i!=-1 && j!=-1 && i!=M1.size() && j!=M1[0].size())
                        Click(M1, D1, i,j);
                }
            }          
        }
    }
}


int main() {

    
    int n = 9;
    int m = 9;
    float df = 0.125;
    int choice;
    int choice2;
    int x = 0;
    int y = 0;
    while (true) {
        
        cout << "choose\n"
            << "1.play\n"
            << "2.change field\n"
            << "3.leave\n";
        cin>>choice;

        if (choice == 1){

            string res = " ";
            vector<vector<int>> M1 = Create_field(n, m, df);
            vector<vector<string>> D1(n, vector<string>(m));
            for(int i = 0; i<D1.size();i++)
                for(int j = 0; j<D1[i].size(); j++)
                    D1[i][j] = '*';
            cout << D1;
            while (res!="X"){
                cout <<"type width\n";
                cin >> x;
                cout <<"type height\n";
                cin >> y;
                if ( y>n && x>m){
                    cout<<"incorrect";
                    continue;
                }
                Click(M1, D1, y-1, x-1);
                cout << D1;
                if (D1[y][x] == "X"){
                    cout << "You lost\n";
                    break;
                }
            }
        }

        if (choice == 2)
        {
            cout << "choose difficulty\n"
                 <<"1 beginner\n"
                 << "2 intermediate\n"
                 << "3 expert\n"
                 << "4 custom\n";
            cin>>choice2;
                if (choice2 == 1){
                    n = 9;
                    m = 9;
                    df = 0.125;
                }
                if (choice2 == 2){
                     n = 16;
                     m = 16;
                     df = 0.157;
                }
                if (choice2 == 3){
                    n = 16;
                    m = 30;
                   df = 0.207;
                }
                if (choice2 == 4){
                    cout<<"type field width";
                    cin>>m;
                    cout<<"type field height";
                    cin>>n;
                    cout<<"type difficulty (from 0 to 1.0) \n exaple:\n 0.125 - beginner difficulty\n 0.207 - expert difficulty";
                    cin>>df;
                }
            }
    
        if (choice == 3){
            break;
        }
    }
}
