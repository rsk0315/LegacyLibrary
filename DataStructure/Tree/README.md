# Trees

[Starry-sky tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/StarrySkyTree.cpp)
- `update(interval, value)`: adds `value` to each of the elements in `interval`
- `query()`: reports the maximum value of all elements

[Fenwick tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/FenwickTree.cpp)
- `update(interval, value)`: adds `value` to each of the elements in `interval`
- `query(interval)`: reports the sum of `range`

[Segment tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/SegmentTree.cpp)
- initialize with aggregative function `F`: e.g. `max`, `add`(`operator +`)
  * F should be binary/associative function
  * if F not in O(1), the complexity of each operation will be O(log(N) F)
- `update(node, value)`: replace the value of `node` with `value`
- `query(interval)`: reports the value of `F(nodes in interval...)`

[Union-find tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/UnionFindTree.cpp)
* Update
  - `unite(node-pair)`: unites `node-pair`
* Queries
  - `connected(node-pair)`: reports whether a path exists between `node-pair` 
  - `rank(node)`: reports the size of the connected components which contains `node`

[Crit-bit tree](https://github.com/rsk0315/Library/blob/master/DataStructure/Tree/CritBitTree.cpp)
* Updates
  - `insert(key, object)`: inserts `object` with `key` mapped to
  - `remove(key)`: removes `key` (with mapped object)
* Queries
  - `contains(key)`: reports whether the tree contains `key`
  - `all-prefixed(handler, prefix)`: handles all items whose key has given `prefix`

## Complexity

- α(N) is the inverse of the function f(N)=A(N, N), where A is Ackermann function
- \|S\| means the length of string S
- *italic* means the amortized time

| Structure name  | update(s) | query(s)  |
| :-------------- | :-------- | :-------- |
| Starry-sky tree | O(log(N)) | O(1)      |
| Fenwick tree    | O(log(N)) | O(log(N)) |
| Segment tree    | O(log(N)) | O(log(N)) |
| Union-find tree | *O(α(N))* | *O(α(N))* |
| Crit-bit tree   | O(\|S\|)  | O(\|S\|)  |
