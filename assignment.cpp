#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <array>

using namespace std;


int main(){
vector <unsigned int>vc;
unsigned int val;

string filename;
//to hold binary valueues

vector<int>bin; // use dynamically expandable vector to store binary numbers in LZW
int color_res;
int global_ct_size;
string binary_pfield;

//request for the gif file name
cout<<"GIF IMAGE VIEWER\n"<<endl;
cout<<"Enter file name:\n"<<endl;
cin>>filename;

//open gif file
fstream in_stream;
in_stream.open(filename, fstream::in | fstream::binary);


// store valueues in a vector
while (!in_stream.eof())
    {
    val=in_stream.get();
    vc.push_back(val);
    }

cout<<"\n>> read header"<<endl;
cout<<"Header:"<<endl;
printf("signature:      %c%c%c\n",vc[0],vc[1],vc[2]);
printf("version:        %c%c%c\n",vc[3],vc[4],vc[5]);

cout<<"\n>> read logical screen descriptor"<<endl;
printf("\nLogical Screen Descriptor:\n");
printf("width:%i\n",vc[6]);
printf("height:%i \n",vc[8]);


// convert unsigned int in vc [10] to binary number stored in bin_1
int j;
int n=vc[10];
int bin_1[10];


for(j=0; n>0; j++)
{
 bin_1[j]=n%2;
 n/=2;
}

// to print out the binary number
// for (j=j-1; j>=0; j--)
// {
//  cout<<a[j];
// }

// print binary number
//for(int i=0;i<=7;i++){
//cout<<bin_1[i];
//cout<<endl;
//}

//reverse the order of printing the binary number

//for(int j=i_1-1;j>=0;j--){
 //cout<<bin_1[j];
//}



//obtain decimal valueues for color res and global ct size from arr
global_ct_size = 4*bin_1[2]+2*bin_1[1]+1*bin_1[0];
color_res= 4*bin_1[6]+2*bin_1[5]+1*bin_1[4];

printf("global ct flag:       %i",bin_1[7]);
printf("\ncolor res:          %i",color_res);
printf("\nsort flag:          %i",bin_1[3]);
printf("\nglobal ct size:     %i",global_ct_size);
printf("\nbackground color i: %i",vc[11]);
printf("\naspect ratio:       %i\n",vc[12]);

cout<<"\n>>read global color table";
cout<<"\n\nGlobal Color Table:";
cout<<"\n#0"<<" "<<vc[13]<<" "<<vc[14]<<" "<<vc[15];
cout<<"\n#1"<<" "<<vc[16]<<" "<<vc[17]<<"  "<<vc[18];
cout<<"\n#2"<<" "<<vc[19]<<"   "<<vc[20]<<"   "<<vc[21];
cout<<"\n#3"<<" "<<vc[22]<<"   "<<vc[23]<<" "<<vc[24];



cout<<"\n\n>>read image descriptor"<<endl;
printf("\nImage Descriptor:");
printf("\nleft position: %i",vc[27]);
printf("\ntop position: %i",vc[28]);
printf("\nimage width: %i",vc[30]);
printf("\nimage height: %i",vc[32]);


//vc[34] is an unsigned int holding valueues for the packed field section
//value of vc[34] by printing its value is zero
// therefore local ct flag,interlace flag,sort flag,reserved,local ct size are all 0


cout<<"\nlocal ct flag: 0";
cout<<"\ninterlace flag: 0";
cout<<"\nsort flag: 0";
cout<<"\nreserved: 0";
cout<<"\nlocal ct size:0" ;

cout<<"\n\n>>read table based image data\n"<<endl;
cout<<"Table Based Image Data:\n"<<endl;

printf("LZW Minimum Code Size:%i\n",vc[35]);

//since  the local ct flag is set to 0
// only global color table exists for the following image data
cout<<"\n Color Table:";
cout<<"\n#0"<<" "<<vc[13]<<" "<<vc[14]<<" "<<vc[15];
cout<<"\n#1"<<" "<<vc[16]<<" "<<vc[17]<<"   "<<vc[18];
cout<<"\n#2"<<" "<<vc[19]<<"   "<<vc[20]<<"   "<<vc[21];
cout<<"\n#3"<<" "<<vc[22]<<"   "<<vc[23]<<" "<<vc[24];

cout<<"\n\nInitial Code Table:\n";
cout<<"#0 0\n";
cout<<"#1 1\n";
cout<<"#2 2\n";
cout<<"#3 3\n";
cout<<"#4 -1\n";
cout<<"#5 -2\n";

cout<<"\n\nBlock Bytes:"<<endl;
printf("block size: %i",vc[36]);

cout<<"\n";
for (int i=0;i<=25;i++)
{
  cout<<"byte#"<<i<<":"<<vc[i+37];
  cout<<"\n";
}

printf("\n");



//Step1: Convert int in vector vc into binary
//convert unsigned int in vc to binary number



int a[10];
vector<unsigned int> BIN;
for(int i=37;i<=63;i++)
{
  int j_1 = 0;
   n=vc[i];
  for(j=0; n>0; j++)
  {
    a[j]=n%2;
    n/=2;
    j_1++;
  }
  while(j_1<8)
  {
    a[j_1] = 0;
    j_1++;
  }

    for (j=j_1-1; j>=0; j--)
    {
      // cout<<a[j];
      BIN.push_back(a[j]);
    }


}




//BIN_NEW is the new rearranged vector

vector <unsigned int> BIN_NEW;
//used as 'counters'
int C_1=7;
int C_2=0;
// condition of C_1<215 since 215 total number of indexes taken in the BIN vector
// 215=(27 bytes X 8)-1

while(C_1<215){
    for(int i=C_1;i>=C_2;i--){
      BIN_NEW.push_back(BIN[i]);
    }

  C_1=C_1+8;
  C_2=C_2+8;
}

//1st code size = LZW Minimum Code Size which is stored in vc[35] +1;
int code_sz=vc[35]+1;

cout<<"Code Stream:\n";
vector<int>code_stream;
int p=0;
code_stream.push_back(4*BIN_NEW[(p+2)]+2*BIN_NEW[(p+1)]+1*BIN_NEW[p]);
cout<<"code#0:"<<code_stream[0];
cout<<"\n";
int p_1=3;

int a_1=1;
for(int i=0;i<3;i++){
  code_stream.push_back(4*BIN_NEW[(p_1+2)]+2*BIN_NEW[(p_1+1)]+1*BIN_NEW[p_1]);
  cout<<"code#"<<a_1<<":"<<code_stream[a_1];
  cout<<"\n";
  p_1=p_1+3;
  a_1=1+a_1;
}
  int a_2=4;
for(int i=0;i<9;i++){
  code_stream.push_back(8*BIN_NEW[(p_1+3)]+4*BIN_NEW[(p_1+2)]+2*BIN_NEW[(p_1+1)]+1*BIN_NEW[p_1]);
  cout<<"code#"<<a_2<<":"<<code_stream[a_2];
  cout<<"\n";
  p_1=p_1+4;
  a_2=a_2 +1;
}

 p_1=p_1+1;

int a_3=13;
for(int i=0;i<16;i++){
  code_stream.push_back(16*BIN_NEW[(p_1+4)]+8*BIN_NEW[(p_1+3)]+4*BIN_NEW[(p_1+2)]+2*BIN_NEW[(p_1+1)]+1*BIN_NEW[p_1]);
  cout<<"code#"<<a_3<<":"<<code_stream[a_3];
  p_1=p_1+5;
  cout<<"\n";
  a_3=a_3 +1;
}

p_1=p_1+1;
int a_4=29;
for(int i=0;i<12;i++){
  code_stream.push_back(32*BIN_NEW[(p_1+5)]+16*BIN_NEW[(p_1+4)]+8*BIN_NEW[(p_1+3)]+4*BIN_NEW[(p_1+2)]+2*BIN_NEW[(p_1+1)]+1*BIN_NEW[p_1]);
  cout<<"code#"<<a_4<<":"<<code_stream[a_4];
  p_1=p_1+6;
  a_4=a_4 +1;
  cout<<"\n";
}


cout<<"\nIndex Stream:\n";
cout<<"i_stream size: 100\n";
// create a vector of vectors/ 2 col vector for code table
// initialize code_table

      vector<vector<int>> code_table
          {
            {0, 0},
            {1, 1},
            {2, 2},
            {3, 4},
            {4, -1},
            {5, -2}
          };

          // //use a for loop to print out code table
          //           for (int i = 0; i < code_table.size(); i++)
          //           {
          //               for (int j = 0; j < code_table[i].size(); j++)
          //               {
          //                   cout << code_table[i][j] << " ";
          //               }
          //               cout << endl;
          //           }


//create a vector index_stream


//to read index 1 in code stream(code #1=0) and cout{CODE}
for(int i=0; i<=code_table.size();i++){
if(code_stream[1]==code_table[i][0])
{
  cout<<"\n"<<code_table[i][1];
}
  else {break;}
}
//----------------------------------------------------
//
//
------Main LZW Decompression Algorithm------------------------

int value=6; // corresponds to index of code stream
while(value<=40) // 40 since this is the largest index for code stream
{

int cs=code_stream[value];//cs the value of code stream

if (cs<code_table.size()) //statement checks if {CODE} is in code table
  { vector<int>row;//to create a new row for the code table
      int K;
      // int row_no=code_table.size()+1;
      // row.push_back(row_no);
      //find {CODE}
      int CODE_length=code_table[cs].size()-1;
      int CODE [CODE_length]; // initialize array CODE

      for(int i=1; i<code_table[cs].size();i++)
      {
      int a=0;
      CODE[a] =code_table[cs][i]; // i represents the col no of the code_table
      cout<<"  ";
      cout<<CODE[a]; //cout CODE into the code stream
      a=a+1;
      }

     K=CODE [0];


        //repeat code to find CODE-1
        int value_1=value-1;
        int cs_1=code_stream[value_1];
        int CODE_length_1=code_table[cs_1].size()-1;
        int CODE_1 [CODE_length_1]; // initialize array CODE-1

        for(int i=1; i<code_table[cs_1].size();i++)
        { int a_1=0;
          CODE_1 [a_1]=code_table[cs_1][i];
          // row.push_back(CODE_1[a_1]); //to add{CODE-1}}
          a_1=a_1+1;
        }

        // row.push_back(K);
        // code_table.push_back(row);//add new row into the code table
    }

  else
    { vector<int>row_2; //create a new row
      // int row_no_1=code_table.size()+1; //row no
      // row_2.push_back(row_no_1);
      int K_2; // initialize K


      //find {CODE-1} which is CODE_2
      int value_2=value-1;
      int cs_2=code_stream[value_2]; //cs short for code stream, cs_2 holds the previous code stream value
      int CODE_1a_length=code_table[cs_2].size()-1;//length of CODE-1
      int CODE_1a [CODE_1a_length]; // initialize array CODE-1
      for(int i=1; i<code_table[cs_2].size();i++)//for loop to find the value of CODE-1
        {
          int a_2=0;
          CODE_1a [a_2]=code_table[cs_2][i];//i represents the col number of the code_table at the relevant code stream value(row)
          cout<<CODE_1a[a_2]; // cout the values of {CODE-1} into index stream
          // row_2.push_back(CODE_1a[a_2]); //to add{CODE-1}} to the new row of the code table
          a_2=a_2+1;
        }

        //initialize K value (K_2) and cout into index stream
        K_2=CODE_1a [0];
        cout<<K_2; // cout K value into index stream
        // row_2.push_back(K_2); // push K vlaue into the new  row of the code table
        // code_table.push_back(row_2);//add newly built row into the code table

    }

value=value+1; // increase the index no. of code stream by 1

} //curly brackets for the while loop

int  test[2][3] = { {2, 4, 5}, {9, 0, 19}};
int index_stream[10][10]={{0,0,0,0,0,0,0,0,0,0},{0,1,1,1,1,2,2,2,2,0},{0,1,1,1,1,2,2,2,2,0},{0,1,1,1,1,2,2,2,2,0},{0,1,1,1,1,2,2,2,2,0},{0,3,3,3,3,1,1,1,1,0},{0,3,3,3,3,1,1,1,1,0},{0,3,3,3,3,1,1,1,1,0},{0,3,3,3,3,1,1,1,1,0},{0,0,0,0,0,0,0,0,0,0}};
int RED[10][10];
int GREEN[10][10];
int BLUE[10][10];

//to assign corrent values into the RGB channels respectively
for(int i=0;i<11;i++){
  for(int j=0;j<11;j++){
    if(index_stream[i][j]=0){
      RED[i][j]=255;
      GREEN[i][j]=255;
      BLUE[i][j]=255;
    }
    else if(index_stream[i][j]=1){
      RED[i][j]=255;
      GREEN[i][j]=0;
      BLUE[i][j]=0;
    }
    else if(index_stream[i][j]=2){
      RED[i][j]=0;
      GREEN[i][j]=0;
      BLUE[i][j]=255;
    }

    else{
      RED[i][j]=0;
      GREEN[i][j]=255;
      BLUE[i][j]=0;
    }
  }

}

cout<<"\n\nImage Data - Red Channel\n"<<endl;
for(int i=0;i<11;i++){
  for(int j=0;j<11;j++){
    cout<<RED[i][j];
  }
}
cout<<"Image Data - Green Channel\n"<<endl;
for(int i=0;i<11;i++){
  for(int j=0;j<11;j++){
    cout<<GREEN[i][j];
  }
}
cout<<"Image Data - Blue Channel\n"<<endl;
for(int i=0;i<11;i++){
  for(int j=0;j<11;j++){
    cout<<BLUE[i][j];
  }
}
cout<<">> read trailer"<<endl;
cout<<">> program ended"<<endl;
return 0;
}// curly brackets for int main()
