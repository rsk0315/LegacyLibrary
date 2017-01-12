template <class T>
class StarrySkyTree {
    vector<T> tree;
    size_t n, m;
    void add(size_t l, size_t r, size_t i, size_t a, size_t b, T x) {
        if (l <= a && b <= r) {
            tree[i] += x;
        } else {
            size_t c=(a+b)>>1;
            if (l < c) add(l, r, i<<1|0, a, c, x);
            if (c < r) add(l, r, i<<1|1, c, b, x);
        }

        if (i == 1) return;
        if (tree[i] > 0 || tree[i^1] > 0 || (tree[i] < 0 && tree[i^1] < 0)) {
            T k=max(tree[i], tree[i^1]);
            tree[i>>1] += k;
            tree[i] -= k;
            tree[i^1] -= k;
        }
    }
public:
    using value_type=T;
    StarrySkyTree(size_t m): m(m) {
        // padding to power of two
        for (n=1; n<m; n<<=1);
        tree = vector<T>(n<<1);
    }
    void add(size_t l, size_t r, size_t x) {
        // add x to [l, r)
        add(l, r, 1, 0, n, x);
    }
    T max() const {
        // get max value in [0, m)
        return tree[1];
    }
    T operator [](size_t i) const {
        T res=0;
        for (i+=n; i>0; i>>=1)
            res += tree[i];

        return res;
    }
};
