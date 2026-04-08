#include <cstddef>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>

template<typename T>
class LinkedList final {
private:
    struct Node final {
        T value;
        Node* previous = nullptr;
        Node* next = nullptr;

        Node(const T& value) : value(value){}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t length = 0;

    void removeNode(Node* node) {
        if (node->previous != nullptr) {
            node->previous->next = node->next;
        } else {
            head = node->next;
        }

        if (node->next != nullptr) {
            node->next->previous = node->previous;
        } else {
            tail = node->previous;
        }
        delete node;
        length--;
    }

public:
    LinkedList() = default;

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void addFirst(const T& value) {
        Node* node = new Node(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            node->next = head;
            head->previous = node;
            head = node;
        }
        length++;
    }

    void add(const T& value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->previous = tail;
            tail = node;
        }
        length++;
    }

    void add(const T& value, unsigned int index) {
        if (index > length) {
            throw std::out_of_range("index out of bounds");
        }

        if (index == 0) {
            addFirst(value);
        } else if (index == length) {
            add(value);
        } else {
            Node* node = new Node(value);
            Node* current = head;

            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            node->previous = current;
            node->next = current->next;
            current->next->previous = node;
            current->next = node;
            length++;
        }
    }

    bool remove(const T& value) {
        if (head == nullptr) return false;

        Node* current = head;
        while (current != nullptr) {
            if (current->value == value) {
                removeNode(current);
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool remove(unsigned int index) {
        if (head == nullptr) return false;
        if (index >= size()) return false;

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        removeNode(current);
        return true;
    }

    T get(unsigned int index) {
        if (index >= size()) {
            throw std::out_of_range("index out of bounds");
        }
        if (index == size() - 1) {
            return tail->value;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    size_t size() const {
        return length;
    }

    bool isEmpty() const {
        return length == 0;
    }

    bool contains(const T& value) {
        return indexOf(value) != -1;
    }

    int indexOf(const T& value) {
        Node* current = head;
        for (int i = 0; i < length; i++) {
            if (current->value == value) {
                return i;
            }
            current = current->next;
        }

        return -1;
    }

    std::string toString() {
        if (isEmpty()) {
            return "[]";
        }

        std::string result = "[";
        Node* current = head;

        while (current != nullptr) {
            result += std::to_string(current->value);
            if (current->next != nullptr) {

                result += ", ";
            }
            current = current->next;
        }
        result += "]";
        return result;
    }
};

int main() {
    LinkedList<int> list{};
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    list.add(0, 0);
    list.add(10, 3);
    list.remove(1);

    std::cout << sizeof(list) << " Bytes\n";
    std::cout << list.indexOf(10) << std::endl;
    std::cout << std::boolalpha << list.contains(9) << std::endl;
    std::cout << list.get(5) << std::endl;
    std::cout << list.toString() << std::endl;
    return 0;
}