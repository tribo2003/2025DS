#include <iostream>
using namespace std;
#ifdef OJ_JUDGE
#define main student_main
#endif

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

Node* head = nullptr;    // head(一個指標)是用來指向Node這種structure(位置固定) 但現在初始化head指向null  (head) -> null

// Add the element x to the "end" of the list
void push_Back(int element) {
    // TO DO

    //原本的最後一個要指向新的 換新的指向nullptr
    Node* newback=new Node(element);                    //(newback) -> {element,NULL}             

    if(head==nullptr){                 //空陣列   
        head=newback;                                           //(head) -> {element,NULL}        
    }else{                             //非空陣列=>只在乎原本指向的最後一個Node{data,nullptr}
        Node* current=head;                                     //current指向head指向的node 
        while(current->next!=nullptr){                          //(current) -> {data,next}
            current=current->next;                              //(current) -> {原next指向的data,原next指向的next}
        }
        current->next=newback;                                  //(current)-> {element,NULL}

    }
    
}

// Add an element to the "head" of the list
void push_Front(int element) {
    // TO DO

    //head要指新的 新的next要指向原head 
    Node* newfront=new Node(element);     //(newfront) -> {element,null}
    
    if(head==nullptr){                 //空陣列   
        head=newfront;                                           //(head) -> {element,null}    
    }else{                             //非空陣列
        newfront->next=head;                                    //nexfront指向的Node的next(原本是null)改成指向head指向的Node
        head=newfront;                                          //再把head改成指向newfront指向的Node
    }

}

// Delete "the specified element" from the list.
void remove_Node(int element) {
    // TO DO
    if(head==nullptr){                //空陣列
        return;
    }

    if(head->data==element){          //刪頭
        Node* temp=head;
        head=head->next;
        delete temp;
        return;
    }

    Node* prev=head;                  
    Node* current=head->next;
    while(current!=nullptr){
        if(current->data==element){
            prev->next=current->next;
            delete current;
            return;
        }
        prev=current;
        current=current->next;
    }
}

// Check if x is in the list, Yes return True; No return False
bool contain(int element) {
    // TO DO
    bool exists=false;
    Node* current=head;
    while(current!=nullptr){
        if(current->data==element){
            exists=true;
            break;
        }
        current=current->next;
    }

    return exists;
}

// Reverse linked list
void invert_List() {
    // TO DO
    Node* prev=nullptr;
    Node* current=head;
    Node* next=nullptr;
    
    while(current!=nullptr){
        next=current->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    head=prev;
}

// Clear the entire list
void clean() {
    // TO DO
    while(head->next!=nullptr){
        Node* temp=head;
        head=temp->next;
        delete temp;
    }
    head=nullptr;
}

// DON'T TOUCH !!!!!
// Output the result
void print_List() {
    Node* temp = head;
    while (temp) {
        cout << temp->data;
        if (temp->next) cout << " ";
        temp = temp->next;
    }
    cout << endl;
}

// You can modify the main() below, it won't be executed.
int main() {
    // You can test your code here.
    return 0;
}

// -----------------------------------------------------
// DON'T TOUCH !!!!!
#ifdef OJ_JUDGE
#undef main
int main() {
    int n, x;
    string op;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> op;
        if (op == "b") {
            cin >> x;
            push_Back(x);
        }
        else if (op == "f") {
            cin >> x;
            push_Front(x);
        }
        else if (op == "r") {
            cin >> x;
            remove_Node(x);
        }
        else if (op == "c") {
            cin >> x;
            cout << (contain(x) ? "True" : "False") << endl;
        }
        else if (op == "i") {
            invert_List();
        }
        else if (op == "C") {
            clean();
            cout << "Clear the list!" << endl;
        }
    }

    print_List();
    return 0;
}
#endif