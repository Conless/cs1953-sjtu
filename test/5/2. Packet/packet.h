#ifndef PACKET_H_
#define PACKET_H_

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Packet {
  public:
    // You should let ... be whatever you want.
    using T = string;
    T src;
    T dest;
    char *data;

  public:
    // TODO: constructor and destructor
    const T &GetSrc() const { return src; }
    const T &GetDest() const { return dest; }
    const char *GetData() const { return data; }
    virtual void Segment(int MTU) {}
    virtual void Print() const { std::cout << "Print start..." << std::endl; }
};

class IPv4Packet : public Packet {
  private:
    // Do whatever you want
  public:
    // TODO
    IPv4Packet(const string _src, const string _dest, const char *_data) {
        string res = "";
        int las = 0;
        for (int i = 0; i < _src.size(); i++) {
            if (_src[i] == '.' || i == _src.size() - 1) {
                string thisone;
                if (i == _src.size() - 1)
                    thisone = _src.substr(las, i - las + 1);
                else
                    thisone = _src.substr(las, i - las);
                las = i + 1;
                int toint = stoi(thisone);
                char sssss[4];
                sprintf(sssss, "%03d", toint);
                if (res != "")
                    res += ".";
                res += string(sssss);
            }
        }
        src = res;
        res = "";
        las = 0;
        for (int i = 0; i < _dest.size(); i++) {
            if (_dest[i] == '.' || i == _dest.size() - 1) {
                string thisone;
                if (i == _dest.size() - 1)
                    thisone = _dest.substr(las, i - las + 1);
                else
                    thisone = _dest.substr(las, i - las);
                las = i + 1;
                int toint = stoi(thisone);
                char sssss[4];
                sprintf(sssss, "%03d", toint);
                if (res != "")
                    res += ".";
                res += string(sssss);
            }
        }
        dest = res;
        data = new char[100];
        strcpy(data, _data);
    }
    void Segment(int MTU) {
        MTU -= 20;
        int offset = MTU / 8 * 8;
        string dataa = data;
        for (int i = 0; i < dataa.size(); i += offset) {
            printf("Fragment %d: Size %d; Header Size 20; Data Size 8; Flag 1; Fragment Offset %d; Data ", i / offset);
        }
    }
    void Print() const {
        std::cout << "Print start..." << std::endl;
        std::cout << src << '\t' << dest << '\t' << data << '\n';
    }
};

class IPv6Packet : public Packet {
  private:
    // Do whatever you want
  public:
    // TODO
    IPv6Packet(string _src, string _dest, const char *_data) {
        int flag = 0;
        if (_src.size() == 2)
            _src = "0000:0000:0000:0000:0000:0000:0000:0000";
        else {
            for (int i = 1; i < _src.size(); i++)
                if (_src[i] == _src[i - 1] && _src[i] == ':') {
                    flag = i;
                    break;
                }
            if (flag) {
                int cnt = 0;
                for (auto ch : _src)
                    if (ch == ':')
                        cnt++;
                if (flag == 1) {
                    _src.erase(0, 1);
                    for (int i = 1; i < 9 - cnt; i++)
                        _src.insert(0, ":0000");
                    _src.insert(0, "0000");
                } else {
                    bool flagg = 0;
                    if (flag == _src.size() - 1)
                        flagg = 1;
                    for (int i = 1; i < 8 - cnt; i++)
                        _src.insert(flag, ":0000");
                    _src.insert(flag, "0000");
                    if (flagg) {
                        _dest.insert(_dest.size(), "0000");
                    }
                }
            }
        }
        src = _src;
        if (_dest.size() == 2)
            _dest = "0000:0000:0000:0000:0000:0000:0000:0000";
        else {
            flag = 0;
            for (int i = 1; i < _dest.size(); i++)
                if (_dest[i] == _dest[i - 1] && _dest[i] == ':') {
                    flag = i;
                    break;
                }
            if (flag) {
                int cnt = 0;
                for (auto ch : _dest)
                    if (ch == ':')
                        cnt++;
                if (flag == 1) {
                    _dest.erase(0, 1);
                    for (int i = 1; i < 9 - cnt; i++)
                        _dest.insert(0, ":0000");
                    _dest.insert(0, "0000");
                } else {
                    bool flagg = 0;
                    if (flag == _dest.size() - 1)
                        flagg = 1;
                    for (int i = 1; i < 8 - cnt; i++)
                        _dest.insert(flag, ":0000");
                    _dest.insert(flag, "0000");
                    if (flagg) {
                        _dest.insert(_dest.size(), "0000");
                    }
                }
            }
        }
        dest = _dest;
        data = new char[100];
        strcpy(data, _data);
    }
    void Segment(int MTU) {
        std::cout << "IPv6Packet is already segmented.\n";
    }
    void Print() const {
        std::cout << "Print start..." << std::endl;
        std::cout << src << '\t' << dest << '\t' << data << '\n';
    }
};

#endif // PACKET_H_
