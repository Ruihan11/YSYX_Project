#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Address {
    int id;                             //数据id
    int set;                            //数据状态
    char *name;                //数据1：name
    char *email;               //数据2：email
    char *address;             //数据3：address
};

struct Database {
    int max_data;
    int max_rows;
    struct Address *rows;      //最大堆栈深度取决于输入的MAX_ROWS
};

struct Connection {                     //struct Connection这个结构体用于将文件和堆栈结合起来，方便查找
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message ,struct Connection *conn)
{
    if(errno) {                                                     //检查一下errno，如果非0则说明有错误，perror输出错误以及message；
        perror(message);
    } else {                                                        //如果errno没有问题，则输出ERROR:message，
        printf("ERROR: %s\n", message);                             
    }
    Database_close(conn);

    exit(1);                                                        //一旦进入这个函数，横竖都会输出错误且退出。
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s %s\n",
            addr->id, addr->name, addr->email, addr->address);
}

void Database_load(struct Connection *conn)                         //根据file初始化db指针指向的结构体数组
{

    int rc0 = fread(&conn->db->max_data, sizeof(int), 1, conn->file);               //前两个参数是max_data和max_rows
    int rc1 = fread(&conn->db->max_rows, sizeof(int), 1, conn->file);

    if(rc0 != 1 || rc1 != 1) die("Failed to load max_data and max_rows to database." ,conn);

    for(int i =0; i< conn->db->max_rows; i++){
    int rc2 = fread(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
    int rc3 = fread(&conn->db->rows[i].set, sizeof(int), 1, conn->file);                  //把db指向的经过修改的结构体成员rows[i]写回conn->file
    int rc4 = fread(conn->db->rows[i].name, conn->db->max_data, 1, conn->file);
    int rc5 = fread(conn->db->rows[i].email, conn->db->max_data, 1, conn->file);
    int rc6 = fread(conn->db->rows[i].address, conn->db->max_data, 1, conn->file);
    if(rc2 != 1 || rc3 != 1 || rc4 != 1 || rc5 != 1 || rc6 != 1) die("Failed to load database." ,conn);
    }
    
}

struct Connection *Database_open(const char *filename, char mode, int max_data, int max_rows)    //为conn和db两个结构体指针指向的结构体开辟一片存储区域，并根据file文件初始化。
{
    struct Connection *conn = malloc(sizeof(struct Connection));     //开辟区域给结构体指针conn
    if(!conn) die("Memory error" ,conn);

    conn->db = malloc(sizeof(struct Database));                     //开辟区域给结构体指针db
    if(!conn->db) die("Memory error" ,conn);
    conn->db->max_data = max_data;
    conn->db->max_rows = max_rows;

    conn->db->rows = malloc(max_rows * sizeof(struct Address));         //开辟区域给所有rows[i]
    if(!conn->db->rows) die("Memory error" ,conn);

    for(int j = 0; j < max_rows ; j++){
    conn->db->rows[j].name = malloc(max_data);                              //开辟区域给每个rows[i]的name、email以及address
    conn->db->rows[j].email = malloc(max_data);
    conn->db->rows[j].address = malloc(max_data);
    
    if(!conn->db->rows[j].name || !conn->db->rows[j].email || !conn->db->rows[j].address) die("Memory error" ,conn);
    }

    if(mode == 'c') {
        conn->file = fopen(filename, "w");                          //如果mode是create，检查一下*filename的可写性
    } else {
        conn->file = fopen(filename, "r+");                         //如果mode是其他的，检查一下*filename的读写性

        if(conn->file) {
            Database_load(conn);                        //其他模式下如果文件可读写，则将file文件的部分内容读取至database
        }
    }

    if(!conn->file) die("Failed to open the file" ,conn);                 //如果file指针是NULL，则输出错误

    return conn;
}

void Database_close(struct Connection *conn)                        //关闭file，释放内存，先malloc的后释放
{
    if(conn) {
        for(int i = 0; i < conn->db->max_rows ; i++){
            free(conn->db->rows[i].name);
            free(conn->db->rows[i].email); 
            free(conn->db->rows[i].address);
        }

        if(conn->db->rows) free(conn->db->rows);
        if(conn->file) fclose(conn->file);                      
        if(conn->db) free(conn->db);
        
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc0 = fwrite(&conn->db->max_data, sizeof(int), 1, conn->file);                      //将max_data和max_rows写入文件
    int rc1 = fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file);

    if(rc0 != 1 || rc1 != 1) die("Failed to write max_data and max_rows to database." ,conn);

    for(int i =0; i< conn->db->max_rows; i++){
    int rc2 = fwrite(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
    int rc3 = fwrite(&conn->db->rows[i].set, sizeof(int), 1, conn->file);                  //把需要存储的参数写回conn->file
    int rc4 = fwrite(conn->db->rows[i].name, conn->db->max_data, 1, conn->file);
    int rc5 = fwrite(conn->db->rows[i].email, conn->db->max_data, 1, conn->file);
    int rc6 = fwrite(conn->db->rows[i].address, conn->db->max_data, 1, conn->file);
    if(rc2 != 1 || rc3 != 1 || rc4 != 1 || rc5 != 1 || rc6 != 1) die("Failed to write database." ,conn);
    }

    int rc7 = fflush(conn->file);                                                            //将缓冲区的东西直接写入文件
    if(rc7 == -1) die("Cannot flush database." ,conn);
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for(i = 0; i < conn->db->max_rows; i++) {                 //初始化Database结构体中的每一个数组元素（也是结构体）
        // make a prototype to initialize it
        conn->db->rows[i].id= i;
        conn->db->rows[i].set = 0;
        memset(conn->db->rows[i].name, 0, conn->db->max_data);
        memset(conn->db->rows[i].email, 0, conn->db->max_data);
        memset(conn->db->rows[i].address, 0, conn->db->max_data);
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email, const char *address)             //根据提供的id name email 写入结构体rows[id]
{
    struct Address *addr = &conn->db->rows[id];                     //addr指向结构体rows[id]
    if(addr->set) die("Already set, delete it first" ,conn);              //set的作用就是判断有无数据

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_data - 1);                //字符串复制，返回值是addr->name的地址
     *(addr->name +  conn->db->max_data -1) = '\0';
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed" ,conn);                               //res为NULL则报错

    res = strncpy(addr->email, email, conn->db->max_data - 1);                  
    *(addr->email + conn->db->max_data -1) = '\0';
    if(!res) die("Email copy failed" ,conn);                            

    res = strncpy(addr->address, address, conn->db->max_data - 1);               
    *(addr->address + conn->db->max_data -1) = '\0';
    if(!res) die("Email copy failed" ,conn);                          
}

void Database_get(struct Connection *conn, int id)                          //打印输出rows[id]
{
    struct Address *addr = &conn->db->rows[id];                             //取rows[id]的地址赋给指针addr

    if(addr->set) {                                                         
        Address_print(addr);                                                //如果rows[id]的set是1，则打印该rows[id]的name id email
    } else {
        die("ID is not set" ,conn);                                               //如果set为0，说明该rows[id]未设置，退出
    }
}

void Database_delete(struct Connection *conn, int id)                       //根据id清空name、email等信息
{
        conn->db->rows[id].id= id;
        conn->db->rows[id].set = 0;
}

void Database_list(struct Connection *conn)                         //只要set为1，代表这个rows[id]写入过，就printf信息
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

void Database_find(struct Connection *conn, char *message)
{
    int comp1, comp2, comp3;
    for(int i = 0;i < conn->db->max_rows; i++){
        comp1 = strcmp(message, conn->db->rows[i].name);                    //将要寻找的字段和存储的name、email、address比较，只要有一个函数返回值为0即匹配成功
        comp2 = strcmp(message, conn->db->rows[i].email);
        comp3 = strcmp(message, conn->db->rows[i].address);
        if(!comp1 || !comp2 || !comp3){
            Address_print(&conn->db->rows[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3) {
        printf("ERROR: USAGE: ex17 <dbfile> <action> [action params]\n");   //argc<4则提前终止程序，即：argc至少要为4（至少要这两个参数：<dbfile文件名> <action执行什么操作>）
        exit(1);
    }

    char *filename, action;
    int MAX_DATA, MAX_ROWS;

    if(argv[2][0] == 'c'){                                                          //c模式下，其命令行格式：可执行文件  c   MAX_DATA   MAX_ROWS
        filename = argv[1];
        action = argv[2][0];
        MAX_DATA = atoi(argv[3]);
        MAX_ROWS = atoi(argv[4]);
    }
    else {
        filename = argv[1];                                                     //其他模式则从file文件中读取MAX_DATA和MAX_ROWS
        action = argv[2][0];

        struct Connection connect;
        connect.db = NULL;
        int temp[2];

        connect.file = fopen(filename, "r+");
        if(connect.file) {
            fread(temp, 2 * sizeof(int), 1, connect.file);
            MAX_DATA = temp[0];
            MAX_ROWS = temp[1];
            fclose(connect.file);
        }
        else
            exit(1);
            
    }
        

    struct Connection *conn = Database_open(filename, action, MAX_DATA, MAX_ROWS);   //Database_open 刨一块区域给结构体指针conn,并根据file文件初始化
    int id = 0;

    if(argc > 3 && action != 'c' && action != 'f') id = atoi(argv[3]);                            //如果不止3个参数，则取第三个参数为id
    if(id >= conn->db->max_rows && action != 'c' && action != 'f') die("There's not that many records." ,conn);

    switch(action) {
        case 'c':                                               //create，初始化一片区域
            if(argc != 5) die("Need filename c max_size max_rows" ,conn);
            Database_create(conn);                              //给conn->db结构体中的每一个数组元素rows[i]（也是结构体）赋id和set = 0；
            Database_write(conn);                               //把db指向的经过修改的结构体成员rows[i]写回conn->file
            break;

        case 'g':                                               //get，用于打印输出
            if(argc != 4) die("Need an id to get" ,conn);             //这个操作要5个参数，<dbfile> <action>以及id

            Database_get(conn, id);                             //打印输出rows[id]
            break;

        case 's':                                                   //set，设置name和email
            if(argc != 7) die("Need id, name, email to set" ,conn);       //这个操作要6个参数：<dbfile> <action> id  name  email address

            Database_set(conn, id, argv[4], argv[5], argv[6]);               //根据提供的id name email 写入结构体rows[id]
            Database_write(conn);                                   //把db指向的经过修改的结构体成员rows[i]写回conn->file
            break;

        case 'd':                                                   //delete
            if(argc != 4) die("Need id to delete" ,conn);                 //delete需要3个参数：<dbfile> <action> id；

            Database_delete(conn, id);                              //delete主要是根据id将set复位，感觉实际上此位置还有数据，但因为set为0，已经是无用数据了
            Database_write(conn);                                   //同步至file
            break;

        case 'l':
            Database_list(conn);                                    //printf已经写入过（set为1）的结构体的信息
            break;

        case 'f':
            if(argc != 4) die("Need message to find" ,conn);
            Database_find(conn, argv[3]);                   //取第四个参数为要寻找的字符串
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list" ,conn);
    }

    Database_close(conn);                                           //关闭file，释放内存

    return 0;
}
