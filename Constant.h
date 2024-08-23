#ifndef __CONSTANT_H__
#define __CONSTANT_H__

enum Chess_Pieces {
	blank,		// Nothing on board
	W_Pawn,		// White Pawn
	B_Pawn,		// Black Pawn
	W_Bishop,	// White Bishop
	B_Bishop,	// Black Bishop
	W_Knight,	// White Knight
	B_Knight,	// Black Knight
	W_Rook,		// White Rook
	B_Rook,		// Black Rook
	W_Queen,	// White Queen
	B_Queen,	// Black Queen
	W_King,		// White King
	B_King,		// Black King
	Attack,		// Can Attack
	Move,		// Show move
};

const INT8 initialBoard[8][8] = { { B_Rook, B_Knight, B_Bishop, B_Queen, B_King, B_Bishop, B_Knight, B_Rook },
								  { B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn, B_Pawn },
								  { blank, },
								  { blank, },
								  { blank, },
								  { blank, },
								  { W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn, W_Pawn },
								  { W_Rook, W_Knight, W_Bishop, W_Queen, W_King, W_Bishop, W_Knight, W_Rook } 
								};

#define BOARD_SIZE (45)
#define PADDING BOARD_SIZE / (5)

#endif // !__CONSTANT_H__
