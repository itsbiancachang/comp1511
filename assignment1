// Assignment 1 19T2 COMP1511: CS Paint
// paint.c
//
// This program was written by CHUNG CHI CHANG (z5224457)
// on 26/06/2019
//
// Version 1.0.0 (2019-06-22): Assignment released.

#include <stdio.h>
#include <stdlib.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define DARK 1
#define GREY 2
#define LIGHT 3
#define WHITE 4




// Provided helper functions:
// Print out the canvas.
void printCanvas(int canvas[N_ROWS][N_COLS]);
void drawLine(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int shade);
void fillRectangle(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int shade);
void copyPaste(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int target_row, int target_col);
void additive(int canvas[N_ROWS][N_COLS], int shade_canvas_pen[3][3], int add_row1, int add_col1, int add_row2, int add_col2);
// Set the entire canvas to be blank.
void setBlankCanvas(int canvas[N_ROWS][N_COLS]);



// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE


int main(void) {

    int canvas[N_ROWS][N_COLS];
    setBlankCanvas(canvas);



    int instruction;
    int row1, col1, row2, col2;
    int shade = BLACK; //default shade
    int target_row, target_col; //for instruction == 4
    int distanceRow, distanceCol;
    //for instruction 5 variables 
    int shade_canvas_pen[3][3];
    int add_shade;
    int add_instruction; 
    int add_row1, add_col1, add_row2, add_col2;
    
    //when EOF scanf... != 1, jump out of the loop then 
    while (scanf("%d", &instruction) == 1) {
        
        if ((instruction == 1) || (instruction == 2) || (instruction == 4)) {
        
            scanf("%d", &row1);
            scanf("%d", &col1);
            scanf("%d", &row2);
            scanf("%d", &col2);

            //check if the input is valid, if not, go back from the start and ask for the input again
            if ((row1 < 0) || (row1 >= N_ROWS) || (row2 < 0) || (row2 >= N_ROWS)) {
            
                continue;
            }

            if ((col1 < 0) || (col1 >= N_COLS) || (col2 < 0) || (col2 >= N_COLS)) {
            
                continue;
            }
        }

        if (instruction == 3) {
            
            scanf("%d", &shade);

            //check if the input is valid - only the specified shade is available
            if ((shade > 4) || (shade < 0)) {
                
                shade = WHITE;
                continue;
                
            }
        }

        if (instruction == 4) {
            
            scanf("%d", &target_row);
            scanf("%d", &target_col);

             //prevent pasting outside the canvas
            distanceRow = abs(row1 - row2 + 1);
            distanceCol = abs(col1 - col2 + 1);

            //check it out of bounds 
            if ((target_row < 0) || (target_col < 0) || (target_row + distanceRow - 1 > N_ROWS) || (target_col + distanceCol - 1 > N_COLS)) {  
                
                continue;
            }
           

        }

        if (instruction == 5) {
            
            for (int r = 0; r < 3; r++) {
                
                for (int c = 0; c < 3; c++) {
                
                    scanf("%d", &add_shade);
                    shade_canvas_pen[r][c] = add_shade; 
                }
            }

            scanf("%d", &add_instruction);
            //only accept for instruction1 - draw a line
            if (add_instruction == 1) { 

                scanf("%d", &add_row1);
                scanf("%d", &add_col1);
                scanf("%d", &add_row2);
                scanf("%d", &add_col2);
            }
            else if ((add_row1 - 1 < 0) || (add_row1 + 1 > N_ROWS) || (add_row2 - 1 < 0) || (add_row2 + 1 > N_ROWS)
                || (add_col1 - 1 < 0) || (add_col1 + 1 > N_COLS) || (add_col2 - 1 < 0) || (add_col2 + 1 > N_COLS)){

                continue;
            }
            else{
                
                continue; 
            }
        }



        //choose the instruction - calling function here

        if (instruction == 1) {
        
            drawLine(canvas, row1, col1, row2, col2, shade);
        }
        else if (instruction == 2) {
        
            fillRectangle(canvas, row1, col1, row2, col2, shade);
        }
        else if (instruction == 4) {
        
            copyPaste(canvas, row1, col1, row2, col2, target_row, target_col);
        }
        else if (instruction == 5) {
        
            additive(canvas, shade_canvas_pen, add_row1, add_col1, add_row2, add_col2);
        }
    }
    
    printCanvas(canvas);

    return 0;
    
    

  

}



// ADD CODE FOR YOUR FUNCTIONS HERE

//instruction1
//drawALine function here: draw horizontal and vertical lines
void drawLine(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int shade){


    //print out a pixel here if.. 
    if ((row1 == row2) && (col1 == col2)) {

        canvas[row1][col1] = shade;
        canvas[row2][col2] = shade;
    }

    //drawing horizontal or vertical line
    if ((row1 == row2) || (col1 == col2)) {

        //checking column
        //horizontal line: always from left to right
        //so make sure col1 < col2; else swap
        int temp_col = 0;
        if (col1 > col2) {
            
            temp_col = col1;
            col1 = col2;
            col2 = temp_col;
        }

        for (int r = row1; r <= row2; r++) {
            
            for (int c = col1; c <= col2; c++) {

                canvas[r][c] = 0;
            }
        }

        //checking row
        //vertical line: always from top to down
        //so make sure row1 < row2; else swap
        int temp_row = 0;
        if (row1 > row2) {
            
            temp_row = row1;
            row1 = row2;
            row2 = temp_row;
        }


        for (int c = col1; c <= col2; c++) {
            
            for (int r = row1; r <= row2; r++) {
            
                canvas[r][c] = shade;
            }
        }
    }//else draw a diagonal line
    else {
        //calculate the gradient to decide the direction, m = 1: starting from upper left, m = -1: upper right
        int m = (row2-row1)/(col2-col1);


        //always drawing from the right
        int temp_col = 0;
        if (col1 > col2) {

            temp_col = col1;
            col1 = col2;
            col2 = temp_col;
        }

        int temp_row = 0;
        if (row1 > row2) {

            temp_row = row1;
            row1 = row2;
            row2 = temp_row;
        }


        if (m == 1) {

            for (int r = row1; r <= row2; r++) {

                for (int c = col1; c <= col2; c++) {

                    if (r == (c + (row1-col1))) {

                        canvas[r][c] = shade;
                    }
                }
            }
        }

        if (m == -1) {

            for (int r = row1; r <= row2; r++) {

                for (int c = col1; c <= col2; c++) {

                    if (r == (c*(-1) + (row1+col2))) {

                        canvas[r][c] = shade;
                    }
                }
            }
        }



    }



}

//instruction 2
//given four additional integers, which describe two pixels: 
//the start and end pixels that make up two corners of the rectangle.

void fillRectangle(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int shade){


        //horizontal line: always from left to right
        int temp_col = 0;
        if (col1 > col2) {

            temp_col = col1;
            col1 = col2;
            col2 = temp_col;
        }


        for (int r = row1; r <= row2; r++) {

            for (int c = col1; c <= col2; c++) {

                canvas[r][c] = shade;
            }
        }


        //vertical line: always from top to down
        //so make sure row1 > row2; else swap
        int temp_row = 0;
        if (row1 > row2) {

            temp_row = row1;
            row1 = row2;
            row2 = temp_row;
        }

        for (int c = col1; c <= col2; c++) {

            for (int r = row1; r <= row2; r++) {

                canvas[r][c] = shade;
            }
        }





}


//copy a certain section of the canvas, and paste it elsewhere on the canvas
void copyPaste(int canvas[N_ROWS][N_COLS], int start_row, int start_col, 
    int end_row, int end_col, int target_row, int target_col){

    int length_of_row = end_row - start_row + 1;
    int length_of_col = end_col - start_col + 1;

    //the empty copyCanvas - later copy over here of what we wish to cut from the original canvas
    int copyCanvas[length_of_row][length_of_col];
    
    //initialize the copyCanvas to default value 0
    for (int i = 0; i < length_of_row; i++) {

        for (int j = 0; j < length_of_col; j++) {

            copyCanvas[i][j] = 0;
        }
    }

    //copy a certain section of the canvas and put it to the copyCanvas
    int copyCanvasRow = 0; 
    int r = start_row;

    int copyCanvasCol = 0;
    int c = start_col; 

    while (copyCanvasRow < length_of_row) {

        while (copyCanvasCol < length_of_col) {

            copyCanvas[copyCanvasRow][copyCanvasCol] = canvas[r][c];
            
            copyCanvasCol++;
            c++;
        }


        copyCanvasRow++;
        r++;
        copyCanvasCol= 0; //starting from the start of the column, or it gonna stay in the end 
        c = start_col;
    }


    //paste the copyCanvas to canvas(the original one)

    int copyCanvasRow1 = 0; 
    int copyCanvasCol1 = 0;
    int standard_target_col = target_col; //save the start of the target_col for later reuse

    //paste the copyCanvas to canvas by each individual value
    while (copyCanvasRow1 < length_of_row) {

        while (copyCanvasCol1 < length_of_col) {

            canvas[target_row][target_col] = copyCanvas[copyCanvasRow1][copyCanvasCol1];

            copyCanvasCol1++;
            target_col++;
        }

        copyCanvasRow1++;
        target_row++;
        copyCanvasCol1 = 0; //starting from the start of the column, or it gonna stay in the end
        target_col = standard_target_col;
    }


}


//instruction 5
//special brush for the drawline command 
//nine pixel brush - This brush will affect a 9 pixel square for 
// every pixel that the original brush would have drawn.


void additive(int canvas[N_ROWS][N_COLS], int shade_canvas_pen[3][3], int start_row, int start_col, int end_row, int end_col){

    //a point - single stamp brush

    if ((start_row == end_row) && (start_col == end_col)) {

        int sr = 0;
        int sc = 0;
        int start_shade_r = start_row - 1;
        int start_shade_c = start_col - 1;

        while (sr < 3) {

            while (sc < 3) {

                    if (canvas[start_shade_r][start_shade_c] + shade_canvas_pen[sr][sc] > 4){
                        
                        canvas[start_shade_r][start_shade_c] = 4;
                    }
                    else if (canvas[start_shade_r][start_shade_c] + shade_canvas_pen[sr][sc] < 0){
                        
                        canvas[start_shade_r][start_shade_c] = 0;
                    }
                    else {

                        canvas[start_shade_r][start_shade_c] += shade_canvas_pen[sr][sc];
                    }

                    sc ++;
                    start_shade_c++;
                }
                sr++;
                start_shade_r++;

                start_shade_c = start_col-1;
                sc = 0;
        }

    }

    //horizontal line

    if ((start_row == end_row) && (start_col != end_col)) {
        
        int sc = start_col;
        int sr = start_row; 
        int ec = end_col;
        

        int i = 0; 

        while (sc + 1 <= ec + 1) {
            
            while (i < 3) {
            
                canvas[sr - 1][sc + 1] += shade_canvas_pen[i][2];

                //correct the color
                if(canvas[sr - 1][sc + 1] > 4) {
                
                    canvas[sr - 1][sc + 1] = 4;
                }

                if(canvas[sr - 1][sc + 1] < 0) {
                
                    canvas[sr - 1][sc + 1] = 0;
                }

                sr += 1;
                i++;
            }

            sc += 1;
            sr = start_row; 
            i = 0; 
        }

        int k = 0;

        sc = start_col;
        sr = start_row; 

        while (sc <= ec) {
            
            while (k < 3) {
            
                canvas[sr - 1][sc] += shade_canvas_pen[k][1];
                
                //correct the color
                if (canvas[sr - 1][sc] > 4) {
                    
                    canvas[sr - 1][sc] = 4;
                }

                if (canvas[sr - 1][sc] < 0) {
                
                    canvas[sr - 1][sc] = 0;
                }

                sr += 1;
                k++;
            }

            sc += 1;
            sr = start_row; 
            k = 0; 

        }

        int h = 0;

        sc = start_col;
        sr = start_row; 

        while (sc - 1 <= ec - 1) {
            
            while(h < 3) {
            
                canvas[sr - 1][sc - 1] += shade_canvas_pen[h][0];

                //correct the color
                if (canvas[sr - 1][sc - 1] > 4) {
                    
                    canvas[sr - 1][sc - 1] = 4;
                }

                if (canvas[sr - 1][sc - 1] < 0) {
                    
                    canvas[sr - 1][sc - 1] = 0;
                }


                sr += 1;
                h++;
            }

            sc += 1;
            sr = start_row; 
            h = 0; 

        }
    }
    
    //veritcal line
    
    if ((start_col == end_col) && (start_row != end_row)) {
    
        int sc = start_col;
        int sr = start_row; 
        int er = end_row; 

        int i = 0; 

    

        while (sr + 1 <= er + 1) {
            
            while (i < 3) {
            
                canvas[sr + 1][sc - 1] += shade_canvas_pen[2][i];

                if (canvas[sr + 1][sc - 1] > 4) {
                    
                    canvas[sr + 1][sc -1] = 4;
                }

                if (canvas[sr + 1][sc - 1] < 0) {
                    
                    canvas[sr + 1][sc - 1] = 0;
                }

                sc += 1;
                i++;
            }

            sr += 1;
            sc = start_col; 
            i = 0; 
        }



        int k = 0;

        sc = start_col;
        sr = start_row; 

        while (sr <= er) {
            
            while(k < 3) {
            
                canvas[sr][sc - 1] += shade_canvas_pen[1][k];

                //correct the color
                if(canvas[sr][sc - 1] > 4) {
                    
                    canvas[sr][sc -1] = 4;
                }

                if(canvas[sr][sc - 1] < 0) {
                    
                    canvas[sr][sc - 1] = 0;
                }

                sc += 1;
                k++;
            }

            sr += 1;
            sc = start_col; 
            k = 0; 
        }

        int h = 0;

        sc = start_col;
        sr = start_row; 

        while (sr - 1 <= er - 1) {
            
            while (h < 3) {
            
                canvas[sr - 1][sc - 1] += shade_canvas_pen[0][h];


                //correct the color
                if (canvas[sr - 1][sc - 1] > 4) {
                    
                    canvas[sr - 1][sc -1] = 4;
                }

                if (canvas[sr - 1][sc - 1] < 0) {
                    
                    canvas[sr - 1][sc - 1] = 0;
                }

                sc += 1;
                h++;
            }

            sr += 1;
            sc = start_col; 
            h = 0; 
        }
    }
}


// Prints the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
//
// You should not need to change the printCanvas function.
void printCanvas(int canvas[N_ROWS][N_COLS]){

    int row = 0;
    while (row < N_ROWS) {

        int col = 0;
        while (col < N_COLS) {

            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}


// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
//
// You should not need to change the setBlankCanvas function.
void setBlankCanvas(int canvas[N_ROWS][N_COLS]){

    int row = 0;
    while (row < N_ROWS) {

        int col = 0;
        while (col < N_COLS) {

            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}
