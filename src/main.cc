#include <iostream>
#include <fstream>
#include <vector>

#include "restclient/restclient.h"
#include "restclient/connection.h"

#include "rapidjson/document.h"

#include "platform.h"

using namespace std;

constexpr auto url =
   "https://api.github.com/repos/wtfbbqhax/tremulous/releases";

int main(int argc, char *argv[])
{
    RestClient::Response r = RestClient::get(url);

    if ( r.code != 200 )
        throw exception();

    //std::cout << r.body << '\n';

    rapidjson::Document d;
    d.Parse( r.body.c_str() );
	//assert( d.IsArray() );

    rapidjson::Value &release = d[0];
    rapidjson::Value &assets = release["assets"];
    for ( rapidjson::SizeType i = 0; i < assets.Size(); ++i )
    {
        auto &a = assets[i];
        std::string name = a["name"].GetString();

        if ( name == package_name )
        {
            std::string url = a["browser_download_url"].GetString();
            auto r = RestClient::get(url);

            if ( r.code != 200 )
                throw exception();

            std::fstream dl;
            dl.open( package_name, fstream::out|ios::binary );
            dl.write( r.body.c_str(), r.body.length() );
            dl.close();
        }

    }

    return 0;
}
