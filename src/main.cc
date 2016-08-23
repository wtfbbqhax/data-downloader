#include <iostream>
#include <fstream>
#include <vector>

#include "restclient/restclient.h"
using namespace std;

int main(int argc, char *argv[])
{
    string baseuri = "https://github.com/wtfbbqhax/tremulous-data/raw/master/";
    vector<string> files = { 
        "data-gpp1.pk3",
        "data-1.1.0.pk3",
        "map-atcs-1.1.0.pk3",
        "map-karith-1.1.0.pk3",
        "map-nexus6-1.1.0.pk3",
        "map-niveus-1.1.0.pk3",
        "map-transit-1.1.0.pk3",
        "map-tremor-1.1.0.pk3",
        "map-uncreation-1.1.0.pk3"
    };

    for (auto f : files )
    {
        cout << "Get " << f << endl;
        RestClient::Response res = RestClient::get(baseuri + f);

        cout << "Status: " << res.code << endl;
        cout << "Opening: " << f << endl;
        ofstream logo;
        logo.open(f);
        logo << res.body;
        logo.close();
    }

    return 0;
}
