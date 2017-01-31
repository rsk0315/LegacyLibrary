#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>

using namespace std;

template <class Key, class T=nullptr_t>
class CritBitTree {
    using mask_type=typename Key::value_type;
    using value_type=pair<const Key, T>;
    struct Node {
        // if one of the child is NULL, the sibling should be also NULL
        size_t nth_byte;
        mask_type mask;
        value_type *value;
        Node *child[2];
        Node(): child{NULL, NULL} {}
    };
    Node *root;
    value_type *trace(const Key &key) {
        Node *pos=root;
        while (pos->child[0]) {
            mask_type byte=0;
            if (pos->nth_byte < key.length())
                byte = key[pos->nth_byte];

            size_t dir=(pos->mask&byte? 1:0);
            pos = pos->child[dir];
        }

        return pos->value;
    }
    value_type *trace(const Key &key, Node **subtop, size_t branchdir) {
        Node *pos=root;
        while (pos->child[0]) {
            mask_type byte=0;
            if (pos->nth_byte < key.length())
                byte = key[pos->nth_byte];

            size_t dir=(pos->mask&byte? 1:0);
            if (dir == branchdir) *subtop = pos->child[1^dir];
            pos = pos->child[dir];
        }

        return pos->value;
    }
    bool differs(
        const Key &key1, const Key &key2, size_t &nth_byte, mask_type &mask
    ) {
        for (nth_byte=0; nth_byte<key1.length(); ++nth_byte)
            if ((mask = (key1[nth_byte] ^ key2[nth_byte])))
                return true;

        return (mask = key2[nth_byte]);
    }
    pair<T *, bool> find(const Key &key, T value) {
        if (!root) {
            root = new Node;
            root->value = new pair<const Key, T>(key, value);

            return make_pair(&(root->value->second), true);
        }

        value_type *bestmatch=trace(key);

        size_t nth_byte;
        mask_type mask;
        if (!differs(key, bestmatch->first, nth_byte, mask))
            return make_pair(bestmatch->second, false);

        // make the new mask
        for (mask_type tmp=mask; (tmp&=tmp-1); mask=tmp);

        size_t dir=(mask&(bestmatch->first[nth_byte])? 1:0);

        Node *newnode=new Node;
        newnode->nth_byte = nth_byte;
        newnode->mask = mask;
        newnode->child[1^dir] = new Node;
        newnode->child[1^dir]->value = new value_type(key, value);

        Node **child=&root;
        while (true) {
            Node *pos=*child;
            if (!pos->child[0]) break;

            if (pos->nth_byte > nth_byte) break;
            if (pos->nth_byte == nth_byte && pos->mask < mask) break;

            mask_type byte=0;
            if (pos->nth_byte < key.length())
                byte = key[pos->nth_byte];

            size_t dir=(pos->mask&byte? 1:0);
            child = &(pos->child[dir]);
        }
        (newnode->child[dir]) = *child;
        *child = newnode;

        return make_pair(&(newnode->child[1^dir]->value->second), true);
    }
    template <class Functor>
    int traverse(Node *top, Functor callback) {
        if (!top->child[0])
            return callback(*(top->value));

        int retval=0;
        for (Node *subtree: top->child)
            if ((retval = traverse(subtree, callback)))
                break;

        return retval;
    }
public:
    CritBitTree(): root(NULL) {}
    bool contains(const Key &key) {
        if (!root) return false;

        value_type *pos=trace(key);
        return key == pos->first;
    }
    bool insert(const Key &key, const T &value=T()) {
        // returns whether the tree is mutated
        return find(key, value).second;
    }
    bool remove(const Key &key) {
        // returns whether the tree is mutated
        if (!root) return false;

        Node **pos=&root, **par=NULL;
        size_t dir;
        while ((*pos)->child[0]) {
            const size_t nth_byte=(*pos)->nth_byte;

            mask_type byte=0;
            if (nth_byte < key.length())
                byte = key[nth_byte];

            dir = ((*pos)->mask&byte? 1:0);

            par = pos;
            pos = &((*pos)->child[dir]);
        }

        if (key != (*pos)->value->first)
            return false;

        delete (*pos)->value;
        delete *pos;
        if (!par) {
            root = NULL;
            return true;
        }

        // reduce the unneeded node, which does not diverge -- not critical bit
        delete *par;
        *par = (*par)->child[1^dir];

        return true;
    }
    template <class Functor>
    int fetch(Functor callback, const Key &prefix="") {
        /* Suffix searching */
        // fetches every element that has given prefix
        // fetches all elements if given prefix is empty
        // returns the status of the last callback executed
        // Note: fetching is aborted if callback returns other than 0

        if (!root) return -1;

        Node *pos=root, *subtop=pos;
        while (pos->child[0]) {
            mask_type byte=0;
            if (pos->nth_byte < prefix.length())
                byte = prefix[pos->nth_byte];

            size_t dir=(pos->mask&byte? 1:0);
            pos = pos->child[dir];
            if (pos->nth_byte < prefix.length())
                subtop = pos;
        }

        for (size_t i=0; i<prefix.length(); ++i)
            if (pos->value->first[i] != prefix[i])
                return -1;

        return traverse(subtop, callback);
    }
    value_type *next(const Key &key) {
        if (!root) return NULL;
        if (!root->child[0])
            return (root->value->first > key)? root->value : NULL;

        Node *subtop=NULL;
        value_type *bestmatch=trace(key, &subtop, 0);

        size_t nth_byte;
        mask_type mask;
        if (differs(key, bestmatch->first, nth_byte, mask)) {
            for (mask_type tmp=mask; (tmp&=tmp-1); mask=tmp);

            Node *pos=root;
            subtop = NULL;
            while (true) {
                if (!pos->child[0]) break;
                if (pos->nth_byte > nth_byte) break;
                if (pos->nth_byte == nth_byte && pos->mask < mask) break;

                mask_type byte=0;
                if (pos->nth_byte < key.length())
                    byte = key[pos->nth_byte];

                size_t dir=(pos->mask&byte? 1:0);
                if (dir == 0) subtop = pos->child[1];
                pos = pos->child[dir];
            }

            if (mask & bestmatch->first[nth_byte]) subtop = pos;
        }

        if (!subtop) return NULL;
        Node *nextleaf=subtop;
        while (nextleaf->child[0])
            nextleaf = nextleaf->child[0];

        return nextleaf->value;
    }
    value_type *prev(const Key &key) {
        if (!root) return NULL;
        if (!root->child[0])
            return (root->value->first < key)? root->value : NULL;

        Node *subtop=NULL;
        value_type *bestmatch=trace(key, &subtop, 1);

        size_t nth_byte;
        mask_type mask;
        if (differs(key, bestmatch->first, nth_byte, mask)) {
            for (mask_type tmp=mask; (tmp&=tmp-1); mask=tmp);

            Node *pos=root;
            subtop = NULL;
            while (true) {
                if (!pos->child[0]) break;
                if (pos->nth_byte > nth_byte) break;
                if (pos->nth_byte == nth_byte && pos->mask < mask) break;

                mask_type byte=0;
                if (pos->nth_byte < key.length())
                    byte = key[pos->nth_byte];

                size_t dir=(pos->mask&byte? 1:0);
                if (dir == 1) subtop = pos->child[1];
                pos = pos->child[dir];
            }

            if (!(mask & bestmatch->first[nth_byte])) subtop = pos;
        }

        if (!subtop) return NULL;
        Node *prevleaf=subtop;
        while (prevleaf->child[1])
            prevleaf = prevleaf->child[1];

        return prevleaf->value;
    }
    T &operator [](const Key &key) {
        return *find(key, T()).first;
    }
};

int main() {
    CritBitTree<string> d;

    while (true) {
        char op, buf[64];
        scanf("%c %s\n", &op, buf);
        string key(buf);

        switch (op) {
        case '$':
            return 0;
        case '?':
            // membership-testing
            printf("%s: %s\n", key.c_str(), d.contains(key)? "Yes":"No");
            break;
        case '+':
            // insertion
            d.insert(key);
            break;
        case '-':
            // removal
            d.remove(key);
            break;
        case '*':
            // traversal in the subset with a given prefix
            if (key == "*")
                key = "";

            printf("%s*:\n", key.c_str());
            {
                // hack: cross initialization
                int order=0;
                auto output=[&order](const auto &item)->int {
                    printf("  %s\n", item.first.c_str());
                    ++order;
                    return 0;
                };
                d.fetch(output, key);

                if (!order) printf("  --\n");
            }

            break;
        case '>':
            // find the smallest string in the tree larger than given key
            {
                pair<const string, nullptr_t> *next=d.next(key);
                printf("%s > %s\n", next? next->first.c_str():"(null)", key.c_str());
            }
            break;
        case '<':
            // find the largest string in the tree smaller than given key
            {
                pair<const string, nullptr_t> *next=d.prev(key);
                printf("%s < %s\n", next? next->first.c_str():"(null)", key.c_str());
            }
            break;
        default:
            printf("Unknown operation: `%c'\n", op);
            return 1;
        }
    }
}
