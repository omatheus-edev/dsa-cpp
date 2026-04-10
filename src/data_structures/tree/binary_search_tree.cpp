#include <iostream>
#include <queue>

template<typename T, typename Compare = std::less<T>>
class BinarySearchTree final {
public:
    struct Node final {
        friend class BinarySearchTree;

    private:
        T value;
        Node* left = nullptr;
        Node* right = nullptr;


    public:
        Node(const T& value) : value(value){}

        T getValue() const {
            return value;
        }

        Node* getLeft() const {
            return left;
        }

        Node* getRight() const {
            return right;
        }
    };

    BinarySearchTree() = default;

    ~BinarySearchTree() {
        if (root == nullptr) return;
        std::queue<Node*> queue;
        queue.push(root);

        while (!queue.empty()) {
            Node* node = queue.front();
            queue.pop();

            if (node->left != nullptr) {
                queue.push(node->left);
            }
            if (node->right != nullptr) {
                queue.push(node->right);
            }
            delete node;
        }
        root = nullptr;
        size_ = 0;
    }

    void insert(const T& value) {
        Node* node = new Node(value);
        if (root == nullptr) {
            root = node;
        } else {
            Node* current = root;

            while (true) {
                if (!compare(current->getValue(), value) && !compare(value, current->getValue())) {
                    delete node;
                    return;
                } else if (compare(current->getValue(), value)) {
                    if (current->getRight() != nullptr) {
                        current = current->getRight();
                    } else {
                        current->right = node;
                        break;
                    }
                } else {
                    if (current->getLeft() != nullptr) {
                        current = current->getLeft();
                    } else {
                        current->left = node;
                        break;
                    }
                }
            }
        }
        size_++;
    }
    
    void remove(const T& value) {
        Node* current = root;
        Node* parent = nullptr;
        bool isLeftChild = true;
        
        while (current != nullptr) {
            if (!compare(current->getValue(), value) && !compare(value, current->getValue())) {
                break;
            }
            
            parent = current;
            if (compare(current->getValue(), value)) { 
                current = current->right;
                isLeftChild = false;
            } else {
                current = current->left;
                isLeftChild = true;
            }
        }
        
        if (current == nullptr) return;
        if (current->left == nullptr && current->right == nullptr ) {
            if (current == root) {
                root = nullptr;
            } else if (isLeftChild) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete current;
        } else if (current->left == nullptr || current->right == nullptr) {
            Node* child = (current->left != nullptr) ? current->left : current->right;
            
            if (current == root) {
                root = child;
            } else if (isLeftChild) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            delete current;
        } else {
            Node* sucessorParent = current;
            Node* sucessor = current->right;
            
            while (sucessor->left != nullptr) {
                sucessorParent = sucessor;
                sucessor = sucessor->left;
            }
            current->value = sucessor->value;
            
            if (sucessorParent == current) {
                sucessorParent->right = sucessor->right;
            } else {
                sucessorParent->left = sucessor->right;
            }
            delete sucessor;
        }
        size_--;
    }

    Node* search(const T& value) const {
        Node* current = root;

        while (current != nullptr) {
            if (!compare(current->getValue(), value) && !compare(value, current->getValue())) {
                return current;
            } else if (compare(current->getValue(), value)) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return nullptr;
    }

    bool isEmpty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }
    
    void preOrder() {
        print(root);
    }
private:
    Node* root;
    size_t size_;
    Compare compare;
    
    void print(const Node* node) const {
        if (node == nullptr) return;
        
        std::cout << node->value << std::endl;
        print(node->getLeft());
        print(node->getRight());
    }
};

int main() {
    BinarySearchTree<int> tree{};
    tree.insert(10);
    tree.insert(3);
    tree.insert(7);
    tree.insert(13);
    tree.insert(11);
    tree.insert(16);
    BinarySearchTree<int>::Node* node = tree.search(7);
    
    std::cout << sizeof(tree) << " Bytes" << std::endl;
    std::cout << tree.size() << std::endl;
    std::cout << node->getValue() << std::endl;
    std::cout << "=== Tree ===\n";
    tree.preOrder();
    tree.remove(13);
    std::cout << "=== Tree ===\n";
    tree.preOrder();
    return 0;
}
