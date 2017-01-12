template <class T, class Functor>
struct SegmentTree {
    size_t n;
    T e;
    vector<T> tree;
    Functor F;
    T query(size_t l, size_t r, size_t i, size_t a, size_t b) {
        if (l <= a && b <= r) return tree[i];

        T vl=e, vr=e;
        size_t c=(a+b)>>1;

        if (l < c) vl=F(e, query(l, r, i<<1|0, a, c));
        if (c < r) vr=F(e, query(l, r, i<<1|1, c, b));

        return F(vl, vr);
    }
public:
    SegmentTree(size_t m, T e=T()): n(1), e(e) {
        while (n <= m) n <<= 1;
        tree.assign(n<<1, e);
    }
    T query(size_t l, size_t r) {
        return query(l, r, 1, 0, n);
    }
    void update(size_t i, T x) {
        i += n;
        tree[i] = x;
        while (i>>=1)
            tree[i] = F(tree[i<<1|0], tree[i<<1|1]);
    }
};
