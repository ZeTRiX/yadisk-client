#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <string>
#include <list>
#include <map>

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include "url/path.hpp"

namespace yadisk
{
    class Client
    {
    public:

        Client(std::string token);

        auto ping() -> bool;

        auto info() -> json;

        auto info(const url::path& resource, const std::map<std::string, std::string>& options = {}) -> json;

        auto list(const std::map<std::string, std::string>& options = {}) -> json;

        auto upload(const url::path& to, const fs::path& from, bool overwrite, const std::list<std::string>& fields = {}) -> json;

        auto upload(const url::path& to, const std::string& url, const std::list<std::string>& fields = {}) -> json;

        auto download(const url::path& from, const url::path& to, const std::list<std::string>& fields = {}) -> json;

        auto copy(const url::path& from, const url::path& to, bool overwrite, const std::list<std::string>& fields = {}) -> json;

        auto move(const url::path& from, const url::path& to, bool overwrite = false, const std::list<std::string>& fields = {}) -> json;

        auto mkdir(const url::path& dir, const std::list<std::string>& fields = {}) -> json;

        auto remove(const url::path& resource, bool permanently, const std::list<std::string>& fields = {}) -> json;

        auto publish(const url::path& resource) -> json;

        auto unpublish(const url::path& resource) -> json;

        auto patch(const url::path& resource, const json& meta, const std::list<std::string>& fields = {}) -> json;

        auto info(const std::string& public_key, const url::path& resource = nullptr, const std::map<std::string, std::string>& options = {}) -> json;
      
        auto download(const std::string& public_key, const fs::path& to, const url::path& file = nullptr)-> json;
      
        auto save(const std::string& public_key, const std::string& name, const url::path& file = nullptr)-> json;

        auto status(const std::string& id) -> json;
        
        std::string token;
    };

}
