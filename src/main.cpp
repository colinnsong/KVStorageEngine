#include "skiplist.hpp"
#include "node.hpp"
#include <iostream>
using namespace std;

int main(){
    int N, K, M;
    cin >> N >> K >> M;
    SkipList<int, int>* skiplist = new SkipList<int, int>(18);
    for(int i = 0; i < N; i++){
        int key, value;
        cin >> key >> value;
        if(skiplist->insertNode(key, value)){
            cout << "Insert Success" << endl;
        }
        else{
            cout << "Insert Failed" << endl;
        }
    }
    skiplist->displayList();
    delete skiplist;
    return 0;
}