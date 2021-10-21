#include<stdio.h>
#include<sys/resource.h>

int main(){
    struct rlimit rlim;
    
    int resources[] = {RLIMIT_AS,RLIMIT_SIGPENDING ,RLIMIT_CORE, RLIMIT_CPU, RLIMIT_DATA, RLIMIT_FSIZE,RLIMIT_MEMLOCK, RLIMIT_NOFILE, RLIMIT_NPROC,
              RLIMIT_RSS,RLIMIT_STACK};
    char *names[] = {"VIRTUAL MEM","QUEUED SIG","CORE", "CPU", "DATA", "FSIZE","MEMLOCK", "NOFILE", "NPROC", "RSS","STACK"};
    int n = sizeof(resources)/sizeof(resources[0]);
    
    printf("Resource\tSOFT_LIMIT\tHARD_LIMIT\n");
    /*
    The hard limit is the maximum value that is allowed for the soft limit. Any changes to the hard limit require root 
    access. The soft limit is the value that Linux uses to limit the system resources for running processes. 
    The soft limit cannot be greater than the hard limit.
    */
    
    for(int i=0;i<n;i++){
        int p = getrlimit(resources[i],&rlim);
        printf("%s\t\t%lu\t\t%lu\n",names[i], rlim.rlim_cur, rlim.rlim_max);//return size in bytes
    }
    return 0;
}

