#include "pch.h"
#include "PathFinding.h"


PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

void PathFinding::givePath()
{
}

void PathFinding::findPath()
{
	//ifstream TestFile("Test Dijkstra 3.txt", ios::in);                            // open the test file
	//if (!TestFile) return 1;
	//cin.rdbuf(TestFile.rdbuf());

	int NbNodes, NbEdges;
	NbNodes = c.getTileNum();
	NbEdges = 4;
	//cin >> NbNodes >> NbEdges;

	vector<vector<pair<int, int>>> G(NbNodes);                                    // The graph is a vector with NbNodes nodes. 
		
	int firstLine = c.getTileNumColumn();
	int lastLine = NbNodes - c.getTileNumColumn();

	for (size_t indiceNode = 0; indiceNode < NbNodes; indiceNode++)
	{

		if (indiceNode >= firstLine)
		{
			if (indiceNode < lastLine)
			{

			}
			else                                                              //If lastLine
			{
					
			}
		}
		else
		{
			if (indiceNode < lastLine)												//If first line
			{
				if (indiceNode = 0)
				{
					// Each node is connected to others nodes via weighted edges. This information is stored in a vector of pair
					for (auto i = 0; i != NbEdges; ++i) {
						int u, v, w;
						//cin >> u >> v >> w;

						switch (i)
						{
						case 0 :

							break;
						case 1 :

						/*	u = ;
							v = ;
							w = 1;
						*/
							break;
						case 2 :

							u = indiceNode;
							v = indiceNode + 1;
							w = 1;

							G[u].push_back(make_pair(v, w));                                            // Each pair contains : first=index of the node connected to u, second=weight/distance/codst of the path from v to u
							G[v].push_back(make_pair(u, w));                                          	// With undirected edges, create link from v to u and u to v. Both with weight w

							break;
						case 3 :

							u = indiceNode;
							v = indiceNode + c.getTileNumColumn();;
							w = 1;

							G[u].push_back(make_pair(v, w));                                            // Each pair contains : first=index of the node connected to u, second=weight/distance/codst of the path from v to u
							G[v].push_back(make_pair(u, w));                                          	// With undirected edges, create link from v to u and u to v. Both with weight w

							break;
						default:
							break;
						}

						//u = ;
						//v = ;
						//w = 1;
						G[u].push_back(make_pair(v, w));                                            // Each pair contains : first=index of the node connected to u, second=weight/distance/codst of the path from v to u
						G[v].push_back(make_pair(u, w));                                          	// With undirected edges, create link from v to u and u to v. Both with weight w
					}
				}
				
			}
			else                                                              //If lastLine == first line
			{

			}
		}


		// Each node is connected to others nodes via weighted edges. This information is stored in a vector of pair
			//for (auto i = 0; i != NbEdges; ++i) {
			//	int u, v, w;
			//	//cin >> u >> v >> w;
			//	u = ;
			//	v = ;
			//	w = 1;
			//	G[u].push_back(make_pair(v, w));                                            // Each pair contains : first=index of the node connected to u, second=weight/distance/codst of the path from v to u
			//	G[v].push_back(make_pair(u, w));                                          // Comment this line if the graph use directed edges. 
			//																				// With undirected edges, create link from v to u and u to v. Both with weight w
			//}
	}

	int StartNode;
	StartNode = 0;						//Origin

	vector<int> Distances(NbNodes, numeric_limits<int>::max());                   // Distances is a vector of NbNodes cells. All cells are initialized with max()
																				  // Distances[i] is the distance from StartNode to node whose index is i

	Distances[StartNode] = 0;                                                     // Distance to StartNode is initialized to 0

	vector<int> Parents(NbNodes, -1);                                             // Parents is a vector of NbNodes cells. All cells are initialized with -1

																				  // Priority queue storing pairs and using a specific comparator function
																				  // Because of the comparator we need to specify the 3 parameters 
																				  // The comparator make sure that the closest node is always on top of the queue
																				  // Each pair is made of : index of the node and the distance to StartNode
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> Q(comp);
	Q.push(make_pair(StartNode, 0));                                              // Initialize the priority queue with StartNode

	while (!Q.empty()) {                                                          // Dijkstra
		int v = Q.top().first;                                                      // get the index of the nearest node  
		int w = Q.top().second;                                                     // get the weight/cost/distance
		Q.pop();

		if (w <= Distances[v]) {                                                    // Pay attention to this test. 
																					// It can be removed, however, it avoid duplicated work

			for (const auto& i : G[v]) {                                              // v is the index of the nearest node 
				auto v2 = i.first;                                                      // For each node connected to node v
				auto w2 = i.second;

				if (Distances[v] + w2 < Distances[v2]) {                                // If distance from StartNode to v2 thru v is shorter then the current distance from StartNode to v2
					Distances[v2] = Distances[v] + w2;                                    // then update the distance from StartNode to v2 and parent[v2]  
					Parents[v2] = v;                                                      // https://www.youtube.com/watch?v=8Ls1RqHCOPw  
					Q.push(make_pair(v2, Distances[v2]));
				}
			}
		}
	}

	for (auto i = 0; i != NbNodes; ++i) {                                          // display the results
		cout << "\nPath from node " << StartNode << " to node " << i << " cost " << Distances[i] << endl;

		cout << i;
		for (auto p = Parents[i]; p != -1; p = Parents[p])
			cout << " <- " << p;                                                      // when links are not bi directional the output is accurate when using <- instead of ->
		cout << endl;                                                               // otherwise it make no difference
	}
	getchar();
}
