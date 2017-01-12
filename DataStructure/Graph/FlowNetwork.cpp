using Weight=int;

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

template <class Weight, Weight INF>
struct FlowNetwork: public vector<Node<Weight>> {
    bool sent_flow;
    Weight total_flow, total_cost;
    Weight inf;
    FlowNetwork(): sent_flow(false), inf(INF) {}
    FlowNetwork(size_t V): vector<Node<Weight>>(V), sent_flow(false), inf(INF)
    {}
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
    pair<Weight, Weight> send(
        size_t source, size_t sink, Weight bound=INF
    ) {
        /* Primal-Dual */
        // sends legal flow at most bound
        // returns its amount and minimum cost
        if (sent_flow)
            reset_flow();

        size_t V=this->size();
        vector<Weight> pot(V);

        while (bound > total_flow) {
            // shortest path from source to sink with available capacity
            vector<Weight> d(V, INF); d[source]=0;
            vector<Arc<Weight> *> prev(V, NULL);
            lp_queue<pair<Weight, size_t>> q; q.push(make_pair(0, source));
            while (!q.empty()) {
                pair<Weight, size_t> p=q.top(); q.pop();
                size_t v=p.second;
                if (d[v] < p.first) continue;

                for (Arc<Weight> &e: (*this)[v]) {
                    if (e.residue() <= 0) continue;

                    Weight new_d=d[e.src]+e.cost+pot[e.src]-pot[e.dst];
                    if (d[e.dst] > new_d) {
                        d[e.dst] = new_d;
                        prev[e.dst] = &e;
                        q.push(make_pair(d[e.dst], e.dst));
                    }
                }
            }

            // has no available capacity
            if (d[sink] == INF)
                break;

            for (size_t v=0; v<V; ++v)
                pot[v] += d[v];

            Weight f=bound-total_flow;
            for (Arc<Weight> *e=prev[sink]; e!=NULL; e=prev[e->src])
                // critical capacity
                if (f > e->capacity)
                    f = e->capacity;

            totalflow += f;
            total_cost += f * pot[sink];
            for (Arc<Weight> *e=prev[sink]; e!=NULL; e=prev[e->src]) {
                e->total_flow += f;
                reverse(*e).capacity += f;
            }
        }

        sent_flow = true;
        return make_pair(total_flow, total_cost);
    }
};
