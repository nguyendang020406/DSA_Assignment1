#include "VectorStore.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
using namespace std;

// ===== Helper assert =====
void assertThrows(const string& testName, function<void()> func, const string& expectedMsg) {
    try {
        func();
        cout << "[FAIL] " << testName << " (no exception thrown)" << endl;
    } catch (const std::exception& ex) {
        if (expectedMsg.empty() || expectedMsg == ex.what())
            cout << "[PASS] " << testName << endl;
        else
            cout << "[FAIL] " << testName 
                 << "\n  Expected exception: " << expectedMsg 
                 << "\n  Actual: " << ex.what() << endl;
    }
}

// Dummy embedding
SinglyLinkedList<float>* dummyEmbedding(const string& rawText) {
    auto* vec = new SinglyLinkedList<float>();
    for (char c : rawText) vec->add((float)((int)c % 10));
    return vec;
}

int main() {
    cout << "=== TESTING START ===" << endl;

    // ===== ArrayList exception =====
    {
        ArrayList<int> arr;
        arr.add(10);
        assertThrows("ArrayList removeAt(-1)", [&]() { arr.removeAt(-1); }, "Index is invalid!");
        assertThrows("ArrayList removeAt(out of range)", [&]() { arr.removeAt(5); }, "Index is invalid!");
        assertThrows("ArrayList get(out of range)", [&]() { arr.get(3); }, "Index is invalid!");
    }

    // ===== SinglyLinkedList exception =====
    {
        SinglyLinkedList<int> sll;
        sll.add(1); sll.add(2);
        assertThrows("SLL removeAt(-1)", [&]() { sll.removeAt(-1); }, "Index is invalid!");
        assertThrows("SLL removeAt(out of range)", [&]() { sll.removeAt(5); }, "Index is invalid!");
        assertThrows("SLL get(out of range)", [&]() { sll.get(10); }, "Index is invalid!");
    }

    // ===== VectorStore exception =====
    {
        VectorStore store(5, dummyEmbedding);
        store.addText("abc");

        assertThrows("VectorStore getVector(-1)", [&]() { store.getVector(-1); }, "Index is invalid!");
        assertThrows("VectorStore getRawText(out of range)", [&]() { store.getRawText(3); }, "Index is invalid!");
        assertThrows("VectorStore removeAt(out of range)", [&]() { store.removeAt(2); }, "Index is invalid!");
        assertThrows("VectorStore updateText(out of range)", [&]() { store.updateText(5, "xxx"); }, "Index is invalid!");
        
        // invalid k
        SinglyLinkedList<float>* q = dummyEmbedding("zzz");
        assertThrows("VectorStore topKNearest(k=0)", [&]() { store.topKNearest(*q, 0, "cosine"); }, "Invalid k value!");
        assertThrows("VectorStore topKNearest(k > size)", [&]() { store.topKNearest(*q, 5, "cosine"); }, "Invalid k value!");
        assertThrows("VectorStore topKNearest(metric error)", [&]() { store.topKNearest(*q, 1, "unknown"); }, "Invalid metric!");
        delete q;
    }

    cout << "=== TESTING END ===" << endl;
    return 0;
}
