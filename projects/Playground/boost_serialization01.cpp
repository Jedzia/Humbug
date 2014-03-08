#include <boost/cstdint.hpp>
//#include <stdint.h>
#include <iostream>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
 
int main()
{
	boost::uint16_t data[] = {1234, 5678};
    char* dataPtr = (char*)&data;
 
    typedef boost::iostreams::basic_array_source<char> Device;
    boost::iostreams::stream_buffer<Device> buffer(dataPtr, sizeof(data));
    boost::archive::binary_iarchive archive(buffer, boost::archive::no_header);
 
    boost::uint16_t word1, word2;
    archive >> word1 >> word2;
    std::cout << word1 << "," << word2 << std::endl;
    return 0;
}
