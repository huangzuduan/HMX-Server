#include "SrvEngine.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>

zRSA::zRSA(const char* _pubfilename, const char* _prifilename, const char* _password)
{
	bzero(pubfilename,sizeof(pubfilename));
	bzero(prifilename, sizeof(prifilename));
	bzero(password, sizeof(password));
	strncpy(pubfilename, _pubfilename, sizeof(pubfilename) - 1);
	strncpy(prifilename, _prifilename, sizeof(prifilename) - 1);
	strncpy(password, _password, sizeof(password) - 1);
}

zRSA::~zRSA()
{

}

bool zRSA::generateKey()
{
	/* 生成公钥 */
	std::stringstream sspub;
	sspub << pubfilename;
	sspub << ".pub.pem";

	char _pubfilename[sizeof(pubfilename) + 8];
	bzero(_pubfilename,sizeof(_pubfilename));
	strncpy(_pubfilename, sspub.str().c_str(), sizeof(_pubfilename) - 1);

	RSA* rsa = RSA_generate_key(1024, RSA_F4, NULL, NULL);
	BIO *bp = BIO_new(BIO_s_file());

	BIO_write_filename(bp, _pubfilename);
	if (PEM_write_bio_RSAPublicKey(bp, rsa) != 1)
	{
		printf("PEM_write_bio_RSAPublicKey error!\n");
		return false;
	}

	BIO_free_all(bp);


	/* 生成私钥 */
	std::stringstream sspri;
	sspri << prifilename;
	sspri << ".pri.pem";

	char _prifilename[sizeof(prifilename) + 8];
	bzero(_prifilename, sizeof(_prifilename));
	strncpy(_prifilename, sspri.str().c_str(), sizeof(_prifilename) - 1);


	bp = BIO_new_file(_prifilename, "w+");

	if (PEM_write_bio_RSAPrivateKey(bp, rsa,
		EVP_des_ede3_ofb(), (unsigned char *)password,
		strlen(password), NULL, NULL) != 1)
	{
		printf("PEM_write_bio_RSAPrivateKey error!\n");
		return false;
	}

	BIO_free_all(bp);
	RSA_free(rsa);

	return true;
}

std::string zRSA::bio_read_privateKey(std::string data)
{
	OpenSSL_add_all_algorithms();

	BIO* bp = BIO_new(BIO_s_file());

	BIO_read_filename(bp, "private.pem");

	char passwd[] = "1234";
	RSA* rsaK = PEM_read_bio_RSAPrivateKey(bp, NULL, NULL, passwd);
	if (NULL == rsaK) {
		perror("read key file fail!");
	}
	else {
		printf("read success!\n");
	}

	int nLen = RSA_size(rsaK);
	//printf("len:%d\n",nLen);
	char *pEncode = new char[nLen + 1];
	int ret = RSA_private_decrypt(data.length(), (const unsigned char*)data.c_str(), (unsigned char *)pEncode, rsaK, RSA_PKCS1_PADDING);
	std::string strRet;
	if (ret >= 0) {
		strRet = std::string(pEncode, ret);
		//printf("%s",strRet.c_str());
	}

	delete[] pEncode;
	CRYPTO_cleanup_all_ex_data();
	BIO_free_all(bp);
	RSA_free(rsaK);
	return strRet;
}

std::string zRSA::bio_read_publicKey(std::string data)
{
	OpenSSL_add_all_algorithms();
	BIO* bp = BIO_new(BIO_s_file());
	BIO_read_filename(bp, "public.pem");
	RSA* rsaK = PEM_read_bio_RSAPublicKey(bp, NULL, NULL, NULL);
	if (NULL == rsaK) {
		perror("read key file fail!");
	}
	else {
		printf("read success!");
		int nLen = RSA_size(rsaK);
		printf("len:%d\n", nLen);
	}
	int nLen = RSA_size(rsaK);
	char *pEncode = new char[nLen + 1];
	int ret = RSA_public_encrypt(data.length(), (const unsigned char*)data.c_str(),
		(unsigned char *)pEncode, rsaK, RSA_PKCS1_PADDING);
	std::string strRet;
	if (ret >= 0) {
		strRet = std::string(pEncode, ret);
		//printf("%s\n",strRet.c_str());
	}
	delete[] pEncode;
	CRYPTO_cleanup_all_ex_data();
	BIO_free_all(bp);
	RSA_free(rsaK);
	return strRet;
}

void zRSA::encryptFile(std::string inputfile, std::string outputfile)
{
	std::ifstream file(inputfile.c_str());
	std::ofstream outfile(outputfile.c_str());
	std::string tsum;
	std::string ss;
	while (getline(file, ss)) {
		tsum.append(ss.append("\n"));
	}
	std::cout << "徐加密内容：" << tsum << std::endl;
	std::string mw = bio_read_publicKey(tsum);
	std::cout << mw << std::endl;
	outfile << mw;
	outfile.flush();
	outfile.close();
	file.close();
}

void zRSA::decryptFile(std::string inputfile, std::string outputfile)
{
	std::ifstream file(inputfile.c_str());
	std::ofstream outfile(outputfile.c_str());
	std::string tsum, ss;
	while (getline(file, ss)) {
		tsum.append(ss);
	}
	std::string cw = bio_read_privateKey(tsum);
	std::cout << "恢复明文：" << cw;
	outfile << cw;
	outfile.flush();
	outfile.close();
	file.close();
}

int zRSA::testEncodeUncode()
{
	//char *str = "第一步，首先需要在openssl官网下载openssl包http://www.openssl.org/source/；\n第二步，自己查资料去！;";
	////system("openssl genrsa -out private.key 1024");
	//bool ret = generateKey(password);
	//if (!ret)
	//{
	//	return 0;
	//}

	//bio_read_publicKey("test");
	//printf("原文：%s\n", str);
	//std::string m = bio_read_publicKey(str);
	//printf("密文：\n------------%s--------------\n\n", m.c_str());
	//std::string miwen = m;
	//std::string c = bio_read_privateKey(miwen);
	//printf("解密后：\n------------%s--------------\n\n", c.c_str());

	//printf("----------------加密文件--------------------------\n");
	//encryptFile("d:/before.txt", "e:/my.txt");
	//std::cout << "------------------done-------------------------------" << std::endl;
	/*
	ifstream infile("f:/my.txt");
	std::string instr,intemp;
	while (getline(infile,intemp)) {
	instr.append(intemp);
	}
	cout<<instr<<endl;
	std::string cwen = bio_read_privateKey(instr);
	cout<<cwen;
	*/
	//printf("-----------------解密文件----------------------------\n");
	//decryptFile("e:/my.txt", "e:/jiemihou.txt");
	//std::cout << "------------------done-------------------------------" << std::endl;

	return 0;
}

const char* zRSA::getPubfilename() const
{
	return pubfilename;
}

const char* zRSA::getPrifilename() const
{
	return prifilename;
}

const char* zRSA::getPassword() const
{
	return password;
}









