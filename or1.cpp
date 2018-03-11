#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
int allocateOrder(int);
void ResetingWorkingVariables(void);

	
	//Order info= = [OrderNum], {price, Item1-Item10}
	int iniOrderItem[11][13] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{9500,0,0,0,2000,3000,0,0,0,0,6000,0,0},
{9300,1000,3000,0,0,0,1000,0,0,0,0,3000,0},
{12300,0,0,1500,0,0,0,4000,4000,6000,0,0,2000},
{15600,0,4000,0,0,5000,0,0,0,8000,0,2000,3000},
{11000,5000,0,0,0,45000,2500,0,0,4500,0,0,0},
{8700,0,1000,3500,1500,0,0,0,3000,0,0,1500,0},
{7700,0,1000,500,0,0,5000,0,0,0,0,0,500},
{10000,2000,2000,0,500,1000,0,1000,0,0,2000,3000,1000},
{14600,2500,0,3000,4000,500,1000,3000,1000,500,3000,500,1500},
{11200,0,0,0,2000,0,0,0,2000,0,3000,0,4000}
};
   //OderInfo = [OrderNum], {CustNo, price, splitting Cost}
    int OrderInfo[11][3]= { 
{0,0,0},
{1,9500,3000},
{1,9300,3000},
{1,12300,3000},
{2,15600,4700},
{3,11000,4250},
{4,8700,4340},
{4,7700,4340},
{5,10000,4620},
{5,14600,4620},
{6,11200,5000}
};
	// FabCap = [FabID], { Capacity}
	int iniFabCap[9] ={
0,
840,
750,
610,
470,
560,
240,
1250,
930      
    };
    int wrkFabCap[9] ={
0,
840,
750,
610,
470,
560,
240,
1250,
930       
    };
    	int wrkOrderItem[11][13] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{9500,0,0,0,2000,3000,0,0,0,0,6000,0,0},
{9300,1000,300,0,0,0,1000,0,0,0,0,3000,0},
{12300,0,0,1500,0,0,0,4000,4000,6000,0,0,2000},
{15600,0,4000,0,0,5000,0,0,0,8000,0,2000,3000},
{11000,5000,0,0,0,45000,2500,0,0,4500,0,0,0},
{8700,0,1000,3500,1500,0,0,0,3000,0,0,1500,0},
{7700,0,1000,500,0,0,5000,0,0,0,0,0,500},
{10000,2000,2000,0,500,1000,0,1000,0,0,2000,3000,1000},
{14600,2500,0,3000,4000,500,1000,3000,1000,500,3000,500,1500},
{11200,0,0,0,2000,0,0,0,2000,0,3000,0,4000}
};
    	// FabCap = [FabID], { Cap, Rate1-Rate10}
	int iniFabRate[9][13] ={
{0,0,0,0,0,0,0,0,0,0,0,0,0},     
{840,10,5,10,10,5,0,20,50,40,0,0,0},
{550,5,0,15,0,0,5,10,15,20,25,20,0},
{440,0,20,30,5,0,10,0,10,30,15,0,30},
{570,25,0,0,20,25,40,5,0,0,0,30,15},
{560,20,15,20,0,0,15,30,0,0,15,0,20},
{340,40,0,40,50,50,0,0,30,0,45,20,0},
{1150,0,5,0,10,15,5,10,5,10,5,15,10},
{930,0,20,0,30,15,0,0,0,20,0,5,20}
    };

    //Order pattern[OrderId] = ItemPattern
    unsigned short OrderPattern[11]={0};
       //Fab pattern[FabId] = ItemPattern
   unsigned short FabPattern[9]={0};
      //ItemMatch
   unsigned short ItemMatch[11][9]={0};
   int custOrderComplete[11]={0};
   int OrderAllocFab[11][9] = {0};
   int OrderAllocFabSucc[11][9] = {0};
   int OrderAllocFabQty[11][9][13] = {0};
   
int main(void)
{
	int i, j, k; 
	int resultingValue=0;
	int iCntSplit=0;
	int OrderSeq[11] = { 0};
    int ifFinished=0;//default "no"
    int iCnt=0;
    int iOrderNum=0;
    int resultingCheck =0;

    
    //Order pattern[OrderId] = ItemPattern
    //unsigned short OrderPattern[11]={0};
    OrderPattern[1] = 1*(16*16) + 8*16 + 4;
    OrderPattern[2] = 12*(16*16) + 4*16 + 2;
    OrderPattern[3] = 2*(16*16) + 3*16 + 9;
    OrderPattern[4] = 4*(16*16) + 8*16 + 11;
    OrderPattern[5] = 8*(16*16) + 12*16 + 8;
    OrderPattern[6] = 7*(16*16) + 1*16 + 2;
    OrderPattern[7] = 6*(16*16) + 4*16 + 1;
    OrderPattern[8] = 13*(16*16) + 10*16 + 7;
    OrderPattern[9] = 11*(16*16) + 15*16 + 15;
    OrderPattern[10] = 1*(16*16) + 1*16 + 5;
   //Fab pattern[FabId] = ItemPattern
   //unsigned short FabPattern[9]={0};
    FabPattern[1] = 15*(16*16) + 11*16 + 8;
    FabPattern[2] = 12*(16*16) + 7*16 + 14;
    FabPattern[3] = 7*(16*16) + 5*16 + 13;
    FabPattern[4] = 9*(16*16) + 14*16 + 3;
    FabPattern[5] = 14*(16*16) + 6*16 + 5;
    FabPattern[6] = 11*(16*16) + 9*16 + 6;
    FabPattern[7] = 5*(16*16) + 15*16 + 15;
    FabPattern[8] = 5*(16*16) + 8*16 + 11;
   //ItemMatch
   //unsigned short ItemMatch[11][9]={0};
   int iCntBit=0;
   unsigned short iStrBit=0;
   unsigned short iValBit=0;
   for( i = 1 ; i < 11 ; i++ ){
     for( j = 1 ; j < 9 ; j++ ){ 
      ItemMatch[i][j]= OrderPattern[i] & FabPattern[j];
	  //printf("ItemMatch[%d][%d]= %#10x \n", i,j, ItemMatch[i][j]);
	  // count the number of "1" bit atfer bitwise and matching
	    iCntBit = 0;
	    iStrBit = ItemMatch[i][j];
        //printf("ItemMatch[%d][%d]: %d\n",i,j,ItemMatch[i][j]);
        for( k = 1 ; k < 12 ; k++ ){
         iValBit = iStrBit & 0x0001;
         //printf("iValBit[%d][%d]: %d\n",i,j,iValBit);
         if( iValBit == 1) iCntBit +=1;
         iStrBit = iStrBit >> 1; 
        }//for k
        ItemMatch[i][j] = iCntBit;
        //printf("ItemMatch[%d][%d]: %d\n",i,j,ItemMatch[i][j]);
      }//for j
      //system("pause"); 
    }//for i
	  
    //Order Sequence
    //---------------------------------------------------------------1

    //int OrderSeq[11] = { 0,10,4,8,9,6,7,5,1,2,3};//Cost-down driven
    OrderSeq[1]=2;OrderSeq[2]=1;OrderSeq[3]=4;OrderSeq[4]=7;OrderSeq[5]=10;
    OrderSeq[6]=3;OrderSeq[7]=5;OrderSeq[8]=8;OrderSeq[9]=9;OrderSeq[10]=6;
   	//printf("Cost-down driven: resultingValue= %d\n",resultingValue);
    ifFinished=0;//default "no"
    iCnt=0;
    iOrderNum=0;
   	//Reseting working variables for another order sequence---------
	//ResetingWorkingVariables;
	//Reseting working variables for another order sequence
    for( j = 1 ; j < 9 ; j++ ) {wrkFabCap[j]=iniFabCap[j];} 
    for( i = 1 ; i < 11 ; i++ ){
       custOrderComplete[i] = 0; 
       for( j = 1 ; j < 9 ; j++ ){
        OrderAllocFab[i][j]  = 0;
        OrderAllocFabSucc[i][j]  = 0;
        
      }//for j
      for( k = 1 ; k < 13 ; k++ ){
        wrkOrderItem[i][k] = iniOrderItem[i][k];
        OrderAllocFabQty[i][j][k] = 0;
      }//for k
    }// for i
	
   for( i = 1 ; i < 11 ; i++ ){
     //ith order
     iOrderNum = OrderSeq[i];
     iCnt=1;
     ifFinished=0;
     do{
        //printf("Order[%d] perform %d th run allocation\n",iOrderNum,iCnt); 
        ifFinished = allocateOrder(iOrderNum); 
        if(ifFinished == 2){ //order cannot compeletely allocated, need to release?
         ifFinished = 1;
        }
        iCnt +=1;
     }while(ifFinished==0);
   }//for
   
	//calcute the resulting value
	resultingValue=0;
	for( i = 1 ; i < 11 ; i++ ){
      iCntSplit=0;
      for( j = 1 ; j < 9 ; j++ ){
           iCntSplit += OrderAllocFabSucc[i][j];
           printf("\nOrder[%d] to Fab[%d]:",i,j);
           for( k = 1 ; k < 13 ; k++ ){
           printf("%5d",OrderAllocFabQty[i][j][k]);
           }//for k
      }//for j
      	resultingCheck = resultingValue;
    	resultingValue += custOrderComplete[i]*OrderInfo[i][1];
       if(iCntSplit >= 1)
	   	resultingValue -= (iCntSplit-1)*OrderInfo[i][2];
		if(resultingCheck > resultingValue)
	   	resultingValue = resultingCheck;
    } //for i    
     
	//printf("resultingValue= %d\n",resultingValue);
	printf("\n-----------------------------resultingValue= %d\n",resultingValue);

	system("pause"); return(0);
}

int allocateOrder(int i)
{
    int iMax=1;
    int toFab=0;
    int iHours=0;
    int j,k;
    unsigned short maxMatch;
    int ifComplete=1; //default "Yes"
    int prevOrderItem=0;
 

     toFab=0;iHours=0;iMax=1;
     //find most match fab with max cap
     maxMatch=0; 
     for( j = 1 ; j < 9 ; j++ ){
         if(OrderAllocFab[i][j] == 0) {maxMatch=ItemMatch[i][j];iMax=j;break;}
     }
     if(maxMatch == 0){
         ///-----release allocated capacity 
         for( j = 1 ; j < 9 ; j++ ){
           //printf("\nOrder[%d] release Fab[%d]:",i,j);
           for( k = 1 ; k < 13 ; k++ ){
             if(OrderAllocFabSucc[i][j] == 1 && iniFabRate[j][k] > 0) {
             wrkFabCap[j] += OrderAllocFabQty[i][j][k]/iniFabRate[j][k];
             OrderAllocFabSucc[i][j] = 0;
             OrderAllocFabQty[i][j][k] = 0;                     
             }//if 
           }//for k
      }//for j
         return 2;// oder cannot completely allocated
     }
     
     //maxMatch=ItemMatch[i][1];
     for( j = 1 ; j < 9 ; j++ ){
          if(OrderAllocFab[i][j] > 0) continue;
          else if(j == iMax) continue;
          else if (ItemMatch[i][j] > maxMatch){ iMax=j;maxMatch=ItemMatch[i][j];}
          else if((ItemMatch[i][j] == maxMatch) && (wrkFabCap[j] > wrkFabCap[iMax]))
          { iMax=j;maxMatch=ItemMatch[i][j];}
     }
     
     toFab = iMax; 
     //printf("toFab = %d\n",toFab);
     OrderAllocFab[i][toFab] = 1;
     //printf("Order[%d] checking Fab[%d]\n", i, toFab);
     //system("pause");
     for( k = 1 ; k < 13 ; k++ ){
       if (wrkOrderItem[i][k] > 0 && iniFabRate[toFab][k] > 0 && wrkFabCap[toFab]>0){  
          iHours = wrkOrderItem[i][k]/iniFabRate[toFab][k];
          ////printf("OrderItem[%d][%d]: iHours = %d\n",i,k,iHours);
          ////system("pause");
          if(iHours <= wrkFabCap[toFab]) {
             prevOrderItem =wrkOrderItem[i][k];
             wrkOrderItem[i][k] =0; 
             wrkFabCap[toFab] -= iHours;
             OrderAllocFabSucc[i][toFab]=1;
             OrderAllocFabQty[i][toFab][k]  += prevOrderItem;
             //printf("OrderItem[%d][%d]: from %d to %d\n",i,k,prevOrderItem,wrkOrderItem[i][k]);
          }         
          else {// allow partial alloc and empty the capacity 
               prevOrderItem =wrkOrderItem[i][k];
               wrkOrderItem[i][k] -= wrkFabCap[toFab]*iniFabRate[toFab][k];
               OrderAllocFabSucc[i][toFab]=1;
               OrderAllocFabQty[i][toFab][k] += wrkFabCap[toFab]*iniFabRate[toFab][k]; 
			   wrkFabCap[toFab] =0;
               //printf("OrderItem[%d][%d]: from %d to %d\n",i,k,prevOrderItem,wrkOrderItem[i][k]);
          }//else
          
       }//if
       
     }//for k
     //system("pause");
     int iSum=0;
     for( k = 1 ; k < 13 ; k++ ){
       iSum += wrkOrderItem[i][k];
      }
     if(iSum==0) { 
        custOrderComplete[i]=1;
        ifComplete=1;
        printf("---------------------------Order[%d] is completed\n",i);
     }//if
     else {custOrderComplete[i]=0;ifComplete=0;}
     
     ////printf("ifComplete=%d\n",ifComplete);
     return ifComplete;
     
}//allocateOrder()



