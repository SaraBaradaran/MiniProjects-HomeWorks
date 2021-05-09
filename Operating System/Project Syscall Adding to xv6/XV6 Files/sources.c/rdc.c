#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{

  if(argc > 1){
    printf(1, "rdc: too many arguments\n");
    exit();
  }

  printf(1, "Hi, the number of read syscall is %d so for!\n", getreadcount());
  exit();
}
