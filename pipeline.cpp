#include <iostream>
#include <iomanip>
using namespace std;

#define INUM 6 /*需要流水处理的浮点加指令数目*/
#define SPACE 4     /*功能部件数目*/
#define TIME  INUM+(SPACE-1)   /*存储不同时间段各个功能部件内指令值*/

int ts[SPACE][TIME] = {0};/*初始化时空图*/
int __time = 1;
int ts1[SPACE][TIME] = {0};
void update(int i){
    for(int i=0;i<SPACE;i++){
        for(int j=0;j<TIME;j++){
            ts1[i][j] = ts[i][j];
        }
    }
    //已经将原属组复制给新数组
    for(int j=0;j<SPACE;j++){
        int flag = 0;
        for(int k=j;k<j+INUM;k++){
            if(ts[j][k] != 0){

                if(j+1<=i){
                    ts1[j+1][k+1] = ts[j][k];
                }
            }
            else if(flag == 0 && j == 0){
                flag = 1;
                ts1[j][k] = __time;
            }
        }
    }

    for(int i=0;i<SPACE;i++){
        for(int j=0;j<TIME;j++){
            ts[i][j] = ts1[i][j];
        }
    }
    
}



void show(){
    for(int i=SPACE-1;i>=0;i--){
        for(int j=0;j<TIME;j++){
            if(ts[i][j] == 0){
                cout<<"\t";
            }
            else{
                if(i == 0){
                    cout<<"ED"<<ts[i][j]<<"\t";
                }
                else if(i == 1){
                    cout<<"EA"<<ts[i][j]<<"\t";
                }
                else if(i == 2){
                    cout<<"MA"<<ts[i][j]<<"\t";
                }
                else if(i == 3){
                    cout<<"NL"<<ts[i][j]<<"\t";
                }
            }
        }
        cout<<endl;
    }
}

int main(){
    cout<<"----Demo the pipline for float point add.----"<<endl;
    cout<<"----We want to execute 5 float poing instructions----"<<endl;
    cout<<"Here, we display all the content in the pipeline: "<<endl;
    
    ts[0][0] = 1;
    cout<<"After time slice"<<__time<<":"<<endl;
    show();
    cout<<"output next time slice?"<<endl;
    char ans;
    cin>>ans;
    bool flag = false;
    if(ans == 'N'||ans == 'n'){
        flag = false;
    }
    else{
        flag = true;
    }
    for(int i=1;i<TIME;i++){
        __time++;

        update(i);
        
        cout<<"After time slice"<<__time<<":"<<endl;
        show();
        cout<<"output next slice?"<<endl;
        cin>>ans;
        if(ans == 'N' || ans == 'n'){
            break;
        }
    }
    
    

    if(__time == TIME){
        std::cout << "\nThe task has been finished!\n" << std::endl;
        std::cout << "The Throughput of the pipeline is " << static_cast<double>(INUM) / static_cast<double>(TIME) << " Δ"<<"t" << std::endl;
        std::cout << "The Speedup of the pipeline is " << static_cast<double>(INUM * SPACE) / static_cast<double>(TIME) << std::endl;
        std::cout << "The Efficiency of the pipeline is " << (static_cast<double>(INUM) / static_cast<double>(TIME))<< std::endl;

    }


}
