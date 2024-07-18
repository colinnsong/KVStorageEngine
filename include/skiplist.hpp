#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "node.hpp"
#include <fstream>
#include <iostream>
using namespace std;

template <typename K, typename V>
class SkipList {
public:
    SkipList(int maxlevel);            // 构造函数
    ~SkipList();                       // 析构函数
    int getRandomLevel();              // 获取节点的随机层级
    Node<K, V> *createNode(K, V, int); // 节点创建
    bool insertNode(K, V);           // 插入节点
    void displayList();                // 展示节点
    bool searchNode(K);             // 搜索节点
    void deleteNode(K);             // 删除节点
    void dumpFile();                   // 持久化数据到文件
    void loadFile();                   // 从文件加载数据
    void clear(Node<K, V> *);          // 递归删除节点
    int size();                        // 跳表中的节点个数
private:
    int _maxlevel;              // 跳表允许的最大层数
    int _curlevel;              // 跳表当前的最大层序号[0, _maxlevel-1]
    Node<K, V> *_header;        // 跳表的头节点(跳表搜索的入口不存储数据)
    int _nodecount;             // 跳表中组织的所有节点的数量
    std::ofstream _filewriter;  // 文件写入器
    std::ifstream _filereader;  // 文件读取器
};

template <typename K, typename V>
SkipList<K, V>::SkipList(int maxlevel) {
    _maxlevel = maxlevel;
    _curlevel = 0;
    _nodecount = 0;
    _header = new Node<K, V>(0, 0, _maxlevel);
}

template <typename K, typename V>
SkipList<K, V>::~SkipList() {
    Node<K, V>* temp = _header;
    while(temp){
        _header = _header->forward[0];
        delete temp;
        temp = _header;
    }
}

// 获取节点的随机层级
template <typename K, typename V>
int SkipList<K, V>::getRandomLevel(){
    // 每个节点至少出现在第一层。
    int k = 1;
    // 使用 rand() % 2 实现抛硬币效果决定是否升层。
    while (rand() % 2) {
        k++;
    }
    k = (k < _maxlevel) ? k : _maxlevel;
    return k - 1;
}

// 节点创建
template <typename K, typename V>
Node<K, V>* SkipList<K, V>::createNode(K key, V value, int level){
    Node<K, V>* node = new Node<K, V>(key, value, level);
    return node;
}

// 搜索节点
template <typename K, typename V>
bool SkipList<K, V>::searchNode(K key){
    Node<K, V>* cur = _header;
    // 从最高层开始搜索到最低层
    for (int i = _curlevel; i >= 0; i--) {
        while (cur->forward[i] && cur->forward[i]->getKey() < key) {
            cur = cur->forward[i];
        }
    }
    // 到最低层之后由于跳表的特性只需要比较下一个节点的key值即可
    cur = cur->forward[0];
    if (cur && cur->getKey() == key) {
        return true;
    }
    return false;
}

// 插入节点
template <typename K, typename V>
bool SkipList<K, V>::insertNode(K key, V value){
    Node<K, V>* cur = _header;
    // 记录每层插入位置的前驱节点
    Node<K, V>* update[_maxlevel];
    for(int i = 0; i < _maxlevel; i++)
        update[i] = nullptr;
    // 从最高层开始搜索到最低层
    for (int i = _curlevel; i >= 0; i--) {
        while (cur->forward[i] && cur->forward[i]->getKey() < key) {
            cur = cur->forward[i];
        }
        update[i] = cur;
    }
    // 检查是否已经存在该节点
    cur = cur->forward[0];
    if (cur && cur->getKey() == key) {
        return false;
    }
    else{
        // 随机生成节点层级
        int level = getRandomLevel();
        // 如果随机生成的层级比跳表的层级还高, 则需要更新跳表的层级
        if (level > _curlevel) {
            for(int i = _curlevel + 1; i <= level; i++){
                update[i] = _header;
            }
            _curlevel = level;
        }
        // 创建新节点
        Node<K, V>* isrnode = createNode(key, value, level + 1);
        // 在每层的updata节点后插入新节点
        for(int i = 0; i <= level; i++){
            isrnode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = isrnode;
        }
        _nodecount++;
    }
    return true;
}

// 删除节点
template <typename K, typename V>
void SkipList<K, V>::deleteNode(K key) {
    Node<K, V>* cur = _header;
    // 记录每层删除位置的前驱节点
    Node<K, V>* update[_maxlevel];
    for(int i = 0; i < _maxlevel; i++)
        update[i] = nullptr;
    // 从最高层开始搜索到最低层
    for (int i = _curlevel; i >= 0; i--) {
        while (cur->forward[i] && cur->forward[i]->getKey() < key) {
            cur = cur->forward[i];
        }
        update[i] = cur;
    }
    // 检查是否已经存在该节点
    cur = cur->forward[0];
    if (!cur || cur->getKey() != key) {
        cout << "No such key in skiplist" << endl;
        return;
    }
    else{
        for(int i = 0; i <= _curlevel; i++){
            if(update[i]->forward[i] != cur){
                break;
            }
            update[i]->forward[i] = cur->forward[i];
        }
        // 调整跳表的层级
        while (_curlevel > 0 && _header->forward[_curlevel] == nullptr) {
            _curlevel--;
        }
        delete cur;
        _nodecount--;
    }
}

// 遍历节点
template <typename K, typename V>
void SkipList<K, V>::displayList() {
    for(int i = _curlevel; i >= 0; i--){
        Node<K, V>* node = _header->forward[i];
        cout << "Level " << i << ": ";
        while(node){
            cout << node->getKey() << ":" << node->getValue() << ";";
            node = node->forward[i];
        }
        cout << endl;
    }
}

#endif