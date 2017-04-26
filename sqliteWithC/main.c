//
//  main.c
//  sqliteWithC

//  C语言实现sqlite的增删改差功能
//
//  Created by 邹前立 on 2017/4/26.
//  Copyright © 2017年 邹前立. All rights reserved.
//

/*
SQLITE_API int sqlite3_exec(
    sqlite3*,                                  // An open database              *数据库
    const char *sql,                           // SQL to be evaluated           *SQL语句
    int (*callback)(void*,int,char**,char**),  // Callback function             *回掉函数
    void *,                                    // 1st argument to callback      *回掉函数第一个参数
    char **errmsg                              // Error msg written here        *错误消息
);

*/
 
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

// 回掉函数
static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: \n", (const char*)data);
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// 创建company表
void createTableCompany(sqlite3 *db, char *sql, int rc,char *zErrMsg) {
    /*创建sql语句：创建company表*/
    sql = "CREATE TABLE COMPANY(" \
    "ID INT PRIMARY KEY NOT NULL," \
    "NAME     TEXT      NOT NULL," \
    "AGE      INT       NOT NULL," \
    "ADDRESS  CHAR(50)," \
    "SALARY   REAL );";
    
    /*执行sql语句*/
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){ // 失败
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }
}
// 添加数据
void insertData(sqlite3 *db, char *sql, int rc,char *zErrMsg) {
    /*创建sql语句：*/
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
    "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
    "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
    "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
    "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
    
    /*执行sql语句*/
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){ // 失败
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }
}

// 查询数据
void selectData(sqlite3 *db, char *sql, int rc,const char* data,char *zErrMsg) {
    /*创建sql语句：*/
    sql = "SELECT * FROM COMPANY;";
    
    /*执行sql语句*/
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){ // 失败
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Selected successfully\n");
    }
}

// 修改数据
void updateData(sqlite3 *db, char *sql, int rc,const char *data, char *zErrMsg) {
    /* 合并SQL语句，先修改然后查询。Create merged SQL statement */
    sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
    "SELECT * from COMPANY";
    
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
}
// 删除数据
void deleteData(sqlite3 *db, char *sql, int rc, const char *data, char *zErrMsg) {
    /* Create merged SQL statement */
    sql = "DELETE from COMPANY where ID=2; " \
          "SELECT * from COMPANY";
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Delete data successfully\n");
    }
}
// #define SQLITE_OK  0   /* Successful result */
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql = 0;
    const char* data = "Callback function called";
    
    // 打开／创建数据库
    rc = sqlite3_open("/Users/reborn/Documents/XcodeFiles/sqliteTest/sqliteWithC/testSqlite.db", &db); // 二级指针，传入指针的地址
    
    if (rc) { // 打开失败
        fprintf(stderr, "Can't open Database:%s.\n",sqlite3_errmsg(db));
        exit(0); // stdlib.h
    }else { // 打开成功
        fprintf(stderr, "Open Database successfully!\n");
    }
    
    // 创建表
//    createTableCompany(db, sql, rc,zErrMsg);
    // 添加数据
//    insertData(db, sql, rc, zErrMsg);
    // 查询数据
//    selectData(db, sql, rc, data, zErrMsg);
    // 修改数据
//    updateData(db, sql, rc, (void*)data, zErrMsg);
    // 删除数据
//    deleteData(db, sql, rc, (const char *)data, zErrMsg);
    // 关闭数据库
    sqlite3_close(db);
    
    return 0;
}
