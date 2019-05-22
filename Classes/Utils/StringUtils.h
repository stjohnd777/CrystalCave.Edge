#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 @brief Basic protable string utils
 */

namespace dsj {
    
    class StringUtils{
        
    public:
        /**
         End with suffix
         */
        static bool endsWith(const std::string& s, const std::string& suffix);
        /**
         Start with suffix
         */
        static bool startsWith(const std::string& s, const std::string& suffix);
        /**
         String s contains key
         */
        static bool contains(const std::string& s, const std::string& key);
        /**
         Replace all instances of target with repl in src
         */
        static std::string replaceAllSubstrings( std::string src, std::string const& target, std::string const& repl);
        /**
         Split
         */
        static void split(std::vector<std::string> &result, std::string str, char delim ) ;
        /**
         Trim
         */
        static std::string trim(std::string s);
        /**
         Is white space
         */
        static bool isWhiteSpaceChar(const char c);

        static std::vector<std::string> split(const char *str,  char c = ' ');

        static bool stob(std::string s, bool throw_on_error = true);
    };
}

