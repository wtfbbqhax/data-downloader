#include <iostream>
#include <fstream>
#include <vector>

#include <memory>
#include <iostream>
#include <map>
#include <typeinfo>
template <typename Key, typename Value>
class Tree
{ 
    using _Tree = std::map<Key, Tree>;

  public:
    auto& operator= (const Value& value)
    {
        _value = value;
        return *this;
    }

    auto operator[] (const std::string& key)
    { 
        return _value;
    }


    Tree&& operator[] (const std::string&& key)
    { 
        _str = key;
        return std::move(_children[key]);
    }

    auto begin() const
    {
        return _children.cbegin();
    }

    auto end() const
    {
        return _children.cend();
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree& tree)
    {
        int o = 4;
        if ( tree._children.empty() )
        {
            os <<  tree._value << ", "; 
            return os;
        }
        else if ( not tree._value.empty() )
        {
            os << ',';
        }
        else
        {
            os << ' ';
        }

        for ( auto&& i : tree._children )
        {
            //os << std::string(o, ' ');
            if ( not i.second._children.empty() )
                os << i.first <<  ": " << i.second; 

            o += 4;
        }

        o += 4;
        os << std::endl;

        return os;
    }

  private:
    Value _value;
    std::string _str;
    _Tree _children;
};

using Tre = Tree<std::string, std::string>;

int main(int argc, char *argv[])
{
    Tre a;
    
    a["Name"] = "Victor";

    auto w = "Earth";
    a["Location"] = w;

    a = "";
    a["offspring"]["1"]["Name"] = "Bob";
    a["offspring"]["1"]["Location"] = "Mars";

    a["offspring"]["2"]["Name"] = "Sarah";
    a["offspring"]["2"]["Location"] = "Venus";

    std::cout << a << "\n";
    return 0;
}

#if 0
template <typename Key, typename Value>
struct Tree
{
    using Child = std::map<Key, Tree>;

    Tree& operator= (const Value&& _value)
    { value = value;
      return *this; }

    Tree& operator[] (const Key&& key)
    { return child[key]; }

    friend std::ostream& operator<<(std::ostream& os, const Tree& tree)
    {
        os << tree.value << " { ";
        for ( auto&& i : tree.child )
            os << i.first << " -> " << i.second << " | ";
        return os << '}';
    }

//private:
    Child child;
    Value value;

};

int main()
{

//    Tree<int, std::string> t;
//    t[1].child[1] = "One";
//    t[1].child[2] = "Two";
//    t[1].child[3] = "Three";
//    t[1] = "Arbitrary Key }";
//    std::cout << t << '\n';
}
#endif

#if 0
#include "restclient/restclient.h"
#include "restclient/connection.h"
#include "cJSON/cJSON.h"
using namespace std;

constexpr char url[] =
   "https://api.github.com/repos/wtfbbqhax/tremulous/releases";

#include <exception>
class HttpStatus : public std::exception {
    public: virtual const char* what() { return "Http status code != 200"; }
};

int main(int argc, char *argv[])
{
    RestClient::Response r = RestClient::get(url);
    if ( r.code != 200 )
        throw HttpStatus();

    Tree<std::string, > json;

    return 0;
}
#endif
