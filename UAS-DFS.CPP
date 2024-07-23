#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<string>> adjList;

    void DFSUtil(string current, string goal, unordered_map<string, bool>& visited, vector<string>& path, vector<string>& shortestPath) {
        path.push_back(current);
        visited[current] = true;

        if (current == goal) {
            if (shortestPath.empty() || path.size() < shortestPath.size()) {
                shortestPath = path; // Simpan jalur terpendek
            }
        } else {
            for (const auto& neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    DFSUtil(neighbor, goal, visited, path, shortestPath);
                }
            }
        }

        path.pop_back();
        visited[current] = false;
    }

public:
    void addEdge(string src, string dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // Untuk graf tidak berarah
    }

    vector<string> DFS(string start, string goal) {
        unordered_map<string, bool> visited;
        vector<string> path;
        vector<string> shortestPath;

        DFSUtil(start, goal, visited, path, shortestPath);

        return shortestPath;
    }
};

int main() {
    Graph g;

    // Menambahkan edges dari data yang Anda berikan
    vector<pair<string, string>> edges = {
        {"Gudang", "A"},
        {"Gudang", "S"},
        {"Gudang", "M"},
        {"Gudang", "B"},
        {"M", "D"},
        {"M", "C"},
        {"M", "B"},
        {"D", "C"},
        {"C", "B"},
        {"C", "E"},
        {"A", "B"},
        {"A", "N"},
        {"S", "A"},
        {"S", "R"},
        {"F", "N"},
        {"F", "A"},
        {"R", "H"},
        {"R", "I"},
        {"I", "H"},
        {"H", "G"},
        {"H", "S"},
        {"G", "F"},
        {"G", "S"},
        {"F", "S"},
        {"N", "B"},
        {"N", "Q"},
        {"N", "L"},
        {"F", "L"},
        {"B", "E"},
        {"B", "O"},
        {"B", "Q"},
        {"E", "O"},
        {"Q", "O"},
        {"Q", "K"},
        {"O", "K"},
        {"L", "Q"},
        {"L", "K"},
        {"L", "P"},
        {"P", "K"},
        {"P", "J"},
        {"K", "J"}
    };

    // Tambahkan semua edge dari data
    for (const auto& edge : edges) {
        g.addEdge(edge.first, edge.second);
    }

    string start = "Gudang";
    string goal = "J"; // Tujuan akhir diubah menjadi "J"

    vector<string> shortestPath = g.DFS(start, goal);

    if (!shortestPath.empty()) {
        cout << "Rute terpendek dari " << start << " ke " << goal << ": ";
        for (size_t i = 0; i < shortestPath.size(); ++i) {
            cout << shortestPath[i];
            if (i < shortestPath.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "Tidak ada jalur dari " << start << " ke " << goal << endl;
    }

    return 0;
}