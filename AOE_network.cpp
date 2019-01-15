#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int eventNum;
typedef struct Map
{
    int source;
    int dest;
    int dur;
} map;
typedef struct adjList
{
    union {
        int count;
        struct node
        {
            int vertex;
            int dur;
        } n;
    } u;
    struct adjList *next;
} List;
void readLine(List **, map *, int *);
void insertToList(List **, int, int);
vector<int> calculateEE(List **, map *, int);
vector<int> calculateLE(vector<int>, map *, int, int);
vector<int> convertEEtoE(vector<int>, map *, int);
vector<int> convertLEtoL(vector<int>, map *, int);
int main()
{
    int lineNum = 0;
    int activityNum;
    eventNum = 0;

    cin >> activityNum;
    // declare adjacency list's head
    List *input[activityNum];

    for (int i = 0; i < activityNum; i++)
    {
        input[i] = (List *)malloc(sizeof(List));
        input[i]->u.count = 0;
        input[i]->next = NULL;
    }
    // declare a array store input line(more intuitive)
    map graph[activityNum];

    // read input data
    while (lineNum < activityNum)
        readLine(input, graph, &lineNum);

    vector<int> ee = calculateEE(input, graph, eventNum + 1);
    vector<int> e = convertEEtoE(ee, graph, activityNum);
    vector<int> le = calculateLE(ee, graph, eventNum + 1, activityNum);
    vector<int> l = convertLEtoL(le, graph, activityNum);

    cout << setw(4) << "act." << setw(4) << "e" << setw(4) << "l" << setw(8) << "slack" << setw(11) << "critical" << endl;
    for (int i = 0; i < l.size(); i++)
    {
        cout << setw(4) << i + 1 << setw(4) << e[i] << setw(4) << l[i] << setw(8) << l[i] - e[i];
        if (l[i] - e[i])
            cout << setw(11) << "No" << endl;
        else
            cout << setw(11) << "Yes" << endl;
    }

    system("pause");
    return 0;
}
vector<int> calculateEE(List **adjList, map *graph, int num)
{
    // return a vector which store each event's EE value
    vector<int> ans(num, 0);
    vector<int> stack;
    stack.push_back(0);

    while (!stack.empty())
    {
        // get top element
        int top = stack[stack.size() - 1];
        stack.pop_back();
        List *first = adjList[top]->next;

        while (first)
        {
            int currentDest = first->u.n.vertex;
            if (adjList[currentDest]->u.count <= 1)
                stack.push_back(first->u.n.vertex);
            else
                adjList[currentDest]->u.count -= 1;
            // update EE value
            if (first->u.n.dur + ans[top] > ans[currentDest])
                ans[currentDest] = first->u.n.dur + ans[top];

            first = first->next;
        }
    }

    return ans;
}
vector<int> calculateLE(vector<int> ee, map *graph, int eventNum, int activityNum)
{
    vector<int> ans(eventNum, 9999);
    ans[eventNum - 1] = ee[eventNum - 1];

    for (int i = eventNum - 2; i >= 0; i--)
    {
        for (int j = 0; j < activityNum; j++)
        {
            if (graph[j].source == i)
                if (ans[i] > ans[graph[j].dest] - graph[j].dur)
                    ans[i] = ans[graph[j].dest] - graph[j].dur;
        }
    }

    return ans;
}
vector<int> convertEEtoE(vector<int> ee, map *graph, int num)
{
    vector<int> ans(num, 0);

    for (int i = 0; i < ans.size(); i++)
    {
        if (graph[i].source == 0)
            ans[i] = 0;
        ans[i] = ans[i] < ee[graph[i].source] ? ee[graph[i].source] : ans[i];
    }

    return ans;
}
vector<int> convertLEtoL(vector<int> le, map *graph, int num)
{
    vector<int> ans(num, 9999);

    for (int i = 0; i < ans.size(); i++)
    {
        ans[i] = ans[i] > (le[graph[i].dest] - graph[i].dur) ? le[graph[i].dest] - graph[i].dur : ans[i];
    }

    return ans;
}
void readLine(List **in, map *graph, int *lineNum)
{
    string num;
    string str;
    getline(cin, str);
    istringstream input(str);
    vector<int> line;
    while (input >> num)
    {

        stringstream geek(num);
        int tmp;
        geek >> tmp;
        line.push_back(tmp);
    }
    if (!line.empty())
    {
        int activity = line[0];
        int source = line[1];
        int dest = line[2];
        int weight = line[3];
        // find eventNum
        eventNum = dest > eventNum ? dest : eventNum;
        // update head's count(predecessor number)
        in[dest]->u.count++;
        // insert new node
        insertToList(&in[source], dest, weight);
        // increase number of line have been read
        (*lineNum)++;
        // store data in map graph
        graph[activity - 1].source = source;
        graph[activity - 1].dest = dest;
        graph[activity - 1].dur = weight;
    }
}
void insertToList(List **list, int dest, int dur)
{
    List *node = (List *)malloc(sizeof(List));
    node->u.n.vertex = dest;
    node->u.n.dur = dur;

    node->next = (*list)->next;
    (*list)->next = node;
}