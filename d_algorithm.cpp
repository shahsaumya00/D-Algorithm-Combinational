#include<iostream>  
#include<bits/stdc++.h> 
using namespace std;
//Global Variables
vector <int> d_path;
int i_gatedata[6];

// Intersection table
// C = conflict, E = ~D, N = no wire
char tc_intersection(char a, char b) {
    char out;
    switch(a) {
        case '0':
            switch(b) {
                case '0':
                    out = '0';
                    break;
                case '1':
                    out = 'C';
                    break;
                case 'x':
                    out = '0';
                    break;
                case 'D':
                    out = 'C';
                    break;
                case 'E':
                    out = 'C';
                    break;
                case 'N':
                    out = 'C';
                    break;
        }
        break;

        case '1':
            switch(b) {
            case '0':
                out = 'C';
                    break;
                case '1':
                    out = '1';
                    break;
                case 'x':
                    out = '1';
                    break;
                case 'D':
                    out = 'C';
                    break;
                case 'E':
                    out = 'C';
                    break;
                case 'N':
                    out = 'C';
                    break;
        }
        break;

        case 'x':
            switch(b) {
                    case '0':
                    out = '0';
                    break;
                case '1':
                    out = '1';
                    break;
                case 'x':
                    out = 'x';
                    break;
                case 'D':
                    out = 'D';
                    break;
                case 'E':
                    out = 'E';
                    break;
                case 'N':
                    out = 'C';
                    break;
            }
        break;

         case 'D':
            switch(b) {
                case '0':
                    out = 'C';
                    break;
                case '1':
                    out = 'C';
                    break;
                case 'x':
                    out = 'D';
                    break;
                case 'D':
                    out = 'D';
                    break;
                case 'E':
                    out = 'C';
                    break;
                case 'N':
                    out = 'C';
                    break;
            }
        break;
        case 'E':
            switch(b) {
                case '0':
                    out = 'C';
                    break;
                case '1':
                    out = 'C';
                    break;
                 case 'x':
                    out = 'E';
                    break;
                case 'D':
                    out = 'C';
                    break;
                case 'E':
                    out = 'E';
                    break;
                case 'N':
                    out = 'C';
                    break;
            }
            break;
        case 'N':
            switch(b) {
                case '0':
                    out = 'C';
                    break;
                case '1':
                    out = 'C';
                    break;
                 case 'x':
                    out = 'C';
                    break;
                case 'D':
                    out = 'C';
                    break;
                case 'E':
                    out = 'C';
                    break;
                case 'N':
                    out = 'C';
                    break;
            }
            break;
    }
    return out;
}

// To add an edge 
void addEdge(vector <pair<int, int> > adj[], int u, 
                                     int v, int wt) 
{ 
    adj[u].push_back(make_pair(v, wt));  
} 
  
// Print adjacency list representaion of graph 
void printGraph(vector<pair<int,int> > adj[], int V) 
{ 
    int v, w; 
    for (int u = 0; u < V; u++) 
    { 
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++) 
        { 
            v = it->first; 
            w = it->second; 

        } 
    } 
} 

// print the Test Cube
void print_tc(vector<vector<char>> tc)
{
    for (int i = 0; i < tc.size(); i++)
    {
        for (int j = 0; j < tc[i].size(); j++)
        {
//            cout << tc[i][j] << " ";
        }    
//        cout << endl;
    }
}

// obtain gate and wire information from adjacency list
void getgatedata(vector<pair<int,int> > adj[], int V, int e, int gate_type[])
{
    e = e+20;
    int v, w; 
    for (int u = 0; u < V; u++) 
    { 
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++) 
        { 
            v = it->first;
            w = it->second;
            if(w == e) {
                i_gatedata[0] = u;
                i_gatedata[1] = v;
                break;
            }
        }
    }
    int i = 2;
    int pi = 1;
    int po = 1;
    for (int u = 0; u < V; u++) 
    {
        for (auto it1 = adj[u].begin(); it1!=adj[u].end(); it1++) 
        { 
            v = it1->first;
            w = it1->second;
            
            if(v == i_gatedata[0]) {
                if(gate_type[i_gatedata[0]]==7) {
                    i_gatedata[2] = w-20;
                    i_gatedata[3] = w-20;
                    pi = 0;
                }
                else{
                    pi = 0;
                    i_gatedata[i] = w-20;
                    i++;
                }
            }
            if(u == i_gatedata[1]) {

                i_gatedata[4] = w-20;
                po = 0;
            }
            if(v == i_gatedata[1] && w != e) {
                i_gatedata[5] = w-20;
                po = 0;
            }
        }
        if(pi == 1) {
            i_gatedata[2] = -1;
            i_gatedata[3] = -1;
        }
        if(po == 1) {
            i_gatedata[4] = -1;
            i_gatedata[5] = -1;
        }
    } 
}

// obtain branch and wire information from adjacency list
vector<int> getbranchdata(vector<pair<int,int> > adj[], int V, int i, int u) {
    vector<int> branchdata;
    int w,v;
    branchdata.push_back(i);
    for (auto it = adj[u].begin(); it!=adj[u].end(); it++) 
    { 
        v = it->first;
        w = it->second;
        branchdata.push_back(w-20);
    }   
    return branchdata;
}

// find gates which are in D-frontier 
vector <pair<int, int> > dfunct(vector<vector<char>> tc,int gate_type [],int gatedata[][6]) {
    vector <pair<int, int> > dfrontier;
    for (int j = 0; j < tc[tc.size()-1].size(); j++)
    {
        if(tc[tc.size()-1][j] == 'D' || tc[tc.size()-1][j] == 'E') {
            if(gatedata[j][4] != -1 || gatedata[j][5] != -1) {
//                cout << "in if-if";
                if(tc[tc.size()-1][gatedata[j][4]] == 'x' && tc[tc.size()-1][gatedata[j][5]] == 'x') {
                    dfrontier.push_back(make_pair(gatedata[j][1],j));
                }
            }
        }
    }
    return dfrontier;
}

// find gates which are in J-frontier
vector <pair<int, int> > jfunct(vector<vector<char>> tc, int gate_type[], int gatedata[][6]) {
    vector <pair<int, int> > jfrontier;
    for (int j = 0; j < tc[tc.size()-1].size(); j++)
    {        
        if(tc[tc.size()-1][j] == '0' || tc[tc.size()-1][j] == '1') {
            if(gatedata[j][2] != -1 || gatedata[j][3] != -1) {  
                if(tc[tc.size()-1][gatedata[j][2]] == 'x' && tc[tc.size()-1][gatedata[j][3]] == 'x') {
                    jfrontier.push_back(make_pair(gatedata[j][0],j));
                }
            }
        } 
    }    
    return jfrontier;
}

vector<char> justify(vector<vector<char>> tmp_tc,char dcubes[8][12][3],int gate_type[], int gatedata[][6]) {
    // Get J frontier
    vector <pair<int, int> > jfrontier;
    int g2,e2;
    jfrontier = jfunct(tmp_tc, gate_type, gatedata);
    if(jfrontier.empty()) {
        return tmp_tc[tmp_tc.size()-1];
    }
    for (auto it = jfrontier.begin(); it!=jfrontier.end(); it++) {
        g2 = it->first;
        e2 = it->second;
    //Find suitable Singular covers
        vector<vector<char>> tmp_sc;
        for(int i=0; i<4; i++) {
            vector<char> vec_sc;
            if(tc_intersection(dcubes[gate_type[g2]][i][0],tmp_tc[tmp_tc.size()-1][gatedata[e2][2]]) != 'C' && 
            tc_intersection(dcubes[gate_type[g2]][i][1],tmp_tc[tmp_tc.size()-1][gatedata[e2][3]]) != 'C' && 
            dcubes[gate_type[g2]][i][2] == tmp_tc[tmp_tc.size()-1][e2]) {
                vec_sc = {tc_intersection(dcubes[gate_type[g2]][i][0],tmp_tc[tmp_tc.size()-1][gatedata[e2][2]]),
                                  tc_intersection(dcubes[gate_type[g2]][i][1],tmp_tc[tmp_tc.size()-1][gatedata[e2][3]]),
                                  dcubes[gate_type[g2]][i][2]};
                tmp_sc.push_back(vec_sc); 
            }
        }
            
        if(tmp_sc.empty()) {
            return {'0'};
        }
        vector<vector<char>> tmp2_tc;
        vector<char> tmp3_tc;
    // check whether assigned values are consistent or not
        while(!tmp_sc.empty()) {
            tmp_tc[tmp_tc.size()-1][gatedata[e2][2]] = tmp_sc[tmp_sc.size()-1][0];
            tmp_tc[tmp_tc.size()-1][gatedata[e2][3]] = tmp_sc[tmp_sc.size()-1][1];
            tmp_tc[tmp_tc.size()-1][e2] = tmp_sc[tmp_sc.size()-1][2];
            tmp_tc.push_back(tmp_tc[tmp_tc.size()-1]);
            tmp_sc.pop_back();
            tmp2_tc = tmp_tc;
            for (auto it = jfrontier.begin(); it!=jfrontier.end(); it++) {
                int e = it->second;
                if(e != e2) {
                    tmp2_tc[tmp_tc.size()-1][e] = 'x';
                }                
            } 
            tmp3_tc = justify(tmp2_tc,dcubes,gate_type,gatedata);
            if(tmp3_tc.size()==1) {
                if(tmp_tc.empty()) {
                    return {'0'};
              
                }
                else{
                    tmp_tc.pop_back();
                }
            }
            else {
                vector<char> vect_tc;
                for(int i=0; i<tmp_tc[tmp_tc.size()-1].size(); i++) {
                    vect_tc.push_back(tc_intersection(tmp_tc[tmp_tc.size()-1][i],tmp3_tc[i]));
                }
                tmp_tc.push_back(vect_tc);              
            }
        }
    }    
return tmp_tc[tmp_tc.size()-1];
}

// reference dalgo function
vector<char> dalgo(vector<vector<char>> tc, int num_out, int gate_type[],char dcubes[8][12][3],int gatedata[][6],vector<vector<int>> branchdata);

// function to run D algo once branch detected
vector<char> D_algo(vector<vector<char>> tc, int num_out, int gate_type[],char dcubes[8][12][3],int gatedata[][6], vector<vector<int>> branchdata) {        
    vector <pair<int, int> > dfrontier = dfunct(tc,gate_type,gatedata);

    //Base condition: If dfrontier is empty and fault has reached PO, return tc. If dfrontier is empty and fault hasn't reached PO, return 0 which indicates that fault is untestable.
    int flag = 0;
    if(dfrontier.empty()){
        for(int i = tc[tc.size()-1].size() - num_out; i < tc[tc.size()-1].size(); i++) {
            if (tc[tc.size()-1][i] == 'D' || tc[tc.size()-1][i] == 'E') {
                flag = 1;
            }
        }
        if(!flag){
            return {'0'};
        }           
        else {
            return tc[tc.size()-1]; 
        }
                 
    }

    vector<vector<char>> dtmp_tc;
    dtmp_tc.push_back(tc[tc.size()-1]);
    int g1,e1;
    int flag1 = 0;
    for (auto it = dfrontier.begin(); it!=dfrontier.end(); it++) { 
        //PDC
        vector<vector<char>> tmp_pdc; 
        g1 = it->first;
        e1 = it->second; 
        for(int i=8; i<12; i++) {
            if(dcubes[gate_type[g1]][i][0] == dtmp_tc[dtmp_tc.size()-1][e1]) {
                tmp_pdc.push_back({dcubes[gate_type[g1]][i][0],dcubes[gate_type[g1]][i][1],dcubes[gate_type[g1]][i][2]});
            }
        }
        for(int i = 0; i< tmp_pdc.size();i++) {

        }
        while(!tmp_pdc.empty()) {
            dtmp_tc[dtmp_tc.size()-1][e1] = tmp_pdc[tmp_pdc.size()-1][0];
            dtmp_tc[dtmp_tc.size()-1][gatedata[e1][5]] = tmp_pdc[tmp_pdc.size()-1][1];
            dtmp_tc[dtmp_tc.size()-1][gatedata[e1][4]] = tmp_pdc[tmp_pdc.size()-1][2];
            tmp_pdc.pop_back();
        // Calling Justify
            vector<char> out_tmp; 
            out_tmp= justify(dtmp_tc,dcubes,gate_type,gatedata);

            if(out_tmp.size()!=1) {
                dtmp_tc.push_back(out_tmp);
                flag1 = 1;
                break;
            }
            else {
            }
        }
        if(flag1)
            break;
    }
    if(flag1) {
        tc[tc.size()-1] = dalgo(dtmp_tc,num_out,gate_type,dcubes,gatedata,branchdata);
        tc.push_back(tc[tc.size()-1]);
        return tc[tc.size()-1];
        
    }
    else {
        return {'0'};
    }
return {'0'};
}
// function for D algo
vector<char> dalgo(vector<vector<char>> tc, int num_out, int gate_type[],char dcubes[8][12][3],int gatedata[][6],vector<vector<int>> branchdata) {
    //GET D FRONTIER
    vector<int> b_data;
    char assgn;
    int branch=0;
    for(int i=0;i<tc[tc.size()-1].size();i++) {
        if(tc[tc.size()-1][i] == 'D' || tc[tc.size()-1][i] == 'E') {
            if(gate_type[gatedata[i][1]] == 7) {
                for(int j=0;j<branchdata.size();j++) {
                    if(branchdata[j][0]==i) {
                        int all_x = 1;
                        for(int k=1;k<b_data.size();k++) {
                            if(tc[tc.size()-1][b_data[k]] != 'x') {
                                all_x = 0;
                            }
                        } 
                        if(all_x) {
                            branch = 1;
                            b_data = branchdata[j];
                            assgn = tc[tc.size()-1][b_data[0]];
                            if(!b_data.empty())
                                b_data.erase(b_data.begin());                            
                        } 
                    }
                }
            }
        }
    }

    vector<char> out_final;
    
    if(branch) {
        int flag2 =0;
        while(!b_data.empty()) {
            tc.push_back(tc[tc.size()-1]);
            tc[tc.size()-1][b_data[b_data.size()-1]] = assgn;
            b_data.pop_back();
            out_final = D_algo(tc,num_out,gate_type,dcubes,gatedata,branchdata);
            if(out_final.size()!=1) {
                flag2 = 1;
                tc.push_back(out_final);
                return tc[tc.size()-1];
            }
            else {
                tc.pop_back();
            }
        }
        if(!flag2) {
            return {'0'};
        }
            
    }
    else {

        out_final = D_algo(tc,num_out,gate_type,dcubes,gatedata,branchdata);
        if(out_final.size()==1) {
            return {'0'};
        }
        else {
            tc.push_back(out_final);
            return tc[tc.size()-1];
        }
    }   
return {'0'};
}

int main() {

    // Input
    // Graph

    int V;
    int edge;
    int u,n,w;
    int var;
    cin >> var;
    
   
    vector <vector<int>> gate_type_tmp;
    if(var == 2) {
        V = 16;
        edge = 16;
    }
    else if(var ==1) {
        V = 8;
        edge = 8;
    }
    else if(var == 3) {
        V = 16;
        edge = 16;
    }
    else if(var ==4) {
        V = 8;
        edge = 8;
    }
    else if(var ==5) {
        V = 16;
        edge = 16;
    }
    vector<pair<int, int> > adj[V];  
    int gate_type[V];     
    if(var == 2) {      
        addEdge(adj, 0, 8, 20); 
        addEdge(adj, 1, 6, 21); 
        addEdge(adj, 2, 9, 22); 
        addEdge(adj, 3, 11, 23); 
        addEdge(adj, 4, 11, 24); 
        addEdge(adj, 5, 13, 25); 
        addEdge(adj, 6, 8, 26);
        addEdge(adj, 6, 9, 27); 
        addEdge(adj, 7, 12, 31); 
        addEdge(adj, 7, 13, 32); 
        addEdge(adj, 8, 10, 28); 
        addEdge(adj, 9, 10, 29); 
        addEdge(adj, 10, 7, 30);
        addEdge(adj, 11, 12, 33);
        addEdge(adj, 12, 14, 34);
        addEdge(adj, 13, 15, 35);
        printGraph(adj, V);
        gate_type_tmp.push_back({-1,-1,-1,-1,-1,-1,7,7,0,1,2,2,0,0,-2,-2});  
    }
    else if(var ==1) {
        addEdge(adj, 0, 4, 20); 
        addEdge(adj, 1, 3, 21); 
        addEdge(adj, 2, 5, 22); 
        addEdge(adj, 3, 4, 23); 
        addEdge(adj, 3, 5, 24); 
        addEdge(adj, 4, 6, 25); 
        addEdge(adj, 5, 6, 26);
        addEdge(adj, 6, 7, 27);
        printGraph(adj, V); 
        gate_type_tmp.push_back({-1,-1,-1,7,0,1,3,-2});
    }
    else if(var == 3) {      
        addEdge(adj, 0, 8, 20); 
        addEdge(adj, 1, 6, 21); 
        addEdge(adj, 2, 9, 22); 
        addEdge(adj, 3, 11, 23); 
        addEdge(adj, 4, 11, 24); 
        addEdge(adj, 5, 13, 25); 
        addEdge(adj, 6, 8, 26);
        addEdge(adj, 6, 9, 27); 
        addEdge(adj, 7, 12, 31); 
        addEdge(adj, 7, 13, 32); 
        addEdge(adj, 8, 10, 28); 
        addEdge(adj, 9, 10, 29); 
        addEdge(adj, 10, 7, 30);
        addEdge(adj, 11, 12, 33);
        addEdge(adj, 12, 14, 34);
        addEdge(adj, 13, 15, 35);
        printGraph(adj, V);
        gate_type_tmp.push_back({-1,-1,-1,-1,-1,-1,7,7,0,1,4,2,0,0,-2,-2});  
    }
    else if(var == 4) {
        addEdge(adj, 0, 4, 20); 
        addEdge(adj, 1, 3, 21); 
        addEdge(adj, 2, 5, 22); 
        addEdge(adj, 3, 4, 23); 
        addEdge(adj, 3, 5, 24); 
        addEdge(adj, 4, 6, 25); 
        addEdge(adj, 5, 6, 26);
        addEdge(adj, 6, 7, 27);
        printGraph(adj, V); 
        gate_type_tmp.push_back({-1,-1,-1,7,5,1,3,-2});
    }
    else if(var == 5) {      
        addEdge(adj, 0, 8, 20); 
        addEdge(adj, 1, 6, 21); 
        addEdge(adj, 2, 9, 22); 
        addEdge(adj, 3, 11, 23); 
        addEdge(adj, 4, 11, 24); 
        addEdge(adj, 5, 13, 25); 
        addEdge(adj, 6, 8, 26);
        addEdge(adj, 6, 9, 27); 
        addEdge(adj, 7, 12, 31); 
        addEdge(adj, 7, 13, 32); 
        addEdge(adj, 8, 10, 28); 
        addEdge(adj, 9, 10, 29); 
        addEdge(adj, 10, 7, 30);
        addEdge(adj, 11, 12, 33);
        addEdge(adj, 12, 14, 34);
        addEdge(adj, 13, 15, 35);
        printGraph(adj, V);
        gate_type_tmp.push_back({-1,-1,-1,-1,-1,-1,7,7,0,2,4,2,5,1,-2,-2});  
    }

    for(int i=0;i<V;i++) {
        if(!gate_type_tmp.empty())
            gate_type[i] = gate_type_tmp[gate_type_tmp.size()-1][i];
    }
    
    


      
//    int fault_net = 6;
//    char fault = 'D';
//============================================================================
//Code
// storing D cubes
// and nand or nor xor xnor not branch
// 0   1    2  3   4   5    6   7
// sc pdcf pdc
    char dcubes [8][12][3] = {
                         {{'0','x','0'},{'x','0','0'},{'1','1','1'},{'N','N','N'},{'1','1','D'},{'0','x','E'},{'x','0','E'},{'N','N','N'},{'E','1','E'},{'D','1','D'},{'N','N','N'},{'N','N','N'}},
                         {{'0','x','1'},{'x','0','1'},{'1','1','0'},{'N','N','N'},{'1','1','E'},{'0','x','D'},{'x','0','D'},{'N','N','N'},{'E','1','D'},{'D','1','E'},{'N','N','N'},{'N','N','N'}},
                         {{'0','0','0'},{'x','1','1'},{'1','x','1'},{'N','N','N'},{'0','0','E'},{'x','1','D'},{'1','x','D'},{'N','N','N'},{'E','0','E'},{'D','0','D'},{'N','N','N'},{'N','N','N'}},
                         {{'0','0','1'},{'x','1','0'},{'1','x','0'},{'N','N','N'},{'0','0','D'},{'x','1','E'},{'1','x','E'},{'N','N','N'},{'E','0','D'},{'D','0','E'},{'N','N','N'},{'N','N','N'}},    
                         {{'0','0','0'},{'0','1','1'},{'1','0','1'},{'1','1','0'},{'0','1','D'},{'1','0','D'},{'0','0','E'},{'1','1','E'},{'E','0','E'},{'D','0','D'},{'D','1','E'},{'E','1','D'}},    
                         {{'0','0','1'},{'0','1','0'},{'1','0','0'},{'1','1','1'},{'0','0','D'},{'1','1','D'},{'0','1','E'},{'1','0','E'},{'E','0','D'},{'D','0','E'},{'D','1','D'},{'E','1','E'}},
                         {{'0','N','1'},{'1','N','0'},{'N','N','N'},{'N','N','N'},{'0','N','D'},{'1','N','E'},{'N','N','N'},{'N','N','N'},{'D','N','E'},{'E','N','D'},{'N','N','N'},{'N','N','N'}},
                         {{'0','0','0'},{'1','1','1'},{'N','N','N'},{'N','N','N'},{'0','0','E'},{'1','1','D'},{'N','N','N'},{'N','N','N'},{'D','D','D'},{'E','E','E'},{'N','N','N'},{'N','N','N'}}
                        }; 
    
    int fault_net;
    char fault;
    char faults[2] = {'D','E'};

    for(int j=0;j<2;j++) { 
        for (int i=0;i<edge;i++) {
            cout << "s-a-" << j << " Fault at w" << i +20 << endl;
            fault = faults[j];
            fault_net = i;
            //Initialization
            vector<vector<char>> tc;
            for (int i =0; i < 1; i++) {
                vector<char> v;
                for (int j = 0; j<edge; j++) {            
                    v.push_back('x');      
                }
                tc.push_back(v);
            }
            tc.push_back(tc[tc.size()-1]);
            
            // Fault assignment
            int gatedata[edge][6];
            for (int i=0;i<edge;i++) {
                for(int j=0;j<6;j++) {
                    gatedata[i][j] = 0;
                }
            }

            for (int i=0; i<edge; i++) {
                getgatedata(adj, V, i, gate_type);
                for(int j=0;j<6;j++) {
                    gatedata[i][j] = i_gatedata[j];
                }
            } 


            vector<vector<int>> branchdata;
            for(int e=0; e<edge; e++) {
                if(gate_type[gatedata[e][1]]==7) {
                    branchdata.push_back(getbranchdata(adj, V, e,gatedata[e][1]));
                }
            }
            tc[tc.size()-1][fault_net] = fault;
            tc.push_back(tc[tc.size()-1]);

            //PDCF

            for(int i = 4; i < 8; i++) {
                if(dcubes[gate_type[gatedata[fault_net][0]]][i][2] == tc[tc.size()-1][fault_net]) {
                    tc[tc.size()-1][gatedata[fault_net][2]] = dcubes[gate_type[gatedata[fault_net][0]]][i][0];
                    tc[tc.size()-1][gatedata[fault_net][3]] = dcubes[gate_type[gatedata[fault_net][0]]][i][1];
                }
            }
            tc.push_back(tc[tc.size()-1]);

            // D algo 
            int num_out = 0;   
            for(int i =0; i<V;i++) {
                if(gate_type[i]==-2) {
                    num_out++;
                }
            }
            int num_in = 0;
            for(int j =0; j<V;j++) {
                if(gate_type[j]==-1) {
                    num_in++;
                }
            }

            vector<char> out(edge);
            out = dalgo(tc,num_out,gate_type,dcubes,gatedata,branchdata);
            if (out.size()==1) {
                cout << "FAULT UNTESTABLE" << endl;
            }
            else {
                
                tc[tc.size()-1] = out;
                cout << "TEST COMPLETED" << endl;
                cout << "Test Vector" << ": ";
                for(int i=0;i<num_in;i++) {
                    if(tc[tc.size()-1][i] == 'D') {
                       cout << 1 << " "; 
                    }                        
                    else if(tc[tc.size()-1][i] == 'E') {
                        cout << 0 << " ";
                    }
                    else {
                        cout << tc[tc.size()-1][i] << " ";
                    }
                    
                }
                cout << "" << endl; 
                cout << "PATH (EdgeNumber-[GateNumber]): ";
                for(int i=0;i<tc[tc.size()-1].size();i++) {
                    if(tc[tc.size()-1][i]=='D' || tc[tc.size()-1][i]=='E') {
                        cout << i + 20 << "-[" << gatedata[i][1] << "]-";
                    }
                }
            }

           
            cout << "" << endl;                


        }   
    }

    return 0;
}