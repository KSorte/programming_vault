#include <iostream>
#include <unordered_map>

/*
    (Feel free to switch the language to C++ if you like.)
    In this problem, we will "decompress" a compressed image of a bunny.
    This is a single-channel (gray-scale) image with only three shades. That makes this a very low-bit image!
    Our three "shades" will be the ASCII characters ' ' (space), ':', and '@', corresponding to trinary digit
    (trit) values 0, 1, and 2.
    A single byte (8-bits) can encode 256 possibilities (2^8). Five trits (base 3 digits) require only 243 possibilities
    (3^5), and can therefore fit into a byte.
    Your program will take an image width and height and a sequence of bytes (as a python "byte-string" or "bytes object",
    which works exactly like a list of bytes), and then print the decompressed image to standard output. Each compressed byte
    corresponds to 5 decompressed characters (' ', ':', or '@') of a row of the image, in little-endian order.
    Because only 243 possibilities are required to represent these 5 characters of output, values >= 243 will not be
    present in the input.
    Due to a limitation of codeinterview.io's built-in terminal output, standard output is wrapped to 60 columns.
    Therefore, please only print out the first 60 columns of the image, skipping the latter columns, to keep the image from
    getting distorted by line-wrapping. Also be warned that longer outputs may be truncated with "..." or only print an error.
    And also be warned that leading spaces in your output will also get trimmed out.
    Given : a list of bytes - compressed image.
    Bytes are numbers - > trits -  little endian

    1. Create a map mappping 0 to ' ', 1 to ':' and 2 to '@'.
    2. max_bytes_in_row = 90/5;
    3. for loop : int i = 0, i up to end of list, i++
            convert it to the trit somehow
            get the character.
            print character
            if (i / max bytes == 4)
                std::cout<<std::endl;
  */

int main() {
    const uint32_t width = 90;
    const uint32_t height = 40;

    // KSORTE: This hexadecimal representation is only for human readability.
    const uint8_t data[] = "\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x50\xed\xf2\xf2\x50\xf1\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x50\xd8\xf2\xf2\xaa\x86\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xa1\xa2\xf2\xf2\xe2\x55\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x86\x00\xf2\x50\x99\xbd\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x86\x00\xf0\x11\x33\xbd\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x2c\x00\xed\x02\x33\xc6\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x2c\x00\xea\x01\x30\xbd\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x86\x0d\x75\x03\x66\xe1\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xa1\x24\x54\x27\x75\x75\xe4\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x1c\x00\x00\x00\x1b\x28\xe4\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x11\x00\x00\x00\x00\x00\x00\xe4\x7d\x5e\xe4\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x01\x00\x00\x00\x00\x00\x00\xd8\x02\x28\x00\xc6\xf2\xf2\xf2\xf2\xf2\xa1\x00\x00\x00\x00\x00\x00\x00\x90\x00\x51\x01\x51\xe1\xf2\xf2\xf2\xf2\x1a\x00\x00\x00\x00\x00\x00\x00\x99\x00\x00\x00\x00\x00\xf0\xf2\xf2\xf2\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xd8\xf2\xf2\xf2\x05\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\xf2\xf2\xf2\x02\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\xe1\xf2\xf2\x01\x00\x00\x00\x00\xa2\x00\x00\x00\x09\x00\x00\x03\x00\x00\xbd\xf2\xf2\x00\x00\x00\x00\x00\x00\x00\x00\x00\x09\x00\x51\x09\x00\x00\x00\xf1\x50\x00\x00\x00\x00\x00\x00\x00\x00\x00\x52\x01\x51\x76\x00\x00\x00\xed\x1a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x6c\x03\x00\x0d\x00\x00\x00\xe4\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\xca\x25\xa2\x28\x04\x00\x03\xe2\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\xca\x79\x00\xc9\x08\x00\x09\xd8\x11\x00\x00\x00\x00\x00\x00\x00\x00\x51\xcb\xa0\x00\x6c\xf2\x01\x75\xdc\x11\x00\x00\x00\x00\x00\x00\x00\x00\xbd\xf2\xf2\x28\x78\x35\x00\x6d\xf0\x1a\x00\x00\x00\x00\x00\x00\x00\x00\xed\xd7\xd3\x01\xc9\x50\x00\x75\xe5\x35\x00\x00\x00\x00\x00\x00\x00\x00\xf1\xaa\x3f\x52\xe1\xa1\x00\xc7\xf1\xa1\x00\x00\x00\x00\x00\x00\x00\xe1\xf2\x82\xa1\x04\xed\x35\x00\x79\xee\xf2\x2c\x00\x00\x00\x00\x00\x00\xee\xf2\xbb\x71\x00\xe4\x2c\x51\x51\xf1\xf2\xf2\xf2\x04\x00\x6c\x01\xbd\xf2\x86\xe9\x83\x8b\xf1\x0b\x27\x61\xee\xf2\xf2\xf2\xf2\xf2\xf2\x86\xf2\xf2\x77\xd3\x31\xd6\xf2\x1a\x42\x1b\xf1\xf2\xf2\xf2\x5f\xf1\xf2\x7d\x5e\x9d\x7d\xf1\xca\x85\xee\x7c\x7c\x5c\xf2\xf2\xf2\xf2\x86\x70\x0d\x01\x6c\x76\xc1\x6f\xe9\x7d\xf2\xd2\x50\xe1\xf2\xf2\xf2\xf2\xf2\x79\x28\x78\x58\x0c\x7f\x5b\xd4\x98\xa1\xe2\xa1\xc2\xf2\xf2\xf2\xf2\xf2\x0d\x25\x6c\x25\xca\xca\x6d\xf2\x1a\xc9\x9d\xf2\xd3\xf2\xf2\xf2\xf2\xf2\x05\x00\x00\x54\x76\x97\x79\xf2\x08\x00\xe4\x59\xf1\xf2\xf2\xf2\xf2\xf2\x01\x00\x00\x00\x52\x2d\x5b\x7a\x00\xbd\x52\x93\xf2\xf2\xf2\xf2\xf2\x11\x00\x00\x00\x00\x00\x00\x00\x00\xf0\xf2\xf2\xf2\xf2\xf2\xf2\xf2\xf2\x16\x00\x00\x00\x00\x00\x00\x6c\xf2\xf2\xf2\xf2\xf2\xf2\xf2";

    // More constants.
    const uint8_t num_trits_in_byte = 5;
    const uint8_t trit_exponent = 3;

    std::cout << (uint32_t)data[0] << std::endl;

    // Initialize an unordered map mapping from integers to the right character.
    std::unordered_map<uint8_t, char> to_char_map = {
      {0, ' '},
      {1, ':'},
      {2, '@'}
    };

    // Get max bytes that can fit in a row using width.
    int max_bytes_in_row = width/num_trits_in_byte;

    // Initialize row count to keep track of row numbers
    int row_count = 0;
    // Initialize count to keep track of byte numbers
    int count = 0;

    // Iterate until row count reaches height.s
    while(row_count < height) {

      // Get byte at count.
      // NOTE: This or any other int (uint32_t say) always stores binary data.
      // This binary data can be used as an integer even as it is stored using hexadecimal digits.
      uint8_t byte_int = data[count];

      // Get the trit digits from the integer.
      for (int j = 0; j < num_trits_in_byte; j++){
        // Get the next digit in the trit and print the associated character.
        std::cout<<to_char_map[byte_int % trit_exponent];
        // Trim the last printed digit.
        byte_int /= trit_exponent;
      }

      // If the algorithm reached the end of an row
      if (count % max_bytes_in_row == max_bytes_in_row - 1) {
        // Increment row count.
        row_count++;
        // Add a new line to start printing from next row
        std::cout<<std::endl;
      }
      count ++;
    }

    return 0;
}