#include "VectorStore.h"
#include <cassert>
#include <iostream>

// embedding giả lập
SinglyLinkedList<float>* dummyEmbedding(const std::string& text) {
    auto* vec = new SinglyLinkedList<float>();
    for (char c : text) {
        vec->add(static_cast<float>(c % 10)); // mã ASCII % 10
    }
    return vec;
}
void testFindNearest() {
    std::cout << "\n=== Test findNearest ===\n";

    auto embed = [](const std::string& text) {
        auto* vec = new SinglyLinkedList<float>();
        for (char c : text) vec->add((float)(c % 5));
        return vec;
    };

    VectorStore store(3, embed);

    store.addText("abc");  // index=0
    store.addText("bcd");  // index=1
    store.addText("xyz");  // index=2

    SinglyLinkedList<float>* q = embed("abc");
    int idCos = store.findNearest(*q, "cosine");
    int idL1  = store.findNearest(*q, "manhattan");
    int idL2  = store.findNearest(*q, "euclidean");

    assert(idCos == 0);
    assert(idL1  == 0);
    assert(idL2  == 0);

    std::cout << "findNearest passed!\n";
}
void testTopKNearest() {
    std::cout << "\n=== Test topKNearest ===\n";

    auto embed = [](const std::string& text) {
        auto* vec = new SinglyLinkedList<float>();
        for (char c : text) vec->add((float)(c % 5));
        return vec;
    };

    VectorStore store(3, embed);

    store.addText("abc");  // index=0
    store.addText("bcd");  // index=1
    store.addText("xyz");  // index=2
    store.addText("aaa");  // index=3

    SinglyLinkedList<float>* q = embed("abc");

    // K=2 cosine
    int* ids1 = store.topKNearest(*q, 2, "cosine");
    assert(ids1[0] == 0);  // chính nó
    std::cout << "cosine top[0] = " << ids1[0] << "\n";
    delete[] ids1;

    // K=3 manhattan
    int* ids2 = store.topKNearest(*q, 3, "manhattan");
    assert(ids2[0] == 0);  // chính nó
    std::cout << "manhattan top[0] = " << ids2[0] << "\n";
    delete[] ids2;

    // Trường hợp k > count → throw
    bool thrown = false;
    try {
        store.topKNearest(*q, 10, "cosine");
    } catch (const invalid_k_value&) {
        thrown = true;
    }
    assert(thrown);

    std::cout << "topKNearest invalid k passed!\n";
}


int main() {
    testFindNearest();
    testTopKNearest();
    std::cout << "All findNearest & topKNearest test cases passed!\n";
    return 0;
}

