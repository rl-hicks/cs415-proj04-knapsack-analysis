#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>


struct Item {
    int index;
    int value;
    int weight;
    double ratio;
};




using namespace std;

vector<int> loadData(const string& filename) {
    vector<int> numbers; // stores each word
    ifstream file(filename);

    if (file.is_open()) {
        int num;

        while (file >> num) {
            // int cleanedWord = cleanWord(word);

            //if (num != "") // isn't empty
            //{
            numbers.push_back(num);
            //}
        }

        
    } else {
        cerr << "File error: " << filename << endl;

    }

    return numbers;
}

void mergeSort(vector<Item>& items, vector<Item>& temp, int left, int right, long long& ops) {
    if (left >= right) return; // List has one record
    int mid = (left + right)/2; // Select midpoint
    mergeSort(items, temp, left, mid, ops); // Mergesort first half
    mergeSort(items, temp, (mid+1), right, ops); // Mergesort second half
    for (int i = left; i <= right; i++)  {// Copy subarray to temp
        temp[i] = items[i];
        ops++;
    }
    // Do the merge operation back to A
    int i1 = left;
    int i2 = mid + 1;
    for (int curr = left; curr <= right; curr++) {
        if (i1 == mid+1) {   // Left sublist exhausted
            items[curr] = temp[i2++];
            ops++;
        }
        else if (i2 > right) {  // Right sublist exhausted 
            items[curr] = temp[i1++];
            ops++;
        }
        else {
            ops++;
        
            if (temp[i1].ratio >= temp[i2].ratio) {   // descending ratio
                items[curr] = temp[i1++];
                ops++; 
            }
            else {
                items[curr] = temp[i2++];
                ops++;
            }
        }
    }   
}


// =================================
using std::vector;
using std::swap;

int leftChild(int pos) {
    return 2 * pos + 1;
}

int rightChild(int pos) {
    return 2 * pos + 2;
}

int parent(int pos) {
    return (pos - 1) / 2;
}

bool isLeaf(const vector<Item>& heap, int pos) {
    int n = heap.size();
    return leftChild(pos) >= n;
}

bool isGreaterThan(const vector<Item>& heap, int i, int j) {
    return heap[i].ratio > heap[j].ratio;
}

void siftDown(vector<Item>& heap, int pos) {
    int n = heap.size();

    assert(pos >= 0 && pos < n && "Invalid heap position");

    while (!isLeaf(heap, pos)) {
        int child = leftChild(pos);

        if (child + 1 < n && isGreaterThan(heap, child + 1, child)) {
            child = child + 1;
        }

        if (!isGreaterThan(heap, child, pos)) {
            return;
        }

        swap(heap[pos], heap[child]);
        pos = child;
    }
}

void buildHeap(vector<Item>& heap, long long& heapOps) {
    if (heap.empty()) return;
    int n = heap.size();

    for (int i = parent(n - 1); i >= 0; i--) {
        siftDown(heap, i, heapOps);
    }
}

Item removeMax(vector<Item>& heap) {
    assert(!heap.empty() && "Heap is empty; cannot remove");

    int lastIndex = heap.size() - 1;

    swap(heap[0], heap[lastIndex]);

    Item maxValue = heap[lastIndex];
    heap.pop_back();

    if (!heap.empty()) {
        siftDown(heap, 0);
    }

    return maxValue;
}
// =================================





int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Incorrect number of arguments" << endl;
        return 1;
    }

    int num =-1;
    if (argc > 1) {
        try {
            num = stoi(argv[1]);
            // std::cout << "Integer: " << num << std::endl;
        } catch (const exception& e) {
            std::cerr << "Invalid input: " << e.what() << std::endl;
            return 1;
        }
    }


    vector<int> fileC, fileV, fileW;
    string fileName1, fileName2, fileName3;
    if (num < 10) {
        fileName1 = "data/p0" + to_string(num) + "_c.txt";
        fileName2 = "data/p0" + to_string(num) + "_v.txt";
        fileName3 = "data/p0" + to_string(num) + "_w.txt";
        
        
        fileC = loadData(fileName1);
        fileV = loadData(fileName2);
        fileW = loadData(fileName3);
    }
    else {

        fileName1 = "data/p" + to_string(num) + "_c.txt";
        fileName2 = "data/p" + to_string(num) + "_v.txt";
        fileName3 = "data/p" + to_string(num) + "_w.txt";

        fileC = loadData(fileName1);
        fileV = loadData(fileName2);
        fileW = loadData(fileName3);

    }

    if (fileC.empty() || fileV.empty() || fileW.empty()) {

            cerr << "File error: Corrosponding file does not exist." << endl;
            return 1;
    }





    int capacity = fileC[0];

    if (fileC.size() != 1) {
        cerr << "Input error: capacity file should contain exactly one integer." << endl;
        return 1;
    }

    if (fileV.size() != fileW.size()) {
        cerr << "Input error: values and weights have different lengths." << endl;
        return 1;
    }

    vector<Item> items;

    // Loads file V and W contents into vector of struct Item
    for (size_t i = 0; i < fileV.size(); i++) {
        Item item;
        item.index = i + 1; 
        item.value = fileV[i];
        item.weight = fileW[i];
        if (fileW[i] == 0) {
            cerr << "Input error: item " << i + 1 << " has zero weight." << endl;
            return 1;
        }
        item.ratio = static_cast<double>(item.value) / item.weight;

    items.push_back(item);

    }

    // 2a
    // ==========================================================
    cout << "Knapsack capacity = " << capacity
     << ". Total number of items = " << items.size() << endl;

    /*
    for (const Item& item : items) {
        cout << item.index << " "
             << item.value << " "
             << item.weight << " "
             << item.ratio << endl;
    }
    */

    cout << endl << "Mergesort: " << endl;

    vector<Item> temp(items.size());

    // Merge sort Decending Order
    long long mergeSortOps = 0;
    if (!items.empty()) {
        mergeSort(items, temp, 0, items.size() - 1, mergeSortOps);
    }

    // cout sorted list
    for (const Item& item : items) {
        cout << item.index << " " << item.ratio << endl;
    }

    // figure out Task 2A
    vector<int> ksBag;
    
    int remainingCapacity = capacity;
    int totalValue = 0;
    for (const Item& item : items) {
        
        if (item.weight <= remainingCapacity) {
            ksBag.push_back(item.index);
            remainingCapacity -= item.weight;
            totalValue += item.value;
            mergeSortOps += 3; 
        }

        else {
            break;
        }
    }

    // sort results of whats in the ksBag
    sort(ksBag.begin(), ksBag.end());



    cout << "(2a) Greedy Approach Optimal value: " << totalValue << endl;
    cout << "(2a) Greedy Approach Optimal subset: {";

    //cout Greedy approach results
    for (size_t i = 0; i < ksBag.size(); i++) {

        cout << ksBag[i];

        if (i != ksBag.size() - 1)
            cout << ", ";
    }

    cout << "}" << endl << endl; 
    
    cout << "(2a) Greedy Approach Total Basic Ops: " << mergeSortOps << endl;
    
    cout << endl << endl;

    // 2b
    // ============================================


    vector<Item> heap = items;
    buildHeap(heap, heapOps);
    long long heapOps = 0;

    vector<int> heapBag;

    int heapRemainingCapacity = capacity;
    int heapTotalValue = 0;

    while (!heap.empty()) {

        Item item = removeMax(heap);

        if (item.weight <= heapRemainingCapacity) {
            heapBag.push_back(item.index);
            heapRemainingCapacity -= item.weight;
            heapTotalValue  += item.value;
        }

        else {
            break;
        }
    }

    sort(heapBag.begin(), heapBag.end());

    cout << "(2b) Heap-based Greedy Approach Optimal value: " << heapTotalValue << endl;

    cout << "(2b) Heap-based Greedy Approach Optimal subset: {";



    for (size_t i = 0; i < heapBag.size(); i++) {

    cout << heapBag[i];

    if (i != heapBag.size() - 1)
        cout << ", ";
    }

    cout << "}" << endl;



    return 0;

}

