#include "ds_q5.hpp"
#include <vector>

using namespace std;

DamageNode_t *getTail(DamageNode_t *head) {
	DamageNode_t *cur = head;
	while (cur && cur->next) {
		cur = cur->next;
	}
	return cur;
}

vector<vector<int>> mapRotatingDamage(DamageNode_t *head, int m, int n, int k) {
	vector<vector<int>> damage(m, vector<int>(n, 0));
	DamageNode_t *cur = head, *tail = getTail(head), *newTail;
	int dcol[] = {0, 1, 0, -1};
	int drow[] = {1, 0, -1, 0};
	int col = 0, row = 0, dir = 0;
	int ub = 0, db = m - 1, lb = 0, rb = n - 1;
	for (int i = 0; i < m * n && cur; ++i, cur = cur->next) {
		damage[row][col] = cur->damage;
		if (row == db && dir == 0) {
			dir = 1;
			lb++;
		} else if (col == rb && dir == 1) {
			dir = 2;
			db--;
		} else if (row == ub && dir == 2) {
			dir = 3;
			rb--;
		} else if (col == lb && dir == 3) {
			dir = 0;
			ub++;
		}
		col += dcol[dir];
		row += drow[dir];
		if (i % k == k-1 && cur->next && cur->next->next) {
			newTail = cur->next;
			cur->next = newTail->next;
			tail->next = newTail;
			newTail->next = nullptr;
			tail = newTail;
		}
	}
	return damage;
}
