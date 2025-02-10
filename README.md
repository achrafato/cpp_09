## 📁 Exercises

### Ex00: Bitcoin Exchange
In Ex00, we implement a program that simulates a Bitcoin exchange rate system. The goal is to parse input data from a file and calculate the total value of Bitcoin based on specific date exchange rates. This exercise involves file handling, parsing data, and managing dates.

```
Files:
├── ex00/BitcoinExchange.cpp
├── ex00/BitcoinExchange.hpp
├── ex00/Makefile
├── ex00/main.cpp
```

### Ex01: RPN (Reverse Polish Notation)
In Ex01, we implement a calculator that evaluates mathematical expressions in Reverse Polish Notation (RPN). RPN eliminates the need for parentheses, using a stack to evaluate expressions as they are read. This exercise reinforces understanding of stacks and operators.

```
Files:
├── ex01/RPN.cpp
├── ex01/RPN.hpp
├── ex01/Makefile
├── ex01/main.cpp
```

### Ex02: PmergeMe
In Ex02, we implement a program that sorts a set of numbers using a combination of merge sort and a custom algorithm. The challenge is to create an efficient sorting algorithm and measure its time performance. This exercise enhances your understanding of sorting algorithms and performance measurement.

```
Files:
├── ex02/PmergeMe.cpp
├── ex02/PmergeMe.hpp
├── ex02/Makefile
├── ex02/main.cpp
```

## 🤖 Class Features

### BitcoinExchange
```cpp
class BitcoinExchange {
private:
    std::map<std::string, float> exchangeRates;

public:
    void loadRates(const std::string &filename);
    float calculateTotal(const std::string &date, float quantity);
};
```

### RPN
```cpp
class RPN {
private:
    std::stack<int> operands;

public:
    int evaluate(const std::string &expression);
    void performOperation(char op);
};
```

### PmergeMe
```cpp
class PmergeMe {
private:
    std::vector<int> numbers;

public:
    void mergeSort(std::vector<int> &vec);
    void sortNumbers(int argc, char **argv);
    double measureTime(void (*sortFunction)(std::vector<int>&));
};
```

## 🎯 Learning Objectives

1. **File Handling & Parsing**
   - Learn how to read and process data from files (BitcoinExchange).
   - Handle various types of data and manage input formats effectively.

2. **Stacks & Data Structures**
   - Understand stack-based operations, especially in RPN calculators.
   - Efficiently implement stack operations and understand stack-based evaluation.

3. **Sorting Algorithms**
   - Gain experience in implementing and testing sorting algorithms, specifically merge sort, and understand their performance characteristics.
   - Analyze time complexity and optimize sorting operations.

4. **Performance Measurement**
   - Learn how to measure and optimize the performance of algorithms (PmergeMe).
   - Use time measurement tools to evaluate the efficiency of sorting algorithms.

## 🛠️ Implementation Requirements

- **Orthodox Canonical Form**: Ensure classes like `BitcoinExchange`, `RPN`, and `PmergeMe` follow the Orthodox Canonical Form.
- **Memory Management**: Properly manage memory, especially when dealing with dynamic data in containers (e.g., `std::map`, `std::stack`, `std::vector`).
- **Template Functions**: If applicable, use template functions for sorting or generic tasks.
- **File Parsing**: Handle the parsing of files, including error checking for data validity.

## 🧪 Testing Guidelines

### Ex00: Bitcoin Exchange
```cpp
BitcoinExchange exchange;
exchange.loadRates("data.txt");
float total = exchange.calculateTotal("2025-02-10", 5);
std::cout << "Total: " << total << " BTC" << std::endl;
```

### Ex01: RPN
```cpp
RPN rpn;
int result = rpn.evaluate("5 3 + 2 *");
std::cout << "RPN Result: " << result << std::endl;
```

### Ex02: PmergeMe
```cpp
PmergeMe sorter;
sorter.sortNumbers(argc, argv);
```

## ⚠️ Common Issues to Watch

1. **File Parsing**
   - Make sure to properly handle errors when loading files (e.g., missing file, malformed data).
   - Ensure the date format and Bitcoin rate are correctly parsed and stored.

2. **Stack Operations in RPN**
   - Ensure that the RPN calculator correctly handles edge cases like invalid expressions or empty stacks.
   - Check that operator precedence is correctly managed.

3. **Sorting Algorithm Efficiency**
   - Ensure that the sorting algorithm in `PmergeMe` works efficiently, especially for larger datasets.
   - Be mindful of the time complexity and avoid unnecessary computations during sorting.

4. **Memory Management**
   - Avoid memory leaks by ensuring proper memory handling, especially when dynamically allocating containers like `std::vector`, `std::map`, or `std::stack`.

## 📝 Style Requirements

- Consistent and descriptive class names, especially for core classes like `BitcoinExchange`, `RPN`, and `PmergeMe`.
- Proper indentation and comments for readability.
- Well-structured header and source files.
- Clear, readable, and self-documenting code.

## 🔍 Debugging Tips

1. **File Parsing Debugging**
   - Check the data format in your files (e.g., date formats, Bitcoin exchange rates) and ensure proper parsing.

2. **RPN Evaluation**
   - Use a debugger or print statements to verify that operators are being correctly applied and the stack behaves as expected.

3. **Sorting Algorithm Debugging**
   - Test with small datasets first to ensure correctness.
   - Use time measurement to evaluate performance for larger datasets.

## 📜 License

This project is part of the 42 curriculum and is provided as-is.
