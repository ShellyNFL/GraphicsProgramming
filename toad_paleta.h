#define ALTOT 28
#define ANCHOT 20
GLubyte paleta1t[9][3] = {{172,212,232}, //blanco 0
						 {255,0,0}, //rojo 1
						 {255,222,173}, //beige 2
                         {65,105,225}, //azul 3
						 {204,102,0}, //cafe claro 4
						 {192,192,192}, //gris  5
						 {139,69,19},//cafe 6
						 {0,0,0},
						 {255,255,255}}; //negro 7
						 	// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
GLubyte toad[ALTOT][ANCHOT]={{0,0,0,0,0,0,7,7,7,7,7,7,7,0,0,0,0,0,0,0},//0
                              {0,0,0,0,7,7,8,8,8,8,8,8,8,7,7,0,0,0,0,0},//1
                              {0,0,0,7,8,8,8,1,1,1,1,8,8,8,8,7,0,0,0,0},//2
                              {0,0,7,8,8,8,1,1,1,1,1,1,8,8,8,8,7,0,0,0},//3
                              {0,7,8,8,8,1,1,1,1,1,1,1,1,8,8,8,8,7,0,0},//4
                              {0,7,1,8,8,1,1,1,1,1,1,1,1,8,8,8,1,7,0,0},//5
                              {7,1,1,1,8,8,1,1,1,1,1,1,8,8,8,1,1,1,7,0},//6
                              {7,1,1,1,8,8,8,1,1,1,1,8,8,8,1,1,1,1,7,0},//7
                              {7,1,1,1,8,8,8,8,8,8,8,8,8,8,1,1,1,1,7,0},//8
                              {7,1,1,8,8,5,7,7,7,7,7,7,7,5,8,1,1,1,7,0},//9
                              {0,7,8,8,5,7,4,2,2,2,2,2,4,7,8,8,1,7,0,0},//10
                              {0,7,5,5,7,4,2,7,2,2,7,2,4,7,5,8,8,7,0,0},//11
                              {0,0,7,7,7,2,2,7,2,2,7,2,2,4,7,5,7,0,0,0},//12
                              {0,0,0,0,7,2,2,2,2,2,2,2,2,4,7,7,0,0,0,0},//13
                              {0,0,0,0,7,4,2,2,7,7,2,2,2,4,7,0,0,0,0,0},//14
                              {0,0,0,0,0,7,4,2,2,2,2,2,4,7,0,0,0,0,0,0},//15
                              {0,0,0,0,0,0,7,7,7,7,7,7,7,3,7,0,0,0,0,0},//16
                              {0,0,0,0,7,7,3,7,4,4,4,7,3,3,7,7,0,0,0,0},//17
                              {0,0,0,7,2,7,3,7,2,2,4,7,3,3,7,4,7,7,0,0},//18
                              {0,0,7,2,4,7,3,7,2,2,4,7,3,3,7,2,2,2,7,0},//19
                              {0,7,2,4,4,7,3,7,7,7,7,7,7,3,3,7,4,2,2,7},//20
                              {0,7,2,2,4,7,7,8,8,8,8,5,5,7,3,7,4,4,2,7},//21
                              {0,0,7,7,7,7,8,8,8,8,8,8,5,7,7,7,7,7,7,0},//22
                              {0,0,0,0,0,7,5,8,8,8,8,8,5,5,7,7,0,0,0,0},//23
                              {0,0,0,7,7,7,7,5,8,8,8,5,7,7,7,7,0,0,0,0},//24
                              {0,0,7,6,6,6,6,7,7,7,7,7,6,6,6,6,7,0,0,0},//25
                              {0,0,7,6,6,6,6,6,7,8,7,6,6,6,6,6,7,0,0,0},//26
                              {0,0,0,7,7,7,7,7,8,8,8,7,7,7,7,7,0,0,0,0}};//27