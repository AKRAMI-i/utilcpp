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
