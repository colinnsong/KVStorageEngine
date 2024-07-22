#include "skiplist.hpp"
#include "node.hpp"

int main(){
    SkipList<string, string>* skiplist = new SkipList<string, string>(18);
    skiplist->loadFile();
    skiplist->displayList();
    delete skiplist;
    return 0;
}