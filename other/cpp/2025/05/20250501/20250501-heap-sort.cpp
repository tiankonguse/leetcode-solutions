#include <iostream>
#include <vector>

// 堆化操作 - 将以 i 为根的子树调整为最大堆
void heapify(std::vector<int>& arr, int n, int i) {
  int largest = i;        // 初始化largest为根节点
  int left = 2 * i + 1;   // 左子节点
  int right = 2 * i + 2;  // 右子节点

  // 如果左子节点大于根节点
  if (left < n && arr[left] > arr[largest]) largest = left;

  // 如果右子节点大于当前最大值
  if (right < n && arr[right] > arr[largest]) largest = right;

  // 如果最大值不是根节点
  if (largest != i) {
    std::swap(arr[i], arr[largest]);

    // 递归地堆化受影响的子树
    heapify(arr, n, largest);
  }
}

// 堆排序函数
void heapSort(std::vector<int>& arr) {
  int n = arr.size();

  // 构建最大堆（从最后一个非叶子节点开始向上调整）
  for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

  // 一个个从堆顶取出元素
  for (int i = n - 1; i > 0; i--) {
    // 将当前根（最大值）移到末尾
    std::swap(arr[0], arr[i]);

    // 在减小的堆上调用heapify
    heapify(arr, i, 0);
  }
}

// 测试函数
int main() {
  std::vector<int> arr = {12, 11, 13, 5, 6, 7};

  std::cout << "排序前的数组: ";
  for (int num : arr) std::cout << num << " ";
  std::cout << std::endl;

  heapSort(arr);

  std::cout << "排序后的数组: ";
  for (int num : arr) std::cout << num << " ";
  std::cout << std::endl;

  return 0;
}