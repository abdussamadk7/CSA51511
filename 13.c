#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to multiply matrices
void multiplyMatrices(int result[2], int matrix[2][2], int vector[2]) {
    result[0] = (matrix[0][0] * vector[0] + matrix[0][1] * vector[1]) % 26;
    result[1] = (matrix[1][0] * vector[0] + matrix[1][1] * vector[1]) % 26;
}

// Function to find modulo inverse
int modInverse(int a, int m) {
    int x;
	a = a % m;
    for ( x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return 1;
}

// Function to encrypt plaintext
void encrypt(char plaintext[], char ciphertext[], int key[2][2]) {
    int len = strlen(plaintext);
    int vector[2], result[2];
    int i;
    for ( i = 0; i < len; i += 2) {
        vector[0] = plaintext[i] - 'a';
        vector[1] = plaintext[i + 1] - 'a';

        multiplyMatrices(result, key, vector);

        ciphertext[i] = result[0] + 'a';
        ciphertext[i + 1] = result[1] + 'a';
    }
    ciphertext[len] = '\0';
}

// Function to decrypt ciphertext
void decrypt(char ciphertext[], char decrypted[], int key[2][2]) {
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = (det % 26 + 26) % 26;
    int invDet = modInverse(det, 26);

    int adj[2][2] = {
        {key[1][1], -key[0][1]},
        {-key[1][0], key[0][0]}
    };

    int i,j,invKey[2][2];
    for ( i = 0; i < 2; i++) {
        for ( j = 0; j < 2; j++) {
            invKey[i][j] = (adj[i][j] * invDet) % 26;
            if (invKey[i][j] < 0) invKey[i][j] += 26;
        }
    }

    int len = strlen(ciphertext);
    int vector[2], result[2];
    for (i = 0; i < len; i += 2) {
        vector[0] = ciphertext[i] - 'a';
        vector[1] = ciphertext[i + 1] - 'a';

        multiplyMatrices(result, invKey, vector);

        decrypted[i] = result[0] + 'a';
        decrypted[i + 1] = result[1] + 'a';
    }
    decrypted[len] = '\0';
}
