#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef unsigned long long int bignum;
int const F=4;

void option1();
void option2();
int menu();
int ascii(int num);
void Key(ifstream & ifile, int & pwd, bignum & key);
void Encrypt(ifstream & ifile, ofstream & ofile, bignum & key, string & name);
void Decrypt(ifstream & ifile, ofstream & ofile, bignum & k, string & name);
void out(ofstream & ofile, string & word, bignum & key);

int main(){
  int op=menu();
  while(op>0){
    if(op==1) option1();
    else if(op==2) option2();
    op=menu();
  }
  return 0;
}

int menu(){
  int num;
  cout<<"1-) Encrypt"<<endl;
  cout<<"2-) Decrypt"<<endl;
  cout<<"0-) Exit"<<endl;
  cin>>num;
  return num;
}
int ascii(int num){
  return num%223+32;
}

void Key(ifstream & ifile, int & pwd, bignum & k){
  string base="Primes";
  string txt=".txt";
  for(int i=1;i<F;i++){
    bignum cont=0;
    string name=base+to_string(i)+txt;
    ifile.open(name);
    if(ifile.is_open()){
      for(bignum j=0;j<pwd;j++){
        ifile.ignore();
      }
      ifile>>cont;
      k*=cont;
      ifile.close();
    }else{
      cout<<"Files don't exist"<<endl;
    }
  }
}


void Encrypt(ifstream & ifile, ofstream & ofile, bignum & key, string & name){
  string on;
  cout<<"Name output file: ";
  cin>>on;
  ifile.open(name);
  ofile.open(on);
  string word;
  ifile>>word;
  while(!ifile.fail()){
    out(ofile, word, key);
    ifile>>word;
  }
  ofile.close();
  cout<<"The file was encrypted succesfully"<<endl;
}

void out(ofstream & ofile, string & word, bignum & key){
  for(int i=0;i<word.length();i++){
    bignum num=(bignum)word.at(i)*key;
    ofile<<num<<" ";
  }
}

void option1(){
  string password;
  string name;
  ifstream ifile;
  ofstream ofile;
  bignum k=1;
  int pwd=0;
  cout<<"Name of the file you want to encrypt: ";
  cin>>name;
  cout<<endl<<"Enter the password: ";
  cin>>password;
  for(int i=0;i<password.length();i++){
    pwd+=(int)password.at(i);
  }
  Key(ifile,pwd,k);
  cout<<"Do you want to see your PwdKey? (Y/n): ";
  char show;
  cin>>show;
  if(show=='y'|| show=='Y'){
    cout<<"Your PwdKey is: "<<pwd<<endl;
  }else cout<<"ok!"<<endl;
  Encrypt(ifile,ofile,k,name);
}


void option2(){
  system("ls");
  bignum k=1;
  string name;
  string password;
  ifstream ifile;
  ofstream ofile;
  int PwdKey=0;
  cout<<"Name of the file you want to decrypt: ";
  cin>>name;
  cout<<"Enter the password: ";
  cin>>password;
  for(int i=0;i<password.length();i++){
    PwdKey+=(int)password.at(i);
  }
  Key(ifile, PwdKey, k);
  Decrypt(ifile, ofile,k,name);

}

void Decrypt(ifstream & ifile, ofstream & ofile, bignum & k, string &name){
  ifile.open(name);
  if(ifile.is_open()){
    string on;
    cout<<"Name de output file: ";
    cin>>on;
    ofile.open(on);
    while(!ifile.fail()){
      bignum chr;
      ifile>>chr;
      if(!ifile.fail()){
        int c=chr/k;
        ofile<<(char)c<<" ";
      }

    }
    cout<<"The file was decrypted succesfully"<<endl;
    ofile.close();
  }else{
    cout<<"File is not found"<<endl;
  }
}
