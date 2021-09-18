#include <iostream>
#include <string>

// ASCII code plain text -> binary form -> group of 6 bits -> base64 conversion -> ASCII code representation

char base64_table[64] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};

// A lot of dealing with bits!
std::string toBase64(const std::string& inputString)
{
    //Declaring variables
    const char* pointer = &inputString[0];
    std::string outputString = "";
    int char_bits = 0;
    int index;
    int mask = 0b11111100000000000000000000000000;
    int zero_mask = 0b00000011111111111111111111111111;
    int shift_index = 26;
    
    for (int j = 0; j < inputString.length()/3; j++)
    {
        // Copying bits from three neighbour characters
        for (int i = 0; i < 3; i++)
        {
            char_bits ^= *(pointer + i);
            char_bits <<= 8;
        }

        for (int i = 0; i < 4; i++)
        {
            index = char_bits & mask;
            index >>= shift_index;
            index &= zero_mask;
            mask >>= 6;
            mask &= zero_mask;
            shift_index -= 6;
            outputString += base64_table[index];
        }

        char_bits = 0;
        mask = 0b11111100000000000000000000000000;
        zero_mask = 0b00000011111111111111111111111111;
        shift_index = 26;
        pointer += 3;
    }
    
    return outputString; 
}

int main()
{
    std::string plain_text = "Many hands make light work.";
    std::string encoded_text = toBase64(plain_text);
    std::cout << "Base64 encoding\n";
    std::cout << "===============\n";
    std::cout << "Plain text: " << plain_text << std::endl;
    std::cout << "Encoded text: " << encoded_text << std::endl;
}