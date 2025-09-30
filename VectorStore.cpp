#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

//Constructor
template <class T>
ArrayList<T>::ArrayList(int initCapacity) {
    this->capacity = initCapacity;
    this->count = 0;       
    this->data = new T[capacity];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    this->capacity = other.capacity;
    this->count = other.count;
    this->data = new T[capacity];  // cấp phát mảng mới
    for (int i = 0; i < count; i++) {
        this->data[i] = other.data[i]; // copy từng phần tử
    }
}
template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other) {
    if (this != &other) {
        ensureCapacity(other.count); // đảm bảo đủ chỗ

        this->count = other.count;
        for (int i = 0; i < count; i++) {
            this->data[i] = other.data[i]; // copy từng phần tử
        }
    }
    return *this;
}


// Destructor
template <class T>
ArrayList<T>::~ArrayList() {
    delete[] data;   // giải phóng mảng
    data = nullptr;  // an toàn
    capacity = 0;
    count = 0;
}

// EnsureCapacity
template <class T>
void ArrayList<T>::ensureCapacity(int cap) {
    if (cap <= this->capacity) return;

    // Tăng capacity lên ít nhất cap (theo hệ số 1.5)
    int newCapacity = this->capacity;
    while (newCapacity < cap) {
        newCapacity = (int)(newCapacity * 1.5);
    }

    // Cấp phát mảng mới
    T* newData = new T[newCapacity];

    // Copy dữ liệu cũ
    for (int i = 0; i < this->count; i++) {
        newData[i] = this->data[i];
    }

    // Giải phóng mảng cũ
    delete[] this->data;

    // Gán lại
    this->data = newData;
    this->capacity = newCapacity;
}

template <class T>
void ArrayList<T>::add(T e) {
    ensureCapacity(count + 1);  // đảm bảo đủ chỗ
    data[count] = e;            // thêm vào cuối
    count++;                    // tăng số phần tử
}
template <class T>
void ArrayList<T>::add(int index, T e) {
    if (index < 0 || index > count) {
        throw std::out_of_range("Index is invalid!");
    }

    ensureCapacity(count + 1); // đảm bảo có chỗ

    // Dịch các phần tử từ index → phải
    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }

    // Gán phần tử mới
    data[index] = e;
    count++;
}

template <class T>
T ArrayList<T>::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }

    T removedItem = data[index];

    // Dịch trái các phần tử sau index
    for (int i = index; i < count - 1; i++) {
        data[i] = data[i + 1];
    }

    count--; // giảm số phần tử
    return removedItem;
}
template <class T>
int ArrayList<T>::size() const {
    return count;
}
template <class T>
bool ArrayList<T>::empty() const{
    return count == 0;
}
template <class T>
void ArrayList<T>::clear() {
    delete[] data;              
    capacity = 10;              
    count = 0;
    data = new T[capacity];     
}
template <class T>
const T& ArrayList<T>::get(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }
    return data[index];
}
template <class T>
void ArrayList<T>::set(int index, T e) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }
    data[index] = e;
}
template <class T>
int ArrayList<T>::indexOf (T item) const {
    for (int i = 0; i < count; i++) {
        if (data[i] == item) return i;
    }
    return -1;
}
template <class T>
bool ArrayList<T>::contains (T item) const{
    return indexOf(item) != -1;
}


template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin() {
    return Iterator(this, 0);
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end() {
    return Iterator(this, count);
}
// đã check


// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index) {
    if (pList && (index < 0 || index > pList->count)) {
        throw std::out_of_range("Index is invalid!");
    }
    this->pList = pList;
    this->cursor = index;
}

template <class T>
typename ArrayList<T>::Iterator&    
ArrayList<T>::Iterator::operator=(const Iterator& other) {
    if (this != &other) {
        this->pList = other.pList;
        this->cursor = other.cursor;
    }
    return *this;
}
template <class T>
T& ArrayList<T>::Iterator::operator*() {
    if (!pList || cursor < 0 || cursor >= pList->count) {
        throw std::out_of_range("Iterator is out of range!");
    }
    return pList->data[cursor];
}
template <class T>
bool ArrayList<T>::Iterator::operator!=(const Iterator& other) const {
    return this->pList != other.pList || this->cursor != other.cursor;
}
template <class T>
typename ArrayList<T>::Iterator& 
ArrayList<T>::Iterator::operator++() {
    if (!pList || cursor >= pList->count) {
        throw std::out_of_range("Iterator cannot advance past end!");
    }
    ++cursor;
    return *this;
}
template <class T>
typename ArrayList<T>::Iterator 
ArrayList<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);  // gọi operator++()
    return temp;
}
// Tiền tố --
template <class T>
typename ArrayList<T>::Iterator& 
ArrayList<T>::Iterator::operator--() {
    if (cursor == 0) {
        throw std::out_of_range("Iterator cannot move before begin!");
    }
    if (cursor == pList->count) {
        cursor = pList->count - 1;
    } else {
        --cursor;
    }
    return *this;
}

// Hậu tố --
template <class T>
typename ArrayList<T>::Iterator 
ArrayList<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);  // gọi lại phiên bản tiền tố
    return temp;
}
// đã check
// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head = tail = nullptr;
    count = 0;
}   

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}   

template <class T>
void SinglyLinkedList<T>::add(T e) {
    Node* newNode = new Node(e);
    if (!head) head = tail = newNode;
    else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

template <class T>
void SinglyLinkedList<T>::add(int index, T e) {
    if (index < 0 || index > count) {
        throw std::out_of_range("Index is invalid!");
    }

    Node* newNode = new Node(e);

    if (index == 0) {
        newNode->next = head;
        head = newNode;
        if (count == 0) tail = newNode;
    } else {
        Node* prev = head;
        for (int i = 0; i < index - 1; i++) prev = prev->next;

        newNode->next = prev->next;
        prev->next = newNode;
        if (newNode->next == nullptr) tail = newNode;
    }
    count++;
}
template <class T>
T SinglyLinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }

    Node* removed;
    if (index == 0) {
        removed = head;
        head = head->next;
        if (count == 1) tail = nullptr;
    } else {
        Node* prev = head;
        for (int i = 0; i < index - 1; i++) prev = prev->next;
        removed = prev->next;
        prev->next = removed->next;
        if (removed == tail) tail = prev;
    }

    T val = removed->data;
    delete removed;
    count--;
    return val;
}
template <class T>
bool SinglyLinkedList<T>::removeItem(T item) {
    if (!head) return false;

   
    if (head->data == item) {
        Node* tmp = head;
        head = head->next;
        if (tmp == tail) tail = nullptr;
        delete tmp;
        count--;
        return true;
    }

    Node* prev = head;
    while (prev->next && !(prev->next->data == item)) {  
        prev = prev->next;
    }

    if (prev->next) {
        Node* tmp = prev->next;
        prev->next = tmp->next;
        if (tmp == tail) tail = prev;
        delete tmp;
        count--;
        return true;
    }
    return false;
}

template <class T>
bool SinglyLinkedList<T>::empty() const {
    return count == 0;
}

template <class T>
int SinglyLinkedList<T>::size() const {
    return count;
}

template <class T>
void SinglyLinkedList<T>::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

template <class T>
const  T& SinglyLinkedList<T>::get(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }
    Node* cur = head;
    for (int i = 0; i < index; i++) cur = cur->next;
    return cur->data;
}

template <class T>
int SinglyLinkedList<T>::indexOf(T item) const {
    Node* cur = head;
    int idx = 0;
    while (cur) {
        if (cur->data == item) return idx;
        cur = cur->next;
        idx++;
    }
    return -1;
}
template <class T>
bool SinglyLinkedList<T>::contains(T item) const {
    return indexOf(item) != -1;
}

// ArrayList
template <class T>
std::string ArrayList<T>::toString(std::string (*item2str)(T&)) const {
    if (count == 0) return "[]";  

    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < count; i++) {
        if (item2str) oss << item2str(data[i]);
        else oss << data[i];   
        if (i < count - 1) oss << ", ";
    }
    oss << "]";
    return oss.str();
}

// SinglyLinkedList
template <class T>
std::string SinglyLinkedList<T>::toString(std::string (*item2str)(T&)) const {
    if (head == nullptr) return "";   

    std::ostringstream oss;
    Node* cur = head;
    while (cur) {
        if (item2str) oss << "[" << item2str(cur->data) << "]";
        else oss << "[" << cur->data << "]";

        if (cur->next) oss << "->";
        cur = cur->next;
    }
    return oss.str();
}

// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node) {
    this -> current = node;
}   

template <class T>
typename SinglyLinkedList<T>::Iterator& 
SinglyLinkedList<T>::Iterator::operator=(const Iterator& other) {
    if (this != &other) {
        this->current = other.current;
    }
    return *this;
}

template <class T>
T& SinglyLinkedList<T>::Iterator::operator*() {
    if (!current) throw std::out_of_range("Iterator is out of range!");
    return current->data;
}

template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return this->current != other.current;
}

template <class T>
typename SinglyLinkedList<T>::Iterator& 
SinglyLinkedList<T>::Iterator::operator++() {
    if (!current) throw std::out_of_range("Iterator cannot advance past end!");
    current = current->next;
    return *this;
}

template <class T>
typename SinglyLinkedList<T>::Iterator 
SinglyLinkedList<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);  
    return temp;
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() const{
    return Iterator(head);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() const{
    return Iterator(nullptr);
}



// ----------------- VectorStore Implementation -----------------

//  constructor cho Vector Record
VectorStore::VectorRecord::VectorRecord(int id, const string& rawText, SinglyLinkedList<float>* vector) {
    this->id = id;
    this->rawText = rawText;
    this->rawLength = (int)rawText.size();
    this->vector = vector;
}

VectorStore::VectorStore(int dimension , EmbedFn embeddingFunction) {
    this -> dimension = dimension;
    this -> embeddingFunction = embeddingFunction;
    this -> count = 0;
    this -> nextId = 1;
}

VectorStore::~VectorStore() {
    clear();
}
int VectorStore::size() const{
    return count;
}
bool VectorStore::empty() const{
    return count == 0 ;
}
void VectorStore::clear(){
    for (int i=0;i< records.size();i++){
        delete records.get(i)->vector;
        delete records.get(i);
    }
    records.clear();
    count =0;
}  
// đã check

SinglyLinkedList<float>* VectorStore::preprocessing(string rawText) {
    if (!embeddingFunction) return nullptr;

    SinglyLinkedList<float>* vec = embeddingFunction(rawText);

    // Chuẩn hóa kích thước
    while (vec->size() > dimension) {
        vec->removeAt(vec->size() - 1);
    }
    while (vec->size() < dimension) {
        vec->add(0.0f);
    }

    return vec;
}
void VectorStore::addText(string rawText) {
    SinglyLinkedList<float>* vec = preprocessing(rawText);

    // Tìm id lớn nhất hiện có
    int maxId = 0;
    for (int i = 0; i < count; i++) {
        int curId = records.get(i)->id;
        if (curId > maxId) maxId = curId;
    }

    // id mới = id lớn nhất + 1
    int newId = maxId + 1;

    VectorRecord* rec = new VectorRecord(newId, rawText, vec);
    records.add(rec);
    count++;
}

SinglyLinkedList<float>& VectorStore::getVector(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }
    return *(records.get(index)->vector);
}
// đã check

string VectorStore::getRawText(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }
    return records.get(index)->rawText;
}
// đã check

int VectorStore::getId(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }
    return records.get(index)->id;
}
// đã check

bool VectorStore::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }
    VectorRecord* rec = records.get(index);
    delete rec->vector; 
    delete rec;         
    records.removeAt(index);
    count--;

    return true;
}


bool VectorStore::updateText(int index, string newRawText) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is invalid!");
    }

    VectorRecord* rec = records.get(index);
    delete rec->vector; // giải phóng vector cũ

    rec->rawText = newRawText;
    rec->rawLength = (int)newRawText.size();
    rec->vector = preprocessing(newRawText);

    return true;
}

void VectorStore::setEmbeddingFunction(EmbedFn newEmbeddingFunction) {
    this->embeddingFunction = newEmbeddingFunction;
} // Phương thức này dễ
// đã check

void VectorStore::forEach(void (*action)(SinglyLinkedList<float>&, int, string&)) {
    for (int i = 0; i < count; i++) {
        VectorRecord* rec = records.get(i);
        if (rec->vector) {  // chỉ xử lý nếu vector tồn tại
            action(*(rec->vector), rec->rawLength, rec->rawText);
        }
    }
}
// đã check

// Phần hiện thức phương thức tính khoảng cách.
double VectorStore::cosineSimilarity(const SinglyLinkedList<float>& v1,
                                     const SinglyLinkedList<float>& v2) const {
    // if (v1.size() != v2.size()) throw std::invalid_argument("Dimension mismatch");

    auto it1 = v1.begin();
    auto it2 = v2.begin();

    double dot = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2) {
        double a = *it1;
        double b = *it2;
        dot   += a * b;
        norm1 += a * a;
        norm2 += b * b;
    }
    if (norm1 == 0 || norm2 == 0) return 0.0;
    return dot / (sqrt(norm1) * sqrt(norm2));
}


double VectorStore::l1Distance(const SinglyLinkedList<float>& v1,
                               const SinglyLinkedList<float>& v2) const {
    // if (v1.size() != v2.size()) throw std::invalid_argument("Dimension mismatch");

    auto it1 = v1.begin();
    auto it2 = v2.begin();

    double dist = 0.0;
    for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2) {
        dist += fabs(*it1 - *it2);
    }
    return dist;
}
double VectorStore::l2Distance(const SinglyLinkedList<float>& v1,
                               const SinglyLinkedList<float>& v2) const {
    // if (v1.size() != v2.size()) throw std::invalid_argument("Dimension mismatch");

    auto it1 = v1.begin();
    auto it2 = v2.begin();

    double sumSq = 0.0;
    for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2) {
        double diff = *it1 - *it2;
        sumSq += diff * diff;
    }
    return sqrt(sumSq);
}
int VectorStore::findNearest(const SinglyLinkedList<float>& query, const string& metric) const {
    double bestScore;
    int bestIndex = -1;

    if (metric == "cosine") bestScore = -1e9;
    else bestScore = 1e18;

    for (int i = 0; i < count; i++) {
        VectorRecord* rec = records.get(i);
        double score = 0.0;

        if (metric == "cosine") {
            score = cosineSimilarity(query, *(rec->vector));
            if (score > bestScore) {
                bestScore = score;
                bestIndex = i;   // dùng index thay vì rec->id
            }
        } else if (metric == "manhattan") {
            score = l1Distance(query, *(rec->vector));
            if (score < bestScore) {
                bestScore = score;
                bestIndex = i;
            }
        } else if (metric == "euclidean") {
            score = l2Distance(query, *(rec->vector));
            if (score < bestScore) {
                bestScore = score;
                bestIndex = i;
            }
        } else {
            throw invalid_metric();
        }
    }
    return bestIndex;
}





void quickSort(ArrayList<Entry>& arr, int left, int right, bool maximize) {
    if (left >= right) return;

    Entry pivot = arr.get((left + right) / 2);

    ArrayList<Entry> less;
    ArrayList<Entry> equal;
    ArrayList<Entry> greater;

    for (int i = left; i <= right; i++) {
        Entry cur = arr.get(i);

        if (fabs(cur.score - pivot.score) < 1e-9) {
            // cùng score -> giữ nguyên theo thứ tự duyệt (ổn định)
            equal.add(cur);
        } else if (maximize ? (cur.score > pivot.score) : (cur.score < pivot.score)) {
            less.add(cur);
        } else {
            greater.add(cur);
        }
    }

    int idx = left;
    for (int i = 0; i < less.size(); i++) arr.set(idx++, less.get(i));
    for (int i = 0; i < equal.size(); i++) arr.set(idx++, equal.get(i));
    for (int i = 0; i < greater.size(); i++) arr.set(idx++, greater.get(i));

    // Đệ quy
    int lsize = less.size();
    int gsize = greater.size();

    if (lsize > 1) quickSort(arr, left, left + lsize - 1, maximize);
    if (gsize > 1) quickSort(arr, right - gsize + 1, right, maximize);
}


int* VectorStore::topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric) const {
    if (k <= 0 || count == 0 || k >count) {
        throw invalid_k_value();
    }
    // if (k > count) k = count;

    ArrayList<Entry> results; 

    // Tính toàn bộ score
    for (int i = 0; i < count; i++) {
        VectorRecord* rec = records.get(i);
        double score;
        if (metric == "cosine") score = cosineSimilarity(query, *(rec->vector));
        else if (metric == "manhattan") score = l1Distance(query, *(rec->vector));
        else if (metric == "euclidean") score = l2Distance(query, *(rec->vector));
        else throw invalid_metric();

        results.add({i, score});   
    }
    bool maximize = (metric == "cosine");
    quickSort(results, 0, results.size() - 1, maximize);

    // Lấy top-k
    int* topIds = new int[k];
    for (int i = 0; i < k; i++) {
        topIds[i] = results.get(i).id;  
    }
    return topIds;
}








template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
