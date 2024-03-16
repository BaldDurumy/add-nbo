#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <stdlib.h> // for exit

uint32_t ntohl(uint32_t n){
	uint32_t n1 = (n & 0xff000000) >> 24;
	uint32_t n2 = (n & 0x00ff0000) >> 8;
	uint32_t n3 = (n & 0x0000ff00) << 8;
	uint32_t n4 = (n & 0x000000ff) << 24;
	return n1 | n2 | n3 | n4;
}

uint32_t filetoint(char* filename){
	//file open
	FILE* fp = fopen(filename, "rb");
	if(fp == NULL){
		printf("Can't Open %s\n", filename);
		exit(0);
	}

	//check file size
	fseek(fp, 0, SEEK_END);
	if(ftell(fp) != 4){
		printf("%s is Not 4bytes\n", filename);
		fclose(fp);
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);

	//read number
	uint32_t tmp = 0;
	fread(&tmp, 4, 1, fp);

	fclose(fp);
	
	return ntohl(tmp);
}

int main(int argc, char* argv[]){
	if (argc != 3){
		printf("Please Enter Two Input FIle\n");
		printf("ex) ./add-nbo thousand.bin five-hundred.bin");
		exit(0);
	}

	uint32_t a = filetoint(argv[1]);
	uint32_t b = filetoint(argv[2]);

	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", a, a, b, b, a+b, a+b);
	return 0;
}