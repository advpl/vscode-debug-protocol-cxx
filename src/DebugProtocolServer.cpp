#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <chrono>
#include <thread>
void run (std::istream &input)
{	 
	
	
	//Se precisar esperar pelo debug
	using namespace boost::algorithm;
	/*using namespace std::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(10s);
    auto end = std::chrono::high_resolution_clock::now();*/
	while (input.good()) {
		// A Debug Protocol message starts with a set of HTTP headers,
		// delimited  by \r\n, and terminated by an empty line (\r\n).
		unsigned long long ContentLength = 0;
		while (input.good()) {
		  std::string Line;
		  std::getline(input, Line);
		  if (!input.good() && errno == EINTR) {
				input.clear();
				continue;
		  }
		  if (starts_with(Line,"Content-Length: ")) {
				Line = erase_head_copy(Line,16);
				ContentLength = boost::lexical_cast<long>(Line.data());
				continue;
		  }

		}
	}
}
int main()
{
	run(std::cin);
}