



void drawPoint(int x, int y)
{
   analogWrite(X_Pin, x);
   analogWrite(Y_Pin, y);
}

void drawLine(byte x1, byte y1, byte x2, byte y2)
{
    // optimized implementation of Bresenham's Algorithm
    // also known as a DDA - digital differential analyzer
    int acc;

    // for speed, there are 8 DDA's, one for each octant
    //  Quadrants
    //  2  |  1
    // ----|----
    //  3  |  4
    if (y1 < y2) { // quadrant 1 or 2
        byte dy = y2 - y1;
        if (x1 < x2) { // quadrant 1
            byte dx = x2 - x1;
            if (dx > dy) { // < 45
                acc = (dx >> 1);
                for (; x1 < x2; x1++) {
                    drawPoint(x1, y1);
                    acc -= dy;
                    if (acc < 0) {
                        y1++;
                        acc += dx;
                    }
                }
            }
            else {   // > 45
                acc = dy >> 1;
                for (; y1 < y2; y1++) {
                    drawPoint(x1, y1);
                    acc -= dx;
                    if (acc < 0) {
                        x1++;
                        acc += dy;
                    }
                }
            }
        }
        else {  // quadrant 2
            byte dx = x1 - x2;
            if (dx > dy) { // < 45
                acc = dx >> 1;
                for (; x1 > x2; x1--) {
                    drawPoint(x1, y1);
                    acc -= dy;
                    if (acc < 0) {
                        y1++;
                        acc += dx;
                    }
                }
            }
            else {  // > 45
                acc = dy >> 1;
                for (; y1 < y2; y1++) {
                    drawPoint(x1, y1);
                    acc -= dx;
                    if (acc < 0) {
                        x1--;
                        acc += dy;
                    }
                }
            }        
        }
    }
    else { // quadrant 3 or 4
        byte dy = y1 - y2;
        if (x1 < x2) { // quadrant 4
            byte dx = x2 - x1;
            if (dx > dy) {  // < 45
                acc = dx >> 1;
                for (; x1 < x2; x1++) {
                    drawPoint(x1, y1);
                    acc -= dy;
                    if (acc < 0) {
                        y1--;
                        acc += dx;
                    }
                }
            
            }
            else {  // > 45
                acc = dy >> 1;
                for (; y1 > y2; y1--) {
                    drawPoint(x1, y1);
                    acc -= dx;
                    if (acc < 0) {
                        x1++;
                        acc += dy;
                    }
                }

            }
        }
        else {  // quadrant 3
            byte dx = x1 - x2;
            if (dx > dy) { // < 45
                acc = dx >> 1;
                for (; x1 > x2; x1--) {
                    drawPoint(x1, y1);
                    acc -= dy;
                    if (acc < 0) {
                        y1--;
                        acc += dx;
                    }
                }

            }
            else {  // > 45
                acc = dy >> 1;
                for (; y1 > y2; y1--) {
                    drawPoint(x1, y1);
                    acc -= dx;
                    if (acc < 0) {
                        x1--;
                        acc += dy;
                    }
                }
            }
        }
    }
}

void drawPattern(prog_uchar *image, int imagesize, uint16_t TimeMs) 
{
   uint32_t StartMillis = millis();
   while (millis() - StartMillis < TimeMs) drawPatternOnce(image, imagesize);
}

void drawPatternOnce(prog_uchar *image, int imagesize) 
{
    bool darkvector = false;
    uint16_t i = 0;
    byte x1 = pgm_read_byte_near(image+i++);
    byte y1 = pgm_read_byte_near(image+i++);
    while (i < imagesize) 
    {
        byte x2 = pgm_read_byte_near(image+i++);
        if (x2 == 255) 
        { // dark drawLine (move)
            x2 = pgm_read_byte_near(image+i++);
            darkvector = true;
        }
        byte y2 = pgm_read_byte_near(image+i++);
        if (!darkvector) drawLine(x1, y1, x2, y2);
        else darkvector = false;
        x1 = x2;
        y1 = y2;
    }
}

