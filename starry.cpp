/*
ID: totheso1
LANG: C++14
TASK: starry
NOTE:
    This is a very unpleasant problem.
    I don't think it's a valuable practice so I'm going to skip it.
    Below is a solution from BYVoid.
    Link is here: https://byvoid.com/zhs/blog/usaco-512-starry-night/
*/

#include <fstream>
#include <iostream>
#define MAX 100
#define INF 0x7FFFFFFF

using namespace std;

typedef struct {
  int x, y;
} point;

class queue {
 private:
  long first, last;
  point list[MAX * MAX + 1];

 public:
  long size;

  queue() {
    reset();
  }

  void reset() {
    first = 1;
    last = size = 0;
  }

  void ins(point k) {
    size++;
    list[++last] = k;
  }

  point del() {
    size--;
    return list[first++];
  }
};

typedef struct {
  int width, height;
  char cate;
  bool c[MAX * MAX];
} hashcode;

ifstream fi("starry.in");
ofstream fo("starry.out");

int M, N, hscnt = -1, w = 0;
char p[MAX][MAX], newcate = 'a';
queue Q;
hashcode Ht[30];
point mv[8];

void init() {
  int i, j;
  fi >> M >> N;
  j = (char)fi.get();
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      p[i][j] = fi.get();
    }
    j = (char)fi.get();
  }
  mv[0].x = -1;
  mv[0].y = -1;
  mv[1].x = -1;
  mv[1].y = 0;
  mv[2].x = -1;
  mv[2].y = 1;
  mv[3].x = 0;
  mv[3].y = -1;
  mv[4].x = 0;
  mv[4].y = 1;
  mv[5].x = 1;
  mv[5].y = -1;
  mv[6].x = 1;
  mv[6].y = 0;
  mv[7].x = 1;
  mv[7].y = 1;
}

void flip(hashcode &h, hashcode &w) {
  int i, j;
  //左右对称变换
  w.height = h.height;
  w.width = h.width;
  for (i = 0; i <= h.height - 1; i++) {
    for (j = 0; j <= h.width - 1; j++) {
      w.c[(i + 1) * h.width - 1 - j] = h.c[i * h.width + j];
    }
  }
  return;
}

void turn(hashcode &h, hashcode &w) {
  int i, j;
  //右旋转90度
  w.height = h.width;
  w.width = h.height;
  for (i = 0; i <= h.height - 1; i++) {
    for (j = 0; j <= h.width - 1; j++) {
      w.c[(j + 1) * h.height - i - 1] = h.c[i * h.width + j];
    }
  }
}

void transform(hashcode *H, int w) {
  hashcode T;
  if (w == 1) {
    //左右对称变换
    flip(H[0], H[w]);
    return;
  }
  if (w == 2) {
    //右旋转90度
    turn(H[0], H[w]);
    return;
  }
  if (w == 3) {
    //右旋转180度
    turn(H[0], T);
    turn(T, H[w]);
    return;
  }
  if (w == 4) {
    //右旋转270度
    turn(H[0], H[w]);
    turn(H[w], T);
    turn(T, H[w]);
    return;
  }
  if (w == 5) {
    //右旋转90度并对称
    turn(H[0], T);
    flip(T, H[w]);
    return;
  }
  if (w == 6) {
    //右旋转180度并对称
    turn(H[0], H[w]);
    turn(H[w], T);
    flip(T, H[w]);
    return;
  }
  if (w == 7) {
    //右旋转270度并对称
    turn(H[0], T);
    turn(T, H[w]);
    turn(H[w], T);
    flip(T, H[w]);
    return;
  }
}

int findsame(hashcode &H) {
  int i, j;
  bool tar;
  for (i = 0; i <= hscnt; i++) {
    if (Ht[i].height != H.height || Ht[i].width != H.width) continue;
    tar = true;
    for (j = 0; j <= H.width * H.height - 1; j++)
      if (H.c[j] != Ht[i].c[j]) {
        tar = false;
        break;
      }
    if (tar) {
      return i;
    }
  }
  return -1;
}

void floodfill(int a, int b) {
  Q.reset();
  point st, cr;
  int i, j, maxx = 0, maxy = 0, minx = INF, miny = INF;
  st.x = a;
  st.y = b;
  Q.ins(st);
  if (w == 26) w = w;
  while (Q.size) {
    cr = Q.del();
    if (cr.x < minx) minx = cr.x;
    if (cr.y < miny) miny = cr.y;
    if (cr.x > maxx) maxx = cr.x;
    if (cr.y > maxy) maxy = cr.y;
    p[cr.x][cr.y] = '2';
    for (i = 0; i < 8; i++) {
      st.x = cr.x + mv[i].x;
      if (st.x < 0 || st.x > N) continue;
      st.y = cr.y + mv[i].y;
      if (st.y < 0 || st.y > M) continue;
      if (p[st.x][st.y] == '1') {
        Q.ins(st);
        p[st.x][st.y] = '2';
      }
    }
  }
  //建立编码
  int k = 0;

  hashcode nh[8];
  char cate = 0;
  nh[0].width = maxy - miny + 1;
  nh[0].height = maxx - minx + 1;
  for (i = minx; i <= maxx; i++) {
    for (j = miny; j <= maxy; j++) {
      if (p[i][j] == '2')
        nh[0].c[k] = true;
      else
        nh[0].c[k] = false;
      k++;
    }
  }
  //寻找全等图形
  for (i = 0; i < 8; i++) {
    if ((k = findsame(nh[i])) != -1) {
      cate = Ht[k].cate;
      break;
    }
    transform(nh, i + 1);
  }
  //建立新图形
  if (!cate) {
    Ht[++hscnt] = nh[0];
    cate = Ht[hscnt].cate = newcate++;
  }
  //修改原图
  for (i = minx; i <= maxx; i++) {
    for (j = miny; j <= maxy; j++) {
      if (p[i][j] == '2') {
        p[i][j] = cate;
      }
    }
  }
}

void compute() {
  int i, j;
  ;
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      if (p[i][j] == '1') {
        floodfill(i, j);
        w++;
        i = i;
      }
    }
  }
}

void print() {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      fo << p[i][j];
    }
    fo << endl;
  }
  fi.close();
  fo.close();
}

int main() {
  init();
  compute();
  print();
  return 0;
}
