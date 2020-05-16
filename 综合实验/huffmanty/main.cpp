#include "commen.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"

int main() {
	//文件最好不要大于5MB
	string s = "pic\\5.bmp";

	string s1 = s + "-zipped";
	string s2 = s1 + "-unzipped";

	/*压缩*/
	HuffmanEncoder mEncoder;
	mEncoder.build((char*)s.c_str(), (char*)s1.c_str());
	mEncoder.encode();
	
	/*解压缩*/
	HuffmanDecoder mDecoder;
	mDecoder.build((char*)s1.c_str(), (char*)s2.c_str());
	mDecoder.decode();
	
	return 0;
}
