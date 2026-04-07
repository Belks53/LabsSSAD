#include "task2.h"
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

class PayPal {
public:
    void makePayment(string item) {
        cout << "Making PayPal payment for item: " << item << endl;
    }

    bool verifyPayment(string transactionId) {
        cout << "Verifying PayPal payment with transaction ID: " << transactionId << endl;
        return true;
    }

    void refundPayment(string item) {
        cout << "Refunding PayPal payment for item: " << item << endl;
    }
};

class Stripe {
public:
    void chargePayment(string item) {
        cout << "Charging Stripe payment for item: " << item << endl;
    }

    bool verifyCharge(string transactionId) {
        cout << "Verifying Stripe payment with transaction ID: " << transactionId << endl;
        return true;
    }

    void issueRefund(string item) {
        cout << "Issuing Refund for Stripe payment for item: " << item << endl;
    }
};

class PaymentProvider {
public:
    virtual ~PaymentProvider() = default;
    virtual void processPayment(const string& item) = 0;
    virtual bool verifyPayment(const string& transactionId) = 0;
    virtual void refundPayment(const string& item) = 0;
};

class PayPalAdapter : public PaymentProvider {
private:
    PayPal* payPal;

public:
    PayPalAdapter(PayPal* pp) : payPal(pp) {}

    void processPayment(const string& item) override {
        payPal->makePayment(item);
    }

    bool verifyPayment(const string& transactionId) override {
        return payPal->verifyPayment(transactionId);
    }

    void refundPayment(const string& item) override {
        payPal->refundPayment(item);
    }
};

class StripeAdapter : public PaymentProvider {
private:
    Stripe* stripe;

public:
    StripeAdapter(Stripe* s) : stripe(s) {}

    void processPayment(const string& item) override {
        stripe->chargePayment(item);
    }

    bool verifyPayment(const string& transactionId) override {
        return stripe->verifyCharge(transactionId);
    }

    void refundPayment(const string& item) override {
        stripe->issueRefund(item);
    }
};

class PaymentGateWay {
private:
    unordered_map<string, PaymentProvider *> paymentProviders;

public:
    PaymentGateWay() {
        paymentProviders = unordered_map<string, PaymentProvider *>();
    }
    void addPaymentProvider(const string& providerName, PaymentProvider* paymentProvider) {
        paymentProviders[providerName] = paymentProvider;
    }
    void processPayment(const string& providerName, const string& paymentInfo) {
        auto it = paymentProviders.find(providerName);
        if (it != paymentProviders.end()) {
            it->second->processPayment(paymentInfo);
        } else {
            cout << "Error: Payment provider '" << providerName << "' not found!" << endl;
        }
    }

    void refundPayment(const string& providerName, const string& refundInfo) {
        auto it = paymentProviders.find(providerName);
        if (it != paymentProviders.end()) {
            it->second->refundPayment(refundInfo);
        } else {
            cout << "Error: Payment provider '" << providerName << "' not found!" << endl;
        }
    }
    void verifyPayment(const string& providerName, const string& paymentInfo) {
        auto it = paymentProviders.find(providerName);
        if (it != paymentProviders.end()) {
            it->second->verifyPayment(paymentInfo);
        } else {
            cout << "Error: Payment provider '" << providerName << "' not found!" << endl;
        }
    }
};





int main() {
    PayPalAdapter* paypalAdapter = new PayPalAdapter(new PayPal());
    StripeAdapter* stripeAdapter = new StripeAdapter(new Stripe());

    PaymentGateWay paymentGateWay;
    paymentGateWay.addPaymentProvider("STRIPE", stripeAdapter);
    paymentGateWay.processPayment("STRIPE", "SHEIN-SHOES");
    paymentGateWay.verifyPayment("STRIPE", "transactionId:001001");
    paymentGateWay.refundPayment("STRIPE", "Refund SHEIN-SHOES");
    cout << endl;
    paymentGateWay.addPaymentProvider("PAYPAL", paypalAdapter);
    paymentGateWay.processPayment("PAYPAL", "KAZAN-EXPRESS-HATS");
    paymentGateWay.verifyPayment("PAYPAL", "transactionId:061041");
    paymentGateWay.refundPayment("PAYPAL", "Refund KAZAN-EXPRESS-HATS");

    delete paypalAdapter;
    delete stripeAdapter;

    return 0;
}
