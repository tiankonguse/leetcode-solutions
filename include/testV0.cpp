#include <iostream>
#include <vector>
#include <functional>

int main() {
    std::vector<std::function<void(typename)>> functions;

    // 添加不同参数类型的函数
    
    functions.emplace_back([](int x) { std::cout << "Function with int argument: " << x << std::endl; });
    
    functions.emplace_back([](double y) { std::cout << "Function with double argument: " << y << std::endl; });

    // 调用存储的函数
    for (const auto& func : functions) {
        func(1.2);
    }

    return 0;
}