#include<bits/stdc++.h>


using namespace std;


string returnMode(int index){
    if(index == 0)
        return "CAB";

    else if(index == 1)
        return "METRO";
    
    else if(index == 2)
        return "BUS";
      
    else
        return "UNDEFINED-MODE";
}

void print_result(float result, vector<pair<int,int>> &parent, int source, int destination, string &criterion){

    cout << endl << endl << endl;
    cout << "Optimal Route as per " << criterion << " from " << source <<" (source) to " << destination << " (destination) is ==>   ";
    cout << result << endl << endl;

    stack<pair<int,int>> route;

    int par = destination;
    while(parent[par].first != -1){
        
        route.push(make_pair(parent[par].first,parent[par].second));
        par = parent[par].first;
    }


    cout << endl << " +-----   Route from " << source <<" (source)  to " << destination << " (destination)    --------+" << endl << endl;

    while(!route.empty()){

        cout << "From  : " << route.top().first << "   [using : " << returnMode(route.top().second);
        cout << "]     Towards : ";

        route.pop();

        if(route.empty()){
            break;
        }
        cout << route.top().first << endl;
    }
    cout << destination ;
    cout << endl << endl;

}



float dijkstra(vector<vector<vector<int>>> &graph,int source,int destination,vector<float>& ratio,vector<pair<int,int>> &parent){
    

    // <weight,<mode,source> >
    set<pair<float,pair<int,int>>>st;

    

// for 3rd dimension => 0: cab, 1: metro, 2: bus;

    // inserting for 0 => cab
    st.insert(make_pair(0.00,make_pair(0,source)));

    // inserting for 1 => metro
    st.insert(make_pair(0.00,make_pair(1,source)));

    // inserting for 2 => bus
    st.insert(make_pair(0.00,make_pair(2,source)));

    vector<pair<float,int> > dijkstra_array(graph.size(),make_pair(FLT_MAX,0));

    //arr->first = val, arr->second = mode
    dijkstra_array[source] = {0.00,0};


    

    while(!st.empty()){

        float val = st.begin()->first*1.0;
        int mode = st.begin()->second.first;
        int src = st.begin()->second.second;

        st.erase(st.begin());


        for(int nbrSrc=0; nbrSrc<graph[src].size(); nbrSrc++){

            for(int modeTrav=0; modeTrav<graph[source][nbrSrc].size(); modeTrav++){

                if(graph[src][nbrSrc][modeTrav] != INT16_MAX && graph[src][nbrSrc][modeTrav] != 0){

                    if((graph[src][nbrSrc][modeTrav]*ratio[modeTrav]*1.0)  +  val < dijkstra_array[nbrSrc].first){

                        //moving from src to nbrSrc using modeTrav:
                        parent[nbrSrc] = {src,modeTrav};

                        pair<float,pair<int,int> > newEdge = {(dijkstra_array[nbrSrc].first)*1.0,{modeTrav,nbrSrc}};

                        //search for newEdge in set

                        //if found

                        if(st.find(newEdge)  != st.end()){
                            //erase
                            st.erase(st.find(newEdge));
                        }

                        // update dijkstra_arr for nbrSrc

                        dijkstra_array[nbrSrc] = {(graph[src][nbrSrc][modeTrav]*ratio[modeTrav]*1.0) + val, modeTrav};

                        // insert new DATA in set 

                        st.insert({dijkstra_array[nbrSrc].first,{dijkstra_array[nbrSrc].second,nbrSrc}});

                    }
                    
                }
            }
        }

    }

    return dijkstra_array[destination].first;
}




void call_function(vector<vector<vector<int>>> &graph, vector<float>& time_per_km, vector<float>& cost_per_km){

    int source, destination;
    string criterion;

    //set source and destination

    // source = 1;
    // destination = 3;
    // criterion = "time";


    // user input data set ==>

    cout << "Locations : " << endl;

    for(int i=0; i<graph.size();i++)
    cout << i << "   ";

    cout << endl;

    cout << "Choose the source location : " << endl;
    cin >> source;

    cout << "Choose the destination location : " << endl;
    cin >> destination;

    cout << "Enter the criterion :" << endl;
    cin >> criterion;

    // parent array to store path
    // parent[]->first: parent  parent[]->second: mode

    vector<pair<int,int>> parent(graph.size(),{-1,-1});

    float result;
    
    if(criterion=="time")
    result = dijkstra(graph,source,destination,time_per_km,parent);

    else if(criterion=="cost")
    result = dijkstra(graph,source,destination,cost_per_km,parent);

    else{
        cout << "Invalid Input Criterion!";
        return;
    }


    print_result(result,parent,source,destination,criterion);
    
}


int main(){

    int no_of_modes = 3;

     vector<vector<vector<int> > > v;
     
     // for 3rd dimension => 0: cab, 1: metro, 2: bus;

    //  v.push_back({{0,0,0} , {7,INT16_MAX,7} , {5,4,INT16_MAX} , {3,6,5} , {9,7,9} , {6,INT16_MAX,INT16_MAX} , {4,13,4}});
    //  v.push_back({{7,INT16_MAX,7} , {0,0,0} , {1,2,1} , {12,INT16_MAX,INT16_MAX} , {3,6,INT16_MAX} , {3,7,3} ,{7,INT16_MAX,9}});
    //  v.push_back({{5,4,INT16_MAX} , {1,2,1} , {0,0,0} , {4,2,4} , {6,INT16_MAX,4} , {8,8,8} , {3,6,3}});
    //  v.push_back({{3,6,5} , {12,INT16_MAX,INT16_MAX} , {4,2,4} , {0,0,0} , {1,2,1} , {9,INT16_MAX,INT16_MAX} , {13,11,11}});
    //  v.push_back({{9,7,9} , {3,6,INT16_MAX} , {6,INT16_MAX,4} , {1,2,1} , {0,0,0} , {4,5,4} , {7,9,INT16_MAX}});
    //  v.push_back({{6,INT16_MAX,INT16_MAX} , {3,7,3} , {8,8,8} , {9,INT16_MAX,INT16_MAX} , {4,5,4} , {0,0,0} , {11,INT16_MAX,11}});
    //  v.push_back({{4,13,4} , {7,INT16_MAX,9} , {3,6,3} , {13,11,11} , {7,9,INT16_MAX} , {11,INT16_MAX,11} , {0,0,0}});

    v.push_back({{0,0,0} , {7,INT16_MAX,7} , {5,4,INT16_MAX} , {3,6,5} });
    v.push_back({{7,INT16_MAX,7} , {0,0,0} , {1,2,1} , {12,INT16_MAX,INT16_MAX} });
    v.push_back({{5,4,INT16_MAX} , {1,2,1} , {0,0,0} , {4,2,4} });
    v.push_back({{3,6,5} , {12,INT16_MAX,INT16_MAX} , {4,2,4} , {0,0,0}});
    



    // for 3rd dimension => 0: cab, 1: metro, 2: bus;
    vector<float> time_per_km(no_of_modes);
    vector<float> cost_per_km(no_of_modes);

    // set default time and cost for each mode of transport:

    // time_per_km = {1.2,1.2,1.2};
    // cost_per_km = {1.2,1.2,1.2};

    //accepting data from usesr : 

    cout << endl << "Set time per km => " << endl;
    for(int i=0; i<no_of_modes; i++){
        cout << "Enter data for mode " << i+1 << " : ";
        cin >> time_per_km[i];
    }cout << endl;

    cout << endl << "Set cost per km => " << endl;

    for(int i=0; i<no_of_modes; i++){
        cout << "Enter data for mode " << i+1 << " : ";
        cin >> cost_per_km[i];
    }cout << endl;

    call_function(v,time_per_km,cost_per_km);

    return 0;
}