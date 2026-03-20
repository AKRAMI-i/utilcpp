#pragma once
#include <string>
#include <cctype>
#include <locale>
#include <vector>
#include <Windows.h>
#include <cstdint>
#include <algorithm>

namespace utility {

	// ASCII character manipulation and string utilities
    namespace str {
        inline std::string upper(std::string text) {
            std::locale loc;
            for (char& c : text) {
                c = std::toupper(static_cast<unsigned char>(c), loc);
            }
            return text;
        }

        inline std::string lower(std::string text) {
            std::locale loc;
            for (char& c : text) {
                c = std::tolower(static_cast<unsigned char>(c), loc);
            }
            return text;
        }


        inline std::string trim(const std::string& str) {
            size_t start = 0;
            size_t end = str.size();

            while (start < end && std::isspace(static_cast<unsigned char>(str[start]))) {
                start++;
            }

            while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) {
                end--;
            }

            return str.substr(start, end - start);
        }

        inline std::string remove_space(std::string str) {
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
            return str;
        }

        inline std::vector<std::string> split(const std::string& str, char delimiter) {
            std::vector<std::string> result;
            size_t start = 0;

            while (true) {
                size_t pos = str.find(delimiter, start);

                if (pos == std::string::npos) {
                    result.push_back(str.substr(start));
                    break;
                }

                result.push_back(str.substr(start, pos - start));
                start = pos + 1;
            }

            return result;
        }

        inline std::string replace_all(std::string str, const std::string& from, const std::string& to) {
            if (from.empty()) return str;

            size_t pos = 0;

            while ((pos = str.find(from, pos)) != std::string::npos) {
                str.replace(pos, from.length(), to);
                pos += to.length();
            }

            return str;
        }

        inline bool contains(const std::string& str, const std::string& sub) {
            return str.find(sub) != std::string::npos;
        }

        inline bool starts_with(const std::string& str, const std::string& prefix) {
            if (prefix.size() > str.size()) return false;
            return str.substr(0, prefix.size()) == prefix;
        }

        inline bool ends_with(const std::string& str, const std::string& suffix) {
            if (suffix.size() > str.size()) return false;
            return str.substr(str.size() - suffix.size()) == suffix;
        }
        
        inline std::string join(const std::vector<std::string>& vec, char delimiter) {
            std::string result;

            for (size_t i = 0; i < vec.size(); i++) {
                result += vec[i];
                if (i != vec.size() - 1) {
                    result += delimiter;
                }
            }

            return result;
        }

        inline std::string remove_spaces(std::string str) {
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
            return str;
        }

        inline int count(const std::string& str, char ch) {
            return std::count(str.begin(), str.end(), ch);
        }

        inline std::string reverse(std::string str) {
            std::reverse(str.begin(), str.end());
            return str;
        }

        inline bool is_number(const std::string& str) {
            if (str.empty()) return false;

            for (char c : str) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    return false;
                }
            }
            return true;
        }

        inline std::string repeat(const std::string& str, int times) {
            std::string result;
            for (int i = 0; i < times; i++) {
                result += str;
            }
            return result;
        }
    }

    
	// UTF-8 string utilities
    namespace utf8
    {

        // UTF-8 DECODE function
        inline std::vector<uint32_t> utf8_to_codepoints(const std::string& str) {
            std::vector<uint32_t> result;

            for (size_t i = 0; i < str.size();) {
                uint32_t cp = 0;
                unsigned char c = str[i];

                if ((c >> 7) == 0) {
                    cp = c;
                    i += 1;
                }
                else if ((c >> 5) == 0b110) {
                    cp = ((c & 0x1F) << 6) |
                        (str[i + 1] & 0x3F);
                    i += 2;
                }
                else if ((c >> 4) == 0b1110) {
                    cp = ((c & 0x0F) << 12) |
                        ((str[i + 1] & 0x3F) << 6) |
                        (str[i + 2] & 0x3F);
                    i += 3;
                }
                else {
                    cp = ((c & 0x07) << 18) |
                        ((str[i + 1] & 0x3F) << 12) |
                        ((str[i + 2] & 0x3F) << 6) |
                        (str[i + 3] & 0x3F);
                    i += 4;
                }

                result.push_back(cp);
            }

            return result;
        }

		// UTF-8 ENCODE function
        inline std::string codepoints_to_utf8(const std::vector<uint32_t>& cps) {
            std::string result;

            for (uint32_t cp : cps) {
                if (cp <= 0x7F)
                    result += static_cast<char>(cp);
                else if (cp <= 0x7FF) {
                    result += static_cast<char>(0xC0 | (cp >> 6));
                    result += static_cast<char>(0x80 | (cp & 0x3F));
                }
                else if (cp <= 0xFFFF) {
                    result += static_cast<char>(0xE0 | (cp >> 12));
                    result += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
                    result += static_cast<char>(0x80 | (cp & 0x3F));
                }
                else {
                    result += static_cast<char>(0xF0 | (cp >> 18));
                    result += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
                    result += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
                    result += static_cast<char>(0x80 | (cp & 0x3F));
                }
            }

            return result;
        }

		// UTF-8 UPPER and LOWER case convertion are extremely complex due to the vast number
		// of Unicode characters and their unique case mapping rules. For this reason,
        // we will not implement these functions here.
        // Instead, we recommend using a library like ICU (International Components for Unicode)
        // for comprehensive Unicode support.



        inline bool is_space(uint32_t cp) {
            return cp == 0x20 || cp == 0x09 || cp == 0x0A || cp == 0x0D;
        }

        inline std::string utf8_trim(const std::string& str) {
            auto cps = utf8_to_codepoints(str);

            size_t start = 0, end = cps.size();

            while (start < end && is_space(cps[start])) start++;
            while (end > start && is_space(cps[end - 1])) end--;

            return codepoints_to_utf8(
                std::vector<uint32_t>(cps.begin() + start, cps.begin() + end)
            );
        }
    
        inline std::string utf8_reverse(const std::string& str) {
            auto cps = utf8_to_codepoints(str);
            std::reverse(cps.begin(), cps.end());
            return codepoints_to_utf8(cps);
        }




        inline std::vector<std::string> utf8_split(const std::string& str, const std::string& delimiter) {
            auto text = utf8_to_codepoints(str);
            auto del = utf8_to_codepoints(delimiter);

            std::vector<std::string> result;
            std::vector<uint32_t> current;

            for (size_t i = 0; i < text.size();) {
                bool match = true;

                if (i + del.size() <= text.size()) {
                    for (size_t j = 0; j < del.size(); j++) {
                        if (text[i + j] != del[j]) {
                            match = false;
                            break;
                        }
                    }
                }
                else {
                    match = false;
                }

                if (match) {
                    result.push_back(codepoints_to_utf8(current));
                    current.clear();
                    i += del.size();
                }
                else {
                    current.push_back(text[i]);
                    i++;
                }
            }

            result.push_back(codepoints_to_utf8(current));
            return result;
        }



        inline std::string utf8_replace_all(const std::string& str,
            const std::string& from,
            const std::string& to) {
            auto text = utf8_to_codepoints(str);
            auto f = utf8_to_codepoints(from);
            auto t = utf8_to_codepoints(to);

            std::vector<uint32_t> result;

            for (size_t i = 0; i < text.size();) {
                bool match = true;

                if (i + f.size() <= text.size()) {
                    for (size_t j = 0; j < f.size(); j++) {
                        if (text[i + j] != f[j]) {
                            match = false;
                            break;
                        }
                    }
                }
                else {
                    match = false;
                }

                if (match) {
                    result.insert(result.end(), t.begin(), t.end());
                    i += f.size();
                }
                else {
                    result.push_back(text[i]);
                    i++;
                }
            }

            return codepoints_to_utf8(result);
        }


        
        inline size_t utf8_length(const std::string& str) {
            return utf8_to_codepoints(str).size();
        }


        inline bool utf8_contains(const std::string& str, const std::string& sub) {
            auto a = utf8_to_codepoints(str);
            auto b = utf8_to_codepoints(sub);

            if (b.empty()) return true;

            for (size_t i = 0; i + b.size() <= a.size(); i++) {
                bool match = true;
                for (size_t j = 0; j < b.size(); j++) {
                    if (a[i + j] != b[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) return true;
            }
            return false;
        }

        inline bool utf8_starts_with(const std::string& str, const std::string& prefix) {
            auto a = utf8_to_codepoints(str);
            auto b = utf8_to_codepoints(prefix);

            if (b.size() > a.size()) return false;

            for (size_t i = 0; i < b.size(); i++) {
                if (a[i] != b[i]) return false;
            }
            return true;
        }
        
        inline bool utf8_ends_with(const std::string& str, const std::string& suffix) {
            auto a = utf8_to_codepoints(str);
            auto b = utf8_to_codepoints(suffix);

            if (b.size() > a.size()) return false;

            size_t offset = a.size() - b.size();

            for (size_t i = 0; i < b.size(); i++) {
                if (a[offset + i] != b[i]) return false;
            }
            return true;
        }
        
        inline size_t utf8_count(const std::string& str, const std::string& target) {
            auto a = utf8_to_codepoints(str);
            auto b = utf8_to_codepoints(target);

            size_t count = 0;

            for (size_t i = 0; i + b.size() <= a.size(); i++) {
                bool match = true;
                for (size_t j = 0; j < b.size(); j++) {
                    if (a[i + j] != b[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) count++;
            }

            return count;
        }

        inline std::string utf8_join(const std::vector<std::string>& vec,
            const std::string& delimiter) {
            std::string result;

            for (size_t i = 0; i < vec.size(); i++) {
                result += vec[i];

                if (i != vec.size() - 1) {
                    result += delimiter;
                }
            }

            return result;
        }


    }
}