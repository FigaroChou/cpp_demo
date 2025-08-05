# C++ STL 容器详细介绍

##  一、STL 容器总览

| 分类         | 容器名                                      |
|--------------|---------------------------------------------|
| 顺序容器     | `vector`, `list`, `deque`, `array`, `forward_list` |
| 关联容器     | `set`, `multiset`, `map`, `multimap`        |
| 无序关联容器 | `unordered_set`, `unordered_multiset`, `unordered_map`, `unordered_multimap` |
| 容器适配器   | `stack`, `queue`, `priority_queue`          |

---

##  二、顺序容器

### 1. `vector`
- 底层结构：动态数组
- 特点：
  - 支持随机访问
  - 末尾操作高效，O(1)
  - 中间插入/删除效率低，O(n)
- 常用操作：`push_back`, `pop_back`, `resize`, `capacity`, `reserve`
- 适用场景：频繁阅读，偶尔操作末尾

### 2. `list`
- 底层结构：双向链表
- 特点：
  - 不支持随机访问
  - 任意位置操作效率高，O(1)
- 常用操作：`push_front`, `push_back`, `insert`, `erase`, `remove`, `splice`
- 适用场景：中间频繁操作

### 3. `deque`
- 底层结构：分段连续内存 + 中控器
- 特点：
  - 支持头尾插入/删除，O(1)
  - 支持随机访问
- 适用场景：需要头尾效率操作

### 4. `array`
- 底层：静态数组封装
- 特点：
  - 定长，编译期大小确定
- 适用场景：性能极致要求

### 5. `forward_list`
- 底层：单向链表
- 特点：
  - 内存占用小
  - 不支持双向遍历，也不支持 `size()`
- 适用场景：工程化、嵌入式系统

---

##  三、关联容器

### `set` / `multiset`
- 特点：元素唯一 / 允许重复
- 底层：红黑树
- 时间复杂度：O(log n)
- 适用场景：需要排序和快速查找

### `map` / `multimap`
- 特点：键值对，key 唯一 / 允许重复
- 常用操作：`insert`, `find`, `erase`, `operator[]`
- 适用场景：排序存储实例

---

##  四、无序关联容器

### `unordered_set` / `unordered_multiset`
- 底层：哪个哪个 hash table
- 特点：无序、快速查找
- 时间复杂度：平均 O(1)，最坏 O(n)

### `unordered_map` / `unordered_multimap`
- 特点：键值对，key 无序
- 适用场景：快速存取、查找

---

## 五、容器适配器

| 名称           | 底层实现      | 特点                                   |
|-------------------|---------------|----------------------------------------|
| `stack`           | `deque`       | 先进后出                         |
| `queue`           | `deque`       | 先进先出                         |
| `priority_queue`  | `vector` + 堆 | 大顶堆                             |

---

##  六、容器选择建议

| 需求             | 选择              |
|------------------|------------------------|
| 随机访问         | `vector`, `deque`     |
| 头尾高效操作     | `list`, `deque`        |
| 有序存储         | `set`, `map`           |
| 无序快速查找     | `unordered_map`, `unordered_set` |
| 键值对存储     | `map`, `unordered_map` |
| 栈             | `stack`                |
| 队列            | `queue`                |
| 堆             | `priority_queue`       |

---

##  七、 迭代器支持

| 容器     | 迭代器类型           |
|----------|------------------------------|
| `vector`/`deque`/`array` | 随机访问迭代器 |
| `list`    | 双向迭代器          |
| `set`/`map` | 双向迭代器          |
| `unordered_*` | 单向迭代器          |

### 常见问题
- 插入/删除导致 **迭代器失效**（如 `vector` 和 `deque`）
- `unordered_map` 中使用自定义 key 需提供 hash 和 `==`
- `map` 使用 `operator[]` 时会插入默认值



## 八、使用陷阱总结

### 1. 迭代器失效

- `vector`/`deque`：插入或删除会导致后续元素迭代器失效
- `list`：插入不影响迭代器，删除元素本身的迭代器会失效
- `map`/`set`：插入不影响现有迭代器，删除元素的迭代器会失效
-  避免在迭代器循环中直接删除当前元素，需用 `it = container.erase(it);`

### 2. 容器适配器不支持遍历

- `stack`、`queue`、`priority_queue` 没有提供迭代器接口，无法遍历其元素
-  若需要遍历，建议使用底层容器自行管理

### 3. `unordered_map` 自定义类型做 key

- 编译报错：“no hash for user-defined type”
-  需自定义 `std::hash<T>` 特化结构体，并重载 `operator==`

### 4. `map::operator[]` 隐式插入

- 使用 `m[key]` 会在 key 不存在时默认插入一条 key 对应的默认值
- 若只想查找，请用 `find()` 避免意外插入

### 5. 使用 insert 时重复插入检查

- `set`/`map` 的 `insert` 返回 `pair<iterator,bool>`，`bool` 表示是否插入成功
-  一般推荐写法：

```c++
auto [it, success] = mySet.insert(x);
if (!success) std::cout << "Already exists";
```

### 6. 指针类型元素的排序问题

- `set<T*>` 会按地址排序，而不是指针所指内容排序
-  若希望按内容排序，应自定义比较器 `struct cmp { bool operator()(T* a, T* b) const { return *a < *b; } };`

### 7. 容器内存膨胀与回收

- `vector` 通过 `reserve` 增长容量，但 `shrink_to_fit()` 不是强制回收
-  清空并回收内存：`vector<T>().swap(v);`

### 8. 指向容器元素的指针悬空

- 删除或 `resize` 后，原有元素地址可能失效
- 不要持有 `vector` 等容器内元素的裸指针

### 9. 对关联容器使用 `erase(it++)`

- 正确写法避免失效：

```c++
for (auto it = m.begin(); it != m.end(); ) {
    if (条件) it = m.erase(it);
    else ++it;
}
```



## 九、常见 STL 容器操作性能对比

| 操作/容器          | `vector`        | `deque`         | `list` | `set` / `map` | `unordered_map` / `unordered_set` |
| ------------------ | --------------- | --------------- | ------ | ------------- | --------------------------------- |
| 随机访问           | ✅ O(1)          | ✅ O(1)          | ❌ O(n) | ❌ O(log n)    | ❌ O(1) 平均                       |
| 尾部插入删除       | ✅ O(1)          | ✅ O(1)          | ✅ O(1) | ❌ O(log n)    | ❌ O(1) 平均                       |
| 头部插入删除       | ❌ O(n)          | ✅ O(1)          | ✅ O(1) | ❌ O(log n)    | ❌ O(1) 平均                       |
| 中间插入删除       | ❌ O(n)          | ❌ O(n)          | ✅ O(1) | ❌ O(log n)    | ❌ O(1) 平均                       |
| 按值查找（非 key） | ❌ O(n)          | ❌ O(n)          | ❌ O(n) | ❌ O(log n)    | ❌ O(n)                            |
| 按 key 查找        | ❌ O(n)          | ❌ O(n)          | ❌ O(n) | ✅ O(log n)    | ✅ O(1) 平均                       |
| 自动排序           | ❌               | ❌               | ❌      | ✅             | ❌                                 |
| 元素唯一性检查     | ❌               | ❌               | ❌      | ✅（set/map）  | ✅（unordered_set/map）            |
| 迭代器稳定性       | ❌ 插入/删除失效 | ❌ 插入/删除失效 | ✅ 稳定 | ✅ 稳定        | ❌ 插入/rehash 失效                |

### 说明：

- 上表为典型复杂度，具体可能因容器状态（负载因子、哈希冲突等）略有浮动。
- `unordered_map` 插入、查找平均 O(1)，但最坏 O(n)，需注意 hash 函数质量。
- `list` 的迭代器在插入/删除时不会失效；而 `vector`/`deque` 中通常会失效。



## 十、容器底层实现结构概览

### 1. `vector`

- **结构**：单块连续内存的动态数组
- **扩容策略**：一般按 2 倍扩容（如 GCC），涉及内存重新分配和元素拷贝
- **适配器容器底层容器**：`priority_queue` 默认使用它

### 2. `deque`

- **结构**：分段数组（central map + buffer block），中控指针数组维护 buffer 指针
- **优点**：支持头尾常数级插入删除，不需要整体移动数据

### 3. `list`

- **结构**：双向链表，每个节点有前驱、数据、后继指针
- **特点**：节点独立分配，插入/删除稳定，不需移动其他元素

### 4. `forward_list`

- **结构**：单向链表，仅维护 next 指针
- **优点**：节省内存，适用于嵌入式等场景

### 5. `set` / `map`

- **结构**：平衡二叉查找树，通常为红黑树（RB-Tree）
- **关键点**：节点中保存 key（set）或 pair<key, value>（map），自动保持有序
- **遍历顺序**：中序遍历，天然有序输出

### 6. `unordered_set` / `unordered_map`

- **结构**：哈希表（Hash Table）+ 拉链法冲突解决
- **组成**：桶数组 + 节点链表；每个桶指向一个链表头
- **rehash 时机**：元素数量超过负载因子阈值

### 7. `stack` / `queue`

- **结构**：容器适配器，默认使用 `deque` 作为底层容器
- **行为**：封装接口，禁止随机访问，仅允许 push/pop/front/back/top 等操作

### 8. `priority_queue`

- **结构**：基于 `vector` 的最大堆
- **实现**：通过 `std::push_heap`, `std::pop_heap` 操作维护堆序性
- **自定义排序**：可通过仿函数指定为小顶堆或其他结构
