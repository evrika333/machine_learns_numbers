#include <iostream>
#define HEIGHT_FRAME 10
#define WIDTH_FRAME 10
#include "FrameSave.H"

struct Coordinates {
    int x;
    int y;
};

void clear_terminal() {
    std::cout << "\033[2J\033[H";
    std::cout.flush();
}

class frame {
    char canva[HEIGHT_FRAME][WIDTH_FRAME];
    Coordinates cursor;

public:
    frame() {
        for(int i = 0; i < HEIGHT_FRAME; i++)
            for(int j = 0; j < WIDTH_FRAME; j++)
                canva[i][j] = ' ';

        for(int j = 0; j < WIDTH_FRAME; j++) {
            canva[0][j] = '#';
            canva[HEIGHT_FRAME - 1][j] = '#';
        }

        for(int i = 0; i < HEIGHT_FRAME; i++) {
            canva[i][0] = '#';
            canva[i][WIDTH_FRAME - 1] = '#';
        }

        cursor.x = 1;
        cursor.y = 1;
        canva[cursor.y][cursor.x] = 'C';
    }

    char (*getData())[WIDTH_FRAME] {
        return canva;
    }

    void print() {
        for(int i = 0; i < HEIGHT_FRAME; i++) {
            for(int j = 0; j < WIDTH_FRAME; j++) {
                if (canva[i][j] == '*')
                    std::cout << "\033[107m \033[0m";
                else
                    std::cout << canva[i][j];
            }
            std::cout << "\n";
        }
    }

    void blinking(char brush = '!') {
        if (canva[cursor.y][cursor.x] != '#') {
            if (canva[cursor.y][cursor.x] == '*' && brush != ' ') {
                canva[cursor.y][cursor.x] = brush;
                clear_terminal();
                print();
                canva[cursor.y][cursor.x] = '*';
            } else {
                canva[cursor.y][cursor.x] = brush;
                clear_terminal();
                print();
            }
        }
    }

    void Cursor() {
        bool Allowed[4] = {false, false, false, false};
        char Where;

        if (cursor.y - 1 > 0 && canva[cursor.y - 1][cursor.x] != '#')
            Allowed[0] = true;
        if (cursor.x - 1 > 0 && canva[cursor.y][cursor.x - 1] != '#')
            Allowed[1] = true;
        if (cursor.x + 1 < WIDTH_FRAME - 1 && canva[cursor.y][cursor.x + 1] != '#')
            Allowed[2] = true;
        if (cursor.y + 1 < HEIGHT_FRAME - 1 && canva[cursor.y + 1][cursor.x] != '#')
            Allowed[3] = true;

        if (Allowed[0]) std::cout << "Top(T)\n";
        if (Allowed[1]) std::cout << "Left(L)\n";
        if (Allowed[2]) std::cout << "Right(R)\n";
        if (Allowed[3]) std::cout << "Bottom(B)\n";
        std::cout << "Save(S) | Exit(E)\n";  // New options shown alongside movement

        std::cin >> Where;

        // Handle Save and Exit before movement logic
        if (Where == 'S' || Where == 's') {
            SaveFrame();
            return;
        }
        if (Where == 'E' || Where == 'e') {
            std::cout << "Goodbye!\n";
            exit(0);
        }

        if (canva[cursor.y][cursor.x] != '*')
            canva[cursor.y][cursor.x] = ' ';

        if ((Where == 'T' || Where == 't') && Allowed[0])
            cursor.y -= 1;
        else if ((Where == 'L' || Where == 'l') && Allowed[1])
            cursor.x -= 1;
        else if ((Where == 'R' || Where == 'r') && Allowed[2])
            cursor.x += 1;
        else if ((Where == 'B' || Where == 'b') && Allowed[3])
            cursor.y += 1;
        else
            std::cout << "Movement not allowed or invalid input!\n";

        bool wasDrawn = (canva[cursor.y][cursor.x] == '*');

        blinking();

        char D;
        if (!wasDrawn) {
            std::cout << "Draw? Yes(Y) / No(N): ";
            std::cin >> D;
            if (D == 'Y' || D == 'y')
                blinking('*');
        } else {
            std::cout << "Erase? Yes(Y) / No(N): ";
            std::cin >> D;
            if (D == 'Y' || D == 'y')
                blinking(' ');
        }
    }

    void SaveFrame() {
        std::string filename;
        std::cout << "Enter label to save: ";
        std::cin >> filename;
        File f;
        f.SaveFile(HEIGHT_FRAME, WIDTH_FRAME,getData(), filename);
        std::cout << "Saved to \"" << filename << "\"!\n";
    }
};

int main() {
    frame Frame;

    clear_terminal();
    Frame.print();

    while(true) {
        Frame.Cursor();
        clear_terminal();
        Frame.print();
    }

    return 0;
}
