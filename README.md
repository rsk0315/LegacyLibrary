# Library

## Data Structure
[Starry-sky tree](https://github.com/rsk0315/Library/blob/master/DataStructure/StarrySkyTree.cpp)
- `update(interval, value)`: adds `value` to each of the elements in `interval`
- `query()`: reports the maximum value of all elements

[Fenwick tree](https://github.com/rsk0315/Library/blob/master/DataStructure/FenwickTree.cpp)
- `update(interval, value)`: adds `value` to each of the elements in `interval`
- `query(interval)`: reports the sum of `range`

### Complexity

| Structure name  | update    | query     |
| :-------------- | :-------- | :-------- |
| Starry-sky tree | O(log(N)) | O(1)      |
| Fenwick tree    | O(log(N)) | O(log(N)) |
