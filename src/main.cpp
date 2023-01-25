#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

#define TWENTY_FOUR 24
#define EPSILON 0.001

string buffer[4];
fstream my_file;
float numbers[4];
char opp[4] = {'+','-','*','/'};
int counter24 = 0;
float result_1,result_2,result_3;
char opp_1,opp_2,opp_3;

#define validInput(x) if (abs(x-TWENTY_FOUR) < EPSILON)

uint64_t theTime() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int rangeInput(int x){
    return (x >= 1 && x <=13);
}

void swap(float *a, float*b){
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int strToInt(string x){
    if (x == "A") return 1;
    else if (x == "2") return 2;
    else if (x == "3") return 3;
    else if (x == "4") return 4;       
    else if (x == "5") return 5;      
    else if (x == "6") return 6;     
    else if (x == "7") return 7;       
    else if (x == "8") return 8;       
    else if (x == "9") return 9;       
    else if (x == "10") return 10;       
    else if (x == "J") return 11;      
    else if (x == "Q") return 12;     
    else if (x == "K") return 13;  
    else return -1;    
}

string f_i_str(float y){ //Convert float menjadi string integer
    return to_string((int) y);
}

void displayOption(){
    cout << "\nMasukkan pilihan anda:\n";
    cout << "1. Random\n";
    cout << "2. Input User\n";
    cout << "3. Exit Program\n\n";
}

void single_operator(float x, float y, float *result, int num_op, char *op){
    switch (num_op)
    {
    case 0:
        *result = x+y;
        *op = opp[0];
        break;
    case 1:
        *result = x-y;
        *op = opp[1];
        break;
    case 2:
        *result = x*y;
        *op = opp[2];
        break;
    case 3:
        *result = x/y;
        *op = opp[3];
        break;
    default:
        break;
    }
}

void double_operator(float x, float y, float z, float *result, int num_op, char *op1, char*op2){
    switch (num_op)
    {
    case 0:
        *result = x+y+z; // ++
        *op1 = opp[0];
        *op2 = opp[0];
        break;
    case 1:
        *result = x+y-z; // +-
        *op1 = opp[0];
        *op2 = opp[1];
        break;
    case 2:
        *result = x+y*z; // +*
        *op1 = opp[0];
        *op2 = opp[2];
        break;
    case 3:
        *result = x+y/z; // +/
        *op1 = opp[0];
        *op2 = opp[3];
        break;
    case 4:
        *result = x-y+z; // -+
        *op1 = opp[1];
        *op2 = opp[0];
        break;
    case 5:
        *result = x-y-z; // --
        *op1 = opp[1];
        *op2 = opp[1];
        break;
    case 6:
        *result = x-y*z; // -*
        *op1 = opp[1];
        *op2 = opp[2];
        break;
    case 7:
        *result = x-y/z; // -/
        *op1 = opp[1];
        *op2 = opp[3];
        break;
    case 8:
        *result = x*y+z; // *+
        *op1 = opp[2];
        *op2 = opp[0];
        break;
    case 9:
        *result = x*y-z; // *-
        *op1 = opp[2];
        *op2 = opp[1];
        break;
    case 10:
        *result = x*y*z; // **
        *op1 = opp[2];
        *op2 = opp[2];
        break;
    case 11:
        *result = x*y/z; // */
        *op1 = opp[2];
        *op2 = opp[3];
        break;
    case 12:
        *result = x/y+z; // /+
        *op1 = opp[3];
        *op2 = opp[0];
        break;
    case 13:
        *result = x/y-z; // /-
        *op1 = opp[3];
        *op2 = opp[1];
        break;
    case 14:
        *result = x/y*z; // /*
        *op1 = opp[3];
        *op2 = opp[2];
        break;
    case 15:
        *result = x/y/z; // //
        *op1 = opp[3];
        *op2 = opp[3];
        break;
    default:
        break;
    }
}

void theSolution(float arr[],int *state,string *res){
    for(int h = 0; h < 10; h++){
        switch (h)
        {
        /*1 Group of 2*/
        case 0: // (a op b) op c op d
            for(int i = 0; i < 4; i++){
                single_operator(arr[0],arr[1],&result_1,i,&opp_1);
                for(int j = 0; j < 16; j++){
                    double_operator(result_1,arr[2],arr[3],&result_2,j,&opp_2,&opp_3);
                    validInput(result_2){
                        counter24++;
                        // cout << "(" << arr[0] << opp_1 << arr[1] << ")" << opp_2 << arr[2] << opp_3 << arr[3] << "\n";
                        *res = *res + '(' + f_i_str(arr[0]) + opp_1  + f_i_str(arr[1]) + ')' + opp_2 + f_i_str(arr[2])  + opp_3 + f_i_str(arr[3]) + '\n';
                    }
                }
            }
            break;
        case 1: // a op (b op c) op d
            for(int i = 0; i < 4; i++){
                single_operator(arr[1],arr[2],&result_1,i,&opp_2);
                for(int j = 0; j < 16; j++){
                    double_operator(arr[0],result_1,arr[3],&result_2,j,&opp_1,&opp_3);
                    validInput(result_2){
                        counter24++;
                        // cout << arr[0] << opp_1 << "(" << arr[1]  << opp_2 << arr[2] << ")" << opp_3 << arr[3] << "\n";
                        *res = *res + f_i_str(arr[0]) + opp_1 + '(' + f_i_str(arr[1]) + opp_2 + f_i_str(arr[2]) +  ')' + opp_3 + f_i_str(arr[3]) + '\n';
                    }
                }
            }
            break;
        case 2: // a op b op (c op d)
            for(int i = 0; i < 4; i++){
                single_operator(arr[2],arr[3],&result_1,i,&opp_3);
                for(int j = 0; j < 16; j++){
                    double_operator(arr[0],arr[1],result_1,&result_2,j,&opp_1,&opp_2);
                    validInput(result_2){
                        counter24++;
                        // cout << arr[0] << opp_1 << arr[1]  << opp_2 << "(" << arr[2] << opp_3 << arr[3] << ")\n";
                        *res = *res + f_i_str(arr[0]) + opp_1  + f_i_str(arr[1]) + opp_2 + '(' + f_i_str(arr[2])  + opp_3 + f_i_str(arr[3]) + ")\n";
                    }
                }
            }
            break;

        /*1 Group of 3*/
        case 3: // (a op b op c) op d 
            for(int i = 0; i < 16; i++){
                double_operator(arr[0],arr[1],arr[2],&result_1,i,&opp_1,&opp_2);
                for(int j = 0; j < 4; j++){
                    single_operator(result_1,arr[3],&result_2,j,&opp_3);
                    validInput(result_2){
                        counter24++;
                        // cout << "(" << arr[0] << opp_1 << arr[1]  << opp_2  << arr[2] << ")" << opp_3 << arr[3] << "\n";
                        *res = *res + '(' + f_i_str(arr[0]) + opp_1  + f_i_str(arr[1]) + opp_2  + f_i_str(arr[2]) + ')' + opp_3 + f_i_str(arr[3]) + '\n';
                    }
                }
            }
            break;
        case 4: //((a op b) op c) op d
            for(int i = 0; i < 4; i++){
                single_operator(arr[0],arr[1],&result_1,i,&opp_1);
                for(int j = 0; j < 4; j++){
                    single_operator(result_1,arr[2],&result_2,j,&opp_2);
                    for(int k = 0; k < 4; k++){
                        single_operator(result_2,arr[3],&result_3,k,&opp_3);
                        validInput(result_3){
                            counter24++;
                            // cout << "((" << arr[0] << opp_1 << arr[1] << ")" << opp_2 << arr[2] << ")" << opp_3 << arr[3] << "\n";
                            *res = *res + "((" + f_i_str(arr[0]) + opp_1  + f_i_str(arr[1]) + ')' + opp_2  + f_i_str(arr[2]) + ')'  + opp_3 + f_i_str(arr[3]) + '\n';
                        }
                    }
                }
            }
            break;
        case 5: //(a op (b op c)) op d
            for(int i = 0; i < 4; i++){
                single_operator(arr[1],arr[2],&result_1,i,&opp_2);
                for(int j = 0; j < 4; j++){
                    single_operator(arr[0],result_1,&result_2,j,&opp_1);
                    for(int k = 0; k < 4; k++){
                        single_operator(result_2,arr[3],&result_3,k,&opp_3);
                        validInput(result_3){
                            counter24++;
                            // cout << "(" << arr[0] << opp_1 << "(" << arr[1] << opp_2 << arr[2] << "))" << opp_3 << arr[3] << "\n";
                            *res = *res + '(' + f_i_str(arr[0]) + opp_1 + '(' + f_i_str(arr[1])  + opp_2  + f_i_str(arr[2]) + "))" + opp_3  + f_i_str(arr[3]) + '\n';
                        }
                    }
                }
            }
            break;
        case 6: // a op (b op c op d)
            for(int i = 0; i < 16; i++){
                double_operator(arr[1],arr[2],arr[3],&result_1,i,&opp_2,&opp_3);
                for(int j = 0; j < 4; j++){
                    single_operator(arr[0],result_1,&result_2,j,&opp_1);
                    validInput(result_2){
                        counter24++;
                        // cout << arr[0] << opp_1 << "(" << arr[1]  << opp_2  << arr[2] << opp_3 << arr[3] << ")\n";
                        *res = *res  + f_i_str(arr[0]) + opp_1 + '(' + f_i_str(arr[1])  + opp_2  + f_i_str(arr[2])  + opp_3  + f_i_str(arr[3]) + ")\n";
                    }
                }
            }
            break;
        case 7: // a op ((b op c) op d)
            for(int i = 0; i < 4; i++){
                single_operator(arr[1],arr[2],&result_1,i,&opp_2);
                for(int j = 0; j < 4; j++){
                    single_operator(result_1,arr[3],&result_2,j,&opp_3);
                    for(int k = 0; k < 4; k++){
                        single_operator(arr[0],result_2,&result_3,k,&opp_1);
                        validInput(result_3){
                            counter24++;
                            // cout<< arr[0] << opp_1 << "((" << arr[1] << opp_2  << arr[2] << ")" << opp_3 << arr[3] << ")\n";
                            *res = *res  + f_i_str(arr[0]) + opp_1 + "((" + f_i_str(arr[1])  + opp_2  + f_i_str(arr[2])  + ')' + opp_3  + f_i_str(arr[3]) + ")\n";
                        }
                    }
                }
            }
            break;
        case 8:// a op (b op (c op d))
            for(int i = 0; i < 4; i++){
                single_operator(arr[2],arr[3],&result_1,i,&opp_3);
                for(int j = 0; j < 4; j++){
                    single_operator(arr[1],result_1,&result_2,j,&opp_2);
                    for(int k = 0; k < 4; k++){
                        single_operator(arr[0],result_2,&result_3,k,&opp_1);
                        validInput(result_3){
                            counter24++;
                            // cout<< arr[0] << opp_1 << "(" << arr[1] << opp_2 << "("<< arr[2]  << opp_3 << arr[3] << "))\n";
                            *res = *res  + f_i_str(arr[0]) + opp_1 + "(" + f_i_str(arr[1])  + opp_2  + '(' + f_i_str(arr[2])   + opp_3  + f_i_str(arr[3]) + "))\n";
                        }
                    }
                }
            }
            break;

        /*2 Group of 2*/
        case 9: //(a op b) op (c op d)
            for(int i = 0; i < 4; i++){
                single_operator(arr[0],arr[1],&result_1,i,&opp_1);
                for(int j = 0; j < 4; j++){
                    single_operator(arr[2],arr[3],&result_2,j,&opp_3);
                    for(int k = 0; k < 4; k++){
                        single_operator(result_1,result_2,&result_3,k,&opp_2);
                        validInput(result_3){
                            counter24++;
                            // cout<< "(" << arr[0] << opp_1  << arr[1] << ")" << opp_2 << "(" << arr[2]<< opp_3 << arr[3] << ")\n";
                            *res = *res  + '(' + f_i_str(arr[0]) + opp_1  + f_i_str(arr[1])  + ')' + opp_2  + '(' + f_i_str(arr[2])   + opp_3  + f_i_str(arr[3]) + ")\n";
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    *state = counter24;
}

void thePermutation(float arr[], int size, int n, int *state,string *res){
    if(n == 1){ //Basis
        theSolution(arr,state,res);
    }
    else{ // Rekurens
        float *bufferArr = (float*)malloc((size) * sizeof(float));
        //Copy Array 
        for(int k = 0; k < size; k++){
            bufferArr[k] = arr[k]; 
        }
        for(int w = size-n; w < size; w++){
            swap(&bufferArr[size-n],&bufferArr[w]);
            thePermutation(bufferArr,size,n-1,state,res);
        }
    
    }
}

void manual_input(){
    cout << "Masukkan 4 angka yang diperlukan:\n";
    int state = 1;
    for(int i = 0; i<4; i++){
        cin >> buffer[i];
        state &= rangeInput(strToInt(buffer[i]));
        numbers[i] = (float) strToInt(buffer[i]);
    }

    if(state){
        int state_2 = 0;
        string result = "";
        uint64_t tic = theTime();
        thePermutation(numbers,4,4,&state_2,&result);
        cout << "Waktu eksekusi: " << theTime()-tic << " milisekon\n";
        if(state_2){
            cout << "\nTerdapat " << counter24 << " solusi!\n";
            cout << result;
            cout << "Ingin menyimpan file? (Y/N)\n";
            char validate;
            cin >> validate;
            while(1){
                if(validate == 'y' || validate == 'Y'){
                    string w;
                    cout << "Masukkan nama file yang ingin disimpan: \n";
                    cin >> w;
                    my_file.open(w, ios::out);
                    if(!my_file) cout<< "File gagal disimpan!\n";
                    else{
                        cout << "File berhasil disimpan!\n";
                        result = f_i_str(numbers[0]) + " " + f_i_str(numbers[1]) + " " + f_i_str(numbers[2]) + " " + f_i_str(numbers[3]) + "\nTerdapat " + to_string(counter24) + " solusi!\n\n" + result;
                        my_file << result;
                        my_file.close();
                    }
                    break;
                }
                else if(validate == 'n' || validate == 'N') break;
                else{
                    cout << "Input tidak valid! Masukkan Y/N untuk menyimpan file.\n";
                    cin >> validate;
                }

            }
        } 
        else cout << "Tidak ada solusi!\n";
    } 
    else cout << "Input tidak valid!\n";

}

void random_input(){
    cout << "Meng-generate random numbers...\n";
    for(int i = 0; i<4; i++){
        numbers[i] = (float) (1 + rand()%13);
    }
    cout << "Berikut adalah bilangan random anda: ";
    for(int i = 0; i<4; i++) cout << numbers[i] << " ";
    cout << "\n";

    int state = 0;
    string result = "";
    uint64_t tic = theTime();
    thePermutation(numbers,4,4,&state,&result);
    cout << "Waktu eksekusi: " << theTime()-tic  << " milisekon\n";
    if(state) {
        cout << "\nTerdapat " << counter24 << " solusi!\n\n";
        cout << result;
        cout << "Ingin menyimpan file? (Y/N)\n";
        char validate;
        cin >> validate;
        while(1){
            if(validate == 'y' || validate == 'Y'){
                string w;
                cout << "Masukkan nama file yang ingin disimpan: \n";
                cin >> w;
                my_file.open(w, ios::out);
                if(!my_file) cout<< "File gagal disimpan!\n";
                else{
                    cout << "File berhasil disimpan!\n";
                    result = f_i_str(numbers[0]) + " " + f_i_str(numbers[1]) + " " + f_i_str(numbers[2]) + " " + f_i_str(numbers[3]) + "\nTerdapat " + to_string(counter24) + "solusi!\n\n" + result;
                    my_file << result;
                    my_file.close();
                }
                break;
            }
            else if(validate == 'n' || validate == 'N') break;
            else{
                cout << "Input tidak valid! Masukkan Y/N untuk menyimpan file.\n";
                cin >> validate;
            }
            
        }
    }
    else cout << "Tidak ada solusi!\n";
    
}


// MAIN PROGRAM
int main(){
    cout << "============================================\n";
    cout << "====Selamat datang di 24 Game Solver! :)====\n";
    cout << "============================================\n";
    while(1){
        int option;
        displayOption();
        cin >> option;
        cout << '\n';
        switch(option){
            case 1:
                random_input();
                break;
            case 2:
                manual_input();
                break;
            case 3:
                cout << "Terima kasih telah memakai program kami!\n";
                break;
            default:
                cout << "Input tidak valid!\n";
                break;
        }

        if(option == 3) break;
    }
        
    return 0;
}