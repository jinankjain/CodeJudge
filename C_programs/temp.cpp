#include <bits/stdc++.h>
#include <unistd.h>
#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"

using namespace std;
int main(){
	Json::Value fromScratch;
	Json::Value array;
	array.append("hello");
	array.append("world");
	fromScratch["hello"] = "world";
	fromScratch["number"] = 2;
	fromScratch["array"] = array;
	fromScratch["object"]["hello"] = "world";

	// output(fromScratch);

	// write in a nice readible way
	Json::StyledWriter styledWriter;
	std::cout << styledWriter.write(fromScratch);

	Json::FastWriter fastWriter;
	std::string output = fastWriter.write(fromScratch);
	cout << "Output : " << endl << output << endl;


	Json::Value root;   
    Json::Reader reader;

    bool parsingSuccessful = reader.parse( output.c_str(), root );     //parse process
        if ( !parsingSuccessful )
        {
            std::cout  << "Failed to parse"
                   << reader.getFormattedErrorMessages();
            return 0;
        }
        std::cout << root.get("hello", "A Default Value if not exists" ).asString() << std::endl;

    return 0;
}