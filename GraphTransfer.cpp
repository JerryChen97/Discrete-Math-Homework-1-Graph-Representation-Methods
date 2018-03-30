#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream input("input.txt");
ofstream output("output.txt");

int **create_Adj(int size)
{
	int **Adj = new int *[size]();
	for (int i = 0; i < size; i++)
	{
		Adj[i] = new int[size]();
	}
	return Adj;
}

void destroy_Adj(int **Adj, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete []Adj[i];
	}
	delete []Adj;
}

int main()
{
	int n;
	int temp;
	int m = 0; //count the number of edges
	input >> n;
	int **Adj = create_Adj(n);
	vector<vector<int> > Inci;
	vector<vector<int> > EdgeList;
	vector<vector<int> > PosiTable;
	vector<int> PosiA;
	vector<int> PosiB;
	vector<int> PosiZ;
	vector<vector<int> > AdjTable;
	int row_counter = 1; //count the number of non-zero of every row
	PosiA.push_back(row_counter);
	for (int i = 0; i < n; i++)
	{
		vector<int> adjtableelement;
		for (int j = 0; j < n; j++)
		{
			input >> temp;
			if (temp) //there exists an edge
			{
				row_counter++;
				m++;
				Adj[i][j] = temp;

				vector<int> edge(n,0);
				edge[i] = 1; edge[j] = -1;
				Inci.push_back(edge);

				vector<int> edgelistelement(3,0);
				edgelistelement[0] = i + 1; edgelistelement[1] = j + 1; edgelistelement[2] = temp;
				EdgeList.push_back(edgelistelement);

				PosiB.push_back(j + 1);
				PosiZ.push_back(temp);

				adjtableelement.push_back(temp);
				adjtableelement.push_back(j + 1);
			}
		}
		PosiA.push_back(row_counter);

		AdjTable.push_back(adjtableelement);
	}
	PosiTable.push_back(PosiA);
	PosiTable.push_back(PosiB);
	PosiTable.push_back(PosiZ);
	//print the incident matrix
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			output << Inci[j][i] << ' ';
		}
		output << endl;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < m; j++)
		{
			output << EdgeList[j][i] << ' ';
		}
		output << endl;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < PosiTable[i].size(); j++)
		{
			output << PosiTable[i][j] << ' ';
		}
		output << endl;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < AdjTable[i].size(); j++)
		{
			output << AdjTable[i][j] << ' ';
		}
		output << endl;
	}
	//close the file stream
	input.close();
	output.close();
}