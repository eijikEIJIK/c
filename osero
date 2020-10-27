#include <stdio.h>

int board[8][8];
int dydx[8][2]={{0,1},{0,-1},{1,0},{1,-1},{1,1},{-1,1},{-1,0},{-1,-1}};

/* (dy,dx)方向の駒を返す */
int judgea(int a,int b,int dy,int dx){
  if (a>9 || a<0 || b>9 || b<0){
    return 0;
  }else if (a+dy>9 || a+dy<0 || b+dx>9 || b+dx<0){
    return 0;
  }else if (board[a+dy][b+dx]==0 ||board[a+dy][b+dx]==3){
    return 0;
  }else{
    return board[a+dy][b+dx];
  }
}
/* (dy,dx)方向にひっくりかえせる駒があるかどうか */
void judgeb(int i,int you,int a,int b,int dy,int dx){
  int c=0,y=a,x=b;
  if (judgea(a,b,dy,dx)==0){
    return ;
  }else if(judgea(a,b,dy,dx)==i){
    return ;
  }else{
    while(1){
      y+=dy;x+=dx;
      if (judgea(y,x,dy,dx)==i){
        board[a][b]=3;/* 置ける場所を記録 */
        return ;
      }else if(judgea(y,x,dy,dx)==0 || judgea(y,x,dy,dx)==3){
        return ;
      }
    }
  }
}

int main(int argc, char **argv)
{
	FILE *fp;
	int i, j;

	if (argc != 2) {
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp ==NULL) {
		return 1;
	}

	for (i=0; i<8; i++) {
		for (j=0; j<8; j++) {
			fscanf(fp, "%d", &(board[i][j]));
		}
	}

  /* 自分が1 */
  for (i=0; i<8; i++) {
    for (j=0; j<8; j++) {
      if(board[i][j]==0){
        for(int k=0;k<8;k++){
          judgeb(1,2,i,j,dydx[k][0],dydx[k][1]);
        }
      }
    }
  }

  printf("[1]\n");
  for (i=0; i<8; i++) {
		for (j=0; j<8; j++) {
      if (board[i][j]<3){
			  printf("%d ", board[i][j]);
      }else{
        printf("x ");
      }
		}
		printf("\n");
	}
  printf("\n");

  /* 初期化 */
  for (i=0; i<8; i++) {
		for (j=0; j<8; j++) {
      if(board[i][j]==3){
        board[i][j]=0;
      }
		}
	}

  /* 自分が2 */
  for (i=0; i<8; i++) {
    for (j=0; j<8; j++) {
      if(board[i][j]==0){
        for(int k=0;k<8;k++){
          judgeb(2,1,i,j,dydx[k][0],dydx[k][1]);
        }
      }
    }
  }

  printf("[2]\n");
  for (i=0; i<8; i++) {
		for (j=0; j<8; j++) {
      if (board[i][j]<3){
			  printf("%d ", board[i][j]);
      }else{
        printf("x ");
      }
		}
		printf("\n");
	}
	return 0;
}
