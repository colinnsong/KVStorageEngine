#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <typename K, typename V>
class Node {
public:
    Node(K key, V value, int node_level);
    ~Node();
    K getKey() const;
    V getValue() const;
    void setValue(V value);

    Node<K, V>** forward;
    int level;  // 节点的层序号[0, _maxlevel-1]
private:
    K key;
    V value;
};

template <typename K, typename V>
Node<K, V>::Node(K key, V value, int level) {
    this->key = key;
    this->value = value;
    this->level = level - 1;
    this->forward = new Node<K, V>*[level];
    for (int i = 0; i < level; i++) {
        this->forward[i] = nullptr;
    }
}

template <typename K, typename V>
Node<K, V>::~Node() {
    /*
        如果forward数组中的指针也指向动态内存, 
        则需要先释放数组中指针的动态内存, 
        然后再释放forward数组的动态内存.
    */
    // for(int i = 0; i < this->level; i++)
    //    delete this->forward[i];
    delete[] this->forward;
}

template <typename K, typename V>
K Node<K, V>::getKey() const {
    return this->key;
}

template <typename K, typename V>
V Node<K, V>::getValue() const {
    return this->value;
}

template <typename K, typename V>
void Node<K, V>::setValue(V value) {
    this->value = value;
}

#endif