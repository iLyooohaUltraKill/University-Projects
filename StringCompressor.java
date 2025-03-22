package org.example;

import java.util.Scanner;


public class Main {
    public static String compressString(String string){

        // If the input string is empty the method returns an empty result
        if(string.isEmpty()||string == null)
        {
            return "";
        }

        // Using StringBuilder variable instead of String,
        // because String can not be modified
        // and with StringBuilder I can easily modify it without creating a new object each modify
        StringBuilder compressed = new StringBuilder();

        // Creating a variable to count repeating characters
        int count = 1;


        // "for" loop starts iterating from the second character
        // so it can be compared to the previous one
        for(int i=1;i<string.length();i++){
            if(string.charAt(i)==string.charAt(i-1)){
                // if the character repeats itself, the count variable increments by 1
                count++;
            }
            else{
                // If the character is no longer repeating itself
                // the program adds the character with it's repeat count
                // to the end of compressed string which will be returned
                compressed.append(string.charAt(i-1));
                compressed.append(count);

                count=1; // counter resets to 1 for the new characte
            }
        }

        // "for" loop does not add the last repeating character,
        // because it only appends a character with repeating number when a different one appears after it
        // so the last character has to be added manually
        compressed.append(string.charAt(string.length()-1));
        compressed.append(count);

        // Converts StringBuilder to match variable types
        // and returns the compressed string
        return compressed.toString();
    }

    public static String decompressString(String compressed) {

        // If the input string is empty
        // the method returns an empty string
        if(compressed.isEmpty() || compressed == null){
            return "";
        }

        // Creating a variable to store the decompressed result
        StringBuilder decompressed = new StringBuilder();

        // Creating a temporary variable to store the number of character's count
        StringBuilder characterCount = new StringBuilder();

        //Index to iterate through the compressed string
        int i = 0;

            while (i<compressed.length()){
                //Extracts the character from compressed string
                char character = compressed.charAt(i);
                i++;

                //Extracts the character's count (only digits)
                while(i<compressed.length()&&Character.isDigit(compressed.charAt(i))){
                    //Appends digits to the temporary string
                    characterCount.append(compressed.charAt(i));
                    i++;
                }

                //Converts the extracted number from string into an integer
                int count = Integer.parseInt(characterCount.toString());

                    //Clears the temporary string for the next iteration
                    characterCount.setLength(0);

                    //Appends the character "count" times to the result
                    for(int j=0;j<count;j++){
                        decompressed.append(character);
                    }
            }

            //  Converts StringBuilder to String to match the types
        //  and returns the decompressed string
        return decompressed.toString();
    }


    public static void main(String[] args) {

        //code for testing both methods
        System.out.println();
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the string you want to compress: ");
        String string = sc.nextLine();
        System.out.println(string+" → "+compressString(string));

        System.out.println();
        System.out.println("Enter the string you want to decompress: ");
        String compressedString = sc.nextLine();
        System.out.println(compressedString+" → "+decompressString(compressedString));

        sc.close();
    }
}
