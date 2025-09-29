#include "VectorStore.h"
#include <iostream>
#include <cassert>
using namespace std;

// Hàm embedding đơn giản: chuyển ký tự thành số (a=1, b=2, ...)
SinglyLinkedList<float>* dummyEmbedding(const string& text) {
    auto* vec = new SinglyLinkedList<float>();
    for (char c : text) vec->add((float)(c - 'a' + 1));
    return vec;
}

void testTopKNearest() {
    cout << "=== Test topKNearest ===" << endl;

    // Tạo VectorStore dimension = 3
    VectorStore store(3, dummyEmbedding);

    // Thêm dữ liệu
    store.addText("abc"); // id=1, vec=[1,2,3]
    store.addText("abd"); // id=2, vec=[1,2,4]
    store.addText("aaa"); // id=3, vec=[1,1,1]

    // Query
    SinglyLinkedList<float> query;
    query.add(1); query.add(2); query.add(3);

    // ---- Case 1: Cosine similarity ----
    int* ids1 = store.topKNearest(query, 2, "cosine");
    cout << "Cosine top-2: " << ids1[0] << ", " << ids1[1] << endl;
    assert(ids1[0] == 0);  // "abc" gần nhất
    delete[] ids1;

    // ---- Case 2: Euclidean (L2) ----
    int* ids2 = store.topKNearest(query, 3, "euclidean");
    cout << "L2 top-3: " << ids2[0] << ", " << ids2[1] << ", " << ids2[2] << endl;
    assert(ids2[0] == 0);
    delete[] ids2;

    // ---- Case 3: Manhattan (L1) ----
    int* ids3 = store.topKNearest(query, 3, "manhattan");
    cout << "L1 top-3: " << ids3[0] << ", " << ids3[1] << ", " << ids3[2] << endl;
    assert(ids3[0] == 0);
    delete[] ids3;  

    // ---- Case 4: invalid k ----
    try {
        store.topKNearest(query, 0, "cosine");
        assert(false);
    } catch (const invalid_k_value& e) {
        cout << "Caught expected: " << e.what() << endl;
    }

    // ---- Case 5: invalid metric ----
    try {
        store.topKNearest(query, 1, "unknown");
        assert(false);
    } catch (const invalid_metric& e) {
        cout << "Caught expected: " << e.what() << endl;
    }

    // ---- Case 6: Tie-break (cùng distance) ----
    VectorStore store2(2, dummyEmbedding);
    store2.addText("aa"); // id=1, vec=[1,1]
    store2.addText("bb"); // id=2, vec=[2,2]
    store2.addText("cc"); // id=3, vec=[3,3]

    SinglyLinkedList<float> q2;
    q2.add(0); q2.add(0);

    int* ids4 = store2.topKNearest(q2, 3, "euclidean");
    cout << "Tie-break L2: " << ids4[0] << ", " << ids4[1] << ", " << ids4[2] << endl;
    // Nếu cùng distance, phải giữ nguyên thứ tự chèn
    assert(ids4[0] == 0);
    assert(ids4[1] == 1);
    assert(ids4[2] == 2);
    delete[] ids4;

    cout << "All topKNearest tests passed!" << endl;
}
int main() {
    testTopKNearest();   // hoặc testArrayList(), testSLL()...
    return 0;
}
