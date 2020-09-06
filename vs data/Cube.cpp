#include <glew.h>
#include <iostream>

class Cube {
	float cX, cY, cZ;
	float halfSide;
	float cvc[8][3];
	float coords[72];
	float colors[72];

	unsigned int vertexArray;
	unsigned int buffer[2];
public:
	Cube(float cXi, float cYi, float cZi, float halfSize,
		float side1clrr, float side1clrg, float side1clrb, 
		float side2clrr, float side2clrg, float side2clrb, 
		float side3clrr, float side3clrg, float side3clrb, 
		float side4clrr, float side4clrg, float side4clrb, 
		float side5clrr, float side5clrg, float side5clrb, 
		float side6clrr, float side6clrg, float side6clrb) {
		this->cX = cXi;
		this->cY = cYi;
		this->cZ = cZi;
		this->halfSide = halfSize;

		cvc[0][0] = cX - halfSide; cvc[0][1] = cY - halfSide; cvc[0][2] = cZ + halfSide;
		cvc[1][0] = cX + halfSide; cvc[1][1] = cY - halfSide; cvc[1][2] = cZ + halfSide;
		cvc[2][0] = cX + halfSide; cvc[2][1] = cY + halfSide; cvc[2][2] = cZ + halfSide;
		cvc[3][0] = cX - halfSide; cvc[3][1] = cY + halfSide; cvc[3][2] = cZ + halfSide;

		cvc[4][0] = cX - halfSide; cvc[4][1] = cY - halfSide; cvc[4][2] = cZ - halfSide;
		cvc[5][0] = cX + halfSide; cvc[5][1] = cY - halfSide; cvc[5][2] = cZ - halfSide;
		cvc[6][0] = cX + halfSide; cvc[6][1] = cY + halfSide; cvc[6][2] = cZ - halfSide;
		cvc[7][0] = cX - halfSide; cvc[7][1] = cY + halfSide; cvc[7][2] = cZ - halfSide;

		coords[0] = cvc[0][0]; coords[1] = cvc[0][1]; coords[2] = cvc[0][2];
		coords[3] = cvc[1][0]; coords[4] = cvc[1][1]; coords[5] = cvc[1][2];
		coords[6] = cvc[2][0]; coords[7] = cvc[2][1]; coords[8] = cvc[2][2];
		coords[9] = cvc[3][0]; coords[10] = cvc[3][1]; coords[11] = cvc[3][2];

		coords[12] = cvc[7][0]; coords[13] = cvc[7][1]; coords[14] = cvc[7][2];
		coords[15] = cvc[6][0]; coords[16] = cvc[6][1]; coords[17] = cvc[6][2];
		coords[18] = cvc[5][0]; coords[19] = cvc[5][1]; coords[20] = cvc[5][2];
		coords[21] = cvc[4][0]; coords[22] = cvc[4][1]; coords[23] = cvc[4][2];

		coords[24] = cvc[3][0]; coords[25] = cvc[3][1]; coords[26] = cvc[3][2];
		coords[27] = cvc[2][0]; coords[28] = cvc[2][1]; coords[29] = cvc[2][2];
		coords[30] = cvc[6][0]; coords[31] = cvc[6][1]; coords[32] = cvc[6][2];
		coords[33] = cvc[7][0]; coords[34] = cvc[7][1]; coords[35] = cvc[7][2];

		coords[36] = cvc[4][0]; coords[37] = cvc[4][1]; coords[38] = cvc[4][2];
		coords[39] = cvc[5][0]; coords[40] = cvc[5][1]; coords[41] = cvc[5][2];
		coords[42] = cvc[1][0]; coords[43] = cvc[1][1]; coords[44] = cvc[1][2];
		coords[45] = cvc[0][0]; coords[46] = cvc[0][1]; coords[47] = cvc[0][2];

		coords[48] = cvc[4][0]; coords[49] = cvc[4][1]; coords[50] = cvc[4][2];
		coords[51] = cvc[0][0]; coords[52] = cvc[0][1]; coords[53] = cvc[0][2];
		coords[54] = cvc[3][0]; coords[55] = cvc[3][1]; coords[56] = cvc[3][2];
		coords[57] = cvc[7][0]; coords[58] = cvc[7][1]; coords[59] = cvc[7][2];

		coords[60] = cvc[6][0]; coords[61] = cvc[6][1]; coords[62] = cvc[6][2];
		coords[63] = cvc[2][0]; coords[64] = cvc[2][1]; coords[65] = cvc[2][2];
		coords[66] = cvc[1][0]; coords[67] = cvc[1][1]; coords[68] = cvc[1][2];
		coords[69] = cvc[5][0]; coords[70] = cvc[5][1]; coords[71] = cvc[5][2];


		for (int i = 0; i < 12; i += 3) {
			colors[i] = side1clrr;
			colors[i+1] = side1clrg;
			colors[i+2] = side1clrb;
		}
		for (int i = 12; i < 24; i += 3) {
			colors[i] = side2clrr;
			colors[i + 1] = side2clrg;
			colors[i + 2] = side2clrb;
		}
		for (int i = 24; i < 36; i += 3) {
			colors[i] = side3clrr;
			colors[i + 1] = side3clrg;
			colors[i + 2] = side3clrb;
		}
		for (int i = 36; i < 48; i += 3) {
			colors[i] = side4clrr;
			colors[i + 1] = side4clrg;
			colors[i + 2] = side4clrb;
		}
		for (int i = 48; i < 60; i += 3) {
			colors[i] = side5clrr;
			colors[i + 1] = side5clrg;
			colors[i + 2] = side5clrb;
		}
		for (int i = 60; i < 72; i += 3) {
			colors[i] = side6clrr;
			colors[i + 1] = side6clrg;
			colors[i + 2] = side6clrb;
		}

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glGenBuffers(2, buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 72 + 1, coords, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
		glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 72 + 1, colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	};

	bool collisionCheckX(float currPosX, float nextPosX, float currPosZ, float currPosY) {
		if (abs(currPosY) < abs(cY + halfSide + 0.15f)) {
			if (abs(currPosZ - cZ) < halfSide + 0.15) {
				if (abs(nextPosX - cX) > halfSide + 0.15f) {
					return true;
				}
				else if (abs(nextPosX - cX) > abs(currPosX - cX)) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}

	bool collisionCheckZ(float currPosZ, float nextPosZ, float currPosX, float currPosY) {
		if (abs(currPosY) < abs(cY + halfSide + 0.15f)) {
			if (abs(currPosX - cX) < halfSide + 0.15) {
				if (abs(nextPosZ - cZ) > halfSide + 0.15f) {
					return true;
				}
				else if (abs(nextPosZ - cZ) > abs(currPosZ - cZ)) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}

	bool collisionCheckY(float currPosX, float currPosZ, float nextPosY) {
		if (abs(currPosX - cX) < abs(halfSide + 0.15f) && (abs(currPosZ - cZ) < abs(halfSide + 0.15f))) {
			if (abs(nextPosY - cY) > abs(cY + halfSide)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}

	void drawIt() {
		glBindVertexArray(vertexArray);
		glDrawArrays(GL_QUADS, 0, 24);
		glBindVertexArray(0);
	}
};