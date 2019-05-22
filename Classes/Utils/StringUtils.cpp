

#include "StringUtils.h"

namespace dsj {
    using namespace std;
    
    bool StringUtils::endsWith(const string& s, const string& suffix)
    {
        return s.rfind(suffix) == (s.size()-suffix.size());
    }
    bool StringUtils::startsWith(const string& s, const string& prefix)
    {
        if ( s.length() < prefix.length() )
        {
            return false;
        }
        string front = s.substr(0,prefix.length());
        if ( front == prefix)
        {
            return true;
        }
        return false;
    }
    bool StringUtils::contains(const string& s, const string& key)
    {
        unsigned found = s.rfind(key);
        bool ret = ( found != std::string::npos );
        return ret;
    }
    string StringUtils::replaceAllSubstrings( string src, string const& target, string const& repl)
    {
        // handle error situations/trivial cases
        
        if (target.length() == 0)
        {
            // searching for a match to the empty string will result in
            //  an infinite loop
            //  it might make sense to throw an exception for this case
            return src;
        }
        
        if (src.length() == 0)
        {
            return src;  // nothing to match against
        }
        
        size_t idx = 0;
        
        for (;;)
        {
            idx = src.find( target, idx);
            if (idx == string::npos)  break;
            
            src.replace( idx, target.length(), repl);
            idx += repl.length();
        }
        
        return src;
    }
    
    void StringUtils::split(vector<string> &result, string str, char delim )
    {
        string tmp;
        string::iterator i;
        result.clear();
        
        for(i = str.begin(); i <= str.end(); ++i)
        {
            if((const char)*i != delim  && i != str.end())
            {
                tmp += *i;
            }
            else
            {
                result.push_back(tmp);
                tmp = "";
            }
        }
    }
    
    string StringUtils::trim(string s)
    {
        char const *str = s.c_str();
        // Trim leading non-letters
        while(! StringUtils::isWhiteSpaceChar(*str))
        {
            str++;
        }
        // Trim trailing non-letters
        char const * end =(char const *) (str + s.length() - 1);
        while(end > str && !StringUtils::isWhiteSpaceChar(*end))
        {
            end--;
        }
        
        return string(str, end+1);
    }
    
    bool StringUtils::isWhiteSpaceChar(const char c)
    {
        bool ret = false;
        if (c==' ' || c=='\n' || c=='\t')
        {
            ret = true;
        }
        return ret;
    }


    std::vector<std::string> StringUtils::split(const char *str,  char c)
    {
        std::vector<std::string> result;
        do {
            const char *begin = str;
            while(*str != c && *str) str++;
            result.push_back(std::string(begin, str));
        } while (0 != *str++);
        return result;
    }

    bool StringUtils::stob(std::string s, bool throw_on_error )
    {
        auto result = false;    // failure to assert is false

        std::istringstream is(s);
        // first try simple integer conversion
        is >> result;

        if (is.fail())
        {
            // simple integer failed; try boolean
            is.clear();
            is >> std::boolalpha >> result;
        }

        if (is.fail() && throw_on_error)
        {
            throw std::invalid_argument(s.append(" is not convertable to bool"));
        }

        return result;
    }
}
