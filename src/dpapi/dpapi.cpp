// dpapi.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


vector<char> read_file()
{
	//ifstream ifs("C:\\Users\\twf\\.arm\\cache_tenants.dat", ios::binary | ios::ate);
	ifstream ifs("C:\\Users\\twf\\.arm\\cache_tokens.dat", ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();
	vector<char> result(pos);
	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);
	ifs.close();
	return result;
}

void print_bytes(const vector<char>& bytes)
{
	int cnt = 0;

	for (vector<char>::const_iterator i = bytes.begin(); i != bytes.end(); ++i, ++cnt)
	{
		if ((cnt % 16) == 0 && cnt > 0) {
			printf("\n");
		}
		else if ((cnt % 2) == 0 && cnt>0) {
			printf(" ");
		}
		printf("%02x", (int)((unsigned char)*i));
	}
	printf("\n");
}


int main()
{

	printf("Hello world\n");

	vector<char> result = read_file();

	//print_bytes(result);
	

	DATA_BLOB DataOut;
	DATA_BLOB DataVerify;

	BYTE *pbDataOutput = (BYTE *)(&result[0]);  //reinterpret_cast<BYTE*>(result.data());
	DWORD cbDataOutput = result.size();

	DataOut.cbData = cbDataOutput;
	DataOut.pbData = pbDataOutput;

	if (CryptUnprotectData(&DataOut, NULL, NULL, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &DataVerify))
	{
		printf("OK\n");
	}
	else
	{
		printf("Decrypt failed: %d", GetLastError());
	}

	vector<char> res(DataVerify.pbData, DataVerify.pbData + DataVerify.cbData);

	for (vector<char>::const_iterator i = res.begin(); i != res.end(); ++i)
	{
		printf("%c", *i);
	}
	printf("\n");

	LocalFree(DataVerify.pbData);


	//DATA_BLOB dbIn;
	//DATA_BLOB dbOut;

	//BYTE *pbDataInput = (BYTE *)"Hello world of data protection.";
	//DWORD cbDataInput = strlen((char *)pbDataInput) + 1;

	//dbIn.cbData = cbDataInput;
	//dbIn.pbData = pbDataInput;

	///*
	//
	// * pDataIn			[in]			A pointer to a DATA_BLOB structure that contains the
	// *									plaintext to be encrypted.
	// * szDataDescr		[in, optional]	A string with a readable description of the data to be
	// *									encrypted. This description string is included with the
	// *									encrypted data. This parameter is optional and can be set
	// *									to NULL.
	// * pOptionalEntropy	[in, optional]	A pointer to a DATA_BLOB structure that contains a
	// *									password or other additional entropy used to encrypt the
	// *									data. The DATA_BLOB structure used in the encryption phase
	// *									must also be used in the decryption phase. This parameter
	// *									can be set to NULL for no additional entropy.
	// *									For information about protecting passwords, see Handling Passwords.
	// * pvReserved		[in]			Reserved for future use and must be set to NULL.
	// * pPromptStruct	[in, optional]	A pointer to a CRYPTPROTECT_PROMPTSTRUCT structure that
	// *									provides information about where and when prompts are to
	// *									be displayed and what the content of those prompts should
	// *									be. This parameter can be set to NULL in both the
	// *									encryption and decryption phases.
	// * dwFlags			[in] 			This parameter can be one of the following flags.


	//*/

	//DWORD dwFlags = CRYPTPROTECT_UI_FORBIDDEN;

	//CryptProtectData(&dbIn, NULL, NULL, NULL, NULL, dwFlags, &dbOut);

	//LocalFree(dbOut.pbData);






    return 0;
}

