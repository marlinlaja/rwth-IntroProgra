#include <iostream>
#include <vector>
#include <limits>
#include <fstream>


// möglicherweise nützlich 
double inf = std::numeric_limits<double>::infinity();

class Graph {
private:
    std::vector<std::vector<double>> adjacency_matrix;
    int n;
public:

    // Konstruktor initialisiert eine n x n Adjazenzmatrix mit 0 in allen Einträgen
    Graph(int n) : n(n), adjacency_matrix(n, std::vector<double>(n, 0)) { }

    void add_edge(int i, int j, double weight) { 
        // TODO 1.1 : Eintrag in die Adjazenzmatrix
        adjacency_matrix[i][j] = weight;
    }

    double cost(int i, int j) const {
        // TODO 1.2 : Kosten der Kante von i nach j
        double cost = adjacency_matrix[i][j];
        if (cost != 0) {return cost;}
        else {return inf;}
    }

    std::vector<int> reachable_nodes(int i) const {
        // TODO 1.3 : Alle von Knoten i aus erreichbaren Knoten
        std::vector<int> connected;
        for (size_t j = 0; j < adjacency_matrix[i].size(); j++)
        {
            if (adjacency_matrix[i][j] != 0) {
                connected.push_back(j);
            }
        }
        return connected;
    }
};

double shortest_path(const Graph& g, int i, int j) {
    // TODO 4:
    
    // Base Case 1: i==j
    if(i == j) {return 0;}
    
    // Base Case 2: g hat keine erreichbaren Kanten von i
    else if(g.reachable_nodes(i).size() == 0) {return inf;}
    
    // Resursive Case: Rekursiver Aufruf auf allen erreichbaren Kanten und ausgabe minimaler Kosten
    else {
        double min_cost = inf;
        for (size_t k = 0; k < g.reachable_nodes(i).size(); k++)
        {
            int next_node = g.reachable_nodes(i)[k];
            double cost = g.cost(i, next_node);
            double additional_cost = shortest_path(g, next_node, j);
            min_cost = std::min(min_cost, cost + additional_cost);
        }
        return min_cost;
    }
}

Graph file_to_graph(std::string filename) {
    std::ifstream infile(filename);

    int amount_nodes;
    infile >> amount_nodes;
    Graph graph(amount_nodes);

    int amount_edges;
    infile >> amount_edges;
    for (size_t i = 0; i < amount_edges; i++)
    {
        std::pair<int, int> edge_nodes;
        infile >> edge_nodes.first; infile >> edge_nodes.second;
        double weight;
        infile >> weight;

        graph.add_edge(edge_nodes.first, edge_nodes.second, weight);
    }
    return graph;
}


int main() {

    // TODO 2 : Auslesen aus my_graph_1.txt, und initialisieren eines ensptrechenden Graph Objekts
    Graph graph1 = file_to_graph("my_graph_1.txt");
    std::cout << "\nGraph 1:" << std::endl;
    
    // TODO 3 : Funktioniert die Implementierung wie gedacht?
    int node = 1;
    for (size_t i = 0; i < graph1.reachable_nodes(node).size(); i++)
    {
        int next_node = graph1.reachable_nodes(node)[i];
        std::cout << "(" << node << " => " << next_node << ")";
        std::cout << " cost: " << graph1.cost(node, next_node) << std::endl;
    }

    // TODO 5 : Aufrufen von shortest_path auf dem oben erstellten Graph.
    // Was sind die Kosten des kürzesten Pfads von 0 nach 4 ?
    int start, end;
    double cost;

    start = 0; end = 4;
    cost = shortest_path(graph1, start, end);
    std::cout << "(" << start << " => " << end << ") cost: " << cost << std::endl;

    // TODO 6 : Erstelle neuen Graph, der my_graph_2.txt entspricht. 
    // Was sind die Kosten des kürzesten Pfads von 0 nach 6?
    Graph graph2 = file_to_graph("my_graph_2.txt");
    std::cout << "\nGraph 2:" << std::endl;


    start = 0; end = 6;
    cost = shortest_path(graph2, start, end);
    std::cout << "(" << start << " => " << end << ") cost: " << cost << std::endl;


    start = 0; end = 8;
    cost = shortest_path(graph2, start, end);
    std::cout << "(" << start << " => " << end << ") cost: " << cost << std::endl;

    std::cout << std::endl;
}