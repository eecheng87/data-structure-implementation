#include <iostream>

using namespace std;
void merge_sort(int[], int, int);
void merge(int[], int, int, int);
/**
 * merge sort: contain two function 
 * time complexity: O(nlogn)
 **/
void quick_sort(int[], int, int);
int partition(int[], int, int);
/**
 * qucik sort : contain two function
 * time complexity: best case , average case->O(nlogn) , worst case->O(n*n) 
 * */
void selection_sort(int[], int);
/**
 * selection sort
 * time complexity: O(n*n)
 * */
void bubble_sort(int[], int);
/**
 * bubble sort
 * time complexity: O(n*n)
 * */
void insertion_sort(int[], int);
/**
*insertion sort
*best condition: O(n)
*worst condition: O(n*n)
 **/
void printArr(int[], int);
int main()
{

    int arr[] = {22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70};

    //insertion_sort(arr, 14);
    //bubble_sort(arr, 14);
    //selection_sort(arr, 14);
    //quick_sort(arr, 0, 13);
    merge_sort(arr, 0, 13);
    printArr(arr, 14);

    system("pause");

    return 0;
}
void printArr(int arr[], int n)
{

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}
void selection_sort(int arr[], int n)
{
    int tmp;
    int min_index;
    for (int i = 0; i < n - 1; i++)
    {
        min_index = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[min_index] > arr[j])
            {
                min_index = j;
            }
        }
        tmp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = tmp;
    }
}
void bubble_sort(int arr[], int n)
{
    int tmp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
void insertion_sort(int arr[], int n)
{
    int j;
    int tmp;

    for (int i = 1; i < n; i++)
    {
        tmp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = tmp;
    }
}

int partition(int arr[], int low, int high)
{
    int tmp;
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;

    return i + 1;
}
void quick_sort(int arr[], int low, int high)
{

    if (low < high)
    {
        int pivot = partition(arr, low, high);

        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}
void merge_sort(int arr[], int left, int right)
{

    if (left < right)
    {
        int m = (left + right) / 2;
        merge_sort(arr, left, m);
        merge_sort(arr, m + 1, right);
        merge(arr, left, m, right);
    }
}
void merge(int arr[], int left, int middle, int right)
{
    int i, j, k; //respectedly index for L,R,arr

    //calculate two copy array's size
    int n = middle - left + 1;
    int m = right - middle; //not including middle

    int L[n], R[m];

    //copy arr to L and R array
    for (i = 0; i < n; i++)
    {
        L[i] = arr[left + i];
    }

    for (j = 0; j < m; j++)
    {
        R[j] = arr[middle + 1 + j];
    }

    //merge L and R into arr

    i = 0, j = 0, k = left;

    while (i < n && j < m)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++; //increment arr's current index
    }

    //handle remaining data

    while (i < n)
    {
        arr[k] = L[i];
        k++;
        i++;
    }

    while (j < m)
    {
        arr[k] = R[j];
        k++;
        j++;
    }
}