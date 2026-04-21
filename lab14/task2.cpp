#include <iostream>
#include <string>

using namespace std;


class Handler {
public:
    virtual ~Handler() {}
    virtual Handler* setNext(Handler* handler) = 0;
    virtual bool handle(const string& request) = 0;
};

class AbstractHandler : public Handler {
private:
    Handler* next = nullptr;

public:
    Handler* setNext(Handler* handler) override {
        next = handler;
        return handler;
    }

    bool handle(const string& request) override {
        if (next) {
            return next->handle(request);
        }
        return true;
    }

protected:
    bool handleNext(const string& request) {
        if (next) {
            return next->handle(request);
        }
        return true;
    }
};

class AuthenticationHandler : public AbstractHandler {
public:
    bool handle(const string& request) override {
        if (request == "invalid") {
            cout << "[Auth] Authentication failed.\n";
            return false;
        }

        cout << "[Auth] Authentication passed.\n";
        return handleNext(request);
    }
};

class RoleCheckHandler : public AbstractHandler {
public:
    bool handle(const string& request) override {
        if (request == "admin") {
            cout << "[Role] Admin access granted.\n";
            return true;
        }

        if (request == "valid") {
            cout << "[Role] User access granted.\n";
            return handleNext(request);
        }

        cout << "[Role] Unknown role.\n";
        return false;
    }
};

void processRequest(const string& request, Handler* handler) {
    cout << "Processing: " << request << endl;
    if (!handler->handle(request)) {
        cout << "Request denied.\n" << endl;
    } else {
        cout << "Request approved.\n" << endl;
    }
}

int main() {
    Handler* roleCheck = new RoleCheckHandler();
    Handler* auth = new AuthenticationHandler();

    auth->setNext(roleCheck);

    processRequest("valid", auth);
    processRequest("invalid", auth);
    processRequest("admin", auth);

    delete auth;
    delete roleCheck;

    return 0;
}