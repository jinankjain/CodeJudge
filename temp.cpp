#include <bits/stdc++.h>
#include <unistd.h>
#include "dist/json/json.h"

using namesapace std;
int main(){
	Json::Value fromScratch;
	Json::Value array;
	array.append("hello");
	array.append("world");
	fromScratch["hello"] = "world";
	fromScratch["number"] = 2;
	fromScratch["array"] = array;
	fromScratch["object"]["hello"] = "world";

	output(fromScratch);

	// write in a nice readible way
	Json::StyledWriter styledWriter;
	std::cout << styledWriter.write(fromScratch);

}