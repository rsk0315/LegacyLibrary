class LinkCutTree {
    struct Node {
        Node *l, *r, *p;
        Node(): l(NULL), r(NULL), p(NULL) {}
    } *nodes;
    int state(Node *u) {
        if (u->p) {
            if (u->p->l == u) return -1;
            if (u->p->r == u) return 1;
        }
        return 0;
    }
    void rotate(Node *u) {
        Node *par=u->p, *mid;
        if (par->l == u) {
            mid = u->r;
            u->r = par;
            par->l = mid;
        } else {
            mid = u->l;
            u->l = par;
            par->r = mid;
        }
        if (mid) mid->p = par;

        u->p = par->p;
        par->p = u;

        if (u->p && u->p->l == par) u->p->l = u;
        if (u->p && u->p->r == par) u->p->r = u;
    }
    void splay_solid(Node *u) {
        while (state(u)) {
            int s=state(u)*state(u->p);
            if (s == 1) {
                rotate(u->p);
            } else if (s == -1) {
                rotate(u);
            }
            rotate(u);
        }
    }
    void splay(Node *u) {
        for (Node *x=u; x; x=x->p) splay_solid(x);
        for (Node *x=u; x->p; x=x->p) x->p->l = x;
        splay_solid(u);
    }
    void link(Node *u, Node *v) {
        splay(v);
        splay(u);
        u->p = v;
    }
    void cut(Node *u) {
        splay(u);
        u->r->p = NULL;
        u->r = NULL;
    }
    Node *lca(Node *u, Node *v) {
        splay(v);
        splay(u);
        u->l = NULL;
        bool connected=false;
        Node *res=v;
        for (; v; v=v->p) {
            if (v->p && !state(v)) res = v->p;
            if (v == u) connected = true;
        }

        return connected? res:NULL;
    }
public:
    LinkCutTree() {}
    LinkCutTree(size_t n) {
        nodes = new Node[n];
    }
    void link(size_t u, size_t v) {
        link(&nodes[u], &nodes[v]);
    }
    void cut(size_t u) {
        cut(&nodes[u]);
    }
    size_t lca(size_t u, size_t v) {
        Node *res=lca(&nodes[u], &nodes[v]);
        return res? (res-nodes):-1;
    }
    bool connected(size_t u, size_t v) {
        return lca(&nodes[u], &nodes[v]) != NULL;
    }
};
