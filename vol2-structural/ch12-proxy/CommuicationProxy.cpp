#include <iostream>
#include <string>
#include <sstream>
#include <memory>

// Define a class that has a virtual ping method
struct Pingable {
    virtual ~Pingable() = default;

    virtual std::wstring ping(const std::wstring &message) = 0;
};

// Pong class which implements Pingable and returns a concatenated response
struct Pong : Pingable {
    std::wstring ping(const std::wstring &message) override {
        return message + L" pong";
    }
};

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

// RemotePong communicates with a remote API to get the response
struct RemotePong : Pingable {
    std::wstring ping(const std::wstring &message) override {
        std::wstring result;
        http_client client(U("http://localhost:9149/"));
        uri_builder builder(U("/api/pingpong/"));
        builder.append(message);
        pplx::task <std::wstring> task = client.request(methods::GET, builder.to_string())
                .then([=](http_response r) {
                    return r.extract_string();
                });
        task.wait();
        return task.get();
    }
};

// Function that tests the ping functionality
void tryit(Pingable &pp) {
    std::wcout << pp.ping(L"ping") << "\n";
}

// Testing the functionality
bool Testing() {
    Pong pp;
    for (int i = 0; i < 3; ++i) {
        tryit(pp);
    }
    return true;
}

int main() { return Testing(); }
