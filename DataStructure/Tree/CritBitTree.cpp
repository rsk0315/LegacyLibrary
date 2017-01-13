template <class Key, class T>
class CritBitTree {
    // acts as a set if T is nullptr_t, otherwise a map
    using mask_t=typename Key::value_type;
    struct Node {
        bool is_internal;
        Node(bool is_internal=false): is_internal(is_internal) {}
    };
    struct InNode: public Node {
        Node *child[2];
        size_t byte;
        mask_t mask;
        InNode(): Node(true) {}
    };
    struct ExNode: private Node {
        Key key;
        T value;
        ExNode(const Key &key="", const T &value=T()):
            Node(), key(key), value(value)
        {}
    };
    Node *root;
    ExNode *seek(const string &key) {
        // Returns the pointer to the best match item with given key
        Node *pos=root;
        while (pos->is_internal) {
            InNode *p=(InNode *)pos;
            mask_t c=0;
            if (p->byte < key.length())
                c = key[p->byte];

            bool bit_set=p->mask&c;
            pos = p->child[bit_set];
        }

        return (ExNode *)pos;
    }
    bool differs(
        const string &key, ExNode *pos, size_t &byte, mask_t &mask
    ) {
        // Returns whether two keys differ and prepares the mask
        for (byte=0; byte<key.length(); ++byte)
            if ((mask = (pos->key[byte] ^ key[byte])))
                return true;

        return (mask = pos->key[byte]);
    }
    template <class Functor>
    int traverse(Node *top, Functor handle) {
        /* Traversal: handles each of nodes in the subtree */
        // Returns 0 if traversal succeeds; other if fails
        // Note: traversal is terminated
        //       when handler returns non-zero value
        if (!top->is_internal)
            return handle(*(ExNode *)top);

        int retval=0;
        for (Node *q: ((InNode *)top)->child)
            if ((retval = traverse(q, handle)))
                break;

        return retval;
    }
    pair<T *, bool> find(const Key &key, T value) {
        // Inserts new node with default value of T if not found
        // Returns:
        // - reference to the value mapped to the key
        // - whether the tree was mutated
        if (!this->root) {
            this->root = (Node *)(new ExNode(key, value));
            return make_pair(&((ExNode *)(this->root))->value, true);
        }

        ExNode *pos=seek(key);

        // Find the critical bit
        size_t newbyte;
        mask_t newmask;
        if (!differs(key, pos, newbyte, newmask))
            return make_pair(&pos->value, false);

        for (mask_t tmp=newmask; (tmp&=tmp-1); newmask=tmp);

        // Decide next child
        mask_t c=pos->key[newbyte];
        bool bit_set=newmask&c;

        // Inserts new node
        InNode *newnode=new InNode;
        newnode->byte = newbyte;
        newnode->mask = newmask;
        newnode->child[1^bit_set] = (Node *)(new ExNode(key, value));

        Node **wherep=(Node **)&(this->root);
        while (true) {
            if (!(*wherep)->is_internal) break;

            InNode *p=(InNode *)*wherep;
            if (p->byte > newbyte) break;
            if (p->byte == newbyte && p->mask < newmask) break;

            mask_t c=0;
            if (p->byte < key.length())
                c = key[p->byte];

            bool bit_set=(p->mask&c);
            wherep = &(p->child[bit_set]);
        }
        (newnode->child[bit_set]) = *wherep;
        *wherep = newnode;
        (*wherep)->is_internal = true;

        return make_pair(&((ExNode *)(newnode->child[1^bit_set]))->value, true);
    }
public:
    using item=ExNode;
    CritBitTree(): root(NULL) {}
    bool contains(const Key &key) {
        if (!root) return false;

        ExNode *pos=seek(key);
        return key == pos->key;
    }
    bool insert(const Key &key, const T &value=T()) {
        // Returns whether the tree was mutated
        return find(key, value).second;
    }
    bool remove(const Key &key) {
        // Returns whether the tree was mutated
        if (!root) return false;

        Node *p=root, **wherep=&root;
        InNode *q=NULL, **whereq=NULL;
        bool bit_set=0;
        while (p->is_internal) {
            whereq = (InNode **)wherep;
            q = (InNode *)p;
            mask_t c=0;
            if (q->byte < key.length())
                c = key[q->byte];

            bit_set = q->mask & c;
            wherep = &(q->child[bit_set]);
            p = *wherep;
        }

        if (key != ((ExNode *)p)->key)
            // key not found
            return false;

        delete p;

        // Remove the element and/or node
        if (!whereq) {
            root = NULL;
            return true;
        }

        *whereq = (InNode *)q->child[1^bit_set];
        delete q;

        return true;
    }
    template <class Functor>
    int all_prefixed(Functor handle, const Key &prefix="") {
        /* Suffix searching: walks all prefixed keys */
        // Functor
        //   type: int handle(dict<Key, T>::item);
        //   return value: 0 if succeeds, nonzero if fails
        if (!root)
            return 1;

        // Walk tree, maintaining top pointer
        Node *p=root, *top=p;
        while (p->is_internal) {
            InNode *q=(InNode *)p;
            mask_t c=0;
            if (q->byte < prefix.length())
                c = prefix[q->byte];

            bool bit_set=q->mask&c;
            p = q->child[bit_set];
            if (q->byte < prefix.length())
                top = p;
        }

        for (size_t i=0; i<prefix.length(); ++i)
            if (((ExNode *)p)->key[i] != prefix[i])
                return 1;

        return traverse(top, handle);
    }
    T &operator [](const Key &key) {
        return *find(key, T()).first;
    }
};
