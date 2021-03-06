#include <bits/stdc++.h>
using namespace std;

struct segtree {
    segtree(const vector<int> &arr) {
        _arr = arr;
        _N = arr.size();
        _tree.resize(4 * _N + 1);
        _lazy.resize(4 * _N + 1, 0LL);
        buildTree(1, 0, _N - 1);
    }

    int query(int L, int R) {
        return queryTree(1, 0, _N - 1, L, R);
    }

    void update(int index, int ele) {
        updateTree(1, 0, _N - 1, index, ele);
    }

    void update(int L, int R, int ele) {
        updateRange(1, 0, _N - 1, L, R, ele);
    }

   private:
    int _N;
    vector<int> _arr, _tree, _lazy;

    void buildTree(int index, int start, int end) {
        if (start > end) {
            return;
        }

        if (start == end) {
            _tree[index] = _arr[start];
            return;
        }

        int mid = start + (end - start) / 2;
        buildTree(2 * index, start, mid);
        buildTree(2 * index + 1, mid + 1, end);
        int L = _tree[2 * index];
        int R = _tree[2 * index + 1];
        _tree[index] = mergeNodes(L, R);
    }

    int queryTree(int index, int start, int end, int left, int right) {
        if (_lazy[index] != 0) {
            int delta = _lazy[index];
            _lazy[index] = 0LL;
            _tree[index] += delta * (end - start + 1);

            if (start != end) {
                _lazy[2 * index] += delta;
                _lazy[2 * index + 1] += delta;
            }
        }

        if (left > end || right < start) {
            return 0;
        }

        if (left <= start && end <= right) {
            return _tree[index];
        }

        int mid = start + (end - start) / 2;
        int L = queryTree(2 * index, start, mid, left, right);
        int R = queryTree(2 * index + 1, mid + 1, end, left, right);
        return mergeNodes(L, R);
    }

    void updateTree(int index, int start, int end, int idx, int val) {
        if (idx < start || idx > end) {
            return;
        }

        if (start == end) {
            _tree[index] += val;
            return;
        }

        int mid = start + (end - start) / 2;
        updateTree(2 * index, start, mid, idx, val);
        updateTree(2 * index + 1, mid + 1, end, idx, val);
        int L = _tree[2 * index];
        int R = _tree[2 * index + 1];
        _tree[index] = mergeNodes(L, R);
    }

    void updateRange(int index, int start, int end, int left, int right, int ele) {
        if (_lazy[index] != 0) {
            int delta = _lazy[index];
            _lazy[index] = 0LL;
            _tree[index] += delta * (end - start + 1);

            if (start != end) {
                _lazy[2 * index] += delta;
                _lazy[2 * index + 1] += delta;
            }
        }

        if (right < start || left > end) {
            return;
        }

        if (left <= start && end <= right) {
            int delta = ele * (end - start + 1);
            _tree[index] += delta;

            if (start != end) {
                _lazy[2 * index] += ele;
                _lazy[2 * index + 1] += ele;
            }

            return;
        }

        int mid = start + (end - start) / 2;
        updateRange(2 * index, start, mid, left, right, ele);
        updateRange(2 * index + 1, mid + 1, end, left, right, ele);
        int L = _tree[2 * index];
        int R = _tree[2 * index + 1];
        _tree[index] = mergeNodes(L, R);
    }

    int mergeNodes(int left, int right) {
        return left + right;
    }
};