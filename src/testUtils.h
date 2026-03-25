void drawLine2D(char grid[][40], int WIDTH, int HEIGHT, float SCALE,
                float x0, float y0, float x1, float y1, char ch = '#') {
    // Bresenham's line algorithm
    int px0 = (int)(x0 * SCALE + WIDTH  / 2);
    int py0 = (int)(-y0 * SCALE + HEIGHT / 2);
    int px1 = (int)(x1 * SCALE + WIDTH  / 2);
    int py1 = (int)(-y1 * SCALE + HEIGHT / 2);

    int dx = abs(px1 - px0);
    int dy = abs(py1 - py0);
    int sx = px0 < px1 ? 1 : -1;
    int sy = py0 < py1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (px0 >= 0 && px0 < WIDTH && py0 >= 0 && py0 < HEIGHT)
            grid[py0][px0] = ch;
        if (px0 == px1 && py0 == py1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; px0 += sx; }
        if (e2 <  dx) { err += dx; py0 += sy; }
    }
}

void visualize2D(const char* label, Vector4f points[], int count, float SCALE = 3.0f) {
    const int WIDTH  = 40;
    const int HEIGHT = 20;

    char grid[20][40];
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            grid[y][x] = '.';

    // draw edges (connect points in order, close the loop)
    for (int i = 0; i < count; i++) {
        int next = (i + 1) % count;
        drawLine2D(grid, WIDTH, HEIGHT, SCALE,
            points[i].x, points[i].y,
            points[next].x, points[next].y);
    }

    // draw corners
    for (int i = 0; i < count; i++) {
        int px = (int)(points[i].x * SCALE + WIDTH  / 2);
        int py = (int)(-points[i].y * SCALE + HEIGHT / 2);
        if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
            grid[py][px] = '@';
    }

    // draw axes
    for (int x = 0; x < WIDTH;  x++) grid[HEIGHT / 2][x] = '-';
    for (int y = 0; y < HEIGHT; y++) grid[y][WIDTH  / 2] = '|';
    grid[HEIGHT / 2][WIDTH / 2] = '+';

    std::cout << "\n[" << label << "]\n";
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
            std::cout << grid[y][x];
        std::cout << "\n";
    }
}