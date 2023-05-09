#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* ---------------------------------------------------------------- */
/* PROGRAM  pingpong :                                              */
/*    This program uses setjmp() and longjmp() to implement an      */
/* example of coroutine.                                            */
/* ---------------------------------------------------------------- */

#include  <stdio.h>
#include  <setjmp.h>

int       max_iteration;                /* the max # of iterations  */
int       iter;                         /* global iteration counter */

jmp_buf   Main;                         /* jump back to main()      */
jmp_buf   PointPing;                    /* jump buffer in Ping()    */
jmp_buf   PointPong;                    /* jump buffer in Pong()    */    

/* ---------------------------------------------------------------- */
/*                     Function Prototypes                          */
/* ---------------------------------------------------------------- */

void      Ping(void);
void      Pong(void);

/* ---------------------------------------------------------------- */
/*                  The main program starts here                    */
/* ---------------------------------------------------------------- */

int  main(int  argc, char* argv[])
{
     if (argc != 2) {                   /* check # of arguments     */
          printf("Use %s max-#-of-lines\n", argv[0]);
          return 1;
          // exit(1);
     }
     max_iteration = abs(atoi(argv[1]));/* get max # of iterations  */
     iter = 1;                          /* initial iteration count  */
     if (setjmp(Main) == 0)             /* set a return mark        */
          Ping();                       /* initialize Ping()        */
     if (setjmp(Main) == 0)             /* set a return mark        */
          Pong();                       /* initialize Pong()        */
     longjmp(PointPing, 1);             /* ok, jump to Ping()       */
}

/* ---------------------------------------------------------------- */
/* FUNCTION  Ping :                                                 */
/*    This function marks a return point when it is initialized.    */
/* Then, it starts a loop and jump back and forth between itself    */
/* and function Pong() using jump buffers.                          */
/* ---------------------------------------------------------------- */

void  Ping(void)
{
     if (setjmp(PointPing) == 0)        /* set a return mark        */
          longjmp(Main, 1);             /* jump back to main        */
     while (1) {                        /* main will jump to here   */
          // printf("%3d : Ping-", iter);  /* display Ping             */
          write(1,"+++ : Ping-",11);  /* display Ping             */
          if (setjmp(PointPing) == 0)   /* set a return mark        */
               longjmp(PointPong, 1);   /* jump to Pong()           */
     }
}

/* ---------------------------------------------------------------- */
/* FUNCTION  Pong :                                                 */
/*    This function marks a return point when it is initialized.    */
/* Then, it starts a loop and jump back and forth between itself    */
/* and function Ping() using jump buffers.                          */
/* ---------------------------------------------------------------- */

void  Pong(void)
{
     if (setjmp(PointPong) == 0)        /* set a return mark        */
          longjmp(Main, 1);             /* jump back to main        */
     while (1) {                        /* main will jump to here   */
          // printf("Pong\n");             /* display Pong             */
          write(1,"Pong\n",5);             /* display Pong             */
          iter++;                       /* increase iteration count */
          if (iter > max_iteration)     /* should I stop?           */
               exit(0);                 /*    yes, then exit        */
          if (setjmp(PointPong) == 0)   /* no, set a return mark    */
               longjmp(PointPing, 1);   /* then jump to Ping()      */
     }
}
