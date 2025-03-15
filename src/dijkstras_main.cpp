// #include <sstream>
// #include <cassert>
// #include "dijkstras.h" // Include your header file

// void test_dijkstra_shortest_path() {
//     Graph G;
//     G.numVertices = 5;
//     G.resize(5);
    
//     G[0].push_back(Edge(0, 1, 10));
//     G[0].push_back(Edge(0, 2, 5));
//     G[1].push_back(Edge(1, 3, 1));
//     G[2].push_back(Edge(2, 1, 3));
//     G[2].push_back(Edge(2, 3, 8));
//     G[2].push_back(Edge(2, 4, 2));
//     G[3].push_back(Edge(3, 4, 4));
//     G[4].push_back(Edge(4, 3, 6));
    
//     vector<int> previous;
//     vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
//     assert(distances[0] == 0);      
//     assert(distances[1] == 8);     
//     assert(distances[2] == 5);     
//     assert(distances[3] == 9);     
//     assert(distances[4] == 7);      
    
//     assert(previous[0] == -1);      
//     assert(previous[1] == 2);       
//     assert(previous[2] == 0);      
//     assert(previous[3] == 1);       
//     assert(previous[4] == 2);      
    
//     cout << "dijkstra_shortest_path test passed!" << endl;
// }

// void test_extract_shortest_path() {
//     Graph G;
//     G.numVertices = 5;
//     G.resize(5);
    
//     G[0].push_back(Edge(0, 1, 10));
//     G[0].push_back(Edge(0, 2, 5));
//     G[1].push_back(Edge(1, 3, 1));
//     G[2].push_back(Edge(2, 1, 3));
//     G[2].push_back(Edge(2, 3, 8));
//     G[2].push_back(Edge(2, 4, 2));
    
//     vector<int> previous;
//     vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
//     vector<int> path_to_3 = extract_shortest_path(distances, previous, 3);
//     vector<int> expected_path_to_3 = {0, 2, 1, 3};
//     assert(path_to_3 == expected_path_to_3);
    
//     vector<int> path_to_4 = extract_shortest_path(distances, previous, 4);
//     vector<int> expected_path_to_4 = {0, 2, 4};
//     assert(path_to_4 == expected_path_to_4);
    
//     vector<int> path_to_0 = extract_shortest_path(distances, previous, 0);
//     vector<int> expected_path_to_0 = {0};
//     assert(path_to_0 == expected_path_to_0);
    
//     cout << "extract_shortest_path test passed!" << endl;
// }

// void test_print_path() {
//     // Create a path
//     vector<int> path = {0, 2, 1, 3};
//     int total_cost = 9;
    
//     std::stringstream ss;
//     std::streambuf* old_cout = std::cout.rdbuf();
//     std::cout.rdbuf(ss.rdbuf());
    
//     print_path(path, total_cost);
    
//     std::cout.rdbuf(old_cout);
    
//     std::string expected_output = "0 2 1 3 \nTotal cost is 9\n";
//     assert(ss.str() == expected_output);
    
//     std::stringstream ss2;
//     std::cout.rdbuf(ss2.rdbuf());
//     print_path({}, 5);
//     std::cout.rdbuf(old_cout);
    
//     std::string expected_empty_output = "\nTotal cost is 5\n";
//     assert(ss2.str() == expected_empty_output);
    
//     cout << "print_path test passed!" << endl;
// }

// void test_unreachable_vertices() {
//     Graph G;
//     G.numVertices = 4;
//     G.resize(4);
    
//     G[0].push_back(Edge(0, 1, 5));
//     // No edges from vertex 2 or 3
    
//     vector<int> previous;
//     vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
//     assert(distances[0] == 0);          
//     assert(distances[1] == 5);
//     assert(distances[2] == INF);       
//     assert(distances[3] == INF); 
    
//     vector<int> path_to_3 = extract_shortest_path(distances, previous, 3);
//     assert(path_to_3.empty());          
    
//     std::stringstream ss;
//     std::streambuf* old_cout = std::cout.rdbuf();
//     std::cout.rdbuf(ss.rdbuf());
    
//     print_path(path_to_3, 0);
    
//     std::cout.rdbuf(old_cout);
//     std::string expected_output = "\nTotal cost is 0\n";
//     assert(ss.str() == expected_output);
    
//     cout << "unreachable vertices test passed!" << endl;
// }

// int main() {
//     test_dijkstra_shortest_path();
//     test_extract_shortest_path();
//     test_print_path();
//     test_unreachable_vertices();
    
//     cout << "All tests passed!" << endl;
//     return 0;
// }