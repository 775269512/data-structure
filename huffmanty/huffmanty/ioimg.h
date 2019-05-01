#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;
int extract(HuffNode huf_tree[], char *ifname, char *ofname);
int compress(HuffNode huf_tree[], int n, long flength, char *ifname, char *ofname);

