
#include <GalileoSDK/GalileoSDK.h>
#include <GalileoSDK/galileo_serial_server/GalileoStatus.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <unistd.h>
static const char jsonfile[] = "new.dat";  // 与写入文件保持一致

void read_file_content(const char *filename);
double x_v_line,z_v_ang;
int pub_flag;

int main(int argc, char **argv)
{
    GalileoSDK::GalileoSDK sdk;

    
    pub_flag = false;

    while (true)
    {
        FILE *fp;
        if ((fp = fopen(jsonfile, "rb")) == NULL)
            return 0;
        // 加锁
        if (0 == flock(fileno(fp), LOCK_EX))
        {
            // printf("lock...\n");
            // 关闭文件前解锁
            fclose(fp);
            flock(fileno(fp), LOCK_UN);
            // 读取文件内容并打印
            read_file_content(jsonfile);
        }
        else
        {
            printf("lock failed\n");
        }


        auto servers = sdk.GetServersOnline(); // 获取当前在线的机器人
        if(servers.size() == 0){
            std::cout << "No server found" << std::endl;
        }
        for (auto it = servers.begin(); it < servers.end(); it++)
        {
            std::cout << it->getID() << std::endl;
            sdk.Connect("", true, 10000, NULL, NULL); // 连接机器人
        }
        if(pub_flag)
        {
            sdk.SetSpeed(x_v_line, z_v_ang);
            std::cout<<"pub: "<<x_v_line<<"  "<<z_v_ang<<std::endl;
        }
            
        // pub_flag = false;
        // sleep(1);
        usleep(200000);


    }
}




// 读取文件并打印内容
void read_file_content(const char *filename)
{
    FILE *fp;
    // FILE *fp_i;
    // FILE *fp_r;


    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Failed to open file for reading.\n");
        return;
    }

    // 加锁，防止与其他写入操作冲突
    if (flock(fileno(fp), LOCK_SH) == 0)  // 共享锁用于读取
    {
        
        // fp_i =fp;
        // std::cout<<fp<<std::endl<<fp_i<<std::endl;
        // printf("Reading file content...\n");

        // 从文件中读取两个 double 和一个 bool（以 int 的形式存储）
        fread(&x_v_line, sizeof(double), 1, fp);
        fread(&z_v_ang, sizeof(double), 1, fp);
        // fp_r = fp;
        // std::cout<<fp<<std::endl<<fp_i<<std::endl<<fp_r<<std::endl;
        fread(&pub_flag, sizeof(int), 1, fp);
        

    //     std::cout<<"--------------"<<std::endl;
    //     std::cout<<"pub_flag: "<<pub_flag<<std::endl;
    //     // pub_flag = 42;

    // // 移动文件指针到 pub_flag 的位置
    // double tem_ = 0;
    // fseek(fp, -sizeof(int), SEEK_CUR);
    // fseek(fp, -sizeof(double), SEEK_CUR);
    // // 将修改后的 pub_flag 写入文件
    // fwrite(&tem_, sizeof(int), 1, fp);

        // // 将修改后的 pub_flag 写回文件
        // int tem_ = 0;
        // fwrite(&tem_, sizeof(int), 1, fp);
        // // fseek(fp, pub_flag_pos, SEEK_SET);
        // int tem_2 = 3;
        // fread(&tem_2, sizeof(int), 1, fp);
        // std::cout<<"pub_flag: "<<pub_flag<<std::endl;
        // {
            
        //     int t_1,t_2,t_3;
        //     fread(&t_1, sizeof(double), 1, fp_i);
        //     fread(&t_2, sizeof(double), 1, fp_i);
        //     fread(&t_3, sizeof(double), 1, fp_i);
        //     std::cout<<"t_1:"<<t_1<<"  t_2:"<<t_1<<"  t_3"<<t_3<<std::endl;
        // }


        fclose(fp);
        flock(fileno(fp), LOCK_UN); // 解锁
    }
    else
    {
        printf("Unable to lock file for reading.\n");
    }
}
