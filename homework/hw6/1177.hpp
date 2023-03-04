#include <bits/stdc++.h>

template <class RandomIt, class Compare> void sort(RandomIt first, RandomIt last, Compare comp) {
    last--;
    auto mid = *(first + (last - first) / 2);
    auto i = first, j = last;
    do {
        while (comp(*i, mid))
            i++;
        while (comp(mid, *j))
            j--;
        if (i <= j) {
            std::swap(*i, *j);
            i++;
            j--;
        }
    } while (i <= j);
    if ((j - first) > 0)
        sort(first, j + 1, comp);
    if ((last - i) > 0)
        sort(i, last + 1, comp);
}

template <class RandomIt, class Compare> void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp) {
    last--;
    auto i = first, j = last;
    auto mid = *(first + (last - first) / 2);
    do {
        while (!comp(*j, mid))
            j--;
        while (!comp(mid, *i))
            i++;
        if (i <= j) {
            std::swap(*i, *j);
            i++;
            j--;
        }
    } while (i <= j);
    if (nth <= j)
        nth_element(first, nth, j + 1, comp);
    else if (i <= nth)
        nth_element(i, nth, last + 1, comp);
    else
        return;
}
