#include "ds_q5.hpp"
#include <vector>

using namespace std;

vector<vector<int>> mapDamage(DamageNode_t *head, int m, int n) {
	// Implement this function for assignment 5-1
    struct Node{
        int data;
        Node* prev;
        Node* next;
        Node(int val):data(val),prev(nullptr),next(nullptr){}
    };

    Node* head=


	return {};
}

vector<vector<int>> mapRotatingDamage(DamageNode_t *head, int m, int n, int k) {
	// Implement this function for assignment 5-2
	return {};
}

#ifndef OJ_MODE
// This main function is for local testing only.
// It will NOT be compiled or executed on the OJ system.
int main() {
    // TODO: Write test code here to verify your implementation.
    return 0;
}
#endif
