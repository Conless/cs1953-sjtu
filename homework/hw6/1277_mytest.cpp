// #include "1277.cpp"
#include "src.hpp"

int main() {
    try {
        Pokedex p("pokedex");
        typeFind("water#ice#block");
        std::cout << p.pokeAdd("haha", 1, "water#dragon") << '\n';
    } catch (BasicException x) {
        std::cout << x.what() << '\n';
    }
}
