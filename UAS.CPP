#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <map>

using namespace std;

class CityGraph {
private:
    vector<vector<pair<int, int>>> adjList; // Daftar adjacency untuk menyimpan graf
    vector<char> vertexNames; // Menyimpan nama vertex dalam bentuk huruf
    map<char, int> vertexIndexMap; // Memetakan nama vertex ke indeks masing-masing
    int numVertices; // Jumlah vertex dalam graf

public:
    // Konstruktor untuk inisialisasi graf dengan jumlah vertex dan nama vertex
    CityGraph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices); // Mengatur ukuran vektor daftar adjacency sesuai jumlah vertex
        vertexNames.resize(vertices); // Mengatur ukuran vektor nama vertex
    }

    // Menetapkan nama untuk setiap vertex dan membuat peta indeks untuk pencarian cepat
    void setVertexNames(vector<char> names) {
        if (names.size() != numVertices) {
            cerr << "Jumlah nama vertex tidak sesuai dengan jumlah vertex dalam graf!" << endl;
            exit(1);
        }
        vertexNames = names;
        for (int i = 0; i < numVertices; ++i) {
            vertexIndexMap[names[i]] = i;
        }
    }

    // Menambahkan jalan (edge) antara dua vertex dengan bobot waktu
    void addRoad(char u, char v, int time) {
        int uIndex = vertexNameToIndex(u); // Mendapatkan indeks vertex dari nama
        int vIndex = vertexNameToIndex(v); // Mendapatkan indeks vertex dari nama
        adjList[uIndex].push_back(make_pair(vIndex, time)); // Menambahkan edge dari u ke v
        adjList[vIndex].push_back(make_pair(uIndex, time)); // Menambahkan edge dari v ke u (graf tak berarah)
    }

    // Mengonversi nama vertex menjadi indeks
    int vertexNameToIndex(char name) {
        if (vertexIndexMap.find(name) != vertexIndexMap.end()) {
            return vertexIndexMap[name];
        } else {
            cerr << "Nama vertex " << name << " tidak ada!" << endl;
            exit(1);
        }
    }

    // Fungsi bantu untuk mencetak jalur dari startVertex ke endVertex
    void printPath(vector<int>& parent, int vertex) {
        stack<int> path; // Menggunakan stack untuk membalik urutan jalur
        for (; vertex != -1; vertex = parent[vertex]) {
            path.push(vertex); // Menyimpan vertex dalam stack
        }
        while (!path.empty()) {
            cout << vertexNames[path.top()]; // Mencetak nama vertex teratas dari stack
            path.pop(); // Menghapus vertex dari stack
            if (!path.empty()) cout << " -> "; // Menambahkan panah antara vertex
        }
        cout << endl;
    }

    // Mencari jalur terpendek dari startVertex ke endVertex menggunakan algoritma Dijkstra
    void findShortestPath(char startVertex, char endVertex) {
        int startIndex = vertexNameToIndex(startVertex); // Mengonversi nama vertex ke indeks
        int endIndex = vertexNameToIndex(endVertex); // Mengonversi nama vertex ke indeks

        vector<int> dist(numVertices, INT_MAX); // Vektor untuk menyimpan jarak minimum dari startVertex ke setiap vertex
        vector<int> parent(numVertices, -1); // Vektor untuk menyimpan parent dari setiap vertex
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Priority queue untuk Dijkstra

        dist[startIndex] = 0; // Jarak dari startVertex ke startVertex adalah 0
        pq.push(make_pair(0, startIndex)); // Memasukkan startVertex ke dalam priority queue dengan jarak 0

        while (!pq.empty()) {
            int u = pq.top().second; // Mengambil vertex dengan jarak terkecil
            pq.pop();

            if (u == endIndex) { // Jika vertex u adalah endVertex, jalur terpendek ditemukan
                cout << "Jalur terpendek dari " << startVertex << " ke " << endVertex << ":" << endl;
                cout << "Total panjang jarak: " << dist[endIndex] << " km" << endl;
                cout << "Jalur: ";
                printPath(parent, endIndex); // Mencetak jalur terpendek
                return;
            }

            // Memproses semua tetangga dari vertex u
            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first; // Vertex tetangga
                int time = neighbor.second; // Bobot edge

                // Jika jarak baru ditemukan lebih kecil dari jarak saat ini, perbarui jarak dan parent
                if (dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    parent[v] = u; // Menyimpan parent dari vertex v
                    pq.push(make_pair(dist[v], v)); // Memasukkan vertex v ke priority queue dengan jarak yang diperbarui
                }
            }
        }

        // Jika endVertex tidak dapat dicapai, tampilkan pesan
        cout << "Tidak ada jalur dari " << startVertex << " ke " << endVertex << "." << endl;
    }
};

int main() {
    CityGraph g(20); // Membuat graf dengan 20 vertex
    vector<char> names = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'Z'}; // Menetapkan nama untuk vertex
    g.setVertexNames(names); // Mengatur nama vertex dalam graf

    // Menambahkan jalan antar vertex dengan bobot waktu
    g.addRoad('Z', 'A', 6);
    g.addRoad('Z', 'S', 11);
    g.addRoad('Z', 'M', 7);
    g.addRoad('Z', 'B', 8);
    g.addRoad('M', 'D', 8);
    g.addRoad('M', 'C', 5);
    g.addRoad('M', 'B', 8);
    g.addRoad('D', 'C', 8);
    g.addRoad('C', 'B', 8);
    g.addRoad('C', 'E', 8);
    g.addRoad('A', 'B', 10);
    g.addRoad('A', 'N', 7);
    g.addRoad('S', 'A', 6);
    g.addRoad('S', 'R', 12);
    g.addRoad('F', 'N', 7);
    g.addRoad('F', 'A', 8);
    g.addRoad('R', 'H', 16);
    g.addRoad('R', 'I', 12);
    g.addRoad('I', 'H', 18);
    g.addRoad('H', 'G', 11);
    g.addRoad('H', 'S', 8);
    g.addRoad('G', 'F', 5);
    g.addRoad('G', 'S', 8);
    g.addRoad('F', 'S', 8);
    g.addRoad('N', 'B', 8);
    g.addRoad('N', 'Q', 6);
    g.addRoad('N', 'L', 5);
    g.addRoad('F', 'L', 7);
    g.addRoad('B', 'E', 10);
    g.addRoad('B', 'O', 10);
    g.addRoad('B', 'Q', 9);
    g.addRoad('E', 'O', 8);
    g.addRoad('Q', 'O', 5);
    g.addRoad('Q', 'K', 8);
    g.addRoad('O', 'K', 8);
    g.addRoad('L', 'Q', 4);
    g.addRoad('L', 'K', 11);
    g.addRoad('L', 'P', 9);
    g.addRoad('P', 'K', 7);
    g.addRoad('P', 'J', 10);
    g.addRoad('K', 'J', 9);

    char startVertex = 'Z'; // Titik awal
    char endVertex = 'J';   // Titik akhir
    g.findShortestPath(startVertex, endVertex); // Mencari jalur terpendek dari startVertex ke endVertex

    return 0;
}
