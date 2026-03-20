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
