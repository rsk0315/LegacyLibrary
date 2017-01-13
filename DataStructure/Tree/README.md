# Trees

[Crit-bit tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/CritBitTree.cpp)
* Update operations
  - `insert(key, object)`: inserts `object` with `key` mapped to
  - `remove(key)`: removes `key` (with mapped object)
* Queries
  - `contains(key)`: reports whether the tree contains `key`
  - `all-prefixed(handler, prefix)`: handles all items whose key has given `prefix`

[Fenwick tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/FenwickTree.cpp)
- `update(interval, value)`: adds `value` to each of the elements in `interval`
- `query(interval)`: reports the sum of `range`

[Link-cut tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/LinkCutTree.cpp)
* Update operations
  - `link(node1, node2)`: links `node1` to `node2`
  - `cut(node)`: cuts `node` from its parent
* Queries
  - `lca(node-pair)`: reports the lowest common ancestor of `node-pair`
  - `connected(node-pair)`: reports whether `node-pair` is connected

[Segment tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/SegmentTree.cpp)
- initialize with aggregative function `F`: e.g. `max`, `add`(`operator +`)
  * F should be binary/associative function
  * if F not in O(1), the complexity of each operation will be O(log(N) F)
- `update(node, value)`: replace the value of `node` with `value`
- `query(interval)`: reports the value of `F(nodes in interval...)`

[Starry-sky tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/StarrySkyTree.cpp)
- `update(interval, value)`: adds `value` to each of the elements in `interval`
- `query()`: reports the maximum value of all elements

[Union-find tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/UnionFindTree.cpp)
* Update operation
  - `unite(node-pair)`: unites `node-pair`
* Queries
  - `connected(node-pair)`: reports whether a path exists between `node-pair` 
  - `rank(node)`: reports the size of the connected components which contains `node`

## Complexity

- α(N) is the inverse of the function f(N)=A(N, N), where A is Ackermann function
- \|S\| is the length of string S

| Structure name  | update(s) | query(s)  |
| :-------------- | :-------- | :-------- |
| Crit-bit tree   | O(\|S\|)  | O(\|S\|)  |
| Fenwick tree    | O(log(N)) | O(log(N)) |
| Link-cut tree   | O(log(N)) | O(log(N)) |
| Segment tree    | O(log(N)) | O(log(N)) |
| Starry-sky tree | O(log(N)) | O(1)      |
| Union-find tree | O(α(N)) <sub>amortized</sub> | O(α(N)) <sub>amortized</sub> |
