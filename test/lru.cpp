// #include "lru.hpp"

// LRUCache::LRUCache(int capacity) {
//     this->capacity = capacity;
//     size = 0;
//     dummyhead = new DListNode();
//     dummytail = new DListNode();
//     dummyhead->next = dummytail;
//     dummytail->prev = dummyhead;
// }

// void LRUCache::removeNode(DListNode* node){
//     node->prev->next = node->next;
//     node->next->prev = node->prev;
// }

// void LRUCache::move2Head(DListNode* node){
//     node->next = dummyhead->next;
//     node->prev = dummyhead;
//     dummyhead->next->prev = node;
//     dummyhead->next = node;
// }

// int LRUCache::get(int key) {
//     if(map.find(key) == map.end()){
//         return -1;
//     }
//     else{
//         DListNode* node = map[key];
//         removeNode(node);
//         move2Head(node);
//         return node->value;
//     }
// }

// void LRUCache::put(int key, int value) {
//     if(map.find(key) != map.end()){
//         map[key]->value = value;
//         removeNode(map[key]);
//         move2Head(map[key]);
//     }
//     else{
//         DListNode* node = new DListNode(key, value);
//         map.insert({key, node});
//         move2Head(node);
//         size++;
//         if(size > capacity){
//             DListNode* node = dummytail->prev;
//             removeNode(node);
//             map.erase(node->key);
//             delete node;
//             size--;
//         }
//     }
// }

// int main(){
//     LRUCache* cache = new LRUCache(2);
//     cache->put(1, 1);
//     cache->put(2, 2);
//     cout << cache->get(1) << endl;
//     cache->put(3, 3);
//     cout << cache->get(2) << endl;
//     cache->put(4, 4);
//     delete cache;
// }