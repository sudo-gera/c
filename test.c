#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <iso646.h>

int main(int argc,char**argv){
    assert(argc>1);
    int pipe_db_to_a[2];
    int pipe_a_to_db[2];
    pipe(pipe_db_to_a);
    pipe(pipe_a_to_db);
    if (not fork()){
        close(pipe_db_to_a[0]);
        close(pipe_a_to_db[1]);
        dup2(pipe_a_to_db[0],0);
        dup2(pipe_db_to_a[1],1);
        execlp("lldb","lldb",argv[1],NULL);
    }else{
        close(pipe_db_to_a[1]);
        close(pipe_a_to_db[0]);
        dup2(pipe_a_to_db[1],1);
        dup2(pipe_db_to_a[0],0);
        execlp(argv[1],argv[1],NULL);
    }
}
