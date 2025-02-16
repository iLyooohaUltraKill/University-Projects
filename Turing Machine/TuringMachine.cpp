#include <iostream> // console input/output
#include <fstream> // file operations
#include <string> // string operations
#include <vector> // vector operations
#include <cstdlib> // system
#include <cstdio> // get
#include <thread> // thread operations

using namespace std;

void ClearConsole()
{
    system("cls"); // clear console
};


// Single tape structure
struct TuringMachine1
{
    vector<string> State;
    vector<char> Symbol;
    vector<char> NewSymbol;
    vector<char> Direction;
    vector<string> NewState;
};

// Two tape structure
struct TuringMachine2
{
    vector<string> State;
    vector<char> Symbol1;
    vector<char> Symbol2;
    vector<char> NewSymbol1;
    vector<char> NewSymbol2;
    vector<char> Direction1;
    vector<char> Direction2;
    vector<string> NewState;
};

int main(int argc, char* argv[])
{
    string FileName = argv[1];
    bool isRunning = true;
    int ConditionCount = 0;
    int TapeCount;
    string CurrentState = "0";
    int StepCount = 0;
    int temp;
    char tempChar;
    string tempString;

    ifstream f1(FileName); // read file name
    f1 >> TapeCount; // read number of tapes

    // With one tape
    if (TapeCount == 1) // check the number of tapes: 1 or 2
    {


        TuringMachine1 tm1; // Create an object with a structure for one tape
        int HeadPosition;
        string Tape;
        string InitialTape;
        f1 >> Tape; // read the tape
        InitialTape = Tape; // create a copy of the initial tape to check for infinite loops later
        f1 >> HeadPosition; // read the initial head position
        HeadPosition--; // since array indexing starts from 0, the head position is adjusted by 1



        /////
        while (!f1.eof()) // read states and conditions
        {
            f1 >> tempString;
            tm1.State.push_back(tempString);
            f1 >> tempChar;
            tm1.Symbol.push_back(tempChar);
            f1 >> tempChar;
            tm1.NewSymbol.push_back(tempChar);
            f1 >> tempChar;
            tm1.Direction.push_back(tempChar);
            f1 >> tempString;
            tm1.NewState.push_back(tempString);
            ConditionCount++;
        }



        while (isRunning == true && HeadPosition >= 0 && HeadPosition <= Tape.size()) // loop continues until the head position goes out of bounds
        {
            StepCount++; // count the steps
            if (StepCount > Tape.size() && InitialTape == Tape && CurrentState == "0") // check for infinite loop
            {
                cout << endl;
                cout << "Program execution finished: Infinite loop detected";
                return 0;
            }
            ClearConsole(); // clear the console for the next step
            for (int i = 0; i <= ConditionCount; i++)
            {


                if (i == ConditionCount) // if the condition is not found, stop the program
                {
                    isRunning = false;
                    cout << Tape; // print the last tape
                    cout << endl;
                    for (int i = 0; i < HeadPosition; i++) // print the head at the last position
                        cout << " ";
                    cout << "^" << endl;
                    cout << "State: " << CurrentState << endl; // print the last applied state
                    cout << "Program execution finished: Reached the final state"; // print the reason for program termination
                    return 0;

                }


                if (Tape[HeadPosition] == tm1.Symbol[i] && CurrentState == tm1.State[i]) // search for the required condition and apply it
                {
                    Tape[HeadPosition] = tm1.NewSymbol[i]; // change the symbol at the head position to the new symbol specified in the state
                    CurrentState = tm1.NewState[i]; // change the current state to the new one based on the condition

                    // move the head in the required direction based on the condition
                    if (tm1.Direction[i] == 'R')
                    {
                        HeadPosition++;
                    }
                    else
                    {
                        HeadPosition--;
                        if (HeadPosition < 0)
                        {
                            isRunning = false;
                        }

                    }

                    break;
                }

            }

            cout << Tape; // print the modified tape and head
            cout << endl;
            for (int i = 0; i < HeadPosition; i++)
                cout << " ";
            cout << "^";
            this_thread::sleep_for(chrono::milliseconds(10)); // thread operation — pause the process for a while to make it easier to track tape changes



        }

        // When the program stops, a message is printed about the termination and the last tape with the head position
        cout << endl << "Program execution finished";
        cout << endl << Tape << endl;
        for (int i = 0; i < HeadPosition; i++)
        {
            cout << " ";
        }
        cout << "^";
        cout << endl;
        cout << "State: " << CurrentState;
        return 0;



    }



    if (TapeCount == 2) // if there are two tapes, the following code is executed
    {
        TuringMachine2 tm2; // create an object with a structure for two tapes
        string Tape1, Tape2;
        string InitialTape1, InitialTape2;
        f1 >> Tape1 >> Tape2; // read the tapes
        // create copies of the initial tapes to check for infinite loops later
        InitialTape1 = Tape1;
        InitialTape2 = Tape2;
        int HeadPosition1, HeadPosition2;
        f1 >> HeadPosition1 >> HeadPosition2; // read the head positions
        // since the first element of an array is 0, the head position is adjusted by 1
        HeadPosition1--;
        HeadPosition2--;

        while (!f1.eof()) // read states and conditions
        {
            f1 >> tempString;
            tm2.State.push_back(tempString);
            f1 >> tempChar;
            tm2.Symbol1.push_back(tempChar);
            f1 >> tempChar;
            tm2.Symbol2.push_back(tempChar);
            f1 >> tempChar;
            tm2.NewSymbol1.push_back(tempChar);
            f1 >> tempChar;
            tm2.NewSymbol2.push_back(tempChar);
            f1 >> tempChar;
            tm2.Direction1.push_back(tempChar);
            f1 >> tempChar;
            tm2.Direction2.push_back(tempChar);
            f1 >> tempString;
            tm2.NewState.push_back(tempString);
            ConditionCount++;
        }

        while (isRunning) // the program runs until the head goes out of bounds, or an infinite loop is detected, or the final state is reached
        {
            StepCount++; // count the steps
            if (StepCount > Tape1.size() && StepCount > Tape2.size() && InitialTape1 == Tape1 && InitialTape2 == Tape2 && CurrentState == "0") // check for infinite loop
            {
                cout << endl;
                cout << "Program execution finished: Infinite loop detected"; // message indicating infinite loop termination
                return 0;
            }
            ClearConsole(); // clear the console

            for (int i = 0; i <= ConditionCount; i++) // loop through all the conditions
            {
                if (i == ConditionCount) // if the required condition is not found, stop the program and print the tape, state, and reason for termination
                {
                    ClearConsole();
                    cout << Tape1 << endl;
                    for (int i = 0; i < HeadPosition1; i++)
                    {
                        cout << " ";
                    }
                    cout << "^" << endl;

                    cout << Tape2 << endl;
                    for (int i = 0; i < HeadPosition2; i++)
                    {
                        cout << " ";
                    }
                    cout << "^" << endl;
                    cout << "State: " << CurrentState << endl;
                    cout << "Program execution finished: Reached the final state";
                    return 0;

                }


                else if (Tape1[HeadPosition1] == tm2.Symbol1[i] && Tape2[HeadPosition2] == tm2.Symbol2[i] && CurrentState == tm2.State[i]) // search for the required state
                {
                    CurrentState = tm2.NewState[i]; // assign the new state to the current state
                    // write new symbols
                    Tape1[HeadPosition1] = tm2.NewSymbol1[i];
                    Tape2[HeadPosition2] = tm2.NewSymbol2[i];
                    // move the heads in the required direction based on the conditions
                    if (tm2.Direction1[i] == 'R')
                    {
                        HeadPosition1++;
                    }
                    else
                    {
                        HeadPosition1--;
                    }
                    if (tm2.Direction2[i] == 'R')
                    {
                        HeadPosition2++;
                    }
                    else
                    {
                        HeadPosition2--;
                    }

                    if (HeadPosition1 < 0 || HeadPosition2 < 0 || HeadPosition1 >= Tape1.size() || HeadPosition2 >= Tape2.size()) // check if the head goes out of bounds
                    {
                        // print the tapes and head positions
                        cout << Tape1 << endl;
                        for (int i = 0; i < HeadPosition1; i++)
                        {
                            cout << " ";
                        }
                        cout << "^" << endl;

                        cout << Tape2 << endl;
                        for (int i = 0; i < HeadPosition2; i++)
                        {
                            cout << " ";
                        }
                        cout << "^" << endl;
                        cout << "State: " << CurrentState << endl;
                        cout << " Program execution finished: Head went out of tape bounds"; // print the reason for stopping
                        return 0;


                    }
                    break;
                }


            }

            // if the program doesn't stop, print the tapes and head positions
            cout << Tape1 << endl;
            for (int i = 0; i < HeadPosition1; i++)
            {
                cout << " ";
            }
            cout << "^" << endl;

            cout << Tape2 << endl;
            for (int i = 0; i < HeadPosition2; i++)
            {
                cout << " ";
            }
            cout << "^" << endl;
            cout << CurrentState;

            this_thread::sleep_for(chrono::milliseconds(100)); // pause the process for a bit to make it easier to observe the tape changes
        }


    }

    f1.close(); // close the file
    return 0;
}
