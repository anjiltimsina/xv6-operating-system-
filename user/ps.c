#include "kernel/types.h"
#include "user/user.h"

// Map state numbers to readable names
const char *state_name(int state) {
  switch(state) {
    case 0: return "unused";
    case 1: return "used";
    case 2: return "sleep";
    case 3: return "runbl";
    case 4: return "run";
    case 5: return "zombie";
    default: return "unknown";
  }
}

int
main(void)
{
  struct procinfo procs[64];
  int nprocs;
  int i;
  
  printf("PID\tPPID\tPRIORITY\tSTATE\t\tNAME\n");
  printf("=============================================================\n");
  
  nprocs = getprocs(procs, 64);
  
  if(nprocs < 0) {
    fprintf(2, "getprocs failed\n");
    exit(1);
  }
  
  for(i = 0; i < nprocs; i++) {
    printf("%d\t%d\t%d\t\t%s\t%s\n",
           procs[i].pid,
           procs[i].ppid,
           procs[i].priority,
           state_name(procs[i].state),
           procs[i].name);
  }
  
  exit(0);
}
