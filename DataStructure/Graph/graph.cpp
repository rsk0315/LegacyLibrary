template <class Weight>
struct Edge {
    size_t src, dst;
    Weight weight;
    Edge() {}
    Edge(size_t src, size_t dst, Weight weight=1):
        src(src), dst(dst), weight(weight)
    {}
    bool operator <(const Edge<Weight> &rhs) const {
        if (weight != rhs.weight) {
            return weight > rhs.weight;
        } else {
            return src!=rhs.src? (src < rhs.src) : (dst < rhs.dst);
        }
    }
};

template <class Weight>
using Edges=vector<Edge<Weight>>;
template <class Weight>
using Vertex=vector<Edge<Weight>>;

template <class Weight>
struct Graph: public vector<Vertex<Weight>> {
    Graph() {}
    Graph(size_t V): vector<Vertex<Weight>>(V) {}
    void join(size_t src, size_t dst, Weight cost=1) {
        // non-directed connection
        (*this)[src].push_back(Edge<Weight>(src, dst, cost));
        (*this)[dst].push_back(Edge<Weight>(dst, src, cost));
    }
    void connect(size_t src, size_t dst, Weight cost=1) {
        // directed connection
        (*this)[src].push_back(Edge<Weight>(src, dst, cost));
    }
};
