// ALU.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
using namespace std;

// NAND and logical operations (INV, AND, OR, NOR, XOR)
bool NAND(bool a, bool b) {
    return !(a && b);
}
bool INV(bool a)
{
    return NAND(a, a);
}
bool AND(bool a, bool b)
{
    return NAND(NAND(a, b), NAND(a, b));
}
bool OR(bool a, bool b)
{
    return NAND(NAND(a, a), NAND(b, b));
}
bool NOR(bool a, bool b)
{
    return NAND((NAND(NAND(a, a), NAND(b, b))), NAND(NAND(a, a), NAND(b, b)));
}
bool XOR(bool a, bool b)
{
    return NAND(NAND(a, NAND(a, b)), NAND(b, NAND(a, b)));
}

// 1-bit ALU decoder (2 signals, 4 possible outputs)
void decoder(bool s[2], bool is[4]) {
    is[0] = AND(INV(s[0]), INV(s[1]));
    is[1] = AND(INV(s[0]), s[1]);
    is[2] = AND(s[0], INV(s[1]));
    is[3] = AND(s[0], s[1]);
};

// Half-Adder
void halfAdder(bool A, bool B, bool& sum, bool& carry)
{
    carry = AND(A, B);
    sum = XOR(A, B);
};

// Full-Adder
void fullAdder(bool A, bool B, bool& sum, bool& output)
{
    bool carry1;
    bool carry2;
    bool result;
    halfAdder(A, B, sum, carry1);
    result = sum;
    halfAdder(sum, output, sum, carry2);
    output = OR(carry1, carry2);
};

// 1-bit ALU
void oneBitAlu(bool A, bool B, bool ENA, bool ENB, bool s[2], bool& output, bool& carry)
{
    A = AND(A, ENA);
    B = AND(B, ENB);
    bool decoderValues[4];
    decoder(s, decoderValues);
    if (decoderValues[0])
    {
        output = INV(A);
    }
    else if (decoderValues[1])
    {
        output = INV(B);
    }
    else if (decoderValues[2])
    {
        output = XOR(A, B);
    }
    else if (decoderValues[3])
    {
        fullAdder(A, B, output, carry);
    }
};

// 8-bit ALU decoder (3 signals, 8 possible outputs)
void decoder8(bool s8[3], bool output[8])
{
    output[0] = AND(AND(INV(s8[0]), INV(s8[1])), INV(s8[2]));
    output[1] = AND(AND(INV(s8[0]), INV(s8[1])), s8[2]);
    output[2] = AND(AND(INV(s8[0]), (s8[1])), INV(s8[2]));
    output[3] = AND(AND(INV(s8[0]), (s8[1])), s8[2]);
    output[4] = AND(AND(s8[0], INV(s8[1])), INV(s8[2]));
    output[5] = AND(AND(s8[0], INV(s8[1])), s8[2]);
    output[6] = AND(AND(s8[0], s8[1]), INV(s8[2]));
    output[7] = AND(AND(s8[0], s8[1]), s8[2]);
};

// Shift operation
void shift(bool A[], bool shiftDirection, bool C[], bool& carry) // shiftDirection(1 - right, 0 - left) 
{
    for (int i = 0; i < 8; i++)
    {
        if (i == 0)
        {
            C[i] = AND(A[1], INV(shiftDirection));
        }
        else if (i == 7)
        {
            C[i] = AND(A[6], shiftDirection);
        }
        else
        {
            C[i] = OR(AND(A[i - 1], shiftDirection), AND(A[i + 1], INV(shiftDirection)));
        }
    }
    if (XOR(A[0], C[0]))
    {
        carry = 1;
    }
};

// Shift operation for 16-bit system
void shift1(bool A[], bool shiftDirection, bool C[], bool& carry) // shiftDirection(1 - right, 0 - left) 
{
    for (int i = 0; i < 16; i++)
    {
        if (i == 0)
        {
            C[i] = AND(A[1], INV(shiftDirection));
        }
        else if (i == 15)
        {
            C[i] = AND(A[14], shiftDirection);
        }
        else
        {
            C[i] = OR(AND(A[i - 1], shiftDirection), AND(A[i + 1], INV(shiftDirection)));
        }
    }
    if (XOR(A[0], C[0]))
    {
        carry = 1;
    }
};

// 8-bit ALU
void eightBitALU(bool A[], bool B[], bool s8[3], bool& carry, bool& F, bool& shiftDirection) /////////////////
{
    bool ENA, ENB;
    bool output[8];
    bool result;
    bool s[2]; // Signal for 1-bit decoder
    bool resultValues[8];

    decoder8(s8, resultValues);

    // No operation
    if (resultValues[0] || resultValues[6] || resultValues[7])
    {
        cout << "A: ";
        for (int i = 0; i < 8; i++)
        {
            cout << A[i];
            if (i != 7)
            {
                cout << " ";
            }
            else cout << endl;
        }
        cout << "B: ";
        for (int i = 0; i < 8; i++)
        {
            cout << B[i];
            if (i != 7)
            {
                cout << " ";
            }
        }
        ENA = 0;
        ENB = 0;
        for (int i = 0; i < 8; i++)
        {
            A[i] = AND(A[i], ENA);
            B[i] = AND(B[i], ENB);
        }
        cout << endl;
        cout << "No operation" << endl;
    }

    // Negative number (1 variant: (-B))
    else if (resultValues[1])
    {
        s[0] = 0; // A 00 | B 01
        s[1] = 1;
        bool C[8] = { 0,0,0,0,0,0,0,1 };
        ENA = 0;
        ENB = 1;

        // Inversion
        for (int i = 0; i < 8; i++)
        {
            oneBitAlu(A[i], B[i], ENA, ENB, s, result, carry);
            output[i] = result;
        }

        // Add one after inversion
        bool carryFlag = 0;
        s[0] = 1;
        s[1] = 1;

        ENA = 1;
        ENB = 1;

        for (int i = 7; i >= 0; i--)
        {
            oneBitAlu(output[i], C[i], ENA, ENB, s, result, carry);
            output[i] = result;
            if (i == 0 && carry == 1)
            {
                carryFlag = 1;
            }
        }
        // Output result
        cout << "Negative (B) = ";
        for (int i = 0; i < 8; i++)
        {
            cout << output[i];
            if (i != 7)
            {
                cout << " ";
            }
        }
    }

    // Comparison
    else if (resultValues[2])
    {
        s[0] = 1;
        s[1] = 0;
        F = 1;
        ENA = 1;
        ENB = 1;

        for (int i = 0; i < 8; i++)
        {
            oneBitAlu(A[i], B[i], ENA, ENB, s, result, carry);
            output[i] = result;
        }

        F = NOR(OR(OR(OR(OR(OR(OR(output[0], output[1]), output[2]), output[3]), output[4]), output[5]), output[6]), output[7]);

        cout << "A: ";
        for (int j = 0; j < 8; j++)
        {
            cout << A[j] << " ";
        }
        cout << endl;
        cout << "B: ";
        for (int j = 0; j < 8; j++)
        {
            cout << B[j] << " ";
        }
        cout << endl;
        cout << "Are equal? (F): " << F;
    }

    // Addition
    else if (resultValues[3])
    {
        bool carryFlag = 0;
        s[0] = 1;
        s[1] = 1;

        ENA = 1;
        ENB = 1;

        for (int i = 7; i >= 0; i--)
        {
            oneBitAlu(A[i], B[i], ENA, ENB, s, result, carry);
            output[i] = result;
            if (i == 0 && carry == 1)
            {
                carryFlag = 1;
            }
        }

        cout << "A: ";
        for (int j = 0; j < 8; j++)
        {
            cout << A[j] << " ";
        }
        cout << endl;
        cout << "B: ";
        for (int j = 0; j < 8; j++)
        {
            cout << B[j] << " ";
        }
        cout << endl;
        cout << "Sum: ";
        for (int i = 0; i < 8; i++)
        {
            cout << output[i] << " ";
        }
        cout << endl;
        cout << "Overflow flag (carry): " << carryFlag;
    }

    // Multiplication   
    else if (resultValues[4]) 
    {
        bool ENA = 1;
        bool ENB = 1;

        // Result of multiplication (16-bit)
        bool product[16] = { 0 };  
        
        // A extended to 16 bits (for proper storage)
        bool AS[16] = { 0 };  

        
        for (int i = 0; i < 8; i++) {
            AS[8 + i] = A[i];
        }

        
        bool temp[16] = { 0 };  

        // Loop through each bit of B 
        for (int i = 7; i >= 0; i--) {
            if (B[i] == 1) {  // If the i-th bit of B is 1, add the shifted A to temp
                // Add AS (A extended to 16 bits) to temp (accumulator)
                bool carry = 0;
                bool sum;
                for (int j = 0; j < 16; j++) {
                    oneBitAlu(temp[j], AS[j], ENA, ENB, s, sum, carry);
                    temp[j] = sum;  // Update the temp array with the sum
                }
            }

            // Shift left (direction 0 = left)
            shift1(AS, 0, AS, carry);  
        }

        //Store the result in product
        for (int i = 0; i < 16; i++) {
            product[i] = temp[i];  // Copy the final product from temp to product
        }

        cout << "A: ";
        for (int j = 0; j < 8; j++)
        {
            cout << A[j] << " ";
        }
        cout << endl;
        cout << "B: ";
        for (int j = 0; j < 8; j++)
        {
            cout << B[j] << " ";
        }
        cout << endl;
        cout << endl;
        cout << "Multiplication: ";
        for (int i = 0; i < 16; i++) {
            cout << product[i] << " ";
        }
        }

    // Shift operation
    else if (resultValues[5])
    {
        bool carryFlag = 0;

        shift(A, shiftDirection, output, carryFlag);
        if (shiftDirection)
        {
            cout << "Shift direction: right";
        }
        else
        {
            cout << "Shift direction: left";
        }
        cout << endl;
        cout << "A: ";
        for (int i = 0; i < 8; i++)
        {
            cout << output[i] << " ";
        }
        cout << endl;
        cout << "Overflow flag (carry): " << carryFlag;
    }
};

int main()
{
    // Bit variables and signal
    bool A[8] = { 0,1,1,0,0,0,0,1 };  // A = 0b01000001
    bool B[8] = { 0,1,0,0,1,1,0,1 };  // B = 0b01001101
    bool s8[3] = { 1,0,0 };  // Selector for operation (this will select a specific operation in ALU)
    bool postumioPuse = 1;  // Shift direction (1 - right shift, 0 - left shift)
    bool carry = 0, F = 1;  // Flags: carry and result flag

    // Call the 8-bit ALU function with the provided inputs
    eightBitALU(A, B, s8, carry, F, postumioPuse);

    return 0;  // End of the program
}