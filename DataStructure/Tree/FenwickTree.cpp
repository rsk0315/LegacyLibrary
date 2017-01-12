template <class T>
class FenwickTree {
    size_t n;
    vector<T> tree0, tree1;
    void update(vector<T> &tree, size_t i, T x) {
        while (i <= n) {
            tree[i] += x;
            i += i & -i;
        }
    }
    T query(vector<T> &tree, size_t i) {
        T res=0;
        while (i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
public:
    FenwickTree(size_t n, T e=0): n(n), tree0(n, e), tree1(n, e) {
        tree0 = vector<T>(n+1, e);
        tree1 = vector<T>(n+1, e);
    }
    void update(size_t l, size_t r, T x) {
        update(tree0, l+1, -x*l);
        update(tree1, l+1, x);
        update(tree0, r+1, x*r);
        update(tree1, r+1, -x);
    }
    T query(size_t l, size_t r) {
        T res=0;
        res += query(tree0, r) + query(tree1, r)*r;
        res -= query(tree0, l) + query(tree1, l)*l;
        return res;
    }
};
