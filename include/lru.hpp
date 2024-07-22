// #include <iostream>
// #include <unordered_map>
// using namespace std;

// // 双向链表
// struct DListNode
// {
//     int key, value;
//     DListNode *prev, *next;
//     DListNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
//     DListNode(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}
// };

// class LRUCache {
// public:
//     LRUCache(int capacity);
//     int get(int key);
//     void put(int key, int value);
// private:
//     int capacity;
//     int size;
//     unordered_map<int, DListNode*> map;
//     DListNode *dummyhead, *dummytail;
//     void removeNode(DListNode* node);
//     void move2Head(DListNode* node);
// };