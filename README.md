#  utilcpp — C++ String Utilities Library

![License](https://img.shields.io/badge/license-MIT-green.svg)  
![C++](https://img.shields.io/badge/language-C++17-blue.svg)  
![Status](https://img.shields.io/badge/status-in%20development-orange.svg)  
![Header Only](https://img.shields.io/badge/library-header--only-lightgrey.svg)  
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20Mac-blueviolet.svg)

---

##  Overview

**utilcpp** is a lightweight, header-only C++ library that provides fast and practical utilities for working with **ASCII and UTF-8 strings**.

It is designed to be:
- ⚡ Fast
-  Easy to integrate
-  Dependency-free
-  Clean and readable

Perfect for developers who need common string operations without relying on heavy external libraries.

---

##  Project Status

>  **This project is currently under development.**  
Some features are incomplete, and additional functionality will be added in future updates.

---

##  Features

###  ASCII Utilities (`utility::str`)
- Case conversion:
  - `upper`
  - `lower`
- Whitespace handling:
  - `trim`
  - `remove_space`
  - `remove_spaces`
- String operations:
  - `split`
  - `join`
  - `replace_all`
- Substring checks:
  - `contains`
  - `starts_with`
  - `ends_with`
- Other helpers:
  - `reverse`
  - `count`
  - `repeat`
  - `is_number`

---

###  UTF-8 Utilities (`utility::utf8`)
- UTF-8 decoding & encoding:
  - `utf8_to_codepoints`
  - `codepoints_to_utf8`
- Unicode-safe operations:
  - `utf8_trim`
  - `utf8_reverse`
  - `utf8_split`
  - `utf8_replace_all`
  - `utf8_join`
- String checks:
  - `utf8_contains`
  - `utf8_starts_with`
  - `utf8_ends_with`
  - `utf8_count`
- Character-aware length:
  - `utf8_length`

---

##  Installation

This is a **header-only library**, so no compilation or installation is required.

### 1. Add the file to your project

---

---

##  Usage

After including the header file, all utilities are available under the `utility` namespace.

---

###  Include the Library

## Usage for UTF-8

```cpp

#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdint>
#include <algorithm>
#include "utilcpp.h"

int main() {

    SetConsoleOutputCP(CP_UTF8);
    using namespace utility::utf8;

    // --------------------------------------------------
    // Basic Input
    // --------------------------------------------------
    std::string text = "   سلام دنیا خوش آمدی   ";

    std::cout << "=== BASIC ===\n";

    // Trim
    std::string trimmed = utf8_trim(text);
    std::cout << "Trim: [" << trimmed << "]\n";

    // Length
    std::cout << "Length: " << utf8_length(trimmed) << "\n";

    // Reverse
    std::cout << "Reverse: " << utf8_reverse(trimmed) << "\n";


    // --------------------------------------------------
    // Search Operations
    // --------------------------------------------------
    std::cout << "\n=== SEARCH ===\n";

    std::cout << "Contains 'دنیا': "
        << (utf8_contains(trimmed, "دنیا") ? "true" : "false") << "\n";

    std::cout << "Starts with 'سلام': "
        << (utf8_starts_with(trimmed, "سلام") ? "true" : "false") << "\n";

    std::cout << "Ends with 'آمدی': "
        << (utf8_ends_with(trimmed, "آمدی") ? "true" : "false") << "\n";


    // --------------------------------------------------
    // Count
    // --------------------------------------------------
    std::cout << "\n=== COUNT ===\n";

    std::cout << "Count 'ا': "
        << utf8_count(trimmed, "ا") << "\n";


    // --------------------------------------------------
    // Split & Join
    // --------------------------------------------------
    std::cout << "\n=== SPLIT & JOIN ===\n";

    std::vector<std::string> parts = utf8_split(trimmed, " ");

    std::cout << "Split:\n";
    for (const auto& p : parts) {
        std::cout << "- " << p << "\n";
    }

    std::cout << "Join: "
        << utf8_join(parts, " | ") << "\n";


    // --------------------------------------------------
    // Replace
    // --------------------------------------------------
    std::cout << "\n=== REPLACE ===\n";

    std::cout << "Replace 'دنیا' → 'جهان': "
        << utf8_replace_all(trimmed, "دنیا", "جهان") << "\n";


    // --------------------------------------------------
    // Chinese Example
    // --------------------------------------------------
    std::cout << "\n=== CHINESE ===\n";

    std::string chinese = "你好 世界";

    std::cout << "Original: " << chinese << "\n";
    std::cout << "Length: " << utf8_length(chinese) << "\n";
    std::cout << "Reverse: " << utf8_reverse(chinese) << "\n";


    // --------------------------------------------------
    // Mixed Language Example
    // --------------------------------------------------
    std::cout << "\n=== MIXED ===\n";

    std::string mixed = "Hello سلام 123";

    std::cout << "Original: " << mixed << "\n";
    std::cout << "Length: " << utf8_length(mixed) << "\n";
    std::cout << "Reverse: " << utf8_reverse(mixed) << "\n";

    std::cout << "Contains 'سلام': "
        << (utf8_contains(mixed, "سلام") ? "true" : "false") << "\n";

    std::cout << "Replace 'سلام' → 'Hi': "
        << utf8_replace_all(mixed, "سلام", "Hi") << "\n";


    return 0;
}

```


##  Usage for ASCII

```cpp
#include <iostream>
#include "utilcpp.h"

int main() {
    using namespace utility::str;

    std::string texts[3] = {
        "   Hello World   ",
        "C++ is AWESOME",
        "   123,abc,XYZ   "
    };

    for (int i = 0; i < 3; i++) {
        std::string text = texts[i];

        std::cout << "\n=== TEST " << i + 1 << " ===\n";
        std::cout << "Original: [" << text << "]\n";

        // TRIM
        auto t = trim(text);
        std::cout << "Trim: [" << t << "]\n";

		// REMOVE SPACES
		std::cout << "Remove spaces: [" << remove_space(t) << "]\n";

        // UPPER
        std::cout << "Upper: " << upper(t) << "\n";

        // LOWER
        std::cout << "Lower: " << lower(t) << "\n";

        // REPLACE
        std::cout << "Replace (World→C++): "
            << replace_all(t, "World", "C++") << "\n";

        // CONTAINS
        std::cout << "Contains 'is': "
            << (contains(t, "is") ? "true" : "false") << "\n";

        // STARTS_WITH
        std::cout << "Starts with 'C++': "
            << (starts_with(t, "C++") ? "true" : "false") << "\n";

        // ENDS_WITH
        std::cout << "Ends with 'XYZ': "
            << (ends_with(t, "XYZ") ? "true" : "false") << "\n";

        // SPLIT (only for comma case)
        auto parts = split(t, ',');
        std::cout << "Split:\n";
        for (auto& p : parts) {
            std::cout << "  - " << p << "\n";
        }

        // JOIN
        std::cout << "Join with '-': "
            << join(parts, '-') << "\n";

        // REVERSE
        std::cout << "Reverse: " << reverse(t) << "\n";

        // COUNT
        std::cout << "Count 'a': "
            << count(t, 'a') << "\n";

        // IS_NUMBER
        std::cout << "Is number: "
            << (is_number(t) ? "true" : "false") << "\n";

        // REPEAT
        std::cout << "Repeat x2: "
            << repeat(t, 2) << "\n";
    }

    return 0;
}

```


---

## 🤝 Contributing

Contributions are welcome and appreciated!

If you'd like to contribute to **utilcpp**, you can:

-  Report bugs
-  Suggest new features
-  Improve existing functions
-  Optimize performance
-  Improve documentation
9
