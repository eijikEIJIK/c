#include <stdio.h>

/* パズドラコンボ数判定プログラム */
/* 1 3 5 2 4 6
   1 4 5 2 3 5 
   1 3 5 2 4 6
   1 4 5 2 3 5 
   5 6 4 5 3 2 */
/* のようなテキストファイル(pazudora.txt)を入力する。各数字が石の種類を表す。 */

int board[5][6];
int board_n[5][6];
int flag[5][6];
int combo=0;

void view(){
  for (int i=0;i<5;i++){
      for (int j=0;j<6;j++){
        if(board[i][j]==0){
          printf("  ");
        }else printf("%d ",board[i][j]);
      }printf("\n");
    }printf("\n");
} 

void yokocheck(int n,int i,int j,int c){
  if (j<6 && board_n[i][j]==n){
    yokocheck(n,i,j+1,c+1);
    return;
  }
  if (j==6 || board_n[i][j]==0){
    if (c>=3){
      for (int k=0;k<c;k++){
        board[i][j-k-1]=0;
        flag[i][j-k-1]=1;
      }
    }
  }
  return;
}

void tatecheck(int n,int i,int j,int c){
  if (i<5 && board_n[i][j]==n){
    tatecheck(n,i+1,j,c+1);
    return;
  }
  if (board_n[i][j]==0 || j>=5){
    if (c>=3){
      for (int k=0;k<c;k++){
        board[i-k-1][j]=0;
        flag[i-k-1][j]=1;
      }
    }
  }
  return;
}


int cmb(int y,int x){
  if(y<0 || y>=5 || x<0 || x>=6){
    return 0;
  }
  else{
    if (flag[y][x]==1){
      flag[y][x]=0;
      cmb(y, x+1);
      cmb(y, x-1);
      cmb(y+1, x);
      cmb(y-1, x);
      return 1;
    }
  }
  return 0;
}

int combo_count(){
  int count=0;
  for (int i=0;i<5;i++){
    for (int j=0;j<6;j++){
      count+=cmb(i,j);
    }
  }
  for (int i=0;i<5;i++){
    for (int j=0;j<6;j++){
      flag[i][j]=0;
    }
  }

  return count;
}

void zero(){
  for (int n=1;n<=6;n++){
    for (int i=0;i<5;i++){
      for (int j=0;j<6;j++){
        if (board[i][j]==n){
          board_n[i][j]=n;
        }else{
          board_n[i][j]=0;
        }
      }
    }
    for (int i=0;i<5;i++){
      for (int j=0;j<6;j++){
        yokocheck(n,i,j,0);
        tatecheck(n,i,j,0);
      }
    }
  combo+=combo_count();
  }
}

void delete(){
  for(int n=0;n<5;n++){
    for (int i=0;i<4;i++){
      for (int j=0;j<6;j++){
        if (board[4-i][5-j]==0){
          int a=0;
          a=board[3-i][5-j];
          board[4-i][5-j]=a;
          board[3-i][5-j]=0;
        }
      }
    }
  }
}

int cnt_stones(){
  int cnt=0;
  for (int i=0;i<5;i++){
    for (int j=0;j<6;j++){
      if (board[i][j]!=0) cnt+=1;
    }
  }
  return cnt;
}

int main(void) {
  FILE* fp;
  fp = fopen("pazudora.txt", "r");
  for (int i=0;i<5;i++){
    for (int j=0;j<6;j++){
      fscanf(fp, "%d", &board[i][j]);
    }
  }

  fclose(fp);

  int count=0,before,now;
  view();
  now=cnt_stones();
  while(before!=now){
    zero();
    delete();
    count+=1;
    before=now;
    now=cnt_stones();
  }
  printf("%d combo",combo);
}