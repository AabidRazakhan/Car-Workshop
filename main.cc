#include <iostream>

#include "reader.h"
#include "writer.h"
#include "reader.cc"
#include "writer.cc"
#include "order.h"

int main() {

  financial::order r = financial::order::create_new_order();

  return 0;
}