char* compress(const char *text_data, size_t text_size, size_t *compressed_size){
	*compressed_size=text_size;
	char*f = malloc(text_size);
	memcpy(f, text_data,text_size);
	return f;
}

char *decompress(const char *compressed_data, size_t compressed_size, size_t *uncompressed_size){
	*uncompressed_size=compressed_size;
	char*f = malloc(compressed_size);
	memcpy(f, compressed_data,compressed_size);
	return f;
}

