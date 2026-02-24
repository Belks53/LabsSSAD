#include <map>
#include <iostream>
#include <string>

template <typename K, typename V>
class Dictionary {
    private:
    std::pmr::map<K, V> p;

    public:
    explicit Dictionary() = default;


    V get(K key) {
        auto it = p.find(key);
        if (it == p.end()) {
            return V();
        }
        return it->second;
    }

    void put(K key, V value) {
        p[key] = value;
    }

    void remove(K key) {
        p.erase(key);
    }

    int size() {
        return p.size();
    }
};

template <typename K>
class Dictionary<K, int> {
private:
    std::pmr::map<K, int> p;

public:
    explicit Dictionary() = default;

    int get(K key) {
        return abs(p.find(key)->second);
    }

    void put(K key, int value) {
        p[key] = value;
    }

    void remove(K key) {
        p.erase(key);
    }

    int size() {
        int result = 0;
        for (auto it = p.begin(); it != p.end(); it++) {
            result += it->second;
        }
        return result;
    }

};

int main() {
    // Dictionary<int, std::string> a;
    // a.put(1, "hello");
    // a.put(2, "world");
    // a.size();
    // std::cout << a.get(1) << std::endl;
    // a.remove(1);
    // a.size();
    // std::cout << a.get(2) << std::endl;

    Dictionary<std::string, int> dic;

    dic.put("hello", -1);
    dic.put("world", 2);
    dic.put("eded", 3);

    std::cout << dic.get("hello") << std::endl;
    std::cout << dic.size();
}