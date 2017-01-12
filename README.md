# Library

## Data Structure
[Starry-sky tree](https://github.com/rsk0315/Library/blob/master/DataStructure/StarrySkyTree.cpp)
- `update(interval, value)`: adds `value` to each of the elements in `interval`
- `query()`: reports the maximum value of all elements

[Fenwick tree](https://github.com/rsk0315/Library/blob/master/DataStructure/FenwickTree.cpp)
- `update(interval, value)`: adds `value` to each of the elements in `interval`
- `query(interval)`: reports the sum of `range`

[Union-find tree](https://github.com/rsk0315/Library/blob/master/DataStructure/UnionFindTree.cpp)
- `unite(node-pair)`: unites `node-pair`
- `connected(node-pair)`: reports whether a path exists between `node-pair` 
- `rank(node)`: reports the size of the connected components which contains `node`

### Complexity

- a(N) is the inverse of the function f(N)=A(N, N), where A is Ackermann function
- *italic* means the amortized time

| Structure name  | update    | query     |
| :-------------- | :-------- | :-------- |
| Starry-sky tree | O(log(N)) | O(1)      |
| Fenwick tree    | O(log(N)) | O(log(N)) |

| Structure name  | unite     | connected | rank      |
| :-------------- | :-------- | :-------- | :-------- |
| Union-find tree | *O(a(N))* | *O(a(N))* | *O(a(N))* |
