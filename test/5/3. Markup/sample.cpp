// correctness: typeIn, insert, erase, split, query, copy_paste

#include <iostream>
#include "markup.h"

using namespace sjtu;

MarkUp mu;

int main() {
  mu.typeIn('A');
  mu.typeIn('S');
  mu.typeIn('O');
  mu.typeIn('U');
  mu.typeIn('L');

  for (int i = 1; i <= 5; i++) {
    std::cout << mu.query(1, i) << ' ';
  }
  std::cout << std::endl;
  // A S O U L 


  mu.insert(1, 2, '-');
  mu.print();
  // A-SOUL

  mu.split(1, 7);
  mu.typeIn('1');
  mu.typeIn('-');
  mu.copy_paste(1, 1, 1, 6, 2, 3);

  mu.print();
  // A-SOUL
  // 1-A-SOUL

  mu.erase(2, 2);


  mu.print();
  // A-SOUL
  // 1A-SOUL

  mu.split(2, 1);
  mu.print();
  // A-SOUL
  //
  // 1A-SOUL

  return 0;
}
