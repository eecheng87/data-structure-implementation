#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
vector<int> inputdata;
int vertexNum;
void ReadData();
int find(vector<int>);
bool finish(vector<int>);
void Sollin(vector<vector<int>>, vector<vector<int>> &, vector<int> &);
void updateGroup(vector<int> &, int, int);
vector<int> connectGroup(vector<vector<int>>, vector<vector<int>> &, vector<int> &);
void printAns(vector<vector<int>> &);
int main()
{
    vertexNum = 0;
    int egdeNum;
    int currentEdgeNum = 0;
    cin >> egdeNum;

    while (currentEdgeNum <= egdeNum)
    {
        ReadData();
        currentEdgeNum++;
    }
    vertexNum++;

    vector<vector<int>> graph(vertexNum, vector<int>(vertexNum, 0));
    vector<vector<int>> spanTree(vertexNum, vector<int>(vertexNum, 0));

    // construct symetric graph
    // init graph to all zeros
    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
        {
            graph[i][j] = 0;
            spanTree[i][j] = 0;
        }

    while (!inputdata.empty())
    {
        int i = inputdata[0];
        int j = inputdata[1];
        int weight = inputdata[2];
        inputdata.erase(inputdata.begin());
        inputdata.erase(inputdata.begin());
        inputdata.erase(inputdata.begin());
        graph[i][j] = weight;
        graph[j][i] = weight;
    }

    // variable help merge two subtree to bigger tree
    vector<int> subTreeIndex(vertexNum, 0);

    for (int i = 0; i < vertexNum; i++)
        subTreeIndex[i] = i + 1; // its value means different group for subtree

    Sollin(graph, spanTree, subTreeIndex);

    printAns(spanTree);

    return 0;
}

void ReadData()
{
    int index = 0;
    string num;
    string str;
    getline(cin, str);
    istringstream input(str);
    while (input >> num)
    {
        index++;
        stringstream geek(num);
        int tmp;
        geek >> tmp;
        inputdata.push_back(tmp);
        if (index < 3)
        {
            if (tmp > vertexNum)
                vertexNum = tmp;
        }
    }
}

void Sollin(vector<vector<int>> g, vector<vector<int>> &s, vector<int> &index)
{
    int i, j;

    int edgeNum = 0;
    // first time to find lowest cost edge, each vertice is A Tree!
    for (i = 0; i < g.size(); i++)
    {
        //cout << g.size() << " " << edgeNum << endl;
        int source;
        int dest;
        int minWeight = 999;

        for (j = 0; i < g[j].size(); j++)
        {
            // no edge, come to next condition
            if (!g[i][j])
                continue;
            if (g[i][j] < minWeight)
            {
                source = i;
                dest = j;
                minWeight = g[i][j];
            }
        }
        // update spanning tree graph
        edgeNum++;
        s[source][dest] = minWeight;
        s[dest][source] = minWeight;
        // merge subtree to bigger one
        if (index[dest] > index[source])
            updateGroup(index, index[source], index[dest]);
        else
            updateGroup(index, index[source], index[dest]);
    }

    while (!finish(index))
    {
        vector<int> newSet = connectGroup(g, s, index);
        int a = newSet[0];
        int b = newSet[1];
        int c = newSet[2];
        s[a][b] = c;
        s[b][a] = c;
        if (index[a] > index[b])
            updateGroup(index, index[b], index[a]);
        else
            updateGroup(index, index[a], index[b]);
    }
}
vector<int> connectGroup(vector<vector<int>> input, vector<vector<int>> &output, vector<int> &index)
{

    int groupIndex;
    int min = 999;
    int source, dest, weight;

    for (int i = 1; i < index.size(); i++)
        if (index[i - 1] != index[i])
        {
            groupIndex = index[i - 1] > index[i] ? index[i] : index[i - 1];
            break;
        }

    for (int i = 0; i < index.size(); i++)
    {
        if (index[i] == groupIndex)
        {

            for (int j = 0; j < index.size(); j++)
            {
                if (input[i][j] != 0 && input[i][j] < min && i != j && index[i] != index[j])
                {
                    source = i;
                    dest = j;
                    weight = input[i][j];
                    min = input[i][j];
                }
            }
        }
    }

    vector<int> tmp;
    tmp.push_back(source);
    tmp.push_back(dest);
    tmp.push_back(weight);
    return tmp;
}

bool finish(vector<int> index)
{
    for (int i = 1; i < index.size(); i++)
        if (index[i - 1] != index[i])
            return false;
    return true;
}
void updateGroup(vector<int> &index, int before, int after)
{
    for (int i = 0; i < index.size(); i++)
        if (index[i] == before)
            index[i] = after;
}
void printAns(vector<vector<int>> &ans)
{
    cout << "\n";
    for (int i = 0; i < ans.size(); i++)
        for (int j = i; j < ans[i].size(); j++)
            if (ans[i][j])
                cout << i << " " << j << " " << ans[i][j] << endl;
}