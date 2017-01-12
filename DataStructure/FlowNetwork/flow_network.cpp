template <class Weight>
struct Arc {
    size_t src, dst;
    Weight capacity, cost, flow;
    size_t rev;
    Arc() {}
    Arc(size_t src, size_t dst, Weight cap, Weight cost):
        src(src), dst(dst), capacity(cap), cost(cost), flow(0), rev(-1)
    {}
    Weight residue() {
        return capacity - flow;
    }
    bool operator <(const Arc<Weight> &rhs) const {
        if (capacity != rhs.capacity) {
            return capacity > rhs.capacity;
        } else {
            return src!=rhs.src? (src<rhs.src) : (dst<rhs.dst);
        }
    }
};

template <class Weight>
using Arcs=vector<Arc<Weight>>;
template <class Weight>
using Node=vector<Arc<Weight>>;

template <class Weight>
struct FlowNetwork: public vector<Node<Weight>> {
    bool sent_flow;
    FlowNetwork(): sent_flow(false) {}
    FlowNetwork(size_t V): vector<Node<Weight>>(V), sent_flow(false) {}
    void join(size_t src, size_t dst, Weight cap=1, Weight cost=1) {
        (*this)[src].push_back(Arc<Weight>(src, dst, cap, cost));
        (*this)[dst].push_back(Arc<Weight>(dst, src, cap, cost));

        (*this)[src].back().rev = (*this)[dst].size()-1;
        (*this)[dst].back().rev = (*this)[src].size()-1;
    }
    void connect(size_t src, size_t dst, Weight cap=1, Weight cost=1) {
        (*this)[src].push_back(Arc<Weight>(src, dst, cap, cost));
        (*this)[dst].push_back(Arc<Weight>(dst, src, 0, -cost));

        (*this)[src].back().rev = (*this)[dst].size()-1;
        (*this)[dst].back().rev = (*this)[src].size()-1;
    }
    Arc<Weight> &reverse(const Arc<Weight> &e) {
        // Assert: e in (*this)
        return (*this)[e.dst][e.rev];
    }
    void reset_flow() {
        if (!sent_flow) return;

        for (Node<Weight> &v: (*this))
            for (Arc<Weight> &e: v)
                e.flow = 0;

        sent_flow = false;
    }
};
