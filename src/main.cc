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
        //cout << "\t" << name << ',' << url << ',' << browser_download_url << '\n';
        cout << "\t" << browser_download_url << '\n';
    }

private:
    string name, url, browser_download_url;
};

struct Release
{
    Release(string t, string u, int d)
        : tag_name(t), url(u), draft(d)
    {
        //cout << tag_name << ',' << url << ',' << draft << '\n';
        cout << tag_name << '\n';
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
    string tag_name, url;
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
                       cJSON_GetObjectItem(o, "draft")->valueint );

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
    /*
     *(
[{
                "url":  "https://api.github.com/repos/wtfbbqhax/tremulous/releases/4097271",
                "assets_url":   "https://api.github.com/repos/wtfbbqhax/tremulous/releases/4097271/assets",
                "upload_url":   "https://uploads.github.com/repos/wtfbbqhax/tremulous/releases/4097271/assets{?name,label}",
                "html_url":     "https://github.com/wtfbbqhax/tremulous/releases/tag/lua-build-2",
                "id":   4097271,
                "tag_name":     "lua-build-2",
                "target_commitish":     "master",
                "name": null,
                "draft":        false,
                "author":       {
                        "login":        "wtfbbqhax",
                        "id":   7323455,
                        "avatar_url":   "https://avatars.githubusercontent.com/u/7323455?v=3",
                        "gravatar_id":  "",
                        "url":  "https://api.github.com/users/wtfbbqhax",
                        "html_url":     "https://github.com/wtfbbqhax",
                        "followers_url":        "https://api.github.com/users/wtfbbqhax/followers",
                        "following_url":        "https://api.github.com/users/wtfbbqhax/following{/other_user}",
                        "gists_url":    "https://api.github.com/users/wtfbbqhax/gists{/gist_id}",
                        "starred_url":  "https://api.github.com/users/wtfbbqhax/starred{/owner}{/repo}",
                        "subscriptions_url":    "https://api.github.com/users/wtfbbqhax/subscriptions",
                        "organizations_url":    "https://api.github.com/users/wtfbbqhax/orgs",
                        "repos_url":    "https://api.github.com/users/wtfbbqhax/repos",
                        "events_url":   "https://api.github.com/users/wtfbbqhax/events{/privacy}",
                        "received_events_url":  "https://api.github.com/users/wtfbbqhax/received_events",
                        "type": "User",
                        "site_admin":   false
                },
                "prerelease":   false,
                "created_at":   "2016-09-10T18:25:06Z",
                "published_at": "2016-09-10T18:33:49Z",
                "assets":       [{
                                "url":  "https://api.github.com/repos/wtfbbqhax/tremulous/releases/assets/2289433",
                                "id":   2289433,
                                "name": "release-darwin-x86_64.zip",
                                "label":        "",
                                "uploader":     {
                                        "login":        "wtfbbqhax",
                                        "id":   7323455,
                                        "avatar_url":   "https://avatars.githubusercontent.com/u/7323455?v=3",
                                        "gravatar_id":  "",
                                        "url":  "https://api.github.com/users/wtfbbqhax",
                                        "html_url":     "https://github.com/wtfbbqhax",
                                        "followers_url":        "https://api.github.com/users/wtfbbqhax/followers",
                                        "following_url":        "https://api.github.com/users/wtfbbqhax/following{/other_user}",
                                        "gists_url":    "https://api.github.com/users/wtfbbqhax/gists{/gist_id}",
                                        "starred_url":  "https://api.github.com/users/wtfbbqhax/starred{/owner}{/repo}",
                                        "subscriptions_url":    "https://api.github.com/users/wtfbbqhax/subscriptions",
                                        "organizations_url":    "https://api.github.com/users/wtfbbqhax/orgs",
                                        "repos_url":    "https://api.github.com/users/wtfbbqhax/repos",
                                        "events_url":   "https://api.github.com/users/wtfbbqhax/events{/privacy}",
                                        "received_events_url":  "https://api.github.com/users/wtfbbqhax/received_events",
                                        "type": "User",
                                        "site_admin":   false
                                },
                                "content_type": "application/zip",
                                "state":        "uploaded",
                                "size": 4173256,
                                "download_count":       0,
                                "created_at":   "2016-09-10T18:33:48Z",
                                "updated_at":   "2016-09-10T18:33:49Z",
                                "browser_download_url": "https://github.com/wtfbbqhax/tremulous/releases/download/lua-build-2/release-darwin-x86_64.zip"
*/

    return 0;
}
