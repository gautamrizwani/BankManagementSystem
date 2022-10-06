#ifndef CUST_STRUCT
#define CUST_STRUCT

struct Cust {
	int id;
	char name[50];
	char gender;
	int age;

	char uname[60]; //Format : name-id
	char passwd[30];

	int accountNo;
};

#endif
