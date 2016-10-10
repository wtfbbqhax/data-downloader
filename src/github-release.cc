#include <iostream>
#include <fstream>
#include <vector>

#include "restclient/restclient.h"
#include "restclient/connection.h"
#include "cJSON/cJSON.h"
using namespace std;

constexpr char url[] =
   "https://api.github.com/repos/wtfbbqhax/tremulous/releases";

struct Asset
{
    Asset(string n, string u, string b)
        : name(n), url(u), browser_download_url(b)
    {
        cout << "\t" << browser_download_url << '\n';
    }

private:
    string name, url, browser_download_url;
};

struct Release
{
    Release(string t, string u, int d, bool pre, string ct, string pt)
        : tag_name(t), url(u), draft(d), prerelease(pre),
          created_at(ct), published_at(pt)
    {
        cout << "Release " << tag_name << '\n';
        cout << "Release Date " << published_at << '\n';
        cout << (prerelease ? "Prerelease" : "Stable") << '\n';
    }


    void push(cJSON *j)
    {
        const int max = cJSON_GetArraySize(j);
        for( int i = 0; i < max; ++i )
        {
            cJSON *o = cJSON_GetArrayItem(j, i);
            assets.emplace_back(
                cJSON_GetObjectItem(o, "name")->valuestring,
                cJSON_GetObjectItem(o, "url")->valuestring,
                cJSON_GetObjectItem(o, "browser_download_url")->valuestring 
            );
        }
    }

private:
    int draft;
    bool prerelease;
    string tag_name, url, created_at, published_at;
    vector<Asset> assets;
};

struct Github_Releases {
    Github_Releases(std::string text)
    {
        cJSON *j = cJSON_Parse(text.c_str());
        const int max = cJSON_GetArraySize(j);
        for (int i = 0; i < max; ++i)
        {
            cJSON *o = cJSON_GetArrayItem(j, i);
            Release r( cJSON_GetObjectItem(o, "tag_name")->valuestring,
                       cJSON_GetObjectItem(o, "url")->valuestring,
                       cJSON_GetObjectItem(o, "draft")->valueint,
                       cJSON_GetObjectItem(o, "prerelease")->valueint,
                       cJSON_GetObjectItem(o, "created_at")->valuestring,
                       cJSON_GetObjectItem(o, "published_at")->valuestring );

            r.push(cJSON_GetObjectItem(o, "assets"));
        }
    }
private:
    std::vector<Release> releases;
};

#include <exception>
class GithubException : public std::exception {
    public: virtual const char* what() { return "Failed to get release list from Github"; }
};

int main(int argc, char *argv[])
{
    RestClient::Response r = RestClient::get(url);
    if ( r.code != 200 )
        throw GithubException();

    Github_Releases(r.body);

    return 0;
}
