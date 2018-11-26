#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

void printHeap(vector<int>);
void changeKey(vector<int> &, int, int);
int main()
{

    vector<int> heap;
    heap.push_back(-1); //don't store key in index 0's

    string num;
    int find_key;
    int change_key;
    string str;

    getline(cin, str);

    istringstream input(str);
    while (input >> num)
    {
        stringstream geek(num);
        int tmp;
        geek >> tmp;
        heap.push_back(tmp);
    }

    cin >> find_key >> change_key;
    changeKey(heap, find_key, change_key);
    printHeap(heap);

        return 0;
}
void changeKey(vector<int> &heap, int find, int change)
{
    int find_index;
    int biggest_child;

    for (int i = 1; i < heap.size(); i++)
    {
        if (heap[i] == find)
        {
            find_index = i;
            break;
        }
    }

    if (find == change)
    {
        return;
    }
    else if (find > change)
    {
        find_index = find_index * 2;
        while (find_index < heap.size())
        {
            if (find_index + 1 < heap.size())
            {
                biggest_child = heap[find_index + 1] > heap[find_index] ? heap[++find_index] : heap[find_index];
            }
            else
            {
                biggest_child = heap[find_index];
            }
            if (biggest_child > change)
            {
                heap[(int)(find_index / 2)] = biggest_child;
            }
            find_index = find_index * 2;
        }
        heap[find_index / 2] = change;
    }
    else
    { //find < change -> bubbling up
        while (heap[(int)(find_index / 2)] < change && find_index != 1)
        {
            heap[find_index] = heap[(int)(find_index / 2)];
            find_index = find_index / 2;
        }
        heap[find_index] = change;
    }
}
void printHeap(vector<int> heap)
{

    for (int i = 1; i < heap.size(); i++)
    {
        cout << heap[i] << " ";
    }
    cout << "\n";
}