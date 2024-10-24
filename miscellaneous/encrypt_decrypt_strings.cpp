#include <iostream>
#include <string>

/*
  Initially I thought of using a map to store letter associations with numbers. A better option
  is to work on the ASCII values of characters themselves.

  Problem Description:
  In this problem you will write a program to "encrypt" and "decrypt" strings of text using a "password".
  The cryptogram will be based on letter rotation, with the password indicating how far each letter of the plain text should be rotated.
  The letter 'a' rotates by 0, 'b' by 1, 'c' by 2, and so forth. For example, 'z' rotated by 'b' (1) would become 'a' again, since in rotation,
  'z' is followed by 'a' again.
  For example, if the password is "abc" and the plain text is "aaaaaa", then the encrypted text is "abcabc", with each letter of the password
  effecting one letter of plain text. The password is just repeated as long as necessary to encrypt all the text.
  Only letters should be encrypted, and they should maintain their case. So password "abc" would encrypt 'Hello World!' as 'Hfnlp Yosnd!'.
  Passwords are not case-sensitive, and characters in the password that are not letters are ignored/skipped/as if they were not there.
  A blank password leaves the plain text unchanged.
  Write two functions: encrypt and decrypt. Each function will take an input string and a password string, and will return the encrypted or
  decrypted string output.

Basic steps for encryption or decryption: str = string, pwd = password
  1. Normalize the password: remove non-alphabets and convert upper case to lower case.
  (Or lower case to upper case. Any approach works.)
  n = pwd.size()
  i = 0  (for password)
  2. Start a for loop over str: i = 0:
    a. if  i >= n : i = 0   (making password application cyclic)
    password character p = pwd [i]
    b. Calculate the shift as shift = p - 'a' for encryption and
    shift = 'a' - p for decryption.
    c. Add shift to s as s = (s - 'a' + shift + 26)%26 + 'a';
    A similar expression exists for upper case s.
    d. i++
  3. Return.
    (Input string is passed by reference.)

  Since encryption and decryption are so similar, I plan to write a transform function that
  takes in a boolean argument indicating encryption or decryption.
  This mitigates code repetition.
 */


/**
 * @param input_string [out] string to be encrypted or decrypted; string transformed in place.
 * @param password password for encryption or decryption.
 * @param boolean boolean indicating whether string is to be encrypted (true) or decrypted (false)
 */
void transform(std::string &input_string, std::string password, bool encrypt){
  // Variable to store processed password after removal of non-lower-case alphabets.
  std::string processed_password;
  for (auto &element : password){
    // Consider password char only if an alphabet.
    if (std::isalpha(element)){
      // Convert password char to lower case and add to processed password.
      processed_password += std::tolower(element);
    }
  }

  // Variable keeping track of password letter used for encoding.
  int pwd_count = 0;

  for (auto &s : input_string){
    // Get letter from processed password.
    auto p = processed_password[pwd_count % processed_password.size()];

    // Do not alter input string character if not alphabet.
    if (!std::isalpha(s)){
      continue;
    }

    // Get shift in integer using password letter and alphabet start as reference.
    auto letter_shift = p - 'a';

    if (!encrypt){
      // If decryption, we need to nullify the shift added during encryption.
      letter_shift *= -1;
    }

    // Alphabet reference will be used to get the integer value of a character
    // with respect to the 'a' or 'A'.
    char alpha_ref;
    if (std::islower(s)){
      alpha_ref = 'a';
    } else {
      alpha_ref = 'A';
    }

    // Normalize the string character with respect to the start of alphabet.
    s -= alpha_ref;
    // Add letter_shift and handle the case if the normalized value of s spills over 25.
    s = (s + letter_shift + 26) % 26;
    // Add the reference to get encoded letter s.
    s += alpha_ref;

    pwd_count++;
  }
  return;
}

/**
 * @param input_string [out] Encrypted input string.
 * @param password Password for encryption.
 */
void encrypt(std::string &input_string, std::string password){
  transform(input_string, password, true);
  return;
}

/**
 * @param input_string [out] Decrypted input string.
 * @param password Password for decryption.
 */
void decrypt(std::string &input_string, std::string password){
  transform(input_string, password, false);
  return;
}


int main() {
  // Test case 1.
  std::string str1 = "Hello World!";
  std::string pwd1 = "abc";
  encrypt(str1, pwd1);
  std::cout<<"Encrypted String: "<<str1<<std::endl;
  decrypt(str1, pwd1);
  std::cout<<"Decrypted String: "<<str1<<std::endl;

  // Test Case 2.
  std::string str2 = "Co@3de IntErview!#$";
  std::string pwd2 = "e3f#g";
  encrypt(str2, pwd2);
  std::cout<<"Encrypted String: "<<str2<<std::endl;
  decrypt(str2, pwd2);
  std::cout<<"Decrypted String: "<<str2<<std::endl;

  // Test Case 3: Password without special characters.
  std::string str3 = "Co@3de IntErview!#$";
  std::string pwd3 = "efg";
  encrypt(str3, pwd3);
  std::cout<<"Encrypted String: "<<str3<<std::endl;
  decrypt(str3, pwd3);
  std::cout<<"Decrypted String: "<<str3<<std::endl;
  return 0;
}

