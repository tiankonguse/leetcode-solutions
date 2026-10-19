[101138\. 设计公交车座位预订系统](https://leetcode.cn/problems/design-bus-seat-booking-system/)

中等

相关企业

请你设计一个公交车座位预订系统。

公交车共有 `n` 排座位。每一排有四个座位，分别标记为 `"A"` 、 `"B"` 、 `"C"` 和 `"D"` 。

座位 `"A"` 和 `"D"` 是 **靠窗** 座位；座位 `"B"` 和 `"C"` 是 **中间** 座位。在每一排中，座位 `"A"` 与座位 `"B"` **相邻** ，座位 `"D"` 与座位 `"C"` **相邻** 。

预订规则如下：

- 预订一个 **中间** 座位（ `"B"` 或 `"C"` ）始终需要 1 秒。
- 预订一个 **靠窗** 座位（ `"A"` 或 `"D"` ）时，如果与其 **相邻的中间** 座位 **尚未** 被预订，则需要 1 秒；如果相邻的中间座位 **已经** 被预订，则需要 3 秒（额外增加 2 秒延迟）。

一个座位由形如 `"A1"` 或 `"D20"` 的字符串表示，即一个从 `A` 到 `D` 的字母，后跟其所在的排号。

实现 `BusBooking` 类：

- `BusBooking(int n)` ：使用 `n` 排 **空** 座位初始化系统。
- `void toggle(string seat)` ：如果 `seat` 尚未被预订，则预订该座位；如果已经被预订，则释放该座位。
- `int getTotalTime()` ：返回预订当前 **所有** 已预订座位所需的总时间（秒），预订顺序按照这些座位对应的 `toggle` 调用顺序。如果当前没有已预订座位，则返回 0。
- `int getMinTime()` ：返回预订当前 **所有** 已预订座位所需的 **最小** 总时间（秒），可以任意调整这些座位的预订顺序。如果当前没有已预订座位，则返回 0。

**注意：** 一个座位的时间开销会在其被预订时确定，取决于当时其他座位的预订状态。之后再预订或释放其他座位，都不会改变已经预订座位的时间开销。

**示例 1：**

**输入：**  
\["BusBooking", "toggle", "toggle", "getTotalTime", "getMinTime", "toggle", "toggle", "getTotalTime", "getMinTime"\]  
\[\[20\], \["B3"\], \["A3"\], \[\], \[\], \["C3"\], \["D3"\], \[\], \[\]\]

**输出：**  
\[null, null, null, 4, 2, null, null, 8, 4\]

**解释：**

BusBooking busBooking = new BusBooking(20); // 初始有 20 排空座位  
busBooking.toggle("B3"); // 预订 `"B3"` 。这是一个中间座位，需要 1 秒。当前总时间为 1。  
busBooking.toggle("A3"); // 预订 `"A3"` 。这是一个靠窗座位，其相邻的中间座位 `"B3"` 已经被预订，因此需要 3 秒。当前总时间为 `1 + 3 = 4` 。  
busBooking.getTotalTime(); // 返回 4，因为按照 toggle 的调用顺序， `"B3"` 需要 1 秒， `"A3"` 需要 3 秒。  
busBooking.getMinTime(); // 返回 2。如果先预订 `"A3"` ，再预订 `"B3"` ，就可以避免额外延迟，因此预订两个座位共需要 2 秒。  
busBooking.toggle("C3"); // 预订 `"C3"` 。这是一个中间座位，需要 1 秒。当前总时间为 `4 + 1 = 5` 。  
busBooking.toggle("D3"); // 预订 `"D3"` 。这是一个靠窗座位，其相邻的中间座位 `"C3"` 已经被预订，因此需要 3 秒。当前总时间为 `5 + 3 = 8` 。  
busBooking.getTotalTime(); // 返回 8，因为按照 toggle 的调用顺序，各座位的时间开销依次为 1、3、1、3。  
busBooking.getMinTime(); // 返回 4。按照最优预订顺序，不会产生任何额外延迟，因此预订 4 个座位需要 `4 * 1 = 4` 秒。

**示例 2：**

**输入：**  
\["BusBooking", "toggle", "toggle", "getTotalTime", "toggle", "toggle", "toggle", "getTotalTime", "getMinTime"\]  
\[\[10\], \["C7"\], \["D7"\], \[\], \["D7"\], \["C7"\], \["D7"\], \[\], \[\]\]

**输出：**  
\[null, null, null, 4, null, null, null, 1, 1\]

**解释：**

BusBooking busBooking = new BusBooking(10); // 初始有 10 排空座位  
busBooking.toggle("C7"); // 预订 `"C7"` 。这是一个中间座位，需要 1 秒。当前总时间为 1。  
busBooking.toggle("D7"); // 预订 `"D7"` 。这是一个靠窗座位，其相邻的中间座位 `"C7"` 已经被预订，因此需要 3 秒。当前总时间为 `1 + 3 = 4` 。  
busBooking.getTotalTime(); // 返回 4，因为按照 toggle 的调用顺序， `"C7"` 需要 1 秒， `"D7"` 需要 3 秒。  
busBooking.toggle("D7"); // `"D7"` 已经被预订，因此将其释放。这会移除它对应的 3 秒时间开销。当前总时间为 `4 - 3 = 1` 。  
busBooking.toggle("C7"); // `"C7"` 已经被预订，因此将其释放。这会移除它对应的 1 秒时间开销。当前总时间为 `1 - 1 = 0` ，此时第 7 排为空。  
busBooking.toggle("D7"); // 再次预订 `"D7"` 。这是一个靠窗座位，这次其相邻的中间座位 `"C7"` 尚未被预订，因此只需要 1 秒。当前总时间为 `0 + 1 = 1` 。  
busBooking.getTotalTime(); // 返回 1，因为当前只有 `"D7"` 被预订，并且这次预订的时间开销为 1 秒。  
busBooking.getMinTime(); // 返回 1。按照最优预订顺序，当前唯一一个已预订座位需要 `1 * 1 = 1` 秒。

**提示：**

- `1 <= n <= 10<sup>5</sup>`
- `seat[0]` 是 `'A'` 、 `'B'` 、 `'C'` 、 `'D'` 之一。
- `seat` 中剩余字符组成一个整数 `row` ，满足 `1 <= row <= n` 。
- 对 `toggle` 、 `getTotalTime` 和 `getMinTime` 的调用总次数不超过 `10<sup>5</sup>` 。

---