ima{
	inf z=1;
	inf x=1;
	printf("{");
	for (size_t w=0;w<1000'000'000;++w){
		if (w%1000==0){
				printf("{%s,%s},",z.to_string().c_str(),x.to_string().c_str());
				fprintf(stderr, "%zu\n", w);
		}
		inf c=z+x;
		z=x;
		x=c;
	}
	printf("}\n");
}
