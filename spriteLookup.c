#include "spriteLookup.h"
#include "map.h"

Sprite gSpriteLookup[100] = {
	{1, 2}, // 0 - solid stone / dark
	{2, 2}, // 1 - cobblestone ground
	{6, 1}, // 2 - :)
	{0, 2}, // 3 - grassy ground
	{0, 3}, // 4 - tree 1
	{1, 3}, // 5 - tree 2
	{2, 3}, // 6 - tree 3
	{0, 4}, // 7 - wood wall
	{0, 6}, // 8 - human, cloth tunic
	{3, 2}, // 9 - wooden plank floor
};


Sprite lookupChar(char c) {
	int i = 0;
	switch (c) {
	case 'A': i = 0;	break;
	case 'B': i = 1;	break;
	case 'C': i = 2;	break;
	case 'D': i = 3;	break;
	case 'E': i = 4;	break;
	case 'F': i = 5;	break;
	case 'G': i = 6;	break;
	case 'H': i = 7;	break;
	case 'I': i = 8;	break;
	case 'J': i = 9;	break;
	case 'K': i = 10;	break;
	case 'L': i = 11;	break;
	case 'M': i = 12;	break;
	case 'N': i = 13;	break;
	case 'O': i = 14;	break;
	case 'P': i = 15;	break;
	case 'Q': i = 16;	break;
	case 'R': i = 17;	break;
	case 'S': i = 18;	break;
	case 'T': i = 19;	break;
	case 'U': i = 20;	break;
	case 'V': i = 21;	break;
	case 'W': i = 22;	break;
	case 'X': i = 23;	break;
	case 'Y': i = 24;	break;
	case 'Z': i = 25;	break;
	case 'a': i = 26;	break;
	case 'b': i = 27;	break;
	case 'c': i = 28;	break;
	case 'd': i = 29;	break;
	case 'e': i = 30;	break;
	case 'f': i = 31;	break;
	case 'g': i = 32;	break;
	case 'h': i = 33;	break;
	case 'i': i = 34;	break;
	case 'j': i = 35;	break;
	case 'k': i = 36;	break;
	case 'l': i = 37;	break;
	case 'm': i = 38;	break;
	case 'n': i = 39;	break;
	case 'o': i = 40;	break;
	case 'p': i = 41;	break;
	case 'q': i = 42;	break;
	case 'r': i = 43;	break;
	case 's': i = 44;	break;
	case 't': i = 45;	break;
	case 'u': i = 46;	break;
	case 'v': i = 47;	break;
	case 'w': i = 48;	break;
	case 'x': i = 49;	break;
	case 'y': i = 50;	break;
	case 'z': i = 51;	break;
	case '1': i = 52;	break;
	case '2': i = 53;	break;
	case '3': i = 54;	break;
	case '4': i = 55;	break;
	case '5': i = 56;	break;
	case '6': i = 57;	break;
	case '7': i = 58;	break;
	case '8': i = 59;	break;
	case '9': i = 60;	break;
	case '0': i = 61;	break;
	case '!': i = 62;	break;
	case '?': i = 63;	break;
	case '.': i = 64;	break;
	case ',': i = 65;	break;
	case '-': i = 66;	break;
	case '+': i = 67;	break;
	case '=': i = 68;	break;
	case '"': i = 69;	break;
	case '#': i = 70;	break;
	case '(': i = 71;	break;
	case ')': i = 72;	break;
	case ':': i = 73;	break;
	case '_': i = 74;	break;
	case '/': i = 75;	break;
	case '\\': i = 76;	break;
	case ' ': i = 77;	break;
	default: i = 78;	break;
	}

	Sprite sp = { i, 0 };
	return sp;
}
