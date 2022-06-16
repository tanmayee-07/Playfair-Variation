#include<iostream>
#include<string.h>
#include<vector>
using namespace std;
char matrix[6][6];
vector<char> nu = { '0','1','2','3','4','5','6','7','8','9','_' };
string ch="abcdefghijklmnoprstuvwxyz";
string result;
char plain[50];
char encrypt[50];
char decrypt[50];
char sig[100];
bool isDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    return false;
}

void checkChar(int b,int j){
    int k=0;
    while(result.find(ch[k])!=-1){
        k++;
    }
    string test=string(1,ch[k]);
    result=result+test;
    matrix[b][j]=ch[k];
}

void checkNumber(int b,int j){
    int k=0;
    while(result.find(nu[k])!=-1){
        k++;
    }if(k<11){
    string test=string(1,nu[k]);
    result=result+test;
    matrix[b][j]=nu[k];
    }
    else
    checkChar(b,j);
}

void decryption(char encrypt[],int num){
    int length=0;
    for(length=0;sig[length]!='\0';length++);
    char sigfull[100];
    int sizep=strlen(plain);
    for(int i=0;i<sizep;i++){
        sigfull[i]=sig[i%length];
    }
    for(int i=0; i<sizep; i=i+2)
    {
            if(sigfull[i]==sigfull[i+1]){
                if(sigfull[i]=='+'){
                    sigfull[i]='-';
                    sigfull[i+1]='-';
                }
                else if(sigfull[i]=='-'){
                    sigfull[i]='+';
                    sigfull[i+1]='+';
                }
            }
    }
    for(int i=0; i<sizep; i++)
        if(sigfull[i]=='~')
        {
                sigfull[i]='-';
                sigfull[i+1]='-';
                sigfull[i+length]='+';
                sigfull[i+length+1]='+';
                i=i+length+1;
        }
    cout<<endl<<"\nDecrypted text: "<<endl;
    for(int i=0;i<num;i++){
        for(int j=0;j<6;j++){
            for(int k=0;k<6;k++){
                if(matrix[j][k]==encrypt[i]){
                    if(sigfull[i]=='+')
                    decrypt[i]=matrix[j][(k+1)%6];
                    if(sigfull[i]=='-'){
                        if(k-1<=-1){
                        int t=k-1+6;
                        decrypt[i]=matrix[j][t%6];
                        }
                        else
                        decrypt[i]=matrix[j][(k-1)%6];
                    }
                }
            }
        }
    }
    for(int i=0;i<num;i++)
    cout<<decrypt[i];
    
    
}

void encryption(char sigfull[50],int num)
{
    cout<<endl<<"\nEncrypted text: "<<endl;
    for(int i=0;i<num;i++){
        for(int j=0;j<6;j++){
            for(int k=0;k<6;k++){
                if(matrix[j][k]==plain[i]){
                    if(sigfull[i]=='+')
                    encrypt[i]=matrix[j][(k+1)%6];
                    if(sigfull[i]=='-'){
                        if(k-1<=-1){
                        int t=k-1+6;
                        encrypt[i]=matrix[j][t%6];
                        }
                        else
                        encrypt[i]=matrix[j][(k-1)%6];
                    }
                }
            }
        }
    }
    for(int i=0;i<16;i++)
    cout<<encrypt[i];
    decryption(encrypt,num);
}

void sign(float phi[50],int num)
{
    int i;
    int sizep=strlen(plain);
    char sigfull[100];
    for(i=0; i<num; i++)
    {
        if(phi[i]==0)
            sig[i]='~';
        else if(phi[i]<0)
            sig[i]='-';
        else
            sig[i]='+';
    }
    for(i=0;i<sizep;i++){
        sigfull[i]=sig[i%num];
    }
    cout<<"\nSigns of offset of prime numbers: "<<endl;
    for(i=0;i<num;i++){
        cout<<sig[i]<<" ";
    }
    cout<<endl<<"\nSigns alloted to the plain text: "<<endl;
    for(i=0;i<sizep;i++){
        cout<<sigfull[i];
        if(i%2!=0)
            printf(" ");
    }
    for(int i=0; i<sizep; i++)
    {
        if(i%2==0)
            if(sigfull[i]=='-')
                if(sigfull[i+1]=='+')
                {
                    sigfull[i]='+';
                    sigfull[i+1]='-';
                }
    }
    for(int i=0; i<sizep; i++)
        if(sigfull[i]=='~')
        {
                sigfull[i]='+';
                sigfull[i+1]='+';
                sigfull[i+num]='-';
                sigfull[i+num+1]='-';
                i=i+num+1;
        }
    cout<<"\n\nText to be encrypted: ";
    for(int i=0; plain[i]; i++)
    {
        putchar(plain[i]);
        if(i%2!=0)
            printf(" ");
    }
    cout<<"\nSigns: \t\t      ";
    for(i=0;i<sizep;i++){
        cout<<sigfull[i];
        if(i%2!=0)
            printf(" ");
    }
    encryption(sigfull,sizep);
}

void offsetcalc(float phi[], int num)
{
    float gr=1.6180339887;
    cout<<"\nOffset values: \n";
    for(int i=2; i<num; i++)
    {
        phi[i]=gr-phi[i];
    }
    for(int i=0; i<num; i++)
    {
        cout<<phi[i]<<"\n";
    }
    sign(phi,num);
}

void phicalc(int arr[],int num)
{
    float phi[num], temp;
    cout<<"\n\nPhi values: \n";
    phi[0]=0; phi[1]=0;
    for(int i=2; i<num; i++)
    {
        phi[i]=(float)arr[i]/arr[i-1];
    }
    for(int i=0; i<num; i++)
    {
        cout<<phi[i];
        cout<<"\n";
    }
    offsetcalc(phi, num);
}

void isprime(int arr[], int num)
{
    int i;
    for(i=0; i<num; i++)
    {
        bool isPrime = true;
        for(int j = 2; j< arr[i]; j++)
        {
            if(arr[i] % j == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (!isPrime)
        {
            for (int k = i; k < num; k++)
            {
                arr[k] = arr[k + 1];
            }
            i--;
            num--;
        }
    }
    cout<<"\nPrime Numbers in the sequence: ";
    for(i=0; i<num; i++)
    {
        cout<<arr[i]<<" ";
    }
    phicalc(arr,num);
}

void fibonacci(int number)
{
    int n1=0,n2=1,n3,i;
    int arr[number];
    arr[0]=0; arr[1]=1;
    for(i=2;i<number;++i)
    {
        n3=n1+n2;
        arr[i]=n3;
        n1=n2;
        n2=n3;
    }
    cout<<"\nFibonacci Sequence: ";
    for(i=0; i<number; i++)
    {
        cout<<arr[i]<<" ";
    }
     for(i = 0; i < number; i++) //removing duplicates
    {
        for(int j = i+1; j < number; )
        {
            if(arr[j] == arr[i])
            {
                for(int k = j; k < number; k++)
                {
                    arr[k] = arr[k+1];
                }
                number--;
            }
            else
            {
                j++;
            }
        }
    }
    isprime(arr,number);
}

string printDistict(string str){
    for(int i=0;str[i]!='\0';i++){
        for(int j=i+1;str[j]!='\0';j++){
            if(str[i]==str[j])
            str.erase(str.begin() + j);
        }
    }
    return(str);
}

void playfair()
{
    int i,j,k,a,b,size,start;
    int keyLen= result.length();
    cout<<"\nLength of keyword: "<<keyLen<<"\n";
    b=keyLen/6;
    for(i=0; i<6; i++){
    for(j=0; j<6; j++)
        matrix[i][j]='0';
    }
    int flag;
    for(i=0;i<=b;i++){
        for(j=0;j<6;j++){
            if((i==0&&result[j]=='\0')||(i>0&&result[j+6]=='\0')){
                start=j;
                flag=1;
                break;
            }
            else if(i==0){
                matrix[i][j]=result[j];
            }
            else{
                matrix[i][j]=result[j+6];
            }
        }
        if(flag==1)
        break;
    }
    for(j=start;j<6;j++){
        if(start%2==0){
            if(j%2==0){
                checkChar(b,j);
            }
            else{
                checkNumber(b,j);
            }
        }
        else{
            if(j%2==0){
                checkNumber(b,j);
            }
            else{
               checkChar(b,j);
            }
        }
    }
    for(i=b+1;i<6;i++){
        for(j=0;j<6;j++){
            int n=result.length();
            if(isDigit(result[n-1])){
                  checkChar(i,j);
            }
            else{
                    checkNumber(i,j);
            }
        }
    }
    cout<<"\nPLAYFAIR MATRIX:\n\n";
    for(i=0; i<6; i++){
    for(j=0; j<6; j++)
        cout<<matrix[i][j]<<" ";
    cout<<'\n';
    }
}

int main() {
    int number, size,i,j;
    string str;
    cout<<"\nEnter the key: ";
    getline(cin, str);
    cout<<"Enter plain text: ";
    cin>>plain;
    size=strlen(plain);
    int count=0;
    for(i=0; plain[i]; i++)
    {
        if(plain[i]!=' ')
            plain[count++]=plain[i];
    }
    plain[count]='\0';
    for(i=0; i<size; i++)
    {
        if(plain[i]==plain[i+1])
        {
            plain[i+1]='z';
        }
    }
    size=strlen(plain);
    if((size%2)!=0)
    {
        plain[size]='z';
        plain[size+1]='\0';
    }
    cout<<"Enter a prime number: ";
    cin>>number;
    string strf = to_string(number);
    str=str+strf;
    result=printDistict(str);
    playfair();
    fibonacci(number);
    return 0;
}
