#include "pch.h"
#define _USE_INIT_WINDOW_
#include "tipsware.h"
#include "Constant.h"
#include <string.h>

#pragma pack(push, 1)
typedef struct GameData {
    INT8 boardData[8][8];
    INT8 moveData[8][8];
    bool is_king_moved[2];
    bool is_rook_moved[2][2];
    bool is_pawn_moved2[2][8];
    UINT8 turn : 1;
    POINT selected_piece;
    void *pieces_image[15];
} Gamedata, *pGameData;
#pragma pack(pop)

// Initialize global attributes that I will use.
void InitWindow()
{
    // Revise window title
    gp_window_title = "CChess";
    // Revise window attribute
    g_wnd_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
}

void drawboard();
void readImages();

INT8 g_clicked_flag = 0;

void OnMouseLeftDown(int a_mixed_key, POINT a_pos)
{
    g_clicked_flag = 1;
    LONG x = a_pos.x / BOARD_SIZE;
    LONG y = a_pos.y / BOARD_SIZE;
    int i;

    pGameData ap_data = (pGameData)GetAppData();

    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        if (ap_data->moveData[y][x] == blank) memset(&ap_data->moveData, blank, sizeof(INT8) * 8 * 8);

        if (ap_data->moveData[y][x]) {
            if (ap_data->boardData[ap_data->selected_piece.y][ap_data->selected_piece.x] == W_King || ap_data->boardData[ap_data->selected_piece.y][ap_data->selected_piece.x] == B_King) ap_data->is_king_moved[ap_data->turn] = true;
            ap_data->boardData[y][x] = ap_data->boardData[ap_data->selected_piece.y][ap_data->selected_piece.x];
            ap_data->boardData[ap_data->selected_piece.y][ap_data->selected_piece.x] = blank;
            memset(&ap_data->moveData, blank, sizeof(INT8) * 8 * 8);
            ap_data->turn++;
        } else if (ap_data->turn == ap_data->boardData[y][x] % 2) {
            ap_data->selected_piece.x = x;
            ap_data->selected_piece.y = y;

            switch (ap_data->boardData[y][x])
            {
            case W_Pawn:
                if (ap_data->boardData[y - 1][x] == blank) {
                    if (ap_data->boardData[y - 2][x] == blank && y == 6) ap_data->moveData[y - 2][x] = Move;
                    if (y > 0) ap_data->moveData[y - 1][x] = Move;
                }
                if (x + 1 < 8 && y > 0 && ap_data->boardData[y - 1][x + 1] % 2 != ap_data->turn && ap_data->boardData[y - 1][x + 1] != blank) ap_data->moveData[y - 1][x + 1] = Attack;
                if (x > 0 && y > 0 && ap_data->boardData[y - 1][x - 1] != ap_data->turn && ap_data->boardData[y - 1][x - 1] != blank) ap_data->moveData[y - 1][x - 1] = Attack;
                break;
            case B_Pawn:
                if (ap_data->boardData[y + 1][x] == blank) {
                    if (ap_data->boardData[y + 2][x] == blank && y == 1) ap_data->moveData[y + 2][x] = Move;
                    if (y < 7) ap_data->moveData[y + 1][x] = Move;
                }
                if (x + 1 < 8 && y < 7 && ap_data->boardData[y + 1][x + 1] % 2 != ap_data->turn) ap_data->moveData[y + 1][x + 1] = Attack;
                if (x > 0 && y < 7 && ap_data->boardData[y + 1][x - 1] % 2 != ap_data->turn) ap_data->moveData[y + 1][x - 1] = Attack;
                break;
            case W_Bishop:
            case B_Bishop:
                for (i = 1; y - i >= 0 && x - i >= 0 && ap_data->boardData[y - i][x - i] == blank; i++) ap_data->moveData[y - i][x - i] = Move;
                if (y - i >= 0 && x - i >= 0 && ap_data->boardData[y - i][x - i] % 2 != ap_data->turn) ap_data->moveData[y - i][x - i] = Attack;
                for (i = 1; y + i < 8 && x + i < 8 && ap_data->boardData[y + i][x + i] == blank; i++) ap_data->moveData[y + i][x + i] = Move;
                if (y + i < 8 && x + i < 8 && ap_data->boardData[y + i][x + i] % 2 != ap_data->turn) ap_data->moveData[y + i][x + i] = Attack;
                for (i = 1; y - i >= 0 && x + i < 8 && ap_data->boardData[y - i][x + i] == blank; i++) ap_data->moveData[y - i][x + i] = Move;
                if (y - i >= 0 && x + i < 8 && ap_data->boardData[y - i][x + i] % 2 != ap_data->turn) ap_data->moveData[y - i][x + i] = Attack;
                for (i = 1; y + i < 8 && x - i >= 0 && ap_data->boardData[y + i][x - i] == blank; i++) ap_data->moveData[y + i][x - i] = Move;
                if (y + i < 8 && x - i >= 0 && ap_data->boardData[y + i][x - i] % 2 != ap_data->turn) ap_data->moveData[y + i][x - i] = Attack;
                break;
            case W_Knight:
            case B_Knight:
                if (y - 2 >= 0 && x - 1 >= 0 && ap_data->boardData[y - 2][x - 1] == blank) ap_data->moveData[y - 2][x - 1] = Move;
                else if (y - 2 >= 0 && x - 1 >= 0 && ap_data->boardData[y - 2][x - 1] % 2 != ap_data->turn) ap_data->moveData[y - 2][x - 1] = Attack;
                if (y - 2 >= 0 && x + 1 < 8 && ap_data->boardData[y - 2][x + 1] == blank) ap_data->moveData[y - 2][x + 1] = Move;
                else if (y - 2 >= 0 && x + 1 < 8 && ap_data->boardData[y - 2][x + 1] % 2 != ap_data->turn) ap_data->moveData[y - 2][x + 1] = Attack;
                if (y + 2 < 8 && x - 1 >= 0 && ap_data->boardData[y + 2][x - 1] == blank) ap_data->moveData[y + 2][x - 1] = Move;
                else if (y + 2 < 8 && x - 1 >= 0 && ap_data->boardData[y + 2][x - 1] % 2 != ap_data->turn) ap_data->moveData[y + 2][x - 1] = Attack;
                if (y + 2 < 8 && x + 1 < 8 && ap_data->boardData[y + 2][x + 1] == blank) ap_data->moveData[y + 2][x + 1] = Move;
                else if (y + 2 < 8 && x + 1 < 8 && ap_data->boardData[y + 2][x + 1] % 2 != ap_data->turn) ap_data->moveData[y + 2][x + 1] = Attack;
                if (y - 1 >= 0 && x - 2 >= 0 && ap_data->boardData[y - 1][x - 2] == blank) ap_data->moveData[y - 1][x - 2] = Move;
                else if (y - 1 >= 0 && x - 2 >= 0 && ap_data->boardData[y - 1][x - 2] % 2 != ap_data->turn) ap_data->moveData[y - 1][x - 2] = Attack;
                if (y - 1 >= 0 && x + 2 < 8 && ap_data->boardData[y - 1][x + 2] == blank) ap_data->moveData[y - 1][x + 2] = Move;
                else if (y - 1 >= 0 && x + 2 < 8 && ap_data->boardData[y - 1][x + 2] % 2 != ap_data->turn) ap_data->moveData[y - 1][x + 2] = Attack;
                if (y + 1 < 8 && x - 2 >= 0 && ap_data->boardData[y + 1][x - 2] == blank) ap_data->moveData[y + 1][x - 2] = Move;
                else if (y + 1 < 8 && x - 2 >= 0 && ap_data->boardData[y + 1][x - 2] % 2 != ap_data->turn) ap_data->moveData[y + 1][x - 2] = Attack;
                if (y + 1 < 8 && x + 2 < 8 && ap_data->boardData[y + 1][x + 2] == blank) ap_data->moveData[y + 1][x + 2] = Move;
                else if (y + 1 < 8 && x + 2 < 8 && ap_data->boardData[y + 1][x + 2] % 2 != ap_data->turn) ap_data->moveData[y + 1][x + 2] = Attack;
                break;
            case W_Rook:
            case B_Rook:
                for (i = 1; x - i >= 0 && ap_data->boardData[y][x - i] == blank; i++) ap_data->moveData[y][x - i] = Move;
                if (x - i >= 0 && ap_data->boardData[y][x - i] % 2 != ap_data->turn) ap_data->moveData[y][x - i] = Attack;
                for (i = 1; x + i < 8 && ap_data->boardData[y][x + i] == blank; i++) ap_data->moveData[y][x + i] = Move;
                if (x + i < 8 && ap_data->boardData[y][x + i] % 2 != ap_data->turn) ap_data->moveData[y][x + i] = Attack;
                for (i = 1; y - i >= 0 && ap_data->boardData[y - i][x] == blank; i++) ap_data->moveData[y - i][x] = Move;
                if (y - i >= 0 && ap_data->boardData[y - i][x] % 2 != ap_data->turn) ap_data->moveData[y - i][x] = Attack;
                for (i = 1; y + i < 8 && ap_data->boardData[y + i][x] == blank; i++) ap_data->moveData[y + i][x] = Move;
                if (y + i < 8 && ap_data->boardData[y + i][x] % 2 != ap_data->turn) ap_data->moveData[y + i][x] = Attack;
                break;
            case W_Queen:
            case B_Queen:
                for (i = 1; y - i >= 0 && x - i >= 0 && ap_data->boardData[y - i][x - i] == blank; i++) ap_data->moveData[y - i][x - i] = Move;
                if (y - i >= 0 && x - i >= 0 && ap_data->boardData[y - i][x - i] % 2 != ap_data->turn) ap_data->moveData[y - i][x - i] = Attack;
                for (i = 1; y + i < 8 && x + i < 8 && ap_data->boardData[y + i][x + i] == blank; i++) ap_data->moveData[y + i][x + i] = Move;
                if (y + i < 8 && x + i < 8 && ap_data->boardData[y + i][x + i] % 2 != ap_data->turn) ap_data->moveData[y + i][x + i] = Attack;
                for (i = 1; y - i >= 0 && x + i < 8 && ap_data->boardData[y - i][x + i] == blank; i++) ap_data->moveData[y - i][x + i] = Move;
                if (y - i >= 0 && x + i < 8 && ap_data->boardData[y - i][x + i] % 2 != ap_data->turn) ap_data->moveData[y - i][x + i] = Attack;
                for (i = 1; y + i < 8 && x - i >= 0 && ap_data->boardData[y + i][x - i] == blank; i++) ap_data->moveData[y + i][x - i] = Move;
                if (y + i < 8 && x - i >= 0 && ap_data->boardData[y + i][x - i] % 2 != ap_data->turn) ap_data->moveData[y + i][x - i] = Attack;
                for (i = 1; x - i >= 0 && ap_data->boardData[y][x - i] == blank; i++) ap_data->moveData[y][x - i] = Move;
                if (x - i >= 0 && ap_data->boardData[y][x - i] % 2 != ap_data->turn) ap_data->moveData[y][x - i] = Attack;
                for (i = 1; x + i < 8 && ap_data->boardData[y][x + i] == blank; i++) ap_data->moveData[y][x + i] = Move;
                if (x + i < 8 && ap_data->boardData[y][x + i] % 2 != ap_data->turn) ap_data->moveData[y][x + i] = Attack;
                for (i = 1; y - i >= 0 && ap_data->boardData[y - i][x] == blank; i++) ap_data->moveData[y - i][x] = Move;
                if (y - i >= 0 && ap_data->boardData[y - i][x] % 2 != ap_data->turn) ap_data->moveData[y - i][x] = Attack;
                for (i = 1; y + i < 8 && ap_data->boardData[y + i][x] == blank; i++) ap_data->moveData[y + i][x] = Move;
                if (y + i < 8 && ap_data->boardData[y + i][x] % 2 != ap_data->turn) ap_data->moveData[y + i][x] = Attack;
                break;
            case W_King:
            case B_King:
                for (int j = -1; j <= 1; j++)
                    for (int k = -1; k <= 1; k++) {
                        if (y + j < 0 || y + j >= 8 || x + k < 0 || x + k >= 8) continue;
                        else if (ap_data->boardData[y + j][x + k] == blank) ap_data->moveData[y + j][x + k] = Move;
                        else if (ap_data->boardData[y + j][x + k] % 2 != ap_data->turn) ap_data->moveData[y + j][x + k] = Attack;
                    }
                break;
            default:
                break;
            }
        }
        drawboard();
    }
}

void OnMouseLeftUP(int a_mixed_key, POINT a_pos)
{
    g_clicked_flag = 2;
}

void OnMouseMove(int a_mixed_key, POINT a_pos)
{
    pGameData ap_data = (pGameData)GetAppData();

    if (g_clicked_flag == 1) {
        ;
    }
    Rectangle(400, 10, 500, 100, 0x00aaaaaa, 0x00aaaaaa);
    TextOut(400, 10, "%d, %d", a_pos.x, a_pos.y);
    TextOut(400, 30, "%d, %d", a_pos.x / BOARD_SIZE, a_pos.y / BOARD_SIZE);
    TextOut(400, 70, "%d | %d, %d", ap_data->turn, ap_data->is_king_moved[1], ap_data->is_king_moved[0]);
    if (a_pos.x / BOARD_SIZE < 8 && a_pos.y / BOARD_SIZE < 8)TextOut(400, 50, "%d", ap_data->boardData[a_pos.y / BOARD_SIZE][a_pos.x / BOARD_SIZE]);
    ShowDisplay(); // 정보를 윈도우에 출력한다.
}

MOUSE_MESSAGE(OnMouseLeftDown, OnMouseLeftUP, OnMouseMove)

int main()
{
    GameData data = { 0, };
    SetAppData(&data, sizeof(GameData));
    pGameData ap_data = (pGameData)GetAppData();
    memcpy(ap_data->boardData, &initialBoard, sizeof(INT8) * 64);
    ap_data->turn = 1;

    readImages();
    drawboard();

    return 0;
}

void drawboard()
{
    pGameData ap_data = (pGameData)GetAppData();

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((x + y) & 1) { SelectBrushObject(RGB(119, 149, 86)); SelectPenObject(RGB(119, 149, 86), 0, PS_SOLID); }
            else { SelectBrushObject(RGB(235, 236, 208)); SelectPenObject(RGB(235, 236, 208), 0, PS_SOLID); }
            Rectangle(x * BOARD_SIZE, y * BOARD_SIZE, BOARD_SIZE + (x * BOARD_SIZE), BOARD_SIZE + (y * BOARD_SIZE));
            if (ap_data->boardData[y][x]) DrawImageGP(ap_data->pieces_image[ap_data->boardData[y][x]], x * BOARD_SIZE, y * BOARD_SIZE, BOARD_SIZE, BOARD_SIZE);
            if (ap_data->moveData[y][x]) DrawImageGP(ap_data->pieces_image[ap_data->moveData[y][x]], x * BOARD_SIZE, y * BOARD_SIZE, BOARD_SIZE, BOARD_SIZE);
        }
    }

    ShowDisplay(); // 정보를 윈도우에 출력한다.
}

void readImages()
{
    pGameData ap_data = (pGameData)GetAppData();

    ap_data->pieces_image[W_Pawn]   = LoadImageGP(".\\pieces\\W_Pawn.png");
    ap_data->pieces_image[W_Bishop] = LoadImageGP(".\\pieces\\W_Bishop.png");
    ap_data->pieces_image[W_Knight] = LoadImageGP(".\\pieces\\W_Knight.png");
    ap_data->pieces_image[W_Rook]   = LoadImageGP(".\\pieces\\W_Rook.png");
    ap_data->pieces_image[W_Queen]  = LoadImageGP(".\\pieces\\W_Queen.png");
    ap_data->pieces_image[W_King]   = LoadImageGP(".\\pieces\\W_King.png");

    ap_data->pieces_image[B_Pawn]   = LoadImageGP(".\\pieces\\B_Pawn.png");
    ap_data->pieces_image[B_Bishop] = LoadImageGP(".\\pieces\\B_Bishop.png");
    ap_data->pieces_image[B_Knight] = LoadImageGP(".\\pieces\\B_Knight.png");
    ap_data->pieces_image[B_Rook]   = LoadImageGP(".\\pieces\\B_Rook.png");
    ap_data->pieces_image[B_Queen]  = LoadImageGP(".\\pieces\\B_Queen.png");
    ap_data->pieces_image[B_King]   = LoadImageGP(".\\pieces\\B_King.png");

    ap_data->pieces_image[Attack]   = LoadImageGP(".\\pieces\\Attack.png");
    ap_data->pieces_image[Move]      = LoadImageGP(".\\pieces\\Way.png");
}