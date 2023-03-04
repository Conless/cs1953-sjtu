#include <bits/stdc++.h>
#include <string>

using namespace std;

const float times[7][7] = {{0.5, 0.5, 2, 1, 1, 1, 0.5}, {2, 0.5, 0.5, 1, 1, 2, 0.5}, {0.5, 2, 0.5, 1, 0.5, 2, 0.5},
                           {1, 2, 0.5, 1, 2, 0, 0.5},   {1, 1, 2, 0.5, 1, 1, 1},     {2, 1, 0.5, 2, 0, 1, 1},
                           {1, 1, 1, 1, 1, 1, 2}};
const string error_message[5] = {"Argument Error: PM Name Invalid (", "Argument Error: PM ID Invalid (",
                                 "Argument Error: PM Type Invalid (", "Iterator Error: Invalid Iterator",
                                 "Iterator Error: Dereference Error"};

class BasicException {
  protected:
    int type;
    string message;

  public:
    explicit BasicException(int _type, string _message) : type(_type), message(_message) {}
    virtual string what() { return type < 3 ? error_message[type] + message + ")" : error_message[type]; }
};

class ArgumentException : public BasicException {
  public:
    explicit ArgumentException(int _type, string _message) : BasicException(_type, _message) {}
    string what() override {
        return error_message[type] + message + ")";
    }
};

class IteratorException : public BasicException {
  public:
    explicit IteratorException(int _type) : BasicException(_type, "") {}
    string what() override { return error_message[type]; }
};

struct Pokemon {
    char name[12], types[8];
    int id;
    Pokemon(const char *_name = "", int _id = 0) {
        strcpy(name, _name);
        id = _id;
        strcpy(types, "0000000");
    }
    friend istream &operator>>(istream &in, Pokemon &x) { return (in >> x.name >> x.id >> x.types); }
    friend ostream &operator<<(ostream &out, const Pokemon &x) { return (out << x.name << ' ' << x.id << ' ' << x.types); }
};

class Pokedex {
  private:
    //可以自己定义需要的成员
    map<int, Pokemon> poke_table;
    string file_name;

  public:
    static bool IsChar(char ch) { return ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z'); }
    static bool IsNameValidate(string s) {
        for (const char &ch : s) {
            if (!IsChar(ch))
                return false;
        }
        return true;
    }
    static vector<string> DivideMsg(string s) {
        int las = 0;
        vector<string> ret;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '#') {
                ret.push_back(s.substr(las, i - las));
                las = i + 1;
            } else if (i == s.size() - 1)
                ret.push_back(s.substr(las, i - las + 1));
        }
        return ret;
    }
    static int TypeToNum(string s) {
        if (s == "fire")
            return 0;
        if (s == "water")
            return 1;
        if (s == "grass")
            return 2;
        if (s == "electric")
            return 3;
        if (s == "flying")
            return 4;
        if (s == "ground")
            return 5;
        if (s == "dragon")
            return 6;
        throw ArgumentException(2, s);
    }
    static vector<int> TypeToNum(vector<string> s) {
        vector<int> ret;
        for (auto str : s)
            ret.push_back(TypeToNum(str));
        return ret;
    }

  public:
    explicit Pokedex(const char *_fileName) {
        ios::sync_with_stdio(false);
        file_name = _fileName;
        ifstream fin(_fileName);
        if (fin.good()) {
            int siz;
            fin >> siz;
            while (siz--) {
                int fir;
                Pokemon sec;
                fin >> fir >> sec;
                poke_table.insert(make_pair(fir, sec));
            }
        }
    }

    ~Pokedex() {
        ofstream fout(file_name, ios::out | ios::trunc);
        fout << poke_table.size() << '\n';
        for (auto it : poke_table)
            fout << it.first << ' ' << it.second << '\n';
    }

    bool pokeAdd(const char *name, int id, const char *types) {
        if (!IsNameValidate(name))
            throw ArgumentException(0, name);
        if (id <= 0)
            throw ArgumentException(1, to_string(id));
        vector<int> ret = TypeToNum(DivideMsg(types));
        if (poke_table.find(id) != poke_table.end())
            return false;
        Pokemon tmp(name, id);
        int siz = ret.size();
        for (int i = 0; i < siz; i++)
            tmp.types[ret[i]] = '1';
        poke_table[id] = tmp;
        return true;
    }

    bool pokeDel(int id) {
        if (id <= 0)
            throw ArgumentException(1, to_string(id));
        if (poke_table.find(id) == poke_table.end())
            return false;
        poke_table.erase(id);
        return true;
    }

    string pokeFind(int id) {
        if (id <= 0)
            throw ArgumentException(1, to_string(id));
        if (poke_table.find(id) == poke_table.end())
            return "None";
        return poke_table[id].name;
    }

    string typeFind(const char *_types) const {
        // TO DO: 查询属性包含了types中的属性的宝可梦
        // return: 如果找到，返回多行字符串。第一行为满足的宝可梦数量，
        //           接下来每一行为宝可梦的name，按id从小到大。
        //         如果找不到，返回字符串 "None"
        //注意，types可能为多种属性，同样用 # 号分隔
        string ret = "";
        int cnt = 0;
        vector<int> types = TypeToNum(DivideMsg(_types));
        for (auto tmp : poke_table) {
            auto tmp_poke = tmp.second.types;
            bool flag = 1;
            for (auto tmp_type : types)
                if (tmp_poke[tmp_type] == '0') {
                    flag = 0;
                    break;
                }
            if (flag) {
                if (!cnt)
                    ret += string(tmp.second.name);
                else
                    ret += "\n" + string(tmp.second.name);
                cnt++;
            }
        }
        if (!cnt)
            ret = "None";
        ret = to_string(cnt) + "\n" + ret;
        return ret;
    }

    float attack(const char *_type, int id) {
        // TO DO: 伤害倍率计算
        // return: 返回id对应的宝可梦受到属性type的攻击的伤害倍率。
        //           如果id对应不存在宝可梦，返回 -1
        //这里type保证为单属性
        if (id <= 0)
            throw ArgumentException(1, to_string(id));
        int type = TypeToNum(_type);
        if (poke_table.find(id) == poke_table.end())
            return -1;
        float tmp = 1.0;
        for (int i = 0; i < 7; i++)
            if (poke_table[id].types[i] == '1')
                tmp *= times[type][i];
        return tmp;
    }
    float attack(int type, int id) {
        // TO DO: 伤害倍率计算
        // return: 返回id对应的宝可梦受到属性type的攻击的伤害倍率。
        //           如果id对应不存在宝可梦，返回 -1
        //这里type保证为单属性
        if (id <= 0)
            throw ArgumentException(1, to_string(id));
        if (poke_table.find(id) == poke_table.end())
            return -1;
        float tmp = 1.0;
        for (int i = 0; i < 7; i++)
            if (poke_table[id].types[i] == '1')
                tmp *= times[type][i];
        return tmp;
    }

    int catchTry() {
        // TO DO: 全图鉴捕获尝试
        // return: 按照前文过程最后能拥有的宝可梦数量。
        if (poke_table.empty())
            return 0;
        auto tmp = poke_table.begin()->second;
        char types[8];
        strcpy(types, tmp.types);
        unordered_map<int, int> vis;
        int cnt = 1;
        vis[tmp.id] = 1;
        while (true) {
            bool flag = 0;
            for (auto it = poke_table.begin(); it != poke_table.end(); it++) {
                int tmp_id = it->first;
                if (vis[tmp_id] == 1)
                    continue;
                float mx = 0;
                for (int i = 0; i < 7; i++) {
                    if (types[i] == '1')
                        mx = max(mx, attack(i, tmp_id));
                }
                if (mx >= 1.999) {
                    vis[tmp_id] = 1;
                    cnt++;
                    for (int i = 0; i < 7; i++) {
                        if (it->second.types[i] == '1' && types[i] == '0') {
                            flag = 1;
                            types[i] = '1';
                        }
                    }
                }
            }
            if (!flag)
                break;
        }
        return cnt;
    }

    struct iterator {
        std::map<int, Pokemon>::iterator iter;

        iterator() { }

        iterator(const std::map<int, Pokemon>::iterator &tmp) {
            iter = tmp;
        }

        iterator(const iterator &tmp) : iterator(tmp.iter) {}

        iterator &operator++() {
            if (!ptr || iter == ptr->end())
                throw IteratorException(3);
            ++iter;
            return *this;
        }

        iterator &operator--() {
            if (!ptr || iter == ptr->begin())
                throw IteratorException(3);
            --iter;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        iterator &operator=(const iterator &rhs) {
            iter = rhs.iter;
            ptr = rhs.ptr;
            return *this;
        }
        bool operator==(const iterator &rhs) const { return iter == rhs.iter; }
        bool operator!=(const iterator &rhs) const { return iter != rhs.iter; }
        const Pokemon &operator*() const {
            if (!ptr || iter == ptr->end())
                throw IteratorException(4);
            return (*iter).second;
        }
        const Pokemon *operator->() const {
            if (!ptr || iter == ptr->end())
                throw IteratorException(4);
            return &((*iter).second);
        }
    };

    iterator begin() { return iterator(poke_table.begin(), &poke_table); }

    iterator end() { return iterator(poke_table.end(), &poke_table); }
};
