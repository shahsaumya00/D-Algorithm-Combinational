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
        cout << "gate " << u << " leads to gate "; 
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++) 
        { 
            v = it->first; 
            w = it->second; 
            cout << "\tNode " << v << " via wire"
                 << w << " "; 
        } 
        cout << "\n"; 
    } 
} 

// print the Test Cube
void print_tc(vector<vector<char>> tc)
{
    for (int i = 0; i < tc.size(); i++)
    {
        for (int j = 0; j < tc[i].size(); j++)
        {
            cout << tc[i][j] << " ";
        }    
        cout << endl;
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

// justify input of gates which are in J-frontier
vector<char> justify(vector<vector<char>> tmp_tc,char dcubes[8][12][3],int gate_type[], int gatedata[][6]) {
    vector <pair<int, int> > jfrontier;
//    int justify_call = func_call;
    int g2,e2;
    jfrontier = jfunct(tmp_tc, gate_type, gatedata);
//    cout << "jfrontier" << ": ";
    for(auto i=jfrontier.begin();i<jfrontier.end();i++) {
        cout << i->first << " ";
    }
    cout << "" << endl;
    if(jfrontier.empty()) {
        cout << "jfrontier = empty" << endl;
        return tmp_tc[tmp_tc.size()-1];
    }
    for (auto it = jfrontier.begin(); it!=jfrontier.end(); it++) {
        g2 = it->first;
        e2 = it->second;
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

        while(!tmp_sc.empty()) {
            cout << "in while - justify" << endl;
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
            cout << "calling justify from justify" << endl;
            tmp3_tc = justify(tmp2_tc,dcubes,gate_type,gatedata);
            cout << "returning from justify to justify" << endl;
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
    cout << "dfrontier" <<  " ";
    cout << dfrontier.size() << endl;

    //Base condition
    int flag = 0;
    if(dfrontier.empty()){
        cout << "in base condition" << endl;
        for(int i = tc[tc.size()-1].size() - num_out; i < tc[tc.size()-1].size(); i++) {
            cout << i << " " << tc[tc.size()-1][i] << endl;
            if (tc[tc.size()-1][i] == 'D' || tc[tc.size()-1][i] == 'E') {
                flag = 1;
            }
        }
        cout << flag << endl;
        if(!flag){
            cout << "returning 0  --1" << endl;
            return {'0'};
        }           
        else {
            cout << "returning tc  --2" << endl;
            return tc[tc.size()-1]; 
        }
                 
    }
    //Pick 1 gate  in dfrontier
    //DEFINE TMP_TC

    vector<vector<char>> dtmp_tc;
    dtmp_tc.push_back(tc[tc.size()-1]);
    int g1,e1;
    int flag1 = 0;
    for (auto it = dfrontier.begin(); it!=dfrontier.end(); it++) { 
        cout << "inside loop:dfrontier" << endl;
        vector<vector<char>> tmp_pdc; 
        g1 = it->first;
        e1 = it->second; 
//        d_path.push_back(e1);
        cout << "push_back: d_path" << e1 << endl;
        cout << g1 << endl;
        for(int i=8; i<12; i++) {
            if(dcubes[gate_type[g1]][i][0] == dtmp_tc[dtmp_tc.size()-1][e1]) {
                tmp_pdc.push_back({dcubes[gate_type[g1]][i][0],dcubes[gate_type[g1]][i][1],dcubes[gate_type[g1]][i][2]});
            }
        }
        for(int i = 0; i< tmp_pdc.size();i++) {
            for(int j=0;j<3;j++) {
                cout << tmp_pdc[i][j] << " ";
            }
            cout << "" << endl;
        }
        cout << "stored tmp_pdc" << endl;
        while(!tmp_pdc.empty()) {
            cout << "in while" << endl;
            dtmp_tc[dtmp_tc.size()-1][e1] = tmp_pdc[tmp_pdc.size()-1][0];

            cout << "before" << gatedata[e1][5] << " " << dtmp_tc[dtmp_tc.size()-1][gatedata[e1][5]] << " " << tmp_pdc[tmp_pdc.size()-1][1] << endl;

            dtmp_tc[dtmp_tc.size()-1][gatedata[e1][5]] = tmp_pdc[tmp_pdc.size()-1][1];

            cout << "after" << gatedata[e1][5] << " " << dtmp_tc[dtmp_tc.size()-1][gatedata[e1][5]] << " " << tmp_pdc[tmp_pdc.size()-1][1] << endl;

            dtmp_tc[dtmp_tc.size()-1][gatedata[e1][4]] = tmp_pdc[tmp_pdc.size()-1][2];

            tmp_pdc.pop_back();

            cout << "calling justify from dalgo" << endl;
            print_tc(dtmp_tc);
            vector<char> out_tmp; 
            out_tmp= justify(dtmp_tc,dcubes,gate_type,gatedata);
            cout << "returning to dalgo from justify" << endl;

            if(out_tmp.size()!=1) {
                dtmp_tc.push_back(out_tmp);
                flag1 = 1;
                break;
            }
            else {
//                cout << "pop_back: d_path" << d_path[d_path.size()-1] << endl;
//                d_path.pop_back();
            }
        }
        if(flag1)
            break;
    }
    if(flag1) {
        cout << "calling dalgo from D_algo" << endl;
        tc[tc.size()-1] = dalgo(dtmp_tc,num_out,gate_type,dcubes,gatedata,branchdata);
        cout << "returning from dalgo to D_algo" << endl;
        tc.push_back(tc[tc.size()-1]);
        cout << "returing tc --3" << endl;
        return tc[tc.size()-1];
        
    }
    else {
        cout << "returning 0 --4" << endl;
        return {'0'};
    }
cout << "returning 0 -extra" << endl;
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
                    cout << branchdata[j][0] << endl;
                    if(branchdata[j][0]==i) {
                        int all_x = 1;
                        for(int k=1;k<b_data.size();k++) {
                            if(tc[tc.size()-1][b_data[k]] != 'x') {
                                all_x = 0;
                            }
                        } 
                        cout << "" << endl; 
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
//            cout << "push_back: d_path" << b_data[b_data.size()-1] << endl; 
//            d_path.push_back(b_data[b_data.size()-1]);
            b_data.pop_back();
            cout << "tc-branch" << endl;
            cout << "calling D_algo from dalgo-branch" << endl;
            out_final = D_algo(tc,num_out,gate_type,dcubes,gatedata,branchdata);
            cout << "returning from D_algo to dalgo-branch" << endl;
            cout << out_final.size() << endl;
            if(out_final.size()!=1) {
                flag2 = 1;
                tc.push_back(out_final);
                return tc[tc.size()-1];
            }
            else {
                tc.pop_back();
//                cout << "pop_back: d_path" << d_path[d_path.size()-1] << endl;
//                d_path.pop_back();
            }
            //call function
        }
        if(!flag2) {
            cout << "returning 0 --5" << endl;
            return {'0'};
        }
            
    }
    else {
//        call function

        cout << "calling D_algo from dalgo-nonbranch" << endl;
        out_final = D_algo(tc,num_out,gate_type,dcubes,gatedata,branchdata);
        cout << "returning from D_algo to dalgo-nonbranch" << endl;
        if(out_final.size()==1) {
            cout << "returning 0  --6" << endl;
            return {'0'};
        }
        else {
            cout << "returning tc --7" << endl;
            tc.push_back(out_final);
            return tc[tc.size()-1];
        }
    }   
cout << "returning 0  --8" << endl;
return {'0'};
}

int main() {

    // Input
    // Graph
    int V,edge;
    cout << "Enter the Number of Vertices: ";
    cin >> V;
    cout << "Enter the Number of Edges: ";
    cin >> edge;
    vector<pair<int, int> > adj[V];

    int u,n,w;
    cout << "Enter u v w:";
    for(int i=0; i<V; i++) {
        cin >> u >> n >> w;
        addEdge(adj,u,n,w);
    }
    printGraph(adj, V);

//    int V = 17;
//    int edge = 17;
 
/*  addEdge(adj, 2, 7, 22); 
    addEdge(adj, 1, 9, 21); 
    addEdge(adj, 7, 9, 29); 
    addEdge(adj, 3, 10, 23); 
    addEdge(adj, 9, 12, 34);
    addEdge(adj, 4, 11, 24); 
    addEdge(adj, 5, 11, 25);
    addEdge(adj, 6, 14, 26); 
    addEdge(adj, 7, 10, 28);
    addEdge(adj, 10, 12, 27); 
    addEdge(adj, 8, 13, 32); 
    addEdge(adj, 11, 13, 31);    
    addEdge(adj, 8, 14, 33); 
    addEdge(adj, 13, 15, 35);
    addEdge(adj, 14, 16, 36); 
    addEdge(adj, 12, 8, 30);  */

/*  2, 7, 22 
    1, 9, 21 
    7, 9, 29 
    3, 10, 23 
    9, 12, 34);
    addEdge(adj, 4, 11, 24); 
    addEdge(adj, 5, 11, 25);
    addEdge(adj, 6, 14, 26); 
    addEdge(adj, 7, 10, 28);
    addEdge(adj, 10, 12, 27); 
    addEdge(adj, 8, 13, 32); 
    addEdge(adj, 11, 13, 31);    
    addEdge(adj, 8, 14, 33); 
    addEdge(adj, 13, 15, 35);
    addEdge(adj, 14, 16, 36); 
    addEdge(adj, 12, 8, 30);  */


    int gate_type[V];
    int gatetype;
    cout << "Enter gate type:";
    for(int i=0;i<V;i++) {
        cin >> gatetype;
        gate_type[i] = gatetype;
    }

//    int gate_type[V] = {-1,-1,-1,-1,-1,-1,-1,7,7,0,1,2,2,0,0,-2,-2};  
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
            cout << faults[j] << " Fault at line " << i << endl;
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
            cout << endl;
            // Fault assignment
            // Get gate numbers for pdcf(0) and pdc(1)
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

            for(int i=0;i<edge;i++) {
                cout << i << ": ";
                for(int j=0;j<6;j++) {
                    cout  << gatedata[i][j] << " ";
                }
                cout << "" << endl;
            }

            vector<vector<int>> branchdata;
            for(int e=0; e<edge; e++) {
                if(gate_type[gatedata[e][1]]==7) {
                    branchdata.push_back(getbranchdata(adj, V, e,gatedata[e][1]));
                }
            }

            for(int i=0;i<branchdata.size();i++) {
                    for (int j=0;j<branchdata[i].size();j++) {
                    cout << branchdata[i][j] << " ";
                }
                cout << "" << endl;
            }

            cout << "" << endl;
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
            print_tc(tc);
            cout << "============" << endl;

            // D algo 
            int num_out = 0;   
            for(int i =0; i<V;i++) {
                if(gate_type[i]==-2) {
                    num_out++;
                }
            }
            int num_in = 0;
            cout << "num input" << " ";
            for(int j =0; j<V;j++) {
                if(gate_type[j]==-1) {
                    cout << j << " ";
                    num_in++;
                }
            }
            cout << num_in << endl;

            vector<char> out(edge);
            cout << "calling dalgo from main" << endl;
            out = dalgo(tc,num_out,gate_type,dcubes,gatedata,branchdata);
            cout << "returning from dalgo to main" << endl;
            if (out.size()==1) {
                cout << "FAULT UNTESTABLE" << endl;
            }
            else {
                
                tc[tc.size()-1] = out;
                print_tc(tc);
                cout << "TEST COMPLETED" << endl;
                cout << "Test Vector" << ": ";
                for(int i=0;i<num_in;i++) {
                    cout << tc[tc.size()-1][i] << " ";
                }
                cout << "" << endl; 
                cout << "PATH (EdgeNumber-[GateNumber]): ";
                for(int i=0;i<tc[tc.size()-1].size();i++) {
                    if(tc[tc.size()-1][i]=='D' || tc[tc.size()-1][i]=='E') {
                        cout << i << "-[" << gatedata[i][1] << "]-";
                    }
                }
            }

            /*    for(int i=0;i<d_path.size();i++) {
                cout << d_path[i] << "[" << gatedata[d_path[i]][1] << "]" << " " ;
            }
            cout << "" << endl;*/



            cout << "" << endl;
        
                
        
        }   
    }

    return 0;
}