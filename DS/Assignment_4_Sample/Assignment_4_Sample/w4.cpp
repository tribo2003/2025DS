#include <iostream>
#include <string>

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Add the element x to the "end" of the list
    void push_Back(int x) {
        Node* newNode = new Node(x);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Add an element to the "head" of the list
    void push_Front(int x) {
        Node* newNode = new Node(x);
        newNode->next = head;
        head = newNode;
    }

    // Delete "the specified element" from the list.
    void remove_Node(int x) {
        if (head == nullptr) return;

        Node* temp = head;
        Node* prev = nullptr;

        while (temp != nullptr) {
            if (temp->data == x) {
                if (prev == nullptr) {
                    head = head->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp; // Use delete instead of free
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    // Check if x is in the list, Yes return true; No return false
    bool contain(int x) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == x) return true;
            temp = temp->next;
        }
        return false;
    }

    // Reverse the list
    void invert_List() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // Clear the entire list
    void clean() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp; // Use delete instead of free
        }
    }

    // Output the result
    void print_List() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data;
            if (temp->next != nullptr) std::cout << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    ~LinkedList() {
        clean(); // Ensure the list is cleared when the LinkedList object is destroyed
    }
};

int main() {
    int n, x;
    std::string op;
    std::cin >> n;

    LinkedList list;

    for (int i = 0; i < n; i++) {
        std::cin >> op;
        if (op[0] == 'b') {
            std::cin >> x;
            list.push_Back(x);
        } else if (op[0] == 'f') {
            std::cin >> x;
            list.push_Front(x);
        } else if (op[0] == 'r') {
            std::cin >> x;
            list.remove_Node(x);
        } else if (op[0] == 'c') {
            std::cin >> x;
            std::cout << (list.contain(x) ? "True" : "False") << std::endl;
        } else if (op[0] == 'i') {
            list.invert_List();
        } else if (op[0] == 'C') {
            list.clean();
            std::cout << "Clear the list!" << std::endl;
        }
    }

    list.print_List();
    return 0;
}