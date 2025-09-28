#include "VectorStore.h"
#include <iostream>
using namespace std;

// Action function dùng cho forEach
void printRecord(SinglyLinkedList<float>& vec, int rawLength, string& rawText) {
    cout << "Record: rawLength=" << rawLength
         << ", rawText=" << rawText
         << ", vector size=" << vec.size() << endl;
}

void testForEachWithNullEmbedding() {
    cout << "=== Test forEach khi embeddingFunction = nullptr ===" << endl;

    // Tạo VectorStore mà không có embedding function
    VectorStore store(5, nullptr);

    // Thêm vài rawText, nhưng preprocessing sẽ trả về nullptr
    store.addText("hello");
    store.addText("world");

    // Gọi forEach
    // Nếu code của bạn đã fix, nó sẽ KHÔNG crash, chỉ bỏ qua record vector=nullptr
    store.forEach(printRecord);

    cout << "Test passed: Không có crash, forEach bỏ qua record không hợp lệ" << endl;
}

int main() {
    testForEachWithNullEmbedding();
    return 0;
}
