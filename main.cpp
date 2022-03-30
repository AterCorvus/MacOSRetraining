#include <iostream>
#include <memory>
#include <string>
#include <locale>
#include <codecvt>

#include <google/protobuf/util/json_util.h>
#include "Version.pb.h"
#include "cpprest/http_listener.h"
#include "cpprest/json.h"

using namespace std;

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace utility;
using namespace google::protobuf::util;

struct Version{
    static const int major = 1;
    static const int minor = 0;
    static const int patch = 0;
};

void start_server() {
    auto version = make_shared<product_info::Version>();
    version->set_major(Version::major);
    version->set_minor(Version::minor);
    version->set_patch(Version::patch);

    http_listener listener(U("http://127.0.0.1:35248/version"));

    listener.support(methods::GET, [weak_product = weak_ptr<product_info::Version>(version)](http_request request) {
        auto version = weak_product.lock();
        if (version) {
            string response;
            JsonPrintOptions options;
            options.add_whitespace = true;
            options.always_print_primitive_fields = true;
            options.preserve_proto_field_names = true;
            MessageToJsonString(*version, &response, options);
            request.reply(status_codes::OK, response);
        }
        else {
            request.reply(status_codes::InternalError);
        }
        });

    try
    {
        listener
            .open()
            .then([]() { cout << "starting to listen\n"; })
            .wait();

        while (true);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << '\n';
    }
}

int main() {
    start_server();

    return 0;
}