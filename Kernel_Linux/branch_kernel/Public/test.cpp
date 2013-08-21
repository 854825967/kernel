/* 
 * File:   test.cpp
 * Author: zc
 *
 * Created on 2013年1月12日, 下午1:40
 */

#include <cstdlib>
#include <iostream>
#include "NewBuff.h"
#include "test1.h"
#include "Itest1.h"
/*
 * 
 */
int main(int argc, char** argv)
{
    char test[]="helloworld";
    
    INewBuff *buff = new NewBuff() ;

   
    for( int i=0;i<5000;i++)
    {
        int m=i ;
        if(m==5545)
        {
            cout<<"hi" ;
        }
        UI32 n = buff->InsertBuff(test,11);
        cout<< n ;
        cout<< i+1 ;
        void *p = buff->QueryBuff(n);
        
        cout<<(char*)p<<endl;
        
    }
    buff->DeleteBuff(1) ;
  
//    Itest1 *p=new test1() ;
//    p->a() ;
    return 0;
}

