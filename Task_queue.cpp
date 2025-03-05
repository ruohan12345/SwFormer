volatile int cg_status[6];//0 free, 1 busy

void barrier_at(int cg_id){
    while(cg_status[cg_id]){};//busy wait
}

//PTK: Data structure for persistent kernels
//Kernels: Reordered Tiled kernels
//Num_Kernels: The number of reordered tiled kernels
void Task_queue(PTK *Kernels,  int Num_Kernels){
    for(int i = 0; i < Num_Kernels; i++){
        int cnt=0;
        while(true){
            int cg_id=cnt%6;
            if(cg_status[cg_id]==0){
                execute(Kernels[i], cg_id);
                break;
            }
            cnt++;
            if(cnt==6){ cnt=0; }
        }
    }
    for (int i = 0; i < 6; i++)
        barrier_at(i);
    //synchronization for the last few kernels
}
