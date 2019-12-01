#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

int arr[8][8][8][8];

int board[8][8];

enum piece{empty, wp, wr, wn, wb, wq, wk, bp, br, bn, bb, bq, bk};

void initmatrix(){
  for(int a = 0; a < 8; a++)
    for(int b = 0; b < 8; b++)
      for(int c = 0; c < 8; c++)
        for(int d = 0; d < 8; d++)
          arr[a][b][c][d] = -1;
}

void initboard(){
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)	
			board[i][j] = empty;
	for(int i = 0; i < 8; i++)
		board[1][i] = wp, board[6][i] = bp;
	board[0][7] = board[0][0] = wr, board[0][1] = board[0][6] = wn, board[0][2] = board[0][5] = wb, board[0][3] = wq, board[0][4] = wk;	
	board[7][7] = board[7][0] = br, board[7][1] = board[7][6] = bn, board[7][2] = board[7][5] = bb, board[7][3] = bq, board[7][4] = bk;
}

int onboard(int x, int y){
	return (x >= 0 && y >= 0 && x < 8 && y < 8);
}

int valid(int x, int y, int color){
	if(x < 0 || y < 0 || x > 7 || y > 7)	return 0;
	if(color){
		if(board[x][y] <= wk && board[x][y] >= wp)
			return 0;
		return 1;
	}
	else{
		if(board[x][y] <= bk && board[x][y] >= bp)
			return 0;
		return 1;
	}
}

void pawn(int x, int y){
	if(board[x + 1][y] == empty && onboard(x + 1, y))
		arr[x][y][x + 1][y] = 0;
	if(x == 1 && board[x + 2][y] == empty && onboard(x + 2, y))
		arr[x][y][x + 2][y] = 0;
	if(board[x + 1][y + 1] <= bk && board[x + 1][y + 1] >= bp && onboard(x + 1, y + 1))
		arr[x][y][x + 1][y + 1] = board[x + 1][y + 1];
	if(board[x + 1][y - 1] <= bk && board[x + 1][y - 1] >= bp && onboard(x + 1, y - 1))
		arr[x][y][x + 1][y - 1] = board[x + 1][y - 1];
}

void rook(int x, int y){
	for(int i = x + 1; valid(i, y, 1); i++){
		arr[x][y][i][y] = board[i][y];
		if(board[i][y] > 0)
			break;
	}
	for(int i = x - 1; valid(i, y, 1); i--){
		arr[x][y][i][y] = board[i][y];
		if(board[i][y] > 0)
			break;
	}
	for(int j = y + 1; valid(x, j, 1); j++){
		arr[x][y][x][j] = board[x][j];
		if(board[x][j] > 0)
			break;
	}
	for(int j = y - 1; valid(x, j, 1); j--){
		arr[x][y][x][j] = board[x][j];
		if(board[x][j])
			break;
	}
}	

void night(int x, int y){
	if(valid(x + 2, y - 1, 1))	arr[x][y][x + 2][y - 1]	= board[x + 2][y - 1];
	if(valid(x + 2, y + 1, 1)) arr[x][y][x + 2][y + 1] = board[x + 2][y + 1];
	if(valid(x - 2, y - 1, 1)) arr[x][y][x - 2][y - 1] = board[x - 2][y - 1];
	if(valid(x - 2, y + 1, 1)) arr[x][y][x - 2][y + 1] = board[x - 2][y + 1];

	if(valid(x + 1, y + 2, 1)) arr[x][y][x + 1][y + 2] = board[x + 1][y + 2];
	if(valid(x + 1, y - 2, 1)) arr[x][y][x + 1][y - 2] = board[x + 1][y - 2];
	if(valid(x - 1, y + 2, 1)) arr[x][y][x - 1][y + 2] = board[x - 1][y + 2];
	if(valid(x - 1, y - 2, 1)) arr[x][y][x - 1][y - 2] = board[x - 1][y - 2];
}

void bishop(int x, int y){
	for(int i = x + 1, j = y + 1; valid(i, j, 1); i++, j++){
    arr[x][y][i][j] = board[i][j];
    if(board[i][j] > empty)
      break;
	}
	for(int i = x + 1, j = y - 1; valid(i, j, 1); i++, j--){
    arr[x][y][i][j] = board[i][j];
    if(board[i][j] > empty)
      break;
	}
  for(int i = x - 1, j = y + 1; valid(i, j, 1); i--, j++){
    arr[x][y][i][j] = board[i][j];
		if(board[i][j] > empty)
      break;
  }
	for(int i = x - 1, j = y - 1; valid(i, j, 1); i--, j--){
    arr[x][y][i][j] = board[i][j];
    if(board[i][j] > empty)
      break;
	}
}

void queen(int x, int y){
	rook(x, y);
	bishop(x, y);
}

void king(int x, int y){
	if(valid(x + 1, y, 1))	arr[x][y][x + 1][y] = board[x + 1][y];
	if(valid(x - 1, y, 1))	arr[x][y][x - 1][y] = board[x - 1][y];
	if(valid(x, y + 1, 1))	arr[x][y][x][y + 1] = board[x][y + 1];
	if(valid(x, y - 1, 1))	arr[x][y][x][y - 1] = board[x][y - 1];
	if(valid(x + 1, y + 1, 1))	arr[x][y][x + 1][y + 1] = board[x + 1][y + 1];
	if(valid(x + 1, y - 1, 1))	arr[x][y][x + 1][y - 1] = board[x + 1][y - 1];
	if(valid(x - 1, y + 1, 1))	arr[x][y][x - 1][y + 1] = board[x - 1][y + 1];
	if(valid(x - 1, y - 1, 1))	arr[x][y][x - 1][y - 1] = board[x - 1][y - 1];
}	

void creategraph(){
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++){
			switch(board[i][j]){
				case 1: {pawn(i, j);	break;}
				case 2: {rook(i, j);	break;}
				case 3: {night(i, j);	break;}
				case 4: {bishop(i, j);	break;}
				case 5: {queen(i, j);	break;}
				case 6: {king(i, j);	break;}
			}
		}
}

void patanahi(int a, int x, int y){
  switch(a){
    case 1: {pawn(x, y);  break;}
    case 2: {rook(x, y);  break;}
		case 3: {night(x, y);	break;}
    case 4: {bishop(x, y);  break;}
    case 5: {queen(x, y); break;}
    case 6: {king(x, y);  break;}
    default: return;
  }
}

void correctgraph(int a, int b){
	int i, j;
	for(i = a + 1; onboard(i, b) && board[i][b] == empty; i++);
  if(board[i][b] > 0 && board[i][b] <= wk && onboard(i, b)) patanahi(board[i][b], i, b);
  for(i = a - 1; onboard(i, b) && board[i][b] == 0 ; i--);
  if(board[i][b] > 0 && board[i][b] <= wk && onboard(i, b)) patanahi(board[i][b], i, b);

  for(j = b; onboard(a, j) && board[a][j] == 0; j++);
  if(board[a][j] > 0 && board[a][j] <= wk && onboard(a, j)) patanahi(board[a][j], a, j);
  for(j = b; onboard(a, j) && board[a][j] == 0; j--);
  if(board[a][j] > 0 && board[a][j] <= wk && onboard(a, j)) patanahi(board[a][j], a, j);

  for(i = a + 1, j = b + 1; onboard(i, j) && board[i][j] == 0; i++, j++);
  if(onboard(i, j) && board[i][j] > 0 && board[i][j] <= wk)  patanahi(board[i][j], i, j);
  for(i = a - 1, j = b + 1; onboard(i, j) && board[i][j] == 0; i--, j++);
  if(onboard(i, j) && board[i][j] > 0 && board[i][j] <= wk)  patanahi(board[i][j], i, j);

  for(i = a + 1, j = b - 1; onboard(i, j) && board[i][j] == 0; i++, j--);
  if(onboard(i, j) && board[i][j] > 0 && board[i][j] <= wk)  patanahi(board[i][j], i, j);
  for(i = a - 1, j = b - 1; onboard(i, j) && board[i][j] == 0; i--, j--);
  if(onboard(i, j) && board[i][j] > 0 && board[i][j] <= wk)  patanahi(board[i][j], i, j);

  if(board[a + 2][b + 1] == 3)  night(a + 2, b + 1);
  if(board[a + 2][b - 1] == 3)  night(a + 2, b - 1);
  if(board[a - 2][b + 1] == 3)  night(a - 2, b + 1);
  if(board[a - 2][b - 1] == 3)  night(a - 2, b - 1);
  if(board[a + 1][b + 2] == 3)  night(a + 1, b + 2);
  if(board[a + 1][b - 2] == 3)  night(a + 1, b - 2);
  if(board[a - 1][b + 2] == 3)  night(a - 1, b + 2);
  if(board[a - 1][b - 2] == 3)  night(a - 1, b - 2);

}

void display(){
	printf("\n  ");
	for(int i = 'a'; i <= 'h'; i++)
		printf("%c ", i);
	printf("\n");
	for(int i = 0; i < 8; i++){
		printf("%d ", i + 1);
		for(int j = 0; j < 8; j++){
			switch(board[i][j]){
				case 0:	{printf("_ ");	break;}
				case 1: {printf("P "); break;}
				case 2: {printf("R "); break;}
				case 3: {printf("N "); break;}
				case 4: {printf("B "); break;}
				case 5: {printf("Q "); break;}
				case 6: {printf("K "); break;}
				case 7: {printf("p "); break;}
				case 8: {printf("r "); break;}
				case 9: {printf("n "); break;}
				case 10: {printf("b "); break;}
				case 11: {printf("q "); break;}
				case 12: {printf("k "); break;}
			}
		}
		printf("\n");
	}
}

int player(){
	int xp, yp, x, y, flag = 0;
	char s[4];
	scanf("%s", s);
	xp = s[0] - '1', yp = s[1] - 'a', x = s[2] - '1', y = s[3] - 'a';
	if(valid(x, y, 0)){
		int temp = board[xp][yp];
		board[xp][yp] = empty;
		flag = (board[x][y] == wk) ? wk : 1;
		board[x][y] = temp;
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
				arr[x][y][i][j] = -1;
		correctgraph(xp, yp);
		correctgraph(x, y);
	}
	return flag;
}

int computer(){
	int m = -1, pos = 9999, a, b, x, y, i, j, flag = 0;
	for(int e = 0; e < 8; e++)
		for(int f = 0; f < 8; f++)
			for(int g = 0; g < 8; g++)
				for(int h = 0; h < 8; h++)
					if(arr[e][f][g][h] >= m){
						if(arr[e][f][g][h] == m)
							(abs(g - 7) + abs(h - 4)) <= pos ?  pos = abs(g - 7) + abs(h - 4), a = e, b = f, x = g, y = h : pos;
						else	m = arr[e][f][g][h], x = g, y = h, a = e, b = f;
					}
	flag = (board[x][y] == bk) ? 1 : 0;
	printf("(%d, %c)->(%d, %c)", a + 1, b + 'a', x + 1, y + 'a');
	board[x][y] = board[a][b];
	board[a][b] = 0;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)	
			arr[a][b][i][j] = -1;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			arr[i][j][x][y] = -1;
	patanahi(board[x][y], x, y);
	correctgraph(x, y);
	correctgraph(a, b);
	
	return flag;
}

void clrscr(){
	system("@cls||clear");
}

void game(){
	int p = 0, c = 0;
	while(1){
		c = computer();
		clrscr();	
		display();
		if(c){  printf("white won!!");  break;}
		if(p == wk){  printf("black won!!");  break;}
		p = 0;
		printf("player's move: ");
		while(!p)	p = player();
	}
}
