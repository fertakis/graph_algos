#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Node {
    public:
    int idx = -1;
    int level = INT_MAX;
    bool visited = false;

    vector<Node> parents;

    void addParent(Node n) {

        //rejecting parent if it's level is equal to ours
        if (n.level == level) {
            return;
        }

        parents.push_back(n);

        level = n.level + 1;
    };

    void printParents() {
        cout << "parents[" << idx << "]->{";
        for (vector<Node>::iterator it = parents.begin() ; it != parents.end(); ++it)
            cout << it->idx << ",";
        cout << "}" << endl;
    };
};

void printQueue(list<int> queue) {
    cout << "printing queue contents:" << endl;
    cout << "{";
    for (auto const& i : queue) {
        cout << i  << ",";
    }
    cout << "}" << endl;
}

//TODO:check for memory leakages
void findPath(int cur, vector<int> &path, Node nodes[], vector<vector<int>> &paths) {
    
    if(nodes[cur].parents.empty()) {
        //found a path, add it to the list
        paths.push_back(path);
        return;
    }
    
    for (const auto& it : nodes[cur].parents) {
        vector<int> new_path(path);
        new_path.push_back(it.idx);

        findPath(it.idx, new_path, nodes, paths);
    }
}


/**
 * Modified version of BFS for calculating all possible 
 * shortest paths from src to dst given unweighted graph
 * represented by an adjacency list
 **/ 
bool BFS(vector<int> adj[], int src, int dest, int v, Node nodes[]) {
    bool ret = false;
    int min_dist = INT_MAX;

    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // BFS algorithm
    list<int> queue;

    // now source is first to be visited and
    // distance from source to itself should be 0
    nodes[src].visited = true;
    nodes[src].level = 0;

    queue.push_back(src);
    // printQueue(queue);

    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        // cout << "removed from queue: " << u << endl;

        // printQueue(queue);
        // visited[u] = true;
        nodes[u].visited = true;

        if(ret == true && nodes[u].level >=min_dist)
            return ret;

        for (int i = 0; i < adj[u].size(); i++) {
            // cout << "checking " << adj[u][i] << endl;
            if (nodes[adj[u][i]].visited == false) {

                // cout << "adding par[" << adj[u][i] << "]=" << u << endl;
                nodes[adj[u][i]].addParent(nodes[u]);

                bool found = (std::find(queue.begin(), queue.end(), adj[u][i]) != queue.end());
                if (!found) {
                    queue.push_back(adj[u][i]);
                    // printQueue(queue);
                }

                if (adj[u][i] == dest) {
                    ret = true;
                    min_dist = nodes[adj[u][i]].level;
                    // cout << "minimum dist =" << min_dist << endl;
                }
            }
        }
    }

    return ret;
}

// utility function to print the shortest distance
// between source vertex and destination vertex
void printShortestDistance(vector<int> adj[], int s, int dest, int v) {

    Node nodes[v];
    for (int i = 0; i < v; i++)
        nodes[i].idx = i;

    if (BFS(adj, s, dest, v, nodes) == false) {
        cout << "Given source and destination" << " are not connected";
        return;
    }

    cout << "printing parents vector: " << endl;
    for (int i=0; i < v; i++) {
        nodes[i].printParents();
    }

    // distance from source is in distance array
    cout << "Shortest path length is : " << nodes[dest].level << endl;

    cout << "going to print all available shortest paths" << endl;
    vector<int> path;
    path.push_back(dest);
    vector<vector<int>> paths;
    findPath(dest, path, nodes, paths);
    
    int i = 0; 
    for (const auto& it: paths) {
        i++;
        cout << "printing path #" << i << endl;
        
        cout << "Path is::";
        for (int i = it.size() - 1; i >= 0; i--)
            cout << it[i] << " ";
        cout << endl;
    }
}

// utility function to form edge between two vertices
// source and dest
void add_edge(std::vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}

int main()
{
    // no. of vertices
    int v = 7;

    // array of std::vectors is used to store the graph
    // in the form of an adjacency list
    std::vector<int> adj[v];

    // Creating graph
    // add_edge function takes adjacency list, source
    // and destination vertex as argument and forms
    // an edge between them.

    // add_edge(adj, 0, 1);
    // add_edge(adj, 0, 3);
    // add_edge(adj, 1, 2);
    // add_edge(adj, 1, 7);
    // add_edge(adj, 3, 4);
    // add_edge(adj, 3, 7);
    // add_edge(adj, 4, 5);
    // add_edge(adj, 4, 6);
    // add_edge(adj, 4, 7);
    // add_edge(adj, 5, 6);
    // add_edge(adj, 6, 7);
    add_edge(adj, 0, 1);
    add_edge(adj, 0, 2);
    add_edge(adj, 1, 3);
    add_edge(adj, 2, 3);
    add_edge(adj, 3, 4);
    add_edge(adj, 3, 5);
    add_edge(adj, 4, 6);
    add_edge(adj, 5, 6);
    int source = 0, dest = 6;
    printShortestDistance(adj, source, dest, v);
    return 0;
}
