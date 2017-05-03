#include <curl/curl.h>

#include <url/params.hpp>
#include <yadisk/client.hpp>
#include <boost/algorithm/string/join.hpp>

#include <algorithm>
#include <sstream>
using std::stringstream;

#include "callbacks.hpp"
#include "quote.hpp"

namespace yadisk
{
	static const std::string api_url = "https://cloud-api.yandex.net/v1/disk";

	Client::Client(std::string token_) : token{token_} {}

    auto Client::info() -> json {
        
        auto curl = curl_easy_init();
        if (!curl) return json{};

        std::string url = api_url + "/";

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		stringstream response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json();

		auto response_data = json::parse(response);
		return response_data;
    }

    auto Client::info(const url::path& resource, const std::map<std::string, std::string>& options) -> json {
        
        auto curl = curl_easy_init();
        if (!curl) return json{};

		url::params_t url_params;
		url_params["path"] = quote(resource.string(), curl);
        for(const auto& item : options) {
            url_params[item.first] = item.second;
        }
    
        std::string url = api_url + "/resources" + "?" + url_params.string();

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		stringstream response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json{};

		auto response_data = json::parse(response);
		return response_data;
    }

    auto Client::status(const std::string& id) -> json {

        auto curl = curl_easy_init();
        if (!curl) return json{};

        std::string url = api_url + "/operations/" + id;

        struct curl_slist *header_list = nullptr;
        std::string auth_header = "Authorization: OAuth " + token;
        header_list = curl_slist_append(header_list, auth_header.c_str());

        stringstream response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

        auto response_code = curl_easy_perform(curl);

        curl_slist_free_all(header_list);
        curl_easy_cleanup(curl);

        if (response_code != CURLE_OK) return json{};

        auto response_data = json::parse(response);
        return response_data;
    }

    auto Client::remove(const url::path& resource, bool permanently, const std::list<std::string>& fields) -> json {

        auto curl = curl_easy_init();
        if (!curl) return json{};

		url::params_t url_params;
		url_params["path"] = quote(resource.string(), curl);
		url_params["permanently"] = permanently ? "true" : "false";
		url_params["fields"] = boost::algorithm::join(fields, ",");

        std::string url = api_url + "/resources" + "?" + url_params.string();

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		stringstream response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

        long http_response_code = 0;
        if (response_code == CURLE_OK) {
            response_code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_response_code);
            if (http_response_code == 204) return json{};
        }

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json();

		auto response_data = json::parse(response);
		return response_data;
    }

    auto Client::publish(const url::path& resource) -> json {

        auto curl = curl_easy_init();
        if (!curl) return json{};

		url::params_t url_params;
		url_params["path"] = quote(resource.string(), curl);

        std::string url = api_url + "/resources/publish" + "?" + url_params.string();

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		stringstream response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json{};

		auto response_data = json::parse(response);
		return response_data;
    }

    auto Client::unpublish(const url::path& resource) -> json {

        auto curl = curl_easy_init();
        if (!curl) return json{};

		url::params_t url_params;
		url_params["path"] = quote(resource.string(), curl);

        std::string url = api_url + "/resources/unpublish" + "?" + url_params.string();

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		stringstream response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json{};

		auto response_data = json::parse(response);
		return response_data;
    }

    auto Client::save(const std::string& public_key, const std::string& name,  const url::path& resource) -> json {

        auto curl = curl_easy_init();
        if (!curl) return json{};

		url::params_t url_params;
        url_params["public_key"] = public_key;
        url_params["name"] = name;
        if (resource.string() != "") {
            url_params["path"] = quote(resource.string(), curl);
        }

        std::string url = api_url + "/public/resources/save-to-disk/" + "?" + url_params.string();

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		stringstream response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json();

		auto response_data = json::parse(response);
		return response_data;
    }

	auto Client::ping() -> bool {

		CURL * curl = curl_easy_init();
		if (curl == nullptr) return false;

		std::string url = api_url;

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);
		
		long http_response_code = 0;
		if (response_code == CURLE_OK) {
			response_code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_response_code);			
		}	
		
		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return false;

		return http_response_code == 200;
	}

	auto Client::move(const url::path& from, const url::path& to, bool overwrite, const std::list<std::string>& fields) -> json {

		CURL * curl = curl_easy_init();
		if (!curl) return json{};

		url::params_t url_params;
		url_params["from"] = quote(from.string(), curl);
		url_params["path"] = quote(to.string(), curl);
		url_params["overwrite"] = overwrite ?  "true" : "false";
		url_params["fields"] = boost::algorithm::join(fields, ",");
		std::string url = api_url + "/resources/move" + "?" + url_params.string();

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		stringstream response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json{};

		auto response_data = json::parse(response);
		return response_data;
	}

	auto Client::copy(const url::path& from, const url::path& to, bool overwrite, const std::list<std::string>& fields) -> json {

		CURL * curl = curl_easy_init();
		if (!curl) return json{};

		url::params_t url_params;
		url_params["from"] = quote(from.string(), curl);
		url_params["path"] = quote(to.string(), curl);
		url_params["overwrite"] = overwrite ? "true" : "false";
		url_params["fields"] = boost::algorithm::join(fields, ",");
		std::string url = api_url + "/resources/copy" + "?" + url_params.string();

		struct curl_slist *header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, auth_header.c_str());

		stringstream response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if (response_code != CURLE_OK) return json{};

		auto response_data = json::parse(response);
		return response_data;
	}
    
	auto Client::patch(const url::path& resource, const json& meta, const std::list<std::string>& fields) -> json {

		CURL * curl = curl_easy_init();
		if (curl == nullptr) return json{};

		url::params_t url_params;
		url_params["fields"] = boost::algorithm::join(fields, ",");
		url_params["path"] = quote(resource.string(), curl);
		std::string url = api_url + "/resources" + "?" + url_params.string();

		curl_slist * header_list = nullptr;
		std::string auth_header = "Authorization: OAuth " + token;
		header_list = curl_slist_append(header_list, "Content-Type: application/json");
		header_list = curl_slist_append(header_list, auth_header.c_str());

		auto request_body = meta.dump();

		stringstream response_body;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_body.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request_body.size());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		auto response_code = curl_easy_perform(curl);

		curl_slist_free_all(header_list);
		curl_easy_cleanup(curl);

		if ( response_code != CURLE_OK ) return json{};

		auto info = json::parse(response_body);
		return info;
	}

    auto Client::mkdir(const url::path& dir, const std::list<std::string>& fields) -> json {

        auto curl = curl_easy_init();
        if (!curl) return json{};

        url::params_t url_params;
        url_params["path"] = quote(dir.string(), curl);
        url_params["fields"] = boost::algorithm::join(fields, ",");

        std::string url = api_url + "/resources/" + "?" + url_params.string();

        struct curl_slist *header_list = nullptr;
        std::string auth_header = "Authorization: OAuth " + token;
        header_list = curl_slist_append(header_list, auth_header.c_str());

        stringstream response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write<stringstream>);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

        auto response_code = curl_easy_perform(curl);

        curl_slist_free_all(header_list);
        curl_easy_cleanup(curl);

        if (response_code != CURLE_OK) return json{};

        auto response_data = json::parse(response);
        return response_data;
    }
}

class curl_environment {
public:
    curl_environment() {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    ~curl_environment() {
        curl_global_cleanup();
    }
};

static const curl_environment env;
