#ifndef LINUX
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include <CppStructz/containers/advmap.hxx>
void makeIntIntMap( std::multimap<int, int> &tree );
void makeStringIntMap( std::multimap<std::string, int> &tree );

class Foo {
public:
    Foo() { Key = 0; }

    Foo(int key) { Key = key; }

    void addChild(Foo& child) { children.push_back(child); }

    int Key;
    std::list<Foo> children;
};

template<class T>
void toStdOut (T i) {
    std::cout << " " << i;
}

typedef std::vector<int> Keylist;

void domap() {
    std::cout << __FUNCTION__ << "| " << "" << " called" << std::endl;

    AdvMap<int, int> testmap;
    makeIntIntMap(testmap);
    AdvMap<int, int>::Keylist mkeys = testmap.getKeys();
    std::cout << "mkeys contains:";
    for_each (mkeys.begin(), mkeys.end(), toStdOut<int>);
    std::cout << std::endl;

    typedef AdvMap<std::string, int> Dictionary;
    Dictionary dict;
    makeStringIntMap(dict);
    Dictionary::Keylist dictkeys = dict.getKeys();
    std::cout << "dictkeys contains:";
    for_each (dictkeys.begin(), dictkeys.end(), toStdOut<std::string>);
    std::cout << std::endl;

    //key_begin(tree);

    //std::map<std::string, int> kackveck;
    /*kackveck.push_back(5);
       kackveck.push_back(15);
       kackveck.push_back(10);*/

    std::multimap<int, int> kackveck;
    makeIntIntMap(kackveck);

    //std::multimap<int, int>::iterator::iterator_category b;
    //key_iterator<std::multimap<int, int>> moep(kackveck);
    //std::multimap<int, int>::iterator keys = kackveck.begin();

    //key_begin(kackveck);

    //int rotz = std::accumulate(tree.begin(),tree.cend(), 0 );
    int rotz = std::accumulate( key_begin(kackveck), key_end(kackveck), 0 );

    Keylist& keys = getKeys(kackveck);

    // http://www.cplusplus.com/reference/algorithm/for_each/
    std::cout << "myvector contains:";
    for_each (keys.begin(), keys.end(), toStdOut<int>);
    std::cout << std::endl;

    std::map<int, Foo> tree;
    tree[1] = Foo(1);
    tree[2] = Foo(2);
    tree[2] = Foo(3);
    tree[3] = Foo(4);
    tree[4] = Foo(5);
    tree[5] = Foo(14);

    for (unsigned int i = 0; i <= tree.size(); i++) {
        std::map<int, Foo>::iterator iter = tree.find(i);

        if ( iter != tree.end() )
            std::cout << "You typed '" << iter->first << "' " << iter->second.Key << " time(s)" <<
            std::endl;
    }
} // domap

void domultimap() {
    std::cout << __FUNCTION__ << "| " << "" << " called" << std::endl;
    std::multimap<int, Foo> tree;
    tree.insert( std::pair<int, Foo>( 1, Foo(1) ) );
    tree.insert( std::pair<int, Foo>( 2, Foo(2) ) );
    tree.insert( std::pair<int, Foo>( 2, Foo(3) ) );
    tree.insert( std::pair<int, Foo>( 3, Foo(4) ) );
    tree.insert( std::pair<int, Foo>( 4, Foo(2) ) );
    tree.insert( std::pair<int, Foo>( 5, Foo(14) ) );

    for (unsigned int i = 0; i <= tree.size(); i++) {
        std::multimap<int, Foo>::iterator iter = tree.find(i);

        if ( iter != tree.end() )
            std::cout << "You typed '" << iter->first << "' " << iter->second.Key << " time(s)" <<
            std::endl;
    }
} // domultimap

void makeIntIntMap( std::multimap<int, int> &tree )
{
    tree.insert( std::make_pair(1, 1) );
    tree.insert( std::make_pair(2, 2) );
    tree.insert( std::make_pair(2, 3) );
    tree.insert( std::make_pair(3, 4) );
    tree.insert( std::make_pair(8, 4) );
    tree.insert( std::make_pair(4, 2) );
    tree.insert( std::make_pair(5, 14) );

    tree.insert( std::make_pair(2, 3) );
    tree.insert( std::make_pair(3, 24) );
    tree.insert( std::make_pair(2, 3) );
    tree.insert( std::make_pair(4, 33) );
    tree.insert( std::make_pair(22, 3) );
}

void makeStringIntMap( std::multimap<std::string, int> &tree )
{
    tree.insert( std::make_pair("Nr 1", 1) );
    tree.insert( std::make_pair("Nr 2", 2) );
    tree.insert( std::make_pair("Nr 2", 3) );
    tree.insert( std::make_pair("Nr 3", 4) );
    tree.insert( std::make_pair("Nr 8", 4) );
    tree.insert( std::make_pair("Nr 4", 2) );
    tree.insert( std::make_pair("Nr 5", 14) );

    tree.insert( std::make_pair("Nr 2", 3) );
    tree.insert( std::make_pair("Nr 3", 24) );
    tree.insert( std::make_pair("Nr 2", 3) );
    tree.insert( std::make_pair("Nr 4", 33) );
    tree.insert( std::make_pair("Nr 424", 3) );
}

void domultimap2() {
    std::cout << __FUNCTION__ << "| " << "" << " called" << std::endl;
    std::multimap<int, int> tree;
    makeIntIntMap(tree);

    std::cout << "Employee list: " << std::endl;

    for (std::multimap<int, int>::iterator iter = tree.begin(); iter != tree.end(); ++iter)
        std::cout << " Name: " << iter->first << ", ID #" << iter->second << std::endl;std::cout << std::endl;

    std::cout << "Find stuff: " << std::endl;

    for (unsigned int i = 0; i <= tree.size(); i++) {
        std::cout << "I[" << i << "]" << std::endl;
        std::multimap<int, int>::iterator iter = tree.find(i);

        while (iter != tree.end() && iter->first == i) {
            std::cout << " X You typed '" << iter->first << "' " << iter->second << " time(s)" << std::endl;
            iter++;
        }
    }
    // See http://www.cplusplus.com/reference/stl/multimap/equal_range/
    std::pair<std::multimap<int, int>::iterator, std::multimap<int, int>::iterator> ret;
    std::multimap<int, int>::iterator it;
    std::multimap<int, int>::iterator allkeys;
    std::multimap<int, int>::key_compare mycomp;

    std::cout << std::endl;
    std::cout << "Find stuff: " << std::endl;

    int highest = tree.rbegin()->first;     // key value of last element
    allkeys = tree.begin();

    int mapiterations = 0;

    for (int i = (*allkeys).first; i <= highest;  i++) {
        mapiterations++;

        //do {
        //     int i = (*allkeys).first;
        ret = tree.equal_range(i);

        if( ret.second == tree.end() ||  ret.second == tree.begin() )
        {
            std::cout << "...Skipping..." << std::endl;
            continue;
        }
        std::cout << "I[" << i << "] Key: " << (*ret.second).first << std::endl;

        for (it = ret.first; it != ret.second; ++it) {
            mapiterations++;
            std::cout << "  You typed '" << (*it).first << "' " << (*it).second << " time(s)" << std::endl;
        }
    }
    //while (mycomp((*allkeys++).first, highest));

    std::set<int> mykeys;
    keys(tree, mykeys);

    std::cout << "XXXXXXXXXXXXX    mapiterations = " << mapiterations << std::endl;
} // domultimap2

void domultimap3()
{
    // See http://stackoverflow.com/questions/247818/stlmultimap-how-do-i-get-groups-of-data

    typedef std::multimap< std::string, int> StringToIntMap;
    typedef StringToIntMap::iterator mapIter;

    StringToIntMap mymap;

    /*mymap.insert(std::make_pair("Group2", 11));
       mymap.insert(std::make_pair("Group1",  3));
       mymap.insert(std::make_pair("Group2", 10));
       mymap.insert(std::make_pair("Group1",  1));
       mymap.insert(std::make_pair("Group2", 12));
       mymap.insert(std::make_pair("Group1",  2));*/
    makeStringIntMap(mymap);

    std::cout << "mymap contains:" << std::endl;

    mapIter m_it, s_it;

    int mapiterations = 0;

    for (m_it = mymap.begin();  m_it != mymap.end();  m_it = s_it)
    {
        mapiterations++;
        std::string theKey = (*m_it).first;

        std::cout << std::endl;
        std::cout << "  key = '" << theKey << "'" << std::endl;

        std::pair<mapIter, mapIter> keyRange = mymap.equal_range(theKey);

        // Iterate over all map elements with key == theKey

        for (s_it = keyRange.first;  s_it != keyRange.second;  ++s_it)
        {
            mapiterations++;
            std::cout << "    value = " << (*s_it).second << std::endl;
        }
    }
    std::cout << "XXXXXXXXXXXXX    mapiterations = " << mapiterations << std::endl;

    std::vector<std::string> &keys = getKeys(mymap);
    std::cout << "mymap contains:";
    for_each (keys.begin(), keys.end(), toStdOut<std::string>);
    std::cout << std::endl;
} // domultimap3

int main(int ac, char* av[]) {
    domap();
    domultimap();
    domultimap2();
    domultimap3();

    return 0;
    const int SIZE = 10;
    int a1[ SIZE ] = { 1, 3, 5, 7, 9, 1, 3, 5, 7, 9 };
    std::vector< int > v1( a1, a1 + SIZE ); // copy of a
    std::ostream_iterator< int > output( std::cout, " " );

    std::cout << "Vector v1 contains: ";
    std::copy( v1.begin(), v1.end(), output );

    std::vector< int > results1;

    std::unique_copy( v1.begin(), v1.end(), std::back_inserter( results1 ) );
    std::cout << "\nAfter unique_copy results1 contains: ";
    std::copy( results1.begin(), results1.end(), output );

    //std::cout <<  << std::endl;
} // main
#else
int main(int ac, char* av[]) {
} // main
#endif // ifndef LINUX

