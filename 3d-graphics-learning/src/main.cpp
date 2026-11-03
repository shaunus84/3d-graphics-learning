#include <iostream>

#include "Application.h"

int main(int argc, char** argv) {
  Application app{"3D Graphics Learning"};

  const InitResult result = app.Initialise();

  if (!result) {
    std::cerr << result.error << '\n';
    return -1;
  }
  app.Run();

  return 0;
}
