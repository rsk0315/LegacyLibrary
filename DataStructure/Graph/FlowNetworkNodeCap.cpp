template <class Weight, Weight INF>
struct FlowNetworkNodeCap: public FlowNetwork<Weight, INF> {
    size_t V;
    FlowNetworkNodeCap() {}
    FlowNetworkNodeCap(size_t V): FlowNetwork<Weight, INF>(V<<1), V(V) {
        // (vin[i], vout[i]): (i, V+i)
        for (size_t i=0; i<V; ++i) {
            (*this)[V+i].push_back(Arc<Weight>(V+i, i, INF, 0));
            (*this)[i].push_back(Arc<Weight>(i, V+i, 0, 0));

            (*this)[V+i].back().rev = (*this)[i].back().rev = 0;
        }
    }
    void join(size_t src, size_t dst, Weight cap=INF, Weight cost=0) {
        // need verify
        connect(src, dst, cap, cost);
        connect(dst, src, cap, cost);
    }
    void connect(size_t src, size_t dst, Weight cap=INF, Weight cost=0) {
        dst += V;
        (*this)[src].push_back(Arc<Weight>(src, dst, cap, cost));
        (*this)[dst].push_back(Arc<Weight>(dst, src, 0, -cost));

        (*this)[src].back().rev = (*this)[dst].size()-1;
        (*this)[dst].back().rev = (*this)[src].size()-1;
    }
    void set_node_cap(size_t node, Weight cap) {
        (*this)[V+node][0].capacity = cap;
    }
    void set_node_cost(size_t node, Weight cost) {
        (*this)[V+node][0].cost = cost;
        (*this)[node][0].cost = -cost;
    }
    void set_node_prop(size_t node, Weight cap, Weight cost) {
        set_node_cap(node, cap);
        set_node_cost(node, cost);
    }
    pair<Weight, Weight> send(size_t source, size_t sink, Weight bound=INF) {
        return FlowNetwork<Weight, INF>::send(V+source, sink, bound);
    }
};
