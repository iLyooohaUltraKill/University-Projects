#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream ftxt("q1_encr.txt"); // Open text file for reading input
    ifstream fbin("decryptor.bin", ios::binary); // Open binary file for reading instructions
    ofstream f2("VMOUT.txt"); // Output file for results
    char programCounter = 0;
    char registers[16] = { 0 }; // Initialize 16 registers with 0
    char instructions[17]{ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11 };
    char flags = 0b00000010; // Set initial flags
    char memory[256] = { 0 }; // Initialize memory
    char temp;
    char i = 0;

    fbin >> noskipws; // Set the binary file stream to not skip whitespaces
    while (fbin.get(temp))
    {
        memory[i] = temp; // Store binary data into memory
        i++;
    }
    fbin.close(); // Close the binary file

    // Start executing instructions from memory
    while (memory[programCounter] != instructions[10]) // Loop until the RET instruction (0x0B) is encountered
    {
        // Increment register RX by 1
        if (memory[programCounter] == instructions[0]) // 01 INC RX+1
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4; // Extract first register
            reg2 = (memory[programCounter + 1] & 0b00001111); // Extract second register
            registers[reg2]++;

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2; // Move to next instruction
        }

        // Decrement register RX by 1
        if (memory[programCounter] == instructions[1]) // 02 DEC RX-1
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            registers[reg2]--;

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2;
        }

        // Move the value of register RX to register RY
        if (memory[programCounter] == instructions[2]) // 03 MOV RX=RY
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            registers[reg2] = registers[reg1];

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2;
        }

        // Move constant value to register R0
        if (memory[programCounter] == instructions[3]) // 04 MOVC R0=CONST
        {
            registers[0] = memory[programCounter + 1];
            programCounter += 2;
        }

        // Perform left shift operation on register RX
        if (memory[programCounter] == instructions[4]) // 05 LSL RX<<
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            registers[reg2] = (registers[reg2] << 1);

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2;
        }

        // Perform right shift operation on register RX
        if (memory[programCounter] == instructions[5]) // 06 LSR RX>>
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            registers[reg2] = (registers[reg2] >> 1);

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2;
        }

        // Jump to a new program counter location with a constant offset
        if (memory[programCounter] == instructions[6]) // 07 JMP programCounter + const
        {
            programCounter += memory[programCounter + 1];
        }

        // Jump if zero flag is set
        if (memory[programCounter] == instructions[7]) // 08 JZ programCounter+const if (zero_flag == 1)
        {
            if ((flags & 0b000001000) >> 3 == 1)
            {
                programCounter += memory[programCounter + 1];
            }
            else {
                programCounter += 2;
            }
        }

        // Jump if zero flag is not set
        if (memory[programCounter] == instructions[8]) // 09 JNZ programCounter+const if (zero_flag == 0)
        {
            if ((flags & 0b000001000) >> 3 == 0)
                programCounter += memory[programCounter + 1];
            else {
                programCounter += 2;
            }
        }

        // Jump if EOF flag is set
        if (memory[programCounter] == instructions[9]) // 0A JFE programCounter+const if (eof_flag == 1)
        {
            if ((flags & 0b00010000) >> 4 == 1)
            {
                programCounter += memory[programCounter + 1];
            }
            else {
                programCounter += 2;
            }
        }

        // Return and end the program
        if (memory[programCounter] == instructions[10]) // 0B RET ends the work
        {
            break;
        }

        // Add RX and RY
        if (memory[programCounter] == instructions[11]) // 0C ADD RX=RX+RY
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            registers[reg2] += registers[reg1];

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2;
        }

        // Subtract RX from RY
        if (memory[programCounter] == instructions[12]) // 0D SUB RX-RY
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            registers[reg2] -= registers[reg1];

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2;
        }

        // Perform XOR on RX and RY
        if (memory[programCounter] == instructions[13]) // 0E XOR RX=RX^RY
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            registers[reg2] = registers[reg2] ^ registers[reg1];

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2;
        }

        // Perform OR on RX and RY
        if (memory[programCounter] == instructions[14]) // 0F OR RX=RX|RY
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            registers[reg2] = registers[reg2] | registers[reg1];

            // Set flag if register becomes zero
            if (registers[reg2] == 0)
            {
                flags = flags | (1 << 3);
            }
            else {
                flags = flags & 0b11110111;
            }

            programCounter += 2;
        }

        // Read input character into register RX and check for EOF
        if (memory[programCounter] == instructions[15]) // 10 IN TXTREAD + EOF_CHECK
        {
            ftxt.get(temp);
            registers[memory[programCounter + 1]] = temp;
            if (ftxt.eof())
            {
                flags = flags | (1 << 4);
            }

            programCounter += 2;
        }

        // Output the value of RX
        if (memory[programCounter] == instructions[16]) // 11 OUT COUT<<RX
        {
            int reg1, reg2;
            reg1 = (memory[programCounter + 1] & 0b11110000) >> 4;
            reg2 = (memory[programCounter + 1] & 0b00001111);
            cout << registers[reg2];

            if (registers[reg2] == 0b00001010) // Check for newline character (0A)
            {
                f2 << endl;
            }
            else {
                f2 << registers[reg2];
            }

            programCounter += 2;
        }
        else
        {
            // Empty else block
        }
    }

    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Program completed!"; // Print message when program finishes
    ftxt.close(); // Close the input file
}
