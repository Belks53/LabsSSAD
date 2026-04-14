#include <iostream>
using namespace std;

class Expression {
    public:
    virtual int interpret() = 0;
    virtual ~Expression() = default;
};

class Number : public Expression {
    private:
    int num;

    public:
    Number(int n) : num(n) {}

    int interpret() override {
        return num;
    }
};

class Multiplication : public Expression {
    private:
    Expression* left;
    Expression* right;

public:
    Multiplication(Expression* l, Expression* r) : left(l), right(r) {}

    int interpret() override {
        return left->interpret() * right->interpret();
    }
};

class Add : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    Add(Expression* l, Expression* r) : left(l), right(r) {}

    int interpret() override {
        return left->interpret() + right->interpret();
    }
};

class Subtract : public Expression {
private:
    Expression* left;
    Expression* right;

public:
    Subtract(Expression* l, Expression* r) : left(l), right(r) {}

    int interpret() override {
        return left->interpret() - right->interpret();
    }
};

int main() {
    Expression* expr = new Multiplication(
            new Add(
                new Number(8),
                new Number(3)
            ),
            new Subtract(
                new Number(10),
                new Number(2)
            )
        );
    cout << "Result: " << expr->interpret() << endl;
    delete expr;
}

