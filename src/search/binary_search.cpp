#include <iostream>
#include <vector>

template<typename T>
class BinarySearch final {
public: 
    static int search(const std::vector<T>& vec, const T& key) {
        int low = 0;
        int high = vec.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            
            if (vec[mid] == key) {
                return mid;
            } else if (vec[mid] < key) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
    
    BinarySearch() = delete;
};

int main() {
    std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = BinarySearch<int>::search(array, 10);
    
    std::cout << key << std::endl;
    std::cout << sizeof(BinarySearch<int>) << " Bytes" << std::endl;
    return 0;
}