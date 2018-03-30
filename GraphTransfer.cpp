#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;
ifstream input("input.txt");
ofstream output("output.txt");

int main()
{
	int n;
	int temp;
	int m_edges = 0; //count the number of edges
	input >> n;

	// Incident Matrix
	vector<vector<int> > Inci;
	// Edge Table
	vector<vector<int> > EdgeTable;
	// Positive Table and the three table A, B and Z
	vector<vector<int> > PosiTable;
	vector<int> PosiA;
	vector<int> PosiB;
	vector<int> PosiZ;
	// Adjacecy List
	vector<list<int> > AdjList;
	PosiA.push_back(m_edges + 1); // push the first place i.e. 1 to the back of row A of the positive table
	for (int i = 0; i < n; i++)
	{
		list<int> adj_table_unit; // for every row in the adjacency matrix, we use a new empty list, witch satisfys the definition of adjacency lists.
		for (int j = 0; j < n; j++)
		{
			input >> temp;
			if (temp) //temps not 0 means that there exists an edge
			{
				// edge number accumulates
				m_edges++;

				// update the incidence matrix
				vector<int> edge(n,0);
				edge[i] = 1; edge[j] = -1;
				Inci.push_back(edge);

				// the unit of edge table is a 3-length vector, and in total there are m such vectors
				vector<int> edge_table_unit(3,0);
				edge_table_unit[0] = i + 1; edge_table_unit[1] = j + 1; edge_table_unit[2] = temp;
				EdgeTable.push_back(edge_table_unit);

				// update the positive table
				PosiB.push_back(j + 1);
				PosiZ.push_back(temp);

				adj_table_unit.push_back(temp);
				adj_table_unit.push_back(j + 1);
			}
		}
		/* push the current m into PosiA, because this stands 
		for the accumulated edge number, till the end of the edge
		counting for the last vertex
		*/
		PosiA.push_back(m_edges + 1); 
		// construct the adjacency list
		AdjList.push_back(adj_table_unit);
	}
	// construct the positive table
	PosiTable.push_back(PosiA);
	PosiTable.push_back(PosiB);
	PosiTable.push_back(PosiZ);
	//print the incident matrix
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m_edges; j++)
		{
			output << Inci[j][i] << ' ';
		}
		output << endl;
	}
	//print the edges table
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < m_edges; j++)
		{
			output << EdgeTable[j][i] << ' ';
		}
		output << endl;
	}
	//print the positive table
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < PosiTable[i].size(); j++)
		{
			output << PosiTable[i][j] << ' ';
		}
		output << endl;
	}
	//print the adjacency list
	for (int i = 0; i < n; i++)
	{
		list<int>::iterator it = AdjList[i].begin();
		for (int j = 0; j < AdjList[i].size(); j++)
		{
			output << *it++ << ' ';
		}
		output << endl;
	}
	//close the file stream
	input.close();
	output.close();
}