#include <iostream>
#include <vector>

template<typename T>
class LinearSearch final {
public:
    static int search(const std::vector<T>& vec, const T& key) {
        for(size_t i = 0; i < vec.size(); i++) {
            if (vec[i] == key) {
                return i;
            }
        }
        return -1;
    }

    LinearSearch() = delete;
};

int main() {
    std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = LinearSearch<int>::search(array, 10);
    
    std::cout << key << std::endl;
    std::cout << sizeof(LinearSearch<int>) << " Bytes" << std::endl;
    return 0;
}
