#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

// long dump(long command,long a1,long a2,long a3){
// 	long ret=0;
// 	ret+=a3;
// 	ret<<=16*4LL;
// 	ret+=a2;
// 	ret<<=16*4LL;
// 	ret+=a1;
// 	ret<<=16*2LL;
// 	ret+=command;
// 	return ret;
// }

static size_t check(size_t q){
	if (q==(size_t)(-1)){
		fprintf(stderr, "\x1b[31mnever read undefined values!\x1b[0m\n");
		assert(0);
	}
	if (q>0xFFFFFFFFFFFFFF){
		fprintf(stderr, "\x1b[31mwhat %lx is doing in memory?\x1b[0m\n",q);
		assert(0);
	}
	return q;
}


static size_t load(size_t q,size_t w){
	if (w==3){
		return q&((1LL<<(4*4))-1);
	}
	q>>=4*4;
	if (w==2){
		return q&((1LL<<(4*4))-1);
	}
	q>>=4*4;
	if (w==1){
		return q&((1LL<<(4*4))-1);
	}
	q>>=4*4;
	if (w==0){
		return q&((1LL<<(4*2))-1);
	}
	return 0;
}

static long ms(size_t q){
	if (q<(1LL<<55)){
		return (long)(q);
	}else{
		return (long)(q)-(1LL<<56);
	}
}

static size_t mu(long q){
	if (q<0){
		return (size_t)(q+(1LL<<56));
	}else{
		return (size_t)(q);
	}
}

int main(int argc,char**argv){
	if (argc<2){
		printf("\x1b[31mgive me a file!\x1b[0m\n");
		return 0;
	}
	FILE*file=fopen(argv[1],"r");
	if (!file){
		printf("\x1b[31mgive me a normal file!\x1b[0m\n");
		return 0;
	}
	size_t mem[0x10000];
	for (size_t w=0;w<0x10000;++w){
		mem[w]=(size_t)(-1);
	}
	size_t allocated[1024];
	size_t as=0;
	while (1){
		size_t address;
		if (fscanf(file,"%lx",&address)!=1){
			break;
		}
		if (address<0x2000){
			char*line=0;
			size_t lsm=0;
			long ls=getline(&line,&lsm,file);
			line[ls]='\0';
			long val=0;
			if (sscanf(line,"%lx",&val)==1){
				mem[address]=mu(val);
			}
			allocated[as++]=address;
			free(line);
		}else{
			char*line=0;
			size_t lsm=0;
			long ls=getline(&line,&lsm,file);
			char line1[1024];
			size_t ls1=0;
			for (long w=0;w<ls;++w){
				if ('0'<=line[w] and line[w]<='9' or 'a'<=line[w] and line[w]<='f' or 'A'<=line[w] and line[w]<='F'){
					line1[ls1++]=line[w];
				}
			}
			line1[ls1]='\0';
			if (ls1!=14){
				fprintf(stderr, "\x1b[31mgive mo args to line %s!\x1b[0m\n", line1);
				assert(0);
			}
			long val=0;
			sscanf(line1,"%lx",&val);
			mem[address]=mu(val);
			free(line);
		}
	}
	size_t address=0x2000;
	while (1){
		fprintf(stderr, "\x1b[32m[" );
		for (size_t w=0x1000;w<as+0x1000;++w){
			if (mem[w]==(size_t)(-1)){
				fprintf(stderr,"undefinedvalue");
			}else{
				for (long e=13;e>-1;--e){
					fprintf(stderr, "%c", "0123456789ABCDEF"[(mem[w]>>(4*e))%16]);
				}
			}
			fprintf(stderr, ", " );
		}
		fprintf(stderr, "]\x1b[0m\n" );
		size_t command,a1,a2,a3;
		if (mem[address]==(size_t)(-1)){
			fprintf(stderr, "\x1b[31mare you unstoppable?\x1b[0m\n" );
			assert(0);
		}
		check(mem[address]);
		command=load(mem[address],0);
		a1=load(mem[address],1);
		a2=load(mem[address],2);
		a3=load(mem[address],3);
		fprintf(stderr, "\x1b[34mperforming %lx(%lx,%lx,%lx)\x1b[0m\n",command,a1,a2,a3);
		address+=1;
		if (command==0x99){
			break;
		}else
		if (command==0x00){
			mem[a3]=check(mem[a1]);
		}else
		if (command==0x01){
			mem[a3]=(check(mem[a1])+check(mem[a2]))%(1LLU<<56);
		}else
		if (command==0x02){
			mem[a3]=((1LLU<<56)+check(mem[a1])-check(mem[a2]))%(1LLU<<56);
		}else
		if (command==0x03){
			mem[a3]=mu(ms( check(mem[a1]) )*ms( check(mem[a2]) ))%(1LLU<<56);
		}else
		if (command==0x13){
			mem[a3]=(check(mem[a1])*check(mem[a2]))%(1LLU<<56);
		}else
		if (command==0x04){
			size_t t1=check(mem[a1]);
			size_t t2=check(mem[a2]);
			mem[a3]=mu(ms(t1)/ms(t2))%(1LLU<<56);
			mem[(a3+1)%0x10000]=mu(ms(t1)%ms(t2))%(1LLU<<56);
		}else
		if (command==0x14){
			size_t t1=check(mem[a1]);
			size_t t2=check(mem[a2]);
			mem[a3]=(t1/t2)%(1LLU<<56);
			mem[(a3+1)%0x10000]=(t1%t2)%(1LLU<<56);
		}else
		if (command==0x80){
			address=a3;
		}else
		if (command==0x81){
			if (check(mem[a1])==check(mem[a2])){
				address=a3;
			}
		}else
		if (command==0x82){
			if (check(mem[a1])!=check(mem[a2])){
				address=a3;
			}
		}else
		if (command==0x83){
			if (ms(check(mem[a1]))<ms(check(mem[a2]))){
				address=a3;
			}
		}else
		if (command==0x93){
			if (check(mem[a1])<check(mem[a2])){
				address=a3;
			}
		}else
		if (command==0x84){
			if (ms(check(mem[a1]))>=ms(check(mem[a2]))){
				address=a3;
			}
		}else
		if (command==0x94){
			if (check(mem[a1])>=check(mem[a2])){
				address=a3;
			}
		}else
		if (command==0x85){
			if (ms(check(mem[a1]))>ms(check(mem[a2]))){
				address=a3;
			}
		}else
		if (command==0x95){
			if (check(mem[a1])>check(mem[a2])){
				address=a3;
			}
		}else
		if (command==0x86){
			if (ms(check(mem[a1]))<=ms(check(mem[a2]))){
				address=a3;
			}
		}else
		if (command==0x96){
			if (check(mem[a1])<=check(mem[a2])){
				address=a3;
			}
		}else{
			fprintf(stderr, "\x1b[31mnever use command %lx!\x1b[0m\n", command);
			assert(0);
		}
	}
		fprintf(stderr, "\x1b[32m[" );
		for (size_t w=0x1000;w<as+0x1000;++w){
			if (mem[w]==(size_t)(-1)){
				fprintf(stderr,"undefinedvalue");
			}else{
				for (long e=13;e>-1;--e){
					fprintf(stderr, "%c", "0123456789ABCDEF"[(mem[w]>>(4*e))%16]);
				}
			}
			fprintf(stderr, ", " );
		}
		fprintf(stderr, "]\x1b[0m\n" );
}
