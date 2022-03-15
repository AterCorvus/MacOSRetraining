#include <iostream>
#include <memory>
#include <string>
#include <locale>
#include <codecvt>

#include "Product.pb.h"
#include "cpprest/http_listener.h"
#include "cpprest/json.h"

using namespace std;

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace utility;

#define TRACE(msg) cout << msg
#define TRACE_ACTION(a, k, v) cout << a << L" { " << k << L". " << v << L"}\n"

const string version = "0.0.1";

void respond(const http_request& request, const status_code& status, const json::value& response)
{
    request.reply(status, response);
}

int main() {
    product_info::Product product;
    product.set_version(version);
    
    http_listener listener(U("http://127.0.0.1:35248/version"));

    listener.support(methods::GET, [&, product](http_request request){ 
        std::wstring_convert<std::codecvt_utf8<wchar_t> > converter;
        std::wstring response = converter.from_bytes(("version: ") + product.version());
        respond(request, status_codes::OK, json::value::string(response));
        });

    try
    {
        listener
        .open()
        .then([&listener](){ TRACE("\nstarting to listen\n"); })
        .wait();

        while (true);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}