#ifndef InErr_H_INC
#define InErr_H_INC

#include <limits>
#include <iostream>

constexpr std::streamsize 
            INF_STREAM{std::numeric_limits<std::streamsize>::max()};   

template <typename ErrT>
inline void InErr(ErrT & in) {
    using namespace std;
    cin >> in;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(INF_STREAM, '\n');
        cerr << "\nInput invalid, please try again.\n";
        cin >> in;
    }

};

#endif
