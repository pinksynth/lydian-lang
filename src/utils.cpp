#define PRINT(string)                                                          \
  if (getenv("DEBUG")) {                                                       \
    std::cout << string << std::endl;                                          \
  };
